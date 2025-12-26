#include "scenario_event_manager.h"

#include "city/city_message.h"
#include "core/string.h"
#include "core/log.h"
#include "core/variant.h"
#include "event_phrases.h"
#include "io/gamefiles/lang.h"
#include "empire/empire.h"
#include "io/io.h"
#include "io/io_buffer.h"
#include "core/random.h"
#include "game/mission.h"
#include "game/game.h"
#include "request.h"
#include "js/js_game.h"
#include "city/city.h"
#include "dev/debug.h"
#include "graphics/elements/lang_text.h"

constexpr int MAX_EVENTS = 150;
constexpr int NUM_AUTO_PHRASE_VARIANTS = 54;

const e_event_type_tokens_t ANK_CONFIG_ENUM(e_event_type_tokens);
const e_event_state_tokens_t e_event_state_tokens;
const e_event_trigger_type_tokens_t e_event_trigger_type_tokens;

struct auto_phrase {
    uint8_t id;
    xstring text;
    svector<uint8_t, 36> phrase_ids;
};
ANK_CONFIG_STRUCT(auto_phrase, id, text, phrase_ids)

struct events_data_t {
    svector<event_ph_t, MAX_EVENTS> event_list;
};

template <>
struct stable_array_max_elements<auto_phrase>{
    enum { max_elements = NUM_AUTO_PHRASE_VARIANTS };
};

template<>
struct std::hash<auto_phrase> {
    [[nodiscard]] size_t operator()(const auto_phrase &p) const noexcept {
        return p.id;
    }
};

using auto_phrases_t = stable_array<auto_phrase>;
auto_phrases_t ANK_VARIABLE(eventmsg_auto_phrases);

events_data_t g_scenario_events;

declare_console_command_p(run_scenario_event) {
    bstring128 args; is >> args;
    int tag_id = atoi(args.empty() ? (pcstr)"0" : args.c_str());

    if (!tag_id) {
        return;
    }

    auto& events = g_scenario_events.event_list;
    auto it = std::find_if(events.begin(), events.end(), [&] (auto& e) { return e.tag_id == tag_id; });
    if (it == events.end()) {
        return;
    }
    
    auto date = game.simtime.date();
    it->event_trigger_type = EVENT_TRIGGER_ONCE;
    it->time.year = date.year;
    it->time.month = date.month;
    g_scenario.events.process_events();
}

uint16_t event_ph_t::rand_reason() const {
    svector<uint16_t, 4> active_reasons;
    std::copy_if(reasons.begin(), reasons.end(), std::back_inserter(active_reasons), [] (auto &p) { return p != -1; });
    return active_reasons.size() > 0 ? active_reasons[rand() % active_reasons.size()] : 0xffff;
}

void event_ph_t::set_param(pcstr name, int param) {
    bstring32 pname(name);
    if (pname == "months_initial") { months_initial = param; return; }
    if (pname == "amount") { amount.value = param; return; }
}

void event_ph_t::archive_load(archive arch) {
    switch (type) {
    case EVENT_TYPE_REQUEST:
        item.value = arch.r_type<e_resource>("resource");
        break;
    case EVENT_TYPE_INVASION:
        item.value = arch.r_int("item");
        break;
    }
}

void event_manager_t::load_mission_metadata(const mission_id_t &missionid) {
    auto &ev_mgr = *this;
    auto &sc_events = g_scenario_events;

    sc_events.event_list.clear();
    sc_events.event_list.push_back({}); // empty events to compatibilty old engine
    g_config_arch.r_section(missionid, [&] (archive arch) {
        const bool enable_scenario_events = arch.r_bool("enable_scenario_events");
        if (!enable_scenario_events) {
            return;
        }

        arch.r("events", sc_events.event_list);
        for (int i = 0; i < sc_events.event_list.size(); ++i) {
            sc_events.event_list[i].event_id = i;
        }

        // first element should contain number of all elements
        sc_events.event_list.front().num_total_header = sc_events.event_list.size();
    });
}

