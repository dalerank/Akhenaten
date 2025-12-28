#include "window_mods.h"

#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "game/player.h"
#include "game/game.h"
#include "content/content.h"
#include "content/reader.h"
#include "core/log.h"
#include "window/popup_dialog.h"
#include "js/js_game.h"
#include "content/dir.h"
#include "core/xstring.h"
#include "core/flat_map.h"
#include "content/mods.h"
#include "window/popup_dialog.h"

#include <vector>
#include <map>
#include <regex>
#include <sstream>
#include <algorithm>

#ifdef GAME_PLATFORM_WIN
#include <curl/curl.h>
#endif

ui::mods_window g_mods_window;

void ui::mods_window::init() {
    autoconfig_window::init();

    auto mods = ui["mods"].dcast_scrollable_list();
    if (mods) {
        mods->clear();
        mods->onrefill([] (escrollable_list::entry_data_vec &r) {
            for (auto &mod : g_mods_list) {
                r.push_back({ mod.second.name, 0 });
            }
        });

        mods->refill();
        mods->onrender_item([] (int index, int flags, const scrollable_list::entry_data &entry, vec2i pos, e_font font) {
            const mod_info &mod = mods_find(entry.text);

            bstring128 text;
            text.printf("[%s] %s", mod.enabled ? "ON" : "OFF", mod.name.c_str());
            
            text_draw(text.c_str(), pos.x, pos.y, font, 0);
        });

        mods->onclick_double_ex_item([] (scrollable_list::entry_data* item) {
            if (!item) {
                return;
            }

            mods_toggle(item->text);
            mods_remount();
        });
    }
}

int ui::mods_window::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

    painter ctx = game.painter();
    ImageDraw::img_background(ctx, image_id_from_group(GROUP_SCORES_BACKGROUND));

    return 0;
}

void ui::mods_window::show() {
    static window_type instance = {
        WINDOW_PLAYER_SELECTION,
        [] (int flags) { g_mods_window.draw_background(flags); },
        [] (int flags) { g_mods_window.ui_draw_foreground(flags); },
        [] (const mouse *m, const hotkeys *h) { g_mods_window.ui_handle_mouse(m); }
    };

    g_mods_window.init();
    window_show(&instance);
}

void window_mods_show(void) {
    ui::mods_window::show();
}

void platform_unpack_scripts() {
    xstring vpath = vfs::platform_unpack_scripts();
    popup_dialog::show_ok("#scripts_unpacked_to", vpath);
}

#ifdef GAME_PLATFORM_WIN
// Callback function for curl to write response data
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* data) {
    size_t totalSize = size * nmemb;
    data->append((char*)contents, totalSize);
    return totalSize;
}
#endif

void mods_refresh_available_list() {
#ifdef GAME_PLATFORM_WIN
    CURLcode res;
    std::string readBuffer;
    std::string url = "https://api.github.com/repos/dalerank/Akhenaten/contents/mods";
    
    CURL *curl = curl_easy_init();
    if (!curl) {
        logs::error("curl_easy_init failed");
        popup_dialog::show_ok("Error", "Failed to initialize HTTP client.");
        return;
    }
    
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Akhenaten/1.0");
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 15L);  // Timeout for connection
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);        // Total timeout for the operation
    
    res = curl_easy_perform(curl);
    
    long httpCode = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    
    if (res != CURLE_OK) {
        logs::error("curl_easy_perform failed: %s", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        
        // Provide more specific error message
        xstring errorMsg;
        if (res == CURLE_OPERATION_TIMEDOUT) {
            errorMsg = "Connection timeout. Please check your internet connection and try again.";
        } else if (res == CURLE_COULDNT_CONNECT) {
            errorMsg = "Could not connect to GitHub. Please check your internet connection.";
        } else {
            errorMsg.printf("Failed to download mods list: %s", curl_easy_strerror(res));
        }
        popup_dialog::show_ok("Error", errorMsg);
        return;
    }
    
    curl_easy_cleanup(curl);
    
    if (httpCode != 200 || readBuffer.empty()) {
        logs::error("Failed to download mods list (HTTP code: %ld)", httpCode);
        popup_dialog::show_ok("Error", "Failed to download mods list from GitHub.");
        return;
    }
    
    // Parse JSON response to extract .sgx files
    // GitHub API returns an array of file objects, each with "name" and "download_url"
    // We need to match each .sgx file name with its corresponding download_url
    std::map<std::string, std::string> modMap; // name -> download_url
    
    // Find all file objects and extract .sgx files with their URLs
    // Pattern: match "name": "filename.sgx" followed by "download_url": "url" within the same object
    // We'll use a pattern that matches name and download_url that are close together
    std::regex modPattern("\"name\"\\s*:\\s*\"([^\"]+\\.sgx)\"[^}]*\"download_url\"\\s*:\\s*\"([^\"]+)\"");
    std::sregex_iterator iter(readBuffer.begin(), readBuffer.end(), modPattern);
    std::sregex_iterator end;
    
    for (; iter != end; ++iter) {
        std::string modName = (*iter)[1].str();
        std::string downloadUrl = (*iter)[2].str();
        modMap[modName] = downloadUrl;
    }
    
    // Fallback: if multiline JSON breaks the regex, try a different approach
    if (modMap.empty()) {
        // Extract positions of .sgx names and find the nearest download_url after each name
        std::regex nameRegex("\"name\"\\s*:\\s*\"([^\"]+\\.sgx)\"");
        std::regex urlRegex("\"download_url\"\\s*:\\s*\"([^\"]+)\"");
        
        std::vector<std::pair<size_t, std::string>> namePositions; // position, name
        std::vector<std::pair<size_t, std::string>> urlPositions;  // position, url
        
        std::sregex_iterator nameIter(readBuffer.begin(), readBuffer.end(), nameRegex);
        for (; nameIter != std::sregex_iterator(); ++nameIter) {
            size_t pos = nameIter->position();
            namePositions.push_back({pos, (*nameIter)[1].str()});
        }
        
        std::sregex_iterator urlIter(readBuffer.begin(), readBuffer.end(), urlRegex);
        for (; urlIter != std::sregex_iterator(); ++urlIter) {
            size_t pos = urlIter->position();
            urlPositions.push_back({pos, (*urlIter)[1].str()});
        }
        
        // Match each .sgx name with the next download_url after it
        for (const auto& namePair : namePositions) {
            // Find the first URL that comes after this name
            for (const auto& urlPair : urlPositions) {
                if (urlPair.first > namePair.first) {
                    modMap[namePair.second] = urlPair.second;
                    break;
                }
            }
        }
    }
    
    if (modMap.empty()) {
        popup_dialog::show_ok("Mods List", "No mods found on GitHub.");
        return;
    }
    
    logs::info("Available mods on GitHub:");
    for (const auto& pair : modMap) {
        logs::info( "* %s", pair.first.c_str());
    }
    logs::info("Total: %d mod(s)", modMap.size());
    
    xstring result; result.printf("Found %zu mods on GitHub", modMap.size());
    popup_dialog::show_ok("Mods", result);
#else
    popup_dialog::show_ok("Error", "Mods list download not supported on this platform.");
#endif
}

ANK_FUNCTION(window_mods_show)
ANK_FUNCTION(platform_unpack_scripts)
ANK_FUNCTION(mods_refresh_available_list)