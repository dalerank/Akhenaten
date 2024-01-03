#include "figuretype/water.h"

#include "figure/figure.h"
#include "city/gods.h"
#include "core/random.h"
#include "graphics/image.h"
#include "graphics/image_desc.h"

static const int FLOTSAM_RESOURCE_IDS[] = {3, 1, 3, 2, 1, 3, 2, 3, 2, 1, 3, 3, 2, 3, 3, 3, 1, 2, 0, 1};
static const int FLOTSAM_WAIT_TICKS[]  = {10, 50, 100, 130, 200, 250, 400, 430, 500, 600, 70, 750, 820, 830, 900, 980, 1010, 1030, 1200, 1300};

static const int FLOTSAM_TYPE_0[] = {0, 1, 2, 3, 4, 4, 4, 3, 2, 1, 0, 0};
static const int FLOTSAM_TYPE_12[] = {0, 1, 1, 2, 2, 3, 3, 4, 4, 4, 3, 2, 1, 0, 0, 1, 1, 2, 2, 1, 1, 0, 0, 0};
static const int FLOTSAM_TYPE_3[] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

void city_river_update_flotsam() {
    if (!scenario_map_has_river_entry() || !scenario_map_has_river_exit() || !scenario_map_has_flotsam()) {
        return;
    }

    for (int i = 1; i < MAX_FIGURES[GAME_ENV]; i++) {
        figure* f = figure_get(i);
        if (f->state == FIGURE_STATE_ALIVE && f->type == FIGURE_FLOTSAM) {
            return;
        }
    }

    tile2i river_entry = scenario_map_river_entry();
    for (int i = 0; i < 1; i++) {
        figure* f = figure_create(FIGURE_FLOTSAM, river_entry, DIR_0_TOP_RIGHT);
        f->action_state = FIGURE_ACTION_128_FLOTSAM_CREATED;
        f->set_resource((e_resource)FLOTSAM_RESOURCE_IDS[i]);
        f->wait_ticks = FLOTSAM_WAIT_TICKS[i];
        f->allow_move_type = EMOVE_FLOTSAM;
    }
}

void figure::flotsam_action() {
    allow_move_type = EMOVE_FLOTSAM;
    if (!scenario_map_has_river_exit()) {
        return;
    }

    cart_image_id = 0;
    terrain_usage = TERRAIN_USAGE_ANY;

    switch (action_state) {
    case FIGURE_ACTION_128_FLOTSAM_CREATED:
        wait_ticks--;
        if (wait_ticks <= 0) {
            action_state = FIGURE_ACTION_129_FLOTSAM_FLOATING;
            wait_ticks = 0;
            if (!resource_id && city_god_osiris_create_shipwreck_flotsam())
                min_max_seen = 1;

            destination_tile = scenario_map_river_exit();
            //                map_point river_exit = scenario_map_river_exit();
            //                destination_tile.x() = river_exit.x();
            //                destination_tile.y() = river_exit.y();
        }
        break;

    case FIGURE_ACTION_129_FLOTSAM_FLOATING:
        if (flotsam_visible) {
            flotsam_visible = false;
        } else {
            flotsam_visible = true;
            wait_ticks++;
            move_ticks(1);
            height_adjusted_ticks = 0;
            if (direction == DIR_FIGURE_NONE || direction == DIR_FIGURE_REROUTE
                || direction == DIR_FIGURE_CAN_NOT_REACH) {
                action_state = FIGURE_ACTION_130_FLOTSAM_OFF_MAP;
            }
        }
        break;

    case FIGURE_ACTION_130_FLOTSAM_OFF_MAP:
        min_max_seen = 0;
        action_state = FIGURE_ACTION_128_FLOTSAM_CREATED;
        if (wait_ticks >= 400) {
            wait_ticks = random_byte() & 7;
        } else if (wait_ticks >= 200) {
            wait_ticks = 50 + (random_byte() & 0xf);
        } else if (wait_ticks >= 100) {
            wait_ticks = 100 + (random_byte() & 0x1f);
        } else if (wait_ticks >= 50) {
            wait_ticks = 200 + (random_byte() & 0x3f);
        } else {
            wait_ticks = 300 + random_byte();
        }
        map_figure_remove();
        tile = scenario_map_river_entry();
        cc_coords.x = 15 * tile.x();
        cc_coords.y = 15 * tile.y();
        break;
    }

    local_data.flotsam.frame = std::min<short>(local_data.flotsam.frame++, 2048);
    int cur_frame = std::min<int>(local_data.flotsam.frame / 36, 35);
    sprite_image_id = image_group(IMG_FLOTSAM) + cur_frame;
}