void event_manager_t::create_good_request(int tag, e_resource r, int amount, int months_initial) {
    auto& request = g_scenario_events.event_list.emplace_back();
    int event_id = g_scenario_events.event_list.size() - 1;
    memset(&request, 0, sizeof(event_ph_t));
    request.type = EVENT_TYPE_REQUEST;
    request.time.year = game.simtime.years_since_start();
    request.time.month = game.simtime.month;
    request.item.value = r;
    request.sender_faction = 1;
    request.amount.value = amount;
    request.tag_id = tag;
    request.location_fields = { -1, -1, -1, -1 };
    request.months_initial = months_initial;
    request.event_id = event_id;
    //process_event(event_id, false, -1);
    //process_active_request(event_id);
    g_scenario_events.event_list.front().num_total_header = g_scenario_events.event_list.size();
}

void event_manager_t::create_trade_city_under_siege(int tag, int months_initial) {
    auto& event = g_scenario_events.event_list.emplace_back();
    int event_id = g_scenario_events.event_list.size() - 1;
    memset(&event, 0, sizeof(event_ph_t));
    event.type = EVENT_TYPE_TRADE_CITY_UNDER_SIEGE;
    event.time.year = game.simtime.years_since_start();
    event.time.month = game.simtime.month;
    event.tag_id = tag;
    event.location_fields = { -1, -1, -1, -1 };
    event.months_initial = months_initial;
    event.event_id = event_id;
    //event.event_trigger_type = EVENT_TRIGGER_GLOBAL_UPDATE;
    event.event_state = e_event_state_initial;
    //process_event(event_id, false, -1);
    g_scenario_events.event_list.front().num_total_header = g_scenario_events.event_list.size();
}

void event_manager_t::create_foreign_army_attack_warning(int tag, int8_t sender_faction) {
    auto& event = g_scenario_events.event_list.emplace_back();
    int event_id = g_scenario_events.event_list.size() - 1;
    memset(&event, 0, sizeof(event_ph_t));
    event.type = EVENT_TYPE_FOREIGN_ARMY_ATTACK_WARNING;
    event.time.year = game.simtime.years_since_start();
    event.time.month = game.simtime.month;
    event.tag_id = tag;
    event.location_fields = { -1, -1, -1, -1 };
    event.sender_faction = sender_faction;
    event.event_id = event_id;
    event.event_state = e_event_state_initial;
    g_scenario_events.event_list.front().num_total_header = g_scenario_events.event_list.size();
}

void event_manager_t::create_distant_battle(int tag, pcstr city, vec2i pos) {
    auto &event = g_scenario_events.event_list.emplace_back();
    int event_id = g_scenario_events.event_list.size() - 1;
    memset(&event, 0, sizeof(event_ph_t));
    event.type = EVENT_TYPE_DISTANT_BATTLE;
    event.time.year = game.simtime.years_since_start();
    event.time.month = game.simtime.month;
    event.tag_id = tag;
    const auto city_ptr = g_empire.city(city);
    event.city_id = city_ptr ? city_ptr->name_id : 0;
    event.location_fields = { -1, -1, -1, -1 };
    //event.sender_faction = sender_faction;
    event.event_id = event_id;
    event.event_state = e_event_state_initial;
    g_scenario_events.event_list.front().num_total_header = g_scenario_events.event_list.size();
}

void event_manager_t::execute_event(int tag) {
    auto it = std::find_if(g_scenario_events.event_list.begin(), g_scenario_events.event_list.end(), [tag] (auto &p) { return p.tag_id == tag; });

    if (it == g_scenario_events.event_list.end()) {
        return;
    }

    process_event(it->event_id, false, -1);
    process_active_request(it->event_id);
}

