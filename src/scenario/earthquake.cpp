#include "earthquake.h"

#include "building/building.h"
#include "building/destruction.h"
#include "building/building_wall.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "city/city_message.h"
#include "core/calc.h"
#include "core/random.h"
#include "figure/figure.h"
#include "game/game.h"
#include "grid/building.h"
#include "grid/canals.h"
#include "grid/grid.h"
#include "grid/image.h"
#include "grid/gardens.h"
#include "grid/property.h"
#include "grid/routing/routing_terrain.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "scenario/scenario.h"
#include "scenario/event_phrases.h"
#include "core/log.h"
#include <algorithm>
#include "sound/effect.h"

static int can_advance_earthquake_to_tile(int x, int y) {
    if (map_terrain_is(MAP_OFFSET(x, y), TERRAIN_ELEVATION | TERRAIN_ROCK | TERRAIN_WATER))
        return 0;
    else {
        return 1;
    }
}

static void advance_earthquake_to_tile(int x, int y) {
    int grid_offset = MAP_OFFSET(x, y);
    int building_id = map_building_at(grid_offset);
    if (building_id) {
        building_get(building_id)->destroy_by_fire();
        int ruin_id = map_building_at(grid_offset);
        if (ruin_id) {
            building_get(ruin_id)->state = BUILDING_STATE_DELETED_BY_GAME;
            map_building_set(grid_offset, 0);
        }
    }
    map_terrain_set(grid_offset, 0);
    map_tiles_set_earthquake(x, y);
    map_tiles_gardens_update_all();
    map_tiles_update_all_roads();
    map_tiles_update_all_plazas();
    // Augustus 3bdd1189d: the fault changes the neighbours of meadow, wall and canal tiles too.
    map_tiles_update_all_meadow();
    building_mud_wall::update_all_walls();
    map_canal_update_all_tiles(0);

    map_routing_update_land();
    map_routing_update_walls();

    figure_create_explosion_cloud(tile2i(x, y), 1);
}

namespace {

    enum e_earthquake_state : uint8_t {
        EARTHQUAKE_STATE_DUE = 0,
        EARTHQUAKE_STATE_RUNNING = 1,
        EARTHQUAKE_STATE_OVER = 2,
    };

    constexpr int EARTHQUAKE_STEPS_PER_AMOUNT = 25;

    // OG scenario_rules.c earthquake_steps: the front each random step moves and its direction.
    struct earthquake_step {
        int front;
        int dx;
        int dy;
    };
    constexpr earthquake_step earthquake_steps[16] = {
      {0, 0, -1},
      {1, 1, 0},
      {2, 0, 1},
      {3, -1, 0},
      {0, 0, -1},
      {0, -1, 0},
      {0, 1, 0},
      {1, 1, 0},
      {1, 0, -1},
      {1, 0, 1},
      {2, 0, 1},
      {2, -1, 0},
      {2, 1, 0},
      {3, -1, 0},
      {3, 0, -1},
      {3, 0, 1},
    };

    bool earthquake_is_due(const event_ph_t& e) {
        switch (e.event_trigger_type) {
        case EVENT_TRIGGER_ONLY_VIA_EVENT:
        case EVENT_TRIGGER_ALREADY_FIRED:
        case EVENT_TRIGGER_BY_FAVOUR:
        case EVENT_TRIGGER_BY_FAVOUR_IN_USE:
            return false;
        default:
            return e.date() == game.simtime.date();
        }
    }

    bool earthquake_start(event_ph_t& e) {
        if (!earthquake_is_due(e)) {
            return false;
        }
        auto& quake = e.data.earthquake;
        for (int i = 0; i < 4; i++) {
            quake.locations[2 * i] = (int16_t)g_scenario.earthquake_point.x();
            quake.locations[2 * i + 1] = (int16_t)g_scenario.earthquake_point.y();
        }
        e.is_active = true;
        if (e.event_trigger_type != EVENT_TRIGGER_RECURRING) {
            e.event_trigger_type = EVENT_TRIGGER_ALREADY_FIRED;
        }
        e.event_state = (e_event_state)EARTHQUAKE_STATE_RUNNING;
        quake.duration = 0;
        quake.ticks = 0;
        advance_earthquake_to_tile(quake.locations[0], quake.locations[1]);
        const int grid_offset = MAP_OFFSET(quake.locations[0], quake.locations[1]);
        city_message_post_full(true, "message_earthquake", &e, -1, PHRASE_earthquake_title,
          PHRASE_earthquake_initial_announcement, PHRASE_earthquake_no_reason_A, 0, grid_offset);

        logs::info("[earthquake] start event=%d at %d,%d", e.event_id, quake.locations[0], quake.locations[1]);
        return true;
    }

} // namespace

