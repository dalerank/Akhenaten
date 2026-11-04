#include "figure_missile.h"

#include "graphics/view/view.h"
#include "graphics/view/lookup.h"
#include "grid/figure.h"
#include "sound/sound.h"
#include "sound/effect.h"
#include "graphics/animkeys.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "figure/combat.h"
#include "figure/formation.h"
#include "figuretype/figure_enemy_archer.h"
#include "figuretype/figure_enemy_spearman.h"
#include "figuretype/figure_war_ship.h"
#include "game/game_events.h"
#include "js/js_game.h"

missile_rules_t ANK_VARIABLE(missile_rules);

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_hunter_arrow);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_arrow);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_spear);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_bolt);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_antelope_hunter_javelin);

figure_missile* figure_missile::create(figure_id fid, tile2i src, tile2i dst, e_figure_type type) {
    auto f = figure_create(type, src, DIR_0_TOP_RIGHT);
    auto missile = f->dcast<figure_missile>();
    if (missile) {
        missile->set_home(0);
        missile->base.missile_damage = (type == FIGURE_BOLT ? 60 : 10);
        missile->base.destination_tile = dst;
        missile->base.set_cross_country_direction(missile->base.cc_coords.x, missile->base.cc_coords.y, 15 * dst.x(), 15 * dst.y(), 1);
        // on_create ran inside figure_create before shooter_id existed — set then refresh.
        auto &d = missile->runtime_data();
        d.shooter_id = fid;
        // OG arrow uses figure_properties[FIGURE_ARROW].missile_attack, not the shooter's.
        int attack = figure_static_params::get(type).missile_attack_value;
        if (attack <= 0) {
            attack = 10;
        }
        if (type != FIGURE_ARROW) {
            if (figure *shooter = figure_get(fid)) {
                if (auto archer = smart_cast<figure_enemy_archer>(shooter)) {
                    attack = archer->missile_attack_value();
                } else if (auto spearman = smart_cast<figure_enemy_spearman>(shooter)) {
                    attack = spearman->missile_attack_value();
                } else if (auto warship = smart_cast<figure_warship>(shooter)) {
                    attack = warship->missile_attack_value();
                } else if (shooter->is_soldier()) {
                    int value = figure_static_params::get(shooter->type).missile_attack_value;
                    attack = value > 0 ? value : shooter->attack_value();
                }
            }
        }
        d.missile_attack_value = attack;
    }

    return missile;
}

void figure_missile::on_create() {
    // Default; create() refreshes from shooter after shooter_id is assigned.
    runtime_data().missile_attack_value = 10;
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
    float dy = src.y - dst.y;
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
        missile_hit_figure(target_id, FIGURE_INFANTRY);
        events::emit(event_sound_effect{ hit_sound_effect() });
        return;
    }

    // Check if missile has reached destination tile and is close to center
    // Center of tile in cross-country coordinates is around 7-8 (out of 0-14)
    bool at_destination_center = (base.tile == base.destination_tile) &&
                                  (base.cc_coords.x % 15 >= 6 && base.cc_coords.x % 15 <= 9) &&
                                  (base.cc_coords.y % 15 >= 6 && base.cc_coords.y % 15 <= 9);

    if (at_destination_center || should_die) {
        building* b = building_at(base.destination_tile);
        if (b->is_valid()) {
            missile_hit_building(b->id);
            events::emit(event_sound_effect{ hit_sound_effect() });
            return;
        }
    }

    if (should_die) {
        poof();
    }
}

void figure_missile::main_image_update() {
    set_image_direction(base.tile.to_view(), base.destination_tile.to_view());
    base.main_image_id = anim(animkeys().walk).first_img() + runtime_data().image_direction;
}

// OG missile_hit_target: first non-corpse figure on tile in the citizen/ship band.
static figure_id arrow_missile_hit_target(tile2i tile) {
    int fid = map_figure_id_get(tile);
    while (fid > 0) {
        figure *f = figure_get(fid);
        if (!f) {
            break;
        }
        const e_figure_type type = f->type;
        if (f->action_state != FIGURE_ACTION_149_CORPSE
            && type != FIGURE_NONE
            && type != FIGURE_EXPLOSION
            && type != FIGURE_STANDARD_BEARER
            && type != FIGURE_MAP_FLAG
            && type != FIGURE_FLOTSAM
            && (type < FIGURE_INDIGENOUS_NATIVE || type >= FIGURE_TRANSPORT_SHIP)
            && type <= FIGURE_WARSHIP) {
            return fid;
        }
        if (fid == f->next_figure) {
            break;
        }
        fid = f->next_figure;
    }
    return 0;
}

