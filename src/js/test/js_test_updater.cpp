#include "js/test/js_test_common.h"

#include "content/zipreader.hpp"
#include "core/xstring.h"
#include "platform/app_updater.h"

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>

static int64_t parse_int64(pcstr text) {
    return text ? std::strtoll(text, nullptr, 10) : 0;
}

static xstring __test_updater_parse_time(pcstr text) {
    int64_t value = 0;
    if (!updater::parse_utc_time(text, value)) {
        return xstring("!");
    }
    return xstring(std::to_string(value).c_str());
}
ANK_FUNCTION_1(__test_updater_parse_time);

// "<run id>|<sha>|<created>", or "!" when the answer is not understood
static xstring __test_updater_parse_run(pcstr json) {
    updater_remote_build remote;
    if (!updater::parse_latest_run(json ? json : "", remote)) {
        return xstring("!");
    }
    const std::string text = std::to_string(remote.run_id) + "|" + remote.sha + "|" + std::to_string(remote.created);
    return xstring(text.c_str());
}
ANK_FUNCTION_1(__test_updater_parse_run);

static bool __test_updater_is_newer(pcstr remote_sha, pcstr remote_created, pcstr local_sha, pcstr local_time) {
    updater_remote_build remote;
    remote.run_id = 1;
    remote.sha = remote_sha ? remote_sha : "";
    remote.created = parse_int64(remote_created);
    return updater::is_newer(remote, local_sha, parse_int64(local_time));
}
ANK_FUNCTION_4(__test_updater_is_newer);

// "<workflow>|<artifact>|<program>", or "!" for a platform without builds
static xstring __test_updater_asset(int platform) {
    updater_asset asset;
    if (!updater::asset_for((e_updater_platform)platform, asset)) {
        return xstring("!");
    }
    const std::string text = std::string(asset.workflow) + "|" + asset.artifact + "|" + asset.program;
    return xstring(text.c_str());
}
ANK_FUNCTION_1(__test_updater_asset);

static xstring __test_updater_runs_url(int platform) {
    updater_asset asset;
    updater::asset_for((e_updater_platform)platform, asset);
    return asset.workflow ? xstring(updater::runs_url(asset).c_str()) : xstring("!");
}
ANK_FUNCTION_1(__test_updater_runs_url);

static xstring __test_updater_download_url(int platform, pcstr run_id) {
    updater_asset asset;
    updater::asset_for((e_updater_platform)platform, asset);
    return asset.workflow ? xstring(updater::download_url(asset, parse_int64(run_id)).c_str()) : xstring("!");
}
ANK_FUNCTION_2(__test_updater_download_url);

static int __test_updater_current_platform() {
    return updater::current_platform();
}
ANK_FUNCTION(__test_updater_current_platform);

// the normalized path, or "!" when the entry would land outside the target folder
static xstring __test_updater_safe_path(pcstr name) {
    std::string path;
    if (!updater::safe_entry_path(name, path)) {
        return xstring("!");
    }
    return xstring(path.c_str());
}
ANK_FUNCTION_1(__test_updater_safe_path);

// entries separated by "|"
static bool __test_updater_has_program(pcstr entries, pcstr program) {
    std::vector<std::string> list;
    std::string all = entries ? entries : "";
    size_t start = 0;
    while (start <= all.size()) {
        size_t end = all.find('|', start);
        if (end == std::string::npos) {
            end = all.size();
        }
        list.push_back(all.substr(start, end - start));
        start = end + 1;
    }
    return updater::has_program(list, program ? program : "");
}
ANK_FUNCTION_2(__test_updater_has_program);

static int __test_updater_next_state(int state, int event) {
    return updater::next_state((e_updater_state)state, (e_updater_event)event);
}
ANK_FUNCTION_2(__test_updater_next_state);

static int __test_updater_button(int state) {
    return updater::button_action((e_updater_state)state);
}
ANK_FUNCTION_1(__test_updater_button);

namespace fs = std::filesystem;

// The swap tests work only under this folder, never in the game's own.
static fs::path updater_scratch_root() {
    std::error_code ec;
    return fs::temp_directory_path(ec) / "akhenaten-updater-test";
}

static bool updater_in_scratch(pcstr path, fs::path& out) {
    if (!path || !*path) {
        return false;
    }
    out = fs::u8path(path).lexically_normal();
    const std::string root = updater::to_utf8(updater_scratch_root().lexically_normal());
    const std::string full = updater::to_utf8(out);
    return full.size() > root.size() && full.compare(0, root.size(), root) == 0;
}

