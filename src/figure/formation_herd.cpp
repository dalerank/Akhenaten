#include "formation_herd.h"

#include "city/city.h"
#include "city/sound.h"
#include "core/random.h"
#include "empire/empire_city.h"
#include "figure/combat.h"
#include "figure/figure.h"
#include "figure/formation.h"
#include "figuretype/figure_hyena.h"
#include "figure/formation_enemy.h"
#include "figure/route.h"
#include "grid/desirability.h"
#include "grid/grid.h"
#include "grid/soldier_strength.h"
#include "grid/terrain.h"
#include "grid/water.h"
#include "sound/effect.h"
#include "dev/debug.h"
#include "game/game_config.h"
#include "js/js_game.h"

#include <vector>
#include <time.h>

declare_console_var_bool(allow_span_ostrich, true)

animal_herds_t ANK_VARIABLE_N(g_animal_herds, "animal_herds");

static int get_free_tile(int x, int y, int allow_negative_desirability, tile2i &outtile) {
    unsigned int disallowed_terrain = ~(TERRAIN_ACCESS_RAMP | TERRAIN_MEADOW);
    bool tile_found = false;
    tile2i tfound;
    grid_area area = map_grid_get_area(tile2i(x, y), 1, 4);

    for (int yy = area.tmin.y(), endy = area.tmax.y(); yy <= endy; yy++) {
        for (int xx = area.tmin.x(), endx = area.tmax.x(); xx <= endx; xx++) {
            int grid_offset = MAP_OFFSET(xx, yy);
            if (!map_terrain_is(grid_offset, disallowed_terrain)) {
                if (map_soldier_strength_get(grid_offset)) {
                    return 0;
                }

                int desirability = g_desirability.get(grid_offset);
                if (allow_negative_desirability) {
                    if (desirability > 1) {
                        return 0;
                    }

                } else if (desirability) {
                    return 0;
                }

                tile_found = 1;
                tfound = tile2i(xx, yy);
            }
        }
    }
    outtile = tfound;
    return tile_found;
}

static int get_roaming_destination(int formation_id, int allow_negative_desirability, tile2i tile, int distance, int direction, tile2i &outtile) {
    int target_direction = (formation_id + random_byte()) & 6;
    if (direction) {
        target_direction = direction;
        allow_negative_desirability = 1;
    }
    int x = tile.x();
    int y = tile.y();
    for (int i = 0; i < 4; i++) {
        int x_target, y_target;
        switch (target_direction) {
        case DIR_0_TOP_RIGHT:
            x_target = x;
            y_target = y - distance;
            break;
        case DIR_1_RIGHT:
            x_target = x + distance;
            y_target = y - distance;
            break;
        case DIR_2_BOTTOM_RIGHT:
            x_target = x + distance;
            y_target = y;
            break;
        case DIR_3_BOTTOM:
            x_target = x + distance;
            y_target = y + distance;
            break;
        case DIR_4_BOTTOM_LEFT:
            x_target = x;
            y_target = y + distance;
            break;
        case DIR_5_LEFT:
            x_target = x - distance;
            y_target = y + distance;
            break;
        case DIR_6_TOP_LEFT:
            x_target = x - distance;
            y_target = y;
            break;
        case DIR_7_TOP:
            x_target = x - distance;
            y_target = y - distance;
            break;
        default:
            continue;
        }
        if (x_target <= 0)
            x_target = 1;
        else if (y_target <= 0)
            y_target = 1;
        else if (x_target >= scenario_map_data()->width - 1)
            x_target = scenario_map_data()->width - 2;
        else if (y_target >= scenario_map_data()->height - 1)
            y_target = scenario_map_data()->height - 2;

        if (get_free_tile(x_target, y_target, allow_negative_desirability, outtile)) {
            return 1;
        }

        target_direction += 2;
        if (target_direction > 6)
            target_direction = 0;
    }
    return 0;
}

