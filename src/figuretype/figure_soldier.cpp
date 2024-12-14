#include "figure_soldier.h"

#include "city/city.h"
#include "city/map.h"
#include "core/calc.h"
#include "figure/combat.h"
#include "figure/formation.h"
#include "figure/formation_layout.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/properties.h"
#include "figure/route.h"
#include "figuretype/figure_missile.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/point.h"
#include "sound/sound.h"

#include "js/js_game.h"

static const vec2i ALTERNATIVE_POINTS[] = {
  {-1, -6}, {0, -1}, {1, -1},  {1, 0},   {1, 1},   {0, 1},   {-1, 1},  {-1, 0},  {-1, -1}, {0, -2},  {1, -2},  {2, -2},
  {2, -1},  {2, 0},  {2, 1},   {2, 2},   {1, 2},   {0, 2},   {-1, 2},  {-2, 2},  {-2, 1},  {-2, 0},  {-2, -1}, {-2, -2},
  {-1, -2}, {0, -3}, {1, -3},  {2, -3},  {3, -3},  {3, -2},  {3, -1},  {3, 0},   {3, 1},   {3, 2},   {3, 3},   {2, 3},
  {1, 3},   {0, 3},  {-1, 3},  {-2, 3},  {-3, 3},  {-3, 2},  {-3, 1},  {-3, 0},  {-3, -1}, {-3, -2}, {-3, -3}, {-2, -3},
  {-1, -3}, {0, -4}, {1, -4},  {2, -4},  {3, -4},  {4, -4},  {4, -3},  {4, -2},  {4, -1},  {4, 0},   {4, 1},   {4, 2},
  {4, 3},   {4, 4},  {3, 4},   {2, 4},   {1, 4},   {0, 4},   {-1, 4},  {-2, 4},  {-3, 4},  {-4, 4},  {-4, 3},  {-4, 2},
  {-4, 1},  {-4, 0}, {-4, -1}, {-4, -2}, {-4, -3}, {-4, -4}, {-3, -4}, {-2, -4}, {-1, -4}, {0, -5},  {1, -5},  {2, -5},
  {3, -5},  {4, -5}, {5, -5},  {5, -4},  {5, -3},  {5, -2},  {5, -1},  {5, 0},   {5, 1},   {5, 2},   {5, 3},   {5, 4},
  {5, 5},   {4, 5},  {3, 5},   {2, 5},   {1, 5},   {0, 5},   {-1, 5},  {-2, 5},  {-3, 5},  {-4, 5},  {-5, 5},  {-5, 4},
  {-5, 3},  {-5, 2}, {-5, 1},  {-5, 0},  {-5, -1}, {-5, -2}, {-5, -3}, {-5, -4}, {-5, -5}, {-4, -5}, {-3, -5}, {-2, -5},
  {-1, -5}, {0, -6}, {1, -6},  {2, -6},  {3, -6},  {4, -6},  {5, -6},  {6, -6},  {6, -5},  {6, -4},  {6, -3},  {6, -2},
  {6, -1},  {6, 0},  {6, 1},   {6, 2},   {6, 3},   {6, 4},   {6, 5},   {6, 6},   {5, 6},   {4, 6},   {3, 6},   {2, 6},
  {1, 6},   {0, 6},  {-1, 6},  {-2, 6},  {-3, 6},  {-4, 6},  {-5, 6},  {-6, 6},  {-6, 5},  {-6, 4},  {-6, 3},  {-6, 2},
  {-6, 1},  {-6, 0}, {-6, -1}, {-6, -2}, {-6, -3}, {-6, -4}, {-6, -5}, {-6, -6}, {-5, -6}, {-4, -6}, {-3, -6}, {-2, -6},
  {-1, -6},
};

figures::model_t<figure_standard_bearer> standard_bearer_m;
figures::model_t<figure_soldier_infantry> soldier_infantry_m;
figures::model_t<figure_soldier_archer> soldier_archer_m;
figures::model_t<figure_soldier_charioteer> soldier_charioterr_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_soldiers);
void config_load_figure_soldiers() {
    standard_bearer_m.load();
    soldier_infantry_m.load();
    soldier_archer_m.load();
    soldier_charioterr_m.load();
}

