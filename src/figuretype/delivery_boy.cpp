#include "market.h"

#include "building/building.h"
#include "building/building_granary.h"
#include "building/storage.h"
#include "core/log.h"
#include "building/storage_yard.h"
#include "figure/combat.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "game/resource.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "config/config.h"

void figure::delivery_boy_action() {
    figure* leader = figure_get(leading_figure_id);
    if (leader->state == FIGURE_STATE_ALIVE) {
        if (leader->type == FIGURE_MARKET_BUYER || leader->type == FIGURE_DELIVERY_BOY) {
            follow_ticks(1);
        } else {
            poof();
        }
    } else { // leader arrived at market, drop resource at market
        if (config_get(CONFIG_GP_CH_DELIVERY_BOY_GOES_TO_MARKET_ALONE)) {
            leading_figure_id = 0;
            if (do_returnhome()) {
                home()->data.market.inventory[collecting_item_id] += 100;
                poof();
            }
        } else {
            home()->data.market.inventory[collecting_item_id] += 100;
            poof();
        }
    }

    if (leader->is_ghost) {
        is_ghost = true;
    }

    int dir = figure_image_normalize_direction(direction < 8 ? direction : previous_tile_direction);
    if (action_state == FIGURE_ACTION_149_CORPSE) {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_GRANARY_BOY_DEATH) + figure_image_corpse_offset();
    } else {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_GRANARY_BOY) + dir + 8 * anim_frame;
    }
}
