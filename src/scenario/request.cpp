#include "request.h"

#include "building/building_storage_yard.h"
#include "game/game_events.h"
#include "city/city_finance.h"
#include "city/city_message.h"
#include "city/city_warnings.h"
#include "city/ratings.h"
#include "city/city_resource.h"
#include "city/city.h"
#include "core/random.h"
#include "core/svector.h"
#include "graphics/elements/lang_text.h"
#include "scenario_event_manager.h"
#include "game/resource.h"
#include "scenario/scenario.h"
#include "scenario/distant_battle.h"
#include "city/legion_requests.h"
#include "figure/formation.h"
#include "event_phrases.h"
#include "core/calc.h"
#include "core/log.h"
#include "empire/empire.h"
#include "empire/empire_city.h"
#include "empire/empire_object.h"
#include "game/game.h"

#include <algorithm>
#include <climits>

namespace {
request_cleared_snapshot_t g_last_request_cleared;

// OG scenario_events.c scenario_event_rules.
constexpr int REQUEST_REMINDER_MONTHS = 6;
constexpr int REQUEST_OVERDUE_MONTHS = 24;
constexpr int REQUEST_IGNORED_KINGDOM_PENALTY = 3;
constexpr int REQUEST_TROOPS_MONTHS_DEFAULT = 12;
constexpr int TROOPS_RETURN_EARLY_MONTHS = 2;
constexpr int EVENT_TRAVEL_MONTHS_DEFAULT = 12;
constexpr int EVENT_MONTHS_MARGIN_MIN = 4;
constexpr int EVENT_MONTHS_MARGIN_CHOICES = 5;
constexpr int ROUTE_TRAVEL_DIVISOR = 400;

// OG scenario_rules.c troops_loss_brackets: the losses by the strength left over, in percent.
struct troops_loss_bracket {
    int below_percent;
    int losses;
};
constexpr troops_loss_bracket troops_loss_brackets[] = {
  {10, 70},
  {25, 50},
  {50, 25},
  {75, 15},
  {100, 10},
  {150, 5},
  {INT_MAX, 0},
};
} // namespace

void scenario_request_emit_cleared(const event_ph_t &event, bool fulfilled) {
    const int tag_id = (int)event.tag_id;
    const int resource = (int)event.item.value;
    const int fulfilled_i = fulfilled ? 1 : 0;
    const int was_overdue_i = event.is_overdue ? 1 : 0;

    g_last_request_cleared.tag_id = tag_id;
    g_last_request_cleared.resource = resource;
    g_last_request_cleared.fulfilled = fulfilled_i;
    g_last_request_cleared.was_overdue = was_overdue_i;
    g_last_request_cleared.seq += 1;

    events::emit(event_request_cleared{ tag_id, resource, fulfilled_i, was_overdue_i });
}

const request_cleared_snapshot_t &scenario_request_last_cleared() {
    return g_last_request_cleared;
}

void scenario_request_init() {
    //for (int i = 0; i < MAX_REQUESTS; i++) {
    //    random_generate_next();
    //    if (g_scenario.requests[i].resource) {
    //        g_scenario.requests[i].month = (random_byte() & 7) + 2;
    //        g_scenario.requests[i].months_to_comply = 12 * g_scenario.requests[i].deadline_years;
    //    }
    //}
}

static int request_pharaoh_shift(const event_ph_t& event) {
    return event.sender_faction == EVENT_FACTION_REQUEST_FROM_CITY ? 1 : 0;
}

static void request_post(const event_ph_t& event, int caller_event_id, int body_p) {
    const int shift = request_pharaoh_shift(event);
    city_message_post_full(true, "message_template_request", &event, caller_event_id,
      PHRASE_general_request_title_P + shift, body_p + shift, PHRASE_general_request_no_reason_P_A + shift * 3,
      event.event_id, 0);
}

static bool request_can_comply(const event_ph_t& event) {
    if (event.item.value == RESOURCE_DEBEN) {
        return g_city.finance.treasury >= event.amount.value;
    }
    return g_city.resource.stored((e_resource)event.item.value) >= event.amount.value * 100;
}

