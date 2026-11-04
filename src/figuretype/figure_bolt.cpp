#include "figure_bolt.h"

#include "city/city_figures.h"
#include "figure/formation.h"
#include "figuretype/figure_javelin.h"
#include "graphics/animkeys.h"
#include "graphics/view/view.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_bolt);

void figure_bolt::figure_action() {
    const auto &r = missile_rules;
    base.use_cross_country = true;
    base.progress_on_tile++;
    if (base.progress_on_tile > r.flight_ticks) {
        poof();
        return;
    }

    const bool should_die = base.move_ticks_cross_country(r.speed);
    // OG bolt: map_figure_find_target (enemies/predators), not missile_hit_target.
    const figure_id target_id = javelin_find_attack_target(tile());
    if (!target_id) {
        if (should_die) {
            poof();
        }
        main_image_update();
        return;
    }

    figure *target = figure_get(target_id);
    formation *m = formation_get(target->formation_id);
    int bonus = 0;
    if (target->faction_id == 1 && m) {
        bonus = (m->experience + 10) / 20;
    }
    const int defense = missile_og_defense(target, m, target->missile_defense_value() + bonus);
    // OG: attack from figure_properties[FIGURE_BOLT].
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
        target->damage = (uint16_t)total;
    }

    // OG bolt does not set formation missile_attack_timeout (unlike arrow).
    poof();
    main_image_update();
}

void figure_bolt::main_image_update() {
    // OG missile_set_image(MISSILE_IMAGE_BOLT): offset 32, 16 directions.
    const auto &r = missile_rules;
    int dir = direction() - 2 * g_camera.orientation;
    if (dir < 0) {
        dir += r.image_directions;
    }
    dir %= r.image_directions;
    base.main_image_id = anim(animkeys().walk).first_img() + r.bolt_image_offset + dir;
}
