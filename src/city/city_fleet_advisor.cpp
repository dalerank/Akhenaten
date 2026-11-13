#include "city/city_fleet_advisor.h"

#include "building/building.h"
#include "building/building_warship_wharf.h"
#include "city/city.h"
#include "city/legion_requests.h"
#include "core/calc.h"
#include "figure/figure.h"
#include "figure/formation.h"
#include "figuretype/figure_war_ship.h"
#include "grid/water.h"
#include "scenario/distant_battle.h"
#include "scenario/request.h"
#include "scenario/scenario_invasion.h"

#include <algorithm>
#include <iterator>

namespace {

    enum e_fleet_military_text {
        MILITARY_TEXT_NO_THREATS = 8,
        MILITARY_TEXT_ENEMIES_APPROACHING = 9,
        MILITARY_TEXT_ENEMIES_IN_SIGHT = 10,
        MILITARY_TEXT_KINGDOM_TROOPS_AT_GATES = 11,
        MILITARY_TEXT_NO_REQUESTS_ABROAD = 12,
        MILITARY_TEXT_TROOPS_NEEDED_ABROAD = 13,
        MILITARY_TEXT_MARCHING_TO_FIGHT = 14,
        MILITARY_TEXT_MARCHING_BACK = 15,
        MILITARY_TEXT_NAVY_NEEDED = 26,
        MILITARY_TEXT_SAILING_TO_FIGHT = 27,
        MILITARY_TEXT_SAILING_BACK = 28,
    };

    enum e_fleet_ship_text {
        SHIP_TEXT_HULL_VERY_STRONG = 3,
        SHIP_TEXT_HULL_WEAK = 8,
        SHIP_TEXT_CREW_RESTED = 28,
        SHIP_TEXT_CREW_TIRED = 29,
        SHIP_TEXT_CREW_EXHAUSTED = 30,
    };

    // OG ship_hull_text_rules, warship column: weak, fair, average, good, strong.
    constexpr int warship_hull_thresholds[] = {15, 30, 50, 70, 90};

    figure_warship* warship_of(int figure_id) {
        figure* f = figure_id > 0 ? figure_get(figure_id) : nullptr;
        return f ? smart_cast<figure_warship>(f) : nullptr;
    }

    template <typename F>
    void for_each_warship(F&& fn) {
        for (int id = 1; id < MAX_FIGURES; id++) {
            figure* f = figure_get(id);
            if (!f || !f->is_alive() || f->type != FIGURE_WARSHIP) {
                continue;
            }
            if (auto* ship = smart_cast<figure_warship>(f)) {
                fn(ship);
            }
        }
    }

    bool ship_is_free(figure_warship* ship) {
        return ship->runtime_data().request_event_id < 0;
    }

    uint8_t hull_text(figure_warship* ship) {
        const int max_hp = ship->base.max_damage();
        const int hp = std::max(0, max_hp - (int)ship->base.damage);
        const int percentage = calc_percentage(hp, max_hp);
        for (int rule = 0; rule < (int)std::size(warship_hull_thresholds); rule++) {
            if (percentage <= warship_hull_thresholds[rule]) {
                return (uint8_t)(SHIP_TEXT_HULL_WEAK - rule);
            }
        }
        return SHIP_TEXT_HULL_VERY_STRONG;
    }

    uint8_t crew_text(figure_warship* ship) {
        switch (ship->runtime_data().ship_move_mode) {
        case WARSHIP_MOVE_FULL_SPEED:
            return SHIP_TEXT_CREW_RESTED;
        case WARSHIP_MOVE_SLOW:
            return SHIP_TEXT_CREW_TIRED;
        default:
            return SHIP_TEXT_CREW_EXHAUSTED;
        }
    }

    bool ship_at_dock(figure_warship* ship) {
        building* home_b = ship->home();
        auto* wharf = home_b ? home_b->dcast_warship_wharf() : nullptr;
        if (!wharf) {
            return false;
        }
        const tile2i dock = wharf->get_water_access_tiles().point_a;
        return dock.valid() && ship->base.destination_tile == dock;
    }

    uint8_t threat_text() {
        if (g_city.figures.kingdome_soldiers != 0) {
            return MILITARY_TEXT_KINGDOM_TROOPS_AT_GATES;
        }
        if (g_city.figures.enemies != 0) {
            return MILITARY_TEXT_ENEMIES_IN_SIGHT;
        }
        return scenario_invasion_exists_upcoming() ? MILITARY_TEXT_ENEMIES_APPROACHING : MILITARY_TEXT_NO_THREATS;
    }

    // OG reads abroad/returning from the troop request's state; here the dispatched
    // request is tracked by the distant battle it started.
    uint8_t request_text(const fleet_troop_requests& requests) {
        const auto& battle = g_distant_battle.battle;
        const int source = g_distant_battle.source_request_event_id;
        const bool by_sea = source >= 0 && troop_request_is_sea(source);
        if (battle.egyptian_months_to_travel_back > 0) {
            return by_sea ? MILITARY_TEXT_SAILING_BACK : MILITARY_TEXT_MARCHING_BACK;
        }
        if (battle.egyptian_months_to_travel_forth > 0) {
            return by_sea ? MILITARY_TEXT_SAILING_TO_FIGHT : MILITARY_TEXT_MARCHING_TO_FIGHT;
        }
        if (requests.by_land()) {
            return MILITARY_TEXT_TROOPS_NEEDED_ABROAD;
        }
        if (requests.by_sea()) {
            return MILITARY_TEXT_NAVY_NEEDED;
        }
        return MILITARY_TEXT_NO_REQUESTS_ABROAD;
    }

