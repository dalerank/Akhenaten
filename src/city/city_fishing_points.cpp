#include "city_fishing_points.h"

#include "scenario/scenario.h"
#include "scenario/map.h"
#include "figuretype/figure_fishing_point.h"
#include "city/city_figures.h"
#include "grid/water.h"
#include "grid/figure.h"
#include "grid/terrain.h"

#include <algorithm>
#include <random>
#include <time.h>

void city_fishing_points_t::create() {
    scenario_map_foreach_fishing_point([] (tile2i tile) {
        figure_fishing_point::create(tile);
    });
}

tile2i city_fishing_points_t::random_fishing_point(tile2i pos, bool free_only) {
    const auto &fpoints = g_scenario.fishing_points;

    svector<tile2i, MAX_FISH_POINTS> apoints;
    std::copy_if(std::begin(fpoints), std::end(fpoints), std::back_inserter(apoints), [] (auto p) { return p.x() > 0; });

    if (apoints.empty()) {
        return tile2i::invalid;
    }

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(std::begin(apoints), std::end(apoints), g);
    for (auto p: apoints) {
        if (free_only) {
            grid_area area = map_grid_get_area(p, 1, 1);
            tile2i result = area.find_if([] (const tile2i &tt) {
                return map_has_figure_types_at(tt, make_array(FIGURE_FISHING_BOAT));
            });

            if (result.valid()) {
                continue;
            }
        }

        return p;
    }

    return tile2i::invalid;
}

tile2i city_fishing_points_t::closest_fishing_point(tile2i pos, bool free_only) {
    const auto &fpoints = g_scenario.fishing_points;
    
    svector<tile2i, MAX_FISH_POINTS> apoints;
    std::copy_if(std::begin(fpoints), std::end(fpoints), std::back_inserter(apoints), [] (auto p) { return p.x() > 0; });

    if (apoints.empty()) {
        return tile2i::invalid;
    }

    int min_dist = 10000;
    tile2i result;
    for (auto p: apoints) {
        int dist = calc_maximum_distance(pos, p);

        if (free_only) {
            grid_area area = map_grid_get_area(pos, 1, 1);
            tile2i result = area.find_if([] (const tile2i &tt) {
                return map_has_figure_types_at(tt, make_array(FIGURE_FISHING_BOAT));
            });

            dist += result.valid() ? 100 : 0;
        }

        if (dist < min_dist) {
            min_dist = dist;
            result = p;
        }
    }

    return (min_dist < 10000) ? result : tile2i::invalid;
}

void city_fishing_points_t::reset() {
    tile_cache &river = river_tiles();
    int num_points = std::max<int>(1, (int)river.size() / 500);
    update(num_points);
}

void city_fishing_points_t::clear() {
    for (int i = 1; i < MAX_FIGURES; i++) {
        if (figure_get(i)->type == FIGURE_NONE) {
            continue;
        }

        figure_fishing_point *fish_point = figure_get<figure_fishing_point>(i);
        if (!fish_point) {
            continue;
        }

        fish_point->poof();
    }
}

void city_fishing_points_t::update(int points_num) {
    clear();

    int num_fishing_spots = 0;
    for (int i = 0; i < MAX_FISH_POINTS; i++) {
        if (g_scenario.fishing_points[i].x() > 0)
            num_fishing_spots++;

        g_scenario.fishing_points[i] = {-1, -1};
    }

    if (points_num >= 0) {
        num_fishing_spots = std::min<uint8_t>(MAX_FISH_POINTS, points_num);
    }

    tile_cache &river = river_tiles();
    std::vector<int> deep_water;
    for (const auto &tile : river) {
        if (map_terrain_is(tile, TERRAIN_DEEPWATER) && !map_terrain_is(tile, TERRAIN_FLOODPLAIN)) {
            deep_water.push_back(tile);
        }
    }

    srand (time(nullptr));

    for (int i = 0; i < num_fishing_spots; i++) {
        int index = rand() % deep_water.size();
        g_scenario.fishing_points[i] = tile2i(deep_water[index]);
    }

    create();
}