// OG disaster_events.c scenario_earthquake_event_process: four fronts, one step every `delay`
// ticks, amount * 25 steps in all.
bool scenario_earthquake_event_process(event_ph_t& e) {
    if (e.type != EVENT_TYPE_EARTHQUAKE) {
        return false;
    }
    if (e.event_state == (e_event_state)EARTHQUAKE_STATE_DUE) {
        return earthquake_start(e);
    }
    if (e.event_state != (e_event_state)EARTHQUAKE_STATE_RUNNING) {
        return false;
    }
    auto& quake = e.data.earthquake;
    if (++quake.ticks < quake.delay) {
        return true;
    }
    quake.ticks = 0;
    const int steps = std::max(e.amount.value * EARTHQUAKE_STEPS_PER_AMOUNT, EARTHQUAKE_STEPS_PER_AMOUNT);
    if (++quake.duration >= steps) {
        e.event_state = (e_event_state)EARTHQUAKE_STATE_OVER;
        e.is_active = false;
    }
    const int r = random_byte() & 15;
    e.earthquake_step = (int16_t)r;
    const earthquake_step& step = earthquake_steps[r];
    int16_t* front = &quake.locations[2 * step.front];
    const int x = calc_bound(front[0] + step.dx, 0, g_scenario.map.width - 1);
    const int y = calc_bound(front[1] + step.dy, 0, g_scenario.map.height - 1);
    if (can_advance_earthquake_to_tile(x, y)) {
        front[0] = (int16_t)x;
        front[1] = (int16_t)y;
        advance_earthquake_to_tile(x, y);
    }
    return true;
}

// OG event_manager.c scenario_earthquake_process: only the first due or running earthquake moves each tick.
void scenario_earthquake_process() {
    if (!g_scenario.earthquake_point.valid()) {
        return;
    }
    for (int i = 0; i < g_scenario.events.events_count(); i++) {
        if (scenario_earthquake_event_process(*g_scenario.events.at(i))) {
            return;
        }
    }
}

int scenario_earthquake_is_in_progress(void) {
    for (int i = 0; i < g_scenario.events.events_count(); i++) {
        const event_ph_t* e = g_scenario.events.at(i);
        if (e->type == EVENT_TYPE_EARTHQUAKE && e->event_state == (e_event_state)EARTHQUAKE_STATE_RUNNING) {
            return 1;
        }
    }
    return 0;
}

static void set_earthquake_image(int grid_offset) {
    tile2i tile(grid_offset);
    if (map_terrain_is(grid_offset, TERRAIN_ROCK) && map_property_is_plaza_or_earthquake(tile)) {
        const terrain_image img = map_image_context_get_earthquake(grid_offset);
        if (img.is_valid) {
            map_image_set(grid_offset, image_id_from_group(GROUP_TERRAIN_EARTHQUAKE) + img.group_offset + img.item_offset);
        } else {
            map_image_set(grid_offset, image_id_from_group(GROUP_TERRAIN_EARTHQUAKE));
        }
        map_property_set_multi_tile_size(grid_offset, 1);
        map_property_mark_draw_tile(grid_offset);
    }
}

void update_earthquake_tile(int grid_offset) {
    tile2i tile(grid_offset);

    if (map_terrain_is(grid_offset, TERRAIN_ROCK) && map_property_is_plaza_or_earthquake(tile)) {
        map_terrain_add(grid_offset, TERRAIN_ROCK);
        map_property_mark_plaza_or_earthquake(grid_offset);
        map_tiles_foreach_region_tile(tile.shifted(-1, -1), tile.shifted(1, 1), set_earthquake_image);
    }
}

void map_tiles_update_all_earthquake(void) {
    map_tiles_foreach_map_tile(update_earthquake_tile);
}

void map_tiles_set_earthquake(int x, int y) {
    int grid_offset = MAP_OFFSET(x, y);
    // earthquake: terrain = rock && bitfields = plaza
    map_terrain_add(grid_offset, TERRAIN_ROCK);
    map_property_mark_plaza_or_earthquake(grid_offset);

    map_tiles_foreach_region_tile(tile2i(x - 1, y - 1), tile2i(x + 1, y + 1), set_earthquake_image);
}


