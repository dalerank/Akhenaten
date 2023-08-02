#include "animal.h"

#include "building/building.h"
#include "city/entertainment.h"
#include "city/figures.h"
#include "core/calc.h"
#include "core/random.h"
#include "figure/combat.h"
#include "figure/formation.h"
#include "figure/formation_layout.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/view/view.h"
#include "grid/building.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/point.h"
#include "grid/terrain.h"
#include "scenario/map.h"
#include "scenario/property.h"

#include "figure/properties.h"
#include "graphics/image_groups.h"
#include "grid/building.h"
#include "grid/terrain.h"
#include "missile.h"

static const coords_t SEAGULL_OFFSETS[] = {{0, 0}, {0, -2}, {-2, 0}, {1, 2}, {2, 0}, {-3, 1}, {4, -3}, {-2, 4}, {0, 0}};

static const coords_t HORSE_DESTINATION_1[]
  = {{2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 1}, {8, 1}, {9, 1}, {10, 1}, {11, 1}, {12, 2}, {12, 3}, {11, 3}, {10, 3}, {9, 3}, {8, 3}, {7, 3}, {6, 3}, {5, 3}, {4, 3}, {3, 3}, {2, 2}};
static const coords_t HORSE_DESTINATION_2[]
  = {{12, 3}, {11, 3}, {10, 3}, {9, 3}, {8, 3}, {7, 3}, {6, 3}, {5, 3}, {4, 3}, {3, 3}, {2, 2}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 1}, {8, 1}, {9, 1}, {10, 1}, {11, 1}, {12, 2}};

static const int SHEEP_IMAGE_OFFSETS[]
  = {0, 0, 1, 1, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 5, 5, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 1, 1, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 5, 5};

enum E_HORSE { HORSE_CREATED = 0,
               HORSE_RACING = 1,
               HORSE_FINISHED = 2 };

static void create_fishing_point(int x, int y) {
    random_generate_next();
    figure* fish = figure_create(FIGURE_FISH_GULLS, x, y, DIR_0_TOP_RIGHT);
    fish->anim_frame = random_byte() & 0x1f;
    fish->progress_on_tile = random_byte() & 7;
    fish->set_cross_country_direction(
      fish->cc_coords.x, fish->cc_coords.y, 15 * fish->destination_tile.x(), 15 * fish->destination_tile.y(), 0);
}
void figure_create_fishing_points(void) {
    scenario_map_foreach_fishing_point(create_fishing_point);
}

static void create_herd(int x, int y) {
    int herd_type;
    int num_animals;
    switch (scenario_property_climate()) {
    case CLIMATE_CENTRAL:
        herd_type = FIGURE_SHEEP;
        num_animals = 10;
        break;
    case CLIMATE_NORTHERN:
        // herd_type = FIGURE_WOLF;
        herd_type = FIGURE_OSTRICH;
        num_animals = 8;
        break;
    case CLIMATE_DESERT:
        herd_type = FIGURE_OSTRICH; // FIGURE_ZEBRA
        num_animals = 12;
        break;
    default:
        return;
    }
    int formation_id = formation_create_herd(herd_type, x, y, num_animals);
    if (formation_id > 0) {
        for (int fig = 0; fig < num_animals; fig++) {
            random_generate_next();

            figure* f = figure_create(herd_type, x, y, DIR_0_TOP_RIGHT);
            f->action_state = FIGURE_ACTION_196_HERD_ANIMAL_AT_REST;
            f->formation_id = formation_id;
            f->wait_ticks = f->id & 0x1f;
        }
    }
}

void figure_create_herds(void) {
    scenario_map_foreach_herd_point(create_herd);
}

