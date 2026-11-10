#include "city/legion_requests.h"

#include "building/building.h"
#include "building/building_warship_wharf.h"
#include "city/city.h"
#include "city/city_figures.h"
#include "core/calc.h"
#include "empire/empire.h"
#include "empire/empire_city.h"
#include "figure/formation.h"
#include "figure/route.h"
#include "figuretype/figure_soldier.h"
#include "figuretype/figure_transport_ship.h"
#include "figuretype/figure_war_ship.h"
#include "grid/routing/routing.h"
#include "grid/terrain.h"
#include "grid/water.h"
#include "scenario/map.h"
#include "scenario/scenario.h"
#include "scenario/scenario_event_manager.h"

namespace {

bool figure_is_alive_soldier(int figure_id) {
    if (figure_id <= 0) {
        return false;
    }
    figure *f = figure_get(figure_id);
    return f && f->is_alive() && f->action_state != FIGURE_ACTION_149_CORPSE;
}

bool event_request_is_sea(int event_id) {
    const event_ph_t *ev = g_scenario.events.at(event_id);
    if (ev && ev->city_id > 0) {
        empire_city *city = g_empire.city(ev->city_id);
        if (city) {
            return city->is_sea_trade;
        }
        const int route = g_empire.trade_route_for_city(ev->city_id);
        if (route > 0) {
            return g_empire.is_sea_trade_route(route);
        }
    }
    // No city/route: sea if any empire-service legion is already aboard a transport.
    for (int id = 1; id < MAX_FORMATIONS; id++) {
        formation *m = formation_get(id);
        if (m && m->in_use && m->own_batalion && m->empire_service && m->num_figures > 0
            && formation_legion_is_on_ship(id)) {
            return true;
        }
    }
    return false;
}

} // namespace

int figure_warship_request_strength(int figure_id) {
    figure *f = figure_get(figure_id);
    if (!f || !f->is_alive()) {
        return 0;
    }
    return (int)f->max_damage() / WARSHIP_STRENGTH_DIVISOR;
}

int formation_request_strength(int request_id, int *warships_out, int *legions_out) {
    if (request_id < 0) {
        if (warships_out) {
            *warships_out = 0;
        }
        if (legions_out) {
            *legions_out = 0;
        }
        return 0;
    }

    int legion_strength = 0;
    for (int id = 1; id < MAX_FORMATIONS; id++) {
        formation *m = formation_get(id);
        if (!m || !m->in_use || !m->own_batalion || !m->empire_service || m->num_figures == 0) {
            continue;
        }
        if (m->request_event_id != request_id) {
            continue;
        }
        const int base = (int)m->experience
            + ((m->figure_type == FIGURE_FCHARIOTEER) ? CHARIOTEER_STRENGTH_BASE : LEGION_STRENGTH_BASE);
        legion_strength += (base * m->num_figures) / 100;
    }
    if (legions_out) {
        *legions_out = legion_strength;
    }

    int total = legion_strength;
    for (int id = 1; id < MAX_FIGURES; id++) {
        figure *f = figure_get(id);
        if (!f || !f->is_alive() || f->type != FIGURE_WARSHIP) {
            continue;
        }
        auto *ship = smart_cast<figure_warship>(f);
        if (!ship || ship->runtime_data().request_event_id != request_id) {
            continue;
        }
        total += figure_warship_request_strength(id);
    }
    if (warships_out) {
        *warships_out = total - legion_strength;
    }
    return total;
}

int figure_find_legion_transport_ship(int formation_id) {
    if (formation_id <= 0) {
        return 0;
    }
    formation *m = formation_get(formation_id);
    if (m && m->ship_figure_id > 0) {
        figure *f = figure_get(m->ship_figure_id);
        auto *ship = f ? smart_cast<figure_transport_ship>(f) : nullptr;
        if (ship && ship->base.is_alive() && ship->transported_formation() == formation_id) {
            return m->ship_figure_id;
        }
    }
    for (int id = 1; id < MAX_FIGURES; id++) {
        figure *f = figure_get(id);
        auto *ship = f ? smart_cast<figure_transport_ship>(f) : nullptr;
        if (ship && ship->base.is_alive() && ship->transported_formation() == formation_id) {
            return id;
        }
    }
    return 0;
}

bool formation_legion_is_on_ship(int formation_id) {
    return figure_find_legion_transport_ship(formation_id) > 0;
}

