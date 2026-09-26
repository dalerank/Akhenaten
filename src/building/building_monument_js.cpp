#include "building/building.h"
#include "building/monuments.h"
#include "figure/figure_type.h"
#include "game/resource.h"

#include "core/bstring.h"
#include "js/js.h"
#include "js/js_game.h"
#include "mujs/jsbuiltin.h"
#include "mujs/jsvalue.h"

#include <cstdio>
#include <optional>

static bool monument_building_alive(const building* b) {
    return b && building_monument_is_alive(*b);
}

static building_monument* monument_from_building(int bid) {
    building* b = building_get(bid);
    if (!monument_building_alive(b) || !b->is_monument()) {
        return nullptr;
    }

    return b->main()->dcast_monument();
}

static int monument_this_id(js_State* J) {
    J->getproperty(J->toobject(0), js_intern("id"));
    const int id = (int)js_tointeger(J, -1);
    js_pop(J, 1);
    return id;
}

static building_monument* monument_this(js_State* J) {
    return monument_from_building(monument_this_id(J));
}

static js_Object* g_monument_proto = nullptr;

static void monument_proto___property_getter(js_State* J) {
    building_monument* m = monument_this(J);
    if (!m) {
        J->push<std::optional<bvariant>>({});
        return;
    }

    xstring prop = js_toxstring(J, 1);
    auto result = archive_helper::get(m->runtime_data(), prop, true);
    if (result.has_value()) {
        J->push<std::optional<bvariant>>(result);
        return;
    }

    J->push<std::optional<bvariant>>(archive_helper::get(m->base, prop, true));
}

static void monument_proto_need_workers(js_State* J) {
    building_monument* m = monument_this(J);
    J->push(m && m->need_workers());
}

static void monument_proto_phase(js_State* J) {
    building_monument* m = monument_this(J);
    // int8_t phase: MONUMENT_FINISHED is -1 (uint8_t phase() would wrap to 255).
    J->push(m ? (int)m->runtime_data().phase : -99);
}

static void monument_proto_phases_total(js_State* J) {
    building_monument* m = monument_this(J);
    J->push(m ? m->phases() : 0);
}

static void monument_proto_material_pct_min(js_State* J) {
    building_monument* m = monument_this(J);
    J->push(m ? m->material_pct_min() : 100);
}

static void monument_proto_need_stonemason(js_State* J) {
    building_monument* m = monument_this(J);
    J->push(m && m->need_stonemason());
}

static void monument_proto_needs_resource(js_State* J) {
    building_monument* m = monument_this(J);
    const int resource = J->to<int>(1);
    J->push(m ? m->needs_resource((e_resource)resource) : 0);
}

static void monument_proto_resource_pct(js_State* J) {
    building_monument* m = monument_this(J);
    const int resource = J->to<int>(1);
    J->push(m ? m->resource_pct((e_resource)resource) : 0);
}

static void monument_proto_workers_assigned(js_State* J) {
    building_monument* m = monument_this(J);
    J->push(m ? m->workers_assigned() : 0);
}

static void monument_proto_workers_slots(js_State* J) {
    building_monument* m = monument_this(J);
    J->push(m ? m->workers_slots() : 0);
}

static void monument_proto_workers_onsite(js_State* J) {
    building_monument* m = monument_this(J);
    const int figure_type = J->to<int>(1);
    J->push(m ? m->workers_onsite((e_figure_type)figure_type) : 0);
}

static void monument_proto_tile_progress(js_State* J) {
    const tile2i tile = J->to<tile2i>(1);
    J->push((int)map_monuments_get_progress(tile));
}

static void monument_proto_set_tile_progress(js_State* J) {
    building_monument* m = monument_this(J);
    if (m) {
        m->set_tile_progress(J->to<tile2i>(1), J->to<int>(2));
    }
    js_helpers::js_push_void(J);
}

static void monument_proto_toString(js_State* J) {
    char buf[64];
    snprintf(buf, sizeof buf, "Monument(%d)", monument_this_id(J));
    J->pushstring(buf);
}

static void jsB_new_Monument(js_State* J) {
    int id = js_gettop(J) > 1 ? (int)js_tointeger(J, 1) : 0;
    building_monument* m = monument_from_building(id);
    if (!m) {
        js_pushnull(J);
        return;
    }

    id = m->id();
    js_pushobject(J, jsV_newobject(J, JS_COBJECT, g_monument_proto));
    js_pushnumber(J, (double)id);
    js_setproperty(J, -2, js_intern("id"));
}

void js_register_monument(js_State* J) {
    js_Object* building_proto = js_get_building_prototype();
    g_monument_proto = jsV_newobject(J, JS_COBJECT, building_proto);
    js_pushobject(J, g_monument_proto);

    jsB_propf(J, js_intern("Monument.prototype.__property_getter"), monument_proto___property_getter, 1);
    jsB_propf(J, js_intern("Monument.prototype.need_workers"), monument_proto_need_workers, 0);
    jsB_propf(J, js_intern("Monument.prototype.phase"), monument_proto_phase, 0);
    jsB_propf(J, js_intern("Monument.prototype.phases_total"), monument_proto_phases_total, 0);
    jsB_propf(J, js_intern("Monument.prototype.material_pct_min"), monument_proto_material_pct_min, 0);
    jsB_propf(J, js_intern("Monument.prototype.need_stonemason"), monument_proto_need_stonemason, 0);
    jsB_propf(J, js_intern("Monument.prototype.needs_resource"), monument_proto_needs_resource, 1);
    jsB_propf(J, js_intern("Monument.prototype.resource_pct"), monument_proto_resource_pct, 1);
    jsB_propf(J, js_intern("Monument.prototype.workers_assigned"), monument_proto_workers_assigned, 0);
    jsB_propf(J, js_intern("Monument.prototype.workers_slots"), monument_proto_workers_slots, 0);
    jsB_propf(J, js_intern("Monument.prototype.workers_onsite"), monument_proto_workers_onsite, 1);
    jsB_propf(J, js_intern("Monument.prototype.tile_progress"), monument_proto_tile_progress, 1);
    jsB_propf(J, js_intern("Monument.prototype.set_tile_progress"), monument_proto_set_tile_progress, 2);
    jsB_propf(J, js_intern("Monument.prototype.toString"), monument_proto_toString, 0);

    J->newcconstructor(jsB_new_Monument, jsB_new_Monument, js_intern("Monument"), 1);
    js_defglobal(J, js_intern("Monument"), JS_DONTENUM);
}

void __map_monuments_clear() {
    map_monuments_clear();
}
ANK_FUNCTION(__map_monuments_clear)
