#include "city/city_figures.h"
#include "figure/figure.h"
#include "figuretype/figure_transport_ship.h"
#include "grid/point.h"
#include "js/js.h"
#include "js/js_game.h"
#include "mujs/jsbuiltin.h"
#include "mujs/mujs.h"

#include <cstdio>

namespace {
figure_transport_ship *figure_transport_ship_get(int fid) {
    figure *f = figure_get(fid);
    return f ? smart_cast<figure_transport_ship>(f) : nullptr;
}
} // namespace

static js_Object *g_figure_transport_ship_proto = nullptr;

static int figure_transport_ship_this_fid(js_State *J) {
    J->getproperty(J->toobject(0), js_intern("id"));
    const int id = (int)js_tointeger(J, -1);
    js_pop(J, 1);
    return id;
}

static figure_transport_ship *figure_transport_ship_this(js_State *J) {
    return figure_transport_ship_get(figure_transport_ship_this_fid(J));
}

static void figure_transport_ship_proto___valid(js_State *J) {
    J->push(figure_transport_ship_this(J) != nullptr);
}

static void figure_transport_ship_proto___has_troops(js_State *J) {
    figure_transport_ship *ship = figure_transport_ship_this(J);
    J->push(ship && ship->has_troops());
}

static void figure_transport_ship_proto___can_embark(js_State *J) {
    figure_transport_ship *ship = figure_transport_ship_this(J);
    J->push(ship && ship->can_embark());
}

static void figure_transport_ship_proto___transported_formation(js_State *J) {
    figure_transport_ship *ship = figure_transport_ship_this(J);
    js_pushnumber(J, (double)(ship ? ship->transported_formation() : 0));
}

static void figure_transport_ship_proto___phase(js_State *J) {
    figure_transport_ship *ship = figure_transport_ship_this(J);
    js_pushnumber(J, (double)(ship ? ship->runtime_data().phase : 0));
}

static void figure_transport_ship_proto_embark(js_State *J) {
    figure_transport_ship *ship = figure_transport_ship_this(J);
    const int formation_id = J->to<int>(1);
    if (ship) {
        ship->embark_formation(formation_id);
    }
}

static void figure_transport_ship_proto_sail_to(js_State *J) {
    figure_transport_ship *ship = figure_transport_ship_this(J);
    const int x = J->to<int>(1);
    const int y = J->to<int>(2);
    if (ship) {
        ship->sail_to_landing(tile2i(x, y));
    }
}

static void figure_transport_ship_proto_toString(js_State *J) {
    char buf[64];
    snprintf(buf, sizeof buf, "FigureTransportShip(%d)", figure_transport_ship_this_fid(J));
    J->pushstring(buf);
}

static void js_push_figure_transport_ship(js_State *J, int fid) {
    js_pushobject(J, jsV_newobject(J, JS_COBJECT, g_figure_transport_ship_proto));
    js_pushnumber(J, (double)fid);
    js_setproperty(J, -2, js_intern("id"));
}

static void jsB_new_FigureTransportShip(js_State *J) {
    const int fid = js_gettop(J) > 1 ? (int)js_tointeger(J, 1) : 0;
    js_push_figure_transport_ship(J, fid);
}

void js_register_figure_transport_ship_proto(js_State *J) {
    g_figure_transport_ship_proto = jsV_newobject(J, JS_COBJECT, J->Object_prototype);
    js_pushobject(J, g_figure_transport_ship_proto);

    jsB_propf(J, js_intern("FigureTransportShip.prototype.__valid"), figure_transport_ship_proto___valid, 0);
    jsB_propf(J, js_intern("FigureTransportShip.prototype.__has_troops"), figure_transport_ship_proto___has_troops, 0);
    jsB_propf(J, js_intern("FigureTransportShip.prototype.__can_embark"), figure_transport_ship_proto___can_embark, 0);
    jsB_propf(J, js_intern("FigureTransportShip.prototype.__transported_formation"), figure_transport_ship_proto___transported_formation, 0);
    jsB_propf(J, js_intern("FigureTransportShip.prototype.__phase"), figure_transport_ship_proto___phase, 0);
    jsB_propf(J, js_intern("FigureTransportShip.prototype.embark"), figure_transport_ship_proto_embark, 1);
    jsB_propf(J, js_intern("FigureTransportShip.prototype.sail_to"), figure_transport_ship_proto_sail_to, 2);
    jsB_propf(J, js_intern("FigureTransportShip.prototype.toString"), figure_transport_ship_proto_toString, 0);

    J->newcconstructor(jsB_new_FigureTransportShip, jsB_new_FigureTransportShip, js_intern("FigureTransportShip"), 1);
    js_defglobal(J, js_intern("FigureTransportShip"), JS_DONTENUM);
}
