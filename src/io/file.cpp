#include "file.h"

#include "core/string.h"
#include "platform/file_manager.h"

FILE* file_open(const char* filename, const char* mode) {
    return platform_file_manager_open_file(filename, mode);
}
int file_close(FILE* stream) {
    return fclose(stream);
}

bool file_has_extension(const char* filename, const char* extension) {
    if (!extension || !*extension)
        return true;

    char c;
    do {
        c = *filename;
        filename++;
    } while (c != '.' && c);
    if (!c)
        filename--;

    return string_compare_case_insensitive(filename, extension) == 0;
}
void file_change_extension(char* filename, const char* new_extension) {
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
void file_append_extension(char* filename, const char* extension) {
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
void file_remove_extension(uint8_t* filename) {
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

bool file_exists(const char* filename, int localizable) {
    const char* path = dir_get_file(filename, localizable);
    if (!path) {
        return false;
    }

    FILE* fp = file_open(path, "rb");
    if (fp) {
        file_close(fp);
        return true;
    }

    return false;
}
bool file_remove(const char* filename) {
    return platform_file_manager_remove_file(filename);
}
