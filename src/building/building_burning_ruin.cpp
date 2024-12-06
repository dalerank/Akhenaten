#include "building_burning_ruin.h"

#include "game/undo.h"
#include "city/city.h"
#include "core/random.h"
#include "grid/building_tiles.h"
#include "grid/terrain.h"
#include "building/maintenance.h"
#include "building/destruction.h"
#include "grid/building.h"
#include "grid/grid.h"
#include "scenario/scenario.h"
#include "grid/road_access.h"

building_burning_ruin::static_params burning_ruin_m;

void building_burning_ruin::static_params::load(archive arch) {
    fire_animations = arch.r_int("fire_animations", 1);
}

tile2i building_burning_ruin::can_be_accessed() {
    int base_offset = tile().grid_offset();
    offsets_array offsets;
    map_grid_adjacent_offsets(1, offsets);
    for (const auto &tile_delta: offsets) {
        int grid_offset = base_offset + tile_delta;

        if (road_tile_valid_access(grid_offset)
            || (building_at(grid_offset)->type == BUILDING_BURNING_RUIN
            && building_at(grid_offset)->fire_duration <= 0)) {
            return tile2i(grid_offset);
        }
    }

    return tile2i::invalid;
}

// NOTE! burning_ruin cant call on_place(), so all preparing actions should
// be executed in on_create()
void building_burning_ruin::on_create(int orientation) {
    building_impl::on_create(orientation);
    base.fire_duration = (rand() % 128) + 120;
    base.state = BUILDING_STATE_VALID;

    uint8_t random = rand() % current_params().fire_animations;
    bstring32 anim_name; anim_name.printf("fire%d", random);
    set_animation(xstring(anim_name));

    bstring32 base_name; base_name.printf("base%d", random);
    int img_id = anim(xstring(base_name)).first_img();
    map_building_tiles_add(id(), tile(), base.size, img_id, TERRAIN_BUILDING);
}

void building_burning_ruin::on_tick(bool refresh_only) {
    building_impl::on_tick(refresh_only);

    if (base.state == BUILDING_STATE_RUBBLE) {
        return;
    }

    if (base.fire_duration <= 0) {
        base.state = BUILDING_STATE_RUBBLE;
        map_building_tiles_set_rubble(id(), tile(), size());
    }
}

bool building_burning_ruin::can_play_animation() const {
    return base.fire_duration > 0;
}

bool building_burning_ruin::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);
    return true;
}

bool building_burning_ruin::update() {
    if (base.state == BUILDING_STATE_RUBBLE) { 
        return true;
    }

    if (base.fire_duration < 0) {
        return true;
    }

    base.fire_duration -= rand() % 16;
    if (base.fire_duration <= 0) {
        game_undo_disable();
        base.state = BUILDING_STATE_RUBBLE;
        map_building_tiles_set_rubble(id(), tile(), size());
        return true;
    }

    if (base.has_plague) {
        return false;
    }

    int climate = scenario_property_climate();
    if (climate == CLIMATE_DESERT) {
        if (base.fire_duration & 3) { // check spread every 4 ticks
            return false;
        }
    } else {
        if (base.fire_duration & 7) { // check spread every 8 ticks
            return false;
        }
    }

    if ((base.map_random_7bit & 3) != (random_byte() & 3)) {
        return false;
    }

    int fire_spread_direction = building_maintenance_fire_direction();
    int dir1 = ((fire_spread_direction - 1) + 8) % 8;
    int dir2 = (fire_spread_direction + 1) % 8;

    int directions[] = {fire_spread_direction, dir1, dir2};
    for (const auto &dir : directions) {
        int grid_offset = tile().grid_offset();
        int next_building_id = map_building_at(grid_offset + map_grid_direction_delta(dir));
        if (next_building_id && !building_get(next_building_id)->fire_proof) {
            building_destroy_by_fire(building_get(next_building_id));
            return true;
        }
    }

    return false;
}
