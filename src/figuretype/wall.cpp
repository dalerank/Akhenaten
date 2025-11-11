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

static const int BALLISTA_FIRING_OFFSETS[]
  = {0, 1, 2, 3, 4, 5, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void figure::ballista_action() {
    building* b = home();
    terrain_usage = TERRAIN_USAGE_WALLS;
    use_cross_country = false;
    height_adjusted_ticks = 10;
    current_height = 45;

    if (b->state != BUILDING_STATE_VALID || !b->has_figure(3, id))
        poof();

    if (b->num_workers <= 0 || !b->has_figure(3))
        poof();

    map_figure_remove();
    switch (city_view_orientation()) {
    case DIR_0_TOP_RIGHT:
        tile = b->tile;
        break;
    case DIR_2_BOTTOM_RIGHT:
        tile = b->tile.shifted(1, 0);
        break;
    case DIR_4_BOTTOM_LEFT:
        tile = b->tile.shifted(1, 1);
        break;
    case DIR_6_TOP_LEFT:
        tile = b->tile.shifted(0, 1);
        break;
    }
    //    tile.grid_offset() = MAP_OFFSET(tile.x(), tile.y());
    map_figure_add();

    switch (action_state) {
    case FIGURE_ACTION_149_CORPSE:
        poof();
        break;

    case FIGURE_ACTION_180_BALLISTA_CREATED:
        wait_ticks++;
        if (wait_ticks > 20) {
            wait_ticks = 0;
            tile2i tile;
            if (figure_combat_get_missile_target_for_soldier(this, 15, &tile)) {
                action_state = FIGURE_ACTION_181_BALLISTA_FIRING;
                wait_ticks_missile = 100; // figure_properties_for_type(type).missile_delay;
            }
        }
        break;

    case FIGURE_ACTION_181_BALLISTA_FIRING:
        wait_ticks_missile++;
        if (wait_ticks_missile > 100) { // figure_properties_for_type(type).missile_delay) {
            tile2i tile;
            if (figure_combat_get_missile_target_for_soldier(this, 15, &tile)) {
                direction = calc_missile_shooter_direction(tile, tile);
                wait_ticks_missile = 0;
                figure* f = figure_get(target_figure_id);
                figure_missile::create(home_building_id, tile, f->tile, FIGURE_BOLT);
                events::emit(event_sound_effect{ SOUND_EFFECT_BALLISTA_SHOOT });
            } else {
                action_state = FIGURE_ACTION_180_BALLISTA_CREATED;
            }
        }
        break;
    }
    int dir = figure_image_direction();
    if (action_state == FIGURE_ACTION_181_BALLISTA_FIRING) {
        main_image_id = image_id_from_group(GROUP_FIGURE_BALLISTA) + dir + 8 * BALLISTA_FIRING_OFFSETS[wait_ticks_missile / 4];
    } else {
        main_image_id = image_id_from_group(GROUP_FIGURE_BALLISTA) + dir;
    }
}

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
