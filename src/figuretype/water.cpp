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

void figure_sink_all_ships(void) {
    for (int i = 1; i < MAX_FIGURES[GAME_ENV]; i++) {
        figure* f = figure_get(i);
        if (f->state != FIGURE_STATE_ALIVE)
            continue;

        if (f->type == FIGURE_TRADE_SHIP)
            f->destination()->data.dock.trade_ship_id = 0;
        else if (f->type == FIGURE_FISHING_BOAT)
            f->home()->data.industry.fishing_boat_id = 0;
        else {
            continue;
        }
        f->set_home(0);
        f->type = FIGURE_SHIPWRECK;
        f->wait_ticks = 0;
    }
}

void figure::shipwreck_action() {
    //    is_ghost = false;
    height_adjusted_ticks = 0;
    allow_move_type = EMOVE_BOAT;
    //    figure_image_increase_offset(128);
    if (wait_ticks < 1000) {
        map_figure_remove();
        tile2i shipwreck_tile;
        if (map_water_find_shipwreck_tile(this, &shipwreck_tile)) {
            tile = shipwreck_tile;
            //            tile.x() = tile.x();
            //            tile.y() = tile.y();
            //            tile.grid_offset() = MAP_OFFSET(tile.x(), tile.y());
            cc_coords.x = 15 * tile.x() + 7;
            cc_coords.y = 15 * tile.y() + 7;
        }
        map_figure_add();
        wait_ticks = 1000;
    }
    wait_ticks++;
    if (wait_ticks > 2000)
        poof();

    sprite_image_id = image_id_from_group(GROUP_FIGURE_SHIPWRECK) + anim_frame / 16;
}


