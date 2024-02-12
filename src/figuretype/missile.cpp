#include "missile.h"

#include "figure/formation.h"
#include "figure/movement.h"
#include "figure/properties.h"
#include "figure/sound.h"
#include "core/profiler.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/view/view.h"
#include "grid/figure.h"
#include "grid/point.h"
#include "sound/effect.h"


void figure_create_missile(int building_id, int x, int y, int x_dst, int y_dst, e_figure_type type) {
    figure* f = figure_create(type, tile2i(x, y), DIR_0_TOP_RIGHT);
    if (f->id) {
        f->missile_damage = (type == FIGURE_BOLT ? 60 : 10);
        f->set_home(building_id);
        f->destination_tile.set(x_dst, y_dst);
        f->set_cross_country_direction(f->cc_coords.x, f->cc_coords.y, 15 * x_dst, 15 * y_dst, 1);
    }
}
void figure::missile_fire_at(int target_id, e_figure_type missile_type) {
    figure* f = figure_get(target_id);
    figure_create_missile(id, tile.x(), tile.y(), f->tile.x(), f->tile.y(), missile_type);
}

bool figure::is_citizen() {
    if (action_state != FIGURE_ACTION_149_CORPSE) {
        if ((type && type != FIGURE_EXPLOSION && type != FIGURE_STANDARD_BEARER && type != FIGURE_MAP_FLAG
             && type != FIGURE_FLOTSAM && type < FIGURE_INDIGENOUS_NATIVE)
            || type == FIGURE_TOWER_SENTRY) {
            return id;
        }
    }
    return 0;
}

bool figure::is_non_citizen() {
    if (action_state == FIGURE_ACTION_149_CORPSE)
        return 0;

    if (is_enemy()) {
        return id;
    }

    if (type == FIGURE_INDIGENOUS_NATIVE && action_state == FIGURE_ACTION_159_NATIVE_ATTACKING)
        return id;

    if (/*type == FIGURE_WOLF*/ type == FIGURE_OSTRICH || type == FIGURE_BIRDS || type == FIGURE_ANTELOPE)
        return id;

    return 0;
}

static int get_citizen_on_tile(int grid_offset) {
    return map_figure_foreach_until(grid_offset, TEST_SEARCH_CITIZEN);
}
static int get_non_citizen_on_tile(int grid_offset) {
    return map_figure_foreach_until(grid_offset, TEST_SEARCH_NON_CITIZEN);
}

void figure::missile_hit_target(int target_id, int legionary_type) {
    figure* target = figure_get(target_id);
    const figure_properties* target_props = figure_properties_for_type(target->type);
    int max_damage = target_props->max_damage;
    int damage_inflicted = figure_properties_for_type(type)->missile_attack_value - target_props->missile_defense_value;
    formation* m = formation_get(target->formation_id);
    if (damage_inflicted < 0) {
        damage_inflicted = 0;
    }

    if (target->type == legionary_type && m->is_halted && m->layout == FORMATION_COLUMN) {
        damage_inflicted = 1;
    }

    int target_damage = damage_inflicted + target->damage;
    if (target_damage <= max_damage) {
        target->damage = target_damage;
    } else { // poof target
        target->damage = max_damage + 1;
        target->kill();
        target->wait_ticks = 0;
        target->play_die_sound();
        formation_update_morale_after_death(m);
    }
    poof();
    // for missiles: building_id contains the figure who shot it
    int missile_formation = figure_get(homeID())->formation_id;
    formation_record_missile_attack(m, missile_formation);
}

void figure::arrow_action() {
    use_cross_country = true;
    progress_on_tile++;
    if (progress_on_tile > 120) {
        poof();
    }

    int should_die = move_ticks_cross_country(4);
    int target_id = get_non_citizen_on_tile(tile.grid_offset());
    if (target_id) {
        missile_hit_target(target_id, FIGURE_STANDARD_BEARER);
        sound_effect_play(SOUND_EFFECT_ARROW_HIT);
    } else if (should_die) {
        poof();
    }
}

void figure::spear_action() {
    use_cross_country = true;
    progress_on_tile++;
    if (progress_on_tile > 120) {
        poof();
    }

    int should_die = move_ticks_cross_country(4);
    int target_id = get_citizen_on_tile(tile.grid_offset());
    if (target_id) {
        missile_hit_target(target_id, FIGURE_STANDARD_BEARER);
        sound_effect_play(SOUND_EFFECT_JAVELIN);
    } else if (should_die) {
        poof();
    }

    int dir = (16 + direction - 2 * city_view_orientation()) % 16;
    sprite_image_id = image_id_from_group(GROUP_FIGURE_MISSILE) + dir;
}

void figure::javelin_action() {
    use_cross_country = true;
    progress_on_tile++;
    if (progress_on_tile > 120) {
        poof();
    }

    int should_die = move_ticks_cross_country(4);
    int target_id = get_non_citizen_on_tile(tile.grid_offset());
    if (target_id) {
        missile_hit_target(target_id, FIGURE_ENEMY_CAESAR_LEGIONARY);
        sound_effect_play(SOUND_EFFECT_JAVELIN);
    } else if (should_die) {
        poof();
    }
}

void figure::bolt_action() {
    use_cross_country = true;
    progress_on_tile++;
    if (progress_on_tile > 120) {
        poof();
    }

    int should_die = move_ticks_cross_country(4);
    int target_id = get_non_citizen_on_tile(tile.grid_offset());
    if (target_id) {
        figure* target = figure_get(target_id);
        const figure_properties* target_props = figure_properties_for_type(target->type);
        int max_damage = target_props->max_damage;
        int damage_inflicted = figure_properties_for_type(type)->missile_attack_value - target_props->missile_defense_value;
        if (damage_inflicted < 0) {
            damage_inflicted = 0;
        }

        int target_damage = damage_inflicted + target->damage;
        if (target_damage <= max_damage) {
            target->damage = target_damage;
        } else { // poof target
            target->damage = max_damage + 1;
            target->kill();
            target->wait_ticks = 0;
            target->play_die_sound();
            formation_update_morale_after_death(formation_get(target->formation_id));
        }

        sound_effect_play(SOUND_EFFECT_BALLISTA_HIT_PERSON);
        poof();

    } else if (should_die) {
        sound_effect_play(SOUND_EFFECT_BALLISTA_HIT_GROUND);
        poof();
    }
    int dir = (16 + direction - 2 * city_view_orientation()) % 16;
    sprite_image_id = image_id_from_group(GROUP_FIGURE_MISSILE) + 32 + dir;
}
