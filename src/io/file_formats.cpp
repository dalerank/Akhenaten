#include "file_formats.h"
#include "file.h"

file_format_t get_format_from_file(const char *filename) {
    if (file_has_extension(filename, "bmp")) return FILE_FORMAT_BMP;
    if (file_has_extension(filename, "png")) return FILE_FORMAT_PNG;
    if (file_has_extension(filename, "jpg") || file_has_extension(filename, "jpeg")) return FILE_FORMAT_JPG;

    if (file_has_extension(filename, "sg2") || file_has_extension(filename, "sg3")) return FILE_FORMAT_SGX;
    if (file_has_extension(filename, "555")) return FILE_FORMAT_555;

    if (file_has_extension(filename, "pak")) return FILE_FORMAT_MISSION_PAK;
    if (file_has_extension(filename, "sav")) return FILE_FORMAT_SAVE_FILE;
    if (file_has_extension(filename, "map")) return FILE_FORMAT_MAP_FILE;

    if (file_has_extension(filename, "jas")) return FILE_FORMAT_JAS_RECORDS;
    if (file_has_extension(filename, "dat")) return FILE_FORMAT_PLAYER_DATA;

    return FILE_FORMAT_NULL;
}