    void count_service_legions(int& on_land, int& on_ship) {
        on_land = 0;
        on_ship = 0;
        for (int id = 1; id < MAX_FORMATIONS; id++) {
            const formation* m = formation_get(id);
            if (!m || !m->in_use || !m->own_batalion || !m->empire_service || m->num_figures == 0
                || m->request_event_id >= 0) {
                continue;
            }
            if (formation_legion_is_on_ship(id)) {
                on_ship++;
            } else {
                on_land++;
            }
        }
    }

} // namespace

fleet_troop_requests fleet_count_troop_requests() {
    fleet_troop_requests r;
    for (const scenario_request& request : scenario_get_visible_requests()) {
        if (request.resource != RESOURCE_TROOPS) {
            continue;
        }
        if (troop_request_is_sea(request.event_id)) {
            if (r.first_by_sea < 0) {
                r.first_by_sea = request.event_id;
            }
            r.count_by_sea++;
        } else {
            if (r.first_by_land < 0) {
                r.first_by_land = request.event_id;
            }
            r.count_by_land++;
        }
    }
    return r;
}

int fleet_warship_by_index(int index) {
    int n = 0;
    int found = 0;
    for_each_warship([&](figure_warship* ship) {
        if (!found && ++n == index) {
            found = ship->id();
        }
    });
    return found;
}

fleet_ship_status fleet_ship_status_by_index(int index) {
    fleet_ship_status s;
    figure_warship* ship = warship_of(fleet_warship_by_index(index));
    if (!ship) {
        return s;
    }
    s.figure_id = ship->id();
    s.free = ship_is_free(ship);
    s.at_dock = ship_at_dock(ship);
    s.in_service = ship->runtime_data().answers_requests != 0;
    s.hull_text = hull_text(ship);
    s.crew_text = crew_text(ship);
    return s;
}

fleet_advisor_status fleet_advisor_collect() {
    fleet_advisor_status st;
    st.requests = fleet_count_troop_requests();
    for (int id = 1; id < MAX_FIGURES; id++) {
        const figure* f = figure_get(id);
        if (f && f->is_alive() && f->type == FIGURE_TRANSPORT_SHIP) {
            st.total_transports++;
        }
    }
    for_each_warship([&](figure_warship* ship) {
        auto& d = ship->runtime_data();
        st.total_warships++;
        if (!st.requests.by_sea() && ship_is_free(ship)) {
            d.answers_requests = 0;
        }
        if (d.answers_requests != 0) {
            st.warships_in_service++;
            if (ship_is_free(ship)) {
                st.any_free_in_service = true;
            }
        }
    });
    st.threat_text = threat_text();
    st.request_text = request_text(st.requests);
    return st;
}

tile2i fleet_ship_tile(int index) {
    figure_warship* ship = warship_of(fleet_warship_by_index(index));
    if (!ship || !ship_is_free(ship)) {
        return tile2i::invalid;
    }
    return ship->base.tile;
}

void fleet_ship_return_to_dock(int index) {
    figure_warship* ship = warship_of(fleet_warship_by_index(index));
    if (!ship || !ship_is_free(ship)) {
        return;
    }
    ship->set_order(figure_warship::e_order_goto_wharf);
}

e_fleet_service_popup fleet_ship_toggle_service(int index) {
    figure_warship* ship = warship_of(fleet_warship_by_index(index));
    if (!ship || !ship_is_free(ship)) {
        return FLEET_SERVICE_POPUP_NONE;
    }
    const fleet_troop_requests requests = fleet_count_troop_requests();
    auto& d = ship->runtime_data();
    if (requests.by_sea()) {
        d.answers_requests = d.answers_requests == 0;
        return FLEET_SERVICE_POPUP_NONE;
    }
    d.answers_requests = 0;
    return requests.by_land() ? FLEET_SERVICE_POPUP_LAND_TROOPS_NEEDED : FLEET_SERVICE_POPUP_NO_TROOPS_NEEDED;
}

e_fleet_dispatch_result fleet_dispatch_now() {
    const fleet_advisor_status st = fleet_advisor_collect();
    if (!st.any_free_in_service) {
        return FLEET_DISPATCH_NONE;
    }
    fleet_troop_requests r = st.requests;
    int legions_on_land = 0;
    int legions_on_ship = 0;
    count_service_legions(legions_on_land, legions_on_ship);
    if (legions_on_land == 0) {
        r.first_by_land = -1;
    }
    if (legions_on_ship == 0 && st.warships_in_service == 0) {
        r.first_by_sea = -1;
    }
    if ((r.count_by_land > 1 && r.first_by_land >= 0) || (r.count_by_sea > 1 && r.first_by_sea >= 0)) {
        return FLEET_DISPATCH_SEVERAL_REQUESTS;
    }
    bool sent = false;
    for (const int event_id : {r.first_by_land, r.first_by_sea}) {
        if (event_id >= 0) {
            sent |= scenario_request_dispatch_event(event_id);
        }
    }
    return sent ? FLEET_DISPATCH_SENT : FLEET_DISPATCH_NONE;
}
