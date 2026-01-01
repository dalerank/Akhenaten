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
#include "core/archive.h"
#include "game/game.h"

#include <regex>
#include <map>
#include <fstream>
#include <filesystem>

#ifdef GAME_PLATFORM_WIN
#include <curl/curl.h>
#endif

flat_map<xstring, mod_info, 32> g_mods_list;
mods_config ANK_VARIABLE_N(g_mods_config, "mods");

mod_info& mods_add_remote_file(xstring name, xstring uri) {
    auto it = g_mods_list.find(name);

    if (it != g_mods_list.end()) {
        return it->second;
    }

    auto &new_mod = g_mods_list[name];
    new_mod.path = "";
    new_mod.downloaded = false;
    new_mod.url = uri;
    new_mod.name = name;

    return new_mod;
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

#ifdef GAME_PLATFORM_WIN
struct mod_download_progress_data {
    mod_info *mod;
    std::ofstream *file;
    size_t total_size;
    size_t downloaded_size;

    mod_download_progress_data() : mod(nullptr), file(nullptr), total_size(0), downloaded_size(0) {}
};

static size_t mods_download_write_callback(void* contents, size_t size, size_t nmemb, mod_download_progress_data * data) {
    if (!data || !data->file || !data->file->is_open()) {
        return 0;
    }
    
    size_t totalSize = size * nmemb;
    data->file->write((char*)contents, totalSize);
    data->downloaded_size += totalSize;
    
    // Update progress (0-100)
    if (data->total_size > 0 && data->mod) {
        uint8_t progress = (uint8_t)((data->downloaded_size * 100) / data->total_size);
        data->mod->download_progress = progress;
    }
    
    return totalSize;
}

static int mods_download_progress_callback(void* clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t, curl_off_t) {
    auto data = (mod_download_progress_data *)clientp;
    if (!data || !data->mod) {
        return 0;
    }
    
    if (dltotal > 0) {
        data->total_size = (size_t)dltotal;
        uint8_t progress = (uint8_t)((dlnow * 100) / dltotal);
        data->mod->download_progress = progress;
    }
    
    return 0;
}
#endif

void mods_download_mod_async(xstring name) {
    auto it = g_mods_list.find(name);
    if (it == g_mods_list.end()) {
        logs::error("Mod not found: %s", name.c_str());
        return;
    }

    mod_info& mod = it->second;
    
    if (mod.downloaded) {
        logs::warn("Mod already downloaded: %s", name.c_str());
        return;
    }
    
    if (mod.url.empty()) {
        logs::error("No download URL for mod: %s", name.c_str());
        return;
    }
    
    if (mod.download_progress > 0 && mod.download_progress < 100) {
        logs::warn("Mod download already in progress: %s", name.c_str());
        return;
    }

#ifdef GAME_PLATFORM_WIN
    // Start download in background thread
    game.mt.detach_task([name]() {
        auto it = g_mods_list.find(name);
        if (it == g_mods_list.end()) {
            return;
        }
        
        mod_info& mod = it->second;
        mod.download_progress = 1; // Start downloading
        
        // Get base path and create Mods directory
        pcstr base_path = vfs::platform_file_manager_get_base_path();
        if (!base_path) {
            logs::error("Failed to get base path for mods download");
            mod.download_progress = 0;
            return;
        }
        
        std::filesystem::path mods_dir = std::filesystem::path(base_path) / "Mods";
        std::filesystem::create_directories(mods_dir);
        
        // Create filename with .sgx extension
        bstring256 filename;
        filename.printf("%s.sgx", mod.name.c_str());
        std::filesystem::path file_path = mods_dir / filename.c_str();
        
        // Open file for writing
        std::ofstream out_file(file_path, std::ios::binary);
        if (!out_file.is_open()) {
            logs::error("Failed to open file for writing: %s", file_path.string().c_str());
            mod.download_progress = 0;
            return;
        }
        
        // Initialize curl
        CURL* curl = curl_easy_init();
        if (!curl) {
            logs::error("curl_easy_init failed");
            out_file.close();
            mod.download_progress = 0;
            return;
        }
        
        // Setup download progress tracking
        mod_download_progress_data *download_progress = new mod_download_progress_data;
        download_progress->mod = &mod;
        download_progress->file = &out_file;
        
        // Configure curl
        curl_easy_setopt(curl, CURLOPT_URL, mod.url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, mods_download_write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, download_progress);
        curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, mods_download_progress_callback);
        curl_easy_setopt(curl, CURLOPT_XFERINFODATA, download_progress);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Akhenaten/1.0");
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 15L);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 300L); // 5 minutes for large files
        
        // Perform download
        CURLcode res = curl_easy_perform(curl);
        
        long httpCode = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
        
        out_file.close();
        
        if (res != CURLE_OK || httpCode != 200) {
            logs::error("Failed to download mod %s: %s (HTTP %ld)", name.c_str(), 
                       curl_easy_strerror(res), httpCode);
            std::filesystem::remove(file_path); // Remove partial file
            mod.download_progress = 0;
            curl_easy_cleanup(curl);
            return;
        }
        
        curl_easy_cleanup(curl);
        
        // Verify file was written
        if (!std::filesystem::exists(file_path) || std::filesystem::file_size(file_path) == 0) {
            logs::error("Downloaded file is empty or missing: %s", file_path.string().c_str());
            mod.download_progress = 0;
            return;
        }
        
        // Update mod info
        mod.downloaded = true;
        mod.download_progress = 100;
        mod.path.printf("Mods/%s", filename.c_str());
        
        // Initialize mod metadata (similar to mods_init)
        mod.useridx = imagepak::get_max_useridx() + 1;
        mod.start_index = imagepak::get_maxseen_imgid() + 1;
        
        vfs::path full_path = mod.path.resolve();
        if (!full_path.empty()) {
            mod.entries_num = imagepak::get_entries_num(mod.path.c_str());
            imagepak::useridx_update(mod.useridx);
            imagepak::update_max_imgid(mod.start_index + mod.entries_num);           
        }
        
        logs::info("Successfully downloaded mod: %s", name.c_str());
        
        // Note: UI update will happen automatically when the window is refreshed
        // The download_progress field is already updated during download
    });
