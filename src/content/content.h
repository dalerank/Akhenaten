#pragma once

#include "core/xstring.h"

#include <utility>
#include <stdio.h>

namespace vfs {

enum {
    TYPE_NONE = 0,
    TYPE_DIR = 1,
    TYPE_FILE = 2,
    TYPE_ANY = 3
};

enum {
    LIST_ERROR = 0,
    LIST_NO_MATCH = 1,
    LIST_CONTINUE = 1,
    LIST_MATCH = 2
};

/**
 * Sets the base path for Akhenaten
 * @param path The path to be set as the base
 * @return true if the base path was correctly set, false otherwise
 */
int platform_file_manager_set_base_path(pcstr path);
pcstr platform_file_manager_get_base_path();

int platform_file_manager_set_ext_path(pcstr path);
pcstr platform_file_manager_get_ext_path();

/**
 * Gets the contents of a directory by the specified extension
 * @param dir The directory to search on, or null if base directory
 * @param type The file type to filter (dir, file or both)
 * @param extension The extension to filter
 * @param callback The function to call when a matched file is found
 * @return LIST_ERROR if error, LIST_MATCH if there was a match in the callback, LIST_NO_MATCH if no match was set
 */
int platform_file_manager_list_directory_contents(pcstr dir, int type, pcstr extension, int (*callback)(pcstr));

/**
 * Opens a file
 * @param filename The file to open
 * @param mode The mode to open the file - refer to fopen()
 * @return A pointer to a FILE structure on success, NULL otherwise
 */
FILE *platform_file_manager_open_file(pcstr filename, pcstr mode);

/**
 * Removes a file
 * @param filename The file to remove
 * @return true if removal was successful, false otherwise
 */
bool platform_file_manager_remove_file(const char *filename);

std::pair<void*, uint32_t> internal_file_open(pcstr path);
xstring platform_unpack_scripts();

} // vfs