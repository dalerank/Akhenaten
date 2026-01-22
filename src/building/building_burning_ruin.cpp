#include "building_burning_ruin.h"

#include "game/undo.h"
#include "city/city.h"
#include "core/random.h"
#include "core/profiler.h"
#include "grid/building_tiles.h"
#include "grid/terrain.h"
#include "building/destruction.h"
#include "grid/building.h"
#include "grid/grid.h"
#include "scenario/scenario.h"
#include "grid/road_access.h"
#include "grid/routing/routing_terrain.h"
#include "grid/routing/routing.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_burning_ruin);
svector<uint16_t, 2500> g_burning_ruins;

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

std::pair<int, tile2i> building_burning_ruin::get_closest_from(tile2i tile) {
    building *near_ruin = nullptr;
    int distance = 10000;

    std::vector<building *> burning_ruins;
    buildings_valid_do([&burning_ruins] (building &b) {
        if (!(b.state == BUILDING_STATE_VALID || b.state == BUILDING_STATE_MOTHBALLED || b.has_plague)) {
            return;
        }

        if (b.has_figure(3)) {
            return;
        }

        burning_ruins.push_back(&b);
    }, BUILDING_BURNING_RUIN);

    std::sort(burning_ruins.begin(), burning_ruins.end(), [&tile] (auto &lhs, auto &rhs) {
        int lhs_dist = calc_maximum_distance(tile, lhs->tile);
        int rhs_dist = calc_maximum_distance(tile, rhs->tile);
        return (lhs_dist < rhs_dist);
    });

    for (const auto &b : burning_ruins) {
        grid_tiles adjacent = map_grid_get_tiles(b, 1);
        for (const auto &t : adjacent) {
            if (map_routing_citizen_can_travel_over_land(tile, t)) {
                return { b->id, t };
            }
        }
    }

    return { 0, tile2i(-1, -1) };
}

// NOTE! burning_ruin cant call on_place(), so all preparing actions should
// be executed in on_create()
void building_burning_ruin::on_create(int orientation) {
    building_impl::on_create(orientation);
    base.fire_duration = (rand() % 128) + 120;
    base.state = BUILDING_STATE_VALID;

    uint8_t random = rand() % current_params().fire_animations;
    xstring anim_name; anim_name.printf("fire%d", random);
    set_animation(anim_name);

    xstring base_name; base_name.printf("base%d", random);
    int img_id = anim(base_name).first_img();
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

custom_span<uint16_t> building_burning_ruin::get_all() {
    return make_span(g_burning_ruins.data(), g_burning_ruins.size());
}

void building_burning_ruin::update_all_ruins() {
    OZZY_PROFILER_FUNCTION();
    int climate = scenario_property_climate();
    bool recalculate_terrain = 0;

    g_burning_ruins.clear();
    buildings_valid_do([&recalculate_terrain] (building &b) {
        auto ruin = b.dcast_burning_ruin();
        g_burning_ruins.push_back(b.id);
        recalculate_terrain |= ruin->update();
    }, BUILDING_BURNING_RUIN);

    if (recalculate_terrain) {
        map_routing_update_land();
    }
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

    const int fire_spread_direction = g_city.maintenance.fire_spread_direction;
    int dir1 = ((fire_spread_direction - 1) + 8) % 8;
    int dir2 = (fire_spread_direction + 1) % 8;

    int directions[] = {fire_spread_direction, dir1, dir2};
    for (const auto &dir : directions) {
        int grid_offset = tile().grid_offset();
        int next_building_id = map_building_at(grid_offset + map_grid_direction_delta(dir));
        if (next_building_id && !building_get(next_building_id)->fire_proof) {
            building_get(next_building_id)->destroy_by_fire();
            return true;
        }
    }

    return false;
}

io_buffer *iob_building_list_burning = new io_buffer([] (io_buffer *iob, size_t version) {
    for (int i = 0; i < g_burning_ruins.capacity(); i++) {
        iob->bind(BIND_SIGNATURE_UINT16, &g_burning_ruins[i]);
    }
});

io_buffer *iob_building_burning_list_info = new io_buffer([] (io_buffer *iob, size_t version) {
    uint32_t total = g_burning_ruins.capacity();
    uint32_t size = g_burning_ruins.size();
    iob->bind(BIND_SIGNATURE_UINT32, &total);
    iob->bind(BIND_SIGNATURE_UINT32, &size);

    g_burning_ruins.resize(size);
});