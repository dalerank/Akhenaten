#include "figure_ballista.h"

#include "building/building.h"
#include "city/city_figures.h"
#include "core/calc.h"
#include "figure/combat.h"
#include "figuretype/figure_missile.h"
#include "game/game_events.h"
#include "graphics/animkeys.h"
#include "graphics/image.h"
#include "graphics/view/view.h"
#include "js/js_game.h"
#include "sound/effect.h"
#include "sound/sound.h"

ballista_rules_t ANK_VARIABLE(ballista_rules);

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_ballista);

void figure_ballista::figure_action() {
    building *b = home();
    runtime_data().shooting = 0;
    base.terrain_usage = TERRAIN_USAGE_WALLS;
    base.use_cross_country = false;
    // OG is_ghost=1: drawn with tower height, not a ground walker.
    base.height_adjusted_ticks = 10;
    base.current_height = 0x2D;

    if (!b || b->state != BUILDING_STATE_VALID || !b->has_figure(BUILDING_SLOT_BALLISTA, id())) {
        poof();
        return;
    }
    // Goes with its tower workers or its sentry (OG figure_id / slot 0).
    if (b->num_workers < 1 || !b->has_figure(0)) {
        poof();
        return;
    }

    base.map_figure_remove();
    switch (g_camera.orientation) {
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
    base.map_figure_add();

    const auto &params = current_params();
    const int missile_delay = params.missile_delay;
    const int missile_range = params.missile_range > 0 ? params.missile_range : 15;
    const auto &rules = ballista_rules;

    switch (base.action_state) {
    case FIGURE_ACTION_149_CORPSE:
        poof();
        return;

    case ACTION_180_BALLISTA_CREATED:
        if (++base.wait_ticks <= rules.search_ticks) {
            break;
        }
        base.wait_ticks = 0;
        {
            tile2i tile;
            if (figure_combat_get_missile_target_for_soldier(&base, missile_range, &tile)) {
                base.action_state = ACTION_181_BALLISTA_FIRING;
                base.wait_ticks_missile = (uint8_t)missile_delay;
            }
        }
        break;

    case ACTION_181_BALLISTA_FIRING:
        if (++base.wait_ticks_missile <= missile_delay) {
            break;
        }
        runtime_data().shooting = 1;
        {
            tile2i tile;
            if (!figure_combat_get_missile_target_for_soldier(&base, missile_range, &tile)) {
                base.action_state = ACTION_180_BALLISTA_CREATED;
                break;
            }
            base.wait_ticks++;
            base.direction = (uint8_t)calc_missile_shooter_direction(base.tile, tile);
            if (base.wait_ticks == rules.aim_ticks) {
                // OG fires FIGURE_JAVELIN (figure_javelin_action), not bolt.
                figure_missile::create(id(), base.tile, tile, FIGURE_JAVELIN);
                events::emit(event_sound_effect{SOUND_EFFECT_BALLISTA_SHOOT});
            } else if (base.wait_ticks > rules.reload_ticks) {
                base.wait_ticks = 0;
                base.wait_ticks_missile = 0;
            }
        }
        break;

    default:
        base.action_state = ACTION_180_BALLISTA_CREATED;
        break;
    }
}

void figure_ballista::update_animation() {
    int dir = base.figure_image_direction();
    if (dir < 0) {
        dir += 8;
    }
    dir %= 8;

    if (base.action_state == ACTION_181_BALLISTA_FIRING && runtime_data().shooting) {
        const int first = anim(animkeys().fire).first_img();
        base.main_image_id = first + ((base.wait_ticks / 2) * 8) + dir;
    } else {
        const int first = anim(animkeys().walk).first_img();
        base.main_image_id = first + dir;
    }
}

void figure_ballista::before_poof() {
}
