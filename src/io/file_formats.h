#ifndef OZYMANDIAS_FILE_FORMATS_H
#define OZYMANDIAS_FILE_FORMATS_H

typedef enum {
    FILE_FORMAT_NULL,
    //
    FILE_FORMAT_BMP,
    FILE_FORMAT_PNG,
    FILE_FORMAT_JPG,
    //
    FILE_FORMAT_SG2,
    FILE_FORMAT_SG3,
    FILE_FORMAT_555,
    //
//    FILE_SCHEMA_SAV_147,
//    FILE_SCHEMA_SAV_160,
//    FILE_SCHEMA_SAV_149,
    FILE_FORMAT_PAK,
    FILE_FORMAT_SAV,
    FILE_FORMAT_MAP
} file_format_t;

file_format_t fet_format_from_file(const char *filename);

#endif //OZYMANDIAS_FILE_FORMATS_H
