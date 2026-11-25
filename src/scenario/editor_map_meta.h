#pragma once

#include "core/vfs/vfs.h"
#include "scenario/editor.h"

vfs::path editor_map_meta_path(pcstr map_path);

bool editor_map_meta_write(pcstr map_path);
bool editor_map_meta_load(pcstr map_path);

void editor_map_meta_remove(pcstr map_path);
void editor_invasions_clear();
void editor_price_changes_clear();
void editor_demand_changes_clear();

// Preserve / wipe / restore editor request slots around terrain-only map write.
void editor_requests_preserve_begin();
void editor_requests_preserve_end();
