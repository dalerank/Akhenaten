#pragma once

#include "building/building.h"
#include "building/monuments.h"
#include "core/svector.h"
#include "graphics/painter.h"
#include "grid/point.h"

#include "building/monument_pyramid_engine.h"

enum e_pyramid_ramp_need : int {
    PYRAMID_RAMP_NONE = 0,
    PYRAMID_RAMP_FIRST = 1,
    PYRAMID_RAMP_SECOND = 2,
};

int pyramid_ramp_og_subtype(int part_count, tile2i footprint_nw, tile2i part_tile);

int pyramid_engine_part_needs_ramp(building_id part_id);
bool pyramid_engine_has_ramp_work(building *main);
building_id pyramid_engine_find_ramp_part(building *main, figure_id claim_fid = 0);

void pyramid_engine_build_ramp(building_id part_id);
void pyramid_engine_update_part_ramp_image(building_id part_id);
void pyramid_engine_clear_part_ramps(building_id part_id);
void pyramid_engine_clear_all_ramps(building *main);
// Debug: apply full ramp schedule sprites and keep them through finish.
void pyramid_engine_set_force_show_ramps(building *main, bool enable);

// Serial: store ramp-links for this frame (call before parallel height ornaments).
void pyramid_ramp_prepare_frame_links();

// Draw cached ramp sprites for a part (OG ramp-link + own). Call from height ornaments.
void pyramid_ramp_draw_part(painter &ctx, building &part, vec2i part_anchor_px, color mask);
