#pragma once

#include "content/dir.h"
#include "content/reader.h"
#include "content/content.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @file
 * File-related functions.
 *
 * Methods related to extensions:
 * @li The extension starts from the first dot, double extensions are not supported
 * @li Extension parameters are expected to be 3 chars, without leading dot
 */

#define MAX_FILE_NAME 300

namespace vfs {

/**
 * Wrapper for fopen converting filename to path in current working directory
 * @param filename Path to open
 * @param mode Mode to open the file (e.g. "wb").
 * @return FILE
 */
FILE *file_open_os(path filename, pcstr mode);
reader file_open(path path, pcstr mode = "rb");


/**
 * Wrapper to fclose
 * @return See fclose (If the stream is successfully closed, a zero value is returned.
 *         On failure, EOF is returned.)
 */
int file_close_os(FILE *stream);

/**
 * Check if file exists
 * @param filename Path or relative path to check
 * @return boolean true if the file exists, false otherwise
 */
bool file_exists(const path &filename);

/**
 * Remove a file
 * @param filename Path to remove
 * @return boolean true if the file removal was successful, false otherwise
 */
bool file_remove(path filename);

/**
 * Rename a file, replacing the destination if it already exists.
 * Used to publish a fully written temporary file over its target in one step,
 * so an interrupted write cannot leave a truncated file behind.
 * @param from Existing file
 * @param to Destination, overwritten if present
 * @return boolean true if the rename was successful, false otherwise
 */
bool file_rename_os(path from, path to);

bool mount_pack(path filename);
void umount_pack(path filename);
bool is_pack_mounted(path filename);

bool mounted_entry_exists(path in_path);
bool mounted_entry_resolve(path in_path, path &out_path);

/**
* Create folders if not exists
* Throw exception if path not exists and can not be created
* @param folder_path to be created
*/
void create_folders(path folder_path);
void remove_folder(path folder_path);

void sync_em_fs();

} // vfs