static void move_animals(const formation* m, int attacking_animals, int terrain_mask) {
    for (int i = 0; i < formation::max_figures_count; i++) {
        if (m->figures[i] <= 0)
            continue;

        figure* f = figure_get(m->figures[i]);
        if (f->action_state == FIGURE_ACTION_149_CORPSE || f->action_state == FIGURE_ACTION_150_ATTACK) {
            continue;
        }

        if (attacking_animals) {
            int target_id = figure_combat_get_target_for_hyena(f->tile, 6);
            if (target_id) {
                f->destination_tile.set(0, 0);
                figure_herd_roost(f, 4, 8, 22, terrain_mask);
                if (f->destination_tile.x() != 0 && f->destination_tile.y() != 0) {
                    auto fanimal = f->dcast_animal();
                    if (fanimal) {
                        fanimal->moveto(f->destination_tile);
                    } else {
                        f->advance_action(16);
                    }
                }
            } else {
                auto fanimal = f->dcast_animal();
                if (fanimal) {
                    fanimal->herd_moved();
                } else {
                    f->advance_action(14);
                }
                f->destination_tile.set(0, 0);
            }
        } else {
            f->action_state = FIGURE_ACTION_196_HERD_ANIMAL_AT_REST;
        }
    }
}

static bool can_spawn_ph_wolf(formation* m) {
    return false;
}

/*static int can_spawn_wolf(formation *m) {
    if (m->num_figures < m->max_figures && m->figure_type == FIGURE_WOLF) {
        m->herd_wolf_spawn_delay++;
        int delay = 32;
        if (GAME_ENV == ENGINE_ENV_PHARAOH)
            delay = 4;
        if (m->herd_wolf_spawn_delay > delay) {
            m->herd_wolf_spawn_delay = 0;
            return 1;
        }
    }
    return 0;
}*/

static bool can_spawn_ostrich(formation* m) {
    if (m->num_figures < m->max_figures && m->figure_type == FIGURE_OSTRICH) {
        m->herd_ostrich_spawn_delay++;
        int delay = 4;
        if (m->herd_ostrich_spawn_delay > delay) {
            m->herd_ostrich_spawn_delay = 0;
            return true;
        }
    }
    return false;
}

static void set_figures_to_initial(const formation* m) {
    for (int i = 0; i < formation::max_figures_count; i++) {
        if (m->figures[i] > 0) {
            figure* f = figure_get(m->figures[i]);
            if (f->action_state != FIGURE_ACTION_149_CORPSE && f->action_state != FIGURE_ACTION_150_ATTACK
                && f->action_state != ACTION_16_FLEEING) {
                f->action_state = FIGURE_ACTION_151_ENEMY_INITIAL;
                f->wait_ticks = 0;

                // ostriches!
                random_generate_next();
                f->wait_ticks = 255 + (random_byte()) - 64;
                if (f->type == FIGURE_OSTRICH) {
                    f->action_state = 18 + (random_byte() & 0x1);
                }
            }
        }
    }
}