void event_manager_t::set_request_location_fields(int tag, int16_t l1, int16_t l2, int16_t l3, int16_t l4) {
    auto it = std::find_if(g_scenario_events.event_list.begin(), g_scenario_events.event_list.end(), [tag] (auto &p) { return p.tag_id == tag; });

    if (it != g_scenario_events.event_list.end()) {
        it->location_fields = { l1, l2, l3, l4 };
    }
}

void event_manager_t::set_request_reasons(int tag, uint16_t r1, uint16_t r2, uint16_t r3, uint16_t r4) {
    auto it = std::find_if(g_scenario_events.event_list.begin(), g_scenario_events.event_list.end(), [tag] (auto &p) { return p.tag_id == tag; });

    if (it != g_scenario_events.event_list.end()) {
        it->reasons = { r1, r2, r3, r4 };
    }
}

void event_manager_t::set_request_param(int tag, pcstr name, int param) {
    auto it = std::find_if(g_scenario_events.event_list.begin(), g_scenario_events.event_list.end(), [tag] (auto &p) { return p.tag_id == tag; });

    if (it != g_scenario_events.event_list.end()) {
        it->set_param(name, param);
    }
}

void event_manager_t::set_request_image(int tag, xstring image) {
    auto it = std::find_if(g_scenario_events.event_list.begin(), g_scenario_events.event_list.end(), [tag] (auto &p) { return p.tag_id == tag; });

    if (it != g_scenario_events.event_list.end()) {
        it->image = image_desc::resolve(image);
    }
}

void event_manager_t::set_request_sender_faction(int tag, int8_t sender_faction) {
    auto it = std::find_if(g_scenario_events.event_list.begin(), g_scenario_events.event_list.end(), [tag] (auto &p) { return p.tag_id == tag; });

    if (it != g_scenario_events.event_list.end()) {
        it->sender_faction = sender_faction;
    }
}

int16_t event_manager_t::events_count() {
    return g_scenario_events.event_list.size();
}

static void update_randomized_values(event_ph_t &event) {
    int seed = 1; // not sure what this is used for...
    randomize_event_fields((int16_t*)&event.item, &seed);
    randomize_event_fields((int16_t*)&event.amount, &seed);
    randomize_event_fields((int16_t*)&event.time, &seed);
    randomize_event_fields(event.location_fields.data(), &seed);
    randomize_event_fields(event.route_fields, &seed);

    // some other unknown stuff also happens here.........
    random_generate_next();
    random_generate_next();
}

event_ph_t* event_manager_t::create(const event_ph_t* parent) {
    auto& data = g_scenario_events;
    if (events_count() >= MAX_EVENTS) {
        return nullptr;
    }

    data.event_list.push_back({});
    int event_id = data.event_list.size() - 1;
    event_ph_t& new_event = data.event_list.back();

    // if parent event is supplied, clone it into the new event
    if (parent != nullptr) {
        memcpy(&new_event, parent, sizeof(event_ph_t));
    }

    new_event.event_id = event_id;
    return &new_event;
}

bool event_manager_t::create(const event_ph_t* master, const event_ph_t* parent, e_event_trigger_type trigger_type) {
    event_ph_t* child = create(master);
    if (!child) {
        return false;
    }

    child->event_state = e_event_state_initial;
    child->event_trigger_type = trigger_type;

    update_randomized_values(*child);

    // calculate date of activation
    int month_abs_parent = parent->time.year * 12 + parent->time.month; // field is YEARS in parent
    int month_abs_child = month_abs_parent + child->time.year;     // field is MONTHS in child
    child->time.year = month_abs_child / 12;            // relinquish previous field (the child needs this for storing the YEAR)
    child->time.month = month_abs_child % 12; // update proper month value relative to the year
    child->quest_months_left = month_abs_child - month_abs_parent;

    return true;
}

const event_ph_t* event_manager_t::at(int id) const {
    assert(id >= 0 && id < g_scenario_events.event_list.size());
    return &g_scenario_events.event_list[id];
}