bool figure::herd_roost(int step, int bias, int max_dist) {
    if (!formation_id) {
        return false;
    }

    const formation* m = formation_get(formation_id);
    int dx;
    int dy;
    random_around_point(m->x_home, m->y_home, tile.x(), tile.y(), &dx, &dy, step, bias, max_dist);

    int offset = MAP_OFFSET(dx, dy);
    if (!map_terrain_is(offset, TERRAIN_IMPASSABLE_WOLF)) { // todo: fix gardens
        destination_tile.set(dx, dy);
        //        destination_tile.x() = dx;
        //        destination_tile.y() = dy;
        return true;
    } else {
        destination_tile.set(0, 0);
        //        destination_tile.x() = 0;
        //        destination_tile.y() = 0;
        return false;
    }
}

void figure::seagulls_action() {
    terrain_usage = TERRAIN_USAGE_ANY;
    is_ghost = false;
    use_cross_country = true;
    if (!(anim_frame & 3) && move_ticks_cross_country(1)) {
        progress_on_tile++;
        if (progress_on_tile > 14) // wrap around
            progress_on_tile = 0;
        set_cross_country_destination(source_tile.x() + SEAGULL_OFFSETS[progress_on_tile].x,
                                      source_tile.y() + SEAGULL_OFFSETS[progress_on_tile].y);
    }
    if (id & 1) {
        image_set_animation(GROUP_FIGURE_SEAGULLS, 0, 54, 3);
        //        figure_image_increase_offset(54);
        //        sprite_image_id = image_id_from_group(GROUP_FIGURE_SEAGULLS) + anim_frame / 3;
    } else {
        image_set_animation(GROUP_FIGURE_SEAGULLS, 18, 72, 3);
        //        figure_image_increase_offset(72);
        //        sprite_image_id = image_id_from_group(GROUP_FIGURE_SEAGULLS) + 18 + anim_frame / 3;
    }
}

void figure::sheep_action() {
    const formation* m = formation_get(formation_id);
    //    terrain_usage = TERRAIN_USAGE_ANIMAL;
    //    use_cross_country = false;
    //    is_ghost = false;
    city_figures_add_animal();
    //    figure_image_increase_offset(6);

    switch (action_state) {
    case FIGURE_ACTION_196_HERD_ANIMAL_AT_REST:
        wait_ticks++;
        if (wait_ticks > 400) {
            wait_ticks = id & 0x1f;
            action_state = FIGURE_ACTION_197_HERD_ANIMAL_MOVING;
            destination_tile.set(m->destination_x + formation_layout_position_x(FORMATION_HERD, index_in_formation),
                                 m->destination_y + formation_layout_position_y(FORMATION_HERD, index_in_formation));
            //                destination_tile.x() = m->destination_x + formation_layout_position_x(FORMATION_HERD,
            //                index_in_formation); destination_tile.y() = m->destination_y +
            //                formation_layout_position_y(FORMATION_HERD, index_in_formation);
            roam_length = 0;
        }
        break;
    case FIGURE_ACTION_197_HERD_ANIMAL_MOVING:
        move_ticks(1);
        if (direction == DIR_FIGURE_NONE || direction == DIR_FIGURE_CAN_NOT_REACH) {
            direction = previous_tile_direction;
            action_state = FIGURE_ACTION_196_HERD_ANIMAL_AT_REST;
            wait_ticks = id & 0x1f;
        } else if (direction == DIR_FIGURE_REROUTE)
            route_remove();

        break;
    }

    int dir = figure_image_direction();
    if (action_state == FIGURE_ACTION_149_CORPSE) {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_SHEEP) + 104 + figure_image_corpse_offset();
    } else if (action_state == FIGURE_ACTION_196_HERD_ANIMAL_AT_REST) {
        if (id & 3)
            sprite_image_id
              = image_id_from_group(GROUP_FIGURE_SHEEP) + 48 + dir + 8 * SHEEP_IMAGE_OFFSETS[wait_ticks & 0x3f];
        else
            sprite_image_id = image_id_from_group(GROUP_FIGURE_SHEEP) + 96 + dir;
    } else
        image_set_animation(GROUP_FIGURE_SHEEP, 0, 6);
    //        sprite_image_id = image_id_from_group(GROUP_FIGURE_SHEEP) + dir + 8 * anim_frame;
}

