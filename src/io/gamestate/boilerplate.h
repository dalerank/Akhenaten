#ifndef GAME_FILE_H
#define GAME_FILE_H

#include <string.h>

void fullpath_saves(char* full, const char* filename);
void fullpath_maps(char* full, const char* filename);

namespace GamestateIO {
const int get_campaign_scenario_offset(int scenario_id);
const int read_file_version(const char* filename, int offset);

bool write_mission(const int scenario_id);
bool write_savegame(const char* filename_short);
bool prepare_folders(const char* path);
bool prepare_savegame(const char* filename_short);
bool write_map(const char* filename_short);

bool load_mission(const int scenario_id, bool start_immediately = true);
bool load_savegame(const char* filename_short, bool start_immediately = true);
bool load_map(const char* filename_short, bool start_immediately = true);

void start_loaded_file();

bool delete_mission(const int scenario_id);
bool delete_savegame(const char* filename_short);
bool delete_map(const char* filename_short);

/**
 * Delete campaign (aka family) created by user.
 * @param family_name to be removed
 * @return true on success
 */
bool delete_family(char const* family_name);
} // namespace GamestateIO
#endif // GAME_FILE_H
