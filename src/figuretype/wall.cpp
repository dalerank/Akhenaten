#include "wall.h"

#include "building/building.h"
#include "core/calc.h"
#include "figure/combat.h"
#include "figure/enemy_army.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "figuretype/figure_missile.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/view/view.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/routing/routing_terrain.h"
#include "figuretype/figure_tower_sentry.h"
#include "grid/terrain.h"
#include "game/game_config.h"
#include "sound/sound.h"
#include "city/city_figures.h"
#include "game/game_events.h"

void figure_tower_sentry_reroute(void) {
    for (int i = 1; i < MAX_FIGURES; i++) {
        figure* f = figure_get(i);
        if (f->type != FIGURE_TOWER_SENTRY || map_routing_is_wall_passable(f->tile.grid_offset()))
            continue;

        // tower sentry got off wall due to rotation
        int x_tile, y_tile;
        if (map_routing_wall_tile_in_radius(f->tile.x(), f->tile.y(), 2, &x_tile, &y_tile)) {
            f->route_remove();
            f->progress_on_tile = 1;
            f->map_figure_remove();
            f->previous_tile = f->tile = tile2i(x_tile, y_tile);

            f->cc_coords.x = 15 * x_tile;
            f->cc_coords.y = 15 * y_tile;

            f->map_figure_add();
            f->action_state = ACTION_173_TOWER_SENTRY_RETURNING;
            f->destination_tile = f->source_tile;
        } else {
            // Teleport back to tower
            f->map_figure_remove();
            building* b = f->home();
            f->source_tile = f->tile = tile2i(b->tile.x(), b->tile.y());
            f->map_figure_add();
            f->action_state = ACTION_170_TOWER_SENTRY_AT_REST;
            f->route_remove();
        }
    }
}

void figure_kill_tower_sentries_at(tile2i tile) {
    for (int i = 0; i < MAX_FIGURES; i++) {
        figure* f = figure_get(i);
        if (!f->is_dead() && f->type == FIGURE_TOWER_SENTRY) {
            if (calc_maximum_distance(f->tile, tile) <= 1)
                f->poof();
        }
    }
}
