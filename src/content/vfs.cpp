#include "vfs.h"

#include "core/string.h"
#include "core/log.h"
#include "platform/platform.h"
#include "content/content.h"

#include <filesystem>

namespace vfs{

FILE * file_open(const char *filename, const char *mode) {
    return platform_file_manager_open_file(filename, mode);
}

int file_close(FILE * stream) {
    return fclose(stream);
}

bool file_has_extension(const char *filename, const char *extension) {
    if (!extension || !*extension)
        return true;

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

void file_change_extension(char *filename, const char *new_extension) {
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

void file_append_extension(char *filename, const char *extension) {
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

void file_remove_extension(uint8_t * filename) {
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

bool file_exists(const char *filename) {
    path fspath = dir_get_file(filename);
    if (fspath.empty()) {
        return false;
    }

    return std::filesystem::exists(fspath.c_str());
}

bool file_remove(const char *filename) {
    return platform_file_manager_remove_file(filename);
}

void create_folders(const char* path) {
    std::error_code err;
    if (!std::filesystem::create_directories(path, err) && !std::filesystem::exists(path)) {
        logs::info(err.message().c_str());
    }
}

void remove_folder(path folder_path) {
    folder_path = dir_get_path(folder_path);
    std::filesystem::remove_all(folder_path.c_str());
}

} //
