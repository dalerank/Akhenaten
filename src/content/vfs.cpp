#include "vfs.h"

#include "core/string.h"
#include "core/log.h"
#include "platform/platform.h"
#include "zipreader.hpp"
#include "reader.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

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

FILE * file_open_os(pcstr filename, pcstr mode) {
    return platform_file_manager_open_file(filename, mode);
}

std::vector<ZipArchive*> g_mounted_archives;

template<typename ... Args>
void log_io(pcstr fmt, Args ... args) {
    if (!g_verbose_log) {
       return;
    }
    logs::info(fmt, args...);
}

namespace detail {
    bool file_exists(pcstr filename) {
        path fspath = path(filename).resolve();
        if (fspath.empty()) {
            return false;
        }

        return std::filesystem::exists(fspath.c_str());
    }
}

vfs::path extract_pack_path(const vfs::path &path) {
    vfs::path result;
    result = path;
    result.replace('\\', '/'); // Normalize slashes

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
        std::ifstream file(path.c_str());
        if (file.is_open()) {
            log_io("[text] loaded from %s", path.c_str());
            std::ostringstream buffer;
            buffer << file.rdbuf();      // read entire file into stream
            std::string str = buffer.str(); // str holds the content of the file
            void *mem = malloc(str.size() + 1);
            memcpy(mem, str.c_str(), str.size());
            ((char *)mem)[str.size()] = 0; // null-terminate the string
            return std::make_shared<data_reader>(path.c_str(), mem, str.size());
        }

        return reader();
    }

    FILE *f = file_open_os(path.c_str(), mode);
    if (f) {
        log_io("[binr] file_open %s", path.c_str());
        fseek(f, 0, SEEK_END);
        uint32_t size = ftell(f);
        fseek(f, 0, SEEK_SET);
        void *mem = malloc(size);
        fread(mem, 1, size, f);
        fclose(f);
        return std::make_shared<data_reader>(path.c_str(), mem, size);
    }

    return reader();
}

int file_close(FILE * stream) {
    return fclose(stream);
}

bool file_has_extension(pcstr filename, pcstr extension) {
    if (!filename || !*filename) {
        return false;
    }

    if (!extension || !*extension) {
        return true;
    }

    char c;
    do {
        c = *filename;
        filename++;
    } while (c != '.' && c);

    if (!c) {
        filename--;
    }

    return string_compare_case_insensitive(filename, extension) == 0;
}

void file_change_extension(char *filename, pcstr new_extension) {
    char c;
    do {
        c = *filename;
        filename++;
    } while (c != '.' && c);

    if (c == '.') {
        filename[0] = new_extension[0];
        filename[1] = new_extension[1];
        filename[2] = new_extension[2];
        filename[3] = 0;
    }
}

void file_append_extension(char *filename, pcstr extension) {
    char c;
    do {
        c = *filename;
        filename++;
    } while (c);
    filename--;
    filename[0] = '.';
    filename[1] = extension[0];
    filename[2] = extension[1];
    filename[3] = extension[2];
    filename[4] = 0;
}

void file_remove_extension(char * filename) {
    uint8_t c;
    do {
        c = *filename;
        filename++;
    } while (c != '.' && c);

    if (c == '.') {
        filename--;
        *filename = 0;
    }
}

bool file_remove(pcstr filename) {
    bool res = platform_file_manager_remove_file(filename);
    sync_em_fs();
    return res;
}

void umount_pack(pcstr filename) {
    const auto it = std::find_if(g_mounted_archives.begin(), g_mounted_archives.end(), [filename] (const ZipArchive *arch) {
        return arch->filepath() == filename;
    });

    if (it == g_mounted_archives.end()) {
        return;
    }

    auto *pack_to_umount = *it;
    g_mounted_archives.erase(it);

    delete pack_to_umount;
}

bool mount_pack(pcstr filename) {
    if (!file_exists(filename)) {
        return false;
    }

    const auto it = std::find_if(g_mounted_archives.begin(), g_mounted_archives.end(), [filename] (const ZipArchive *arch) {
        return arch->filepath() == filename;
    });
        
    if (it != g_mounted_archives.end()) {
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

void create_folders(pcstr path) {
    std::error_code err;
    if (!std::filesystem::create_directories(path, err) && !std::filesystem::exists(path)) {
        logs::info(err.message().c_str());
    }
}

void sync_em_fs() {
#if defined( __EMSCRIPTEN__ )
    __sync_em_fs();
    logs::info("em fs synced");
    g_verbose_log = true;
#endif
}

void remove_folder(path folder_path) {
    folder_path = content_path(folder_path);
    std::filesystem::remove_all(folder_path.c_str());
    sync_em_fs();
}

} // vfs
