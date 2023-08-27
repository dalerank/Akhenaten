#ifndef GAME_FILE_H
#define GAME_FILE_H

#include <cstdint>
#include <string.h>

// file versions found so far:
//  144 (Bridges.map only)
//  146 (NAFTA.map and Warfare.map only)
//  147 (most of the older campaign scenarios)
//  149 (later campaign scenarios and maps)
//  150 (later campaign scenarios and maps)
//  160 (post-Cleopatra campaign scenarios, patched Bubastis scenario)
//  161 ozymandias: save foods in houses
//  162 ozymandias: save g_terrain_floodplain_growth
//  163 ozymandias: save bazaar_days in house
//  164 ozymandias: save water_supply in house
//  165 ozymandias: save house health option
constexpr uint32_t latest_save_version = 165;

void fullpath_saves(char* full, const char* filename);
void fullpath_maps(char* full, const char* filename);

namespace GamestateIO {
const int get_campaign_scenario_offset(int scenario_id);
const int read_file_version(const char* filename, int offset);

bool write_mission(const int scenario_id);
bool write_savegame(const char* filename_short);

/**
 * Create folders if not exists
 * Throw exception if path not exists and can not be created
 * @param path to be created
 */
void prepare_folders(const char* path);
bool prepare_savegame(const char* filename_short);
bool write_map(const char* filename_short);

bool load_mission(const int scenario_id, bool start_immediately);
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