void figure_standard_bearer::figure_action() {
    const formation* m = formation_get(base.formation_id);

    //    terrain_usage = TERRAIN_USAGE_ANY;
    //    figure_image_increase_offset(16);
    base.map_figure_remove();
    if (m->is_at_fort) {
        base.tile = m->tile;
    } else {
        base.tile = m->standard_tile;
    }
    //    tile.grid_offset() = MAP_OFFSET(tile.x(), tile.y());
    base.cc_coords.x = 15 * tilex() + 7;
    base.cc_coords.y = 15 * tiley() + 7;
    base.map_figure_add();

    base.sprite_image_id = image_id_from_group(GROUP_FIGURE_FORT_STANDARD_POLE) + 20 - m->morale / 5;
    if (m->figure_type == FIGURE_INFANTRY) {
        if (m->is_halted)
            base.cart_image_id = image_id_from_group(GROUP_FIGURE_FORT_FLAGS) + 8;
        else {
            base.cart_image_id = image_id_from_group(GROUP_FIGURE_FORT_FLAGS) + base.anim.frame / 2;
        }
    } else if (m->figure_type == FIGURE_FCHARIOTEER) {
        if (m->is_halted)
            base.cart_image_id = image_id_from_group(GROUP_FIGURE_FORT_FLAGS) + 26;
        else {
            base.cart_image_id = image_id_from_group(GROUP_FIGURE_FORT_FLAGS) + 18 + base.anim.frame / 2;
        }
    } else {
        if (m->is_halted)
            base.cart_image_id = image_id_from_group(GROUP_FIGURE_FORT_FLAGS) + 17;
        else {
            base.cart_image_id = image_id_from_group(GROUP_FIGURE_FORT_FLAGS) + 9 + base.anim.frame / 2;
        }
    }
}

void figure::javelin_launch_missile() {
    tile2i tile = {-1, -1};
    wait_ticks_missile++;
    if (wait_ticks_missile > figure_properties_for_type(type)->missile_delay) {
        wait_ticks_missile = 0;
        if (figure_combat_get_missile_target_for_soldier(this, 10, &tile)) {
            attack_image_offset = 1;
            direction = calc_missile_shooter_direction(tile, tile);
        } else
            attack_image_offset = 0;
    }
    if (attack_image_offset) {
        if (attack_image_offset == 1) {
            if (tile.x() == -1 || tile.y() == -1) {
                map_point_get_last_result(tile);
            }

            figure* f = figure_get(target_figure_id);
            figure_missile::create(home_building_id, tile, f->tile, FIGURE_JAVELIN);
            formation_record_missile_fired(formation_get(formation_id));
        }
        attack_image_offset++;
        if (attack_image_offset > 100)
            attack_image_offset = 0;
    }
}
void figure::legionary_attack_adjacent_enemy() {
    for (int i = 0; i < 8 && action_state != FIGURE_ACTION_150_ATTACK; i++)
        figure_combat_attack_figure_at(tile.grid_offset() + map_grid_direction_delta(i));
}

int figure::find_mop_up_target() {
    int target_id = target_figure_id;
    if (figure_get(target_id)->is_dead()) {
        target_figure_id = 0;
        target_id = 0;
    }
    if (target_id <= 0) {
        target_id = figure_combat_get_target_for_soldier(tile, 20);
        if (target_id) {
            figure* target = figure_get(target_id);
            destination_tile = target->tile;
            target_figure_id = target_id;
            target->targeted_by_figure_id = id;
            //target_figure_created_sequence = target->created_sequence;
        } else {
            action_state = FIGURE_ACTION_84_SOLDIER_AT_STANDARD;
            anim.frame = 0;
        }
        route_remove();
    }
    return target_id;
}

void figure_soldier::update_image(const formation* m, int &dir) {
    if (action_state() == FIGURE_ACTION_150_ATTACK) {
        dir = base.attack_direction;
    } else if (m->missile_fired) {
        dir = direction();
    } else if (action_state() == FIGURE_ACTION_84_SOLDIER_AT_STANDARD) {
        dir = m->direction;
    } else if (direction() < 8) {
        dir = direction();
    } else {
        dir = base.previous_tile_direction;
    }

    dir = figure_image_normalize_direction(dir);
}

bool figure_soldier::play_die_sound() {
    if (g_city.figures.soldiers == 1) {
        g_sound.speech_play_file("Wavs/barbarian_war_cry.wav", 255);
    }

    return true;
}