#else
    logs::error("Mod download not supported on this platform");
    mod.download_progress = 0;
#endif
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
    for (auto &it : g_mods_list) {
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

            it.second.fill_entries();

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
                mod.downloaded = true;
                mod.useridx = imagepak::get_max_useridx() + 1;
                mod.start_index = imagepak::get_maxseen_imgid() + 1;
                mod.entries_num = imagepak::get_entries_num(mod.path.c_str());

                imagepak::useridx_update(mod.useridx);
                imagepak::update_max_imgid(mod.start_index + mod.entries_num);

                vfs::path full_path = mod.path.resolve();
                if (full_path.empty()) {
                    continue;
                }

                mod.fill_entries();
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

vfs::path mods_exist_audio(pcstr wav_path) {
    if (!wav_path || !*wav_path) {
        return {};
    }

    vfs::path name_lower(wav_path);
    name_lower.tolower();
    for (const auto &it : g_mods_list) {
        if (!it.second.enabled) {
            continue;
        }

        if (!it.second.audio_exist(name_lower.c_str())) {
            continue;
        }

        return vfs::path(it.second.path.c_str(), "/", name_lower);
    }

    return {};
}

mod_reader mods_find_audio(pcstr wav_path) {
    if (!wav_path || !*wav_path) {
        return {};
    }

    for (const auto &it : g_mods_list) {
        if (!it.second.enabled) {
            continue;
        }

        if (!it.second.audio_exist(wav_path)) {
            continue;
        }

        vfs::path mod_audio_path(it.second.path.c_str(), "/", wav_path);
        vfs::reader reader = vfs::file_open(mod_audio_path, "r");
        if (reader) {
            return { mod_audio_path.c_str(), reader };
        }
    }

    return {};
}

mod_reader mods_find_script(pcstr script_path, bool find_in_enabled) {
    if (!script_path || !*script_path) {
        return {};
    }

    for (const auto &it : g_mods_list) {
        if (!it.second.enabled) {
            continue;
        }

        if (!it.second.script_exist(script_path)) {
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

void mods_refresh_from_remote_repo (pcstr remote_repo) {
#ifdef GAME_PLATFORM_WIN
    CURLcode res;
    std::string readBuffer;

    CURL *curl = curl_easy_init();
    if (!curl) {
        logs::error("curl_easy_init failed");
        popup_dialog::show_ok("Error", "Failed to initialize HTTP client.");
        return;
    }

    curl_easy_setopt(curl, CURLOPT_URL, remote_repo);
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

        struct pos_name {
            size_t position;
            std::string name;
        };
        struct pos_url {
            size_t position;
            std::string url;
        };
        std::vector<pos_name> namePositions; // position, name
        std::vector<pos_url> urlPositions;  // position, url

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
                if (urlPair.position > namePair.position) {
                    modMap[namePair.name] = urlPair.url;
                    break;
                }
            }
        }
    }

    if (modMap.empty()) {
        popup_dialog::show_ok("Mods List", "No mods found on GitHub.");
        return;
    }

    logs::info("Available mods on repo: %s", remote_repo);
    for (const auto &pair : modMap) {
        logs::info("* %s|%s", pair.first.c_str(), pair.second.c_str());
        bstring128 mod_name = pair.first.c_str();
        mod_name.replace_str(".sgx", "");
        mods_add_remote_file(mod_name.c_str(), pair.second.c_str());
    }
    logs::info("Total: %d mod(s)", modMap.size());

    xstring result; result.printf("Found %zu mods on %s", modMap.size(), remote_repo);
    popup_dialog::show_ok("Mods", result);
#endif
}

void mods_refresh_from_config() {
    for (const auto &cmod : g_mods_config.mods_list) {
        auto &mod_info = mods_add_remote_file(cmod.name, cmod.url);
        mod_info.desc = cmod.desc;
        mod_info.version = cmod.version;
        mod_info.author = cmod.author;
        mod_info.email = cmod.email;
    }
}

void mods_refresh_available_list() {
#ifdef GAME_PLATFORM_WIN
    if (!g_mods_config.mods_repo.empty()) {
        mods_refresh_from_remote_repo(g_mods_config.mods_repo.front().url.c_str());
    } else {
        popup_dialog::show_ok("Error", "Mods repository URL is not configured.");
    }

    mods_refresh_from_config();

    mods_remount();
#else
    popup_dialog::show_ok("Error", "Mods list download not supported on this platform.");
#endif
}

void mod_info::fill_entries() {
    vfs::ZipArchive archive(path.c_str());
    if (archive.isValid()) {
        const auto &entries = archive.entries();
        scripts.clear();
        sounds.clear();
        for (const auto &entry : entries) {
            if (vfs::file_has_extension(entry.c_str(), "js")) {
                scripts.push_back(entry.tolower());
            }

            if (vfs::file_has_extension(entry.c_str(), "wav")) {
                sounds.push_back(entry.tolower());
            }
        }
    }
}