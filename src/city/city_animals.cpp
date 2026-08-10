#include "city_animals.h"

#include "city/city.h"
#include "core/log.h"
#include "core/random.h"
#include "figuretype/figure_animal.h"
#include "figuretype/animal_hyena.h"
#include "js/js_game.h"
#include "grid/terrain.h"
#include "grid/soldier_strength.h"
#include "grid/hyena_strength.h"
#include "grid/grid.h"
#include "grid/routing/routing.h"
#include "grid/routing/routing_terrain.h"
#include "city/city_figures.h"
#include "game/game_config.h"
#include "figure/figure.h"
#include "figure/formation_enemy.h"
#include "scenario/map.h"
#include "scenario/scenario.h"
#include "dev/debug.h"

declare_console_var_bool(allow_span_ostrich, true)

e_figure_type climate_prey_type() {
    switch (g_scenario.climate) {
    case CLIMATE_CENTRAL:
        return FIGURE_ANTELOPE;
    case CLIMATE_NORTHERN:
        return FIGURE_BIRDS;
    case CLIMATE_DESERT:
        return FIGURE_OSTRICH;
    default:
        return FIGURE_NONE;
    }
}

// Pre-Cleopatra / maps without prey points: one climate animal on killer-point slots.
e_figure_type climate_legacy_animal_type() {
    switch (g_scenario.climate) {
    case CLIMATE_CENTRAL:
        return FIGURE_ANTELOPE;
    case CLIMATE_NORTHERN:
        return FIGURE_CROCODILE;
    case CLIMATE_DESERT:
        return FIGURE_OSTRICH;
    default:
        return FIGURE_NONE;
    }
}

bool scenario_has_prey_points() {
    for (const herd_point_t &hp : g_scenario.herd_points_prey) {
        if (hp.valid()) {
            return true;
        }
    }
    return false;
}

// Cleopatra Killer Type: climate pair + alt_predator_type flag.
// Arid: hyena | scorpion; Normal: crocodile | lion; Humid: hippo | asp.
e_figure_type climate_predator_type() {
    const bool alt = g_scenario.alt_predator_type;
    switch (g_scenario.climate) {
    case CLIMATE_CENTRAL:
        return alt ? FIGURE_LION : FIGURE_CROCODILE;
    case CLIMATE_NORTHERN:
        return alt ? FIGURE_ASP : FIGURE_HIPPO;
    case CLIMATE_DESERT:
        return alt ? FIGURE_SCORPION : FIGURE_HYENA;
    default:
        return FIGURE_NONE;
    }
}

e_figure_type hunting_lodge_default_hunter_type() {
    e_figure_type prey = FIGURE_NONE;
    if (scenario_has_prey_points()) {
        prey = climate_prey_type();
    } else {
        prey = climate_legacy_animal_type();
    }

    switch (prey) {
    case FIGURE_ANTELOPE:
        return FIGURE_ANTELOPE_HUNTER;
    case FIGURE_OSTRICH:
        return FIGURE_OSTRICH_HUNTER;
    case FIGURE_BIRDS:
        return FIGURE_BIRDS_HUNTER;
    default:
        // Legacy Northern crocodile etc. — keep ostrich interim.
        return FIGURE_OSTRICH_HUNTER;
    }
}

namespace {

int herd_impassable_mask(e_figure_type herd_type) {
    switch (herd_type) {
    case FIGURE_OSTRICH:
    case FIGURE_BIRDS:
    // Cleopatra editor: scorpions / lions / asps / ostriches / antelopes → plain/meadow.
    case FIGURE_SCORPION:
    case FIGURE_LION:
    case FIGURE_ASP:
        return TERRAIN_IMPASSABLE_OSTRICH;
    case FIGURE_ANTELOPE:
        return TERRAIN_IMPASSABLE_ANTELOPE;
    case FIGURE_CROCODILE:
    case FIGURE_HIPPO:
        return TERRAIN_IMPASSABLE_HIPPO;
    case FIGURE_HYENA:
    default:
        // Hyenas: sand dunes (editor); mask matches historical hyena impassable set.
        return TERRAIN_IMPASSABLE_HYENA;
    }
}

int climate_herd_count(e_figure_type type) {
    // A herd point must never roll an empty herd — prey herds are the only food source
    // for hunting lodges, and ostrich respawn needs at least one live figure to seed from.
    switch (type) {
    case FIGURE_ANTELOPE:
        return 1 + (rand() % 10);
    case FIGURE_BIRDS:
        return 1 + (rand() % 8);
    case FIGURE_OSTRICH:
        return 1 + (rand() % 12);
    case FIGURE_CROCODILE:
    case FIGURE_HIPPO:
        return 1 + (rand() % 8);
    case FIGURE_HYENA:
    case FIGURE_SCORPION:
    case FIGURE_LION:
    case FIGURE_ASP:
        return 2 + (rand() % 5);
    default:
        return 1 + (rand() % 8);
    }
}

bool figure_is_prey(e_figure_type type) {
    return type == FIGURE_OSTRICH || type == FIGURE_ANTELOPE || type == FIGURE_BIRDS;
}

bool herd_can_travel_to(tile2i src, tile2i dst, e_figure_type herd_type) {
    switch (herd_type) {
    case FIGURE_CROCODILE:
    case FIGURE_HIPPO:
        return map_routing_amphibia_can_travel_over_land_water(src, dst, -1, 2000);
    default:
        return map_routing_noncitizen_can_travel_over_land(src, dst, -1, 2000);
    }
}

} // namespace

