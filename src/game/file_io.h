#ifndef GAME_FILE_IO_H
#define GAME_FILE_IO_H

enum {
    FILE_144 = 144,
    FILE_147 = 147,
    FILE_149 = 149,
    FILE_150 = 150,
    FILE_160 = 160,
};

enum {
    FILE_MAP = 24,
    FILE_PAK_MISSION = 175,
    FILE_SAVEGAME = 181
};

const int *get_file_version();
bool game_file_io_read_scenario(const char *filename);

bool game_file_io_write_scenario(const char *filename);

bool game_file_io_read_saved_game(const char *filename, int offset);

bool game_file_io_write_saved_game(const char *filename);

bool game_file_io_delete_saved_game(const char *filename);

#endif // GAME_FILE_IO_H
