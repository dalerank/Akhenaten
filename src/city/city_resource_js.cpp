#include "city/city_resource.h"

#include "core/profiler.h"
#include "game/game_events.h"
#include "js/js_game.h"
#include "city/city.h"

int __city_yards_stored(int resource) {
    return g_city.resource.yards_stored((e_resource)resource);
}
ANK_FUNCTION_1(__city_yards_stored)

void __cheat_add_resource(int resource, int amount) {
    city_resource_add_items((e_resource)resource, amount);
    city_resource_was_added_warning((e_resource)resource);
}
ANK_FUNCTION_2(__cheat_add_resource)

int __city_resources_count() {
    return (int)resource_list::all.size() - 1;
}
ANK_FUNCTION(__city_resources_count)

e_resource __city_resource_at(int index) {
    return resource_list::all.at(index).type;
}
ANK_FUNCTION_1(__city_resource_at)

void __city_resource_set_produce(int resource, bool val) {
    g_city.set_produce_resource((e_resource)resource, val);
    if ((e_resource)resource == RESOURCE_FISH) {
        if (val) {
            g_city.fishing_points.reset();
        } else {
            g_city.fishing_points.clear();
        }
    }
}
ANK_FUNCTION_2(__city_resource_set_produce)

pcstr __city_resource_name(int resource) {
    return resource_name((e_resource)resource);
}
ANK_FUNCTION_1(__city_resource_name)