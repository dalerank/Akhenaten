#include "file_formats.h"

#include "content/vfs.h"
#include "core/bstring.h"

e_file_format get_format_from_file(const char* filename) {
    struct format_alias {
        e_file_format format;
        bstring32 ext;
    } formats[] = {{FILE_FORMAT_BMP, "bmp"},
                   {FILE_FORMAT_PNG, "png"},
                   {FILE_FORMAT_JPG, "jpg"},
                   {FILE_FORMAT_JPG, "jpeg"},
                   {FILE_FORMAT_SGX, "sg2"},
                   {FILE_FORMAT_SGX, "sg3"},
                   {FILE_FORMAT_555, "555"},
                   {FILE_FORMAT_MISSION_PAK, "pak"},
                   {FILE_FORMAT_SAVE_FILE, "sav"},
                   {FILE_FORMAT_MAP_FILE, "map"},
                   {FILE_FORMAT_JAS_RECORDS, "jas"},
                   {FILE_FORMAT_PLAYER_DATA, "dat"},
                   {FILE_FORMAT_SAVE_FILE_EXT, "svx"},
            };

    auto it = std::find_if(std::begin(formats), std::end(formats), [filename] (auto &p) { return vfs::file_has_extension(filename, p.ext);  });

    return (it == std::end(formats) ? FILE_FORMAT_NULL : it->format);
}