#include "figure_missile.h"

#include "grid/figure.h"
#include "sound/sound.h"
#include "graphics/animkeys.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "figuretype/figure_enemy_archer.h"
#include "game/game_events.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_hunter_arrow);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_arrow);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_spear);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_javelin);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_bolt);

figure_missile* figure_missile::create(figure_id fid, tile2i src, tile2i dst, e_figure_type type) {
    auto f = figure_create(type, src, DIR_0_TOP_RIGHT);
    auto missile = f->dcast<figure_missile>();
    if (missile) {
        missile->set_home(0);
        missile->base.missile_damage = (type == FIGURE_BOLT ? 60 : 10);
        missile->base.destination_tile = dst;
        missile->base.set_cross_country_direction(missile->base.cc_coords.x, missile->base.cc_coords.y, 15 * dst.x(), 15 * dst.y(), 1);
        missile->runtime_data().shooter_id = fid;
    }

    return missile;
}

void figure_missile::on_create() {
    auto &d = runtime_data();
    auto shooter = figure_get<figure_enemy_archer>(d.shooter_id);
    d.missile_attack_value = (shooter ? shooter->missile_attack_value() : 10);
}

void figure_missile::figure_before_action() {

}

figure_id figure_missile::get_non_citizen_on_tile() {
    return map_figure_foreach_until(tile(), TEST_SEARCH_NON_CITIZEN);
}

figure_id figure_missile::get_citizen_on_tile() {
    return map_figure_foreach_until(tile(), TEST_SEARCH_CITIZEN);
}

void figure_missile::set_image_direction(vec2i src, vec2i dst) {
    float dx = dst.x - src.x;
    float dy = dst.y - src.y;
    float angle_rad = atan2(dy, dx);
    float angle_deg = angle_rad * 180.0f / M_PI;
    if (angle_deg < 0) {
        angle_deg += 360.0f;
    }
    angle_deg = angle_deg - 22.5f - 90.f;
    if (angle_deg < 0) {
        angle_deg += 360.0f;
    }
    int index = (int)(angle_deg / 11.25f + 0.5f) % 32;
    runtime_data().image_direction = (32 - index) % 32;
}

figure *figure_missile::shooter() const { 
    return figure_get(runtime_data().shooter_id); 
}

void figure_missile::figure_action() {
    base.use_cross_country = true;
    base.progress_on_tile++;
    if (base.progress_on_tile > 120) {
        poof();
    }

    bool should_die = base.move_ticks_cross_country(4);
    figure_id target_id = get_non_citizen_on_tile();
    if (target_id && target_id != runtime_data().shooter_id) {
        missile_hit_figure(target_id, FIGURE_STANDARD_BEARER);
        events::emit(event_sound_effect{ SOUND_EFFECT_ARROW_HIT });
        return;
    } 

    building* b = building_at(tile());
    if (b->is_valid()) {
        missile_hit_building(b->id);
        events::emit(event_sound_effect{ SOUND_EFFECT_ARROW_HIT });
        return;
    }

    if (should_die) {
        poof();
    }
}

void figure_missile::main_image_update() {
    set_image_direction(base.tile.to_view(), base.destination_tile.to_view());
    base.main_image_id = anim(animkeys().walk).first_img() + runtime_data().image_direction;
}

void figure_missile::cart_image_update() {
    // nothing
}

void figure_missile::missile_hit_building(building_id target_id) {
    building *b = building_get(target_id);

    if (!b->is_valid()) {
        return;
    }

    b->force_damage(false, runtime_data().missile_attack_value);

    poof();
}

void figure_missile::missile_hit_figure(figure_id target_id, int legionary_type) {
    figure* target = figure_get(target_id);

    while (target->id) {
        if (target->is_dead()) {
            target = figure_get(target->next_figure);
            continue;
        }
        break;
    }

    int target_max_damage = target->max_damage();
    int damage_inflicted = runtime_data().missile_attack_value - target->missile_defense_value();

    formation *m = formation_get(target->formation_id);
    if (damage_inflicted < 0) {
        damage_inflicted = 0;
    }

    if (target->type == legionary_type && m->is_halted && m->layout == FORMATION_COLUMN) {
        damage_inflicted = 1;
    }

    int target_damage = damage_inflicted + target->damage;
    target->apply_damage(damage_inflicted);
    if (target->damage > target_max_damage) {
        target->damage = target_max_damage + 1;
        target->kill();
        target->wait_ticks = 0;
        target->play_die_sound();
        formation_update_morale_after_death(m);
    }

    poof();

    int missile_formation = shooter()->formation_id;
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
        missile_hit_figure(target_id, FIGURE_STANDARD_BEARER);
        events::emit(event_sound_effect{ SOUND_EFFECT_JAVELIN });
    } else if (should_die) {
        poof();
    }

    int dir = (16 + direction() - 2 * city_view_orientation()) % 16;
    base.main_image_id = anim(animkeys().walk).first_img() + dir;
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
        missile_hit_figure(target_id, FIGURE_ENEMY_KINGDOME_INFANTRY);
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
        int target_max_damage = target->max_damage();
        int damage_inflicted = runtime_data().missile_attack_value - target->missile_defense_value();
        if (damage_inflicted < 0) {
            damage_inflicted = 0;
        }

        int target_damage = damage_inflicted + target->damage;
        if (target_damage <= target_max_damage) {
            target->damage = target_damage;
        } else { // poof target
            target->damage = target_max_damage + 1;
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
    base.main_image_id = anim(animkeys().walk).first_img() + 32 + dir;
}