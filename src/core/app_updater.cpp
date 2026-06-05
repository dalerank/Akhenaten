#include "core/app.h"
#include "core/log.h"
#include "game/game.h"
#include "js/js_game.h"
#include "net/http_client.h"
#include "content/vfs.h"
#include "content/zipreader.hpp"

#ifdef GAME_PLATFORM_WIN
#include <windows.h>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <string>
#endif

struct app_updater_module_t {
    void download_latest_version(pcstr url);
};

#ifdef GAME_PLATFORM_WIN
namespace {

// Directory of the running executable (forward slashes, no trailing slash).
std::string updater_exe_dir() {
    char exe_path[MAX_PATH] = { 0 };
    GetModuleFileNameA(nullptr, exe_path, MAX_PATH);
    std::string path(exe_path);
    for (char &c : path) {
        if (c == '\\') {
            c = '/';
        }
    }
    const size_t slash = path.find_last_of('/');
    return (slash == std::string::npos) ? path : path.substr(0, slash);
}

std::string updater_exe_path() {
    char exe_path[MAX_PATH] = { 0 };
    GetModuleFileNameA(nullptr, exe_path, MAX_PATH);
    return std::string(exe_path);
}

std::string updater_exe_name() {
    const std::string path = updater_exe_path();
    const size_t slash = path.find_last_of("/\\");
    return (slash == std::string::npos) ? path : path.substr(slash + 1);
}

std::string updater_to_native(std::string path) {
    for (char &c : path) {
        if (c == '/') {
            c = '\\';
        }
    }
    return path;
}

bool updater_write_file(const std::string &path, const void *data, size_t size) {
    FILE *f = vfs::file_open_os(path.c_str(), "wb");
    if (!f) {
        logs::error("[updater] cannot create file %s", path.c_str());
        return false;
    }
    const size_t written = (size > 0) ? fwrite(data, 1, size, f) : 0;
    fclose(f);
    if (written != size) {
        logs::error("[updater] short write to %s (%zu/%zu)", path.c_str(), written, size);
        return false;
    }
    return true;
}

bool updater_download(const std::string &zip_path, const std::string &url) {
    logs::info("[updater] downloading from %s", url.c_str());
    const http_get_result response = http_get(url.c_str(), 120, false);
    if (!response.ok || response.body.empty()) {
        logs::error("[updater] download failed (HTTP code: %ld)", response.http_code);
        return false;
    }

    if (!updater_write_file(zip_path, response.body.data(), response.body.size())) {
        return false;
    }

    logs::info("[updater] downloaded %zu bytes -> %s", response.body.size(), zip_path.c_str());
    return true;
}

bool updater_extract(const std::string &zip_path, const std::string &staging_dir) {
    vfs::ZipArchive archive(vfs::path(zip_path.c_str()));
    if (!archive.isValid()) {
        logs::error("[updater] invalid or empty archive %s", zip_path.c_str());
        return false;
    }

    const std::vector<xstring> &entries = archive.entries();
    int extracted = 0;
    for (unsigned int i = 0; i < entries.size(); ++i) {
        pcstr name = entries[i].c_str();
        if (!name || name[0] == 0) {
            continue; // placeholder entry produced by central-directory scan
        }

        const size_t len = std::strlen(name);
        if (name[len - 1] == '/' || name[len - 1] == '\\') {
            continue; // directory entry
        }

        vfs::reader r = archive.createAndOpenFile(i, "rb");
        if (!r) {
            logs::warn("[updater] failed to decompress %s", name);
            continue;
        }

        const std::string out_path = staging_dir + "/" + name;
        const size_t slash = out_path.find_last_of('/');
        if (slash != std::string::npos) {
            vfs::create_folders(out_path.substr(0, slash).c_str());
        }

        if (!updater_write_file(out_path, r->data(), (size_t)r->size())) {
            return false;
        }
        ++extracted;
    }

    if (extracted == 0) {
        logs::error("[updater] no files extracted from %s", zip_path.c_str());
        return false;
    }

    logs::info("[updater] extracted %d files -> %s", extracted, staging_dir.c_str());
    return true;
}

// Generates the minimal external helper that performs the parts that the running
// process cannot do itself: wait for this exe to exit, copy the staged files over
// the installation, restart the game and clean up after itself.
bool updater_spawn_swap_and_restart(const std::string &work_dir, const std::string &staging_dir, const std::string &zip_path) {
    const std::string cmd_path = work_dir + "/apply_update.cmd";

    const std::string n_staging = updater_to_native(staging_dir);
    const std::string n_exe_dir = updater_to_native(updater_exe_dir());
    const std::string n_exe_path = updater_to_native(updater_exe_path());
    const std::string n_zip = updater_to_native(zip_path);
    const std::string n_work = updater_to_native(work_dir);
    const unsigned long pid = GetCurrentProcessId();

    std::string script;
    script += "@echo off\r\n";
    script += "setlocal\r\n";
    script += "set \"PID=" + std::to_string(pid) + "\"\r\n";
    script += ":wait\r\n";
    script += "tasklist /FI \"PID eq %PID%\" /NH 2>nul | find /I \"" + updater_exe_name() + "\" >nul\r\n";
    script += "if not errorlevel 1 (\r\n";
    script += "  timeout /t 1 /nobreak >nul\r\n";
    script += "  goto wait\r\n";
    script += ")\r\n";
    script += "xcopy /E /Y /I /Q \"" + n_staging + "\\*\" \"" + n_exe_dir + "\\\" >nul\r\n";
    script += "rmdir /S /Q \"" + n_work + "\" >nul 2>&1\r\n";
    script += "del /Q \"" + n_zip + "\" >nul 2>&1\r\n";
    script += "start \"\" \"" + n_exe_path + "\"\r\n";
    script += "(goto) 2>nul & del \"%~f0\"\r\n";

    if (!updater_write_file(cmd_path, script.data(), script.size())) {
        return false;
    }

    const std::string n_cmd = updater_to_native(cmd_path);
    const HINSTANCE result = ShellExecuteA(nullptr, "open", n_cmd.c_str(), nullptr, n_exe_dir.c_str(), SW_HIDE);
    if ((INT_PTR)result <= 32) {
        logs::error("[updater] failed to launch helper script (code %lld)", (long long)(INT_PTR)result);
        return false;
    }

    logs::info("[updater] helper launched, waiting for game to exit");
    return true;
}

void updater_run(const std::string &url) {
    const std::string work_dir = updater_exe_dir() + "/update_tmp";
    const std::string staging_dir = work_dir + "/staging";
    const std::string zip_path = work_dir + "/windows_build.zip";

    std::error_code ec;
    std::filesystem::remove_all(work_dir, ec); // drop leftovers from a previous run
    vfs::create_folders(staging_dir.c_str());

    if (!updater_download(zip_path, url)) {
        return;
    }

    if (!updater_extract(zip_path, staging_dir)) {
        return;
    }

    if (!updater_spawn_swap_and_restart(work_dir, staging_dir, zip_path)) {
        return;
    }

    // Quit so the helper can replace the now-unlocked executable and restart it.
    game.add_frame_end_event([]() {
        app_post_event(USER_EVENT_QUIT);
    });
}

} // namespace
#endif // GAME_PLATFORM_WIN

void app_updater_module_t::download_latest_version(pcstr url) {
#ifdef GAME_PLATFORM_WIN
    if (!url || !*url) {
        logs::error("[updater] update URL is empty");
        return;
    }
    const std::string url_str(url);
    game.mt.detach_task([url_str]() {
        updater_run(url_str);
    });
#endif
}

void __game_download_latest_version(pcstr url) {
    static app_updater_module_t mod;
    mod.download_latest_version(url);
}
ANK_FUNCTION_1(__game_download_latest_version)

void ANK_REGISTER_APPLICATION_MODULE(register_app_updater_module) {
}
