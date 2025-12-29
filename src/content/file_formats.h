#pragma once

enum e_file_format {
    FILE_FORMAT_NULL,
    //
    FILE_FORMAT_BMP,
    FILE_FORMAT_PNG,
    FILE_FORMAT_JPG,
    //
    FILE_FORMAT_SGX,
    FILE_FORMAT_555,
    //
    FILE_FORMAT_MISSION_PAK,
    FILE_FORMAT_SAVE_FILE,
    FILE_FORMAT_MAP_FILE,
    //
    FILE_FORMAT_JAS_RECORDS,
    FILE_FORMAT_PLAYER_DATA,
    //
    FILE_FORMAT_SAVE_FILE_EXT,
    //
    FILE_FORMAT_JS,
    FILE_FORMAT_MP3,
    FILE_FORMAT_WAV,
};

e_file_format get_format_from_file(const char* filename);
