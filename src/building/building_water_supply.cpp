#include "building/building_water_supply.h"

#include "grid/desirability.h"
#include "grid/terrain.h"
#include "graphics/image_desc.h"
#include "grid/building_tiles.h"
#include "window/building/common.h"
#include "widget/city/ornaments.h"
#include "graphics/elements/ui.h"
#include "city/labor.h"

buildings::model_t<building_water_supply> water_supply_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_water_supply);
void config_load_building_water_supply() {
    water_supply_m.load();
}

void building_water_supply::update_month() {
    int avg_desirability = map_desirabilty_avg(tile(), 4);
    base.fancy_state = (avg_desirability > 30) ? efancy_good : efancy_normal;
    pcstr anim_name = (base.fancy_state == efancy_good) ? "fancy" : "base";
    const animation_t &anim = water_supply_m.anim[anim_name];
    map_building_tiles_add(id(), tile(), 2, anim.first_img(), TERRAIN_BUILDING);
}

void building_water_supply::spawn_figure() {
    if (!base.has_water_access) {
        base.show_on_problem_overlay = 2;
    }

    common_spawn_roamer(FIGURE_WATER_CARRIER, 50, FIGURE_ACTION_125_ROAMING);
    //    set_water_supply_graphic();

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
    pcstr anim_name = (base.fancy_state == efancy_good) ? "fancy_work" : "base_work";
    const auto &anim = water_supply_m.anim[anim_name];
    building_draw_normal_anim(ctx, point, &base, tile, anim, color_mask);

    return true;
}

void building_water_supply::window_info_background(object_info &c) {
    c.help_id = 61;

    window_building_play_sound(&c, "wavs/fountain.wav");
    
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(108, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);

    building* b = building_get(c.building_id);
    if (!c.has_road_access)
        window_building_draw_description(c, 69, 25);
    else {
        if (!b->num_workers)
            window_building_draw_description(c, 108, 7);
        else {
            int text_id;
            if (c.worker_percentage >= 100)
                text_id = 2;
            else if (c.worker_percentage >= 75)
                text_id = 3;
            else if (c.worker_percentage >= 50)
                text_id = 4;
            else if (c.worker_percentage >= 25)
                text_id = 5;
            else
                text_id = 7;
            window_building_draw_description(c, 108, text_id);
            window_building_draw_description_at(c, 16 * c.bgsize.y - 120, 108, 1);
        }
    }
    inner_panel_draw(c.offset.x + 16, c.offset.y + 144, c.bgsize.x - 2, 4);
    window_building_draw_employment(&c, 150);
}