event_ph_t* event_manager_t::at(int id) {
    assert(id >= 0 && id < g_scenario_events.event_list.size());
    return &g_scenario_events.event_list[id];
}

bool event_manager_t::is_valid_event_index(int id) {
    if (id >= MAX_EVENTS || id >= events_count()) {
        return false;
    }
    return true;
}

int event_manager_t::get_auto_reason_phrase_id(int param_1, int param_2) {
    return eventmsg_auto_phrases[param_1].phrase_ids[param_2];
}

xstring event_manager_t::msg_text(int group_id, int index) {
    auto& data = g_scenario_events;
    return lang_text_from_message(group_id + index);
}

void event_manager_t::process_active_request(int id) {
    if (id < 0) {
        return;
    }

    auto &data = g_scenario_events;
    if (!is_valid_event_index(id)) {
        return;
    }

    event_ph_t &event = data.event_list[id];
    if (event.type != EVENT_TYPE_REQUEST) {
        return;
    }

    if (!event.is_active) {
        return;
    }

    e_event_action chain_action_next = EVENT_ACTION_COMPLETED;
    scenario_request_handle(event, -1, chain_action_next);
}

void event_manager_t::process_event_distant_battle(const event_ph_t &event, bool via_event_trigger, int chain_action_parent, int caller_event_id, int caller_event_var) {
    const int template_str = event.reasons[0];
    const int reason = event.reasons[1];
    city_message_post_full(true, "message_distant_battle", &event, caller_event_id,
        PHRASE_distant_battle_title_P, template_str, reason,
        event.event_id, 0);

    g_city.distant_battle.init_distant_battle(event.amount.value);
    g_city.distant_battle.battle.city = event.city_id;
}

void event_manager_t::process_event_city_under_siege(const event_ph_t& event, bool via_event_trigger, int chain_action_parent, int caller_event_id, int caller_event_var) {
    int8_t cityid = event.location_fields[0];
    if (cityid == -1) {
        svector<empire_city *, 16> trade_cities;
        g_empire.select_cities(trade_cities, [&] (empire_city *city) {
            int route_id = g_empire.trade_route_for_city(city->name_id);
            return g_empire.is_trade_route_open(route_id);
        });

        if (trade_cities.size() > 0) {
            cityid = trade_cities[rand() % trade_cities.size()]->name_id;
        }
    }

    if (cityid == -1) {
        cityid = g_empire.random_city();
    }

    if (cityid == -1) {
        logs::debug("EVENT_TYPE_TRADE_CITY_UNDER_SIEGE: no valid trade city found");
        return;
    }

    empire_city_handle city{ static_cast<uint8_t>(cityid) };
    city.set_under_siege(event.months_initial);

    event_ph_t copy_event = event;
    copy_event.location_fields[0] = (cityid + 1);
    uint16_t reason = copy_event.rand_reason();
    if (reason == 0xffff) {
        reason = PHRASE_trade_city_siege_no_reason_A;
    }

    city_message_post_full(true, "message_template_general", &copy_event, caller_event_id >= 0 ? caller_event_id : event.event_id,
        PHRASE_trade_city_siege_title, PHRASE_trade_city_siege_announcement, reason,
        event.event_id, cityid);
}

