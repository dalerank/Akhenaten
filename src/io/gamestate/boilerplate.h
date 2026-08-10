#pragma once

#include <cstdint>
#include "content/dir.h"

// file versions found so far:
//  144 (Bridges.map only)
//  146 (NAFTA.map and Warfare.map only)
//  147 (most of the older campaign scenarios)
//  149 (later campaign scenarios and maps)
//  150 (later campaign scenarios and maps)
//  160 (post-Cleopatra campaign scenarios, patched Bubastis scenario)
//  161 akhenaten: save foods in houses
//  162 akhenaten: save g_terrain_floodplain_growth
//  163 akhenaten: save bazaar_days in house
//  164 akhenaten: save water_supply in house
//  165 akhenaten: save house health option
//  167 akhenaten: save sandstone terrain values
//  168 akhenaten: save stone terrain values
//  169 akhenaten: save golden terrain values
//  170 akhenaten: save enemy armies props
//  171 akhenaten: bridge_part / bridge_type grids
//  172 akhenaten: B2 invasion event pending (deprecated stub)
//  173 akhenaten: invasion_runtime — bind resolve + history ring
//  174 akhenaten: house zookeeper coverage (Cleopatra Zoo)
//  175 akhenaten: storage Empty All order snapshot
//  176 akhenaten: wall_material_grid (mud/brick terrain walls)
//  177 akhenaten: invasion auto-resolve pending queue
//  178 akhenaten: (reserved / in-tree)
//  179 akhenaten: monument funeral_done (pyramid append; mastaba reclaims skip byte)
//  180 akhenaten: monument preexisting (pyramid append; mastaba/sphinx/obelisk reclaim skip)
//  181 akhenaten: house frog_infest_days (Cleopatra Plague of Frogs / CF1)
//  182 akhenaten: pyramid complex causeway_length / causeway_dir
//  183 akhenaten: campaign_carry_troops (Cleopatra fort carry CO2)
//  184 akhenaten: campaign_carry_monuments (Cleopatra monument carry CO1)
//  185 akhenaten: (reserved / in-tree)
//  186 akhenaten: labor STORAGE category priority (enhanced labor split LC4)
//  188 akhenaten: recorded cart trails (pool + last-4 building rings)
//  189 akhenaten: sectioned .svx container (chunk layout unchanged)
constexpr uint32_t latest_save_version = 189;

// Two numbers that are easy to confuse, so they get one accessor each:
//   save_data_version   - WHAT sits inside the chunks. Drives if (version > N) in binds.
//   svx_container_version - HOW chunks are laid out in the .svx file. Only the
//                           container reader/writer cares, and it never affects binds.
uint32_t save_data_version();
uint32_t svx_container_version();

vfs::path fullpath_saves(vfs::path filename);
vfs::path fullpath_maps(char* full, vfs::path filename);

namespace GamestateIO {
int get_campaign_scenario_offset(int scenario_id);
const int read_file_version(const char* filename, int offset);

bool write_mission(const int scenario_id);
bool write_savegame(pcstr filename_short);

bool write_map(pcstr filename_short);
/** Write current in-memory map grids as FILE_FORMAT_MAP_FILE to an absolute/relative path. */
bool write_map_path(pcstr path);
/** load_mission_pak_raw(scenario_id) then write_map_path(path). */
bool export_mission_map(const int scenario_id, pcstr path);

bool load_mission(const int scenario_id, bool start_immediately);

bool load_mission_pak_raw(const int scenario_id);
bool load_mission_map_raw(const int scenario_id, pcstr map_path);
bool load_savegame(pcstr filename_short, bool start_immediately = true);
bool load_map(pcstr filename, bool relative, bool start_immediately);

void start_loaded_file();

bool delete_mission(const int scenario_id);
bool delete_savegame(vfs::path filename_short);
bool delete_map(const char* filename_short);

} // namespace GamestateIO
