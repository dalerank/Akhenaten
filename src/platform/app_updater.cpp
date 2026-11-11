#include "platform/app_updater.h"

#include "content/vfs.h"
#include "content/zipreader.hpp"
#include "core/app.h"
#include "core/log.h"
#include "game/game.h"
#include "game/game_config.h"
#include "game/game_events.h"
#include "js/js_events.h"
#include "js/js_game.h"
#include "net/http_client.h"
#include "platform/arguments.h"
#include "platform/platform.h"

#include <algorithm>
#include <atomic>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <thread>

#if defined(GAME_PLATFORM_WIN)
#include <windows.h>
#elif defined(GAME_PLATFORM_LINUX) || defined(GAME_PLATFORM_MACOSX)
#include <unistd.h>
#endif
#if defined(GAME_PLATFORM_MACOSX)
#include <mach-o/dyld.h>
#include <sys/xattr.h>
#endif

#if defined(GAME_UPDATER)                                                                          \
  && (defined(GAME_PLATFORM_WIN) || defined(GAME_PLATFORM_LINUX) || defined(GAME_PLATFORM_MACOSX))
#define GAME_UPDATER_ACTIVE 1
#endif

#ifndef GAME_BUILD_COMMIT
#define GAME_BUILD_COMMIT ""
#endif
#ifndef GAME_BUILD_COMMIT_TIME
#define GAME_BUILD_COMMIT_TIME 0
#endif

namespace fs = std::filesystem;

struct event_updater_state_changed {
    int state;
};
ANK_SCRIPT_EVENT(event_updater_state_changed, state)

static constexpr pcstr updater_repo = "dalerank/Akhenaten";

e_updater_state updater::next_state(e_updater_state state, e_updater_event event) {
    switch (state) {
    case UPDATER_OFF:
        return event == UPDATER_EV_START ? UPDATER_CHECKING : state;
    case UPDATER_CHECKING:
        switch (event) {
        case UPDATER_EV_NO_ANSWER:
            return UPDATER_NO_ANSWER;
        case UPDATER_EV_SAME_BUILD:
            return UPDATER_UP_TO_DATE;
        case UPDATER_EV_NEWER_BUILD:
            return UPDATER_AVAILABLE;
        default:
            return state;
        }
    case UPDATER_AVAILABLE:
    case UPDATER_FAILED:
        return event == UPDATER_EV_DOWNLOAD ? UPDATER_DOWNLOADING : state;
    case UPDATER_DOWNLOADING:
        switch (event) {
        case UPDATER_EV_DOWNLOAD_OK:
            return UPDATER_READY;
        case UPDATER_EV_DOWNLOAD_FAILED:
            return UPDATER_FAILED;
        default:
            return state;
        }
    default:
        return state;
    }
}

e_updater_button updater::button_action(e_updater_state state) {
    switch (state) {
    case UPDATER_READY:
        return UPDATER_BUTTON_RESTART;
    case UPDATER_AVAILABLE:
    case UPDATER_FAILED:
        return UPDATER_BUTTON_DOWNLOAD_THEN_RESTART;
    case UPDATER_DOWNLOADING:
        return UPDATER_BUTTON_RESTART_WHEN_READY;
    default:
        return UPDATER_BUTTON_NONE;
    }
}

e_updater_platform updater::current_platform() {
#if defined(GAME_PLATFORM_WIN64)
    return UPDATER_PLATFORM_WINDOWS;
#elif defined(GAME_PLATFORM_LINUX)
    return UPDATER_PLATFORM_LINUX;
#elif defined(GAME_PLATFORM_MACOSX) && (defined(__aarch64__) || defined(__arm64__))
    return UPDATER_PLATFORM_MACOS_ARM;
#elif defined(GAME_PLATFORM_MACOSX)
    return UPDATER_PLATFORM_MACOS_X64;
#else
    return UPDATER_PLATFORM_NONE;
#endif
}

// The workflows and artifacts of .github/workflows/akhenaten_{windows,linux,mac_arm,mac_x64}.yml.
bool updater::asset_for(e_updater_platform platform, updater_asset& out) {
    switch (platform) {
    case UPDATER_PLATFORM_WINDOWS:
        out = {"akhenaten_windows", "windows_build", "akhenaten.exe"};
        return true;
    case UPDATER_PLATFORM_LINUX:
        out = {"akhenaten_linux", "linux_build", "akhenaten.linux"};
        return true;
    case UPDATER_PLATFORM_MACOS_ARM:
        out = {"akhenaten_mac_arm", "macos_arm_build", "akhenaten.app/Contents/MacOS/akhenaten"};
        return true;
    case UPDATER_PLATFORM_MACOS_X64:
        out = {"akhenaten_mac_x64", "macos_x64_build", "akhenaten.app/Contents/MacOS/akhenaten"};
        return true;
    default:
        out = {};
        return false;
    }
}

