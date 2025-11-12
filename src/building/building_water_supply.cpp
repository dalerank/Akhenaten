#include "building/building_water_supply.h"

#include "grid/desirability.h"
#include "grid/terrain.h"
#include "grid/building_tiles.h"
#include "window/building/common.h"
#include "city/city_warnings.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_water_supply);

void building_water_supply::update_month() {
    int avg_desirability = g_desirability.get_avg(tile(), 4);
    base.fancy_state = (avg_desirability > 30) ? efancy_good : efancy_normal;
    const xstring &animkey = (base.fancy_state == efancy_good) ? animkeys().fancy : animkeys().base;
    const animation_t &anim = this->anim(animkey);
    map_building_tiles_add(id(), tile(), 2, anim.first_img(), TERRAIN_BUILDING);
}

void building_water_supply::update_graphic() {
    const xstring &animwork = (base.fancy_state == efancy_good) ? animkeys().fancy_work : animkeys().base_work;
    set_animation(animwork);

    building_impl::update_graphic();
}

void building_water_supply::spawn_figure() {
    if (!base.has_water_access) {
        base.show_on_problem_overlay = 2;
    }

    common_spawn_roamer(FIGURE_WATER_CARRIER, current_params().min_houses_coverage, ACTION_125_ROAMER_ROAMING);

    //    check_labor_problem();
    //    if (has_figure_of_type(FIGURE_WATER_CARRIER))
    //        return;
    //    map_point road;
    //    if (map_has_road_access(x, y, size, &road)) {
    //        spawn_labor_seeker(100);
    //        int pct_workers = worker_percentage();
    //        int spawn_delay;
    //        if (pct_workers >= 100)
    //            spawn_delay = 0;
    //        else if (pct_workers >= 75)
    //            spawn_delay = 1;
    //        else if (pct_workers >= 50)
    //            spawn_delay = 3;
    //        else if (pct_workers >= 25)
    //            spawn_delay = 7;
    //        else if (pct_workers >= 1)
    //            spawn_delay = 15;
    //        else
    //            return;
    //        figure_spawn_delay++;
    //        if (figure_spawn_delay > spawn_delay) {
    //            figure_spawn_delay = 0;
    //            figure *f = figure_create(FIGURE_WATER_CARRIER, road.x, road.y, DIR_0_TOP_RIGHT);
    //            f->action_state = ACTION_1_ROAMING;
    //            f->home() = b;
    //            figure_id = f->id;
    //        }
    //    }
}

bool building_water_supply::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    return true;
}

void building_water_supply::on_place_checks() {
    construction_warnings warnings;

    int has_water = map_terrain_is(tile(), TERRAIN_GROUNDWATER);
    warnings.add_if(!has_water, "#needs_groundwater");
}