bool city_animals_t::is_herd_spawn_accessible(tile2i tile, e_figure_type herd_type) {
    if (!tile.valid()) {
        return false;
    }

    const int mask = herd_impassable_mask(herd_type);
    if (map_terrain_is(tile, mask)) {
        return false;
    }

    // Birds fly over the terrain, so the land-routing probe below does not apply to them.
    if (herd_type == FIGURE_BIRDS) {
        return true;
    }

    static const int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
    static const int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    static const int distances[] = {8, 12, 16};

    for (const int dist : distances) {
        for (int d = 0; d < 8; d++) {
            tile2i dest = tile.shifted(dx[d] * dist, dy[d] * dist);
            if (!dest.valid() || !map_grid_is_inside(dest, 1)) {
                continue;
            }
            if (map_terrain_is(dest, mask)) {
                continue;
            }
            if (herd_can_travel_to(tile, dest, herd_type)) {
                return true;
            }
        }
    }

    return false;
}

formation* city_animals_t::create_herd(tile2i tile, e_figure_type herd_type, int num_animals) {
    if (!is_herd_spawn_accessible(tile, herd_type)) {
        // Map points sit on the terrain the designer picked, which is not always walkable for
        // the climate animal (marsh for antelopes, dunes for hyenas). Nudge onto a neighbour
        // tile instead of dropping the herd — #624: a skipped prey herd leaves the mission
        // without any huntable wildlife.
        const tile2i original = tile;
        tile = tile2i::invalid;
        for (int radius = 1; radius <= 4 && !tile.valid(); radius++) {
            grid_area area = map_grid_get_area(original, 1, radius);
            for (int y = area.tmin_y; y <= area.tmax_y && !tile.valid(); y++) {
                for (int x = area.tmin_x; x <= area.tmax_x; x++) {
                    tile2i candidate(x, y);
                    if (is_herd_spawn_accessible(candidate, herd_type)) {
                        tile = candidate;
                        break;
                    }
                }
            }
        }

        if (!tile.valid()) {
            logs::warn("animals: herd spawn at (%d,%d) type=%d has no accessible exit - skipping",
                       original.x(), original.y(), (int)herd_type);
            return nullptr;
        }

        logs::info("animals: herd spawn at (%d,%d) type=%d moved to (%d,%d)", original.x(), original.y(),
                   (int)herd_type, tile.x(), tile.y());
    }

    formation* formation = formation_create_herd(herd_type, tile, num_animals);
    if (formation && formation->id > 0) {
        for (int fig = 0; fig < num_animals; fig++) {
            random_generate_next();

            figure *f = figure_create(herd_type, tile, DIR_0_TOP_RIGHT);
            f->formation_id = formation->id;
            f->wait_ticks = f->id & 0x1f;

            auto fanimal = f->dcast_animal();

            if (fanimal) {
                fanimal->herd_rest();
            }
        }
    }

    return formation;
}

void city_animals_t::create_herds() {
    map_routing_update_land();

    // Killer points hold predators and prey points hold prey on every map, Pharaoh and
    // Cleopatra alike — only the Killer Type pairing (alt_predator_type) is Cleopatra's.
    // Per-point type/count/radius come from mission JS (herd_point_t); zeros use climate defaults.
    auto spawn_points = [this](const auto &points, e_figure_type climate_type) {
        for (const herd_point_t &hp : points) {
            if (!hp.valid()) {
                continue;
            }
            const e_figure_type type = (hp.type != FIGURE_NONE) ? hp.type : climate_type;
            if (type == FIGURE_NONE) {
                continue;
            }
            const int count = hp.count > 0 ? hp.count : climate_herd_count(type);
            formation *m = create_herd(hp.tile, type, count);
            if (m && m->id > 0 && hp.radius > 0) {
                m->reseach_radius = hp.radius;
            }
        }
    };

    spawn_points(g_scenario.herd_points_prey, climate_prey_type());
    spawn_points(g_scenario.herd_points_predator, climate_predator_type());

    emit(esid(__func__));
}

