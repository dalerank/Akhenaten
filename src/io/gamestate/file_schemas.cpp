#include "file_schemas.h"

#include <cassert>

void file_schema(e_file_format file_format, const int file_version) {
    switch (file_format) {
    case FILE_FORMAT_MAP_FILE:
        file_schema_map(file_version);
        break;
    case FILE_FORMAT_SAVE_FILE:
        file_schema_sav(file_version);
        break;
    case FILE_FORMAT_SAVE_FILE_EXT:
        file_schema_svx(file_version);
        break;
    default:
        assert(false);
        break;
    }
}
