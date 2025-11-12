#include "figure_ballista.h"

#include "figure/combat.h"
#include "city/city_figures.h"
#include "figuretype/figure_missile.h"
#include "sound/sound.h"
#include "game/game_events.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_ballista);

static const int BALLISTA_FIRING_OFFSETS[] = {
   0, 1, 2, 3, 4, 5, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
};

void figure_ballista::figure_action() {
    building *b = home();
    base.terrain_usage = TERRAIN_USAGE_WALLS;
    base.use_cross_country = false;
    base.height_adjusted_ticks = 10;
    base.current_height = 45;

    if (b->state != BUILDING_STATE_VALID || !b->has_figure(3, id()))
        poof();

    if (b->num_workers <= 0 || !b->has_figure(3))
        poof();

    base.map_figure_remove();
    switch (city_view_orientation()) {
    case DIR_0_TOP_RIGHT:
        base.tile = b->tile;
        break;
    case DIR_2_BOTTOM_RIGHT:
        base.tile = b->tile.shifted(1, 0);
        break;
    case DIR_4_BOTTOM_LEFT:
        base.tile = b->tile.shifted(1, 1);
        break;
    case DIR_6_TOP_LEFT:
        base.tile = b->tile.shifted(0, 1);
        break;
    }
    //    tile.grid_offset() = MAP_OFFSET(tile.x(), tile.y());
    base.map_figure_add();

    switch (base.action_state) {
    case FIGURE_ACTION_149_CORPSE:
        poof();
        break;

    case ACTION_180_BALLISTA_CREATED:
        base.wait_ticks++;
        if (base.wait_ticks > 20) {
            base.wait_ticks = 0;
            tile2i tile;
            if (figure_combat_get_missile_target_for_soldier(&base, 15, &tile)) {
                base.action_state = ACTION_181_BALLISTA_FIRING;
                base.wait_ticks_missile = 100; // figure_properties_for_type(type).missile_delay;
            }
        }
        break;

    case ACTION_181_BALLISTA_FIRING:
        base.wait_ticks_missile++;
        if (base.wait_ticks_missile > 100) { // figure_properties_for_type(type).missile_delay) {
            tile2i tile;
            if (figure_combat_get_missile_target_for_soldier(&base, 15, &tile)) {
                base.direction = calc_missile_shooter_direction(tile, tile);
                base.wait_ticks_missile = 0;
                figure *f = figure_get(base.target_figure_id);
                figure_missile::create(base.home_building_id, tile, f->tile, FIGURE_BOLT);
                events::emit(event_sound_effect{ SOUND_EFFECT_BALLISTA_SHOOT });
            } else {
                base.action_state = ACTION_180_BALLISTA_CREATED;
            }
        }
        break;
    }
}

void figure_ballista::update_animation() {
    int dir = base.figure_image_direction();
    if (base.action_state == ACTION_181_BALLISTA_FIRING) {
        base.main_image_id = image_id_from_group(GROUP_FIGURE_BALLISTA) + dir + 8 * BALLISTA_FIRING_OFFSETS[base.wait_ticks_missile / 4];
    } else {
        base.main_image_id = image_id_from_group(GROUP_FIGURE_BALLISTA) + dir;
    }
}

void figure_ballista::before_poof() {
    // do nothing
}
