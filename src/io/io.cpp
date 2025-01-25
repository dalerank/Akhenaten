#include "io.h"

#include "content/vfs.h"
#include "platform/platform.h"

int io_read_file_into_buffer(const char* filepath, int localizable, buffer* buf, int max_size) {
    if (buf == nullptr) {
        return 0;
    }

    vfs::path fs_file = vfs::content_file(filepath);
    if (fs_file.empty()) {
        return 0;
    }

    FILE* fp = vfs::file_open(fs_file, "rb");
    if (!fp) {
        return 0;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    if (size > max_size) {
        size = max_size;
    }

    if (size > buf->size()) {
        return 0;
    }

    fseek(fp, 0, SEEK_SET);
    int bytes_read = buf->from_file((size_t)size, fp);
    vfs::file_close(fp);
    return bytes_read;
}

int io_read_file_part_into_buffer(const char* filepath, int localizable, buffer* buf, int size, int offset_in_file) {
    vfs::path fs_file = vfs::content_file(filepath);
    if (fs_file.empty()) {
        return 0;
    }

    int bytes_read = 0;
    FILE* fp = vfs::file_open(fs_file, "rb");
    if (fp) {
        int seek_result = fseek(fp, offset_in_file, SEEK_SET);
        if (seek_result == 0) {
            bytes_read = buf->from_file((size_t)size, fp);
        }
        vfs::file_close(fp);
    }
    return bytes_read;
}

int io_write_buffer_to_file(const char* filepath, buffer* buf, int size) {
    // Find existing file to overwrite
    vfs::path fs_file = vfs::content_file(filepath);
    if (fs_file.empty()) {
        fs_file = filepath;
    }

    FILE* fp = vfs::file_open(fs_file, "wb");
    if (!fp) {
        return 0;
    }

    int bytes_written = buf->to_file((size_t)size, fp);
    vfs::file_close(fp);
    vfs::sync_em_fs();
    return bytes_written;
}