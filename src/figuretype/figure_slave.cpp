#include "figure_slave.h"

#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_slave);

void figure_slave::figure_action() {
    //    terrain_usage = TERRAIN_USAGE_ANY;
    //    use_cross_country = false;
    //    figure_image_increase_offset(12);
    // if (scenario_revolt_is_finished()) {
    //     // end of gladiator revolt: poof gladiators
    //     if (action_state != FIGURE_ACTION_149_CORPSE) {
    //         kill();
    //         wait_ticks = 0;
    //         direction = 0;
    //     }
    // }

    switch (base.action_state) {
    case ACTION_158_SLAVE_CREATED:
        base.animctx.frame = 0;
        base.wait_ticks++;
        if (base.wait_ticks > 10 + (base.id & 3)) {
            base.wait_ticks = 0;
            base.action_state = ACTION_159_SLAVE_ATTACKING;
            int x_tile, y_tile;
            int building_id = formation_rioter_get_target_building(&x_tile, &y_tile);
            if (building_id) {
                base.destination_tile.set(x_tile, y_tile);
                set_destination(building_id);
                route_remove();
            } else {
                poof();
            }
        }
        break;
    }
}

void figure_slave::update_animation() {
    int dir;
    if (base.action_state == ACTION_150_SLAVE_ATTACK || base.direction == DIR_FIGURE_ATTACK)
        dir = base.attack_direction;
    else if (base.direction < 8)
        dir = base.direction;
    else {
        dir = base.previous_tile_direction;
    }
    dir = base.figure_image_normalize_direction(dir);

    assert(false);
    if (base.action_state == ACTION_150_SLAVE_ATTACK || base.direction == DIR_FIGURE_ATTACK) {
        //sprite_image_id = image_id_from_group(GROUP_FIGURE_MUSICIAN) + dir + 104 + 8 * (anim.frame / 2);
    } else if (base.action_state == FIGURE_ACTION_149_CORPSE) {
        //sprite_image_id = image_id_from_group(GROUP_FIGURE_MUSICIAN) + 96 + figure_image_corpse_offset();
    } else {
        //sprite_image_id = image_id_from_group(GROUP_FIGURE_MUSICIAN) + dir + 8 * anim.frame;
    }
}

void figure_slave::before_poof() {
}
