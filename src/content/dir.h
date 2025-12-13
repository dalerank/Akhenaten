#pragma once

#include "core/xstring.h"

#include <vector>

/**
 * @file
 * Directory-related functions.
 */
enum {
    NOT_LOCALIZED = 0,
    MAY_BE_LOCALIZED = 1,
    MUST_BE_LOCALIZED = 2
};

/**
* Directory listing
*/
struct dir_listing {
    char **files;  /**< Filenames in UTF-8 encoding */
    int num_files; /**< Number of files in the list */
};

namespace vfs {

struct path : public bstring256 {
    template<typename ...Args>
    inline path(Args &&...args) : bstring256(std::forward<Args>(args)...) {
        bstring256 tmp = *this;
        clear();
        tmp.replace('\\', '/'); // Replace backslashes with slashes
        pcstr c = tmp.data();
        pstr mptr = data();
        if (c) {
            *mptr = *c;
            ++c;
        }

        for (; *c != 0; ++c) {
            if (*c == '/' && *mptr == '/') {
                continue;
            }

            ++mptr;
            *mptr = *c;
        }

        size_t size = mptr - _data;
        int remain = capacity - size;
        *(mptr + ((remain > 0) ? 1 : 0)) = 0;
        replace('\\', '/'); // Replace backslashes with slashes
    }

    path &operator=(pcstr str) {
        clear();
        append(str);
        replace('\\', '/'); // Replace backslashes with slashes
        return *this;
    }

    path &operator=(const std::string &str) {
        clear();
        append(str.c_str());
        replace('\\', '/'); // Replace backslashes with slashes
        return *this;
    }

    void remove_extension() {
        pstr ptr_point = ::strchr(_data, '.');
        if (ptr_point) {
            *ptr_point = 0;
        }
    }

    /**
     * Get the case sensitive and localized filename of the file
     * @param filepath File path to match to a case-sensitive file on the filesystem
     * @param localizable Whether the file may, must or must not be localized
     * @return Corrected file, or NULL if the file was not found
     */
    vfs::path resolve();
    static vfs::path resolve(pcstr p) {
        vfs::path r(p);
        return r.resolve();
    }
};

constexpr pcstr SAVE_FOLDER = "Save";
constexpr pcstr SCRIPTS_FOLDER = "Scripts";
constexpr pcstr content_audio = "AUDIO/";

/**
 * Finds files with the given extension
 * @param dir The directory to search on, or null if base directory
 * @param extension Extension of the files to find
 * @return Directory listing
 */
const dir_listing *dir_find_files_with_extension(pcstr dir, const xstring& extension);
const dir_listing *dir_append_files_with_extension(pcstr dir, pcstr extension);

/**
 * Finds all subdirectories
 * @return Directory listing
 */
const dir_listing *dir_find_all_subdirectories(pcstr dir);
std::vector<path> dir_find_all_subdirectories(vfs::path dir, bool);

vfs::path content_path(pcstr filepath, pcstr extdir = nullptr);

void content_cache_real_file_paths(pcstr folder);
void content_cache_paths();

} // vfs
