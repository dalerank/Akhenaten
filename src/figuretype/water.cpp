#include "figuretype/water.h"

#include "building/building.h"
#include "building/model.h"
#include "city/gods.h"
#include "city/message.h"
#include "core/calc.h"
#include "core/random.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/water.h"
#include "scenario/map.h"

void figure::shipwreck_action() {
    //    is_ghost = false;
    height_adjusted_ticks = 0;
    allow_move_type = EMOVE_BOAT;
    //    figure_image_increase_offset(128);
    if (wait_ticks < 1000) {
        map_figure_remove();
        water_dest result = map_water_find_shipwreck_tile(*this);
        if (result.found) {
            tile = result.tile;
            cc_coords.x = 15 * tile.x() + 7;
            cc_coords.y = 15 * tile.y() + 7;
        }
        map_figure_add();
        wait_ticks = 1000;
    }
    wait_ticks++;
    if (wait_ticks > 2000)
        poof();

    sprite_image_id = image_id_from_group(GROUP_FIGURE_SHIPWRECK) + anim.frame / 16;
}


