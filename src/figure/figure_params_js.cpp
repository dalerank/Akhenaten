#include "figure/figure_static_params.h"
#include "figure/figure_type.h"
#include "js/js_game.h"
#include "js/js.h"
#include "mujs/jsbuiltin.h"
#include "mujs/jsvalue.h"

#include <cstdio>

static int figure_params_this_type(js_State *J) {
    J->getproperty(J->toobject(0), js_intern("type"));
    if (J->isundefined(-1) || J->isnull(-1)) {
        js_pop(J, 1);
        return FIGURE_NONE;
    }

    const int type = (int)js_tointeger(J, -1);
    js_pop(J, 1);
    return type;
}

static const figure_static_params *figure_params_for_type(int type) {
    if (type <= FIGURE_NONE || type >= FIGURE_MAX) {
        return nullptr;
    }
    return &figure_static_params::get((e_figure_type)type);
}

std::optional<bvariant> __figure_get_static_params_property(int type, pcstr property) {
    const figure_static_params *params = figure_params_for_type(type);
    if (!params) {
        return {};
    }
    return archive_helper::get(*params, property, true);
}
ANK_FUNCTION_2(__figure_get_static_params_property)

static js_Object *g_figure_params_proto = nullptr;

static void figure_params_proto___property_getter(js_State *J) {
    const figure_static_params *params = figure_params_for_type(figure_params_this_type(J));
    if (!params) {
        J->pushundefined();
        return;
    }

    xstring prop = js_toxstring(J, 1);
    auto opt = archive_helper::get(*params, prop, true);
    J->push<std::optional<bvariant>>(opt);
}

int figure_static_first_img_for_type(int type, xstring anim_key) {
    const figure_static_params *params = figure_params_for_type(type);
    if (!params) {
        return 0;
    }
    return params->first_img(anim_key);
}

static void figure_params_proto_first_img(js_State *J) {
    const int type = figure_params_this_type(J);
    const xstring anim_key = js_toxstring(J, 1);
    J->push(figure_static_first_img_for_type(type, anim_key));
}

static void figure_params_proto_toString(js_State *J) {
    char buf[64];
    snprintf(buf, sizeof buf, "FigureParams(type=%d)", figure_params_this_type(J));
    J->pushstring(buf);
}

static void jsB_FigureParams_for_type(js_State *J) {
    const int type = js_gettop(J) > 0 ? (int)js_tointeger(J, 1) : FIGURE_NONE;
    js_pushobject(J, jsV_newobject(J, JS_COBJECT, g_figure_params_proto));
    js_pushnumber(J, (double)type);
    js_setproperty(J, -2, js_intern("type"));
}

void js_register_figure_params(js_State *J) {
    g_figure_params_proto = jsV_newobject(J, JS_COBJECT, J->Object_prototype);
    js_pushobject(J, g_figure_params_proto);

    jsB_propf(J, js_intern("FigureParams.prototype.__property_getter"), figure_params_proto___property_getter, 1);
    jsB_propf(J, js_intern("FigureParams.prototype.first_img"), figure_params_proto_first_img, 1);
    jsB_propf(J, js_intern("FigureParams.prototype.toString"), figure_params_proto_toString, 0);

    J->newcconstructor(jsB_FigureParams_for_type, jsB_FigureParams_for_type, js_intern("FigureParams"), 1);
    jsB_propf(J, js_intern("FigureParams.for_type"), jsB_FigureParams_for_type, 1);
    js_defglobal(J, js_intern("FigureParams"), JS_DONTENUM);
}
