#include "figure_javelin.h"

#include "city/city_figures.h"
#include "figure/formation.h"
#include "figuretype/figure_native.h"
#include "graphics/animkeys.h"
#include "graphics/view/view.h"
#include "grid/figure.h"
#include "js/js_game.h"

javelin_rules_t ANK_VARIABLE(javelin_rules);

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_javelin);

// OG map_figure_find_target / is_attack_target (military.c figure_javelin_action).
static bool javelin_is_attack_target(const figure *f) {
    // Poof sets FIGURE_STATE_DEAD before the figure leaves the tile map.
    if (!f || !f->is_alive() || f->action_state == FIGURE_ACTION_149_CORPSE) {
        return false;
    }
    if (f->is_enemy()) {
        return true;
    }
    switch (f->type) {
    case FIGURE_INDIGENOUS_NATIVE:
        return f->action_state == ACTION_11_NATIVE_ATTACKING;
    case FIGURE_CROCODILE:
    case FIGURE_HYENA:
    case FIGURE_HIPPO:
    case FIGURE_ASP:
    case FIGURE_LION:
    case FIGURE_SCORPION:
    case FIGURE_MUMMY:
        return true;
    default:
        return false;
    }
}

figure_id javelin_find_attack_target(tile2i tile) {
    int fid = map_figure_id_get(tile);
    while (fid > 0) {
        figure *f = figure_get(fid);
        if (!f) {
            break;
        }
        if (javelin_is_attack_target(f)) {
            return fid;
        }
        if (fid == f->next_figure) {
            break;
        }
        fid = f->next_figure;
    }
    return 0;
}

static bool javelin_is_herd_animal(e_figure_type type) {
    return type >= FIGURE_BIRDS && type <= FIGURE_ANTELOPE;
}

static bool javelin_is_predator_animal(e_figure_type type) {
    switch (type) {
    case FIGURE_CROCODILE:
    case FIGURE_HYENA:
    case FIGURE_HIPPO:
    case FIGURE_ASP:
    case FIGURE_LION:
    case FIGURE_SCORPION:
        return true;
    default:
        return false;
    }
}

static int javelin_missile_damage(int attack, int defense) {
    if (attack <= 0) {
        return 0;
    }
    const auto &r = javelin_rules;
    int damage = ((r.damage_base - defense) * attack) / r.damage_base;
    return damage < 0 ? 0 : damage;
}

void figure_javelin::figure_action() {
    const auto &r = javelin_rules;
    base.use_cross_country = true;
    base.progress_on_tile++;
    if (base.progress_on_tile > r.flight_ticks) {
        poof();
        return;
    }

    const bool should_die = base.move_ticks_cross_country(r.speed);
    const figure_id target_id = javelin_find_attack_target(tile());
    figure *sh = shooter();
    if (!sh) {
        if (should_die) {
            poof();
        }
        main_image_update();
        return;
    }

    const int shooter_formation = sh->formation_id;
    formation *shooter_legion = formation_get(shooter_formation);

    if (target_id) {
        figure *target = figure_get(target_id);
        const int target_formation = target->formation_id;

        e_figure_type attack_type;
        if (sh->type == FIGURE_BALLISTA) {
            attack_type = FIGURE_BALLISTA;
        } else if (sh->type == FIGURE_WARSHIP) {
            if (sh->state != FIGURE_STATE_ALIVE) {
                poof();
                main_image_update();
                return;
            }
            attack_type = FIGURE_WARSHIP;
        } else {
            attack_type = shooter_legion ? shooter_legion->figure_type : FIGURE_NONE;
        }

        int defense = target->missile_defense_value();
        if (defense >= r.max_defense) {
            defense = r.max_defense;
        }
        const int attack = figure_static_params::get(attack_type).missile_attack_value;
        const int damage = javelin_missile_damage(attack, defense);
        const int max_damage = target->max_damage();
        const int total = target->damage + damage;

        if (total > max_damage) {
            target->damage = max_damage + 1;
            target->kill();
            target->wait_ticks = 0;
            target->play_die_sound();
            if (target_formation) {
                formation_update_morale_after_death(formation_get(target_formation));
            }
            if (!javelin_is_predator_animal(target->type)
                && !javelin_is_herd_animal(target->type)
                && target->type != FIGURE_ROBBER
                && sh->faction_id == 1
                && shooter_legion) {
                int experience = shooter_legion->experience + 1;
                if (experience >= r.max_experience) {
                    experience = r.max_experience;
                }
                shooter_legion->experience = (uint16_t)experience;
            }
        } else {
            target->damage = (uint16_t)total;
        }

        if (target_formation) {
            formation *hit = formation_get(target_formation);
            hit->missile_attack_timeout = r.attack_timeout;
            hit->missile_attack_formation_id = shooter_formation;
        }
        poof();
    } else if (should_die) {
        poof();
    }

    main_image_update();
}

void figure_javelin::main_image_update() {
    const auto &r = javelin_rules;
    int dir = direction() - r.orientation_mult * g_camera.orientation;
    if (dir < 0) {
        dir += r.image_directions;
    }
    dir %= r.image_directions;

    figure *sh = shooter();
    int first;
    if (sh && (sh->type == FIGURE_TOWER_SENTRY || sh->type == FIGURE_BALLISTA)) {
        first = anim("tower").first_img();
        if (!first) {
            first = figure_static_params::get(FIGURE_SPEAR).first_img(animkeys().walk);
        }
    } else {
        first = anim(animkeys().walk).first_img();
    }
    base.main_image_id = first + dir;

    const int shadow = anim("shadow").first_img();
    if (shadow) {
        base.cart_image_id = shadow + dir;
    }
}

void figure_javelin::cart_image_update() {
}
