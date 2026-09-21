#include "vfs.h"

#include "core/string.h"
#include "core/log.h"
#include "platform/platform.h"
#include "zipreader.hpp"
#include "reader.h"

#include <filesystem>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <string>

#if defined(GAME_PLATFORM_ANDROID)
#include "platform/android/android.h"
#endif

#if defined( __EMSCRIPTEN__ )
#include <emscripten.h>
EM_ASYNC_JS(void, __sync_em_fs, (), {
    // clang-format off
    // The following code is not C++ code, but JavaScript code.
    await new Promise((resolve, reject) => FS.syncfs(err => {
        if (err) reject(err);
        resolve();
    }));
    // (normally you would do something with the fetch here)
});
#endif

namespace vfs{

bool g_verbose_log = false;

FILE * file_open_os(path filename, pcstr mode) {
    return platform_file_manager_open_file(filename.c_str(), mode);
}

std::vector<ZipArchive*> g_mounted_archives;

#if defined(GAME_PLATFORM_ANDROID)
namespace {
    reader read_file_stream(path path, FILE *f, bool null_terminate) {
        std::string buffer;
        char chunk[8192];

        while (true) {
            const size_t read = fread(chunk, 1, sizeof(chunk), f);
            if (read > 0) {
                buffer.append(chunk, read);
            }

            if (read < sizeof(chunk)) {
                break;
            }
        }

        const bool failed = ferror(f) != 0;
        fclose(f);
        if (failed) {
            return reader();
        }

        const size_t extra = null_terminate ? 1 : 0;
        void *mem = malloc(buffer.size() + extra);
        if (!mem && (buffer.size() + extra) > 0) {
            return reader();
        }

        if (!buffer.empty()) {
            memcpy(mem, buffer.data(), buffer.size());
        }
        if (null_terminate) {
            ((char *)mem)[buffer.size()] = 0;
        }

        return std::make_shared<data_reader>(path.c_str(), mem, static_cast<int>(buffer.size()));
    }
}
#endif

template<typename ... Args>
void log_io(pcstr fmt, Args ... args) {
    if (!g_verbose_log) {
       return;
    }
    logs::info(fmt, args...);
}

bool file_exists(const path &filename) {
    path fspath = filename;
    fspath = fspath.resolve();
    if (fspath.empty()) {
        return false;
    }

#if defined(GAME_PLATFORM_ANDROID)
    if (std::filesystem::exists(fspath.c_str())) {
        return true;
    }

    FILE *fp = file_open_os(fspath, "rb");
    if (!fp) {
        return false;
    }

    fclose(fp);
    return true;
#else
    return std::filesystem::exists(fspath.c_str());
#endif
}

vfs::path extract_pack_path(const vfs::path &path) {
    vfs::path result = path;

    pcstr zip_pos = result.strstr(".zip/");
    pcstr sgx_pos = result.strstr(".sgx/");

    if (!zip_pos && !sgx_pos) {
        return {}; // No .zip/.sgx found
    }

    pcstr pack_pos = zip_pos ? zip_pos : sgx_pos;
    // Go backwards from .zip to find the start of the zip file name
    *((pstr)pack_pos + 4) = 0;
    return result;
}

vfs::path extract_pack_name(const vfs::path &path) {
    vfs::path result = extract_pack_path(path);

    pcstr begin_packname = strstr_rev(result, "/");
    if (begin_packname) {
        result = begin_packname + 1; // in case of Windows backslash
        return result;
    }

    return {};
}

reader file_open(path path, pcstr mode) {
    log_io("[begn] file_open %s", path.c_str());
    const bool is_text_file = !!strstr(mode, "t");
    const char* is_zip = strstr(path, ".zip/");
    const char *is_sgx = strstr(path, ".sgx/");

    if (!path.empty() && (!!is_zip || !!is_sgx)) {
        const vfs::path pack_name = extract_pack_name(path);
        const auto it = std::find_if(g_mounted_archives.begin(), g_mounted_archives.end(), [&pack_name] (const ZipArchive *arch) {
            return arch->filepath().ends_with(pack_name);
        });

        if (it == g_mounted_archives.end()) {
            return reader();
        }

        auto archive = *it;
        pcstr path_pos = (is_zip ? is_zip : is_sgx);
        const vfs::path filename = (path_pos + 5);
        reader data = archive->createAndOpenFile(filename, mode);

        return data; // empty reader
    }

    if (!path.empty() && path.data()[0] == ':') {
        auto data = internal_file_open(path.c_str());
        if (data.first) {
            log_io("[intr] loaded from %s", path.c_str());
            const int addb = is_text_file ? 1 : 0;
            void *mem = malloc(data.second + is_text_file);
            memcpy(mem, data.first, data.second);
            if (is_text_file) {
                ((char *)mem)[data.second] = 0; // null-terminate the string
            }
            return std::make_shared<data_reader>(path.c_str(), mem, data.second);
        }

        return reader();
    }

    if (is_text_file) { // text mode
#if defined(GAME_PLATFORM_ANDROID)
        FILE *f = file_open_os(path, mode);
        if (f) {
            log_io("[text] loaded from %s", path.c_str());
            return read_file_stream(path, f, true);
        }

        return reader();
#else
        std::ifstream file(path.c_str());
        if (file.is_open()) {
            log_io("[text] loaded from %s", path.c_str());
            std::ostringstream buffer;
            buffer << file.rdbuf();      // read entire file into stream
            std::string str = buffer.str(); // str holds the content of the file
            void *mem = malloc(str.size() + 1);
            memcpy(mem, str.c_str(), str.size());
            ((char *)mem)[str.size()] = 0; // null-terminate the string
            return std::make_shared<data_reader>(path.c_str(), mem, static_cast<int>(str.size()) );
        }

        return reader();
#endif
    }

    FILE *f = file_open_os(path, mode);
    if (f) {
        log_io("[binr] file_open %s", path.c_str());
#if defined(GAME_PLATFORM_ANDROID)
        return read_file_stream(path, f, false);
#else
        fseek(f, 0, SEEK_END);
        uint32_t size = ftell(f);
        fseek(f, 0, SEEK_SET);
        void *mem = malloc(size);
        fread(mem, 1, size, f);
        fclose(f);
        return std::make_shared<data_reader>(path.c_str(), mem, size);
#endif
    }

    return reader();
}

int file_close_os(FILE * stream) {
    return fclose(stream);
}

bool file_remove(path filename) {
    if (filename.empty()) {
        return false;
    }
    bool res = platform_file_manager_remove_file(filename.c_str());
    sync_em_fs();
    return res;
}

bool file_rename_os(path from, path to) {
    if (from.empty() || to.empty()) {
        return false;
    }

#if defined(GAME_PLATFORM_ANDROID)
    // POSIX rename() replaces an existing destination atomically
    const bool res = (::rename(from.c_str(), to.c_str()) == 0);
    if (!res) {
        logs::error("unable to rename %s -> %s", from.c_str(), to.c_str());
    }
#else
    std::error_code err;
    std::filesystem::rename(from.c_str(), to.c_str(), err);
    const bool res = !err;
    if (!res) {
        logs::error("unable to rename %s -> %s: %s", from.c_str(), to.c_str(), err.message().c_str());
    }
#endif

    sync_em_fs();
    return res;
}

void umount_pack(path filename) {
    if (filename.empty()) {
        return;
    }

    const auto it = std::find_if(g_mounted_archives.begin(), g_mounted_archives.end(), [&filename] (const ZipArchive *arch) {
        return arch->filepath() == filename;
    });

    if (it == g_mounted_archives.end()) {
        return;
    }

    auto *pack_to_umount = *it;
    g_mounted_archives.erase(it);

    delete pack_to_umount;
}

bool mounted_entry_resolve(path in_path, path &out_path) {
    if (in_path.empty()) {
        return false;
    }

    path want = in_path.split(".zip/");
    if (want.empty()) {
        want = in_path.split(".sgx/");
    }
    if (want.empty()) {
        return false;
    }

    const path pack_name = extract_pack_name(in_path);
    if (pack_name.empty()) {
        return false;
    }

    const auto it = std::find_if(g_mounted_archives.begin(), g_mounted_archives.end(), [&pack_name] (const ZipArchive *arch) {
        return arch->filepath().ends_with(pack_name);
    });
    if (it == g_mounted_archives.end()) {
        return false;
    }

    const auto &entries = (*it)->entries();
    for (const auto &entry : entries) {
        if (entry.empty()) {
            continue;
        }
        if (string_compare_case_insensitive(entry.c_str(), want.c_str()) != 0) {
            continue;
        }

        // Rebuild URI with the pack path used at mount time + archive entry casing.
        out_path = path((*it)->filepath().c_str(), "/", entry.c_str());
        return true;
    }

    return false;
}

bool mounted_entry_exists(path in_path) {
    path resolved;
    return mounted_entry_resolve(in_path, resolved);
}

bool is_pack_mounted(path filename) {
    if (filename.empty()) {
        return false;
    }

    const auto it = std::find_if(g_mounted_archives.begin(), g_mounted_archives.end(), [&filename] (const ZipArchive *arch) {
        return arch->filepath() == filename;
    });
    return it != g_mounted_archives.end();
}

bool mount_pack(path filename) {
    if (filename.empty() || !file_exists(filename)) {
        return false;
    }

    if (is_pack_mounted(filename)) {
        return true;
    }

    auto newzip = new ZipArchive(filename);
    if (!newzip->isValid()) {
        delete newzip;
        return false;
    }

    g_mounted_archives.push_back(newzip);

    return true;
}

void create_folders(path folder_path) {
#if defined(GAME_PLATFORM_ANDROID)
    if (!folder_path.empty()) {
        ::android_create_directories(folder_path.c_str());
    }
    return;
#else
    std::error_code err;
    if (!std::filesystem::create_directories(folder_path.c_str(), err) && !std::filesystem::exists(folder_path.c_str())) {
        logs::info(err.message().c_str());
    }
#endif
}

void sync_em_fs() {
#if defined( __EMSCRIPTEN__ )
    __sync_em_fs();
    logs::info("em fs synced");
    g_verbose_log = true;
#endif
}

void remove_folder(path folder_path) {
#if defined(GAME_PLATFORM_ANDROID)
    ::android_remove_directory(folder_path.c_str());
#else
    folder_path = content_path(folder_path);
    std::filesystem::remove_all(folder_path.c_str());
#endif
    sync_em_fs();
}

} // vfs
