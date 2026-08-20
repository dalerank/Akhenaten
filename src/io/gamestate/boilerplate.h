#pragma once

#include <cstdint>
#include "content/dir.h"
#include "io/gamestate/save_versions.h"

// Two numbers that are easy to confuse, so they get one accessor each:
//   save_data_version   - WHAT sits inside the chunks. Drives if (version > N) in binds.
//   svx_container_version - HOW chunks are laid out in the .svx file. Only the
//                           container reader/writer cares, and it never affects binds.
uint32_t save_data_version();
uint32_t svx_container_version();

vfs::path fullpath_saves(vfs::path filename);
vfs::path fullpath_maps(vfs::path filename);

namespace GamestateIO {

bool write_savegame(pcstr filename_short);
/** Write current map grids as FILE_FORMAT_MAP_FILE. relative → under Maps/. */
bool write_map(pcstr path, bool relative = true);

bool load_mission(const int scenario_id, bool start_immediately);
bool load_savegame(pcstr filename_short, bool start_immediately = true);
bool load_map(pcstr filename, bool relative, bool start_immediately);

void start_loaded_file();

bool delete_savegame(vfs::path filename_short);
bool delete_map(const char* filename_short);

// Dynasty folder marker (family.sav stub). Not a city save — no Ironwill gate.
bool write_family_marker(pcstr filename_short = "family.sav");

} // namespace GamestateIO
