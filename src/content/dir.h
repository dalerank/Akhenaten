#pragma once

#include "core/string.h"

#include <vector>

/**
 * @file
 * Directory-related functions.
 */

#define ASSETS_DIR_NAME "assets"
#define ASSETS_DIRECTORY "***" ASSETS_DIR_NAME "***"

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

using path = bstring256;

constexpr pcstr SAVE_FOLDER = "Save";
constexpr pcstr SCRIPTS_FOLDER = "Scripts";
constexpr pcstr content_audio = "AUDIO/";

/**
 * Finds files with the given extension
 * @param dir The directory to search on, or null if base directory
 * @param extension Extension of the files to find
 * @return Directory listing
 */
const dir_listing *dir_find_files_with_extension(const char *dir, const char *extension);
const dir_listing *dir_append_files_with_extension(const char *dir, const char *extension);

/**
 * Finds all subdirectories
 * @return Directory listing
 */
const dir_listing *dir_find_all_subdirectories(pcstr dir);
std::vector<path> dir_find_all_subdirectories(vfs::path dir, bool);

/**
 * Get the case sensitive and localized filename of the file
 * @param filepath File path to match to a case-sensitive file on the filesystem
 * @param localizable Whether the file may, must or must not be localized
 * @return Corrected file, or NULL if the file was not found
 */
vfs::path content_file(pcstr filepath);
vfs::path content_path(pcstr filepath);

void content_cache_real_file_paths(pcstr folder);
void content_cache_paths();

} // vfs
