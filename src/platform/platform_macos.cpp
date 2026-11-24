#include "platform.h"

#if defined(GAME_PLATFORM_MACOSX)

#include "core/bstring.h"
#include "core/log.h"

#include <SDL.h>
#include <pwd.h>

#include "content/vfs.h"
#include <unistd.h>

#if defined(GAME_PLATFORM_IOS)
#include "platform/innoextract_util.h"

#include <cstdlib>
#include <filesystem>
#include <string>
#include <vector>
#endif

uint32_t platform_init_sdl_flags() {
    return 0;
}

void platform_post_hint_init() {
#if defined(GAME_PLATFORM_IOS)
    SDL_SetHint(SDL_HINT_ORIENTATIONS, "LandscapeLeft LandscapeRight");
#endif
}

void platform_setup_begin() {
}

void platform_run_init_callback() {
}

void platform_run_per_frame_callback() {
}

int platform_poll_event(CoreEvent* event) {
    return SDL_PollEvent(reinterpret_cast<SDL_Event*>(event));
}

#if defined(GAME_PLATFORM_IOS)
pcstr platform_request_initial_data_directory() {
    pcstr home = getenv("HOME");
    if (!home || !*home) {
        return nullptr;
    }

    namespace fs = std::filesystem;
    const fs::path documents = fs::path(home) / "Documents";
    std::vector<std::string> candidates{documents.string()};
    std::error_code ec;
    for (const auto& entry : fs::directory_iterator(documents, ec)) {
        const std::string name = entry.path().filename().string();
        if (entry.is_directory(ec) && !name.empty() && name[0] != '.') {
            candidates.push_back(entry.path().string());
        }
    }

    static bstring512 found;
    for (const auto& dir : candidates) {
        if (innoextract::has_required_game_files(dir.c_str())) {
            found = dir.c_str();
            return found.c_str();
        }
    }
    for (const auto& dir : candidates) {
        if (innoextract::has_pharaoh_data(dir.c_str())) {
            found = dir.c_str();
            return found.c_str();
        }
    }
    logs::info("ios: no Pharaoh data in %s or its folders", documents.string().c_str());
    return nullptr;
}
#else
pcstr platform_request_initial_data_directory() {
    return nullptr;
}
#endif

void platform_append_startup_log(pcstr message) {
}

void platform_hide_startup_log() {
}

bool platform_run_main_loop(platform_pump_frame_cb pump_frame, platform_should_continue_cb should_continue) {
    while (should_continue()) {
        pump_frame();
    }
    return true;
}

void platform_resolve_user_directory(bstring512& dir) {
    char* pref = SDL_GetPrefPath("", "Akhenaten");
    if (pref) {
        dir = pref;
        SDL_free(pref);
    } else {
        logs::warn("platform::user_directory: SDL_GetPrefPath failed, using cwd");
        dir = ".";
    }
}

#if defined(GAME_PLATFORM_IOS)
void platform_t::open_url(pcstr url, pcstr prefix) {
    SDL_OpenURL(url);
}

pcstr platform_t::get_steam_path() {
    return "";
}
#else
void platform_t::open_url(pcstr url, pcstr prefix) {
    bstring256 command("open \"", url, "\" &");
    [[maybe_unused]] auto result = ::system(command.c_str());
    //result;
}

pcstr platform_t::get_steam_path() {
    const passwd *pw = getpwuid(getuid());
    if (!pw || !pw->pw_dir) {
        return {};
    }

    vfs::path home_dir(pw->pw_dir);

    static vfs::path steam_path;
    steam_path.concat(home_dir.c_str(), "/Library/Application Support/Steam");

    return steam_path.c_str();
}
#endif

void platform_show_virtual_keyboard(const uint8_t *text, int max_length) {
    (void)text;
    (void)max_length;
#if defined(GAME_PLATFORM_IOS)
    SDL_StopTextInput();
    SDL_StartTextInput();
#endif
}

void platform_hide_virtual_keyboard(void) {
#if defined(GAME_PLATFORM_IOS)
    if (SDL_IsTextInputActive()) {
        SDL_StopTextInput();
    }
#endif
}

#endif