bool city_animals_t::get_free_tile(int x, int y, int allow_negative_desirability, tile2i &outtile) {
    unsigned int disallowed_terrain = ~(TERRAIN_ACCESS_RAMP | TERRAIN_MEADOW);
    bool tile_found = false;
    tile2i tfound;
    grid_area area = map_grid_get_area(tile2i(x, y), 1, 4);

    for (int yy = area.tmin_y, endy = area.tmax_y; yy <= endy; yy++) {
        for (int xx = area.tmin_x, endx = area.tmax_x; xx <= endx; xx++) {
            int grid_offset = MAP_OFFSET(xx, yy);
            if (!map_terrain_is(grid_offset, disallowed_terrain)) {
                if (map_soldier_strength_get(grid_offset)) {
                    return 0;
                }

                int desirability = g_desirability.get(grid_offset);
                if (allow_negative_desirability) {
                    if (desirability > 1) {
                        return false;
                    }

                } else if (desirability) {
                    return false;
                }

                tile_found = true;
                tfound = tile2i(xx, yy);
            }
        }
    }
    outtile = tfound;
    return tile_found;
}

bool city_animals_t::get_roaming_destination(int formation_id, int allow_negative_desirability, tile2i tile, int distance, int direction, tile2i &outtile) {
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
            return true;
        }

        target_direction += 2;
        if (target_direction > 6)
            target_direction = 0;
    }
    return false;
}

void city_animals_t::add_animals_point(int index, int x, int y, e_figure_type ftype, int num) {
    if (index < 0 || index > UINT8_MAX) {
        return;
    }

    formation *m = create_herd(tile2i{ x, y }, ftype, num);
    if (!m || m->id <= 0) {
        return;
    }

    m->herd_point = index;

    // Prey belongs in the prey array, or the mission reads as predator-only and the hunting
    // lodge resolves the wrong hunter. Record the tile the herd actually got, not the
    // requested one — create_herd() may have nudged it onto walkable ground.
    const bool prey = figure_is_prey(ftype);
    auto &points = prey ? g_scenario.herd_points_prey : g_scenario.herd_points_predator;
    const size_t capacity = prey ? MAX_PREY_HERD_POINTS : MAX_PREDATOR_HERD_POINTS;
    if (points.size() >= capacity) {
        logs::warn("animals: no free %s point slot for herd at (%d,%d)", prey ? "prey" : "killer", m->tile.x(),
                   m->tile.y());
        return;
    }

    herd_point_t hp;
    hp.tile = m->tile;
    hp.type = ftype;
    hp.count = (int16_t)num;
    points.push_back(hp);
}

void city_animals_t::set_animals_area(int index, int reseach_radius) {
    formation *m = g_formations.get_from_herd(index);
    if (m->id > 0) {
        m->reseach_radius = reseach_radius;
    }
}

void city_animals_t::move_animals(const formation *m, int attacking_animals, int terrain_mask) {
    for (int i = 0; i < formation::max_figures_count; i++) {
        if (m->figures[i] <= 0)
            continue;

        figure *f = figure_get(m->figures[i]);
        auto fanimal = f->dcast_animal();

        if (!fanimal) {
            continue;
        }

        if (f->action_state == FIGURE_ACTION_149_CORPSE) {
            continue;
        }

        if (attacking_animals) {
            int target_id = figure_combat_get_target_for_hyena(f->tile, 6);
            if (target_id) {
                f->destination_tile.set(0, 0);
                figure_herd_roost(f, 4, 8, 22, terrain_mask);
                if (f->destination_tile.x() != 0 && f->destination_tile.y() != 0) {
                    fanimal->moveto(f->destination_tile);
                }
            } else {
                fanimal->herd_moved();
                fanimal->base.destination_tile = tile2i::invalid;
            }
        } else {
            fanimal->herd_rest();
        }
    }
}

bool city_animals_t::can_spawn_ph_wolf(formation *m) {
    return false;
}