void animal_herds_t::update_herd_formation(formation* m) {
    if (can_spawn_ph_wolf(m)) {
        // spawn new wolf
        if (!map_terrain_is(m->tile, TERRAIN_IMPASSABLE_WOLF)) {
            figure* wolf = figure_create(m->figure_type, m->tile, DIR_0_TOP_RIGHT);
            wolf->action_state = FIGURE_ACTION_196_HERD_ANIMAL_AT_REST;
            wolf->action_state = 24;
            wolf->formation_id = m->id;
            wolf->wait_ticks = wolf->id & 0x1f;
        }
    }

    if (can_spawn_ostrich(m) && allow_span_ostrich()) {
        if (m->failed_creation_count > 10) {
            m->home = random_around_point(m->home, m->home, /*step*/4, /*bias*/8, /*max_dist*/32);
        }

        bool is_passible = !map_terrain_is(m->tile, TERRAIN_IMPASSABLE_OSTRICH);
        bool valid_tile = m->tile.valid();
        if (is_passible && valid_tile) {
            figure* ostrich = figure_create(m->figure_type, m->tile, DIR_0_TOP_RIGHT);
            ostrich->advance_action(FIGURE_ACTION_196_HERD_ANIMAL_AT_REST);
            ostrich->formation_id = m->id;
            ostrich->wait_ticks = ostrich->id & 0x1f;
            m->failed_creation_count = 0;
        } else {
            m->tile = random_around_point(m->home, m->home, /*step*/4, /*bias*/8, /*max_dist*/32);

            bool is_passible = !map_terrain_is(m->tile, TERRAIN_IMPASSABLE_OSTRICH);
            bool valid_tile = m->tile.valid();

            m->failed_creation_count += !(is_passible && valid_tile) ? 1 : 0;
        }
    }

    int attacking_animals = 0;
    for (int fig = 0; fig < formation::max_figures_count; fig++) {
        int figure_id = m->figures[fig];
        if (figure_id > 0 && figure_get(figure_id)->action_state == FIGURE_ACTION_150_ATTACK)
            attacking_animals++;
    }

    if (m->missile_attack_timeout) {
        attacking_animals = 1;
        m->missile_attack_timeout--;
    }
    //if (m->figures[0] && GAME_ENV != ENGINE_ENV_PHARAOH) {
    //    figure* f = figure_get(m->figures[0]);
    //    if (f->state == FIGURE_STATE_ALIVE)
    //        formation_set_home(m, f->tile.x(), f->tile.y());
    //}
    int roam_distance;
    int roam_delay;
    int allow_negative_desirability;
    int terrain_mask = TERRAIN_IMPASSABLE_WOLF;
    switch (m->figure_type) {
    case FIGURE_BIRDS:
        roam_distance = 8;
        roam_delay = 20;
        allow_negative_desirability = 0;
        attacking_animals = 0;
        terrain_mask = TERRAIN_IMPASSABLE_WOLF;
        break;
    case FIGURE_ANTELOPE:
        roam_distance = 20;
        roam_delay = 4;
        allow_negative_desirability = 0;
        attacking_animals = 0;
        terrain_mask = TERRAIN_IMPASSABLE_WOLF;
        break;
    case FIGURE_OSTRICH:
        roam_distance = 16;
        //            roam_delay = 6;
        roam_delay = 9;
        allow_negative_desirability = 1;
        terrain_mask = TERRAIN_IMPASSABLE_OSTRICH;
        break;
    default:
        return;
    }
    m->wait_ticks++;
    if (m->wait_ticks > roam_delay || attacking_animals) {
        m->wait_ticks = 0;
        if (attacking_animals) {
            formation_set_destination(m, m->home);
            move_animals(m, attacking_animals, terrain_mask);
        } else {
            set_figures_to_initial(m);

            tile2i rtile;
            const bool found = get_roaming_destination(m->id, allow_negative_desirability, m->home, roam_distance, m->herd_direction, rtile);
            if (found) {
                m->herd_direction = 0;
                
                auto destination = formation_enemy_move_formation_to(m, rtile);
                if (destination.valid) {
                    formation_set_destination(m, destination.tile);
                    move_animals(m, attacking_animals, terrain_mask);
                }
            }
        }
    }
}

void animal_herds_t::update() {
    const bool has_animals = scenario_map_has_animals() || !!game_features::gameplay_change_hasanimals;
    if (!has_animals) {
        return;
    }

    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation* m = formation_get(i);
        if (m->in_use && m->is_herd && !m->batalion_id && m->max_figures > 0) {
            update_herd_formation(m);
        }
    }
}

bool formation_herd_breeding_ground_at(tile2i tile, int size) {
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation* m = formation_get(i);
        if (m->in_use && m->is_herd && !m->batalion_id) {
            if (m->tile.x() >= tile.x() && m->tile.x() < tile.x() + size && m->tile.y() >= tile.y() && m->tile.y() < tile.y() + size)
                return true;
        }
    }
    return false;
}