void figure::hyena_action() {
    const formation* m = formation_get(formation_id);
    city_figures_add_animal();

    switch (action_state) {
    case FIGURE_ACTION_196_HERD_ANIMAL_AT_REST:
        wait_ticks++;
        if (wait_ticks > 400) {
            wait_ticks = id & 0x1f;
            action_state = FIGURE_ACTION_197_HERD_ANIMAL_MOVING;
            destination_tile.set(m->destination_x + formation_layout_position_x(FORMATION_HERD, index_in_formation),
                                 m->destination_y + formation_layout_position_y(FORMATION_HERD, index_in_formation));
            //                destination_tile.x() = m->destination_x + formation_layout_position_x(FORMATION_HERD,
            //                index_in_formation); destination_tile.y() = m->destination_y +
            //                formation_layout_position_y(FORMATION_HERD, index_in_formation);
            roam_length = 0;
        }
        break;
    case FIGURE_ACTION_197_HERD_ANIMAL_MOVING:
        move_ticks(2);
        if (direction == DIR_FIGURE_NONE || direction == DIR_FIGURE_CAN_NOT_REACH) {
            direction = previous_tile_direction;
            action_state = FIGURE_ACTION_196_HERD_ANIMAL_AT_REST;
            wait_ticks = id & 0x1f;
        } else if (direction == DIR_FIGURE_REROUTE)
            route_remove();
        break;
    case FIGURE_ACTION_199_WOLF_ATTACKING:
        move_ticks(2);
        if (direction == DIR_FIGURE_NONE) {
            int target_id = figure_combat_get_target_for_wolf(tile.x(), tile.y(), 6);
            if (target_id) {
                figure* target = figure_get(target_id);
                destination_tile = target->tile;
                //                    destination_tile.x() = target->tile.x();
                //                    destination_tile.y() = target->tile.y();
                target_figure_id = target_id;
                target->targeted_by_figure_id = id;
                target_figure_created_sequence = target->created_sequence;
                route_remove();
            } else {
                direction = previous_tile_direction;
                action_state = FIGURE_ACTION_196_HERD_ANIMAL_AT_REST;
                wait_ticks = id & 0x1f;
            }
        } else if (direction == DIR_FIGURE_REROUTE)
            route_remove();
        else if (direction == DIR_FIGURE_CAN_NOT_REACH) {
            direction = previous_tile_direction;
            action_state = FIGURE_ACTION_196_HERD_ANIMAL_AT_REST;
            wait_ticks = id & 0x1f;
        }
        break;
    }

    int dir = figure_image_direction();
    if (action_state == FIGURE_ACTION_149_CORPSE) {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_HYENA_DEATH) + figure_image_corpse_offset();
    } else if (action_state == FIGURE_ACTION_150_ATTACK) {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_HYENA_ATTACK) + 104 + dir + 8 * (attack_image_offset / 4);
    } else if (action_state == FIGURE_ACTION_196_HERD_ANIMAL_AT_REST) {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_HYENA_IDLE) + 152 + dir;
    } else {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_HYENA_WALK) + dir + 8 * anim_frame;
    }
}

