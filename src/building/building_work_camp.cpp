#include "building/building_work_camp.h"

#include "building/industry.h"
#include "city/object_info.h"
#include "figure/figure.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/boilerplate.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"

void building_work_camp_draw_info(object_info &c) {
    const int32_t group_id = 179;
    c.help_id = 81;
    window_building_play_sound(&c, snd::get_building_info_sound("work_camp")); // TODO: change to work_camp
    outer_panel_draw(c.offset, c.width_blocks, c.height_blocks);
    lang_text_draw_centered(group_id, 0, c.offset.x, c.offset.y + 10, 16 * c.width_blocks, FONT_LARGE_BLACK_ON_LIGHT);

    building* b = building_get(c.building_id);

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

            window_building_draw_description_at(c, 16 * c.height_blocks - 120, group_id, 1);
        }
    }

    inner_panel_draw(c.offset.x + 16, c.offset.y + 136, c.width_blocks - 2, 4);
    window_building_draw_employment(&c, 142);
}

void building_work_camp::spawn_figure() {
    if (!common_spawn_figure_trigger(100)) {
        return;
    }

    if (config_get(CONFIG_GP_CH_WORK_CAMP_ONE_WORKER_PER_MONTH) && data.industry.spawned_worker_this_month) {
        return;
    }

    building* dest = building_determine_worker_needed();
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