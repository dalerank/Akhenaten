#include "figure_flotsam.h"

#include "figuretype/figure_flotsam.h"
#include "figure/figure.h"
#include "city/city.h"
#include "core/random.h"
#include "graphics/image.h"
#include "graphics/image_desc.h"

#include "js/js_game.h"

figures::model_t<figure_flotsam> flotsam_m;

static const int FLOTSAM_TYPE_0[] = {0, 1, 2, 3, 4, 4, 4, 3, 2, 1, 0, 0};
static const int FLOTSAM_TYPE_12[] = {0, 1, 1, 2, 2, 3, 3, 4, 4, 4, 3, 2, 1, 0, 0, 1, 1, 2, 2, 1, 1, 0, 0, 0};
static const int FLOTSAM_TYPE_3[] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

void figure_flotsam::on_create() {

}

void figure_flotsam::figure_action() {
    base.allow_move_type = EMOVE_DEEPWATER;
    if (!scenario_map_has_river_exit()) {
        return;
    }

    base.cart_image_id = 0;
    base.terrain_usage = TERRAIN_USAGE_ANY;

    switch (action_state()) {
    case FIGURE_ACTION_128_FLOTSAM_CREATED:
        base.wait_ticks--;
        if (base.wait_ticks <= 0) {
            base.action_state = FIGURE_ACTION_129_FLOTSAM_FLOATING;
            base.wait_ticks = 0;
            if (!base.resource_id && g_city.religion.osiris_create_shipwreck_flotsam()) {
                base.min_max_seen = 1;
            }

            base.destination_tile = scenario_map_river_exit();
        }
        break;

    case FIGURE_ACTION_129_FLOTSAM_FLOATING:
        if (base.flotsam_visible) {
            base.flotsam_visible = false;
        } else {
            base.flotsam_visible = true;
            base.wait_ticks++;
            base.move_ticks(1);
            base.height_adjusted_ticks = 0;
            if (direction() == DIR_FIGURE_NONE || direction() == DIR_FIGURE_REROUTE
                || direction() == DIR_FIGURE_CAN_NOT_REACH) {
                base.action_state = FIGURE_ACTION_130_FLOTSAM_OFF_MAP;
            }
        }
        break;

    case FIGURE_ACTION_130_FLOTSAM_OFF_MAP:
        base.min_max_seen = 0;
        base.action_state = FIGURE_ACTION_128_FLOTSAM_CREATED;
        if (base.wait_ticks >= 400) {
            base.wait_ticks = random_byte() & 7;
        } else if (base.wait_ticks >= 200) {
            base.wait_ticks = 50 + (random_byte() & 0xf);
        } else if (base.wait_ticks >= 100) {
            base.wait_ticks = 100 + (random_byte() & 0x1f);
        } else if (base.wait_ticks >= 50) {
            base.wait_ticks = 200 + (random_byte() & 0x3f);
        } else {
            base.wait_ticks = 300 + random_byte();
        }
        base.map_figure_remove();
        base.tile = scenario_map_river_entry();
        base.cc_coords.x = 15 * tilex();
        base.cc_coords.y = 15 * tiley();
        break;
    }
}

void figure_flotsam::update_animation() {
    auto &d = runtime_data();
    d.frame = std::min<short>(d.frame++, 2048);
    int cur_frame = std::min<int>(d.frame / 36, 35);
    base.main_image_id = flotsam_m.anim["walk"].first_img() + cur_frame;
}
