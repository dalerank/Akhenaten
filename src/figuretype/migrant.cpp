#include "migrant.h"

#include "building/building_house.h"
#include "building/model.h"
#include "city/map.h"
#include "city/population.h"
#include "city/city.h"
#include "core/calc.h"
#include "core/random.h"
#include "core/profiler.h"
#include "figure/combat.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "grid/road_access.h"
#include "grid/terrain.h"

void figure::update_direction_and_image() {
    //    figure_image_update(image_id_from_group(GROUP_FIGURE_MIGRANT));
    if (action_state == FIGURE_ACTION_2_IMMIGRANT_ARRIVING || action_state == FIGURE_ACTION_6_EMIGRANT_LEAVING) {
        int dir = figure_image_direction();
        cart_image_id = image_id_from_group(GROUP_FIGURE_IMMIGRANT_CART) + dir;
        figure_image_set_cart_offset((dir + 4) % 8);
    }
}

int figure_closest_house_with_room(tile2i tile) {
    int min_dist = 1000;
    int min_building_id = 0;
    int max_id = building_get_highest_id();
    for (int i = 1; i <= max_id; i++) {
        building* b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->house_size && b->distance_from_entry > 0
            && b->house_population_room > 0) {
            if (!b->has_figure(2)) {
                int dist = calc_maximum_distance(tile, b->tile);
                if (dist < min_dist) {
                    min_dist = dist;
                    min_building_id = i;
                }
            }
        }
    }
    return min_building_id;
}

void figure_add_house_population(building* house, int num_people) {
    int max_people = model_get_house(house->subtype.house_level)->max_people;
    if (house->house_is_merged)
        max_people *= 4;

    int room = max_people - house->house_population;
    if (room < 0)
        room = 0;

    if (room < num_people)
        num_people = room;

    if (!house->house_population) {
        building_house_change_to(house, BUILDING_HOUSE_CRUDE_HUT);
    }

    house->house_population += num_people;
    house->house_population_room = max_people - house->house_population;
    city_population_add(num_people);
    house->remove_figure(2);
}