void figure_soldier::figure_action() {
    formation* m = formation_get(base.formation_id);
    g_city.figures_add_soldier();
    //    terrain_usage = TERRAIN_USAGE_ANY;
    //    figure_image_increase_offset(12);
    //    cart_image_id = 0;
    if (m->in_use != 1) {
        base.kill();
    }

    int speed_factor;
    if (type() == FIGURE_INFANTRY) {
        speed_factor = 1;
    } else if (type() == FIGURE_ARCHER) {
        speed_factor = 1;
    } else {
        speed_factor = 1;
    }
    int layout = m->layout;
    if (base.formation_at_rest || action_state() == FIGURE_ACTION_81_SOLDIER_GOING_TO_FORT)
        layout = FORMATION_AT_REST;

    base.formation_position_x.soldier = m->tile.x() + formation_layout_position_x(layout, base.index_in_formation);
    base.formation_position_y.soldier = m->tile.y() + formation_layout_position_y(layout, base.index_in_formation);

    switch (action_state()) {
    case FIGURE_ACTION_80_SOLDIER_AT_REST:
        base.map_figure_update();
        wait_ticks = 0;
        base.formation_at_rest = 1;
        base.anim.frame = 0;
        if (tilex() != base.formation_position_x.soldier || tiley() != base.formation_position_y.soldier)
            base.action_state = FIGURE_ACTION_81_SOLDIER_GOING_TO_FORT;
        break;

    case FIGURE_ACTION_81_SOLDIER_GOING_TO_FORT:
    case FIGURE_ACTION_148_FLEEING:
        wait_ticks = 0;
        base.formation_at_rest = 1;
        destination_tile.set(base.formation_position_x.soldier, base.formation_position_y.soldier);
        base.move_ticks(speed_factor);
        if (direction() == DIR_FIGURE_NONE)
            base.action_state = FIGURE_ACTION_80_SOLDIER_AT_REST;
        else if (direction() == DIR_FIGURE_REROUTE)
            route_remove();
        else if (direction() == DIR_FIGURE_CAN_NOT_REACH)
            poof();
        break;

    case FIGURE_ACTION_82_SOLDIER_RETURNING_TO_BARRACKS:
        base.formation_at_rest = 1;
        destination_tile = base.source_tile;
        //            destination_tile.x() = source_tile.x();
        //            destination_tile.y() = source_tile.y();
        base.move_ticks(speed_factor);
        if (direction() == DIR_FIGURE_NONE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        }

        break;
    case FIGURE_ACTION_83_SOLDIER_GOING_TO_STANDARD:
    base.formation_at_rest = 0;
        destination_tile= m->standard_tile.shifted(formation_layout_position_x(m->layout, base.index_in_formation),
                                                    formation_layout_position_y(m->layout, base.index_in_formation));
        if (base.alternative_location_index) {
            destination_tile.set(ALTERNATIVE_POINTS[base.alternative_location_index].x,
                                 ALTERNATIVE_POINTS[base.alternative_location_index].y);
        }
        //            destination_tile.grid_offset() = MAP_OFFSET(destination_tile.x(), destination_tile.y());
        base.move_ticks(speed_factor);
        if (direction() == DIR_FIGURE_NONE) {
            base.action_state = FIGURE_ACTION_84_SOLDIER_AT_STANDARD;
            base.anim.frame = 0;
        } else if (direction() == DIR_FIGURE_REROUTE)
            route_remove();
        else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            base.alternative_location_index++;
            if (base.alternative_location_index > 168) {
                poof();
            }

            base.anim.frame = 0;
        }
        break;

    case FIGURE_ACTION_84_SOLDIER_AT_STANDARD:
        base.formation_at_rest = 0;
        base.anim.frame = 0;
        base.map_figure_update();
        destination_tile = m->standard_tile.shifted(formation_layout_position_x(m->layout, base.index_in_formation),
                                                     formation_layout_position_y(m->layout, base.index_in_formation));

        if (base.alternative_location_index) {
            destination_tile.set(ALTERNATIVE_POINTS[base.alternative_location_index].x,
                                 ALTERNATIVE_POINTS[base.alternative_location_index].y);
        }
        if (tilex() != destination_tile.x() || tiley() != destination_tile.y()) {
            if (m->missile_fired <= 0 && m->recent_fight <= 0 && m->missile_attack_timeout <= 0) {
                base.action_state = FIGURE_ACTION_83_SOLDIER_GOING_TO_STANDARD;
                base.alternative_location_index = 0;
            }
        }
        if (action_state() != FIGURE_ACTION_83_SOLDIER_GOING_TO_STANDARD) {
            if (type() == FIGURE_ARCHER) {
                base.javelin_launch_missile();
            } else if (type() == FIGURE_FCHARIOTEER) {
                base.legionary_attack_adjacent_enemy();
            }
        }
        break;

    case FIGURE_ACTION_85_SOLDIER_GOING_TO_MILITARY_ACADEMY:
        m->has_military_training = 1;
        base.formation_at_rest = 1;
        base.move_ticks(speed_factor);
        if (direction() == DIR_FIGURE_NONE) {
            base.action_state = FIGURE_ACTION_81_SOLDIER_GOING_TO_FORT;
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }
        break;

    case FIGURE_ACTION_86_SOLDIER_MOPPING_UP:
        base.formation_at_rest = 0;
        if (base.find_mop_up_target()) {
            base.move_ticks(speed_factor);
            if (direction() == DIR_FIGURE_NONE) {
                figure* target = figure_get(base.target_figure_id);
                destination_tile = target->tile;
                //                    destination_tile.x() = target->tile.x();
                //                    destination_tile.y() = target->tile.y();
                route_remove();
            } else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
                base.action_state = FIGURE_ACTION_84_SOLDIER_AT_STANDARD;
                base.target_figure_id = 0;
                base.anim.frame = 0;
            }
        }
        break;

    case FIGURE_ACTION_87_SOLDIER_GOING_TO_DISTANT_BATTLE: {
        base.formation_at_rest = 0;
        destination_tile = g_city.map.exit_point;
        base.move_ticks(speed_factor);
        if (direction() == DIR_FIGURE_NONE) {
            base.action_state = FIGURE_ACTION_89_SOLDIER_AT_DISTANT_BATTLE;
            route_remove();
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }

        break;
    }
    case FIGURE_ACTION_88_SOLDIER_RETURNING_FROM_DISTANT_BATTLE:
        //            is_ghost = false;
        wait_ticks = 0;
        base.formation_at_rest = 1;
        destination_tile.set(base.formation_position_x.soldier, base.formation_position_y.soldier);
        //            destination_tile.x() = formation_position_x.soldier;
        //            destination_tile.y() = formation_position_y.soldier;
        //            destination_tile.grid_offset() = MAP_OFFSET(destination_tile.x(), destination_tile.y());
        base.move_ticks(speed_factor);
        if (direction() == DIR_FIGURE_NONE) {
            base.action_state = FIGURE_ACTION_80_SOLDIER_AT_REST;
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }
        break;

    case FIGURE_ACTION_89_SOLDIER_AT_DISTANT_BATTLE:
        //            is_ghost = true;
        base.formation_at_rest = 1;
        break;
    }

    int dir = -1;
    update_image(m, dir);
}