std::string updater::runs_url(const updater_asset& asset) {
    return std::string("https://api.github.com/repos/") + updater_repo + "/actions/workflows/" + asset.workflow
           + ".yml/runs?branch=master&event=push&status=success&per_page=1";
}

std::string updater::download_url(const updater_asset& asset, int64_t run_id) {
    return std::string("https://nightly.link/") + updater_repo + "/actions/runs/" + std::to_string(run_id) + "/"
           + asset.artifact + ".zip";
}

std::string updater::download_page_url(const updater_asset& asset) {
    return std::string("https://nightly.link/") + updater_repo + "/workflows/" + asset.workflow + "/master/"
           + asset.artifact + ".zip";
}

// "YYYY-MM-DDTHH:MM:SSZ", as the GitHub API writes its times
bool updater::parse_utc_time(pcstr text, int64_t& out) {
    if (!text) {
        return false;
    }
    int y, mo, d, h, mi, s;
    char z = 0;
    if (std::sscanf(text, "%4d-%2d-%2dT%2d:%2d:%2d%c", &y, &mo, &d, &h, &mi, &s, &z) != 7 || z != 'Z') {
        return false;
    }
    if (mo < 1 || mo > 12 || d < 1 || d > 31 || h > 23 || mi > 59 || s > 60 || h < 0 || mi < 0 || s < 0) {
        return false;
    }
    // days from civil (H. Hinnant)
    const int64_t yy = y - (mo <= 2);
    const int64_t era = (yy >= 0 ? yy : yy - 399) / 400;
    const int64_t yoe = yy - era * 400;
    const int64_t doy = (153 * (mo + (mo > 2 ? -3 : 9)) + 2) / 5 + d - 1;
    const int64_t doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
    const int64_t days = era * 146097 + doe - 719468;
    out = days * 86400 + h * 3600 + mi * 60 + s;
    return true;
}

static size_t json_value_after_key(const std::string& json, size_t from, pcstr key) {
    const std::string quoted = std::string("\"") + key + "\"";
    size_t pos = json.find(quoted, from);
    if (pos == std::string::npos) {
        return pos;
    }
    pos += quoted.size();
    while (pos < json.size() && (json[pos] == ' ' || json[pos] == '\t' || json[pos] == '\r' || json[pos] == '\n')) {
        ++pos;
    }
    if (pos >= json.size() || json[pos] != ':') {
        return std::string::npos;
    }
    ++pos;
    while (pos < json.size() && (json[pos] == ' ' || json[pos] == '\t' || json[pos] == '\r' || json[pos] == '\n')) {
        ++pos;
    }
    return pos < json.size() ? pos : std::string::npos;
}

static bool json_string_after_key(const std::string& json, size_t from, pcstr key, std::string& out) {
    const size_t pos = json_value_after_key(json, from, key);
    if (pos == std::string::npos || json[pos] != '"') {
        return false;
    }
    const size_t end = json.find('"', pos + 1);
    if (end == std::string::npos) {
        return false;
    }
    out = json.substr(pos + 1, end - pos - 1);
    return true;
}

// The first run of the Actions API's "workflow_runs": its id is the run object's first key, before any nested object.
bool updater::parse_latest_run(const std::string& json, updater_remote_build& out) {
    size_t runs = json_value_after_key(json, 0, "workflow_runs");
    if (runs == std::string::npos || json[runs] != '[') {
        return false;
    }
    size_t first = json.find_first_not_of(" \t\r\n", runs + 1);
    if (first == std::string::npos || json[first] != '{') {
        return false;
    }
    const size_t id_pos = json_value_after_key(json, first, "id");
    if (id_pos == std::string::npos) {
        return false;
    }
    const int64_t id = std::strtoll(json.c_str() + id_pos, nullptr, 10);
    std::string sha, created;
    if (id <= 0 || !json_string_after_key(json, first, "head_sha", sha)
        || !json_string_after_key(json, first, "created_at", created)) {
        return false;
    }
    int64_t created_time = 0;
    if (sha.size() != 40 || !parse_utc_time(created.c_str(), created_time)) {
        return false;
    }
    out.run_id = id;
    out.sha = sha;
    out.created = created_time;
    return true;
}

