#include "building/building_courthouse.h"

#include "window/building/common.h"
#include "widget/city/ornaments.h"
#include "graphics/elements/ui.h"
#include "figure/figure.h"
#include "window/window_building_info.h"
#include "js/js_game.h"
#include "graphics/animation.h"
#include "city/city_labor.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_courthouse);

struct info_window_courthouse : public building_info_window_t<info_window_courthouse> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        return c.building_get()->dcast_courthouse();
    }
};

info_window_courthouse courthouse_infow;

void info_window_courthouse::init(object_info &c) {
    building_info_window::init(c);

    building* b = c.building_get();
    std::pair<int, int> reason = { c.group_id, 0 };

    if (!b->has_road_access) reason = { 69, 25 };
    else if (b->num_workers <= 0) reason.second = 2;
    else reason.second = approximate_value(b->worker_percentage() / 100.f, make_array(4, 5, 6));
    ui["workers_desc"] = ui::str(reason.first, reason.second);

    textid magistrate_state{58 ,51};
    if (b->num_workers > 0) {
        if (!b->get_figure(BUILDING_SLOT_SERVICE)->is_valid()) {
            magistrate_state = { c.group_id, 8 };
        } else {
            magistrate_state = { c.group_id, 7 };
        }
    } 

    ui["state"] = magistrate_state;
    ui["warning_text"] = ui::str(c.group_id, 1);
}

void building_courthouse::spawn_figure() {
    common_spawn_roamer(FIGURE_MAGISTRATE, 50, FIGURE_ACTION_125_ROAMING);
}

void building_courthouse::update_graphic() {
    const xstring &animkey = can_play_animation()
                                ? animkeys().work
                                : animkeys().none;
    set_animation(animkey);
    building_impl::update_graphic();
}

bool building_courthouse::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_normal_anim(ctx, point, tile, color_mask);

    return true;
}