void figure::ostrich_action() {
    const formation* m = formation_get(formation_id);
    city_figures_add_animal();

    switch (action_state) {
    case 24:                           // spawning
    case 14:                           // scared
    case 15:                           // terrified
    case 18:                           // roosting
    case FIGURE_ACTION_19_ANIMAL_IDLE: // idle
    case FIGURE_ACTION_196_HERD_ANIMAL_AT_REST:
        wait_ticks--;
        //            if (wait_ticks % 5 == 0 && is_nearby(NEARBY_ANY, 6))
        //                advance_action(ACTION_16_FLEEING);
        if (wait_ticks <= 0)
            advance_action(ACTION_8_RECALCULATE);
        break;
    case 199:
    case ACTION_8_RECALCULATE:
        wait_ticks--;
        if (wait_ticks <= 0) {
            if (herd_roost(4, 8, 32)) {
                wait_ticks = 0;
                advance_action(ACTION_10_GOING);
            } else
                wait_ticks = 5;
        }
        break;
    case 16: // fleeing
    case ACTION_10_GOING:
    case FIGURE_ACTION_197_HERD_ANIMAL_MOVING:
        //            if (action_state == 16)
        //                while (destination_x == 0 || destination_y == 0)
        //                    herd_roost(4, 8, 22);
        if (do_goto(destination_tile.x(),
                    destination_tile.y(),
                    TERRAIN_USAGE_ANIMAL,
                    18 + (random_byte() & 0x1),
                    ACTION_8_RECALCULATE))
            wait_ticks = 50;
        break;
    }
    switch (action_state) {
    case ACTION_8_RECALCULATE:
    case FIGURE_ACTION_19_ANIMAL_IDLE: // idle
        image_set_animation(GROUP_FIGURE_OSTRICH_IDLE, 0, 8);
        break;
    case ACTION_18_ROOSTING: // roosting
        image_set_animation(GROUP_FIGURE_OSTRICH_EATING, 0, 7);
        break;
    case ACTION_16_FLEEING: // fleeing
        image_set_animation(GROUP_FIGURE_OSTRICH_RUN, 0, 11);
        break;
    case ACTION_10_GOING: // on the move
        image_set_animation(GROUP_FIGURE_OSTRICH_WALK, 0, 11);
        break;
    case ACTION_15_ANIMAL_TERRIFIED: // terrified
    case 14:                         // scared
        image_set_animation(GROUP_FIGURE_OSTRICH_IDLE, 0, 8);
        anim_frame = 0;
        break;
    case FIGURE_ACTION_150_ATTACK: // unused?
        image_set_animation(GROUP_FIGURE_OSTRICH_IDLE, 0, 8);
        break;
    default:
        // In any strange situation load eating/roosting animation
        image_set_animation(GROUP_FIGURE_OSTRICH_EATING, 0, 7);
        break;
        break;
    }
}

// TODO: Rewrite hippo action & add correct animations
void figure::hippo_action() {
    const formation* m = formation_get(formation_id);
    city_figures_add_animal();

    switch (action_state) {
    case 24: // spawning
    case 14: // scared
    case 15: // terrified
    case 18: // roosting
    case 19: // idle
    case FIGURE_ACTION_196_HERD_ANIMAL_AT_REST:
        wait_ticks--;
        //            if (wait_ticks % 5 == 0 && is_nearby(NEARBY_ANY, 6))
        //                advance_action(ACTION_16_FLEEING);
        if (wait_ticks <= 0)
            advance_action(ACTION_8_RECALCULATE);
        break;
    case 199:
    case ACTION_8_RECALCULATE:
        wait_ticks--;
        if (wait_ticks <= 0) {
            if (herd_roost(4, 8, 32)) {
                wait_ticks = 0;
                advance_action(ACTION_10_GOING);
            } else
                wait_ticks = 5;
        }
        break;
    case 16: // fleeing
    case ACTION_10_GOING:
    case FIGURE_ACTION_197_HERD_ANIMAL_MOVING:
        //            if (action_state == 16)
        //                while (destination_x == 0 || destination_y == 0)
        //                    herd_roost(4, 8, 22);
        if (do_goto(destination_tile.x(),
                    destination_tile.y(),
                    TERRAIN_USAGE_ANIMAL,
                    18 + (random_byte() & 0x1),
                    ACTION_8_RECALCULATE))
            wait_ticks = 50;
        break;
    }
    switch (action_state) {
    case ACTION_8_RECALCULATE:
    case 19: // idle
        image_set_animation(GROUP_FIGURE_HIPPO, 104, 7);
        break;
    case 18: // roosting
        image_set_animation(GROUP_FIGURE_HIPPO, 448, 8);
        break;
    case 16: // fleeing
    case 10: // on the move
        image_set_animation(GROUP_FIGURE_HIPPO, 0, 11);
        break;
    case 15: // terrified
    case 14: // scared
        image_set_animation(GROUP_FIGURE_HIPPO, 0, 11);
        anim_frame = 0;
        break;
    case FIGURE_ACTION_150_ATTACK: // unused?
        image_set_animation(GROUP_FIGURE_HIPPO, 104, 7);
        break;
    default:
        image_set_animation(GROUP_FIGURE_HIPPO, 0, 11);
        break;
    }
}