// The run is created when its commit is pushed, so it is later than the commit time of any build pushed before it;
// the same commit is never newer than itself.
bool updater::is_newer(const updater_remote_build& remote, pcstr local_sha, int64_t local_time) {
    if (remote.run_id <= 0 || remote.sha.empty()) {
        return false;
    }
    if (local_sha && remote.sha == local_sha) {
        return false;
    }
    return remote.created > local_time;
}

bool updater::safe_entry_path(pcstr name, std::string& out) {
    if (!name || !*name) {
        return false;
    }
    std::string path = name;
    for (char& c : path) {
        if (c == '\\') {
            c = '/';
        }
    }
    while (path.compare(0, 2, "./") == 0) {
        path.erase(0, 2);
    }
    if (path.empty() || path[0] == '/' || path.find(':') != std::string::npos) {
        return false;
    }
    size_t start = 0;
    while (start <= path.size()) {
        size_t end = path.find('/', start);
        if (end == std::string::npos) {
            end = path.size();
        }
        const std::string part = path.substr(start, end - start);
        if (part == "..") {
            return false;
        }
        if (part.empty() && end != path.size()) {
            return false;
        }
        start = end + 1;
    }
    if (path.back() == '/') {
        return false;
    }
    out = path;
    return true;
}

bool updater::has_program(const std::vector<std::string>& entries, pcstr program) {
    for (const std::string& entry : entries) {
        if (entry == program) {
            return true;
        }
    }
    return false;
}

std::string updater::to_utf8(const std::filesystem::path& path) {
    return path.u8string();
}

static fs::path aside_of(const fs::path& target) {
    fs::path aside = target;
    aside += ".old";
    return aside;
}

static void roll_back(const std::vector<updater_moved_file>& done) {
    std::error_code ec;
    for (auto it = done.rbegin(); it != done.rend(); ++it) {
        fs::remove(it->target, ec);
        if (it->had_old) {
            fs::rename(it->aside, it->target, ec);
        }
    }
}

// Renames every file of from that exists under to aside (*.old) and moves the new one in; the running program can be
// renamed but not overwritten on Windows, and keeps its old inode on Linux and macOS. On failure all is rolled back.
bool updater::swap_in(const fs::path& from, const fs::path& to, std::vector<updater_moved_file>& done) {
    std::error_code ec;
    std::vector<fs::path> files;
    for (auto it = fs::recursive_directory_iterator(from, ec); !ec && it != fs::recursive_directory_iterator();
      it.increment(ec)) {
        if (it->is_regular_file(ec)) {
            files.push_back(it->path());
        }
    }
    if (ec) {
        logs::error("[updater] cannot list %s: %s", to_utf8(from).c_str(), ec.message().c_str());
        return false;
    }
    std::sort(files.begin(), files.end());
    for (const fs::path& source : files) {
        const fs::path target = to / fs::relative(source, from, ec);
        const fs::path aside = aside_of(target);
        fs::create_directories(target.parent_path(), ec);
        const bool had_old = fs::exists(target, ec);
        if (had_old) {
            fs::remove(aside, ec);
            fs::rename(target, aside, ec);
            if (ec) {
                logs::error("[updater] cannot move %s aside: %s", to_utf8(target).c_str(), ec.message().c_str());
                roll_back(done);
                return false;
            }
        }
        fs::rename(source, target, ec);
        if (ec) {
            logs::error("[updater] cannot put %s in place: %s", to_utf8(target).c_str(), ec.message().c_str());
            if (had_old) {
                fs::rename(aside, target, ec);
            }
            roll_back(done);
            return false;
        }
        done.push_back({target, aside, had_old});
    }
    return true;
}

void updater::drop_asides(const std::vector<updater_moved_file>& done, const fs::path& old_bundle,
  const fs::path& leftovers_list) {
    std::error_code ec;
    std::vector<std::string> left;
    for (const updater_moved_file& file : done) {
        if (file.had_old && !fs::remove(file.aside, ec)) {
            left.push_back(to_utf8(file.aside));
        }
    }
    if (!old_bundle.empty()) {
        fs::remove_all(old_bundle, ec);
        if (fs::exists(old_bundle, ec)) {
            left.push_back(to_utf8(old_bundle));
        }
    }
    if (!left.empty()) {
        std::ofstream list(leftovers_list, std::ios::app);
        for (const std::string& path : left) {
            list << path << "\n";
        }
    }
}

