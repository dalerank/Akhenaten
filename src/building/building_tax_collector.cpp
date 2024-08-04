#include "building_tax_collector.h"

#include "building/building.h"
#include "city/object_info.h"
#include "figure/figure.h"
#include "game/resource.h"
#include "city/finance.h"
#include "graphics/window.h"
#include "graphics/elements/arrow_button.h"
#include "graphics/elements/panel.h"
#include "graphics/view/view.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "sound/sound_building.h"
#include "building/count.h"
#include "game/game.h"
#include "city/labor.h"
#include "widget/city/ornaments.h"

buildings::model_t<building_tax_collector> btax_collector_m;
buildings::model_t<building_tax_collector_up> btax_collector_up_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_tax_collector);
void config_load_building_tax_collector() {
    btax_collector_m.load();
    btax_collector_up_m.load();
}

void building_tax_collector::spawn_figure() {
    if (!has_road_access()) {
        return;
    }

    check_labor_problem();
    if (has_figure_of_type(BUILDING_SLOT_SERVICE, FIGURE_TAX_COLLECTOR)) {
        return;
    }

    common_spawn_labor_seeker(50);

    int pct_workers = worker_percentage();
    int spawn_delay;
    if (pct_workers >= 100) {
        spawn_delay = 0;
    } else if (pct_workers >= 75) {
        spawn_delay = 1;
    } else if (pct_workers >= 50) {
        spawn_delay = 3;
    } else if (pct_workers >= 25) {
        spawn_delay = 7;
    } else if (pct_workers >= 1) {
        spawn_delay = 15;
    } else {
        return;
    }

    base.figure_spawn_delay++;
    if (base.figure_spawn_delay > spawn_delay) {
        base.figure_spawn_delay = 0;
        create_roaming_figure(FIGURE_TAX_COLLECTOR, FIGURE_ACTION_40_TAX_COLLECTOR_CREATED, BUILDING_SLOT_SERVICE);
    }
}

void building_tax_collector::window_info_background(object_info &c) {
    ui::begin_widget(c.offset);

    c.go_to_advisor.left_a = ADVISOR_RATINGS;
    c.go_to_advisor.left_b = ADVISOR_FINANCIAL;

    c.help_id = params().meta.help_id;
    int group_id = params().meta.text_id;

    window_building_play_sound(&c, get_sound());

    { // header
        ui::panel(vec2i{0, 0}, {c.bgsize.x, c.bgsize.y}, UiFlags_PanelOuter);
        ui::label(106, 0, vec2i{0, 10}, FONT_LARGE_BLACK_ON_LIGHT, UiFlags_LabelCentered, 16 * c.bgsize.x);
        ui::icon(vec2i{16, 36}, RESOURCE_DEBEN);
    }

    int width = ui::label(106, 2, {44, 43});
    int amount = config_get(CONFIG_GP_CH_NEW_TAX_COLLECTION_SYSTEM) ? base.deben_storage : base.tax_income_or_storage;
    ui::label_amount(8, 0, amount, {44 + width, 43});

    int tax_block = c.bgsize.x * 16 / 2;
    ui::label(60, 1, {tax_block + 50, 44});
    ui::label_percent(city_finance_tax_percentage(), {tax_block + 140, 44});
    ui::arw_button({tax_block + 170, 36}, true)
            .onclick([] (int, int) { 
                city_finance_change_tax_percentage(-1);
                window_invalidate();
            });
    ui::arw_button({tax_block + 194, 36}, false)
            .onclick([] (int, int) { 
                city_finance_change_tax_percentage(1);
                window_invalidate();
            });

    if (!c.has_road_access) {
        window_building_draw_description(c, 69, 25);
    } else if (base.num_workers <= 0) {
        window_building_draw_description_at(c, 72, 106, 10);
    } else if (c.worker_percentage >= 100) {
        window_building_draw_description_at(c, 72, 106, 5);
    } else if (c.worker_percentage >= 75) {
        window_building_draw_description_at(c, 72, 106, 6);
    } else if (c.worker_percentage >= 50) {
        window_building_draw_description_at(c, 72, 106, 7);
    } else if (c.worker_percentage >= 25) {
        window_building_draw_description_at(c, 72, 106, 8);
    } else {
        window_building_draw_description_at(c, 72, 106, 9);
    }

    inner_panel_draw(c.offset.x + 16, c.offset.y + 136, c.bgsize.x - 2, 4);
    window_building_draw_employment(&c, 142);
}

void building_tax_collector::update_month() {
    if (!config_get(CONFIG_GP_CH_NEW_TAX_COLLECTION_SYSTEM)) {
        return;
    }

    if (base.has_figure_of_type(BUILDING_SLOT_CARTPUSHER, FIGURE_CART_PUSHER)) {
        return;
    }

    if (base.has_road_access && base.deben_storage > 100) {
        int may_send = std::min<int>((base.deben_storage / 100) * 100, 400);
        figure *f = base.create_cartpusher(RESOURCE_GOLD, may_send, FIGURE_ACTION_20_CARTPUSHER_INITIAL, BUILDING_SLOT_CARTPUSHER);
        base.deben_storage -= may_send;
        f->sender_building_id = base.id;
    }
}

void building_tax_collector::update_graphic() {
    const xstring &animkey = can_play_animation() ? animkeys().work : animkeys().none;
    set_animation(animkey);
}

const building_impl::static_params &building_tax_collector::params() const {
    return (type() == BUILDING_TAX_COLLECTOR) 
                ? *(static_params*)&btax_collector_m
                : *(static_params*)&btax_collector_up_m;
}