static void troops_request_start(event_ph_t& e);

// OG scenario_events.c request_start.
void scenario_request_activate(event_ph_t& event) {
    if (event.is_active) {
        return;
    }
    if (event.item.value == RESOURCE_TROOPS) {
        troops_request_start(event);
        return;
    }

    event.is_active = true;
    event.is_overdue = false;
    event.event_state = e_event_state_in_progress;
    event.can_comply_dialog_shown = request_can_comply(event);
    event.quest_months_left = event.months_initial;
    event.appear_dialgow_shown = true;
    request_post(event, event.parent_id, PHRASE_general_request_initial_announcement_P);
}

// OG scenario_events.c request_check_compliance.
static void request_check_compliance(event_ph_t& event) {
    if (event.can_comply_dialog_shown || !request_can_comply(event)) {
        return;
    }
    event.can_comply_dialog_shown = true;
    const scenario_request request = scenario_request_get(event);
    // Popup Messages "Compliance" (remake option): goods/deben go out at once with a banner.
    if (popup_messages_want_banner(POPUP_MSG_COMPLIANCE) && event.item.value != RESOURCE_TROOPS
        && scenario_request_dispatch_event(event.event_id)) {
        g_warning_manager.show_message_banner(lang_text_from_key("#goods_auto_dispatched"));
        return;
    }
    const bool deben = event.item.value == RESOURCE_DEBEN;
    city_message& message = g_message_manager.post_common(true,
      deben ? "message_compliance_now_possible" : "message_storage_yards_ready_to_fulfill_request", event.event_id, 0,
      GOD_UNKNOWN, 0);
    message.req_amount = request.resource_amount();
    message.req_resource = request.resource;
    message.req_months_left = request.months_to_comply;
}

// OG scenario_events.c request_dispatched: the goods arrive after the delivery months.
static void request_dispatched(event_ph_t& event) {
    if (event.quest_months_left > 0) {
        event.quest_months_left--;
    }
    if (event.quest_months_left > 0) {
        return;
    }
    const bool on_time = event.event_state == e_event_state_dispatched || event.event_state == e_event_state_finished;
    event.event_state = e_event_state_received;
    event.is_active = false;
    if (on_time) {
        g_scenario.events.process_event(event.on_completed_action, true, EVENT_ACTION_COMPLETED, event.event_id);
    } else {
        g_scenario.events.process_event(event.on_too_late_action, true, EVENT_ACTION_TOOLATE, event.event_id);
    }
    scenario_request_emit_cleared(event, true);
    logs::info("[request] arrived event=%d on_time=%d", event.event_id, on_time ? 1 : 0);
}

// OG scenario_events.c request_active.
static void request_active(event_ph_t& event, int caller_event_id) {
    const int months = event.quest_months_left - 1;
    event.quest_months_left = (uint8_t)std::max(months, 0);
    if (event.event_state == e_event_state_in_progress || event.event_state == e_event_state_initial) {
        if (months == REQUEST_REMINDER_MONTHS) {
            request_post(event, caller_event_id, PHRASE_general_request_reminder_P);
        } else if (months <= 0) {
            event.quest_months_left = REQUEST_OVERDUE_MONTHS;
            event.event_state = e_event_state_overdue;
            event.is_overdue = true;
            request_post(event, caller_event_id, PHRASE_general_request_overdue_P);
            g_city.kingdome.reduce_missed_request(REQUEST_IGNORED_KINGDOM_PENALTY);
            logs::info("[request] overdue event=%d", event.event_id);
        }
    } else if (event.event_state == e_event_state_overdue && months <= 0) {
        event.event_state = e_event_state_failed;
        event.is_active = false;
        g_scenario.events.process_event(event.on_refusal_action, true, EVENT_ACTION_REFUSED, event.event_id);
        scenario_request_emit_cleared(event, false);
        logs::info("[request] ignored event=%d", event.event_id);
        return;
    }
    request_check_compliance(event);
}

