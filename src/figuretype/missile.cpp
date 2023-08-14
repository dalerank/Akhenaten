#include "missile.h"

#include "figure/formation.h"
#include "figure/movement.h"
#include "figure/properties.h"
#include "figure/sound.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/view/view.h"
#include "grid/figure.h"
#include "grid/point.h"
#include "sound/effect.h"

static const int CLOUD_TILE_OFFSETS[] = {0, 0, 0, 1, 1, 2};

static const int CLOUD_CC_OFFSETS[] = {0, 7, 14, 7, 14, 7};

static const int CLOUD_SPEED[] = {1, 2, 1, 3, 2, 1, 3, 2, 1, 1, 2, 1, 2, 1, 3, 1};

static const tile2i CLOUD_DIRECTION[] = {{0, -6},
                                           {-2, -5},
                                           {-4, -4},
                                           {-5, -2},
                                           {-6, 0},
                                           {-5, -2},
                                           {-4, -4},
                                           {-2, -5},
                                           {0, -6},
                                           {-2, -5},
                                           {-4, -4},
                                           {-5, -2},
                                           {-6, 0},
                                           {-5, -2},
                                           {-4, -4},
                                           {-2, -5}};

static const int CLOUD_IMAGE_OFFSETS[] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 4, 4, 5, 6, 7};

void figure_create_explosion_cloud(int x, int y, int size) {
    int tile_offset = CLOUD_TILE_OFFSETS[size];
    int cc_offset = CLOUD_CC_OFFSETS[size];
    for (int i = 0; i < 16; i++) {
        figure* f = figure_create(FIGURE_EXPLOSION, x + tile_offset, y + tile_offset, DIR_0_TOP_RIGHT);
        if (f->id) {
            f->cc_coords.x += cc_offset;
            f->cc_coords.y += cc_offset;
            f->destination_tile.shift(CLOUD_DIRECTION[i].x, CLOUD_DIRECTION[i].y);
            //            f->destination_tile.x() += CLOUD_DIRECTION[i].x;
            //            f->destination_tile.y() += CLOUD_DIRECTION[i].y;
            f->set_cross_country_direction(f->cc_coords.x,
                                           f->cc_coords.y,
                                           15 * f->destination_tile.x() + cc_offset,
                                           15 * f->destination_tile.y() + cc_offset,
                                           0);
            f->speed_multiplier = CLOUD_SPEED[i];
        }
    }
}

void figure_create_missile(int building_id, int x, int y, int x_dst, int y_dst, e_figure_type type) {
    figure* f = figure_create(type, x, y, DIR_0_TOP_RIGHT);
    if (f->id) {
        f->missile_damage = (type == FIGURE_BOLT ? 60 : 10);
        f->set_home(building_id);
        f->destination_tile.set(x_dst, y_dst);
        //        f->destination_tile.x() = x_dst;
        //        f->destination_tile.y() = y_dst;
        f->set_cross_country_direction(f->cc_coords.x, f->cc_coords.y, 15 * x_dst, 15 * y_dst, 1);
    }
}
void figure::missile_fire_at(int target_id, e_figure_type missile_type) {
    figure* f = figure_get(target_id);
    figure_create_missile(id, tile.x(), tile.y(), f->tile.x(), f->tile.y(), missile_type);
}

bool figure::is_citizen() {
    if (action_state != FIGURE_ACTION_149_CORPSE) {
        if ((type && type != FIGURE_EXPLOSION && type != FIGURE_FORT_STANDARD && type != FIGURE_MAP_FLAG
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

    if (is_enemy())
        return id;

    if (type == FIGURE_INDIGENOUS_NATIVE && action_state == FIGURE_ACTION_159_NATIVE_ATTACKING)
        return id;

    if (/*type == FIGURE_WOLF*/ type == FIGURE_OSTRICH || type == FIGURE_SHEEP || type == FIGURE_ZEBRA)
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

void figure::explosion_cloud_action() {
    use_cross_country = true;
    progress_on_tile++;
    if (progress_on_tile > 44)
        poof();

    move_ticks_cross_country(speed_multiplier);
    if (progress_on_tile < 48) {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_EXPLOSION) + CLOUD_IMAGE_OFFSETS[progress_on_tile / 2];
    } else {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_EXPLOSION) + 7;
    }
}
void figure::arrow_action() {
    use_cross_country = true;
    progress_on_tile++;
    if (progress_on_tile > 120)
        poof();

    int should_die = move_ticks_cross_country(4);
    int target_id = get_non_citizen_on_tile(tile.grid_offset());
    if (target_id) {
        missile_hit_target(target_id, FIGURE_FORT_LEGIONARY);
        sound_effect_play(SOUND_EFFECT_ARROW_HIT);
    } else if (should_die)
        poof();
}
void figure::spear_action() {
    use_cross_country = true;
    progress_on_tile++;
    if (progress_on_tile > 120)
        poof();

    int should_die = move_ticks_cross_country(4);
    int target_id = get_citizen_on_tile(tile.grid_offset());
    if (target_id) {
        missile_hit_target(target_id, FIGURE_FORT_LEGIONARY);
        sound_effect_play(SOUND_EFFECT_JAVELIN);
    } else if (should_die)
        poof();

    int dir = (16 + direction - 2 * city_view_orientation()) % 16;
    sprite_image_id = image_id_from_group(GROUP_FIGURE_MISSILE) + dir;
}
void figure::javelin_action() {
    use_cross_country = true;
    progress_on_tile++;
    if (progress_on_tile > 120)
        poof();

    int should_die = move_ticks_cross_country(4);
    int target_id = get_non_citizen_on_tile(tile.grid_offset());
    if (target_id) {
        missile_hit_target(target_id, FIGURE_ENEMY_CAESAR_LEGIONARY);
        sound_effect_play(SOUND_EFFECT_JAVELIN);
    } else if (should_die)
        poof();
}
void figure::bolt_action() {
    use_cross_country = true;
    progress_on_tile++;
    if (progress_on_tile > 120)
        poof();

    int should_die = move_ticks_cross_country(4);
    int target_id = get_non_citizen_on_tile(tile.grid_offset());
    if (target_id) {
        figure* target = figure_get(target_id);
        const figure_properties* target_props = figure_properties_for_type(target->type);
        int max_damage = target_props->max_damage;
        int damage_inflicted
          = figure_properties_for_type(type)->missile_attack_value - target_props->missile_defense_value;
        if (damage_inflicted < 0)
            damage_inflicted = 0;

        int target_damage = damage_inflicted + target->damage;
        if (target_damage <= max_damage)
            target->damage = target_damage;
        else { // poof target
            target->damage = max_damage + 1;
            target->kill();
            target->wait_ticks = 0;
            target->play_die_sound();
            formation_update_morale_after_death(formation_get(target->formation_id));
        }
        sound_effect_play(SOUND_EFFECT_BALLISTA_HIT_PERSON);
        poof();
    } else if (should_die) {
        poof();
        sound_effect_play(SOUND_EFFECT_BALLISTA_HIT_GROUND);
    }
    int dir = (16 + direction - 2 * city_view_orientation()) % 16;
    sprite_image_id = image_id_from_group(GROUP_FIGURE_MISSILE) + 32 + dir;
}
