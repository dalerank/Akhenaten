#include "city/city_figures.h"
#include "figure/figure.h"
#include "figuretype/figure_war_ship.h"
#include "js/js.h"
#include "js/js_game.h"
#include "mujs/jsbuiltin.h"
#include "mujs/mujs.h"

#include <cstdio>

namespace {
figure_warship *figure_warship_get(int fid) {
    figure *f = figure_get(fid);
    return f ? smart_cast<figure_warship>(f) : nullptr;
}
} // namespace

static js_Object *g_figure_warship_proto = nullptr;

static int figure_warship_this_fid(js_State *J) {
    J->getproperty(J->toobject(0), js_intern("id"));
    const int id = (int)js_tointeger(J, -1);
    js_pop(J, 1);
    return id;
}

static figure_warship *figure_warship_this(js_State *J) {
    return figure_warship_get(figure_warship_this_fid(J));
}

static void figure_warship_proto___valid(js_State *J) {
    J->push(figure_warship_this(J) != nullptr);
}

static void figure_warship_proto___active_order(js_State *J) {
    figure_warship *ship = figure_warship_this(J);
    js_pushnumber(J, (double)(ship ? ship->runtime_data().active_order : 0));
}

static void figure_warship_proto___crew_fatigue(js_State *J) {
    figure_warship *ship = figure_warship_this(J);
    js_pushnumber(J, (double)(ship ? ship->runtime_data().crew_fatigue : 0));
}

static void figure_warship_proto___damage(js_State *J) {
    figure_warship *ship = figure_warship_this(J);
    js_pushnumber(J, (double)(ship ? ship->base.damage : 0));
}

static void figure_warship_proto___max_damage(js_State *J) {
    figure_warship *ship = figure_warship_this(J);
    js_pushnumber(J, (double)(ship ? ship->base.max_damage() : 0));
}

static void figure_warship_proto_set_order(js_State *J) {
    figure_warship *ship = figure_warship_this(J);
    const int order = J->to<int>(1);
    if (ship) {
        ship->runtime_data().active_order = (short)order;
    }
}

static void figure_warship_proto_toString(js_State *J) {
    char buf[64];
    snprintf(buf, sizeof buf, "FigureWarship(%d)", figure_warship_this_fid(J));
    J->pushstring(buf);
}

static void js_push_figure_warship(js_State *J, int fid) {
    js_pushobject(J, jsV_newobject(J, JS_COBJECT, g_figure_warship_proto));
    js_pushnumber(J, (double)fid);
    js_setproperty(J, -2, js_intern("id"));
}

static void jsB_new_FigureWarship(js_State *J) {
    const int fid = js_gettop(J) > 1 ? (int)js_tointeger(J, 1) : 0;
    js_push_figure_warship(J, fid);
}

void js_register_figure_warship_proto(js_State *J) {
    g_figure_warship_proto = jsV_newobject(J, JS_COBJECT, J->Object_prototype);
    js_pushobject(J, g_figure_warship_proto);

    jsB_propf(J, js_intern("FigureWarship.prototype.__valid"), figure_warship_proto___valid, 0);
    jsB_propf(J, js_intern("FigureWarship.prototype.__active_order"), figure_warship_proto___active_order, 0);
    jsB_propf(J, js_intern("FigureWarship.prototype.__crew_fatigue"), figure_warship_proto___crew_fatigue, 0);
    jsB_propf(J, js_intern("FigureWarship.prototype.__damage"), figure_warship_proto___damage, 0);
    jsB_propf(J, js_intern("FigureWarship.prototype.__max_damage"), figure_warship_proto___max_damage, 0);
    jsB_propf(J, js_intern("FigureWarship.prototype.set_order"), figure_warship_proto_set_order, 1);
    jsB_propf(J, js_intern("FigureWarship.prototype.toString"), figure_warship_proto_toString, 0);

    J->newcconstructor(jsB_new_FigureWarship, jsB_new_FigureWarship, js_intern("FigureWarship"), 1);
    js_defglobal(J, js_intern("FigureWarship"), JS_DONTENUM);
}
