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
 * @param filename Filename
 * @param mode Mode to open the file (e.g. "wb").
 * @return FILE
 */
FILE *file_open_os(pcstr filename, pcstr mode);
reader file_open(path path, pcstr mode = "rb");


/**
 * Wrapper to fclose
 * @return See fclose (If the stream is successfully closed, a zero value is returned.
 *         On failure, EOF is returned.)
 */
int file_close(FILE *stream);

/**
 * Checks whether the file has the given extension
 * @param filename Filename to check
 * @param extension Extension
 * @return boolean true if the file has the given extension, false otherwise
 */
bool file_has_extension(pcstr filename, pcstr extension);

/**
 * Replaces the current extension by the given new extension.
 * Filename is unchanged if there was no extension.
 * @param[in,out] filename Filename to change
 * @param new_extension New extension
 */
void file_change_extension(char *filename, pcstr new_extension);

/**
 * Appends the extension to the file
 * @param[in,out] filename Filename to change
 * @param extension Extension to append
 */
void file_append_extension(char *filename, pcstr extension);

/**
 * Removes the extension from the file
 * @param[in,out] filename Filename to change
 */
void file_remove_extension(char *filename);

/**
 * Check if file exists
 * @param filename Filename to check
 * @param localizable Whether the file may be localized (see core/dir.h)
 * @return boolean true if the file exists, false otherwise
 */
bool file_exists(pcstr filename);

/**
 * Remove a file
 * @param filename Filename to remove
 * @return boolean true if the file removal was successful, false otherwise
 */
bool file_remove(pcstr filename);

bool mount_pack(pcstr filename);
void umount_pack(pcstr filename);

/**
* Create folders if not exists
* Throw exception if path not exists and can not be created
* @param path to be created
*/
void create_folders(pcstr path);
void remove_folder(path folder_path);

void sync_em_fs();

} // vfs