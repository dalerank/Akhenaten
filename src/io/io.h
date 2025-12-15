#pragma once

#include "core/buffer.h"
#include "content/dir.h"

/**
 * @file
 * I/O functions.
 */
int io_read_sg3_entries_num(vfs::path filepath);

int io_read_sgx_entries_num(vfs::path filename);

/**
 * Reads the entire file into the buffer
 * @param filepath File to read
 * @param localizable Whether the file may be localized (see core/dir.h)
 * @param buffer Buffer to read into
 * @param max_size Max size to read
 * @return Number of bytes read
 */
int io_read_file_into_buffer(vfs::path filepath, int localizable, buffer* buf, int max_size);

/**
 * Reads part of the file into the buffer
 * @param filepath File to read
 * @param localizable Whether the file may be localized (see core/dir.h)
 * @param buffer Buffer to read into
 * @param size Number of bytes to read
 * @param offset_in_file Offset into the file to start reading
 */
int io_read_file_part_into_buffer(vfs::path filepath, int localizable, buffer* buf, int size, int offset_in_file);

/**
 * Writes the entire buffer to the file
 * @param filepath File to write
 * @param buffer Buffer to write
 * @param size Number of bytes to write
 * @return Number of bytes written
 */
int io_write_buffer_to_file(vfs::path filepath, buffer* buf, int size);
