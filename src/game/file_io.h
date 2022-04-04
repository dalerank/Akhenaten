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
    FILE_SAVESTATE = 175,
    FILE_SAVESTATE_EXP = 181
};

typedef struct {
    int minor;
    int major;
} file_version_t;

bool load_file_version(const char *filename, int offset);
const file_version_t *get_file_version();
bool game_file_io_read_scenario(const char *filename);

bool game_file_io_write_scenario(const char *filename);

bool game_file_io_read_saved_game(const char *filename, int offset);

bool game_file_io_write_saved_game(const char *filename);

bool game_file_io_delete_saved_game(const char *filename);

#endif // GAME_FILE_IO_H
