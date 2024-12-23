#include "building/building_work_camp.h"

#include "building/industry.h"
#include "building/monuments.h"
#include "city/object_info.h"
#include "city/labor.h"
#include "city/city_floods.h"
#include "figure/figure.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "window/window_building_info.h"
#include "sound/sound_building.h"
#include "js/js_game.h"
#include "widget/city/ornaments.h"

struct info_window_work_camp : public building_info_window_t<info_window_work_camp> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        building *b = c.building_get();
        return !!b->dcast_work_camp();
    }
};

buildings::model_t<building_work_camp> work_camp_m;
info_window_work_camp work_camp_infow;

void info_window_work_camp::init(object_info &c) {
    building_info_window::init(c);

    building *b = c.building_get();

    textid reason = { c.group_id, 0 };
    if (!c.has_road_access) {
        reason = { 69, 25 };
    } if (!b->num_workers) {
        reason.id = 2; // not enough workers
    } else {
        if (b->has_figure(0)) {
            figure* f = b->get_figure(0);
            building* b_dest = f->destination();
            if (building_is_farm(b_dest->type)) { reason.id = 5; }// working on floodplains
            else if (building_is_monument(b_dest->id)) { reason.id = 6; } // working on monuments
            else { reason.id = 4; }; // looking for work
            //                window_building_draw_description(c, group_id, 7); // working on both floodplains and
            //                monuments (unused?)
        } else {
            reason.id = 3;
        }
    }

    int workers_desc = approximate_value(c.worker_percentage / 100.f, make_array(8, 7, 6, 5, 4));
    ui["workers_desc"] = ui::str(c.group_id, workers_desc);

    bstring256 warning_text = ui::str(c.group_id, 1);
    if (reason.id) {
        warning_text.append(ui::str(reason));
    }
    ui["warning_text"] = warning_text;
}

building* building_work_camp::determine_worker_needed() {
    return building_first([] (building &b) {
        const bool floodplain_farm = g_floods.state_is(FLOOD_STATE_FARMABLE) && building_is_floodplain_farm(b);
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

    building_impl::update_graphic();
}

void building_work_camp::update_month() {
    data.industry.spawned_worker_this_month = false;
}
