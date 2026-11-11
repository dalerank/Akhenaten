#pragma once

#include "core/bstring.h"

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

// The game's own update. Compiled in only for CI builds (AKHENATEN_UPDATER, CMakeLists.txt): at start a thread asks
// the GitHub Actions API for the newest successful master push run of this platform's workflow, compares its date
// with the commit this build was made from, and downloads that run's artifact from nightly.link into
// <install>/update_tmp/staging. The swap happens in this process after the game ends: the running files are renamed
// to *.old, the staged ones moved in (rolled back on failure); "Update now" also restarts the game afterwards.

enum e_updater_state {
    UPDATER_OFF,
    UPDATER_CHECKING,
    UPDATER_NO_ANSWER,
    UPDATER_UP_TO_DATE,
    UPDATER_AVAILABLE,
    UPDATER_DOWNLOADING,
    UPDATER_READY,
    UPDATER_FAILED,
};

enum e_updater_event {
    UPDATER_EV_START,
    UPDATER_EV_NO_ANSWER,
    UPDATER_EV_SAME_BUILD,
    UPDATER_EV_NEWER_BUILD,
    UPDATER_EV_DOWNLOAD,
    UPDATER_EV_DOWNLOAD_OK,
    UPDATER_EV_DOWNLOAD_FAILED,
};

enum e_updater_button {
    UPDATER_BUTTON_NONE,
    UPDATER_BUTTON_RESTART,
    UPDATER_BUTTON_DOWNLOAD_THEN_RESTART,
    UPDATER_BUTTON_RESTART_WHEN_READY,
};

enum e_updater_platform {
    UPDATER_PLATFORM_NONE,
    UPDATER_PLATFORM_WINDOWS,
    UPDATER_PLATFORM_LINUX,
    UPDATER_PLATFORM_MACOS_ARM,
    UPDATER_PLATFORM_MACOS_X64,
};

struct updater_asset {
    pcstr workflow = nullptr;
    pcstr artifact = nullptr;
    // must be inside the artifact, relative to its root
    pcstr program = nullptr;
};

struct updater_remote_build {
    int64_t run_id = 0;
    std::string sha;
    int64_t created = 0;
};

struct updater_moved_file {
    std::filesystem::path target;
    std::filesystem::path aside;
    bool had_old;
};

namespace updater {
    e_updater_state next_state(e_updater_state state, e_updater_event event);
    e_updater_button button_action(e_updater_state state);
    e_updater_platform current_platform();
    bool asset_for(e_updater_platform platform, updater_asset& out);
    std::string runs_url(const updater_asset& asset);
    std::string download_url(const updater_asset& asset, int64_t run_id);
    std::string download_page_url(const updater_asset& asset);
    bool parse_utc_time(pcstr text, int64_t& out);
    bool parse_latest_run(const std::string& json, updater_remote_build& out);
    bool is_newer(const updater_remote_build& remote, pcstr local_sha, int64_t local_time);
    bool safe_entry_path(pcstr name, std::string& out);
    bool has_program(const std::vector<std::string>& entries, pcstr program);
    std::string to_utf8(const std::filesystem::path& path);
    bool swap_in(const std::filesystem::path& from, const std::filesystem::path& to,
      std::vector<updater_moved_file>& done);
    void drop_asides(const std::vector<updater_moved_file>& done, const std::filesystem::path& old_bundle,
      const std::filesystem::path& leftovers_list);
    void remove_leftovers(const std::filesystem::path& leftovers_list);
} // namespace updater

void app_updater_start(int argc, char** argv);
void app_updater_finish();
e_updater_state app_updater_state();
