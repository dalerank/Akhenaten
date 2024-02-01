#include "building_jugler_school.h"

#include "building/building_entertainment.h"
#include "figuretype/entertainer.h"

void building_juggler_school::window_info_background(object_info &c) {
    building_entertainment_school_draw_info(c, "juggler_school", 77);
}

void building_juggler_school::update_month() {
    data.entertainment.spawned_entertainer_this_month = false;
}

void building_juggler_school::spawn_figure() {
    if (!common_spawn_figure_trigger(50)) {
        return;
    }

    if (data.entertainment.spawned_entertainer_this_month) {
        return;
    }

    int venue_destination = determine_venue_destination(base.road_access, BUILDING_PAVILLION, BUILDING_BANDSTAND, BUILDING_BOOTH);
    building* dest = building_get(venue_destination);
    if (dest->id > 0) {
        create_figure_with_destination(FIGURE_JUGGLER, dest, FIGURE_ACTION_92_ENTERTAINER_GOING_TO_VENUE);
        data.entertainment.spawned_entertainer_this_month = true;
    } else {
        common_spawn_roamer(FIGURE_JUGGLER, 50, FIGURE_ACTION_90_ENTERTAINER_AT_SCHOOL_CREATED);
    }
}