// The files the last install could not delete (the running program on Windows, loaded libraries).
void updater::remove_leftovers(const fs::path& leftovers_list) {
    std::error_code ec;
    {
        std::ifstream list(leftovers_list);
        std::string line;
        while (list && std::getline(list, line)) {
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            if (!line.empty()) {
                fs::remove_all(fs::u8path(line), ec);
            }
        }
    }
    fs::remove(leftovers_list, ec);
}

#if !defined(GAME_UPDATER_ACTIVE)

void app_updater_start(int, char**) {
}

void app_updater_finish() {
}

e_updater_state app_updater_state() {
    return UPDATER_OFF;
}

static void app_updater_apply() {
}

static xstring app_updater_remote_date() {
    return xstring();
}

#else

namespace {

    struct updater_data_t {
        std::atomic<int> state{UPDATER_OFF};
        std::atomic<bool> restart_after_download{false};
        std::atomic<bool> restart_requested{false};
        std::mutex lock;
        updater_asset asset;
        updater_remote_build remote;
        bool can_swap = false;
        bool auto_download = true;
        fs::path program;
        fs::path bundle;
        fs::path install_dir;
        fs::path work_dir;
        fs::path staging_dir;
        fs::path start_dir;
        std::vector<std::string> argv;
    };

    updater_data_t g_updater;


    using updater::to_utf8;

    fs::path leftovers_list() {
        return g_updater.install_dir / "update_old.txt";
    }

    void notify(e_updater_state state) {
        game.add_frame_end_event([state]() { events::emit(event_updater_state_changed{state}); });
    }

    bool fire(e_updater_event event) {
        std::lock_guard<std::mutex> guard(g_updater.lock);
        const e_updater_state from = (e_updater_state)g_updater.state.load();
        const e_updater_state to = updater::next_state(from, event);
        if (to == from) {
            return false;
        }
        g_updater.state = to;
        notify(to);
        return true;
    }

    fs::path running_program() {
#if defined(GAME_PLATFORM_WIN)
        wchar_t buffer[32768];
        const DWORD length = GetModuleFileNameW(nullptr, buffer, (DWORD)(sizeof(buffer) / sizeof(buffer[0])));
        if (length == 0 || length >= sizeof(buffer) / sizeof(buffer[0])) {
            return {};
        }
        return fs::path(std::wstring(buffer, length));
#elif defined(GAME_PLATFORM_LINUX)
        std::error_code ec;
        fs::path path = fs::read_symlink("/proc/self/exe", ec);
        return ec ? fs::path() : path;
#elif defined(GAME_PLATFORM_MACOSX)
        char buffer[4096] = {0};
        uint32_t size = sizeof(buffer);
        if (_NSGetExecutablePath(buffer, &size) != 0) {
            return {};
        }
        std::error_code ec;
        fs::path path = fs::canonical(buffer, ec);
        return ec ? fs::path(buffer) : path;
#endif
    }

    fs::path bundle_of(const fs::path& program) {
        const std::string text = program.generic_string();
        const size_t app = text.find(".app/Contents/MacOS/");
        if (app == std::string::npos) {
            return {};
        }
        return fs::path(text.substr(0, app + 4));
    }

    bool install_writable(std::string& why) {
#if defined(GAME_PLATFORM_MACOSX)
        if (g_updater.program.generic_string().find("/AppTranslocation/") != std::string::npos) {
            why = "macOS runs the game from App Translocation (move the app out of Downloads first)";
            return false;
        }
        if (g_updater.bundle.empty()) {
            why = "the game does not run from an .app bundle, and the build artifact holds only the bundle";
            return false;
        }
#endif
        std::error_code ec;
        fs::create_directories(g_updater.work_dir, ec);
        if (ec) {
            why = "cannot create " + to_utf8(g_updater.work_dir) + ": " + ec.message();
            return false;
        }
        const fs::path probe = g_updater.work_dir / "write_probe";
        {
            std::ofstream file(probe, std::ios::binary);
            file << "1";
            if (!file) {
                why = "cannot write into " + to_utf8(g_updater.install_dir);
                return false;
            }
        }
        fs::remove(probe, ec);
        fs::remove(g_updater.work_dir, ec);
        return true;
    }

