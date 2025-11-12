#include "building_library.h"

#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_library)

void building_library::spawn_figure() {
    common_spawn_roamer(FIGURE_LIBRARIAN, current_params().min_houses_coverage, (e_figure_action)ACTION_125_ROAMER_ROAMING);
    check_labor_problem();
    //    if (has_figure_of_type(FIGURE_LIBRARIAN))
    //        return;
    //    map_point road;
    //    if (map_has_road_access(x, y, size, &road)) {
    //        spawn_labor_seeker(50);
    //        int spawn_delay = figure_spawn_timer();
    //        if (spawn_delay == -1)
    //            return;
    //        figure_spawn_delay++;
    //        if (figure_spawn_delay > spawn_delay) {
    //            figure_spawn_delay = 0;
    //            create_roaming_figure(road.x, road.y, FIGURE_LIBRARIAN);
    //        }
    //    }
}
