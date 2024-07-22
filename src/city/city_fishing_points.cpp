#include "city_fishing_points.h"

#include "scenario/scenario.h"
#include "scenario/map.h"
#include "figuretype/figure_fishing_point.h"
#include "grid/water.h"
#include <time.h>

void city_fishing_points_t::create() {
    scenario_map_foreach_fishing_point([] (tile2i tile) {
        figure_fishing_point::create(tile);
    });
}

tile2i city_fishing_points_t::closest_fishing_point(tile2i pos) {
    int num_fishing_spots = 0;
    for (int i = 0; i < MAX_FISH_POINTS; i++) {
        if (g_scenario_data.fishing_points[i].x() > 0)
            num_fishing_spots++;
    }

    if (num_fishing_spots <= 0) {
        return tile2i::invalid;
    }

    int min_dist = 10000;
    int min_fish_id = 0;
    for (int i = 0; i < MAX_FISH_POINTS; i++) {
        if (g_scenario_data.fishing_points[i].x() > 0) {
            int dist = calc_maximum_distance(pos, g_scenario_data.fishing_points[i]);
            if (dist < min_dist) {
                min_dist = dist;
                min_fish_id = i;
            }
        }
    }

    if (min_dist < 10000) {
        return g_scenario_data.fishing_points[min_fish_id];
    }

    return tile2i::invalid;
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

        figure_fishing_point *fish_point = figure_get(i)->dcast_fishing_point();
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
        if (g_scenario_data.fishing_points[i].x() > 0)
            num_fishing_spots++;

        g_scenario_data.fishing_points[i] = {-1, -1};
    }

    if (points_num >= 0) {
        num_fishing_spots = std::min(MAX_FISH_POINTS, points_num);
    }

    tile_cache &river = river_tiles();
    std::vector<int> deep_water;
    for (const auto &tile : river) {
        if (map_terrain_is(tile, TERRAIN_DEEPWATER)) {
            deep_water.push_back(tile);
        }
    }

    srand (time(nullptr));

    for (int i = 0; i < num_fishing_spots; i++) {
        int index = rand() % deep_water.size();
        g_scenario_data.fishing_points[i] = tile2i(deep_water[index]);
    }

    create();
}