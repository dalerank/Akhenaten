#include "empire/trader_handler.h"

#include "city/city_figures.h"
#include "figure/figure.h"
#include "figuretype/figure_caravan_donkey.h"
#include "figuretype/figure_kingdome_trader.h"
#include "figuretype/figure_trader_ship.h"
#include "game/resource.h"
#include "js/js.h"
#include "js/js_game.h"
#include "mujs/jsbuiltin.h"
#include "mujs/mujs.h"

#include <cstdio>

namespace {
struct figure_trade_session {
    empire_trader_handle trader;
    empire_city_handle city;
    int capacity = 0;
};

figure_trade_session figure_trade_session_get(int fid) {
    figure_trade_session out;
    figure *f = figure_get(fid);
    if (!f || !f->is_valid()) {
        return out;
    }

    if (auto donkey = f->dcast<figure_caravan_donkey>()) {
        auto head = donkey->head_of_caravan() ? donkey->head_of_caravan()->dcast<figure_trade_caravan>() : nullptr;
        out.trader = head ? head->empire_trader() : empire_trader_handle{};
        out.city = head ? head->empire_city() : empire_city_handle{};
        out.capacity = head ? head->max_capacity() : 0;
    } else if (auto caravan = f->dcast<figure_trade_caravan>()) {
        out.trader = caravan->empire_trader();
        out.city = caravan->empire_city();
        out.capacity = caravan->max_capacity();
    } else if (auto ship = f->dcast<figure_trade_ship>()) {
        out.trader = ship->empire_trader();
        out.city = ship->empire_city();
        out.capacity = ship->max_capacity();
    }

    return out;
}
} // namespace

static js_Object *g_figure_trade_proto = nullptr;

static int figure_trade_this_fid(js_State *J) {
    J->getproperty(J->toobject(0), js_intern("id"));
    const int id = (int)js_tointeger(J, -1);
    js_pop(J, 1);
    return id;
}

static figure_trade_session figure_trade_this_session(js_State *J) {
    return figure_trade_session_get(figure_trade_this_fid(J));
}

static void figure_trade_proto___valid(js_State *J) {
    js_helpers::js_push_value(J, figure_trade_this_session(J).trader.valid());
}

static void figure_trade_proto___capacity(js_State *J) {
    const auto session = figure_trade_this_session(J);
    if (empire_trader_ignore_total_bag()) {
        js_pushnumber(J, (double)empire_trader_per_good_cap());
        return;
    }
    js_pushnumber(J, (double)session.capacity);
}

static void figure_trade_proto___per_good(js_State *J) {
    js_helpers::js_push_value(J, empire_trader_ignore_total_bag());
}

static void figure_trade_proto___empire_city_id(js_State *J) {
    js_pushnumber(J, (double)figure_trade_this_session(J).city.handle);
}

static void figure_trade_proto___has_traded(js_State *J) {
    empire_trader_handle trader = figure_trade_this_session(J).trader;
    js_helpers::js_push_value(J, trader.valid() && trader.has_traded());
}

static figure_trade_caravan *figure_trade_this_caravan(js_State *J) {
    figure *f = figure_get(figure_trade_this_fid(J));
    if (!f || !f->is_valid()) {
        return nullptr;
    }
    if (auto caravan = f->dcast<figure_trade_caravan>()) {
        return caravan;
    }
    if (auto donkey = f->dcast<figure_caravan_donkey>()) {
        auto *head = donkey->head_of_caravan();
        return head ? head->dcast<figure_trade_caravan>() : nullptr;
    }
    return nullptr;
}

static void figure_trade_proto___can_buy_at_destination(js_State *J) {
    auto *caravan = figure_trade_this_caravan(J);
    if (!caravan) {
        js_helpers::js_push_value(J, false);
        return;
    }
    js_helpers::js_push_value(J, caravan->can_buy(caravan->destination(), caravan->empire_city()));
}