// OG event_helpers.c scenario_event_travel_months: the route of the request city.
static int request_travel_months(const event_ph_t& e) {
    empire_city* city = e.city_id >= 0 ? g_empire.city(e.city_id) : nullptr;
    if (!city || !city->in_use || city->route_id <= 0) {
        return 0;
    }
    const map_route_object& route = g_empire.get_route_object(city->route_id);
    if (!route.in_use || route.num_points <= 1) {
        return 0;
    }
    // OG empire_route_travel_months: path_length * step / 400, at least 1; step is the route header byte.
    const int step = route.unk_header[0];
    if (step <= 0) {
        return 0;
    }
    return std::max(1, route.path_length * step / ROUTE_TRAVEL_DIVISOR);
}

static int request_travel_months_or_default(const event_ph_t& e) {
    const int travel = request_travel_months(e);
    return travel > 0 ? travel : EVENT_TRAVEL_MONTHS_DEFAULT;
}

// OG event_helpers.c scenario_event_months_left: months to the deadline by the calendar.
static int request_months_to_deadline(const event_ph_t& e) {
    const game_date_t now = game.simtime.date();
    return e.months_initial + (e.time.year - now.year) * 12 + e.time.month - now.month;
}

static int troops_losses_by_surplus(int percent) {
    for (const troops_loss_bracket& b : troops_loss_brackets) {
        if (percent < b.below_percent) {
            return b.losses;
        }
    }
    return 0;
}

// OG requests.c scenario_troops_request_dispatched: the legions win when strong enough or under the
// blessing of Seth; their losses fall with the strength they have to spare.
static bool troops_request_won(const event_ph_t& e) {
    const int strength = formation_request_strength(e.event_id, nullptr, nullptr);
    const int needed = e.amount.value;
    uint8_t& seth = g_city.religion.seth_protect_player_troops_months;
    if (strength < needed && seth == 0) {
        formation_legions_request_losses(REQUEST_LOSSES_ALL, e.event_id);
        logs::info("[request] troops lost event=%d strength=%d needed=%d", e.event_id, strength, needed);
        return false;
    }
    if (seth != 0) {
        seth = 0;
        formation_legions_request_losses(0, e.event_id);
        logs::info("[request] troops won by Seth event=%d", e.event_id);
        return true;
    }
    const int percent = calc_percentage(strength - needed, strength);
    const int losses = troops_losses_by_surplus(percent);
    formation_legions_request_losses(losses, e.event_id);
    logs::info("[request] troops won event=%d strength=%d needed=%d losses=%d", e.event_id, strength, needed, losses);
    return true;
}

static void troops_request_finish(event_ph_t& e) {
    e.event_state = e_event_state_received;
    e.is_active = false;
}

// OG scenario_events.c troops_request_months_up: the deadline has come.
static void troops_request_months_up(event_ph_t& e) {
    if (e.event_state == e_event_state_in_progress || e.event_state == e_event_state_initial) {
        troops_request_finish(e);
        g_scenario.events.process_event(e.on_refusal_action, true, EVENT_ACTION_REFUSED, e.event_id);
        scenario_request_emit_cleared(e, false);
        return;
    }
    if (e.event_state != e_event_state_troops_away) {
        troops_request_finish(e);
        return;
    }
    int left;
    if (e.quest_months_left > TROOPS_RETURN_EARLY_MONTHS) {
        e.is_overdue = true;
        e.event_state = e_event_state_troops_return_too_late;
        left = request_travel_months(e) - e.quest_months_left;
        g_scenario.events.process_event(e.on_too_late_action, true, EVENT_ACTION_TOOLATE, e.event_id);
        scenario_request_emit_cleared(e, true);
    } else if (troops_request_won(e)) {
        e.event_state = e_event_state_troops_return;
        left = request_travel_months(e);
        g_scenario.events.process_event(e.on_completed_action, true, EVENT_ACTION_COMPLETED, e.event_id);
        scenario_request_emit_cleared(e, true);
    } else {
        troops_request_finish(e);
        g_scenario.events.process_event(e.on_defeat_action, true, EVENT_ACTION_DEFEAT, e.event_id);
        scenario_request_emit_cleared(e, false);
        return;
    }
    e.quest_months_left = (uint8_t)std::clamp(left, 1, 255);
}