void figure::zebra_action() {
    const formation* m = formation_get(formation_id);
    //    terrain_usage = TERRAIN_USAGE_ANIMAL;
    //    use_cross_country = false;
    //    is_ghost = false;
    city_figures_add_animal();
    //    figure_image_increase_offset(12);

    switch (action_state) {
    case FIGURE_ACTION_196_HERD_ANIMAL_AT_REST:
        wait_ticks++;
        if (wait_ticks > 200) {
            wait_ticks = id & 0x1f;
            action_state = FIGURE_ACTION_197_HERD_ANIMAL_MOVING;
            destination_tile.set(m->destination_x + formation_layout_position_x(FORMATION_HERD, index_in_formation),
                                 m->destination_y + formation_layout_position_y(FORMATION_HERD, index_in_formation));
            //                destination_tile.x() = m->destination_x + formation_layout_position_x(FORMATION_HERD,
            //                index_in_formation); destination_tile.y() = m->destination_y +
            //                formation_layout_position_y(FORMATION_HERD, index_in_formation);
            roam_length = 0;
        }
        break;
    case FIGURE_ACTION_197_HERD_ANIMAL_MOVING:
        move_ticks(2);
        if (direction == DIR_FIGURE_NONE || direction == DIR_FIGURE_CAN_NOT_REACH) {
            direction = previous_tile_direction;
            action_state = FIGURE_ACTION_196_HERD_ANIMAL_AT_REST;
            wait_ticks = id & 0x1f;
        } else if (direction == DIR_FIGURE_REROUTE)
            route_remove();

        break;
    }
    int dir = figure_image_direction();
    if (action_state == FIGURE_ACTION_149_CORPSE) {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_CROCODILE) + 96 + figure_image_corpse_offset();
    } else if (action_state == FIGURE_ACTION_196_HERD_ANIMAL_AT_REST) {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_CROCODILE) + dir;
    } else {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_CROCODILE) + dir + 8 * anim_frame;
    }
}