void figure_soldier_infantry::update_image(const formation *m, int &dir) {
    figure_soldier::update_image(m, dir);

    if (action_state() == FIGURE_ACTION_150_ATTACK) {
        //int image_id = image_id_from_group(GROUP_BUILDING_FORT_LEGIONARY);
        //if (base.attack_image_offset < 12)
        //    image_id = image_id + 96 + dir;
        //else {
        //    image_id = image_id + 96 + dir + 8 * ((base.attack_image_offset - 12) / 2);
        //}
        image_set_animation(soldier_infantry_m.anim["attack"]);
    } else if (action_state() == FIGURE_ACTION_149_CORPSE) {
        image_set_animation(soldier_infantry_m.anim["death"]);
    } else if (action_state() == FIGURE_ACTION_84_SOLDIER_AT_STANDARD) {
        //if (m->is_halted && m->layout == FORMATION_COLUMN && m->missile_attack_timeout)
        //    image_id = image_id + dir + 144;
        //else {
        //    image_id = image_id + dir;
        //}
        image_set_animation(soldier_infantry_m.anim["walk"]);
        base.anim.frame = 0;
    } else {
        image_set_animation(soldier_infantry_m.anim["walk"]);
    }
}

void figure_soldier_charioteer::update_image(const formation *m, int &dir) {
    figure_soldier::update_image(m, dir);

    if (action_state() == FIGURE_ACTION_150_ATTACK) {
        //int image_id = image_id_from_group(GROUP_BUILDING_FORT_LEGIONARY);
        //if (base.attack_image_offset < 12)
        //    image_id = image_id + 96 + dir;
        //else {
        //    image_id = image_id + 96 + dir + 8 * ((base.attack_image_offset - 12) / 2);
        //}
        image_set_animation(soldier_charioterr_m.anim["attack"]);
    } else if (action_state() == FIGURE_ACTION_149_CORPSE) {
        image_set_animation(soldier_charioterr_m.anim["death"]);
    } else {
        image_set_animation(soldier_charioterr_m.anim["walk"]);
    }
}

void figure_soldier_archer::update_image(const formation *m, int &dir) {
    figure_soldier::update_image(m, dir);

    if (action_state() == FIGURE_ACTION_150_ATTACK) {
        //int image_id = image_id_from_group(GROUP_BUILDING_FORT_LEGIONARY);
        //if (base.attack_image_offset < 12)
        //    image_id = image_id + 96 + dir;
        //else {
        //    image_id = image_id + 96 + dir + 8 * ((base.attack_image_offset - 12) / 2);
        //}
        image_set_animation(soldier_archer_m.anim["attack"]);
    } else if (action_state() == FIGURE_ACTION_149_CORPSE) {
        image_set_animation(soldier_archer_m.anim["death"]);
    } else if (action_state() == FIGURE_ACTION_84_SOLDIER_AT_STANDARD) {
        //if (m->is_halted && m->layout == FORMATION_COLUMN && m->missile_attack_timeout)
        //    image_id = image_id + dir + 144;
        //else {
        //    image_id = image_id + dir;
        //}
        image_set_animation(soldier_archer_m.anim["walk"]);
        base.anim.frame = 0;
    } else {
        image_set_animation(soldier_archer_m.anim["walk"]);
    }
}
