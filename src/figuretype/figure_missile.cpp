#include "figure_missile.h"

#include "grid/figure.h"
#include "sound/sound.h"
#include "graphics/animkeys.h"
#include "figure/properties.h"
#include "city/city_figures.h"

figures::model_t<figure_hunter_arrow> hunter_arrow_m;
figures::model_t<figure_arrow> arrow_m;
figures::model_t<figure_spear> spear_m;
figures::model_t<figure_javelin> javelin_m;
figures::model_t<figure_bolt> bolt_m;

void figure_missile::create(int building_id, tile2i src, tile2i dst, e_figure_type type) {
    figure* f = figure_create(type, src, DIR_0_TOP_RIGHT);
    if (f->id) {
        f->missile_damage = (type == FIGURE_BOLT ? 60 : 10);
        f->set_home(building_id);
        f->destination_tile = dst;
        f->set_cross_country_direction(f->cc_coords.x, f->cc_coords.y, 15 * dst.x(), 15 * dst.y(), 1);
    }
}

void figure_missile::figure_before_action() {

}

int figure_missile::get_non_citizen_on_tile() {
    return map_figure_foreach_until(tile(), TEST_SEARCH_NON_CITIZEN);
}

int figure_missile::get_citizen_on_tile() {
    return map_figure_foreach_until(tile(), TEST_SEARCH_CITIZEN);
}

void figure_missile::figure_action() {
    base.use_cross_country = true;
    base.progress_on_tile++;
    if (base.progress_on_tile > 120) {
        poof();
    }

    int should_die = base.move_ticks_cross_country(4);
    int target_id = get_non_citizen_on_tile();
    if (target_id) {
        missile_hit_target(target_id, FIGURE_STANDARD_BEARER);
        g_sound.play_effect(SOUND_EFFECT_ARROW_HIT);
    } else if (should_die) {
        poof();
    }
}

void figure_missile::missile_hit_target(int target_id, int legionary_type) {
    figure* target = figure_get(target_id);

    while (target) {
        if (target->is_dead()) {
            target = figure_get(target->next_figure);
            continue;
        }
        break;
    }

    const figure_properties *target_props = figure_properties_for_type(target->type);
    int max_damage = target_props->max_damage;
    int damage_inflicted = figure_properties_for_type(type())->missile_attack_value - target_props->missile_defense_value;

    formation *m = formation_get(target->formation_id);
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
    int missile_formation = figure_get(base.homeID())->formation_id;
    formation_record_missile_attack(m, missile_formation);
}

void figure_spear::figure_action() {
    base.use_cross_country = true;
    base.progress_on_tile++;
    if (base.progress_on_tile > 120) {
        poof();
    }

    int should_die = base.move_ticks_cross_country(4);
    int target_id = get_citizen_on_tile();
    if (target_id) {
        missile_hit_target(target_id, FIGURE_STANDARD_BEARER);
        g_sound.play_effect(SOUND_EFFECT_JAVELIN);
    } else if (should_die) {
        poof();
    }

    int dir = (16 + direction() - 2 * city_view_orientation()) % 16;
    base.sprite_image_id = anim(animkeys().walk).first_img() + dir;
}

void figure_javelin::figure_action() {
    base.use_cross_country = true;
    base.progress_on_tile++;
    if (base.progress_on_tile > 120) {
        poof();
    }

    int should_die = base.move_ticks_cross_country(4);
    int target_id = get_non_citizen_on_tile();
    if (target_id) {
        missile_hit_target(target_id, FIGURE_ENEMY_CAESAR_LEGIONARY);
        g_sound.play_effect(SOUND_EFFECT_JAVELIN);
    } else if (should_die) {
        poof();
    }
}

void figure_bolt::figure_action() {
    base.use_cross_country = true;
    base.progress_on_tile++;
    if (base.progress_on_tile > 120) {
        poof();
    }

    int should_die = base.move_ticks_cross_country(4);
    int target_id = get_non_citizen_on_tile();
    if (target_id) {
        figure* target = figure_get(target_id);
        const figure_properties* target_props = figure_properties_for_type(target->type);
        int max_damage = target_props->max_damage;
        int damage_inflicted = figure_properties_for_type(type())->missile_attack_value - target_props->missile_defense_value;
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

        g_sound.play_effect(SOUND_EFFECT_BALLISTA_HIT_PERSON);
        poof();

    } else if (should_die) {
        g_sound.play_effect(SOUND_EFFECT_BALLISTA_HIT_GROUND);
        poof();
    }
    int dir = (16 + direction() - 2 * city_view_orientation()) % 16;
    base.sprite_image_id = anim(animkeys().walk).first_img() + 32 + dir;
}