#include "main_menu.h"

#include "editor/editor.h"
#include "core/log.h"
#include "core/profiler.h"
#include "platform/platform.h"
#include "graphics/elements/ui.h"
#include "graphics/graphics.h"
#include "graphics/window.h"
#include "graphics/screen.h"
#include "graphics/image.h"
#include "game/game.h"
#include "game/settings.h"
#include "game/game_config.h"
#include "core/app.h"
#include "window/records.h"
#include "window/popup_dialog.h"
#include "window/player_selection.h"
#include "window/file_dialog.h"
#include "window/window_features.h"
#include "window/window_city.h"
#include "sound/sound.h"
#include "sound/sound_city.h"
#include "io/gamestate/boilerplate.h"
#include "graphics/elements/ui_js.h"
#include "resource/icons.h"
#include "js/js_game.h"
#include <regex>

#ifdef GAME_HAVE_CURL
#include <curl/curl.h>
#endif

main_menu_screen g_main_menu;

struct event_totals_commits_loaded { int current_commit; };
struct event_changelog_loaded { xstring change_log; };
ANK_REGISTER_STRUCT_WRITER(event_totals_commits_loaded, current_commit);
ANK_REGISTER_STRUCT_WRITER(event_changelog_loaded, change_log);

#ifdef GAME_HAVE_CURL
// Callback function for curl to write response data
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* data) {
    size_t totalSize = size * nmemb;
    data->append((char*)contents, totalSize);
    return totalSize;
}

// Callback function for curl to write header data
size_t HeaderCallback(char* buffer, size_t size, size_t nitems, std::string* headers) {
    size_t totalSize = size * nitems;
    headers->append(buffer, totalSize);
    return totalSize;
}
#endif

std::string main_menu_download_changelog() {
#ifdef GAME_HAVE_CURL
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    std::string url = "https://raw.githubusercontent.com/dalerank/Akhenaten/master/changelog.txt";

    curl = curl_easy_init();
    if (!curl) {
        logs::error("curl_easy_init failed");
        return "Failed to initialize HTTP client.";
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Akhenaten/1.0");
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);

    // Windows Schannel will automatically use system certificates
    res = curl_easy_perform(curl);

    long httpCode = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);

    if (res != CURLE_OK) {
        logs::error("curl_easy_perform failed: %s", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        return "Failed to download changelog from GitHub.";
    }

    curl_easy_cleanup(curl);

    if (httpCode == 200 && !readBuffer.empty()) {
        logs::info("Changelog downloaded successfully (%zu bytes)", readBuffer.size());
        return readBuffer;
    } else {
        logs::error("Failed to download changelog (HTTP code: %ld)", httpCode);
        return "Failed to download changelog from GitHub.";
    }
#else
    return "Changelog download not supported on this platform (libcurl is not available).";
#endif
}

int main_menu_get_total_commits(pcstr owner, pcstr repo) {
#ifdef GAME_HAVE_CURL
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    std::string headers;
    std::string url;
    url = "https://api.github.com/repos/";
    url += owner;
    url += "/";
    url += repo;
    url += "/commits?per_page=1";

    curl = curl_easy_init();
    if (!curl) {
        logs::error("curl_easy_init failed");
        return -1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, HeaderCallback);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headers);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Akhenaten/1.0");
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);

    // Windows Schannel will automatically use system certificates
    res = curl_easy_perform(curl);

    long httpCode = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);

    curl_easy_cleanup(curl);

    if (res != CURLE_OK || httpCode != 200) {
        logs::error("Unable to fetch commits (curl error: %s, HTTP code: %ld)", 
                   res != CURLE_OK ? curl_easy_strerror(res) : "OK", httpCode);
        return -1;
    }

    // Parse Link header for pagination info
    std::regex linkRegex(R"(<([^>]+)>; rel="last")");
    std::smatch match;

    if (std::regex_search(headers, match, linkRegex)) {
        std::string lastPageUrl = match[1].str();
        std::regex pageRegex(R"(&page=(\d+))");
        if (std::regex_search(lastPageUrl, match, pageRegex)) {
            return std::stoi(match[1].str());
        }
    }

    // If no pagination info, assume 1 page
    return 1;
#else
    return -1;
#endif
}

void __game_download_latest_version() {
#ifdef GAME_PLATFORM_WIN
    game.mt.detach_task([] () {
        ShellExecuteA(0, "Open", "update_binary_windows.cmd", 0, 0, SW_SHOW);
    });
#endif // GAME_PLATFORM_WIN
}
ANK_FUNCTION(__game_download_latest_version)

int main_menu_screen::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

    g_render.clear_screen();
    return 0;
}

void main_menu_screen::draw_foreground(UiFlags flags) {
    ui.begin_frame();
    ui.draw();
}

void main_menu_screen::init() {
    // Download changelog in background
    game.mt.detach_task([&, this] () {
        xstring changelog = main_menu_download_changelog().c_str();
        game.add_frame_end_event([this, changelog] () {
            ui.event(event_changelog_loaded{ changelog });
        });
    });

    // Check for updates
    game.mt.detach_task([&] () {
        int current_commit = main_menu_get_total_commits("dalerank", "Akhenaten");
        game.add_frame_end_event([this, current_commit] () {
            ui.event(event_totals_commits_loaded{ current_commit });
        });
    });

    autoconfig_window::init();
}

void main_menu_screen::show(bool restart_music) {
    sound_city_stop();
    sound_city_init();
    if (restart_music) {
        g_sound.play_intro();
    }

    static window_type window = {
        WINDOW_MAIN_MENU,
        [] (int flags) { instance().draw_background(flags); },
        [] (int flags) { instance().draw_foreground(flags); },
        [] (auto m, auto h) { instance().ui_handle_mouse(m); },
    };

    instance().init();
    window_show(&window);
}

main_menu_screen &main_menu_screen::instance() {
    return g_main_menu;
}