void formation_legions_dispatch_to_request(int event_id) {
    if (event_id < 0) {
        return;
    }
    const bool by_sea = event_request_is_sea(event_id);

    for (int id = 1; id < MAX_FORMATIONS; id++) {
        formation *m = formation_get(id);
        if (!m || !m->in_use || !m->own_batalion || !m->empire_service || m->num_figures == 0) {
            continue;
        }
        if (m->request_event_id >= 0) {
            continue;
        }
        const bool on_ship = formation_legion_is_on_ship(id);
        if (on_ship != by_sea) {
            continue;
        }

        m->request_event_id = (int16_t)event_id;
        m->is_at_fort = 0;
        m->in_distant_battle = 1;

        if (on_ship) {
            const int ship_id = figure_find_legion_transport_ship(id);
            figure *f = figure_get(ship_id);
            auto *ship = f ? smart_cast<figure_transport_ship>(f) : nullptr;
            if (ship) {
                ship->runtime_data().request_event_id = (int16_t)event_id;
                ship->begin_kingdom_request();
            }
            continue;
        }

        for (int i = 0; i < m->num_figures; i++) {
            const int fid = m->figures[i];
            if (!figure_is_alive_soldier(fid)) {
                continue;
            }
            figure *soldier = figure_get(fid);
            auto *s = soldier ? soldier->dcast_soldier() : nullptr;
            if (s) {
                s->send_to_distant_battle();
            }
        }
    }

    if (!by_sea) {
        return;
    }

    for (int id = 1; id < MAX_FIGURES; id++) {
        figure *f = figure_get(id);
        auto *ship = f ? smart_cast<figure_warship>(f) : nullptr;
        if (!ship || !f->is_alive()) {
            continue;
        }
        auto &d = ship->runtime_data();
        if (!d.answers_requests || d.request_event_id >= 0) {
            continue;
        }
        ship->begin_kingdom_request(event_id);
    }
}

void formation_legions_return_from_request(int event_id) {
    for (int id = 1; id < MAX_FORMATIONS; id++) {
        formation *m = formation_get(id);
        if (!m || !m->in_use || !m->own_batalion || m->request_event_id != event_id) {
            continue;
        }
        m->request_event_id = -1;

        if (formation_legion_is_on_ship(id)) {
            const int ship_id = figure_find_legion_transport_ship(id);
            figure *f = figure_get(ship_id);
            auto *ship = f ? smart_cast<figure_transport_ship>(f) : nullptr;
            if (!ship) {
                continue;
            }
            ship->runtime_data().request_event_id = -1;
            tile2i land = m->home.valid() ? m->home : m->tile;
            ship->return_from_kingdom_request(land);
            continue;
        }

        for (int i = 0; i < m->num_figures; i++) {
            const int fid = m->figures[i];
            if (!figure_is_alive_soldier(fid)) {
                continue;
            }
            figure *soldier = figure_get(fid);
            if (soldier) {
                soldier->action_state = ACTION_8_SOLDIER_RETURNING_FROM_DISTANT_BATTLE;
                soldier->wait_ticks = (int16_t)(4 + (fid & 63));
                soldier->formation_at_rest = 1;
            }
        }
        m->in_distant_battle = 0;
    }

    for (int id = 1; id < MAX_FIGURES; id++) {
        figure *f = figure_get(id);
        auto *ship = f ? smart_cast<figure_warship>(f) : nullptr;
        if (!ship || !f->is_alive()) {
            continue;
        }
        if (ship->runtime_data().request_event_id != event_id) {
            continue;
        }
        ship->return_from_kingdom_request();
    }
}

void formation_legions_request_losses(int percentage, int event_id) {
    for (int id = 1; id < MAX_FORMATIONS; id++) {
        formation *m = formation_get(id);
        if (!m || !m->in_use || !m->own_batalion || m->request_event_id != event_id) {
            continue;
        }

        int alive = 0;
        for (int i = 0; i < m->num_figures; i++) {
            if (figure_is_alive_soldier(m->figures[i])) {
                alive++;
            }
        }
        int lost = calc_adjust_with_percentage(alive, percentage);
        if (lost >= alive) {
            if (formation_legion_is_on_ship(id)) {
                const int ship_id = figure_find_legion_transport_ship(id);
                figure *f = figure_get(ship_id);
                auto *ship = f ? smart_cast<figure_transport_ship>(f) : nullptr;
                if (ship) {
                    ship->runtime_data().request_event_id = -1;
                    ship->kill();
                }
            }
            m->is_at_fort = 1;
            m->in_distant_battle = 0;
            m->request_event_id = -1;
        }

        for (int i = 0; i < m->num_figures && lost > 0; i++) {
            const int fid = m->figures[i];
            if (!figure_is_alive_soldier(fid)) {
                continue;
            }
            lost--;
            figure *soldier = figure_get(fid);
            if (soldier) {
                soldier->kill();
            }
        }
    }

    int warships = 0;
    int legions = 0;
    formation_request_strength(event_id, &warships, &legions);
    int damage = calc_adjust_with_percentage(warships * WARSHIP_STRENGTH_DIVISOR, percentage);

    for (int id = 1; id < MAX_FIGURES && damage > 0; id++) {
        figure *f = figure_get(id);
        auto *ship = f ? smart_cast<figure_warship>(f) : nullptr;
        if (!ship || !f->is_alive()) {
            continue;
        }
        if (ship->runtime_data().request_event_id != event_id) {
            continue;
        }
        const int strength = (int)f->max_damage() - (int)f->damage;
        if (strength >= damage && percentage != REQUEST_LOSSES_ALL) {
            f->damage = (uint16_t)std::min((int)f->max_damage(), (int)f->damage + damage);
            return;
        }
        damage -= std::max(1, strength);
        ship->runtime_data().request_event_id = -1;
        ship->kill();
    }
}