static xstring __test_updater_scratch() {
    std::error_code ec;
    const fs::path root = updater_scratch_root();
    fs::remove_all(root, ec);
    fs::create_directories(root, ec);
    return xstring(root.generic_u8string().c_str());
}
ANK_FUNCTION(__test_updater_scratch);

static bool __test_updater_write(pcstr path, pcstr text) {
    fs::path target;
    if (!updater_in_scratch(path, target)) {
        return false;
    }
    std::error_code ec;
    fs::create_directories(target.parent_path(), ec);
    std::ofstream file(target, std::ios::binary | std::ios::trunc);
    file << (text ? text : "");
    return (bool)file;
}
ANK_FUNCTION_2(__test_updater_write);

// the file's text, "!missing" when there is none
static xstring __test_updater_read(pcstr path) {
    fs::path target;
    std::error_code ec;
    if (!updater_in_scratch(path, target) || !fs::is_regular_file(target, ec)) {
        return xstring("!missing");
    }
    std::ifstream file(target, std::ios::binary);
    std::string text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return xstring(text.c_str());
}
ANK_FUNCTION_1(__test_updater_read);

static bool __test_updater_exists(pcstr path) {
    fs::path target;
    std::error_code ec;
    return updater_in_scratch(path, target) && fs::exists(target, ec);
}
ANK_FUNCTION_1(__test_updater_exists);

static std::vector<updater_moved_file> g_test_updater_moved;

static bool __test_updater_swap(pcstr staging, pcstr install) {
    fs::path from, to;
    g_test_updater_moved.clear();
    if (!updater_in_scratch(staging, from) || !updater_in_scratch(install, to)) {
        return false;
    }
    return updater::swap_in(from, to, g_test_updater_moved);
}
ANK_FUNCTION_2(__test_updater_swap);

static void __test_updater_drop_asides(pcstr leftovers) {
    fs::path list;
    if (updater_in_scratch(leftovers, list)) {
        updater::drop_asides(g_test_updater_moved, fs::path(), list);
    }
}
ANK_FUNCTION_1(__test_updater_drop_asides);

static void __test_updater_remove_leftovers(pcstr leftovers) {
    fs::path list;
    if (updater_in_scratch(leftovers, list)) {
        updater::remove_leftovers(list);
    }
}
ANK_FUNCTION_1(__test_updater_remove_leftovers);

static bool __test_updater_write_hex(pcstr path, pcstr hex) {
    fs::path target;
    if (!updater_in_scratch(path, target) || !hex) {
        return false;
    }
    std::string bytes;
    for (size_t i = 0; hex[i] && hex[i + 1]; i += 2) {
        const char pair[3] = {hex[i], hex[i + 1], 0};
        bytes.push_back((char)std::strtol(pair, nullptr, 16));
    }
    std::error_code ec;
    fs::create_directories(target.parent_path(), ec);
    std::ofstream file(target, std::ios::binary | std::ios::trunc);
    file.write(bytes.data(), (std::streamsize)bytes.size());
    return (bool)file;
}
ANK_FUNCTION_2(__test_updater_write_hex);

// the archive's entry names as the updater reads them, separated by "|"
static xstring __test_updater_zip_names(pcstr path) {
    fs::path target;
    if (!updater_in_scratch(path, target)) {
        return xstring("!");
    }
    vfs::ZipArchive archive(vfs::path(updater::to_utf8(target).c_str()));
    std::string all;
    for (const xstring& name : archive.names()) {
        all += (all.empty() ? "" : "|") + std::string(name.c_str());
    }
    return xstring(all.c_str());
}
ANK_FUNCTION_1(__test_updater_zip_names);

static xstring __test_updater_zip_read(pcstr path, int index) {
    fs::path target;
    if (!updater_in_scratch(path, target)) {
        return xstring("!");
    }
    vfs::ZipArchive archive(vfs::path(updater::to_utf8(target).c_str()));
    if (index < 0 || index >= (int)archive.names().size()) {
        return xstring("!");
    }
    vfs::reader file = archive.createAndOpenFile((unsigned int)index, "rb");
    if (!file) {
        return xstring("!unreadable");
    }
    return xstring(std::string((const char*)file->data(), (size_t)file->size()).c_str());
}
ANK_FUNCTION_2(__test_updater_zip_read);
