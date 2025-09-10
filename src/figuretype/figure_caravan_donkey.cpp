#include "figure_caravan_donkey.h"

#include "figure/trader.h"
#include "figuretype/figure_kingdome_trader.h"

#include "building/building_storage_yard.h"
#include "building/building_storage_room.h"

#include "empire/empire.h"
#include "empire/empire_map.h"
#include "empire/trade_prices.h"

#include "city/trade.h"
#include "city/city_resource.h"
#include "city/city_finance.h"
#include "figure/image.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "game/game.h"
#include "graphics/elements/lang_text.h"
#include "window/window_figure_info.h"
#include "core/profiler.h"

figure_caravan_donkey::static_params caravan_donkey_m;

const empire_city *figure_caravan_donkey::get_empire_city() const {
    const empire_city *city = g_empire.city(base.empire_city_id);
    return city;
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
    int image_id = anim(animkeys().walk).first_img();
    base.main_image_id = image_id + dir + 8 * base.anim.frame;
}

void figure_caravan_donkey::figure_before_action() {
    figure* leader = figure_get(base.leading_figure_id);
    if (base.leading_figure_id <= 0) {
        //poof();
    }

    if (leader->action_state == FIGURE_ACTION_149_CORPSE) {  
        poof(); // TODO make runaway from this tile
    }
}

void figure_caravan_donkey::update_animation() {
    /*nothing*/
}

figure* figure_caravan_donkey::get_head_of_caravan() const {
    figure* f = &base;
    while (f->type == FIGURE_TRADE_CARAVAN_DONKEY) {
        f = figure_get(f->leading_figure_id);
    }
    return f;
}

xstring figure_caravan_donkey::action_tip() const {
    int text_id = 0;
    figure *f = get_head_of_caravan();
    switch (f->action_state) {
    case ACTION_101_TRADE_CARAVAN_ARRIVING: text_id = 12; break;
    case ACTION_102_TRADE_CARAVAN_TRADING: text_id = 10; break;
    case ACTION_103_TRADE_CARAVAN_LEAVING: text_id = trader_has_traded(base.trader_id) ? 11 : 13; break;
    default:
        text_id = 11;
        break;
    }

    return { ui::str(129, text_id) };
}