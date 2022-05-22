#ifndef GAME_FILE_H
#define GAME_FILE_H

#include <string.h>

//enum { // MINOR versioning found so far
//    FILE_144 = 144,
//    FILE_147 = 147,
//    FILE_149 = 149,
//    FILE_150 = 150,
//    FILE_160 = 160,
//};

//enum { // MAJOR versioning found so far
//    FILE_MAP = 24,
//    FILE_SAVESTATE = 175,
//    FILE_SAVESTATE_EXP = 181
//};

void fullpath_saves(char *full, const char *filename);
void fullpath_maps(char *full, const char *filename);

namespace GamestateIO {
//    const int get_file_version();
    const int get_campaign_scenario_offset(int scenario_id);
    const int read_file_version(const char *filename, int offset);

    bool write_mission(const int scenario_id);
    bool write_savegame(const char *filename_short);
    bool write_map(const char *filename_short);

    bool load_mission(const int scenario_id, bool start_immediately = true);
    bool load_savegame(const char *filename_short, bool start_immediately = true);
    bool load_map(const char *filename_short, bool start_immediately = true);

    void start_loaded_file();

    bool delete_mission(const int scenario_id);
    bool delete_savegame(const char *filename_short);
    bool delete_map(const char *filename_short);
}
#endif // GAME_FILE_H
