#include "building_industry_office.h"

#include "building/building_cast.h"
#include "city/city_buildings.h"
#include "core/profiler.h"
#include "js/js_game.h"

bool __building_industry_office_is_active(int bid) {
    auto *office = building_get_ex<building_industry_office>(bid);
    return office && office->is_management_active();
}
ANK_FUNCTION_1(__building_industry_office_is_active)

int __building_industry_office_radius(int bid) {
    auto *office = building_get_ex<building_industry_office>(bid);
    return office ? office->management_radius() : 0;
}
ANK_FUNCTION_1(__building_industry_office_radius)

hvector<building_id, 64> __building_industry_office_managed_ids(int bid) {
    hvector<building_id, 64> empty;
    auto *office = building_get_ex<building_industry_office>(bid);
    if (!office) {
        return empty;
    }
    return city_buildings().find_manageable_industry_in_radius(office->tile(), office->size(),
      office->management_radius());
}
ANK_FUNCTION_1(__building_industry_office_managed_ids)

int __building_industry_office_mothball_all(int bid, bool mothball) {
    auto *office = building_get_ex<building_industry_office>(bid);
    if (!office || !office->is_management_active()) {
        return 0;
    }

    int changed = 0;
    auto ids = city_buildings().find_manageable_industry_in_radius(office->tile(), office->size(),
      office->management_radius());
    for (building_id id : ids) {
        building *b = building_get(id);
        if (!b) {
            continue;
        }
        if (mothball && b->state == BUILDING_STATE_VALID) {
            b->mothball_toggle();
            changed++;
        } else if (!mothball && b->state == BUILDING_STATE_MOTHBALLED) {
            b->mothball_toggle();
            changed++;
        }
    }
    return changed;
}
ANK_FUNCTION_2(__building_industry_office_mothball_all)