static void troops_request_post(const event_ph_t& e, int phrase_offset) {
    const bool city_asks = e.subtype == EVENT_SUBTYPE_CITY_ASKS_FOR_TROOPS;
    const int base = city_asks ? PHRASE_egyptian_city_attacked_title_P : PHRASE_distant_battle_title_P;
    const int shift = request_pharaoh_shift(e);
    const int reason = city_asks ? PHRASE_egyptian_city_attacked_no_reason_P_A : PHRASE_distant_battle_no_reason_P_A;
    city_message_post_full(true, city_asks ? "message_trade_city_under_siege" : "message_distant_battle_request", &e,
      e.parent_id, base + shift, base + phrase_offset + shift, reason + shift, e.event_id, 0);
}

// OG scenario_events.c troops_request_waiting: the reminders before the troops must leave.
static void troops_request_waiting(event_ph_t& e, int months) {
    const int ahead = months - request_travel_months_or_default(e);
    if (ahead == e.data.request.months_margin) {
        troops_request_post(e, 4);
    } else if (ahead == e.coin) {
        troops_request_post(e, 6);
    }
}

// OG scenario_events.c troops_request_returning.
static void troops_request_returning(event_ph_t& e) {
    if (e.quest_months_left > 0) {
        e.quest_months_left--;
    }
    if (e.quest_months_left >= 1) {
        return;
    }
    const bool won = e.event_state == e_event_state_troops_return;
    messages::popup(won ? "message_troops_return_victorious" : "message_troops_return_failed", 0, 0);
    formation_legions_return_from_request(e.event_id);
    troops_request_finish(e);
    logs::info("[request] troops back event=%d won=%d", e.event_id, won ? 1 : 0);
}

// OG scenario_events.c scenario_event_process_troops_request.
static void troops_request_process(event_ph_t& e) {
    const int months = request_months_to_deadline(e);
    if (months == 0) {
        troops_request_months_up(e);
        return;
    }
    switch (e.event_state) {
    case e_event_state_initial:
    case e_event_state_in_progress:
        troops_request_waiting(e, months);
        break;
    case e_event_state_troops_away:
        e.quest_months_left = (uint8_t)std::max(e.quest_months_left - 1, 1);
        break;
    case e_event_state_troops_return:
    case e_event_state_troops_return_too_late:
        troops_request_returning(e);
        break;
    default:
        break;
    }
}

// OG scenario_events.c troops_request_waiting, first month: the announcement.
static void troops_request_start(event_ph_t& e) {
    e.is_active = true;
    e.is_overdue = false;
    e.event_state = e_event_state_in_progress;
    e.time.year = (int16_t)game.simtime.years_since_start();
    e.time.month = (int16_t)game.simtime.month;
    e.quest_months_left = e.months_initial;
    e.appear_dialgow_shown = true;
    random_generate_next();
    e.data.request.months_margin
      = (uint8_t)(((uint16_t)random_short() & 0x7FFF) % EVENT_MONTHS_MARGIN_CHOICES + EVENT_MONTHS_MARGIN_MIN);
    random_generate_next();
    e.coin = (uint8_t)(random_short() & 1);
    troops_request_post(e, 2);
}

// OG scenario_events.c scenario_event_process_request, for a request that has started.
void scenario_request_handle(event_ph_t& event, int caller_event_id, e_event_action& next_action) {
    next_action = EVENT_ACTION_NONE;
    if (event.item.value == RESOURCE_TROOPS) {
        troops_request_process(event);
        return;
    }
    switch (event.event_state) {
    case e_event_state_dispatched:
    case e_event_state_dispatched_late:
    case e_event_state_finished: // pre-OG saves: dispatched, arrives now
    case e_event_state_finished_late:
        request_dispatched(event);
        return;
    default:
        break;
    }
    if (event.is_active) {
        request_active(event, caller_event_id);
    }
}

