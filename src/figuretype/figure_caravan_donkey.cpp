#include "figure_caravan_donkey.h"

#include "empire/trader_handler.h"
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
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_caravan_donkey);

empire_city_handle figure_caravan_donkey::empire_city() const {
    auto head = head_of_caravan();
    assert(head != nullptr);

    return head->dcast<figure_trade_caravan>()->empire_city();
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

    int dir = base.figure_image_normalize_direction(direction() < 8 ? direction() : base.previous_tile_direction);
    int image_id = anim(animkeys().walk).first_img();
    base.main_image_id = image_id + dir + 8 * base.animctx.frame;
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

figure* figure_caravan_donkey::head_of_caravan() const {
    figure* f = &base;
    while (f->type == FIGURE_TRADE_CARAVAN_DONKEY) {
        f = figure_get(f->leading_figure_id);
    }
    return f;
}

bvariant figure_caravan_donkey::get_property(const xstring& domain, const xstring& name) const {
    auto head = head_of_caravan()->dcast<figure_trade_caravan>();
    if (head) {
        return head->get_property(domain, name);
    }

    return figure_impl::get_property(domain, name);
}

xstring figure_caravan_donkey::action_tip() const {
    auto head = head_of_caravan()->dcast<figure_trade_caravan>();
    if (!head) {
        return "#donkey_no_trader_head";
    }

    switch (head->action_state()) {
    case ACTION_101_TRADE_CARAVAN_ARRIVING: return "#trader_heading_storage";
    case ACTION_102_TRADE_CARAVAN_TRADING: return "#trader_trading_goods"; 
    case ACTION_103_TRADE_CARAVAN_LEAVING: 
        return head->empire_trader().has_traded() 
                    ? "#trader_returning_home" 
                    : "#trader_nothing_to_trage";
    default:
        return "#trader_returning_home";
    }

    return "#trader_unknown";
}