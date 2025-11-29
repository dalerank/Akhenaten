#include "figure_animal.h"

#include "building/building.h"
#include "city/entertainment.h"
#include "city/city.h"
#include "core/calc.h"
#include "core/random.h"
#include "core/profiler.h"
#include "figure/combat.h"
#include "figure/formation.h"
#include "figure/formation_layout.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "graphics/image.h"
#include "graphics/image_desc.h"
#include "graphics/image_groups.h"
#include "graphics/view/view.h"
#include "grid/building.h"
#include "grid/figure.h"
#include "grid/water.h"
#include "grid/grid.h"
#include "grid/point.h"
#include "grid/terrain.h"
#include "scenario/map.h"
#include "scenario/scenario.h"

#include "graphics/image_groups.h"
#include "grid/building.h"
#include "grid/terrain.h"

static const vec2i HORSE_DESTINATION_1[] = {
    {2, 1},  {3, 1},  {4, 1},  {5, 1}, {6, 1}, {7, 1}, {8, 1}, {9, 1}, {10, 1}, {11, 1}, {12, 2},
    {12, 3}, {11, 3}, {10, 3}, {9, 3}, {8, 3}, {7, 3}, {6, 3}, {5, 3}, {4, 3},  {3, 3},  {2, 2}
};
static const vec2i HORSE_DESTINATION_2[] = {
    {12, 3}, {11, 3}, {10, 3}, {9, 3}, {8, 3}, {7, 3}, {6, 3}, {5, 3}, {4, 3},  {3, 3},  {2, 2},
    {2, 1},  {3, 1},  {4, 1},  {5, 1}, {6, 1}, {7, 1}, {8, 1}, {9, 1}, {10, 1}, {11, 1}, {12, 2}
};

static const int SHEEP_IMAGE_OFFSETS[] = {
    0, 0, 1, 1, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,  3,  3,  3,  3,  3,  3,  3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 5, 5, -1, -1, -1, -1, -1, -1, -1, -1,
    0, 0, 1, 1, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,  3,  3,  3,  3,  3,  3,  3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,  3,  3,  3,  4,  4,  5,  5
};

enum E_HORSE { HORSE_CREATED = 0, HORSE_RACING = 1, HORSE_FINISHED = 2 };

bool figure_herd_roost(figure* f, int step, int bias, int max_dist, int terrain_mask) {
    OZZY_PROFILER_SECTION("Figure/Herd Rooost");
    if (!f->formation_id) {
        return false;
    }

    formation* m = formation_get(f->formation_id);
    if (m->home.x() <= 0 || m->home.y() <= 0) {
        m->home = f->tile;
    }
    tile2i dest = random_around_point(m->home, f->tile, step, bias, max_dist);

    if (!map_terrain_is(dest.grid_offset(), terrain_mask)) { // todo: fix gardens
        f->destination_tile = dest;
        return true;

    } else {
        f->destination_tile.set(0, 0);
        return false;
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
    //if (!city_entertainment_hippodrome_has_race()) {
        return;
    //}

    for (int i = 1; i < MAX_FIGURES; i++) {
        figure* f = figure_get(i);
        if (f->state == FIGURE_STATE_ALIVE && f->type == FIGURE_CHARIOR_RACER) {
            f->wait_ticks_missile = 0;
            set_horse_destination(HORSE_CREATED);
        }
    }
}

void figure_animal::herd_moved() {
    base.advance_action(14);
}

void figure_animal::herd_rest() {
    base.advance_action(196);
}

void figure_animal::moveto(tile2i tile) {
    base.advance_action(16);
}
