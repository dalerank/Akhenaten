#include "empire/empire_markers.h"

#include "core/calc.h"
#include "empire/empire.h"
#include "empire/empire_object.h"
#include "game/resource.h"
#include "js/js_game.h"
#include "scenario/request.h"
#include "scenario/scenario.h"

#include <algorithm>

const e_empire_marker_kind_tokens_t ANK_CONFIG_ENUM(e_empire_marker_kind_tokens);
empire_markers_rules_t ANK_VARIABLE(empire_markers_rules);
empire_markers_t g_empire_markers;

namespace {

    constexpr int EMPIRE_ROUTES = 50;
    constexpr int ROUTE_KIND_SEA = 2;

    const map_route_object* marker_route(int route_id) {
        // OG io/empire_file.c: route 0 never has a path.
        if (route_id <= 0 || route_id >= EMPIRE_ROUTES) {
            return nullptr;
        }
        const map_route_object& route = g_empire.get_route_object(route_id);
        return (route.in_use && route.num_points > 1 && route.path_length > 0) ? &route : nullptr;
    }

    // OG empire_window.c route_path_point.
    vec2i route_point_at_percent(const map_route_object& route, int percent, int offset) {
        const int length = route.path_length;
        percent = std::clamp(percent, 0, 100);
        const int index = std::min(length * percent / 100 + offset, length - 1);
        return route.path_point(index);
    }

    // OG empire.c empire_route_find_for_city: whether the route begins at our city (the end nearer to it).
    bool route_starts_at_ourcity(const map_route_object& route) {
        const empire_object* ours = g_empire.ourcity_object();
        if (!ours) {
            return false;
        }
        const vec2i first = route.points[0].p;
        const vec2i last = route.points[route.num_points - 1].p;
        return calc_maximum_distance(first, ours->pos) < calc_maximum_distance(last, ours->pos);
    }

} // namespace

void empire_markers_t::update() {
    anim_counter++;
    if (anim_counter > empire_markers_rules.anim_counter_max) {
        anim_counter = 0;
    }
    rebuild();
}

void empire_markers_t::rebuild() {
    markers.clear();
    add_invasions();
    add_troops();
    if (!selected()) {
        clear_selection();
    }
}

// OG empire_window.c:615-640: an invasion shows once it is no farther than its route takes, and creeps on.
void empire_markers_t::add_invasions() {
    if (!g_scenario.events.og_invasions) {
        return;
    }
    const auto& rules = empire_markers_rules;
    for (int i = 0; i < g_scenario.events.events_count() && !markers.full(); i++) {
        const event_ph_t* e = g_scenario.events.at(i);
        if (!e || e->type != EVENT_TYPE_INVASION || !scenario_invasion_is_running(*e)) {
            continue;
        }
        const map_route_object* route = marker_route(e->route_fields[0]);
        if (!route) {
            continue;
        }
        const int months = scenario_invasion_months_left(*e);
        const int total = route->travel_months();
        if (months > total) {
            continue;
        }
        int percent = 100 - months * 100 / total;
        if (percent > 100) {
            percent = 0;
        }
        const int offset
          = std::max(0, (anim_counter - rules.anim_offset_start) / std::max(1, rules.anim_offset_divisor));
        markers.push_back({e->event_id, EMPIRE_MARKER_INVASION, route->route_type == ROUTE_KIND_SEA,
          route_point_at_percent(*route, percent, offset), {}});
    }
}

// OG empire_window.c:641-659 with editor/scenario_event_methods.c troops_request_state.
void empire_markers_t::add_troops() {
    for (int i = 0; i < g_scenario.events.events_count() && !markers.full(); i++) {
        const event_ph_t* e = g_scenario.events.at(i);
        if (!e || e->type != EVENT_TYPE_REQUEST || !e->is_active || e->item.value != RESOURCE_TROOPS) {
            continue;
        }
        const map_route_object* route = marker_route(scenario_request_route(*e));
        if (!route) {
            continue;
        }
        const int travel = std::max(1, scenario_request_travel_months(*e));
        int percent;
        e_empire_marker_kind kind;
        switch (e->event_state) {
        case e_event_state_troops_away:
            percent = 100 - e->quest_months_left * 100 / travel;
            kind = EMPIRE_MARKER_TROOPS_AWAY;
            break;
        case e_event_state_troops_return:
        case e_event_state_troops_return_too_late:
            percent = e->quest_months_left * 100 / travel;
            kind = EMPIRE_MARKER_TROOPS_RETURN;
            break;
        default:
            continue;
        }
        percent = std::clamp(percent, 0, 100);
        // The percent runs from our city: the troops march off from it and come back to it.
        if (!route_starts_at_ourcity(*route)) {
            percent = 100 - percent;
        }
        markers.push_back(
          {e->event_id, kind, route->route_type == ROUTE_KIND_SEA, route_point_at_percent(*route, percent, 0), {}});
    }
}

void empire_markers_t::set_size(int index, vec2i size) {
    if (index >= 0 && index < (int)markers.size()) {
        markers[index].size = size;
    }
}

bool empire_markers_t::select(vec2i map_pos, int object_distance) {
    int best = std::min(empire_markers_rules.pick_distance, object_distance);
    selected_event = -1;
    for (const empire_marker_t& m : markers) {
        const int d = calc_maximum_distance(map_pos, vec2i(m.pos.x + m.size.x / 2, m.pos.y + m.size.y / 2));
        if (d < best) {
            best = d;
            selected_event = m.event_id;
        }
    }
    return selected_event >= 0;
}

const empire_marker_t* empire_markers_t::selected() const {
    if (selected_event < 0) {
        return nullptr;
    }
    for (const empire_marker_t& m : markers) {
        if (m.event_id == selected_event) {
            return &m;
        }
    }
    return nullptr;
}
