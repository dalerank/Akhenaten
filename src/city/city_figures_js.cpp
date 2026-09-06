#include "city/city.h"

#include "figure/figure.h"
#include "figure/figure_static_params.h"
#include "game/resource.h"
#include "core/direction.h"
#include "window/window_info.h"
#include "city/city.h"
#include "io/gamefiles/lang.h"
#include "game/game.h"

#include "js/js_game.h"
#include "js/js.h"
#include "js/js_mujs_bound_offset.h"
#include "mujs/mujs.h"
#include "mujs/jsvalue.h"
#include "mujs/jsbuiltin.h"
#include "core/bstring.h"
#include "core/log.h"
#include "core/object_property.h"
#include "core/profiler.h"

std::optional<bvariant> __city_get_figures_property(pcstr property) {
    return archive_helper::get(g_city.figures, property, true);
}
ANK_FUNCTION_1(__city_get_figures_property)

void __city_remove_figures(int ftype) { g_city.figures.remove_figures((e_figure_type)ftype); }
ANK_FUNCTION_1(__city_remove_figures)

int __figure_get_type(int fid) {
    if (!fid) {
        return 0;
    }
    figure *f = figure_get(fid);
    return f ? (int)f->type : 0;
}
ANK_FUNCTION_1(__figure_get_type)

bool __figure_is_valid(int fid) {
    if (!fid) {
        return false;
    }
    figure *f = figure_get(fid);
    return f && f->is_valid();
}
ANK_FUNCTION_1(__figure_is_valid)

bool __figure_is_scared(int fid) {
    figure *f = figure_get(fid);
    return f && f->is_valid() && f->is_scared();
}
ANK_FUNCTION_1(__figure_is_scared)

int __figure_get_action_state(int fid) {
    if (!fid) {
        return 0;
    }
    figure *f = figure_get(fid);
    return f ? f->action_state : 0;
}
ANK_FUNCTION_1(__figure_get_action_state)

int __figure_get_target_figure_id(int fid) {
    if (!fid) {
        return 0;
    }
    figure *f = figure_get(fid);
    return f ? f->target_figure_id : 0;
}
ANK_FUNCTION_1(__figure_get_target_figure_id)

int __figure_get_destination_building_id(int fid) {
    if (!fid) {
        return 0;
    }
    figure *f = figure_get(fid);
    return f ? f->destination_building_id : 0;
}
ANK_FUNCTION_1(__figure_get_destination_building_id)

int __figure_get_home_building_id(int fid) {
    if (!fid) {
        return 0;
    }
    figure *f = figure_get(fid);
    return f ? f->homeID() : 0;
}
ANK_FUNCTION_1(__figure_get_home_building_id)

int __figure_get_state(int fid) {
    if (!fid) {
        return 0;
    }
    figure *f = figure_get(fid);
    return f ? (int)f->state : 0;
}
ANK_FUNCTION_1(__figure_get_state)

int __figure_get_resource(int fid) {
    if (!fid) {
        return (int)RESOURCE_NONE;
    }
    figure *f = figure_get(fid);
    return f ? (int)f->get_resource() : (int)RESOURCE_NONE;
}
ANK_FUNCTION_1(__figure_get_resource)

int __figure_get_resource_amount(int fid) {
    if (!fid) {
        return 0;
    }
    figure *f = figure_get(fid);
    return f ? f->resource_amount_full : 0;
}
ANK_FUNCTION_1(__figure_get_resource_amount)

int __figure_get_direction(int fid) {
    if (!fid) {
        return 0;
    }
    figure *f = figure_get(fid);
    return f ? f->direction : 0;
}
ANK_FUNCTION_1(__figure_get_direction)

int __figure_get_wait_ticks(int fid) {
    if (!fid) {
        return 0;
    }
    figure *f = figure_get(fid);
    return f ? f->wait_ticks : 0;
}
ANK_FUNCTION_1(__figure_get_wait_ticks)

int __figure_get_movement_watchdog(int fid) {
    if (!fid) {
        return 0;
    }
    figure *f = figure_get(fid);
    return f ? f->movement_ticks_watchdog : 0;
}
ANK_FUNCTION_1(__figure_get_movement_watchdog)

bool __figure_is_on_previous_tile(int fid) {
    if (!fid) {
        return false;
    }
    figure *f = figure_get(fid);
    return f && f->tile == f->previous_tile;
}
ANK_FUNCTION_1(__figure_is_on_previous_tile)

tile2i __figure_get_tile(int fid) {
    if (!fid) {
        return tile2i::invalid;
    }
    figure *f = figure_get(fid);
    return (f && f->is_valid()) ? f->tile : tile2i::invalid;
}
ANK_FUNCTION_1(__figure_get_tile)

xstring __figure_get_anim_key(int fid) {
    if (!fid) {
        return {};
    }
    figure *f = figure_get(fid);
    return (f && f->is_valid()) ? f->animctx.key : xstring{};
}
ANK_FUNCTION_1(__figure_get_anim_key)

xstring __figure_phrase_text(int fid) {
    figure *f = figure_get(fid);
    if (!f || !f->is_valid()) {
        return {};
    }

    const auto sound_reaction = f->dcast()->get_sound_reaction(f->phrase_key);
    if (!sound_reaction.text.empty()) {
        return sound_reaction.text;
    }
    pcstr localized = lang_get_string(sound_reaction.group, sound_reaction.id);
    if (localized && *localized) {
        return xstring(localized);
    }
    bstring64 fallback;
    fallback.printf("#%s", sound_reaction.key.c_str());
    return xstring(fallback.c_str());
}
ANK_FUNCTION_1(__figure_phrase_text)