static void set_horse_destination(int state) {
    //    building *b = building_get(building_id);
    //    int orientation = city_view_orientation();
    //    int rotation = b->subtype.orientation;
    //    if (state == HORSE_CREATED) {
    //        map_f->map_figure_remove();
    //        if (rotation == 0) {
    //            if (orientation == DIR_0_TOP_RIGHT || orientation == DIR_6_TOP_LEFT) {
    //                f->destination_x = b->tile.x() + HORSE_DESTINATION_1[f->wait_ticks_missile].x;
    //                f->destination_y = b->tile.y() + HORSE_DESTINATION_1[f->wait_ticks_missile].y;
    //            } else {
    //                f->destination_x = b->tile.x() + HORSE_DESTINATION_2[f->wait_ticks_missile].x;
    //                f->destination_y = b->tile.y() + HORSE_DESTINATION_2[f->wait_ticks_missile].y;
    //            }
    //        } else {
    //            if (orientation == DIR_0_TOP_RIGHT || orientation == DIR_2_BOTTOM_RIGHT) {
    //                f->destination_x = b->tile.x() + HORSE_DESTINATION_1[f->wait_ticks_missile].y;
    //                f->destination_y = b->tile.y() + HORSE_DESTINATION_1[f->wait_ticks_missile].x;
    //            } else {
    //                f->destination_x = b->tile.x() + HORSE_DESTINATION_2[f->wait_ticks_missile].y;
    //                f->destination_y = b->tile.y() + HORSE_DESTINATION_2[f->wait_ticks_missile].x;
    //            }
    //        }
    //        if (f->resource_id == 1)
    //            f->destination_y++;
    //
    //        f->x = f->destination_x;
    //        f->y = f->destination_y;
    //        f->cross_country_x = 15 * f->x;
    //        f->cross_country_y = 15 * f->y;
    //        f->grid_offset_figure = map_grid_offset(f->x, f->y);
    //        map_figure_add();
    //    } else if (state == HORSE_RACING) {
    //        if (rotation == 0) {
    //            if (orientation == DIR_0_TOP_RIGHT || orientation == DIR_6_TOP_LEFT) {
    //                f->destination_x = b->tile.x() + HORSE_DESTINATION_1[f->wait_ticks_missile].x;
    //                f->destination_y = b->tile.y() + HORSE_DESTINATION_1[f->wait_ticks_missile].y;
    //            } else {
    //                f->destination_x = b->tile.x() + HORSE_DESTINATION_2[f->wait_ticks_missile].x;
    //                f->destination_y = b->tile.y() + HORSE_DESTINATION_2[f->wait_ticks_missile].y;
    //            }
    //        } else {
    //            if (orientation == DIR_0_TOP_RIGHT || orientation == DIR_2_BOTTOM_RIGHT) {
    //                f->destination_x = b->tile.x() + HORSE_DESTINATION_1[f->wait_ticks_missile].y;
    //                f->destination_y = b->tile.y() + HORSE_DESTINATION_1[f->wait_ticks_missile].x;
    //            } else {
    //                f->destination_x = b->tile.x() + HORSE_DESTINATION_2[f->wait_ticks_missile].y;
    //                f->destination_y = b->tile.y() + HORSE_DESTINATION_2[f->wait_ticks_missile].x;
    //            }
    //        }
    //    } else if (state == HORSE_FINISHED) {
    //        if (rotation == 0) {
    //            if (orientation == DIR_0_TOP_RIGHT || orientation == DIR_6_TOP_LEFT) {
    //                if (f->resource_id) {
    //                    f->destination_x = b->tile.x() + 1;
    //                    f->destination_y = b->tile.y() + 2;
    //                } else {
    //                    f->destination_x = b->tile.x() + 1;
    //                    f->destination_y = b->tile.y() + 1;
    //                }
    //            } else {
    //                if (f->resource_id) {
    //                    f->destination_x = b->tile.x() + 12;
    //                    f->destination_y = b->tile.y() + 3;
    //                } else {
    //                    f->destination_x = b->tile.x() + 12;
    //                    f->destination_y = b->tile.y() + 2;
    //                }
    //            }
    //        } else {
    //            if (orientation == DIR_0_TOP_RIGHT || orientation == DIR_2_BOTTOM_RIGHT) {
    //                if (f->resource_id) {
    //                    f->destination_x = b->tile.x() + 2;
    //                    f->destination_y = b->tile.y() + 1;
    //                } else {
    //                    f->destination_x = b->tile.x() + 1;
    //                    f->destination_y = b->tile.y() + 1;
    //                }
    //            } else {
    //                if (f->resource_id) {
    //                    f->destination_x = b->tile.x() + 3;
    //                    f->destination_y = b->tile.y() + 12;
    //                } else {
    //                    f->destination_x = b->tile.x() + 2;
    //                    f->destination_y = b->tile.y() + 12;
    //                }
    //            }
    //        }
    //    }
}