void scenario_request_dispatch(int id) {
    scenario_request request = scenario_request_get_visible(id);
    if (!request.is_valid()) {
        return;
    }

    event_ph_t *ev = g_scenario.events.at(request.event_id);
    if (!ev) {
        return;
    }

    // OG requests.c scenario_request_dispatch: legions march off and are away for the travel months.
    if (request.resource == RESOURCE_TROOPS) {
        ev->event_state = e_event_state_troops_away;
        const int travel = request_travel_months(*ev);
        ev->quest_months_left = (uint8_t)(travel > 0 ? travel : REQUEST_TROOPS_MONTHS_DEFAULT);
        formation_legions_dispatch_to_request(ev->event_id);
        logs::info("[request] troops dispatched event=%d strength=%d months=%d", ev->event_id,
          formation_request_strength(ev->event_id, nullptr, nullptr), ev->quest_months_left);
        return;
    }

    // OG requests.c scenario_request_dispatch: the goods leave now and arrive in 1..4 months.
    ev->event_state = ev->is_overdue ? e_event_state_dispatched_late : e_event_state_dispatched;
    random_generate_next();
    ev->quest_months_left = (uint8_t)((random_short() & 3) + 1);
    if (request.resource == RESOURCE_DEBEN) {
        events::emit(event_finance_request{efinance_request_kigdome, request.amount});
    } else {
        events::emit(event_city_remove_resource{request.resource, request.resource_amount()});
    }
    logs::info("[request] dispatched event=%d months=%d late=%d", ev->event_id, ev->quest_months_left,
      ev->is_overdue ? 1 : 0);
}

bool scenario_request_dispatch_event(int event_id) {
    const auto visible = scenario_get_visible_requests();
    for (int i = 0; i < (int)visible.size(); i++) {
        if (visible[i].event_id == event_id) {
            scenario_request_dispatch(i);
            return true;
        }
    }
    return false;
}

int scenario_requests_active_count() {
    int count = 0;
    for (int i = 0; i < g_scenario.events.events_count(); i++) {
        const event_ph_t* event = g_scenario.events.at(i);
        if (event->type == EVENT_TYPE_REQUEST && event->is_active
            && event->event_state <= e_event_state_overdue) {
            count++;
        }
    }
    return count;
}

scenario_request scenario_request_get(const event_ph_t &event) {
    scenario_request request;

    request.event_id = event.event_id;
    request.amount = event.amount.value;
    request.resource = (e_resource)event.item.value;
    request.state = event.event_state;
    request.months_to_comply = event.quest_months_left;

    return request;
}

void scenario_request_set_state(const scenario_request &request, e_event_state new_state) {
    if (event_ph_t* event = g_scenario.events.at(request.event_id)) {
        event->event_state = new_state;
    }
}

void scenario_request_set_active(const scenario_request &request, bool active) {
    if (event_ph_t* event = g_scenario.events.at(request.event_id)) {
        event->is_active = active;
    }
}

std::vector<scenario_request> scenario_get_visible_requests() {
    std::vector<scenario_request> requests;

    for (int i = 0, size = g_scenario.events.events_count(); i < size; i++) {
        const event_ph_t* event = g_scenario.events.at(i);
        if (event->type == EVENT_TYPE_REQUEST && event->is_active && event->event_state <= e_event_state_overdue) {
            requests.push_back(scenario_request_get(*event));
        }
    }

    return requests;
}

scenario_request scenario_request_get_visible(int index) {
    int event_index = 0;
    const int total_events = g_scenario.events.events_count();
    if (index >= total_events) {
        return {};
    }

    for (int i = 0; i < total_events; i++) {
        const event_ph_t* event = g_scenario.events.at(i);
        if (!(event->type == EVENT_TYPE_REQUEST && event->is_active && event->event_state <= e_event_state_overdue)) {
            continue;
        }

        if (event_index == index) {
            return scenario_request_get(*event);
        }
        ++event_index;
    }

    return {};
}