void __figure_info_set_help(int fid) {
    figure *f = figure_get(fid);
    if (!f || !f->is_valid()) {
        return;
    }
    object_info &c = common_info_window::get_object_info();
    const auto &meta = figure_static_params::get(f->type).meta;
    c.help_link = meta.help_link;
    c.help_id = 0;
    c.group_id = meta.text_id;
}
ANK_FUNCTION_1(__figure_info_set_help)

static js_Object *g_figure_proto = nullptr;

static int figure_this_id(js_State *J) {
    J->getproperty(J->toobject(0), js_intern("id"));
    const int id = (int)js_tointeger(J, -1);
    js_pop(J, 1);
    return id;
}

static void js_push_figure(js_State *J, int id) {
    figure *f = figure_get(id);
    js_pushobject(J, jsV_newobject(J, JS_COBJECT, g_figure_proto));
    js_pushnumber(J, (double)id);
    js_setproperty(J, -2, js_intern("id"));
    js_register_cobj_ptr_property(J, f);
}

static void jsB_new_Figure(js_State *J) {
    const int id = js_gettop(J) > 1 ? (int)js_tointeger(J, 1) : 0;
    js_push_figure(J, id);
}

static void figure_proto___property_getter(js_State *J) {
    const int fid = figure_this_id(J);
    xstring prop = js_toxstring(J, 1);
    figure *f = figure_get(fid);
    if (!f || !f->is_valid()) {
        J->pushundefined();
        return;
    }

    const bvariant value = f->dcast()->get_property(tags().figure, prop);
    if (value.value_type() == bvariant::etype_none) {
        logs::error("figure: JS read of unregistered property '%s' on figure type %d "
                    "(add a CPTROFF binding in js_register_figure or a get binding)",
                    prop.c_str(), (int)f->type);
        J->pushundefined();
    } else {
        js_helpers::js_push_bvariant(J, value);
    }
}

static void figure_proto___valid(js_State *J) {
    js_helpers::js_push_value(J, __figure_is_valid(figure_this_id(J)));
}

static void figure_proto___is_on_previous_tile(js_State *J) {
    js_helpers::js_push_value(J, __figure_is_on_previous_tile(figure_this_id(J)));
}

static void figure_proto___anim_key(js_State *J) {
    js_helpers::js_push_value(J, __figure_get_anim_key(figure_this_id(J)));
}

static void figure_proto___overlay(js_State *J) {
    const int fid = figure_this_id(J);
    figure *f = figure_get(fid);
    js_helpers::js_push_value(J, f && f->is_valid() ? (int)f->dcast()->get_overlay() : (int)OVERLAY_NONE);
}

static void figure_proto_setup_phrase(js_State *J) {
    figure *f = figure_get(figure_this_id(J));
    if (f && f->is_valid()) {
        f->dcast()->setup_phrase();
    }
    J->pushundefined();
}

static void figure_proto_sound_path(js_State *J) {
    figure *f = figure_get(figure_this_id(J));
    xstring prop = js_toxstring(J, 1);
    js_helpers::js_push_value(J, f && f->is_valid() ? f->dcast()->get_sound_reaction(prop).sound : xstring());
}

static void figure_proto_toString(js_State *J) {
    const int id = figure_this_id(J);
    figure *f = figure_get(id);
    if (!f || !f->is_valid()) {
        J->pushstring("Figure(invalid)");
        return;
    }

    bstring64 text;
    text.printf("Figure(%d, type=%d)", id, (int)f->type);
    J->pushstring(text.c_str());
}

void js_register_figure(js_State *J) {
    g_figure_proto = jsV_newobject(J, JS_COBJECT, J->Object_prototype);
    js_pushobject(J, g_figure_proto);

    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, figure, type);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, figure, action_state);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, figure, state);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, figure, wait_ticks);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, figure, direction);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, figure, target_figure_id);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, figure, destination_building_id);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, figure, home_building_id);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, figure, movement_ticks_watchdog);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, figure, resource_id);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, figure, resource_amount_full);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, figure, draw_mode);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, figure, phrase_key);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, figure, phrase_sound);
    JS_REGISTER_BOUND_OFFSET_MEMBER_LIT(J, figure, min_max_seen);

    jsB_propf(J, js_intern("Figure.prototype.__property_getter"), figure_proto___property_getter, 1);
    jsB_propf(J, js_intern("Figure.prototype.__valid"), figure_proto___valid, 0);
    jsB_propf(J, js_intern("Figure.prototype.__is_on_previous_tile"), figure_proto___is_on_previous_tile, 0);
    jsB_propf(J, js_intern("Figure.prototype.__anim_key"), figure_proto___anim_key, 0);
    jsB_propf(J, js_intern("Figure.prototype.__overlay"), figure_proto___overlay, 0);
    jsB_propf(J, js_intern("Figure.prototype.setup_phrase"), figure_proto_setup_phrase, 0);
    jsB_propf(J, js_intern("Figure.prototype.sound_path"), figure_proto_sound_path, 1);
    jsB_propf(J, js_intern("Figure.prototype.toString"), figure_proto_toString, 0);

    js_newcconstructor(J, jsB_new_Figure, jsB_new_Figure, js_intern("Figure"), 1);
    js_defglobal(J, js_intern("Figure"), JS_DONTENUM);
}