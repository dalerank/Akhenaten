#include "request.h"

#include "js/js_game.h"
#include "scenario/scenario.h"
#include "scenario/scenario_event_manager.h"
#include "scenario/scenario_invasion.h"
#include "empire/empire.h"
#include "core/variant.h"
#include "core/profiler.h"
#include "game/game.h"

#include <algorithm>

void ANK_FUNCTION_UNIFIED(__city_create_good_request)(const bvariant_map &args) {
    int8_t city_id = (int8_t)args.i32("city_id", -1);
    const xstring city_name = args.s("city");
    if (city_id < 0 && !city_name.empty()) {
        city_id = (int8_t)g_empire.find_city_name_id(city_name.c_str());
    }
    g_scenario.events.create_good_request(
        args.n("tag_id"),
        (e_resource)args.n("resource"),
        args.n("amount"),
        args.n("months_initial"),
        (int8_t)args.i32("subtype", 0),
        (e_event_trigger_type)args.i32("trigger", EVENT_TRIGGER_ONCE),
        city_id
    );
}

void ANK_FUNCTION_UNIFIED(__city_create_pharaoh_gift)(const bvariant_map &args) {
    g_scenario.events.create_pharaoh_gift(
        args.n("tag_id"), (e_resource)args.n("resource"), args.n("amount")
    );
}

void ANK_FUNCTION_UNIFIED(__city_event_create_foreign_army_attack_warning)(const bvariant_map &args) {
    g_scenario.events.create_foreign_army_attack_warning(
        args.n("tag_id"),
        (int8_t)args.i32("sender_faction", 0),
        args.i32("months", args.i32("months_initial", 0)),
        args.i32("invader", args.i32("item", 0)));
}

void ANK_FUNCTION_UNIFIED(__city_event_create_distant_battle)(const bvariant_map &args) {
    const xstring pcity = args.s("city");
    g_scenario.events.create_distant_battle(args.n("tag_id"), pcity.c_str(), args.vec2i_or_def("pos", {0, 0}));
}

void __city_request_set_image(int tag, xstring image) {
    g_scenario.events.set_request_image(tag, image);
}
ANK_FUNCTION_2(__city_request_set_image)

void __city_request_set_reasons(int tag, int r1, int r2, int r3, int r4) {
    g_scenario.events.set_request_reasons(tag, r1, r2, r3, r4);
}
ANK_FUNCTION_5(__city_request_set_reasons)

void __city_request_set_location_fields(int tag, int l1, int l2, int l3, int l4) {
    g_scenario.events.set_request_location_fields(tag, l1, l2, l3, l4);
}
ANK_FUNCTION_5(__city_request_set_location_fields)

void __city_request_set_sender_faction(int tag, int sender_faction) {
    g_scenario.events.set_request_sender_faction(tag, sender_faction);
}
ANK_FUNCTION_2(__city_request_set_sender_faction)

void __city_request_execute(int tag) {
    g_scenario.events.execute_event(tag);
}
ANK_FUNCTION_1(__city_request_execute)

// True if any EVENT_TYPE_REQUEST for this resource is currently is_active.
bool __city_has_active_request(int resource) {
    const e_resource res = (e_resource)resource;
    for (int i = 0; i < g_scenario.events.events_count(); ++i) {
        const event_ph_t *e = g_scenario.events.at(i);
        if (!e || e->type != EVENT_TYPE_REQUEST || !e->is_active) {
            continue;
        }
        if ((e_resource)e->item.value == res) {
            return true;
        }
    }
    return false;
}
ANK_FUNCTION_1(__city_has_active_request)

// Fire an ONLY_VIA_EVENT master (chain child) from JS — e.g. force troops×4 if luxury late never came.
void __city_event_fire_chain(int tag) {
    event_ph_t *only_via = nullptr;
    event_ph_t *burned = nullptr;
    for (int i = 0; i < g_scenario.events.events_count(); ++i) {
        event_ph_t *e = g_scenario.events.at(i);
        if (!e || e->tag_id != tag) {
            continue;
        }
        if (e->event_trigger_type == EVENT_TRIGGER_ONLY_VIA_EVENT) {
            only_via = e;
            break;
        }
        if (e->event_trigger_type == EVENT_TRIGGER_ALREADY_FIRED && !burned) {
            burned = e;
        }
    }
    event_ph_t *e = only_via ? only_via : burned;
    if (!e) {
        return;
    }
    // caller_event_id=0: header slot (always valid); used only for activation date math.
    g_scenario.events.process_event(e->event_id, true, EVENT_ACTION_COMPLETED, 0);
}
ANK_FUNCTION_1(__city_event_fire_chain)

void __city_request_set_param(int tag, pcstr name, int param1) {
    g_scenario.events.set_request_param(tag, name, param1);
}
ANK_FUNCTION_3(__city_request_set_param)

void ANK_FUNCTION_UNIFIED(__city_create_chain_event)(const bvariant_map &args) {
    int8_t city_id = (int8_t)args.i32("city_id", -1);
    const xstring city_name = args.s("city");
    if (city_id < 0 && !city_name.empty()) {
        city_id = (int8_t)g_empire.find_city_name_id(city_name.c_str());
    }

    const e_resource resource = (e_resource)args.i32("resource", args.i32("item", RESOURCE_NONE));
    const e_event_trigger_type trigger = (e_event_trigger_type)args.i32(
        "trigger", EVENT_TRIGGER_ONLY_VIA_EVENT);
    g_scenario.events.create_chain_event(
        args.n("tag_id"),
        (e_event_type)args.n("type"),
        args.n("amount"),
        resource,
        (int8_t)args.i32("subtype", 0),
        city_id,
        trigger
    );
}

