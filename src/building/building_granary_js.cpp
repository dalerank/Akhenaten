#include "building_granary.h"

#include "building/building_storage.h"
#include "city/city_buildings.h"
#include "js/js_game.h"
#include "core/profiler.h"

int __granary_get_amount(int bid, int resource) {
    building_granary *granary = building_get(bid)->dcast_granary();
    return granary ? granary->amount((e_resource)resource) : 0;
}
ANK_FUNCTION_2(__granary_get_amount)

int __granary_get_total_stored(int bid) {
    building_granary *granary = building_get(bid)->dcast_granary();
    return granary ? granary->total_stored() : 0;
}
ANK_FUNCTION_1(__granary_get_total_stored)

bool __granary_is_accepting(int bid, int resource) {
    building_granary *granary = building_get(bid)->dcast_granary();
    return granary ? granary->is_accepting((e_resource)resource) : false;
}
ANK_FUNCTION_2(__granary_is_accepting)

int __granary_get_freespace(int bid) {
    building_granary *granary = building_get(bid)->dcast_granary();
    return granary ? granary->freespace() : 0;
}
ANK_FUNCTION_1(__granary_get_freespace)

bool __granary_is_empty_all(int bid) {
    building_granary *granary = building_get(bid)->dcast_granary();
    return granary ? granary->is_empty_all() : false;
}
ANK_FUNCTION_1(__granary_is_empty_all)

int __granary_resource_state(int bid, int resource) {
    building_granary *granary = building_get(bid)->dcast_granary();
    const storage_t *s = granary ? granary->storage() : nullptr;
    return s ? s->resource_state[resource] : 0;
}
ANK_FUNCTION_2(__granary_resource_state)

int __granary_resource_max_accept(int bid, int resource) {
    building_granary *granary = building_get(bid)->dcast_granary();
    const storage_t *s = granary ? granary->storage() : nullptr;
    return s ? s->resource_max_accept[resource] : 0;
}
ANK_FUNCTION_2(__granary_resource_max_accept)

int __granary_resource_max_get(int bid, int resource) {
    building_granary *granary = building_get(bid)->dcast_granary();
    const storage_t *s = granary ? granary->storage() : nullptr;
    return s ? s->resource_max_get[resource] : 0;
}
ANK_FUNCTION_2(__granary_resource_max_get)

void __granary_toggle_empty_all(int bid) {
    building_granary *granary = building_get(bid)->dcast_granary();
    if (granary) {
        building_storage_toggle_empty_all(granary->storage_id());
    }
}
ANK_FUNCTION_1(__granary_toggle_empty_all)

void __granary_accept_none(int bid) {
    building_granary *granary = building_get(bid)->dcast_granary();
    if (granary) {
        building_storage_accept_none(granary->storage_id());
    }
}
ANK_FUNCTION_1(__granary_accept_none)

void __granary_cycle_resource_state(int bid, int resource) {
    building_granary *granary = building_get(bid)->dcast_granary();
    if (granary) {
        building_storage_cycle_resource_state(granary->storage_id(), resource, false);
    }
}
ANK_FUNCTION_2(__granary_cycle_resource_state)

void __granary_increase_decrease_resource_state(int bid, int resource, bool increase) {
    building_granary *granary = building_get(bid)->dcast_granary();
    if (granary) {
        building_storage_increase_decrease_resource_state(granary->storage_id(), resource, increase);
    }
}
ANK_FUNCTION_3(__granary_increase_decrease_resource_state)

