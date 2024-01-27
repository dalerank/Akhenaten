#include "building_tax_collector.h"

#include "building/building.h"
#include "city/object_info.h"
#include "figure/figure.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/view/view.h"
#include "graphics/elements/lang_text.h"
#include "graphics/boilerplate.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "sound/sound_building.h"
#include "game/game.h"

void building_tax_collector::window_info_background(object_info &c) {
    ui::begin_window(c.offset);

    c.help_id = e_text_building_tax_collector;
    c.go_to_advisor.left_a = ADVISOR_RATINGS;
    c.go_to_advisor.left_b = ADVISOR_FINANCIAL;

    window_building_play_sound(&c, snd::get_building_info_sound("tax_collector"));

    {
        ui::panel(vec2i{0, 0}, {c.width_blocks, c.height_blocks}, UiFlags_PanelOuter);
        ui::label(106, 0, vec2i{0, 10}, 16 * c.width_blocks, FONT_LARGE_BLACK_ON_LIGHT, UiFlags_LabelCentered);
        ui::icon(vec2i{16, 36}, RESOURCE_DEBEN);
    }

    building* b = building_get(c.building_id);
    int width = lang_text_draw(106, 2, c.offset.x + 44, c.offset.y + 43, FONT_NORMAL_BLACK_ON_LIGHT);
    if (config_get(CONFIG_GP_CH_NEW_TAX_COLLECTION_SYSTEM)) {
        lang_text_draw_amount(8, 0, b->deben_storage, c.offset.x + 44 + width, c.offset.y + 43, FONT_NORMAL_BLACK_ON_LIGHT);
    } else {
        lang_text_draw_amount(8, 0, b->tax_income_or_storage, c.offset.x + 44 + width, c.offset.y + 43, FONT_NORMAL_BLACK_ON_LIGHT);
    }

    if (!c.has_road_access) {
        window_building_draw_description(c, 69, 25);
    } else if (b->num_workers <= 0) {
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

    inner_panel_draw(c.offset.x + 16, c.offset.y + 136, c.width_blocks - 2, 4);
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
