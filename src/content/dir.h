#pragma once

#include "core/core.h"
#include "core/xfunction.h"
#include "content/path.h"

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

constexpr pcstr SAVE_FOLDER = "Save";
constexpr pcstr SCRIPTS_FOLDER = "Scripts";
constexpr pcstr content_audio = "AUDIO/";

/**
 * Finds files with the given extension
 * @param dir The directory to search on, or null if base directory
 * @param extension Extension of the files to find
 * @return Directory listing
 */
const dir_listing *dir_find_files_with_extension(xstring dir, xstring extension);
const dir_listing *dir_append_files_with_extension(xstring dir, xstring extension);

/**
 * Finds all subdirectories
 * @return Directory listing
 */
const dir_listing *dir_find_all_subdirectories(pcstr dir);
std::vector<path> dir_find_all_subdirectories(vfs::path dir, bool);
void dir_look_entries(pcstr path, xfunction<void(pcstr, bool)> fn);

vfs::path content_path(pcstr filepath);
vfs::path current_path(pcstr filepath);

bool is_directory(pcstr path);

void content_cache_real_file_paths(pcstr folder);
void content_cache_paths();

} // vfs