void event_manager_t::process_event(int id, bool via_event_trigger, int chain_action_parent, int caller_event_id, int caller_event_var) {
    if (id < 0) {
        return;
    }

    auto& data = g_scenario_events;
    if (!is_valid_event_index(id)) {
        return;
    }

    event_ph_t &event = data.event_list[id];

    // must be a valid event type;
    // also, can not invoke event from an event if trigger is set to global update;
    // also, can not invoke from global update if trigger is set to event only;
    // also, events with 'EVENT_TRIGGER_ALREADY_FIRED' can not fire again.
    if (event.type == EVENT_TYPE_NONE) {
        return;
    }

    assert(event.event_id == id);
    if (event.event_trigger_type == EVENT_TRIGGER_ALREADY_FIRED) {
        return;
    }

    if (event.event_trigger_type == EVENT_TRIGGER_ONLY_VIA_EVENT && !via_event_trigger) {
        return;
    }

    if (event.event_trigger_type != EVENT_TRIGGER_ONLY_VIA_EVENT && via_event_trigger) {
        return;
    }

    // create follow-up "actual" active events when triggered
    // (very convoluted and annoying way in which Pharaoh events work...)
    if (event.event_trigger_type == EVENT_TRIGGER_ONLY_VIA_EVENT) {
        if (!is_valid_event_index(caller_event_id)) {
            return;
        }

        if (event.type == EVENT_TYPE_REQUEST) {
            create(&event, at(caller_event_id), EVENT_TRIGGER_ACTIVATED_8);
        } else {
            create(&event, at(caller_event_id), EVENT_TRIGGER_ACTIVATED_12);
        }
        return;
    }

    // check if the trigger time has come, if not return.
    // for ACTIVE EVENTS (requests?): ignore specific time of the year IF quest is active
    const bool should_handle = !event.is_active && event.date() == game.simtime.date();
    if (!(should_handle)) {
        return;
    }

    // ------ MAIN EVENT HANDLER
    e_event_action chain_action_next = EVENT_ACTION_COMPLETED; // default action to fire next (determined by handler)
    switch (event.type) {
    case EVENT_TYPE_REQUEST:
        scenario_request_activate(event);
        break;

    case EVENT_TYPE_INVASION:
        // TODO
        break;

    case EVENT_TYPE_SEA_TRADE_PROBLEM:
    case EVENT_TYPE_LAND_TRADE_PROBLEM:
    case EVENT_TYPE_WAGE_INCREASE:
    case EVENT_TYPE_WAGE_DECREASE:
    case EVENT_TYPE_CONTAMINATED_WATER:
    case EVENT_TYPE_GOLD_MINE_COLLAPSE:
    case EVENT_TYPE_CLAY_PIT_FLOOD:
    case EVENT_TYPE_DEMAND_INCREASE:
    case EVENT_TYPE_DEMAND_DECREASE:
    case EVENT_TYPE_PRICE_INCREASE:
    case EVENT_TYPE_PRICE_DECREASE:
    case EVENT_TYPE_REPUTATION_INCREASE:
        city_message_post_full(true, "message_template_general", &event, caller_event_id,
                               PHRASE_rating_change_title_I, PHRASE_rating_change_initial_announcement_I, PHRASE_rating_change_reason_I_A,
                               id, 0);
        break;

    case EVENT_TYPE_FOREIGN_ARMY_ATTACK_WARNING: {
            const int annoucement = event.reasons[0];
            const int reason = event.reasons[1];
            city_message_post_full(true, "message_template_general", &event, caller_event_id,
                PHRASE_foreign_army_attacks_you_title, annoucement, reason,
                id, 0);
        }
        break;

    case EVENT_TYPE_TRADE_CITY_UNDER_SIEGE: {
            process_event_city_under_siege(event, via_event_trigger, chain_action_parent, caller_event_id, caller_event_var);
        }
        break;

    case EVENT_TYPE_DISTANT_BATTLE:{
            process_event_distant_battle(event, via_event_trigger, chain_action_parent, caller_event_id, caller_event_var);
        }
        break;

    case EVENT_TYPE_REPUTATION_DECREASE:
    case EVENT_TYPE_CITY_STATUS_CHANGE:
        break;

    case EVENT_TYPE_MESSAGE: {
        int phrase_id = -1; // TODO
        switch (event.subtype) {
        case EVENT_SUBTYPE_CITY_UNDER_SIEGE:
            process_event_city_under_siege(event, via_event_trigger, chain_action_parent, caller_event_id, caller_event_var);
            break;

        case EVENT_SUBTYPE_MSG_CITY_SAVED:
            city_message_post_full(true, "message_template_city_saved", &event, caller_event_id,
                                   PHRASE_eg_city_saved_title, PHRASE_eg_city_saved_initial_announcement, PHRASE_eg_city_saved_reason_A,
                                   id, 0);
            break;

        case EVENT_SUBTYPE_MSG_DISTANT_BATTLE_WON:
            city_message_post_full(true, "message_template_distant_battle_won", &event, caller_event_id,
                                   PHRASE_battle_won_title, PHRASE_battle_won_initial_announcement, PHRASE_battle_won_reason_A,
                                   id, 0);
            break;

        case EVENT_SUBTYPE_MSG_DISTANT_BATTLE_LOST:
            city_message_post_full(true, "message_template_distant_battle_won", &event, caller_event_id,
                                   PHRASE_battle_lost_title, PHRASE_battle_lost_initial_announcement, PHRASE_battle_lost_reason_A,
                                   id, 0);
            break;

        case EVENT_SUBTYPE_MSG_ACKNOWLEDGEMENT:
            city_message_post_full(true, "message_template_general", &event, caller_event_id,
                                   PHRASE_acknowledgement_title, PHRASE_acknowledgement_initial_announcement, PHRASE_acknowledgement_no_reason_A,
                                   id, 0);
            break;
        }
        break;
    }
    case EVENT_TYPE_FAILED_FLOOD:
    case EVENT_TYPE_PERFECT_FLOOD:
    case EVENT_TYPE_LOCUSTS:
    case EVENT_TYPE_FROGS:
    case EVENT_TYPE_HAILSTORM:
    case EVENT_TYPE_BLOOD_RIVER:
    case EVENT_TYPE_CRIME_WAVE:
        break;

    case EVENT_TYPE_GIFT_FROM_PHARAOH:
        city_message_post_full(true, "message_template_general", &event, caller_event_id,
            PHRASE_rating_change_title_I, PHRASE_rating_change_initial_announcement_I, PHRASE_rating_change_reason_I_A,
            id, 0);
        break;
    }

    // propagate trigger events
    switch (chain_action_next) {
    case EVENT_ACTION_COMPLETED:
        process_event(event.on_completed_action, true, EVENT_ACTION_COMPLETED, id);
        break;

    case EVENT_ACTION_REFUSED:
        process_event(event.on_refusal_action, true, EVENT_ACTION_REFUSED, id);
        break;

    case EVENT_ACTION_TOOLATE:
        process_event(event.on_too_late_action, true, EVENT_ACTION_TOOLATE, id);
        break;

    case EVENT_ACTION_DEFEAT:
        process_event(event.on_defeat_action, true, EVENT_ACTION_DEFEAT, id);
        break;
    }

    // disable if already done
    if (event.event_trigger_type == EVENT_TRIGGER_ONCE) {
        event.event_trigger_type = EVENT_TRIGGER_ALREADY_FIRED;
    }
}

