#include "building/building_water_supply.h"

#include "grid/desirability.h"
#include "grid/terrain.h"
#include "graphics/image_desc.h"
#include "grid/building_tiles.h"
#include "window/building/common.h"
#include "widget/city/ornaments.h"
#include "graphics/elements/ui.h"
#include "window/window_building_info.h"
#include "city/labor.h"
#include "city/warnings.h"
#include "js/js_game.h"

struct info_window_water_supply : building_info_window {
    virtual void window_info_background(object_info &c) override;
    virtual bool check(object_info &c) override {
        return c.building_get()->dcast_water_supply();
    }
};

buildings::model_t<building_water_supply> water_supply_m;
info_window_water_supply water_supply_infow;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_water_supply);
void config_load_building_water_supply() {
    water_supply_infow.load("building_info_window");
}

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

    common_spawn_roamer(FIGURE_WATER_CARRIER, 50, FIGURE_ACTION_125_ROAMING);

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

void info_window_water_supply::window_info_background(object_info &c) {
    building_info_window::window_info_background(c);

    building* b = c.building_get();

    std::pair<int, int> reason = { c.group_id, 1 };
    std::pair<int, int> workers = { c.group_id, 0 };
    if (!b->has_road_access) {
        reason = { 69, 25 };
    } else {
        workers.second = approximate_value(c.worker_percentage / 100.f, make_array(7, 5, 4, 3, 2));
    }

    ui["warning_text"] = ui::str(reason.first, reason.second);
    ui["workers_desc"] = ui::str(workers.first, workers.second);

    draw_employment_details_ui(ui, c, b, -1);
}

void building_water_supply::on_place_checks() {
    if (building_construction_has_warning()) {
        return;
    }

    int has_water = map_terrain_is(tile(), TERRAIN_GROUNDWATER);
    if (!has_water) {
        building_construction_warning_show(WARNING_WATER_PIPE_ACCESS_NEEDED);
    }
}