void figure::hippodrome_horse_action() {
    //    city_entertainment_set_hippodrome_has_race(1);
    //    f->use_cross_country = true;
    //    f->is_ghost = false;
    //    figure_image_increase_offset(8);
    //    if (!(building_get(building_id)->state)) {
    //        f->poof();
    //        return;
    //    }
    //    switch (f->action_state) {
    //        case FIGURE_ACTION_200_HIPPODROME_HORSE_CREATED:
    //            f->anim_frame = 0;
    //            f->wait_ticks_missile = 0;
    //            set_horse_destination(f, HORSE_CREATED);
    //            f->wait_ticks++;
    //            if (f->wait_ticks > 60 && f->resource_id == 0) {
    //                f->action_state = FIGURE_ACTION_201_HIPPODROME_HORSE_RACING;
    //                f->wait_ticks = 0;
    //            }
    //            f->wait_ticks++;
    //            if (f->wait_ticks > 20 && f->resource_id == 1) {
    //                f->action_state = FIGURE_ACTION_201_HIPPODROME_HORSE_RACING;
    //                f->wait_ticks = 0;
    //            }
    //            break;
    //        case FIGURE_ACTION_201_HIPPODROME_HORSE_RACING:
    //            f->direction = calc_general_direction(f->x, f->y, f->destination_x, f->destination_y);
    //            if (f->direction == DIR_FIGURE_AT_DESTINATION) {
    //                f->wait_ticks_missile++;
    //                if (f->wait_ticks_missile >= 22) {
    //                    f->wait_ticks_missile = 0;
    //                    f->leading_figure_id++;
    //                    if (f->leading_figure_id >= 6) {
    //                        f->wait_ticks = 0;
    //                        f->action_state = FIGURE_ACTION_202_HIPPODROME_HORSE_DONE;
    //                    }
    //                    if ((f->id + random_byte()) & 1)
    //                        f->speed_multiplier = 3;
    //                    else {
    //                        f->speed_multiplier = 4;
    //                    }
    //                } else if (f->wait_ticks_missile == 11) {
    //                    if ((f->id + random_byte()) & 1)
    //                        f->speed_multiplier = 3;
    //                    else {
    //                        f->speed_multiplier = 4;
    //                    }
    //                }
    //                set_horse_destination(f, HORSE_RACING);
    //                f->direction = calc_general_direction(f->x, f->y, f->destination_x, f->destination_y);
    //                figure_movement_set_cross_country_direction(f,
    //                                                            f->cross_country_x, f->cross_country_y,
    //                                                            15 * f->destination_x, 15 * f->destination_y, 0);
    //            }
    //            if (f->action_state != FIGURE_ACTION_202_HIPPODROME_HORSE_DONE)
    //                move_ticks_cross_country(f->speed_multiplier);
    //
    //            break;
    //        case FIGURE_ACTION_202_HIPPODROME_HORSE_DONE:
    //            if (!f->wait_ticks) {
    //                set_horse_destination(f, HORSE_FINISHED);
    //                f->direction = calc_general_direction(f->x, f->y, f->destination_x, f->destination_y);
    //                figure_movement_set_cross_country_direction(f,
    //                                                            f->cross_country_x, f->cross_country_y,
    //                                                            15 * f->destination_x, 15 * f->destination_y, 0);
    //            }
    //            if (f->direction != DIR_FIGURE_AT_DESTINATION)
    //                move_ticks_cross_country(1);
    //
    //            f->wait_ticks++;
    //            if (f->wait_ticks > 30)
    //                f->anim_frame = 0;
    //
    //            f->wait_ticks++;
    //            if (f->wait_ticks > 150)
    //                f->poof();
    //
    //            break;
    //    }
    //
    //    int dir = figure_image_direction(f);
    //    if (f->resource_id == 0) {
    //        f->sprite_image_id = image_id_from_group(GROUP_FIGURE_HIPPODROME_HORSE_1) +
    //                      dir + 8 * f->anim_frame;
    //        f->cart_image_id = image_id_from_group(GROUP_FIGURE_HIPPODROME_CART_1) + dir;
    //    } else {
    //        f->sprite_image_id = image_id_from_group(GROUP_FIGURE_HIPPODROME_HORSE_2) +
    //                      dir + 8 * f->anim_frame;
    //        f->cart_image_id = image_id_from_group(GROUP_FIGURE_HIPPODROME_CART_2) + dir;
    //    }
    //    int cart_dir = (dir + 4) % 8;
    //    figure_image_set_cart_offset(f, cart_dir);
}

