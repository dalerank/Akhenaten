#include "core/io.h"

#include <stdio.h>

#include "core/file.h"

int io_read_file_into_buffer(const char *filepath, int localizable, buffer *buf, int max_size) {
    const char *cased_file = dir_get_file(filepath, localizable);
    if (!cased_file)
        return 0;

    FILE *fp = file_open(cased_file, "rb");
    if (!fp)
        return 0;

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    if (size > max_size)
        size = max_size;

    fseek(fp, 0, SEEK_SET);
    int bytes_read = buf->from_file((size_t) size, fp);
    file_close(fp);
    return bytes_read;
}
int io_read_file_part_into_buffer(const char *filepath, int localizable, buffer *buf, int size, int offset_in_file) {
    const char *cased_file = dir_get_file(filepath, localizable);
    if (!cased_file)
        return 0;

    int bytes_read = 0;
    FILE *fp = file_open(cased_file, "rb");
    if (fp) {
        int seek_result = fseek(fp, offset_in_file, SEEK_SET);
        if (seek_result == 0)
            bytes_read = buf->from_file((size_t) size, fp);
        file_close(fp);
    }
    return bytes_read;
}
int io_write_buffer_to_file(const char *filepath, buffer *buf, int size) {
    // Find existing file to overwrite
    const char *cased_file = dir_get_file(filepath, NOT_LOCALIZED);
    if (!cased_file)
        cased_file = filepath;

    FILE *fp = file_open(cased_file, "wb");
    if (!fp)
        return 0;

    int bytes_written = buf->to_file((size_t) size, fp);
    file_close(fp);
    return bytes_written;
}