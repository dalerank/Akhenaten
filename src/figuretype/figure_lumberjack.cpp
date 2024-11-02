#include "figuretype/figure_lumberjack.h"

#include "graphics/image_groups.h"
#include "grid/vegetation.h"
#include "config/config.h"
#include "figure_lumberjack.h"
#include "graphics/image.h"
#include "graphics/graphics.h"

#include "js/js_game.h"

figures::model_t<figure_lumberjack> lumberjack_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_lumberjack);
void config_load_figure_lumberjack() {
    lumberjack_m.load();
}

void figure_lumberjack::figure_action() {
    switch (action_state()) {
    case ACTION_8_RECALCULATE:
    case ACTION_14_GATHERER_CREATED: // spawning
        base.anim.frame = 0;
        if (--wait_ticks <= 0) {
            tile2i dest(-1, -1);
            bool found_resource = base.find_resource_tile(RESOURCE_TIMBER, dest);

            if (found_resource) {
                base.anim.offset = 0;
                do_goto(dest, TERRAIN_USAGE_PREFER_ROADS);
                advance_action(9);
            } else {
                poof();
            }
        }
        break;

    case 9: // go to gathering place
        if (do_goto(destination_tile, TERRAIN_USAGE_PREFER_ROADS)) {
            if (!can_harvest_point(MAP_OFFSET(destination_tile.x(), destination_tile.y()))) {
                wait_ticks = 0;
                advance_action(8);
            } else
                advance_action(10);
        }
        break;

    case 10: // gathering resource
        // someone finished harvesting this spot (for "multiple gatherers" config setting enabled)
        if (map_get_vegetation_growth(tile()) < 255) {
            wait_ticks = 10;
            advance_action(8);
        } else {
            // harvesting.....
            if (wait_ticks >= 300) {
                map_vegetation_deplete(tile());
                advance_action(11);
            }
            // progress faster with multiple people on one spot
            if (config_get(CONFIG_GP_CH_MULTIPLE_GATHERERS))
                wait_ticks += gatherers_harvesting_point(tile());
            else
                wait_ticks++;
        }
        break;
    case 11: // returning with resource
        if (do_returnhome(TERRAIN_USAGE_PREFER_ROADS)) {
            home()->stored_amount_first += 25;
        }
        break;
    }
}

const animations_t &figure_lumberjack::anim() const {
    return lumberjack_m.anim;
}

void figure_lumberjack::update_animation() {
    figure_impl::update_animation();

    pcstr anim_key = "walk";
    switch (action_state()) {
    case 10: // gathering
        anim_key = "work";
        break;

    case FIGURE_ACTION_149_CORPSE:
        anim_key = "death";
        break;

    case 11: // returning
        anim_key = "back";
        break;
    }

    image_set_animation(anim_key);
}

void figure_lumberjack::figure_before_action() {
    building *b = home();
    if (b->state != BUILDING_STATE_VALID) {
        poof();
    }
}