static void figure_trade_proto___can_sell_at_destination(js_State *J) {
    auto *caravan = figure_trade_this_caravan(J);
    if (!caravan) {
        js_helpers::js_push_value(J, false);
        return;
    }
    js_helpers::js_push_value(J, caravan->can_sell(caravan->destination(), caravan->empire_city()));
}

static void figure_trade_proto___is_trading(js_State *J) {
    figure *f = figure_get(figure_trade_this_fid(J));
    auto *ship = (f && f->is_valid()) ? f->dcast<figure_trade_ship>() : nullptr;
    js_pushnumber(J, ship ? (double)ship->is_trading() : 0.0);
}

static void figure_trade_proto_bought_amount(js_State *J) {
    const int resource = js_helpers::js_to_value<int>(J, 1);
    empire_trader_handle trader = figure_trade_this_session(J).trader;
    if (!trader.valid() || resource <= RESOURCE_NONE || resource >= RESOURCES_MAX) {
        js_pushnumber(J, 0);
        return;
    }
    js_pushnumber(J, (double)trader.bought_resources((e_resource)resource));
}

static void figure_trade_proto_sold_amount(js_State *J) {
    const int resource = js_helpers::js_to_value<int>(J, 1);
    empire_trader_handle trader = figure_trade_this_session(J).trader;
    if (!trader.valid() || resource <= RESOURCE_NONE || resource >= RESOURCES_MAX) {
        js_pushnumber(J, 0);
        return;
    }
    js_pushnumber(J, (double)trader.sold_resources((e_resource)resource));
}

static void figure_trade_proto_toString(js_State *J) {
    char buf[64];
    snprintf(buf, sizeof buf, "FigureTrade(%d)", figure_trade_this_fid(J));
    J->pushstring(buf);
}

static void js_push_figure_trade(js_State *J, int fid) {
    js_pushobject(J, jsV_newobject(J, JS_COBJECT, g_figure_trade_proto));
    js_pushnumber(J, (double)fid);
    js_setproperty(J, -2, js_intern("id"));
}

static void jsB_new_FigureTrade(js_State *J) {
    const int fid = js_gettop(J) > 1 ? (int)js_tointeger(J, 1) : 0;
    js_push_figure_trade(J, fid);
}

void js_register_figure_trade_proto(js_State *J) {
    g_figure_trade_proto = jsV_newobject(J, JS_COBJECT, J->Object_prototype);
    js_pushobject(J, g_figure_trade_proto);

    jsB_propf(J, js_intern("FigureTrade.prototype.__valid"), figure_trade_proto___valid, 0);
    jsB_propf(J, js_intern("FigureTrade.prototype.__capacity"), figure_trade_proto___capacity, 0);
    jsB_propf(J, js_intern("FigureTrade.prototype.__per_good"), figure_trade_proto___per_good, 0);
    jsB_propf(J, js_intern("FigureTrade.prototype.__empire_city_id"), figure_trade_proto___empire_city_id, 0);
    jsB_propf(J, js_intern("FigureTrade.prototype.__has_traded"), figure_trade_proto___has_traded, 0);
    jsB_propf(J, js_intern("FigureTrade.prototype.__can_buy_at_destination"), figure_trade_proto___can_buy_at_destination, 0);
    jsB_propf(J, js_intern("FigureTrade.prototype.__can_sell_at_destination"), figure_trade_proto___can_sell_at_destination, 0);
    jsB_propf(J, js_intern("FigureTrade.prototype.__is_trading"), figure_trade_proto___is_trading, 0);
    jsB_propf(J, js_intern("FigureTrade.prototype.bought_amount"), figure_trade_proto_bought_amount, 1);
    jsB_propf(J, js_intern("FigureTrade.prototype.sold_amount"), figure_trade_proto_sold_amount, 1);
    jsB_propf(J, js_intern("FigureTrade.prototype.toString"), figure_trade_proto_toString, 0);

    js_newcconstructor(J, jsB_new_FigureTrade, jsB_new_FigureTrade, js_intern("FigureTrade"), 1);
    js_defglobal(J, js_intern("FigureTrade"), JS_DONTENUM);
}
