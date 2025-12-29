#include "file_formats.h"

#include "content/vfs.h"
#include "core/bstring.h"

struct format_alias {
    e_file_format format;
    bstring32 ext;
} file_formats[] = { 
    {FILE_FORMAT_BMP, "bmp"},
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
    {FILE_FORMAT_JS, "js"},
    {FILE_FORMAT_MP3, "mp3"},
    {FILE_FORMAT_WAV, "wav"}
};

e_file_format get_format_from_file(const char* filename) {
    auto it = std::find_if(std::begin(file_formats), std::end(file_formats),
                           [filename] (auto &p) { return vfs::file_has_extension(filename, p.ext);  });

    return (it == std::end(file_formats) ? FILE_FORMAT_NULL : it->format);
}