void event_manager_t::process_events() {
    auto& data = g_scenario_events;
   
    // main event update loop/fire events
    for (int i = 0; i < events_count(); i++) {
        process_event(i, false, -1);
    }

    // update active srequests
    for (int i = 0; i < events_count(); i++) {
        process_active_request(i);
    }

    // secondly, update random value fields for recurring events
    for (int i = 0; i < events_count(); i++) {
        event_ph_t &event = data.event_list[i];
        if (event.event_trigger_type == EVENT_TRIGGER_RECURRING) {
            update_randomized_values(event);
        }
    }
}

io_buffer* iob_scenario_events = new io_buffer([](io_buffer* iob, size_t version) {
    auto& data = g_scenario_events;
    // the first event's header always contains the total number of events

    if (iob->is_read_access()) {
        g_scenario_events.event_list.clear();
    }
    int events_to_read = g_scenario_events.event_list.size();

    for (int i = 0; i < MAX_EVENTS; i++) {
        event_ph_t &event = data.event_list[i];
        iob->bind(BIND_SIGNATURE_INT16, &event.num_total_header);
        if (iob->is_read_access() && i == 0) {
            events_to_read = event.num_total_header;
            g_scenario_events.event_list.resize(event.num_total_header);
            g_scenario_events.event_list.front().num_total_header = events_to_read;
        }
        if (i >= events_to_read) {
            break;
        }
        iob->bind(BIND_SIGNATURE_INT16, &event.__unk01);
        iob->bind(BIND_SIGNATURE_INT16, &event.event_id);
        iob->bind(BIND_SIGNATURE_INT8, &event.type);
        iob->bind(BIND_SIGNATURE_INT8, &event.time.month);
        iob->bind(BIND_SIGNATURE_INT16, &event.item.value);
        iob->bind(BIND_SIGNATURE_INT16, &event.item.f_fixed);
        iob->bind(BIND_SIGNATURE_INT16, &event.item.f_min);
        iob->bind(BIND_SIGNATURE_INT16, &event.item.f_max);
        iob->bind(BIND_SIGNATURE_INT16, &event.amount.value);
        iob->bind(BIND_SIGNATURE_INT16, &event.amount.f_fixed);
        iob->bind(BIND_SIGNATURE_INT16, &event.amount.f_min);
        iob->bind(BIND_SIGNATURE_INT16, &event.amount.f_max);
        iob->bind(BIND_SIGNATURE_INT16, &event.time.year);
        iob->bind____skip(2); // (BIND_SIGNATURE_INT16, &event.time.unk01);
        iob->bind(BIND_SIGNATURE_INT16, &event.time.unk02);
        iob->bind(BIND_SIGNATURE_INT16, &event.time.unk03);
        iob->bind(BIND_SIGNATURE_INT16, &event.location_fields[0]);
        iob->bind(BIND_SIGNATURE_INT16, &event.location_fields[1]);
        iob->bind(BIND_SIGNATURE_INT16, &event.location_fields[2]);
        iob->bind(BIND_SIGNATURE_INT16, &event.location_fields[3]);
        iob->bind(BIND_SIGNATURE_INT16, &event.on_completed_action);
        iob->bind(BIND_SIGNATURE_INT16, &event.on_refusal_action);
        iob->bind(BIND_SIGNATURE_INT8, &event.event_trigger_type);
        iob->bind____skip(1);
        iob->bind____skip(2); // iob->bind(BIND_SIGNATURE_INT16, &event.__unk07);
        iob->bind_u8(event.months_initial);
        iob->bind____skip(1);
        iob->bind_u8(event.quest_months_left);
        iob->bind____skip(1);
        iob->bind(BIND_SIGNATURE_INT8,  &event.event_state);
        iob->bind(BIND_SIGNATURE_INT8,  &event.is_overdue);
        iob->bind(BIND_SIGNATURE_INT8,  &event.is_active);
        iob->bind(BIND_SIGNATURE_INT8,  &event.can_comply_dialog_shown);
        iob->bind(BIND_SIGNATURE_INT16, &event.__unk11);
        iob->bind(BIND_SIGNATURE_INT8,  &event.festival_deity);
        iob->bind(BIND_SIGNATURE_INT8,  &event.reserved_unk12);
        iob->bind(BIND_SIGNATURE_INT8,  &event.invasion_attack_target);
        iob->bind_bool(event.appear_dialgow_shown);
        // ...
        // ...
        // ...
        iob->bind____skip(20); // ???
        iob->bind(BIND_SIGNATURE_INT32, &event.param1);
        iob->bind(BIND_SIGNATURE_INT16, &event.on_too_late_action);
        iob->bind(BIND_SIGNATURE_INT16, &event.on_defeat_action);
        iob->bind(BIND_SIGNATURE_INT8, &event.sender_faction);
        iob->bind____skip(1); // iob->bind(BIND_SIGNATURE_INT8, &event.__unk13_i8);
        iob->bind(BIND_SIGNATURE_INT16, &event.route_fields[0]);
        iob->bind(BIND_SIGNATURE_INT16, &event.route_fields[1]);
        iob->bind(BIND_SIGNATURE_INT16, &event.route_fields[2]);
        iob->bind(BIND_SIGNATURE_INT16, &event.route_fields[3]);
        iob->bind(BIND_SIGNATURE_INT8, &event.subtype);
        iob->bind(BIND_SIGNATURE_INT8, &event.city_id);
        iob->bind(BIND_SIGNATURE_INT16, &event.__unk16);
        iob->bind(BIND_SIGNATURE_INT16, &event.image.pack);
        iob->bind(BIND_SIGNATURE_INT16, &event.image.id);
        iob->bind(BIND_SIGNATURE_INT16, &event.image.offset);
        iob->bind(BIND_SIGNATURE_INT8, &event.on_completed_msgAlt);
        iob->bind(BIND_SIGNATURE_INT8, &event.on_refusal_msgAlt);
        iob->bind(BIND_SIGNATURE_INT8, &event.on_tooLate_msgAlt);
        iob->bind(BIND_SIGNATURE_INT8, &event.on_defeat_msgAlt);
        iob->bind(BIND_SIGNATURE_INT16, &event.reserved_1);
        iob->bind(BIND_SIGNATURE_RAW, event.reasons.data(), sizeof(event.reasons));
    }
});