    bool write_file(const fs::path& path, const void* data, size_t size) {
        std::error_code ec;
        fs::create_directories(path.parent_path(), ec);
        std::ofstream file(path, std::ios::binary | std::ios::trunc);
        if (size > 0) {
            file.write((const char*)data, (std::streamsize)size);
        }
        return (bool)file;
    }

    bool download_and_stage() {
        std::error_code ec;
        fs::remove_all(g_updater.work_dir, ec);
        fs::create_directories(g_updater.staging_dir, ec);

        const std::string url = updater::download_url(g_updater.asset, g_updater.remote.run_id);
        logs::info("[updater] downloading %s", url.c_str());
        const http_get_result response = http_get(url.c_str(), 900, false);
        if (!response.ok || response.body.empty()) {
            logs::error("[updater] download failed (HTTP code %ld)", response.http_code);
            return false;
        }

        const fs::path zip_path = g_updater.work_dir / "update.zip";
        if (!write_file(zip_path, response.body.data(), response.body.size())) {
            logs::error("[updater] cannot write %s", to_utf8(zip_path).c_str());
            return false;
        }

        vfs::ZipArchive archive(vfs::path(to_utf8(zip_path).c_str()));
        if (!archive.isValid()) {
            logs::error("[updater] the download is not a zip archive");
            return false;
        }

        const std::vector<xstring>& entries = archive.entries();
        std::vector<std::string> names(entries.size());
        for (size_t i = 0; i < entries.size(); ++i) {
            pcstr name = entries[i].c_str();
            const size_t length = name ? std::strlen(name) : 0;
            if (length == 0 || name[length - 1] == '/' || name[length - 1] == '\\') {
                continue;
            }
            if (!updater::safe_entry_path(name, names[i])) {
                logs::error("[updater] the archive names a path outside its folder: %s", name);
                return false;
            }
        }
        if (!updater::has_program(names, g_updater.asset.program)) {
            logs::error("[updater] the archive has no %s", g_updater.asset.program);
            return false;
        }

        int extracted = 0;
        for (size_t i = 0; i < names.size(); ++i) {
            if (names[i].empty()) {
                continue;
            }
            vfs::reader file = archive.createAndOpenFile((unsigned int)i, "rb");
            if (!file) {
                logs::error("[updater] cannot unpack %s", names[i].c_str());
                return false;
            }
            const fs::path target = g_updater.staging_dir / fs::u8path(names[i]);
            if (!write_file(target, file->data(), (size_t)file->size())) {
                logs::error("[updater] cannot write %s", to_utf8(target).c_str());
                return false;
            }
#if !defined(GAME_PLATFORM_WIN)
            // GitHub artifacts do not keep the file modes
            fs::permissions(target, fs::perms::owner_exec | fs::perms::group_exec | fs::perms::others_exec,
              fs::perm_options::add, ec);
#endif
            ++extracted;
        }
        fs::remove(zip_path, ec);
        logs::info("[updater] unpacked %d files into %s", extracted, to_utf8(g_updater.staging_dir).c_str());
        return true;
    }

    void post_restart_quit() {
        g_updater.restart_requested = true;
        game.add_frame_end_event([]() { app_post_event(USER_EVENT_QUIT); });
    }

    void download_thread() {
        const bool ok = download_and_stage();
        if (!ok) {
            std::error_code ec;
            fs::remove_all(g_updater.work_dir, ec);
        }
        fire(ok ? UPDATER_EV_DOWNLOAD_OK : UPDATER_EV_DOWNLOAD_FAILED);
        if (ok) {
            logs::info("[updater] the build of run %lld is ready, it is installed when the game closes",
              (long long)g_updater.remote.run_id);
            if (g_updater.restart_after_download) {
                post_restart_quit();
            }
        }
    }

    void start_download() {
        if (fire(UPDATER_EV_DOWNLOAD)) {
            std::thread(download_thread).detach();
        }
    }