void figure_hippodrome_horse_reroute(void) {
    if (!city_entertainment_hippodrome_has_race()) {
        return;
    }

    for (int i = 1; i < MAX_FIGURES[GAME_ENV]; i++) {
        figure* f = figure_get(i);
        if (f->state == FIGURE_STATE_ALIVE && f->type == FIGURE_HIPPODROME_HORSES) {
            f->wait_ticks_missile = 0;
            set_horse_destination(HORSE_CREATED);
        }
    }
}

void figure::hunter_action() {
    figure* prey = figure_get(target_figure_id);
    int dist = 0;
    if (target_figure_id) {
        dist = calc_maximum_distance(tile.x(), tile.y(), prey->tile.x(), prey->tile.y());
    }

    switch (action_state) {
    case ACTION_8_RECALCULATE:
    case 14: // spawning
        target_figure_id = is_nearby(1, &dist, 10000, false);
        if (target_figure_id) {
            figure_get(target_figure_id)->targeted_by_figure_id = id;
            advance_action(9);
        }
        break;
    case 13: // pitpat
        if (!target_figure_id)
            return advance_action(8);
        wait_ticks--;
        if (wait_ticks <= 0) {
            advance_action(9);
        }
        break;
    case 9: // following prey
        if (!target_figure_id)
            return advance_action(8);
        if (dist >= 2) {
            do_goto(prey->tile.x(), prey->tile.y(), TERRAIN_USAGE_ANIMAL, 15, 8);
        } else {
            wait_ticks = figure_properties_for_type(FIGURE_HUNTER_ARROW)->missile_delay;
            advance_action(15);
        }
        break;
        //        case ??: // attacking enemy
    case 15: // firing at prey
        wait_ticks--;
        if (wait_ticks <= 0) {
            if (!target_figure_id) {
                return advance_action(8);
            }
            wait_ticks = figure_properties_for_type(FIGURE_HUNTER_ARROW)->missile_delay;
            if (prey->state == FIGURE_STATE_DYING) {
                advance_action(11);
            } else if (dist >= 2) {
                //                    advance_action(9);
                //                    wait_ticks = 0;
                wait_ticks = 12;
                advance_action(13);
            } else {
                direction = calc_missile_shooter_direction(tile.x(), tile.y(), prey->tile.x(), prey->tile.y());
                missile_fire_at(target_figure_id, FIGURE_HUNTER_ARROW);
            }
        }
        break;
    case 11: // going to pick up prey
        if (!target_figure_id) {
            return advance_action(8);
        }

        if (do_goto(prey->tile.x(), prey->tile.y(), TERRAIN_USAGE_ANIMAL, 10, 11)) {
            anim_offset = 0;
        }
        break;
    case 10: // picking up prey
        if (target_figure_id) {
            prey->poof();
        }
        target_figure_id = 0;
        if (anim_frame >= 17) {
            advance_action(12);
        }
        break;
    case 12:                                     // returning with prey
        if (do_returnhome(TERRAIN_USAGE_ANIMAL)) // add game meat to hunting lodge!
            home()->stored_full_amount += 100;

        break;
    }
    switch (action_state) {
    case ACTION_8_RECALCULATE:
    case 14:
    case 13:
    case 9:
    case ACTION_11_HUNTER_WALK: // normal walk
        image_set_animation(GROUP_FIGURE_HUNTER_OSTRICH_MOVE, 0, 12);
        break;

    case ACTION_15_HUNTER_HUNT: // hunting
        image_set_animation(GROUP_FIGURE_HUNTER_OSTRICH_HUNT, 0, 12);
        break;
        //        case ??: // attacking
        //            image_set_animation(GROUP_FIGURE_HUNTER, 200, 12);
        //        case ??: // attacking w/ prey on his back
        //            image_set_animation(GROUP_FIGURE_HUNTER, 296, 12);
    case ACTION_15_HUNTER_PACK:
        image_set_animation(GROUP_FIGURE_HUNTER_OSTRICH_PACK, 0, 18);
        break;

    case ACTION_15_HUNTER_MOVE_PACKED:
        image_set_animation(GROUP_FIGURE_HUNTER_OSTRICH_MOVE_PACKED, 0, 12);
        break;
    }
}