io_buffer* iob_scenario_events_extra = new io_buffer([](io_buffer* iob, size_t version) {
    // TODO ????????
});

static const uint8_t* skip_non_digits(const uint8_t* str) {
    int safeguard = 0;
    while (1) {
        if (++safeguard >= 1000)
            break;

        if ((*str >= '0' && *str <= '9') || *str == '-')
            break;

        str++;
    }
    return str;
}
static const uint8_t* get_value(const uint8_t* ptr, const uint8_t* end_ptr, int* value) {
    ptr = skip_non_digits(ptr);
    *value = string_to_int(ptr);
    ptr += index_of(ptr, ',', (int)(end_ptr - ptr));
    return ptr;
}

static int next_skipping_lines_counter = 0;
static bool is_line_standalone_group(pcstr start_of_line, int size) {
    if (next_skipping_lines_counter > 0) {
        next_skipping_lines_counter--;
        return false;
    }
    if (index_of_string(start_of_line, "_A", size)) {
        next_skipping_lines_counter = 2;
        return true;
    }
    return true;

    //    int i_P = index_of_string(start_of_line, term_1, ptr - start_of_line);
    //    int i_P_A = index_of_string(start_of_line, term_2, ptr - start_of_line);
    //    int i_P_xx = index_of_string(start_of_line, term_3, ptr - start_of_line);

    //    int i_P_B = index_of_string(start_of_line, _P_B, size);
    //    int i_P_C = index_of_string(start_of_line, _P_C, size);
    //    int i_C_B = index_of_string(start_of_line, _C_B, size);
    //    int i_C_C = index_of_string(start_of_line, _C_C, size);
    //
    //    if (i_P_B > 0 || i_P_C > 0 || i_C_B > 0 || i_C_C > 0)
    //        return false;
    //
    //    if (index_of_string(start_of_line, (const uint8_t*)"_A", size))
    //        return true;
    //
    //    if (index_of_string(start_of_line, (const uint8_t*)"_P", size))
    //        return true;
    //
    //    if (index_of_string(start_of_line, (const uint8_t*)"_C", size))
    //        return true;
    //
    //    if (index_of_string(start_of_line, (const uint8_t*)"_B", size))
    //        return false;
    //    if (index_of_string(start_of_line, (const uint8_t*)"_C", size))
    //        return false;
    //
    //    return true;
}