    void check_thread() {
        const std::string url = updater::runs_url(g_updater.asset);
        const http_get_result response = http_get(url.c_str(), 15, false);
        updater_remote_build remote;
        if (!response.ok || !updater::parse_latest_run(response.body, remote)) {
            logs::warn("[updater] no answer about the newest build (HTTP code %ld)", response.http_code);
            fire(UPDATER_EV_NO_ANSWER);
            return;
        }
        logs::info("[updater] newest build: run %lld, commit %s; this build: commit %s", (long long)remote.run_id,
          remote.sha.c_str(), GAME_BUILD_COMMIT);
        if (!updater::is_newer(remote, GAME_BUILD_COMMIT, (int64_t)GAME_BUILD_COMMIT_TIME)) {
            fire(UPDATER_EV_SAME_BUILD);
            return;
        }
        {
            std::lock_guard<std::mutex> guard(g_updater.lock);
            g_updater.remote = remote;
        }
        fire(UPDATER_EV_NEWER_BUILD);
        if (g_updater.can_swap && g_updater.auto_download) {
            start_download();
        }
    }

#if defined(GAME_PLATFORM_MACOSX)
    void clear_quarantine(const fs::path& root) {
        static const char attribute[] = "com.apple.quarantine";
        std::error_code ec;
        auto clear = [](const fs::path& path) {
            if (getxattr(path.c_str(), attribute, nullptr, 0, 0, XATTR_NOFOLLOW) >= 0) {
                removexattr(path.c_str(), attribute, XATTR_NOFOLLOW);
                logs::info("[updater] cleared the quarantine of %s", path.c_str());
            }
        };
        clear(root);
        for (auto it = fs::recursive_directory_iterator(root, ec); !ec && it != fs::recursive_directory_iterator();
          it.increment(ec)) {
            clear(it->path());
        }
    }
#endif

    bool install() {
        std::error_code ec;
        std::vector<updater_moved_file> done;
        fs::path old_bundle;
        if (!g_updater.bundle.empty()) {
            const fs::path staged_bundle = g_updater.staging_dir / "akhenaten.app";
            old_bundle = g_updater.bundle;
            old_bundle += ".old";
            fs::remove_all(old_bundle, ec);
            fs::rename(g_updater.bundle, old_bundle, ec);
            if (ec) {
                logs::error("[updater] cannot move the app aside: %s", ec.message().c_str());
                return false;
            }
            fs::rename(staged_bundle, g_updater.bundle, ec);
            if (ec) {
                logs::error("[updater] cannot put the new app in place: %s", ec.message().c_str());
                fs::rename(old_bundle, g_updater.bundle, ec);
                return false;
            }
        }
        if (!updater::swap_in(g_updater.staging_dir, g_updater.install_dir, done)) {
            if (!old_bundle.empty()) {
                fs::remove_all(g_updater.bundle, ec);
                fs::rename(old_bundle, g_updater.bundle, ec);
            }
            fs::remove_all(g_updater.work_dir, ec);
            logs::error("[updater] the update is rolled back");
            return false;
        }
        updater::drop_asides(done, old_bundle, leftovers_list());
#if defined(GAME_PLATFORM_MACOSX)
        clear_quarantine(g_updater.bundle);
#endif
        fs::remove_all(g_updater.work_dir, ec);
        logs::info("[updater] the build of run %lld is installed", (long long)g_updater.remote.run_id);
        return true;
    }

    // The update puts the program under its packaged name, which a renamed copy of the game does not have.
    fs::path installed_program() {
        std::error_code ec;
        const fs::path packaged = g_updater.install_dir / fs::u8path(g_updater.asset.program);
        return (g_updater.bundle.empty() && fs::exists(packaged, ec)) ? packaged : g_updater.program;
    }

    void relaunch() {
        logs::info("[updater] restarting %s in %s", to_utf8(installed_program()).c_str(),
          to_utf8(g_updater.start_dir).c_str());
        logs::flush();
#if defined(GAME_PLATFORM_WIN)
        std::wstring command = GetCommandLineW();
        const std::wstring program = installed_program().wstring();
        const std::wstring dir = g_updater.start_dir.wstring();
        STARTUPINFOW startup{};
        startup.cb = sizeof(startup);
        PROCESS_INFORMATION process{};
        if (!CreateProcessW(program.c_str(), command.data(), nullptr, nullptr, FALSE, 0, nullptr,
              dir.empty() ? nullptr : dir.c_str(), &startup, &process)) {
            logs::error("[updater] cannot start the new program (error %lu)", (unsigned long)GetLastError());
            return;
        }
        CloseHandle(process.hThread);
        CloseHandle(process.hProcess);
#else
        std::vector<std::string> args = g_updater.argv;
        std::string path = installed_program().string();
#if defined(GAME_PLATFORM_MACOSX)
        // "open -n" starts the bundle through LaunchServices as Finder would, as the old akhenaten-updater did.
        if (!g_updater.bundle.empty()) {
            std::vector<std::string> open_args = {"open", "-n", g_updater.bundle.string()};
            if (args.size() > 1) {
                open_args.push_back("--args");
                open_args.insert(open_args.end(), args.begin() + 1, args.end());
            }
            args = open_args;
            path = "/usr/bin/open";
        }
#endif
        std::vector<char*> raw;
        for (std::string& arg : args) {
            raw.push_back(arg.data());
        }
        raw.push_back(nullptr);
        if (!g_updater.start_dir.empty() && chdir(g_updater.start_dir.c_str()) != 0) {
            logs::warn("[updater] cannot return to %s", g_updater.start_dir.c_str());
        }
        execv(path.c_str(), raw.data());
        logs::error("[updater] cannot start %s", path.c_str());
#endif
    }

} // namespace

