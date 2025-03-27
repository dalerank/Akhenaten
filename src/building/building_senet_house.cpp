#include "building_senet_house.h"

#include "graphics/graphics.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "io/gamefiles/lang.h"
#include "window/building/common.h"
#include "city/labor.h"
#include "city/buildings.h"
#include "city/city.h"
#include "city/city_warnings.h"
#include "window/building/common.h"
#include "sound/sound_building.h"

buildings::model_t<building_senet_house> senet_house_m;
buildings::model_t<building_bullfight_school> bullfight_school_m;

void building_senet_house::window_info_background(object_info &c) {
    c.help_id = 74;
    window_building_play_sound(&c, "Wavs/hippodrome.wav");
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(73, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    building* b = building_get(c.building_id);

    auto &d = runtime_data();
    if (!b->has_road_access)
        window_building_draw_description(c, 69, 25);
    else if (b->num_workers <= 0)
        window_building_draw_description(c, 73, 4);
    else if (!d.num_shows)
        window_building_draw_description(c, 73, 2);
    else if (d.juggler_visited)
        window_building_draw_description(c, 73, 3);

    inner_panel_draw(c.offset + vec2i{ 16, 136 }, { c.bgsize.x - 2, 6 });
    window_building_draw_employment(&c, 138);
    if (d.juggler_visited > 0) {
        int width = lang_text_draw(73, 6, c.offset.x + 32, c.offset.y + 202, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw_amount(8, 44, 2 * d.juggler_visited, c.offset.x + width + 32, c.offset.y + 202, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        lang_text_draw(73, 5, c.offset.x + 32, c.offset.y + 202, FONT_NORMAL_BLACK_ON_DARK);
    }
}

void building_senet_house::on_place_checks() {
    construction_warnings warnings;

    const bool has_senet_master = (g_city.buildings.count_active(BUILDING_SENET_MASTER) > 0);
    warnings.add_if(!has_senet_master, "#build_senet_house");
}

void building_senet_house::on_destroy() {
    city_buildings_remove_senet_house();
}

void building_senet_house::spawn_figure() {
    // TODO
    //    check_labor_problem();
    //    if (prev_part_building_id)
    //        return;
    //    building *part = b;
    //    for (int i = 0; i < 2; i++) {
    //        part = part->next();
    //        if (part->id)
    //            part->show_on_problem_overlay = show_on_problem_overlay;
    //
    //    }
    //    if (has_figure_of_type(FIGURE_CHARIOTEER))
    //        return;
    //    map_point road;
    //    if (map_has_road_access_hippodrome_rotation(x, y, &road, subtype.orientation)) {
    //        if (houses_covered <= 50 || data.entertainment.days1 <= 0)
    //            generate_labor_seeker(road.x, road.y);
    //
    //        int pct_workers = worker_percentage();
    //        int spawn_delay;
    //        if (pct_workers >= 100)
    //            spawn_delay = 7;
    //        else if (pct_workers >= 75)
    //            spawn_delay = 15;
    //        else if (pct_workers >= 50)
    //            spawn_delay = 30;
    //        else if (pct_workers >= 25)
    //            spawn_delay = 50;
    //        else if (pct_workers >= 1)
    //            spawn_delay = 80;
    //        else
    //            return;
    //        figure_spawn_delay++;
    //        if (figure_spawn_delay > spawn_delay) {
    //            figure_spawn_delay = 0;
    //            figure *f = figure_create(FIGURE_CHARIOTEER, road.x, road.y, DIR_0_TOP_RIGHT);
    //            f->action_state = FIGURE_ACTION_94_ENTERTAINER_ROAMING;
    //            f->home() = b;
    //            figure_id = f->id;
    //            f->init_roaming();
    //
    //            if (!city_entertainment_hippodrome_has_race()) {
    //                // create mini-horses
    //                figure *horse1 = figure_create(FIGURE_HIPPODROME_HORSES, x + 2, y + 1, DIR_2_BOTTOM_RIGHT);
    //                horse1->action_state = FIGURE_ACTION_200_HIPPODROME_HORSE_CREATED;
    //                horse1->building_id = id;
    //                horse1->set_resource(0);
    //                horse1->speed_multiplier = 3;
    //
    //                figure *horse2 = figure_create(FIGURE_HIPPODROME_HORSES, x + 2, y + 2, DIR_2_BOTTOM_RIGHT);
    //                horse2->action_state = FIGURE_ACTION_200_HIPPODROME_HORSE_CREATED;
    //                horse2->building_id = id;
    //                horse1->set_resource(1);
    //                horse2->speed_multiplier = 2;
    //
    //                if (data.entertainment.days1 > 0) {
    //                    if (city_entertainment_show_message_hippodrome())
    //                        city_message_post(true, MESSAGE_WORKING_HIPPODROME, 0, 0);
    //
    //                }
    //            }
    //        }
    //    }
}

void building_bullfight_school::window_info_background(object_info &c) {
    building *b = building_get(c.building_id);
    const auto &params = b->dcast()->params();
    
    c.help_id = params.meta.help_id;
    int group_id = params.meta.text_id;

    window_building_play_sound(&c, b->get_sound());

    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(group_id, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    if (!b->has_road_access) {
        window_building_draw_description(c, 69, 25);
    } else if (building_get(c.building_id)->num_workers <= 0) {
        window_building_draw_description(c, group_id, 7);
    } else if (b->worker_percentage() >= 100) {
        window_building_draw_description(c, group_id, 2);
    } else if (b->worker_percentage() >= 75) {
        window_building_draw_description(c, group_id, 3);
    } else if (b->worker_percentage() >= 50) {
        window_building_draw_description(c, group_id, 4);
    } else if (b->worker_percentage() >= 25) {
        window_building_draw_description(c, group_id, 5);
    } else {
        window_building_draw_description(c, group_id, 6);
    }
    inner_panel_draw(c.offset + vec2i{ 16, 136 }, { c.bgsize.x - 2, 4 });
    window_building_draw_employment(&c, 142);
}

bool building_bullfight_school::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    //            ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_STOCK_CHARIOTS_2) + amount, x + 65, y +
    //            3, color_mask);
    return true;
}