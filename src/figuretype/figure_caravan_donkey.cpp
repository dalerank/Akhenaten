#include "figure_caravan_donkey.h"

#include "figure/trader.h"
#include "figure/figure.h"

#include "building/storage.h"
#include "building/building_storage_yard.h"
#include "building/building_storage_room.h"

#include "empire/empire.h"
#include "empire/empire_map.h"
#include "empire/trade_prices.h"

#include "city/trade.h"
#include "city/resource.h"
#include "city/finance.h"
#include "figure/image.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "game/game.h"
#include "graphics/elements/lang_text.h"

#include "core/profiler.h"

figures::model_t<figure_caravan_donkey> caravan_donkey_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_caravan_donkey);
void config_load_figure_caravan_donkey() {
    caravan_donkey_m.load();
}

void figure_caravan_donkey::figure_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/CaravanDonkey");
    figure* leader = figure_get(base.leading_figure_id);
    if (leader->action_state == FIGURE_ACTION_149_CORPSE)
        poof();
    else if (leader->state != FIGURE_STATE_ALIVE)
        poof();
    else if (leader->type != FIGURE_TRADE_CARAVAN && leader->type != FIGURE_TRADE_CARAVAN_DONKEY)
        poof();
    else
        follow_ticks(1);

    int dir = figure_image_normalize_direction(direction() < 8 ? direction() : base.previous_tile_direction);
    int image_id = caravan_donkey_m.anim["walk"].first_img();
    base.sprite_image_id = image_id + dir + 8 * base.anim.frame;
}

void figure_caravan_donkey::figure_before_action() {
    figure* leader = figure_get(base.leading_figure_id);
    if (base.leading_figure_id <= 0) {
        //poof();
    }

    if (leader->action_state == FIGURE_ACTION_149_CORPSE) {  
        poof(); // TODO make runaway from this tile
    }

    if (leader->is_ghost) {
        base.is_ghost = true;
    }
}

void figure_caravan_donkey::update_animation() {
    /*nothing*/
}

figure* figure_caravan_donkey::get_head_of_caravan() {
    figure* f = &base;
    while (f->type == FIGURE_TRADE_CARAVAN_DONKEY) {
        f = figure_get(f->leading_figure_id);
    }
    return f;
}

bool figure_caravan_donkey::window_info_background(object_info &c) {
    painter ctx = game.painter();
    figure* f = get_head_of_caravan();
    const empire_city* city = g_empire.city(f->empire_city_id);
    int width = lang_text_draw(64, f->type, c.offset.x + 40, c.offset.y + 110, FONT_NORMAL_BLACK_ON_DARK);
    lang_text_draw(21, city->name_id, c.offset.x + 40 + width, c.offset.y + 110, FONT_NORMAL_BLACK_ON_DARK);

    width = lang_text_draw(129, 1, c.offset.x + 40, c.offset.y + 132, FONT_NORMAL_BLACK_ON_DARK);
    lang_text_draw_amount(8, 10, 800, c.offset.x + 40 + width, c.offset.y + 132, FONT_NORMAL_BLACK_ON_DARK);

    int trader_id = f->trader_id;
    
    int text_id;
    switch (f->action_state) {
    case FIGURE_ACTION_101_TRADE_CARAVAN_ARRIVING:
        text_id = 12;
        break;

    case FIGURE_ACTION_102_TRADE_CARAVAN_TRADING:
        text_id = 10;
        break;

    case FIGURE_ACTION_103_TRADE_CARAVAN_LEAVING:
        text_id = trader_has_traded(trader_id) ? 11 : 13;
        break;

    default:
        text_id = 11;
        break;
    }
    lang_text_draw(129, text_id, c.offset.x + 40, c.offset.y + 154, FONT_NORMAL_BLACK_ON_DARK);

    if (trader_has_traded(trader_id)) {
        // bought
        int y_base = c.offset.y + 180;
        width = lang_text_draw(129, 4, c.offset.x + 40, y_base, FONT_NORMAL_BLACK_ON_DARK);
        for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; ++r) {
            if (trader_bought_resources(trader_id, r)) {
                width += text_draw_number(trader_bought_resources(trader_id, r), '@'," ", c.offset.x + 40 + width, y_base, FONT_NORMAL_BLACK_ON_DARK);
                int image_id = image_id_resource_icon(r) + resource_image_offset(r, RESOURCE_IMAGE_ICON);
                ImageDraw::img_generic(ctx, image_id, vec2i{c.offset.x + 40 + width, y_base - 3});
                width += 25;
            }
        }
        // sold
        y_base = c.offset.y + 210;
        width = lang_text_draw(129, 5, c.offset.x + 40, y_base, FONT_NORMAL_BLACK_ON_DARK);
        for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; ++r) {
            if (trader_sold_resources(trader_id, r)) {
                width += text_draw_number(trader_sold_resources(trader_id, r), '@', " ", c.offset.x + 40 + width, y_base, FONT_NORMAL_BLACK_ON_DARK);
                int image_id = image_id_resource_icon(r) + resource_image_offset(r, RESOURCE_IMAGE_ICON);
                ImageDraw::img_generic(ctx, image_id, vec2i{c.offset.x + 40 + width, y_base - 3});
                width += 25;
            }
        }
    } else { // nothing sold/bought (yet)
             // buying
        int y_base = c.offset.y + 180;
        width = lang_text_draw(129, 2, c.offset.x + 40, y_base, FONT_NORMAL_BLACK_ON_DARK);
        for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; ++r) {
            if (city->buys_resource[r]) {
                int image_id = image_id_resource_icon(r) + resource_image_offset(r, RESOURCE_IMAGE_ICON);
                ImageDraw::img_generic(ctx, image_id, vec2i{c.offset.x + 40 + width, y_base - 3});
                width += 25;
            }
        }
        // selling
        y_base = c.offset.y + 210;
        width = lang_text_draw(129, 3, c.offset.x + 40, y_base, FONT_NORMAL_BLACK_ON_DARK);
        for (int r = RESOURCE_MIN; r < RESOURCES_MAX; r++) {
            if (city->sells_resource[r]) {
                int image_id = image_id_resource_icon(r) + resource_image_offset(r, RESOURCE_IMAGE_ICON);
                ImageDraw::img_generic(ctx, image_id, vec2i{c.offset.x + 40 + width, y_base - 3});
                width += 25;
            }
        }
    }
    return true;
}