void app_updater_start(int argc, char** argv) {
    if (g_args.is_integral_tests()) {
        return;
    }
    if (g_args.is("no_update", false)) {
        logs::info("[updater] off (--no-update)");
        return;
    }
    if (!updater::asset_for(updater::current_platform(), g_updater.asset)) {
        return;
    }
    g_updater.program = running_program();
    if (g_updater.program.empty()) {
        logs::warn("[updater] cannot find the running program");
        return;
    }
    g_updater.bundle = bundle_of(g_updater.program);
    g_updater.install_dir = g_updater.bundle.empty() ? g_updater.program.parent_path() : g_updater.bundle.parent_path();
    g_updater.work_dir = g_updater.install_dir / "update_tmp";
    g_updater.staging_dir = g_updater.work_dir / "staging";
    std::error_code ec;
    g_updater.start_dir = fs::current_path(ec);
    for (int i = 0; i < argc; ++i) {
        g_updater.argv.push_back(argv[i] ? argv[i] : "");
    }

    updater::remove_leftovers(leftovers_list());
    fs::remove_all(g_updater.work_dir, ec);

    std::string why;
    g_updater.can_swap = install_writable(why);
    if (!g_updater.can_swap) {
        logs::warn("[updater] cannot update in place: %s; \"Update now\" opens the download page", why.c_str());
    }
    g_updater.auto_download = !!game_features::gameopt_auto_update;
    if (!g_updater.auto_download) {
        logs::info("[updater] the automatic download is off (gameopt_auto_update)");
    }

    fire(UPDATER_EV_START);
    std::thread(check_thread).detach();
}

void app_updater_finish() {
    if (g_updater.state != UPDATER_READY) {
        return;
    }
    install();
    if (g_updater.restart_requested) {
        relaunch();
    }
}

e_updater_state app_updater_state() {
    return (e_updater_state)g_updater.state.load();
}

static void app_updater_apply() {
    if (!g_updater.can_swap) {
        platform.open_url(updater::download_page_url(g_updater.asset).c_str(), "");
        return;
    }
    switch (updater::button_action(app_updater_state())) {
    case UPDATER_BUTTON_RESTART:
        post_restart_quit();
        break;
    case UPDATER_BUTTON_DOWNLOAD_THEN_RESTART:
        g_updater.restart_after_download = true;
        start_download();
        break;
    case UPDATER_BUTTON_RESTART_WHEN_READY:
        g_updater.restart_after_download = true;
        break;
    default:
        break;
    }
}

static xstring app_updater_remote_date() {
    std::lock_guard<std::mutex> guard(g_updater.lock);
    if (g_updater.remote.created <= 0) {
        return xstring();
    }
    const time_t created = (time_t)g_updater.remote.created;
    char text[32] = {0};
    std::tm* utc = std::gmtime(&created);
    if (utc) {
        std::strftime(text, sizeof(text), "%Y-%m-%d %H:%M UTC", utc);
    }
    return xstring(text);
}

#endif

static bool __updater_available() {
#if defined(GAME_UPDATER_ACTIVE)
    return true;
#else
    return false;
#endif
}
ANK_FUNCTION(__updater_available)

static int __updater_state() {
    return app_updater_state();
}
ANK_FUNCTION(__updater_state)

static void __updater_apply() {
    app_updater_apply();
}
ANK_FUNCTION(__updater_apply)

static xstring __updater_remote_date() {
    return app_updater_remote_date();
}
ANK_FUNCTION(__updater_remote_date)