static int arrow_missile_defense(figure *target, formation *legion, int defense) {
    const auto &r = missile_rules;
    if (defense >= r.max_defense) {
        defense = r.max_defense;
    }
    if (legion && legion->is_halted) {
        const e_figure_type ltype = legion->figure_type;
        if (ltype >= FIGURE_ARCHER && ltype <= FIGURE_INFANTRY) {
            if (!attack_is_same_direction(target->attack_direction, legion->direction)) {
                defense -= r.facing_away_penalty;
            } else if (legion->layout >= FORMATION_SINGLE_LINE_1 && legion->layout <= FORMATION_SINGLE_LINE_2) {
                defense += r.single_line_bonus;
            } else if (legion->layout == FORMATION_MOP_UP) {
                defense -= r.mop_up_penalty;
            }
        } else if (ltype == FIGURE_FCHARIOTEER) {
            if (!attack_is_same_direction(target->attack_direction, legion->direction)) {
                defense -= r.facing_away_penalty;
            } else if (legion->layout == FORMATION_MOP_UP) {
                defense -= r.mop_up_penalty;
            }
        }
    }
    if (defense < 0) {
        defense = 0;
    }
    if (defense > r.max_defense) {
        defense = r.max_defense;
    }
    return defense;
}

static int arrow_missile_damage(int attack, int defense) {
    if (attack == 0) {
        return 0;
    }
    const auto &r = missile_rules;
    const int damage = ((r.damage_base - defense) / r.max_defense) * attack;
    return damage < 0 ? 0 : damage;
}

void figure_arrow::figure_action() {
    base.use_cross_country = true;
    base.progress_on_tile++;
    if (base.progress_on_tile > missile_rules.flight_ticks) {
        poof();
        return;
    }

    const bool should_die = base.move_ticks_cross_country(missile_rules.speed);
    const figure_id target_id = arrow_missile_hit_target(tile());
    if (!target_id) {
        if (should_die) {
            poof();
        }
        return;
    }

    figure *target = figure_get(target_id);
    formation *m = formation_get(target->formation_id);
    int bonus = 0;
    if (target->faction_id == 1 && m) {
        bonus = (m->experience + 10) / 20;
    }
    const int defense = arrow_missile_defense(target, m, target->missile_defense_value() + bonus);
    // OG: attack from figure_properties[FIGURE_ARROW], not shooter.
    int attack = params().missile_attack_value;
    if (attack <= 0) {
        attack = runtime_data().missile_attack_value;
    }
    const int damage = arrow_missile_damage(attack, defense);
    const int max_damage = target->max_damage();
    const int total = target->damage + damage;
    if (total > max_damage) {
        target->damage = max_damage + 1;
        target->kill();
        target->wait_ticks = 0;
        target->play_die_sound();
        if (m) {
            formation_update_morale_after_death(m);
        }
    } else {
        target->damage = (uint8_t)total;
    }

    if (m && target->formation_id) {
        m->missile_attack_timeout = missile_rules.attack_timeout;
        figure *sh = shooter();
        m->missile_attack_formation_id = sh ? sh->formation_id : 0;
    }

    events::emit(event_sound_effect{ hit_sound_effect() });
    poof();
}

void figure_arrow::main_image_update() {
    // OG missile_set_image: arrow_image_offset + 16-dir frame.
    const auto &r = missile_rules;
    int dir = direction() - 2 * g_camera.orientation;
    if (dir < 0) {
        dir += r.image_directions;
    }
    dir %= r.image_directions;
    base.main_image_id = anim(animkeys().walk).first_img() + r.arrow_image_offset + dir;
}

void figure_missile::cart_image_update() {
    // nothing
}

void figure_missile::missile_hit_building(building_id target_id) {
    building *b = building_get(target_id);

    if (!b->is_valid()) {
        return;
    }

    b->force_damage(e_damage_enemy, runtime_data().missile_attack_value);

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

    auto &d = runtime_data();
    int target_max_damage = target->max_damage();
    int damage_inflicted = d.missile_attack_value - target->missile_defense_value();

    formation *m = formation_get(target->formation_id);
    if (damage_inflicted < 0) {
        damage_inflicted = 0;
    }

    if (target->type == legionary_type && m->is_halted && m->layout == FORMATION_COLUMN) {
        damage_inflicted = 1;
    }

    target->apply_damage(damage_inflicted, d.shooter_id);
    if (target->damage >= target_max_damage) {
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
        missile_hit_figure(target_id, FIGURE_INFANTRY);
        events::emit(event_sound_effect{ SOUND_EFFECT_JAVELIN });
    } else if (should_die) {
        poof();
    }

    int dir = (16 + direction() - 2 * g_camera.orientation) % 16;
    base.main_image_id = anim(animkeys().walk).first_img() + dir;
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
        if (target_damage < target_max_damage) {
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

    int dir = (16 + direction() - 2 * g_camera.orientation) % 16;
    base.main_image_id = anim(animkeys().walk).first_img() + 32 + dir;
}

