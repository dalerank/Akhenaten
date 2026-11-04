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
#include "figuretype/figure_hunter.h"
#include "figuretype/animal_ostrich.h"
#include "figuretype/figure_birds.h"
#include "figuretype/figure_antelope.h"
#include "game/game_events.h"
#include "js/js_game.h"
#include "scenario/scenario.h"

missile_rules_t ANK_VARIABLE(missile_rules);
hunter_spear_rules_t ANK_VARIABLE(hunter_spear_rules);

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_hunter_spear);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_arrow);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_spear);
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
        // OG arrow/bolt/spear: figure_properties[type].missile_attack (spear ships use shooter type at hit).
        int attack = figure_static_params::get(type).missile_attack_value;
        if (attack <= 0) {
            attack = 10;
        }
        if (type != FIGURE_ARROW && type != FIGURE_BOLT && type != FIGURE_SPEAR) {
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

int missile_og_defense(figure *target, formation *legion, int defense) {
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

int missile_og_damage(int attack, int defense) {
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
    const int defense = missile_og_defense(target, m, target->missile_defense_value() + bonus);
    // OG: attack from figure_properties[FIGURE_ARROW], not shooter.
    int attack = params().missile_attack_value;
    if (attack <= 0) {
        attack = runtime_data().missile_attack_value;
    }
    const int damage = missile_og_damage(attack, defense);
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

static bool spear_is_ship(e_figure_type type) {
    return type == FIGURE_WARSHIP || type == FIGURE_TRANSPORT_SHIP || type == FIGURE_FISHING_BOAT;
}

static void spear_hit(figure_spear *spear, figure_id target_id, figure_id shooter_id, int shooter_formation) {
    const auto &r = missile_rules;
    figure *target = figure_get(target_id);
    if (!target) {
        spear->poof();
        return;
    }

    const int formation_id = target->formation_id;
    formation *m = formation_get(formation_id);
    int bonus = 0;
    const e_figure_type type = target->type;
    const bool is_ship = spear_is_ship(type);

    if (target->faction_id == 1 && type == FIGURE_WARSHIP
        && target->action_state == ACTION_203_WARSHIP_MOORED) {
        bonus = r.docked_warship_bonus;
    } else if (target->faction_id == 1 && type >= FIGURE_ARCHER && type <= FIGURE_FCHARIOTEER) {
        bonus = m ? (m->experience + 10) / 20 : 0;
    }

    int defense = bonus + target->missile_defense_value();
    if (defense >= r.max_defense) {
        defense = r.max_defense;
    }

    e_figure_type attack_type;
    if (is_ship) {
        figure *sh = figure_get(shooter_id);
        if (!sh || sh->state != FIGURE_STATE_ALIVE) {
            spear->poof();
            return;
        }
        attack_type = sh->type;
    } else {
        attack_type = FIGURE_SPEAR;
    }

    int attack = figure_static_params::get(attack_type).missile_attack_value;
    if (attack <= 0) {
        attack = spear->runtime_data().missile_attack_value;
    }
    defense = missile_og_defense(target, m, defense);
    const int damage = missile_og_damage(attack, defense);

    if (is_ship) {
        const int max_hp = target->max_damage();
        const int remaining = max_hp - (int)target->damage - damage;
        if (remaining <= 0) {
            target->damage = max_hp + 1;
            target->kill();
            target->wait_ticks = 0;
            target->play_die_sound();
        } else {
            target->damage = (uint16_t)(max_hp - remaining);
        }
    } else {
        const int max_damage = target->max_damage();
        const int total = target->damage + damage;
        if (total > max_damage) {
            target->damage = max_damage + 1;
            target->kill();
            target->wait_ticks = 0;
            target->play_die_sound();
            if (m && formation_id) {
                formation_update_morale_after_death(m);
            }
        } else {
            target->damage = (uint16_t)total;
        }
        if (m && formation_id) {
            m->missile_attack_timeout = r.attack_timeout;
            m->missile_attack_formation_id = shooter_formation;
        }
    }

    events::emit(event_sound_effect{ spear->hit_sound_effect() });
    spear->poof();
}

void figure_spear::figure_action() {
    const auto &r = missile_rules;
    base.use_cross_country = true;
    base.progress_on_tile++;
    if (base.progress_on_tile > r.flight_ticks) {
        poof();
        main_image_update();
        return;
    }

    const bool should_die = base.move_ticks_cross_country(r.speed);
    const figure_id target_id = arrow_missile_hit_target(tile());
    figure *sh = shooter();
    const int shooter_formation = sh ? sh->formation_id : 0;

    if (target_id) {
        spear_hit(this, target_id, runtime_data().shooter_id, shooter_formation);
    } else if (should_die) {
        poof();
    }

    main_image_update();
}

void figure_spear::main_image_update() {
    // OG spear_set_image: 32 dirs, orientation*4; enemy-archer sprite path is dead (spear type ≠ archer).
    const auto &r = missile_rules;
    int dir = direction() - r.spear_orientation_mult * g_camera.orientation;
    if (dir < 0) {
        dir += r.spear_image_directions;
    }
    dir %= r.spear_image_directions;
    base.main_image_id = anim(animkeys().walk).first_img() + dir;

    const int shadow = anim("shadow").first_img();
    if (shadow) {
        base.cart_image_id = shadow + dir;
    }
}

static figure_id hunter_spear_prey_on_tile(tile2i tile) {
    int fid = map_figure_id_get(tile);
    while (fid > 0) {
        figure *f = figure_get(fid);
        if (!f) {
            break;
        }
        const e_figure_type type = f->type;
        if ((type == FIGURE_ANTELOPE || type == FIGURE_BIRDS || type == FIGURE_OSTRICH)
            && f->action_state != FIGURE_ACTION_149_CORPSE
            && !figure_hunter::prey_is_downed(f)) {
            return fid;
        }
        if (fid == f->next_figure) {
            break;
        }
        fid = f->next_figure;
    }
    return 0;
}

static void hunter_spear_mark_hunted(figure *prey) {
    switch (prey->type) {
    case FIGURE_OSTRICH:
        prey->advance_action(ACTION_12_OSTRICH_HUNTED);
        break;
    case FIGURE_BIRDS:
        prey->advance_action(ACTION_12_BIRDS_HUNTED);
        break;
    case FIGURE_ANTELOPE:
        prey->advance_action(ACTION_12_ANTELOPE_HUNTED);
        break;
    default:
        break;
    }
    prey->wait_ticks = 0;
}

void hunter_spear_figure_action(figure_missile *missile) {
    const auto &r = hunter_spear_rules;
    auto &base = missile->base;
    base.use_cross_country = true;
    base.progress_on_tile++;
    if (base.progress_on_tile > r.flight_ticks) {
        missile->poof();
        missile->main_image_update();
        return;
    }

    const bool landed = base.move_ticks_cross_country(r.speed);
    const figure_id prey_id = hunter_spear_prey_on_tile(missile->tile());
    figure *hunter = missile->shooter();

    if (prey_id) {
        figure *prey = figure_get(prey_id);
        hunter_spear_mark_hunted(prey);
        if (auto *h = hunter ? hunter->dcast_hunter() : nullptr) {
            h->on_spear_hit_prey(prey);
        }
        events::emit(event_sound_effect{ missile->hit_sound_effect() });
        missile->poof();
        missile->main_image_update();
        return;
    }

    if (landed) {
        if (auto *h = hunter ? hunter->dcast_hunter() : nullptr) {
            h->on_spear_miss();
        }
        missile->poof();
    }

    missile->main_image_update();
}

void hunter_spear_main_image_update(figure_missile *missile) {
    const auto &r = hunter_spear_rules;
    int dir = missile->direction() - r.orientation_mult * g_camera.orientation;
    if (dir < 0) {
        dir += r.image_directions;
    }
    dir %= r.image_directions;
    missile->base.main_image_id = missile->anim(animkeys().walk).first_img() + dir;
    const int shadow = missile->anim("shadow").first_img();
    if (shadow) {
        missile->base.cart_image_id = shadow + dir;
    }
}

void figure_hunter_spear::figure_action() {
    hunter_spear_figure_action(this);
}

void figure_hunter_spear::main_image_update() {
    // OG: central climate uses frame-only stick (no 32-dir shadow); others SpeAmbient spear+shadow.
    if (g_scenario.climate == CLIMATE_CENTRAL) {
        const int central = anim("central").first_img();
        if (central) {
            base.main_image_id = central + (base.progress_on_tile % 5);
            base.cart_image_id = 0;
            return;
        }
    }
    hunter_spear_main_image_update(this);
}

void figure_antelope_hunter_javelin::figure_action() {
    hunter_spear_figure_action(this);
}

void figure_antelope_hunter_javelin::main_image_update() {
    hunter_spear_main_image_update(this);
}


