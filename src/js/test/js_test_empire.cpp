#include "js/test/js_test_common.h"

#include "empire/empire.h"
#include "empire/empire_markers.h"
#include "empire/empire_object.h"

// A route through three way points with the step the empire file gives every route (5).
static bool __test_empire_route_set(int route_id, int route_type, vec2i a, vec2i b, vec2i c) {
    if (route_id <= 0 || route_id >= 50) {
        return false;
    }
    map_route_object& route = g_empire.ref_route_object(route_id);
    route = {};
    route.in_use = true;
    route.route_type = (char)route_type;
    route.unk_header[0] = 5;
    const vec2i points[] = {a, b, c};
    for (int i = 0; i < 3; i++) {
        route.points[i].p = points[i];
        route.points[i].is_in_use = true;
    }
    route.num_points = 3;
    route.path_length = route.calc_length();
    return true;
}
ANK_FUNCTION_5(__test_empire_route_set);

static int __test_empire_route_path_length(int route_id) {
    return g_empire.get_route_object(route_id).path_length;
}
ANK_FUNCTION_1(__test_empire_route_path_length);

static int __test_empire_route_travel_months(int route_id) {
    return g_empire.get_route_object(route_id).travel_months();
}
ANK_FUNCTION_1(__test_empire_route_travel_months);

static vec2i __test_empire_route_path_point(int route_id, int index) {
    return g_empire.get_route_object(route_id).path_point(index);
}
ANK_FUNCTION_2(__test_empire_route_path_point);

// The markers as the map would draw them with the animation counter at `anim_counter`.
static void __test_empire_markers_rebuild(int anim_counter) {
    g_empire_markers.anim_counter = anim_counter;
    g_empire_markers.rebuild();
}
ANK_FUNCTION_1(__test_empire_markers_rebuild);
