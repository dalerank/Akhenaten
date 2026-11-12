#include "dir.h"

#include "content/vfs.h"
#include "core/string.h"
#include "game/game_config.h"
#include "content/content.h"
#include "platform/platform.h"

#include <stdlib.h>
#include <string.h>
#include <filesystem>
#include <SDL.h>
#include <algorithm>
#include <map>
#include <set>
#include <string>

namespace fs = std::filesystem;

#define BASE_MAX_FILES 100

struct dir_data_t {
    dir_listing listing;
    int max_files;
};

dir_data_t g_dir_data;

namespace vfs {

struct path_uri {
    vfs::path original;
    vfs::path lowered;
};

std::map<size_t, path_uri> path_cache;
std::set<size_t> path_missing;

vfs::path content_internal_path(pcstr path) {
    pcstr dir = platform_file_manager_get_base_path();
    vfs::path corrected_path(dir, "/", path);
    return corrected_path;
}

void content_cache_real_file_paths(pcstr f) {
    vfs::path folder = content_internal_path(f);
    if (!fs::exists(folder.c_str()) || !fs::is_directory(folder.c_str())) {
        return;
    }

    auto add_cached_path = [] (pcstr entry) {
        path_uri uri;
        uri.original = entry;
        uri.original.replace('\\', '/');
        uri.lowered = uri.original;
        uri.lowered.tolower();
        size_t lhash = uri.lowered.hash();

        path_cache.insert({lhash, uri});
    };

    add_cached_path(folder);

    for (const auto &entry : fs::directory_iterator(folder.c_str())) {
        if (!fs::is_regular_file(entry.path())) {
            continue;
        }

        add_cached_path(entry.path().string().c_str());
    }
}

void content_cache_paths() {
    pcstr folders[] = {
        "",
        "AUDIO",
        "AUDIO/Ambient",
        "AUDIO/Music",
        "AUDIO/Voice",
        "AUDIO/Wavs",
        "Data",
    };

    for (const auto &folder : folders) {
        content_cache_real_file_paths(folder);
    }
}

static void allocate_listing_files(int min, int max) {
    auto &data = g_dir_data;
    for (int i = min; i < max; i++) {
        data.listing.files[i] = (char *)malloc(MAX_FILE_NAME * sizeof(char));
        data.listing.files[i][0] = 0;
    }
}

static void clear_dir_listing() {
    auto &data = g_dir_data;
    data.listing.num_files = 0;
    if (data.max_files <= 0) {
        data.listing.files = (char **)malloc(BASE_MAX_FILES * sizeof(char *));
        allocate_listing_files(0, BASE_MAX_FILES);
        data.max_files = BASE_MAX_FILES;
    } else {
        for (int i = 0; i < data.max_files; i++) {
            data.listing.files[i][0] = 0;
        }
    }
}

static void expand_dir_listing() {
    auto &data = g_dir_data;
    int old_max_files = data.max_files;

    data.max_files = 2 * old_max_files;
    data.listing.files = (char **)realloc(data.listing.files, data.max_files * sizeof(char *));
    allocate_listing_files(old_max_files, data.max_files);
}

static int compare_lower(const void *va, const void *vb) {
    // arguments are pointers to char*
    return string_compare_case_insensitive(*(pcstr *)va, *(pcstr *)vb);
}

static int add_to_listing(pcstr filename) {
    auto &data = g_dir_data;

    if (data.listing.num_files >= data.max_files)
        expand_dir_listing();

    strncpy(data.listing.files[data.listing.num_files], filename, MAX_FILE_NAME);
    data.listing.files[data.listing.num_files][MAX_FILE_NAME - 1] = 0;
    ++data.listing.num_files;
    return LIST_CONTINUE;
}

const dir_listing *dir_find_files_with_extension(xstring dir, xstring extension) {
    auto &data = g_dir_data;

    clear_dir_listing();
    platform_file_manager_list_directory_contents(dir.c_str(), TYPE_FILE, extension.c_str(), add_to_listing);
    qsort(data.listing.files, data.listing.num_files, sizeof(char *), compare_lower);
    return &data.listing;
}

const dir_listing *dir_find_all_subdirectories(pcstr dir) {
    auto &data = g_dir_data;

    clear_dir_listing();
    platform_file_manager_list_directory_contents(dir, TYPE_DIR, 0, add_to_listing);
    qsort(data.listing.files, data.listing.num_files, sizeof(char *), compare_lower);
    return &data.listing;
}


std::vector<path> dir_find_all_subdirectories(vfs::path dir, bool) {
    auto *listing = dir_find_all_subdirectories(dir.c_str());
    std::vector<path> folders;
    for (int i = 0; i < listing->num_files; i++) {
         folders.push_back(listing->files[i]);
    }
    return folders;
}

void content_clear_path_cache() {
    path_cache.clear();
    path_missing.clear();
}

#if !defined(GAME_PLATFORM_WIN) && !defined(GAME_PLATFORM_ANDROID)
// Case-sensitive file systems: Pharaoh installs mix "Data"/"data", "SprMain.sg3"/"SPRMAIN.SG3", and the
// game asks for one fixed spelling. Correct every component under the base dir, not just the files of
// the folders content_cache_paths() pre-lists.
static bool correct_case_on_disk(pcstr relative, vfs::path& out) {
    std::error_code ec;
    fs::path cur(platform_file_manager_get_base_path());
    if (cur.empty()) {
        cur = ".";
    }

    std::string rel(relative);
    std::replace(rel.begin(), rel.end(), '\\', '/');
    size_t pos = 0;
    while (pos <= rel.size()) {
        const size_t slash = rel.find('/', pos);
        const std::string part = rel.substr(pos, slash == std::string::npos ? std::string::npos : slash - pos);
        pos = (slash == std::string::npos) ? rel.size() + 1 : slash + 1;
        if (part.empty() || part == ".") {
            continue;
        }

        fs::path exact = cur / part;
        if (fs::exists(exact, ec)) {
            cur = exact;
            continue;
        }

        bool found = false;
        for (const auto& entry : fs::directory_iterator(cur, ec)) {
            const std::string name = entry.path().filename().string();
            if (string_compare_case_insensitive(name.c_str(), part.c_str()) == 0) {
                cur = entry.path();
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }

    out = cur.string().c_str();
    return true;
}
#endif

vfs::path content_path(pcstr path) {
    vfs::path uri_path = content_internal_path(path);
    vfs::path orig_path = uri_path;
    vfs::path lower = uri_path.tolower();
    const size_t lhash = lower.hash();

    if (const auto it = path_cache.find(lhash); it != path_cache.end()) {
        if (strcmp(it->second.lowered.c_str(), uri_path.c_str()) == 0) {
            return it->second.original;
        }
    }

#if !defined(GAME_PLATFORM_WIN) && !defined(GAME_PLATFORM_ANDROID)
    std::error_code ec;
    if (fs::exists(orig_path.c_str(), ec) || path_missing.count(lhash)) {
        return orig_path;
    }

    vfs::path corrected;
    if (correct_case_on_disk(path, corrected)) {
        path_uri uri;
        uri.original = corrected;
        uri.lowered = lower;
        path_cache.insert({lhash, uri});
        return corrected;
    }
    // A file created later gets this spelling, which the exists() check above finds first.
    path_missing.insert(lhash);
#endif

    return orig_path;
}

vfs::path current_path(pcstr path) {
    vfs::path result;
    if (char* base = SDL_GetBasePath()) {
        result.concat(base, "/", path);
        SDL_free(base);
    }

    return result;
}

void dir_look_entries(pcstr path, xfunction<void(pcstr, bool)> fn) {
    namespace fs = std::filesystem;
    std::error_code ec;
    for (const auto& e : fs::directory_iterator(path, ec)) {
        fn(e.path().string().c_str(), !e.is_regular_file());
    }
}

bool is_directory(pcstr path) {
    std::error_code ec;
    return fs::is_directory(path, ec);
}

vfs::path vfs::path::resolve() {
#ifndef GAME_PLATFORM_ANDROID
    pcstr filepath = data();

    // Check if the path is absolute
    bool is_absolute_path = false;
    if (platform.is_windows()) {
        is_absolute_path = std::isalpha(*filepath) && (*(filepath + 1) == ':') && ((*(filepath + 2) == '/') || (*(filepath + 2) == '\\'));
    } else {
        is_absolute_path = (*filepath) == '/';
    }

    // For absolute paths, return as-is (normalized)
    if (is_absolute_path) {
        return filepath;
    }

    vfs::path from_content = content_path(filepath);
    if (std::filesystem::exists(from_content.c_str())) {
        return from_content;
    }

    vfs::path from_pwd = vfs::path("./", filepath);
    if (std::filesystem::exists(from_pwd.c_str())) {
        return std::filesystem::absolute(from_pwd.c_str()).string().c_str();
    }

#if defined(GAME_PLATFORM_BROWSER)
    // Engine data embedded at link time (--embed-file), outside the IDBFS game dir.
    vfs::path from_engine("/engine/", filepath);
    if (std::filesystem::exists(from_engine.c_str())) {
        return from_engine;
    }
#endif

    // Not found anywhere (new file) — return game-dir path so writes go to the right place.
    return from_content;
#else
    pcstr filepath = data();
    vfs::path corrected_filename = content_path(filepath);
    // Native absolute paths still pass through directly on Android.
    if (!corrected_filename.empty() && corrected_filename.data()[0] == '/') {
        return corrected_filename;
    }
    // SAF-backed paths stay relative and are resolved by the Java bridge.
    return filepath;
#endif
}

const dir_listing *dir_append_files_with_extension(xstring dir, xstring extension) {
    auto &data = g_dir_data;

    platform_file_manager_list_directory_contents(dir.c_str(), TYPE_FILE, extension.c_str(), add_to_listing);
    qsort(data.listing.files, data.listing.num_files, sizeof(char *), compare_lower);
    return &data.listing;
}

} // vfs
