#include "mods.h"

#include "content/content.h"
#include "content/reader.h"
#include "content/zipreader.hpp"
#include "graphics/imagepak_holder.h"
#include "core/log.h"
#include "js/js.h"
#include "game/game_config.h"
#include "core/settings_vars.h"
#include "content/vfs.h"
#include "window/popup_dialog.h"
#include "platform/platform.h"

#include <regex>
#include <map>

#ifdef GAME_PLATFORM_WIN
#include <curl/curl.h>
#endif

flat_map<xstring, mod_info, 32> g_mods_list;

void mods_add_remote_file(xstring name, xstring uri) {
    auto it = g_mods_list.find(name);

    if (it != g_mods_list.end()) {
        return;
    }

    auto &new_mod = g_mods_list[name];
    new_mod.downloaded = false;
    new_mod.url = uri;
    new_mod.name = name;
    new_mod.path = "";
}

vfs::path mods_get_path(xstring name) {
    auto it = g_mods_list.find(name);
    if (it == g_mods_list.end()) {
        return "";
    }
    return it->second.path.c_str();
}

bool mods_get_enabled(xstring name) {
    auto it = g_mods_list.find(name);
    if (it == g_mods_list.end()) {
        return false;
    }
    return it->second.enabled;
}

void mods_set_enabled(xstring name, bool enabled) {
    auto it = g_mods_list.find(name);
    if (it == g_mods_list.end()) {
        return;
    }
    it->second.enabled = enabled;
    mods_save();
}

void mods_toggle(xstring name) {
    auto it = g_mods_list.find(name);
    if (it == g_mods_list.end()) {
        return;
    }

    it->second.enabled = !it->second.enabled;
    mods_save();
}

void mods_remount() {
    for (const auto &it : g_mods_list) {
        if (!it.second.downloaded) {
            continue;
        }

        if (it.second.enabled) {
            vfs::mount_pack(it.second.path.c_str());

            auto &modpack = g_image_data->pak_list[it.second.useridx];            
            if (!modpack.handle) {
                modpack.entries_num = it.second.entries_num;
                modpack.index = it.second.start_index;
                modpack.id = it.second.useridx;
                modpack.name = it.second.name;
                modpack.delayed = true;
                modpack.custom = true;
            }

            for (const auto &s: it.second.scripts) {
                js_vm_reload_file(s.c_str());
            }
        } else {
            vfs::umount_pack(it.second.path.c_str());

            auto &modpack = g_image_data->pak_list[it.second.useridx];
            if (modpack.handle) {
                delete modpack.handle;

                modpack.entries_num = 0;
                modpack.index = 0;
                modpack.id = 0;
                modpack.delayed = true;
                modpack.name = xstring();
            }

            for (const auto &s : it.second.scripts) {
                js_vm_reload_file(s.c_str());
            }
        }
    }

    mods_save();
}

void mods_init() {
    g_mods_list.clear();

    auto append_mods = [] (pcstr dir, const dir_listing *files) {
        for (int i = 0; i < files->num_files; ++i) {
            bstring128 mod_name_short(files->files[i]);
            mod_name_short.replace_str(".sgx", "");
            mod_name_short.replace_str(dir, "");

            xstring mod_name(mod_name_short.c_str());
            auto it = g_mods_list.find(mod_name);
            if (it == g_mods_list.end()) {
                mod_info &mod = g_mods_list[mod_name];
                mod.path.printf("Mods/%s", files->files[i]);
                mod.name = mod_name;
                mod.useridx = imagepak::get_max_useridx() + 1;
                mod.start_index = imagepak::get_maxseen_imgid() + 1;
                mod.entries_num = imagepak::get_entries_num(mod.path);

                imagepak::useridx_update(mod.useridx);
                imagepak::update_max_imgid(mod.start_index + mod.entries_num);

                vfs::path full_path = vfs::path::resolve(mod.path.c_str());
                if (full_path.empty()) {
                    continue;
                }

                vfs::ZipArchive archive(full_path);
                if (!archive.isValid()) {
                    continue;
                }

                const auto &entries = archive.entries();
                mod.scripts.clear();

                for (const auto &entry : entries) {
                    if (vfs::file_has_extension(entry.c_str(), "js")) {
                        mod.scripts.push_back(entry);
                    }
                }
            } else {
                logs::warn("WARN! Duplicate mod %s", mod_name.c_str());
            }
        }
    };

    const dir_listing *sgx_files = vfs::dir_find_files_with_extension("Mods", "sgx");
    append_mods("Mods/", sgx_files);
}

const mod_info &mods_find(xstring hash) {
    auto it = g_mods_list.find(hash);
    if (it != g_mods_list.end()) {
        return it->second;
    }

    static mod_info dummy;
    return dummy;
}

mod_reader mods_find_script(pcstr script_path, bool find_in_enabled) {
    if (!script_path || !*script_path) {
        return {};
    }

    for (const auto &it : g_mods_list) {
        if (!it.second.enabled) {
            continue;
        }

        if (!it.second.exist(script_path)) {
            continue;
        }

        vfs::path mod_script_path(it.second.path.c_str(), "/", script_path);
        vfs::reader reader = vfs::file_open(mod_script_path, "rt");
        if (reader) {
            return { mod_script_path.c_str(), reader };
        }
    }

    return {};
}

void mods_save() {
    std::string enabled_mods;
    for (const auto &it : g_mods_list) {
        if (it.second.enabled) {
            enabled_mods.append(it.first.c_str());
            enabled_mods.append(",");
        }
    }
    game_features::gameopt_enabled_mods = enabled_mods.c_str();
    game_features::save();
}

void mods_load() {
    xstring enabled_mods = game_features::gameopt_enabled_mods.to_string();

    svector<bstring64, 128> mod_names;
    string_to_array_t(mod_names, enabled_mods.c_str(), ',');
    
    // Restore enabled status for each mod
    for (const auto &name : mod_names) {
        mods_set_enabled(name.c_str(), true);
    }
}

#ifdef GAME_PLATFORM_WIN
// Callback function for curl to write response data
static size_t mods_refresh_available_list_cb(void *contents, size_t size, size_t nmemb, std::string *data) {
    size_t totalSize = size * nmemb;
    data->append((char *)contents, totalSize);
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
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, mods_refresh_available_list_cb);
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
            namePositions.push_back({ pos, (*nameIter)[1].str() });
        }

        std::sregex_iterator urlIter(readBuffer.begin(), readBuffer.end(), urlRegex);
        for (; urlIter != std::sregex_iterator(); ++urlIter) {
            size_t pos = urlIter->position();
            urlPositions.push_back({ pos, (*urlIter)[1].str() });
        }

        // Match each .sgx name with the next download_url after it
        for (const auto &namePair : namePositions) {
            // Find the first URL that comes after this name
            for (const auto &urlPair : urlPositions) {
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
    for (const auto &pair : modMap) {
        logs::info("* %s|%s", pair.first.c_str(), pair.second.c_str());
        bstring128 mod_name = pair.first.c_str();
        mod_name.replace_str(".sgx", "");
        mods_add_remote_file(mod_name.c_str(), pair.second.c_str());
    }
    logs::info("Total: %d mod(s)", modMap.size());

    xstring result; result.printf("Found %zu mods on GitHub", modMap.size());
    popup_dialog::show_ok("Mods", result);

    mods_remount();
#else
    popup_dialog::show_ok("Error", "Mods list download not supported on this platform.");
#endif
}