// city.create_invasion: keys as in a mission events[] invasion entry. `delay` (months from now) replaces
// year/month; for a chain template (trigger ONLY_VIA) it is the delay after the parent fires.
int ANK_FUNCTION_UNIFIED(__city_create_invasion)(const bvariant_map &args) {
    event_manager_t::invasion_event_desc desc;
    desc.tag = args.i32("tag_id", 0);
    desc.trigger = (e_event_trigger_type)args.i32("trigger", EVENT_TRIGGER_ONCE);
    desc.invader = args.i32("invader", EVENT_INVADER_ENEMY);
    desc.amount = args.i32("amount", 0);
    desc.months_initial = args.i32("months_initial", 0);
    desc.route = args.i32("route", 0);
    desc.attack_target = (int8_t)args.i32("attack_target", EVENT_ATTACK_TARGET_RANDOM);

    const int delay = args.i32("delay", -1);
    if (desc.trigger == EVENT_TRIGGER_ONLY_VIA_EVENT) {
        desc.year = std::max(delay, 0);
    } else if (delay >= 0) {
        const int month_abs = game.simtime.years_since_start() * 12 + game.simtime.month + delay;
        desc.year = month_abs / 12;
        desc.month = month_abs % 12;
    } else {
        desc.year = args.i32("year", game.simtime.years_since_start());
        desc.month = args.i32("month", game.simtime.month);
    }
    return g_scenario.events.create_invasion(desc);
}

void __city_request_set_completed_action(int master_tag, int slave_tag) {
    g_scenario.events.set_request_completed_action(master_tag, slave_tag);
}
ANK_FUNCTION_2(__city_request_set_completed_action)

void __city_request_set_refusal_action(int master_tag, int slave_tag) {
    g_scenario.events.set_request_refusal_action(master_tag, slave_tag);
}
ANK_FUNCTION_2(__city_request_set_refusal_action)

void __city_request_set_too_late_action(int master_tag, int slave_tag) {
    g_scenario.events.set_request_too_late_action(master_tag, slave_tag);
}
ANK_FUNCTION_2(__city_request_set_too_late_action)

void __city_request_set_defeat_action(int master_tag, int slave_tag) {
    g_scenario.events.set_request_defeat_action(master_tag, slave_tag);
}
ANK_FUNCTION_2(__city_request_set_defeat_action)

int ANK_FUNCTION_UNIFIED(__city_start_foreign_army_invasion)(const bvariant_map &args) {
    invasion_opts_t opts;
    opts.mode = (e_attack_faction)args.i32("mode", ATTACK_TYPE_ENEMIES);
    opts.enemy_type = (e_enemy_type)args.i32("enemy", ENEMY_0_BARBARIAN);
    opts.size = args.i32("size", 0);
    opts.invasion_point = { args.i32("tilex", -1), args.i32("tiley", -1) };
    opts.invasion_id = args.i32("invasion_id", 0);
    opts.want_destroy = (uint8_t)args.i32("want_destroy_buildings", 0);
    opts.attack_type = formation_attack_from_event_target(
        args.i32("invasion_attack_target", EVENT_ATTACK_TARGET_RANDOM));
    opts.on_completed_tag = (uint16_t)args.i32("on_completed_tag", 0);
    opts.on_refusal_tag = (uint16_t)args.i32("on_refusal_tag", 0);
    opts.on_defeat_tag = (uint16_t)args.i32("on_defeat_tag", 0);
    opts.via_sea = args.i32("via_sea", 0) != 0;
    opts.sea_point_index = (int8_t)args.i32("sea_point", -1);
    // Optional spawn kind (favour → INVASION_KIND_KINGDOME). Omitted → derive.
    {
        const int kind_arg = args.i32("kind", -1);
        if (kind_arg >= 0 && kind_arg < INVASION_KIND_MAX) {
            opts.kind = (e_invasion_spawn_kind)kind_arg;
        }
    }
    return scenario_invasion_start(opts);
}

int __city_invasion_history_count() {
    return g_invasions.history_entry_count();
}
ANK_FUNCTION(__city_invasion_history_count)

int __city_invasion_history_seq(int index) {
    const invasion_history_entry_t *e = g_invasions.history_at(index);
    return e ? (int)e->seq : 0;
}
ANK_FUNCTION_1(__city_invasion_history_seq)

int __city_invasion_history_year(int index) {
    const invasion_history_entry_t *e = g_invasions.history_at(index);
    return e ? (int)e->year : 0;
}
ANK_FUNCTION_1(__city_invasion_history_year)

int __city_invasion_history_month(int index) {
    const invasion_history_entry_t *e = g_invasions.history_at(index);
    return e ? (int)e->month : 0;
}
ANK_FUNCTION_1(__city_invasion_history_month)

int __city_invasion_history_invasion_id(int index) {
    const invasion_history_entry_t *e = g_invasions.history_at(index);
    return e ? (int)e->invasion_id : 0;
}
ANK_FUNCTION_1(__city_invasion_history_invasion_id)

int __city_invasion_history_size(int index) {
    const invasion_history_entry_t *e = g_invasions.history_at(index);
    return e ? (int)e->size : 0;
}
ANK_FUNCTION_1(__city_invasion_history_size)

int __city_invasion_history_outcome(int index) {
    const invasion_history_entry_t *e = g_invasions.history_at(index);
    return e ? (int)e->outcome : 0;
}
ANK_FUNCTION_1(__city_invasion_history_outcome)
