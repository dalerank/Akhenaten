#include "building/building_work_camp.h"

#include "building/industry.h"
#include "building/monuments.h"
#include "city/object_info.h"
#include "city/labor.h"
#include "city/floods.h"
#include "figure/figure.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"

#include "widget/city/ornaments.h"

buildings::model_t<building_work_camp> work_camp_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_work_camp);
void config_load_building_work_camp() {
    work_camp_m.load();
}

void building_work_camp::window_info_background(object_info &c) {
    building *b = building_get(c.building_id);
    const auto &params = b->dcast()->params();

    c.help_id = params.meta.help_id;
    int group_id = params.meta.text_id;

    window_building_play_sound(&c, snd::get_building_info_sound(type()));
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(group_id, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);

    if (!c.has_road_access) {
        window_building_draw_description(c, 69, 25);
    } else {
        if (!b->num_workers) {
            window_building_draw_description(c, group_id, 2); // not enough workers
        } else {
            if (b->has_figure(0)) {
                figure* f = b->get_figure(0);
                building* b_dest = f->destination();
                if (building_is_farm(b_dest->type))
                    window_building_draw_description(c, group_id, 5); // working on floodplains
                else if (building_is_monument(b_dest->id))
                    window_building_draw_description(c, group_id, 6); // working on monuments
                else
                    window_building_draw_description(c, group_id, 4); // looking for work
                //                window_building_draw_description(c, group_id, 7); // working on both floodplains and
                //                monuments (unused?)
            } else {
                window_building_draw_description(c, group_id, 3);
            }
            //            if (c.worker_percentage >= 100)
            //                window_building_draw_description_at(c, 72, group_id, 4);
            //            else if (c.worker_percentage >= 75)
            //                window_building_draw_description_at(c, 72, group_id, 5);
            //            else if (c.worker_percentage >= 50)
            //                window_building_draw_description_at(c, 72, group_id, 6);
            //            else if (c.worker_percentage >= 25)
            //                window_building_draw_description_at(c, 72, group_id, 7);
            //            else
            //                window_building_draw_description_at(c, 72, group_id, 8);

            window_building_draw_description_at(c, 16 * c.bgsize.y - 120, group_id, 1);
        }
    }

    inner_panel_draw(c.offset.x + 16, c.offset.y + 136, c.bgsize.x - 2, 4);
    window_building_draw_employment(&c, 142);
}

building* building_work_camp::determine_worker_needed() {
    return building_first([] (building &b) {
        const bool floodplain_farm = floodplains_is(FLOOD_STATE_FARMABLE) && building_is_floodplain_farm(b);
        if (floodplain_farm) {
            return (!b.data.industry.worker_id && b.data.industry.labor_days_left <= 47 && !b.num_workers);
        }

        const bool monument_leveling = building_is_monument(b.type) && b.data.monuments.phase < 2;
        if (monument_leveling) {
            return building_monument_need_workers(&b);
        }

        return false;
    });
}


void building_work_camp::spawn_figure() {
    if (!common_spawn_figure_trigger(100)) {
        return;
    }

    if (config_get(CONFIG_GP_CH_WORK_CAMP_ONE_WORKER_PER_MONTH) && data.industry.spawned_worker_this_month) {
        return;
    }

    building* dest = determine_worker_needed();
    if (dest) {
        figure *f = base.create_figure_with_destination(FIGURE_LABORER, dest, FIGURE_ACTION_10_WORKER_CREATED, BUILDING_SLOT_SERVICE);
        data.industry.spawned_worker_this_month = true;
        if (dest->is_industry()) {
            dest->industry_add_workers(f->id);
        } else if (dest->is_monument()) {
            dest->monument_add_workers(f->id);
        }
    }
}

bool building_work_camp::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    building_impl::draw_ornaments_and_animations_height(ctx, point, tile, color_mask);

    return true;
}

void building_work_camp::update_graphic() {
    set_animation(can_play_animation() ? animkeys().work : animkeys().none);
}

void building_work_camp::update_month() {
    data.industry.spawned_worker_this_month = false;
}