bool city_animals_t::can_spawn_ostrich(formation *m) {
    if (m->num_figures < m->max_figures && m->figure_type == FIGURE_OSTRICH) {
        m->herd_spawn_delay++;
        int delay = 4;
        if (m->herd_spawn_delay > delay) {
            m->herd_spawn_delay = 0;
            return true;
        }
    }
    return false;
}

void city_animals_t::set_herd_figures_to_initial(const formation *m) {
    for (int i = 0; i < formation::max_figures_count; i++) {
        if (m->figures[i] > 0) {
            figure *f = figure_get(m->figures[i]);
            if (!f->is_alive()) {
                continue;
            }

            f->dcast()->formation_reset_to_initial(m);
        }
    }
}

void city_animals_t::update_herd_formation(formation *m) {
    if (can_spawn_ph_wolf(m)) {
        // spawn new wolf
        if (!map_terrain_is(m->tile, TERRAIN_IMPASSABLE_HYENA)) {
            figure *wolf = figure_create(m->figure_type, m->tile, DIR_0_TOP_RIGHT);
            wolf->action_state = 24;
            wolf->formation_id = m->id;
            wolf->wait_ticks = wolf->id & 0x1f;

            auto fanimal = wolf->dcast_animal();
            if (fanimal) {
                fanimal->herd_rest();
            }
        }
    }

    if (can_spawn_ostrich(m) && allow_span_ostrich()) {
        if (m->failed_creation_count > 10) {
            m->home = random_around_point(m->home, m->home, /*step*/4, /*bias*/8, /*max_dist*/32);
        }

        bool is_passible = !map_terrain_is(m->tile, TERRAIN_IMPASSABLE_OSTRICH);
        bool valid_tile = m->tile.valid();
        if (is_passible && valid_tile) {
            figure *ostrich = figure_create(m->figure_type, m->tile, DIR_0_TOP_RIGHT);
            ostrich->formation_id = m->id;
            ostrich->wait_ticks = ostrich->id & 0x1f;
            m->failed_creation_count = 0;

            auto fanimal = ostrich->dcast_animal();
            if (fanimal) {
                fanimal->herd_rest();
            }
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
        if (figure_id > 0 && figure_get(figure_id)->in_attack())
            attacking_animals++;
    }

    if (m->missile_attack_timeout) {
        attacking_animals = 1;
        m->missile_attack_timeout--;
    }

    int roam_distance;
    int roam_delay;
    int allow_negative_desirability;
    const int terrain_mask = herd_impassable_mask(m->figure_type);
    switch (m->figure_type) {
    case FIGURE_BIRDS:
        roam_distance = 8;
        roam_delay = 20;
        allow_negative_desirability = 0;
        attacking_animals = 0;
        break;
    case FIGURE_ANTELOPE:
        roam_distance = 20;
        roam_delay = 4;
        allow_negative_desirability = 0;
        attacking_animals = 0;
        break;
    case FIGURE_OSTRICH:
        roam_distance = 16;
        //            roam_delay = 6;
        roam_delay = 9;
        allow_negative_desirability = 1;
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
            set_herd_figures_to_initial(m);

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

void city_animals_t::remove_all() {
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation *m = formation_get(i);
        if (m->in_use && m->is_herd) {
            m->in_use = false;

            for (auto f : m->valid_figures()) {
                f->poof();
            }
        }
    }

    figure_valid_do([] (figure &f) {
        f.poof();
    }, make_array(FIGURE_CROCODILE, FIGURE_OSTRICH, FIGURE_ANTELOPE, FIGURE_HYENA, FIGURE_BIRDS,
                  FIGURE_HIPPO, FIGURE_LION, FIGURE_SCORPION, FIGURE_ASP));

    g_scenario.herd_points_prey.clear();
    g_scenario.herd_points_predator.clear();
}

void city_animals_t::update() {
    const bool has_animals = g_scenario.env.has_animals || !!game_features::gameplay_change_hasanimals;
    if (!has_animals) {
        return;
    }

    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation *m = formation_get(i);
        if (m->in_use && m->is_herd && m->max_figures > 0) {
            update_herd_formation(m);
        }
    }

    // Update hyena strength grid
    map_hyena_strength_update();
}

bool city_animals_t::breeding_ground_at(tile2i tile, int size) {
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation *m = formation_get(i);
        if (m->in_use && m->is_herd) {
            if (m->tile.x() >= tile.x() && m->tile.x() < tile.x() + size && m->tile.y() >= tile.y() && m->tile.y() < tile.y() + size)
                return true;
        }
    }
    return false;
}