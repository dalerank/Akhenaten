#include "building_library.h"

struct library_model : public buildings::model_t<building_library> {
} library_m;


void building_library::spawn_figure() {
    common_spawn_roamer(FIGURE_LIBRARIAN, 50, FIGURE_ACTION_125_ROAMING);
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
