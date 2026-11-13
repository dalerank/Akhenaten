#include "scenario_event_manager.h"

#include "building/building.h"
#include "building/building_house.h"
#include "building/building_type.h"
#include "city/city_buildings.h"
#include "city/city_finance.h"
#include "city/city_floods.h"
#include "city/city_message.h"
#include "city/city_population.h"
#include "city/city_trade.h"
#include "core/string.h"
#include "core/log.h"
#include "core/variant.h"
#include "event_phrases.h"
#include "io/gamefiles/lang.h"
#include "empire/empire.h"
#include "empire/empire_city.h"
#include "empire/trade_prices.h"
#include "empire/trade_route.h"
#include "io/io.h"
#include "io/io_buffer.h"
#include "core/random.h"
#include "game/mission.h"
#include "game/game.h"
#include "game/game_events.h"
#include "request.h"
#include "scenario/editor.h"
#include "js/js_game.h"
#include "city/city.h"
#include "city/city_resource.h"
#include "dev/debug.h"
#include "scenario/distant_battle.h"
#include "scenario/scenario.h"
#include "scenario/scenario_invasion.h"
#include "graphics/elements/lang_text.h"
#include "figure/enemy_army.h"
#include "figure/formation.h"
#include "figuretype/figure_mummy.h"
#include "figuretype/figure_locust.h"
#include "figuretype/figure_frog.h"
#include "figuretype/figure_tomb_robber.h"
#include "figuretype/figure_fishing_boat.h"
#include "grid/terrain.h"
#include "game/game_config.h"
#include "core/svector.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <vector>

constexpr int MAX_EVENTS = 150;
constexpr int NUM_AUTO_PHRASE_VARIANTS = 54;

const e_event_type_tokens_t ANK_CONFIG_ENUM(e_event_type_tokens);
const e_event_state_tokens_t e_event_state_tokens;
const e_event_trigger_type_tokens_t ANK_CONFIG_ENUM(e_event_trigger_type_tokens);
const e_event_attack_tokens_t ANK_CONFIG_ENUM(e_event_attack_tokens);
const e_event_invader_tokens_t ANK_CONFIG_ENUM(e_event_invader_tokens);
const e_event_subtype_tokens_t ANK_CONFIG_ENUM(e_event_subtype_tokens);

// Alias names that share numeric ids with the token_holder primaries (first name at
// each value). js_register_token allows multiple globals → same int.
void register_event_subtype_aliases(config::type_enum);
namespace config {
int ANK_CONFIG_PULL_VAR_NAME(register_event_subtype_aliases) = 1;
}
static config::EnumIterator ANK_CONFIG_CC1(config_handler, __LINE__)(register_event_subtype_aliases);
void register_event_subtype_aliases(config::type_enum) {
    js_register_token(EVENT_SUBTYPE_CITY_FELL_TO_ENEMY, "EVENT_SUBTYPE_CITY_FELL_TO_ENEMY");
    js_register_token(EVENT_SUBTYPE_GENERIC_REQUEST, "EVENT_SUBTYPE_GENERIC_REQUEST");
    js_register_token(EVENT_SUBTYPE_CITY_ASKS_FOR_TROOPS, "EVENT_SUBTYPE_CITY_ASKS_FOR_TROOPS");
    js_register_token(EVENT_SUBTYPE_DISTANT_BATTLE, "EVENT_SUBTYPE_DISTANT_BATTLE");
    js_register_token(EVENT_SUBTYPE_NEW_TRADE_ROUTE, "EVENT_SUBTYPE_NEW_TRADE_ROUTE");
    js_register_token(EVENT_SUBTYPE_REQ_FOR_FESTIVAL, "EVENT_SUBTYPE_REQ_FOR_FESTIVAL");
    js_register_token(EVENT_SUBTYPE_LOST_TRADE_ROUTE, "EVENT_SUBTYPE_LOST_TRADE_ROUTE");
    js_register_token(EVENT_SUBTYPE_CONSTRUCTION_PROJECT, "EVENT_SUBTYPE_CONSTRUCTION_PROJECT");
}

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
    int tag_id = args.next_int(0);

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
    // Empty slot = 0xffff. Must compare as uint16_t: `p != -1` after int promotion
    // never filters 0xffff (65535 != -1).
    svector<uint16_t, 4> active_reasons;
    std::copy_if(reasons.begin(), reasons.end(), std::back_inserter(active_reasons),
                 [](uint16_t p) { return p != 0xffff; });
    return active_reasons.size() > 0 ? active_reasons[rand() % active_reasons.size()] : 0xffff;
}

void event_ph_t::set_param(pcstr name, int param) {
    bstring32 pname(name);
    if (pname == "months_initial") { months_initial = param; return; }
    if (pname == "amount") { amount.value = param; return; }
    if (pname == "subtype") { subtype = (int8_t)param; return; }
    if (pname == "year") { time.year = (int16_t)param; return; }
    if (pname == "month") { time.month = (int16_t)param; return; }
    if (pname == "delay" && type == EVENT_TYPE_EARTHQUAKE) {
        data.earthquake.delay = (int16_t)param;
        return;
    }
}

void event_ph_t::archive_load(archive arch) {
    // Optional alias: resource: RESOURCE_* overlays item.value (requests/gifts/prices).
    const e_resource resource = arch.r_type<e_resource>("resource");
    if (resource != RESOURCE_NONE) {
        item.value = resource;
    }
    if (type == EVENT_TYPE_EARTHQUAKE) {
        data.earthquake.delay = (int16_t)arch.r_int("delay", 0);
    }
}

void event_manager_t::load_mission_metadata(const mission_id_t &missionid) {
    auto &sc_events = g_scenario_events;

    // Events come only from the mission script; whatever the map/pak loaded is dropped.
    bool enable_scenario_events = false;
    g_config_arch.r_section(missionid, [&] (archive arch) {
        enable_scenario_events = arch.r_bool("enable_scenario_events", false);
    });

    sc_events.event_list.clear();
    sc_events.event_list.push_back({}); // empty header for old-engine compatibility
    if (!enable_scenario_events) {
        return;
    }

    g_config_arch.r_section(missionid, [&] (archive arch) {
        arch.r("events", sc_events.event_list);
        for (int i = 0; i < sc_events.event_list.size(); ++i) {
            sc_events.event_list[i].event_id = i;
            sc_events.event_list[i].parent_id = -1;
        }

        // first element should contain number of all elements
        sc_events.event_list.front().num_total_header = sc_events.event_list.size();
    });
}

void event_manager_t::create_good_request(int tag, e_resource r, int amount, int months_initial, int8_t subtype,
                                          e_event_trigger_type trigger, int8_t city_id) {
    auto& request = g_scenario_events.event_list.emplace_back();
    int event_id = g_scenario_events.event_list.size() - 1;
    memset(&request, 0, sizeof(event_ph_t));
    request.type = EVENT_TYPE_REQUEST;
    request.time.year = game.simtime.years_since_start();
    request.time.month = game.simtime.month;
    request.item.value = r;
    request.sender_faction = 1;
    request.amount.value = amount;
    request.subtype = subtype;
    request.event_trigger_type = trigger;
    request.tag_id = tag;
    request.city_id = city_id;
    request.location_fields = { -1, -1, -1, -1 };
    request.months_initial = months_initial;
    request.event_id = event_id;
    request.on_completed_action = -1;
    request.on_refusal_action = -1;
    request.on_too_late_action = -1;
    request.on_defeat_action = -1;
    g_scenario_events.event_list.front().num_total_header = g_scenario_events.event_list.size();
}

void event_manager_t::create_pharaoh_gift(int tag, e_resource r, int amount) {
    auto& event = g_scenario_events.event_list.emplace_back();
    int event_id = g_scenario_events.event_list.size() - 1;
    memset(&event, 0, sizeof(event_ph_t));
    event.type = EVENT_TYPE_GIFT_FROM_PHARAOH;
    event.time.year = game.simtime.years_since_start();
    event.time.month = game.simtime.month;
    event.item.value = r;
    event.sender_faction = 1;
    event.amount.value = amount;
    event.tag_id = tag;
    event.location_fields = { -1, -1, -1, -1 };
    event.event_id = event_id;
    g_scenario_events.event_list.front().num_total_header = g_scenario_events.event_list.size();
}

void event_manager_t::create_foreign_army_attack_warning(int tag, int8_t sender_faction, int months_initial,
                                                         int invader) {
    auto& event = g_scenario_events.event_list.emplace_back();
    int event_id = g_scenario_events.event_list.size() - 1;
    memset(&event, 0, sizeof(event_ph_t));
    event.type = EVENT_TYPE_FOREIGN_ARMY_ATTACK_WARNING;
    event.time.year = game.simtime.years_since_start();
    event.time.month = game.simtime.month;
    event.tag_id = tag;
    event.location_fields = { -1, -1, -1, -1 };
    event.sender_faction = sender_faction;
    event.months_initial = (uint8_t)(months_initial > 0 ? months_initial : 0);
    event.quest_months_left = event.months_initial;
    event.item.value = invader;
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

void event_manager_t::win_distant_battle(int tag, pcstr city, vec2i pos) {
    auto &event = g_scenario_events.event_list.emplace_back();
    int event_id = g_scenario_events.event_list.size() - 1;
    memset(&event, 0, sizeof(event_ph_t));
    event.type = EVENT_TYPE_DISTANT_BATTLE_WON;
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

void event_manager_t::create_chain_event(int tag, e_event_type type, int amount, e_resource resource,
                                         int8_t subtype, int8_t city_id, e_event_trigger_type trigger) {
    auto& event = g_scenario_events.event_list.emplace_back();
    int event_id = g_scenario_events.event_list.size() - 1;
    memset(&event, 0, sizeof(event_ph_t));
    event.type = type;
    event.amount.value = amount;
    event.amount.f_fixed = (int16_t)amount;
    event.amount.f_max = -1; // keep fixed through update_randomized_values on clone
    event.item.value = resource;
    event.item.f_fixed = (int16_t)resource;
    event.item.f_max = -1;
    event.subtype = subtype;
    event.city_id = city_id;
    event.tag_id = tag;
    event.time.year = game.simtime.years_since_start();
    event.time.month = game.simtime.month;
    event.event_trigger_type = trigger;
    event.event_id = event_id;
    event.location_fields = { -1, -1, -1, -1 };
    event.on_completed_action = -1;
    event.on_refusal_action = -1;
    event.on_too_late_action = -1;
    event.on_defeat_action = -1;
    event.reasons = { 0xffff, 0xffff, 0xffff, 0xffff };
    g_scenario_events.event_list.front().num_total_header = g_scenario_events.event_list.size();
}

int event_manager_t::create_invasion(const invasion_event_desc &desc) {
    if (events_count() >= MAX_EVENTS) {
        return -1;
    }
    auto &event = g_scenario_events.event_list.emplace_back();
    const int event_id = g_scenario_events.event_list.size() - 1;
    memset(&event, 0, sizeof(event_ph_t));
    event.type = EVENT_TYPE_INVASION;
    event.event_id = event_id;
    event.tag_id = desc.tag;
    event.event_trigger_type = desc.trigger;
    event.time.year = desc.year;
    event.time.month = desc.month;
    event.item = {(int16_t)desc.invader, (int16_t)desc.invader, -1, -1};
    event.amount = {(int16_t)desc.amount, (int16_t)desc.amount, -1, -1};
    event.months_initial = desc.months_initial;
    event.location_fields = {(int16_t)desc.route, (int16_t)desc.route, -1, -1};
    event.invasion_attack_target = desc.attack_target;
    event.parent_id = -1;
    event.on_completed_action = -1;
    event.on_refusal_action = -1;
    event.on_too_late_action = -1;
    event.on_defeat_action = -1;
    event.reasons = {0xffff, 0xffff, 0xffff, 0xffff};
    g_scenario_events.event_list.front().num_total_header = g_scenario_events.event_list.size();
    return event_id;
}

static event_ph_t *find_event_by_tag(int tag) {
    auto it = std::find_if(g_scenario_events.event_list.begin(), g_scenario_events.event_list.end(),
                           [tag] (auto &p) { return p.tag_id == tag; });
    return (it == g_scenario_events.event_list.end()) ? nullptr : &*it;
}

void event_manager_t::set_request_completed_action(int master_tag, int slave_tag) {
    event_ph_t *master = find_event_by_tag(master_tag);
    event_ph_t *slave = find_event_by_tag(slave_tag);
    if (master && slave) {
        master->on_completed_action = slave->event_id;
    }
}

void event_manager_t::set_request_refusal_action(int master_tag, int slave_tag) {
    event_ph_t *master = find_event_by_tag(master_tag);
    event_ph_t *slave = find_event_by_tag(slave_tag);
    if (master && slave) {
        master->on_refusal_action = slave->event_id;
    }
}

void event_manager_t::set_request_too_late_action(int master_tag, int slave_tag) {
    event_ph_t *master = find_event_by_tag(master_tag);
    event_ph_t *slave = find_event_by_tag(slave_tag);
    if (master && slave) {
        master->on_too_late_action = slave->event_id;
    }
}

void event_manager_t::set_request_defeat_action(int master_tag, int slave_tag) {
    event_ph_t *master = find_event_by_tag(master_tag);
    event_ph_t *slave = find_event_by_tag(slave_tag);
    if (master && slave) {
        master->on_defeat_action = slave->event_id;
    }
}

static void editor_reindex_events() {
    auto &list = g_scenario_events.event_list;
    for (int i = 0; i < (int)list.size(); ++i) {
        list[i].event_id = i;
    }
    if (!list.empty()) {
        list.front().num_total_header = (int16_t)list.size();
    }
}

static void editor_ensure_header() {
    auto &list = g_scenario_events.event_list;
    if (list.empty()) {
        list.push_back({});
    }
    list.front().num_total_header = (int16_t)list.size();
}

static int editor_request_tag(int slot) {
    return 8000 + slot;
}

static int editor_request_event_id(int slot) {
    if (slot < 0 || slot >= event_manager_t::editor_request_slots) {
        return -1;
    }
    const int tag = editor_request_tag(slot);
    auto &list = g_scenario_events.event_list;
    for (int i = 1; i < (int)list.size(); ++i) {
        if (list[i].type == EVENT_TYPE_REQUEST && list[i].tag_id == tag) {
            return i;
        }
    }
    return -1;
}

static void editor_fill_from_event(const event_ph_t &e, editor_request *out) {
    out->year = e.time.year;
    out->resource = (e_resource)e.item.value;
    out->amount = e.amount.value;
    out->deadline_years = e.months_initial > 0 ? (e.months_initial + 11) / 12 : 0;
    out->kingdom = e.data.request.kingdom;
}

static void editor_apply_to_event(event_ph_t &e, const editor_request *in, int event_id, int tag_id) {
    memset(&e, 0, sizeof(event_ph_t));
    e.type = EVENT_TYPE_REQUEST;
    e.event_id = event_id;
    e.tag_id = (uint16_t)tag_id;
    e.time.year = (int16_t)in->year;
    e.time.month = 0;
    e.item.value = (int16_t)in->resource;
    e.amount.value = (int16_t)in->amount;
    e.amount.f_fixed = (int16_t)in->amount;
    int months = in->deadline_years * 12;
    if (months < 1) {
        months = 12;
    }
    if (months > 255) {
        months = 255;
    }
    e.months_initial = (uint8_t)months;
    e.data.request.kingdom = in->kingdom;
    e.event_trigger_type = EVENT_TRIGGER_ONCE;
    e.sender_faction = EVENT_FACTION_REQUEST_FROM_PHARAOH;
    e.location_fields = { -1, -1, -1, -1 };
    e.on_completed_action = -1;
    e.on_refusal_action = -1;
    e.on_too_late_action = -1;
    e.on_defeat_action = -1;
    e.subtype = EVENT_SUBTYPE_GENERIC_REQUEST;
    e.city_id = -1;
}

void event_manager_t::clear_for_editor() {
    g_scenario_events.event_list.clear();
    g_scenario_events.event_list.push_back({});
    g_scenario_events.event_list.front().num_total_header = 1;
}

void event_manager_t::editor_request_get(int slot, editor_request *out) const {
    if (!out) {
        return;
    }
    memset(out, 0, sizeof(*out));
    const int eid = editor_request_event_id(slot);
    if (eid < 0) {
        return;
    }
    editor_fill_from_event(g_scenario_events.event_list[eid], out);
}

void event_manager_t::editor_request_save(int slot, const editor_request *in) {
    if (!in || slot < 0 || slot >= editor_request_slots) {
        return;
    }
    editor_ensure_header();
    auto &list = g_scenario_events.event_list;

    if (in->resource == RESOURCE_NONE || in->amount <= 0) {
        editor_request_delete(slot);
        return;
    }

    const int tag = editor_request_tag(slot);
    int eid = editor_request_event_id(slot);
    if (eid < 0) {
        if ((int)list.size() >= MAX_EVENTS) {
            return;
        }
        list.push_back({});
        eid = (int)list.size() - 1;
    }
    editor_apply_to_event(list[eid], in, eid, tag);
    editor_reindex_events();
}

void event_manager_t::editor_request_delete(int slot) {
    const int eid = editor_request_event_id(slot);
    if (eid < 0) {
        return;
    }
    auto &list = g_scenario_events.event_list;
    list.erase(list.begin() + eid);
    editor_ensure_header();
    editor_reindex_events();
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
    child->parent_id = parent->event_id;
    child->invasion_warnings_shown = 0;

    if ((og_invasions && child->type == EVENT_TYPE_INVASION) || child->type == EVENT_TYPE_EARTHQUAKE) {
        // OG scenario_event_chain: a child's delay (months, in time.year) counts from the current month.
        // Read from the template: update_randomized_values treats time as {year, month, ...} value/fixed/min/max.
        const int delay = master->time.year;
        const game_date_t now = game.simtime.date();
        const int month_abs = now.year * 12 + now.month + delay;
        child->time.year = month_abs / 12;
        child->time.month = month_abs % 12;
        child->quest_months_left = delay;
        return true;
    }

    // calculate date of activation
    int month_abs_parent = parent->time.year * 12 + parent->time.month; // field is YEARS in parent
    int month_abs_child = month_abs_parent + child->time.year;     // field is MONTHS in child
    child->time.year = month_abs_child / 12;            // relinquish previous field (the child needs this for storing the YEAR)
    child->time.month = month_abs_child % 12; // update proper month value relative to the year
    child->quest_months_left = month_abs_child - month_abs_parent;

    return true;
}

// Out-of-range ids return nullptr: the list is a fixed-capacity svector, so indexing past size()
// reads stale events left by an earlier mission instead of failing.
const event_ph_t* event_manager_t::at(int id) const {
    if (id < 0 || id >= (int)g_scenario_events.event_list.size()) {
        return nullptr;
    }
    return &g_scenario_events.event_list[id];
}

event_ph_t* event_manager_t::at(int id) {
    if (id < 0 || id >= (int)g_scenario_events.event_list.size()) {
        return nullptr;
    }
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

enum class e_disaster_destroy_mode {
    collapse,
    flood,
};

// Fidelity default: one random building. Enhanced: up to event.amount.
static building *destroy_disaster_buildings(e_building_type type, int amount, e_disaster_destroy_mode mode) {
    int want = 1;
    if (!!game_features::gameplay_change_disaster_events_use_amount && amount > 1) {
        want = amount;
    }

    svector<building_id, 256> candidates;
    for (int i = 1; i < MAX_BUILDINGS; ++i) {
        building *b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->type == type) {
            if (candidates.full()) {
                break;
            }
            candidates.push_back(b->id);
        }
    }

    if (candidates.empty()) {
        return nullptr;
    }

    const int destroy_n = std::min<int>(want, (int)candidates.size());
    // Fisher–Yates partial shuffle for first destroy_n picks.
    for (int i = 0; i < destroy_n; ++i) {
        const int j = i + (std::rand() % ((int)candidates.size() - i));
        std::swap(candidates[i], candidates[j]);
    }

    building *first = nullptr;
    for (int i = 0; i < destroy_n; ++i) {
        building *b = building_get(candidates[i]);
        if (!b || !b->is_valid()) {
            continue;
        }
        if (mode == e_disaster_destroy_mode::flood) {
            b->destroy_by_flooded();
        } else {
            b->destroy_by_collapse();
        }
        if (!first) {
            first = b;
        }
    }
    return first;
}

// OG city_disasters.c rules.
constexpr int DISASTER_HAPPINESS_LOSS = 15;
constexpr int DISASTER_TICKS_PER_AMOUNT = 816;
constexpr int HAILSTORM_ACTION_CREATED = 8;
constexpr int HAILSTORM_CHANCE_CREATED = 25;
constexpr int HAILSTORM_CHANCE_FIGHTER = 50;
constexpr int HAILSTORM_CHANCE_OTHER = 75;
constexpr int BLOOD_RIVER_MIN_AMOUNT = 3;
constexpr int BLOOD_RIVER_MAX_AMOUNT = 9;
constexpr int BLOOD_RIVER_RISK = 5000;
constexpr int BLOOD_RIVER_WATER_SUPPLY_PER_DISTANCE = 3;

static bool hailstorm_hits_as_fighter(figure* f) {
    if (f->is_soldier() || f->is_enemy() || f->is_boat()) {
        return true;
    }
    return f->type == FIGURE_CROCODILE || f->type == FIGURE_HYENA || f->type == FIGURE_HIPPO;
}

// OG city_disasters.c city_hailstorm_start: every figure dies on a roll of 0..99 <= its chance.
static void city_hailstorm_start() {
    int killed = 0;
    for (int id = 1; id < MAX_FIGURES; id++) {
        figure* f = figure_get(id);
        if (!f->is_valid()) {
            continue;
        }
        random_generate_next();
        const int roll = (uint16_t)random_short() % 100;
        int chance = HAILSTORM_CHANCE_OTHER;
        if (f->action_state == HAILSTORM_ACTION_CREATED) {
            chance = HAILSTORM_CHANCE_CREATED;
        } else if (hailstorm_hits_as_fighter(f)) {
            chance = HAILSTORM_CHANCE_FIGHTER;
        }
        if (roll <= chance && f->is_alive()) {
            f->kill();
            killed++;
        }
    }
    events::emit(event_sound_track{"plague_hailstorm"});
    g_city.change_happiness(-DISASTER_HAPPINESS_LOSS);
    logs::info("[disaster] hailstorm killed=%d", killed);
}

static int nearest_water_distance(tile2i t, const std::vector<tile2i>& water, int limit) {
    int best = limit;
    for (const tile2i& w : water) {
        const int dx = t.x() - w.x();
        const int dy = t.y() - w.y();
        const int d = (int)std::sqrt((double)(dx * dx + dy * dy));
        best = std::min(best, d);
    }
    return best;
}

// OG city_disasters.c city_blood_river_start. The sweep countdown lives in the event's data slot.
static void city_blood_river_start(event_ph_t& event) {
    const int amount = std::clamp<int>(event.amount.value, BLOOD_RIVER_MIN_AMOUNT, BLOOD_RIVER_MAX_AMOUNT);
    const int limit = std::max(g_scenario.map.width, g_scenario.map.height);
    std::vector<tile2i> water;
    for (int y = 0; y < g_scenario.map.height; y++) {
        for (int x = 0; x < g_scenario.map.width; x++) {
            tile2i t(x, y);
            if (map_terrain_is(t, TERRAIN_WATER)) {
                water.push_back(t);
            }
        }
    }
    buildings_house_do([&](building_house* house) {
        if (!house->hsize()) {
            return;
        }
        const int distance = nearest_water_distance(house->tile(), water, limit);
        const int risk = BLOOD_RIVER_RISK / (distance + 1);
        house->base.malaria_risk = (uint8_t)std::min<int>(255, house->base.malaria_risk + risk);
        auto& housed = house->runtime_data();
        const int water_supply_cap = distance * BLOOD_RIVER_WATER_SUPPLY_PER_DISTANCE;
        if (water_supply_cap < housed.water_supply) {
            housed.water_supply = (uint8_t)water_supply_cap;
        }
    });
    for (int id = 1; id < MAX_FIGURES; id++) {
        figure* f = figure_get(id);
        if (!f->is_valid() || f->type != FIGURE_FISHING_BOAT) {
            continue;
        }
        if (
          f->action_state == ACTION_1_FISHING_BOAT_GOING_TO_FISH || f->action_state == ACTION_2_FISHING_BOAT_FISHING) {
            f->wait_ticks = 0;
            f->advance_action(ACTION_5_FISHING_BOAT_RETURNING_WITH_FISH);
            f->destination_tile = f->source_tile;
            f->route_remove();
        }
    }
    g_city.fishing_points.clear();
    event.data.sweep.total = (int16_t)(amount * DISASTER_TICKS_PER_AMOUNT);
    event.data.sweep.countdown = event.data.sweep.total;
    g_city.change_happiness(-DISASTER_HAPPINESS_LOSS);
    logs::info("[disaster] blood river amount=%d sweep=%d", amount, event.data.sweep.countdown);
}

bool event_manager_t::blood_river_sweep_active() const {
    for (const event_ph_t& e : g_scenario_events.event_list) {
        if (e.type == EVENT_TYPE_BLOOD_RIVER && e.data.sweep.countdown > 0) {
            return true;
        }
    }
    return false;
}

void event_manager_t::process_event_distant_battle(const event_ph_t& event, bool via_event_trigger,
  int chain_action_parent, int caller_event_id, int caller_event_var) {
    const int template_str = event.reasons[0];
    const int reason = event.reasons[1];
    city_message_post_full(true, "message_distant_battle", &event, caller_event_id,
        PHRASE_distant_battle_title_P, template_str, reason,
        event.event_id, 0);

    g_distant_battle.init_distant_battle(event.amount.value);
    g_distant_battle.battle.city = event.city_id;
}

void event_manager_t::process_event_city_under_siege(const event_ph_t& event, bool via_event_trigger, int chain_action_parent, int caller_event_id, int caller_event_var) {
    // Prefer explicit location, then city_id from create_chain_event({ city: "…" }),
    // then a random open trade city.
    int8_t cityid = event.location_fields[0];
    if (cityid < 0 && event.city_id >= 0) {
        cityid = event.city_id;
    }
    if (cityid < 0) {
        svector<empire_city *, 16> trade_cities;
        g_empire.select_cities(trade_cities, [&] (empire_city *city) {
            int route_id = g_empire.trade_route_for_city(city->name_id);
            return g_empire.is_trade_route_open(route_id);
        });

        if (trade_cities.size() > 0) {
            cityid = trade_cities[rand() % trade_cities.size()]->name_id;
        }
    }

    if (cityid < 0) {
        cityid = g_empire.random_city();
    }

    if (cityid < 0) {
        logs::debug("CITY_UNDER_SIEGE: no valid trade city found");
        return;
    }

    int months = event.months_initial > 0 ? event.months_initial : event.amount.value;
    if (months <= 0) {
        months = 12;
    }

    empire_city_handle city{ static_cast<uint8_t>(cityid) };
    city.set_under_siege((uint8_t)months);

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

    if (event.type == EVENT_TYPE_NONE) {
        return;
    }

    assert(event.event_id == id);
    if (event.event_trigger_type == EVENT_TRIGGER_BY_FAVOUR_IN_USE) {
        return;
    }

    // Mid-save / pre-B14: burned ONLY_VIA facades revive so shared leaves can re-fire.
    if (event.event_trigger_type == EVENT_TRIGGER_ALREADY_FIRED) {
        if (!via_event_trigger) {
            return;
        }
        event.event_trigger_type = EVENT_TRIGGER_ONLY_VIA_EVENT;
    }

    if (event.event_trigger_type == EVENT_TRIGGER_ONLY_VIA_EVENT && !via_event_trigger) {
        return;
    }

    if (event.event_trigger_type != EVENT_TRIGGER_ONLY_VIA_EVENT && via_event_trigger) {
        return;
    }

    if (event.event_trigger_type == EVENT_TRIGGER_ONLY_VIA_EVENT) {
        if (!is_valid_event_index(caller_event_id)) {
            return;
        }

        if (event.type == EVENT_TYPE_REQUEST) {
            create(&event, at(caller_event_id), EVENT_TRIGGER_ACTIVATED_8);
        } else if (create(&event, at(caller_event_id), EVENT_TRIGGER_ACTIVATED_12)
                   && og_invasions && event.type == EVENT_TYPE_INVASION) {
            event_ph_t &child = g_scenario_events.event_list.back();
            if (child.quest_months_left == 0) {
                // OG scenario_event_chain: an undelayed invasion child is processed at once.
                process_invasion(child);
            }
        }
        // Clone-on-fire: keep the ONLY_VIA master as a reusable template (Iunet 1011 etc.).
        return;
    }

    if (og_invasions && event.type == EVENT_TYPE_INVASION) {
        return; // process_invasions() runs these every month
    }
    if (event.type == EVENT_TYPE_EARTHQUAKE) {
        return; // scenario_earthquake_process() runs these every tick
    }

    // check if the trigger time has come, if not return.
    // for ACTIVE EVENTS (requests?): ignore specific time of the year IF quest is active.
    // ACTIVATED_8/12 are children spawned by chain propagation — their date copies the master's
    // creation date which is in the past, so fire immediately instead of waiting for date match.
    const bool activated_child = event.event_trigger_type == EVENT_TRIGGER_ACTIVATED_8
                              || event.event_trigger_type == EVENT_TRIGGER_ACTIVATED_12;
    const bool should_handle = !event.is_active
                            && (activated_child || event.date() == game.simtime.date());
    if (!(should_handle)) {
        return;
    }

    // ------ MAIN EVENT HANDLER
    e_event_action chain_action_next = EVENT_ACTION_COMPLETED; // default action to fire next (determined by handler)
    switch (event.type) {
    case EVENT_TYPE_REQUEST:
        scenario_request_activate(event);
        // Outcomes fire later from scenario_request_handle — do not propagate now.
        chain_action_next = EVENT_ACTION_NONE;
        break;

    case EVENT_TYPE_INVASION:
        // Campaign invasions are JS-driven (start_foreign_army_invasion + bind tags).
        // Pak EVENT_TYPE_INVASION is intentionally a no-op here.
        chain_action_next = EVENT_ACTION_NONE;
        break;

    case EVENT_TYPE_REPUTATION_INCREASE:
        g_city.kingdome.change(event.amount.value);
        city_message_post_full(true, "message_template_general", &event, caller_event_id,
                               PHRASE_rating_change_title_I, PHRASE_rating_change_initial_announcement_I, PHRASE_rating_change_reason_I_A,
                               id, 0, POPUP_MSG_KINGDOM);
        break;

    case EVENT_TYPE_SEA_TRADE_PROBLEM:
        // Same duration as random_events sea disruption.
        if (city_trade_has_sea_trade_route()) {
            city_trade_start_sea_trade_problems(48);
        }
        city_message_post_full(true, "message_template_general", &event, caller_event_id,
                               PHRASE_stormy_seas_title, PHRASE_stormy_seas_initial_announcement,
                               PHRASE_stormy_seas_no_reason_A, id, 0);
        break;

    case EVENT_TYPE_LAND_TRADE_PROBLEM:
        if (city_trade_has_land_trade_route()) {
            city_trade_start_land_trade_problems(48);
        }
        if (g_scenario.climate == CLIMATE_DESERT) {
            city_message_post_full(true, "message_template_general", &event, caller_event_id,
                                   PHRASE_sandstorm_title, PHRASE_sandstorm_initial_announcement,
                                   PHRASE_sandstorm_no_reason_A, id, 0);
        } else {
            city_message_post_full(true, "message_template_general", &event, caller_event_id,
                                   PHRASE_landslide_title, PHRASE_landslide_initial_announcement,
                                   PHRASE_landslide_no_reason_A, id, 0);
        }
        break;

    case EVENT_TYPE_WAGE_INCREASE:
        g_city.finance.raise_wages_kingdome();
        city_message_post_full(true, "message_template_general", &event, caller_event_id,
                               PHRASE_wage_change_title_I, PHRASE_wage_change_initial_announcement_I,
                               PHRASE_wage_change_no_reason_I_A, id, 0, POPUP_MSG_WAGE);
        break;

    case EVENT_TYPE_WAGE_DECREASE:
        g_city.finance.lower_wages_kingdome();
        city_message_post_full(true, "message_template_general", &event, caller_event_id,
                               PHRASE_wage_change_title_D, PHRASE_wage_change_initial_announcement_D,
                               PHRASE_wage_change_no_reason_D_A, id, 0, POPUP_MSG_WAGE);
        break;

    case EVENT_TYPE_CONTAMINATED_WATER: {
            const int city_population = g_city.population.current;
            if (city_population > 200) {
                const int health_rate = g_city.health.value;
                int change = -25;
                if (health_rate > 80) {
                    change = -50;
                } else if (health_rate > 60) {
                    change = -40;
                }
                g_city.health.change(change);
            }
            city_message_post_full(true, "message_template_general", &event, caller_event_id,
                                   PHRASE_bad_water_title, PHRASE_bad_water_initial_announcement,
                                   PHRASE_bad_water_no_reason_A, id, 0);
        }
        break;

    case EVENT_TYPE_DEMAND_INCREASE:
    case EVENT_TYPE_DEMAND_DECREASE: {
            const e_resource resource = (e_resource)event.item.value;
            const bool is_rise = (event.type == EVENT_TYPE_DEMAND_INCREASE);
            int touched_city_id = 0;
            for (auto &city : g_empire.get_cities()) {
                if (!city.in_use || !city.is_open || city.route_id <= 0) {
                    continue;
                }
                if (!city.buys_resource[resource] && !city.sells_resource[resource]) {
                    continue;
                }
                auto &route = g_empire.get_route(city.route_id);
                const bool changed = is_rise ? route.increase_limit(resource) : route.decrease_limit(resource);
                if (changed && !touched_city_id) {
                    touched_city_id = city.name_id;
                }
            }
            if (is_rise) {
                city_message_post_full(true, "message_template_general", &event, caller_event_id,
                                       PHRASE_demand_change_title_I, PHRASE_demand_change_initial_announcement_I,
                                       PHRASE_demand_change_no_reason_I_A, id, touched_city_id, POPUP_MSG_TRADE_LEVEL);
            } else {
                city_message_post_full(true, "message_template_general", &event, caller_event_id,
                                       PHRASE_demand_change_title_D, PHRASE_demand_change_initial_announcement_D,
                                       PHRASE_demand_change_no_reason_D_A, id, touched_city_id, POPUP_MSG_TRADE_LEVEL);
            }
        }
        break;

    case EVENT_TYPE_PRICE_INCREASE:
    case EVENT_TYPE_PRICE_DECREASE: {
            const e_resource resource = (e_resource)event.item.value;
            const int amount = event.amount.value;
            const bool is_rise = (event.type == EVENT_TYPE_PRICE_INCREASE);
            if (trade_price_change(resource, is_rise ? amount : -amount)) {
                if (is_rise) {
                    city_message_post_full(true, "message_template_general", &event, caller_event_id,
                                           PHRASE_price_change_title_I, PHRASE_price_change_initial_announcement_I,
                                           PHRASE_price_change_no_reason_I_A, id, 0, POPUP_MSG_PRICE);
                } else {
                    city_message_post_full(true, "message_template_general", &event, caller_event_id,
                                           PHRASE_price_change_title_D, PHRASE_price_change_initial_announcement_D,
                                           PHRASE_price_change_no_reason_D_A, id, 0, POPUP_MSG_PRICE);
                }
            }
        }
        break;

    case EVENT_TYPE_GOLD_MINE_COLLAPSE: {
            building *b = destroy_disaster_buildings(BUILDING_GOLD_MINE, event.amount.value,
                                                     e_disaster_destroy_mode::collapse);
            if (b) {
                city_message_post_full(true, "message_template_general", &event, caller_event_id,
                                       PHRASE_goldmine_cavein_title, PHRASE_goldmine_cavein_initial_announcement,
                                       PHRASE_goldmine_cavein_no_reason_A, id, b->tile.grid_offset());
            }
        }
        break;

    case EVENT_TYPE_CLAY_PIT_FLOOD: {
            // Fidelity: rubble one working pit. Feature: up to event.amount distinct pits.
            building *b = destroy_disaster_buildings(BUILDING_CLAY_PIT, event.amount.value,
                                                     e_disaster_destroy_mode::flood);
            if (b) {
                messages::popup("message_tutorial_flooded_clay_pit", 0, b->tile.grid_offset());
            }
        }
        break;

    case EVENT_TYPE_FAILED_FLOOD:
        // OG floods.c floods_worsen_next_quality: -30..-100 in steps of 10, not a forced 0.
        g_floods.adjust_next_quality((-3 - anti_scum_random_15bit() % 8) * 10);
        city_message_post_full(true, "message_template_general", &event, caller_event_id,
                               PHRASE_flood_fails_title, PHRASE_flood_fails_initial_announcement,
                               PHRASE_flood_fails_no_reason_A, id, 0, POPUP_MSG_FLOOD);
        break;

    case EVENT_TYPE_PERFECT_FLOOD:
        g_floods.adjust_next_quality((anti_scum_random_15bit() % 8 + 3) * 10);
        city_message_post_full(true, "message_template_general", &event, caller_event_id,
                               PHRASE_perfect_flood_title, PHRASE_perfect_flood_initial_announcement,
                               PHRASE_perfect_flood_no_reason_A, id, 0, POPUP_MSG_FLOOD);
        break;

    case EVENT_TYPE_FOREIGN_ARMY_ATTACK_WARNING: {
            const bool bedouin = event.item.value == EVENT_INVADER_BEDUINS;
            const int title = bedouin ? PHRASE_bedouin_attacks_you_title
                                      : PHRASE_foreign_army_attacks_you_title;
            const int announcement = event.reasons[0]
                ? event.reasons[0]
                : (bedouin ? PHRASE_bedouin_attacks_you_initial_announcement
                           : PHRASE_foreign_army_attacks_you_initial_announcement);
            const int reason = event.reasons[1]
                ? event.reasons[1]
                : (bedouin ? PHRASE_bedouin_attacks_you_no_reason_A
                           : PHRASE_foreign_army_attacks_you_no_reason_A);
            city_message_post_full(true, "message_template_general", &event, caller_event_id,
                title, announcement, reason, id, 0);
        }
        break;

    case EVENT_TYPE_MUMMY: {
            int n = event.amount.value > 0 ? event.amount.value : 1;
            figure_mummy::spawn_wave(n);
        }
        break;

    case EVENT_TYPE_DISTANT_BATTLE_WON:
        city_message_post_full(true, "message_template_distant_battle_won", &event, caller_event_id,
            PHRASE_battle_won_title, PHRASE_battle_won_initial_announcement, PHRASE_battle_won_reason_A,
            id, 0);
        break;

    case EVENT_TYPE_DISTANT_BATTLE:{
            process_event_distant_battle(event, via_event_trigger, chain_action_parent, caller_event_id, caller_event_var);
        }
        break;

    case EVENT_TYPE_REPUTATION_DECREASE:
        g_city.kingdome.change(-event.amount.value);
        city_message_post_full(true, "message_template_general", &event, caller_event_id,
                               PHRASE_rating_change_title_I, PHRASE_rating_change_initial_announcement_I, PHRASE_rating_change_reason_I_A,
                               id, 0);
        break;

    case EVENT_TYPE_CITY_STATUS_CHANGE: {
            empire_city *city = nullptr;
            if (event.city_id >= 0) {
                city = g_empire.city(event.city_id);
            }
            if (!city || !city->in_use) {
                logs::debug("EVENT_TYPE_CITY_STATUS_CHANGE: no city for id=%d subtype=%d",
                    (int)event.city_id, (int)event.subtype);
                break;
            }

            switch (event.subtype) {
            case EVENT_SUBTYPE_CITY_FELL_TO_ENEMY:
                // Pak CITY_STATUS subtype=0 — Egyptian city falls (Buhen troops refuse/defeat
                // chains i=34 Dahshur / i=36 Enkomi). Close trade like a lost route and mark
                // the city foreign-occupied (same type flip as distant_battle::set_city_foreign).
                city->is_open = false;
                if (full_empire_object *full = g_empire.ref_full_object(city->empire_object_id)) {
                    full->trade_route_open = 0;
                }
                city->set_foreign();
                city_message_post_full(true, "message_template_general", &event, caller_event_id,
                    PHRASE_eg_city_falls_title, PHRASE_eg_city_falls_initial_announcement,
                    PHRASE_eg_city_falls_reason_A, id, city->name_id);
                break;

            case EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED:
                // Same subtype value as CITY_ASKS_FOR_TROOPS (requests) / MESSAGE conquered.
                // Pak uses CITY_STATUS subtype=1 as "foreign city conquered" (e.g. Abu y6 Selima).
                city_message_post_full(true, "message_template_foreign_city_conquered", &event, caller_event_id,
                    PHRASE_foreign_city_conquered_title, PHRASE_foreign_city_conquered_initial_announcement,
                    PHRASE_foreign_city_conquered_reason_A, id, city->name_id);
                break;

            case EVENT_SUBTYPE_NEW_TRADE_ROUTE:
                // Unlock trading type (e.g. PHARAOH → PHARAOH_TRADING) and open the route.
                city->set_trade_enabled(true);
                city->is_open = true;
                if (full_empire_object *full = g_empire.ref_full_object(city->empire_object_id)) {
                    full->trade_route_open = 1;
                    full->city_type = city->type;
                }
                city_message_post_full(true, "message_template_general", &event, caller_event_id,
                    PHRASE_route_opened_title, PHRASE_route_opened_initial_announcement, PHRASE_route_opened_reason_A,
                    id, city->name_id);
                break;

            case EVENT_SUBTYPE_LOST_TRADE_ROUTE:
                // Close the route only — do not demote type / wipe sells-buys (temporary loss).
                city->is_open = false;
                if (full_empire_object *full = g_empire.ref_full_object(city->empire_object_id)) {
                    full->trade_route_open = 0;
                }
                city_message_post_full(true, "message_template_general", &event, caller_event_id,
                    PHRASE_route_closed_title, PHRASE_route_closed_initial_announcement, PHRASE_route_closed_reason_A,
                    id, city->name_id);
                break;

            case EVENT_SUBTYPE_CITY_UNDER_SIEGE:
                process_event_city_under_siege(event, via_event_trigger, chain_action_parent, caller_event_id, caller_event_var);
                break;

            default:
                logs::debug("EVENT_TYPE_CITY_STATUS_CHANGE: unhandled subtype=%d city=%d",
                    (int)event.subtype, (int)event.city_id);
                break;
            }
        }
        break;

    case EVENT_TYPE_MESSAGE: {
        // Prefer event.reasons[] (pak / JS); fall back to the subtype's default phrase.
        auto message_phrase = [&](uint16_t fallback) -> int {
            const uint16_t r = event.rand_reason();
            return (r != 0xffff) ? (int)r : (int)fallback;
        };
        switch (event.subtype) {
        case EVENT_SUBTYPE_CITY_UNDER_SIEGE:
            process_event_city_under_siege(event, via_event_trigger, chain_action_parent, caller_event_id, caller_event_var);
            break;

        case EVENT_SUBTYPE_MSG_CITY_SAVED:
            city_message_post_full(true, "message_template_city_saved", &event, caller_event_id,
                                   PHRASE_eg_city_saved_title, PHRASE_eg_city_saved_initial_announcement,
                                   message_phrase(PHRASE_eg_city_saved_reason_A), id, 0);
            break;

        case EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED:
            city_message_post_full(true, "message_template_foreign_city_conquered", &event, caller_event_id,
                                   PHRASE_foreign_city_conquered_title, PHRASE_foreign_city_conquered_initial_announcement,
                                   message_phrase(PHRASE_foreign_city_conquered_reason_A), id, 0);
            break;

        case EVENT_SUBTYPE_MSG_DISTANT_BATTLE_LOST:
            city_message_post_full(true, "message_template_distant_battle_lost", &event, caller_event_id,
                                   PHRASE_battle_lost_title, PHRASE_battle_lost_initial_announcement,
                                   message_phrase(PHRASE_battle_lost_reason_A), id, 0);
            break;

        case EVENT_SUBTYPE_MSG_ACKNOWLEDGEMENT:
            city_message_post_full(true, "message_template_general", &event, caller_event_id,
                                   PHRASE_acknowledgement_title, PHRASE_acknowledgement_initial_announcement,
                                   message_phrase(PHRASE_acknowledgement_no_reason_A), id, 0);
            break;

        default:
            logs::debug("EVENT_TYPE_MESSAGE: unhandled subtype=%d city=%d",
                (int)event.subtype, (int)event.city_id);
            break;
        }
        break;
    }
    case EVENT_TYPE_LOCUSTS: {
        const int n = event.amount.value > 0 ? event.amount.value : 0;
        figure_locust::apply_plague(n);
        messages::popup("message_plague_of_locusts", 0, 0);
        break;
    }
    case EVENT_TYPE_CRIME_WAVE: {
        // TR4a: popup 491 + spawn 2 tomb robbers (TEMP).
        const int n = event.amount.value > 0 ? event.amount.value : 2;
        figure_tomb_robber::spawn_wave(n);
        break;
    }
    case EVENT_TYPE_FROGS: {
        const int n = event.amount.value > 0 ? event.amount.value : 0;
        figure_frog::apply_plague(n);
        messages::popup("message_plague_of_frogs", 0, 0);
        break;
    }
    case EVENT_TYPE_HAILSTORM:
        messages::popup("message_hailstorm", 0, 0);
        city_hailstorm_start();
        break;

    case EVENT_TYPE_BLOOD_RIVER:
        city_blood_river_start(event);
        messages::popup("message_river_of_blood", 0, 0);
        break;

    case EVENT_TYPE_GIFT_FROM_PHARAOH:
        if (event.item.value != RESOURCE_NONE && event.amount.value > 0) {
            events::emit(event_storageyards_add_resource{ (e_resource)event.item.value, event.amount.value * 100 });
        }
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
    if (event.event_trigger_type == EVENT_TRIGGER_ONCE
     || event.event_trigger_type == EVENT_TRIGGER_ACTIVATED_8
     || event.event_trigger_type == EVENT_TRIGGER_ACTIVATED_12) {
        event.event_trigger_type = EVENT_TRIGGER_ALREADY_FIRED;
    }
}

namespace {

// OG scenario_rules.c invasion_warnings: [0] = the announcement in the event's own month,
// then the reminders at 24 / 12 / 6 / 1 months before the attack.
struct invasion_warning_rule {
    int months_left;
    xstring message[EVENT_INVADER_MAX - EVENT_INVADER_ENEMY];
};

const invasion_warning_rule *invasion_warning_rules() {
    static const invasion_warning_rule rules[] = {
        {0, {"message_invasion_enemy_far", "message_invasion_egypt_far", "message_enemies_at_the_door", "message_invasion_enemy_far"}},
        {24, {"message_invasion_enemy_far", "message_invasion_egypt_far", "message_enemies_at_the_door", "message_invasion_enemy_far"}},
        {12, {"message_wrath_of_the_emperor", "message_invasion_egypt_mid", "message_enemies_closing", "message_wrath_of_the_emperor"}},
        {6, {"message_invasion_enemy_near", "message_invasion_egypt_near", "message_distant_battle", "message_invasion_enemy_near"}},
        {1, {"message_invasion_enemy_near", "message_invasion_egypt_near", "message_distant_battle", "message_invasion_enemy_near"}},
    };
    return rules;
}
constexpr int invasion_warning_count = 5;
constexpr int invasion_bribe_kingdom = 15;

struct invasion_phrase_set {
    int title;
    int warning[invasion_warning_count];
    int alert;
    int text;
    int text_by_favour;
};

const invasion_phrase_set &invasion_phrases(int invader) {
    static const invasion_phrase_set enemy = {
        PHRASE_foreign_army_attacks_you_title,
        {PHRASE_foreign_army_attacks_you_initial_announcement, PHRASE_foreign_army_attacks_you_2year_reminder,
         PHRASE_foreign_army_attacks_you_1year_reminder, PHRASE_foreign_army_attacks_you_6month_warning,
         PHRASE_foreign_army_attacks_you_1month_Warning},
        PHRASE_foreign_army_attacks_you_city_attacked_alert,
        PHRASE_foreign_army_attacks_you_no_reason_A,
        PHRASE_foreign_army_attacks_you_no_reason_A};
    static const invasion_phrase_set egypt = {
        PHRASE_eg_city_attacks_you_title,
        {PHRASE_eg_city_attacks_you_initial_announcement, PHRASE_eg_city_attacks_you_2year_reminder,
         PHRASE_eg_city_attacks_you_1year_reminder, PHRASE_eg_city_attacks_you_6month_warning,
         PHRASE_eg_city_attacks_you_1month_warning},
        PHRASE_eg_city_attacks_you_city_attacked_alert,
        PHRASE_eg_city_attacks_you_no_reason_A,
        PHRASE_eg_city_attacks_you_because_of_low_kingdom};
    static const invasion_phrase_set pharaoh = {
        PHRASE_pharaoh_attacks_you_title,
        {PHRASE_pharaoh_attacks_you_initial_announcement, PHRASE_pharaoh_attacks_you_2year_reminder,
         PHRASE_pharaoh_attacks_you_1year_reminder, PHRASE_pharaoh_attacks_you_6month_warning,
         PHRASE_pharaoh_attacks_you_1month_warning},
        PHRASE_pharaoh_attacks_you_city_attacked_alert,
        PHRASE_pharaoh_attacks_you_no_reason_A,
        PHRASE_pharaoh_attacks_you_because_of_low_kingdom};
    static const invasion_phrase_set bedouin = {
        PHRASE_bedouin_attacks_you_title,
        {PHRASE_bedouin_attacks_you_initial_announcement, PHRASE_bedouin_attacks_you_2year_reminder,
         PHRASE_bedouin_attacks_you_1year_reminder, PHRASE_bedouin_attacks_you_6month_warning,
         PHRASE_bedouin_attacks_you_1month_warning},
        PHRASE_bedouin_attacks_you_city_attacked_alert,
        PHRASE_bedouin_attacks_you_no_reason_A,
        PHRASE_bedouin_attacks_you_no_reason_A};
    switch (invader) {
    case EVENT_INVADER_EGYPT: return egypt;
    case EVENT_INVADER_PHARAOH: return pharaoh;
    case EVENT_INVADER_BEDUINS: return bedouin;
    default: return enemy;
    }
}

int months_since_event_date(const event_ph_t &e) {
    const game_date_t now = game.simtime.date();
    return (now.year - e.time.year) * 12 + now.month - e.time.month;
}

bool invasion_fired(const event_ph_t &e) {
    return e.event_state == e_event_state_already_fired;
}

// OG event_helpers.c scenario_event_is_running: chain templates and favour masters never run on the calendar.
bool invasion_is_running(const event_ph_t &e) {
    switch (e.event_trigger_type) {
    case EVENT_TRIGGER_ONLY_VIA_EVENT:
    case EVENT_TRIGGER_BY_FAVOUR:
    case EVENT_TRIGGER_BY_FAVOUR_IN_USE:
        return false;
    default:
        break;
    }
    const int months = months_since_event_date(e);
    return months >= 0 && months <= e.months_initial;
}

bool invasion_parent_by_favour(const event_ph_t &e) {
    const event_ph_t *parent = g_scenario.events.at(e.parent_id);
    if (!parent || parent == &e) {
        return false;
    }
    return parent->event_trigger_type == EVENT_TRIGGER_BY_FAVOUR
        || parent->event_trigger_type == EVENT_TRIGGER_BY_FAVOUR_IN_USE;
}

// OG scenario_events.c invasion_warning_for: a reminder by months left, else the announcement in the event's month.
int invasion_warning_for(const event_ph_t &e, int months_left) {
    const invasion_warning_rule *rules = invasion_warning_rules();
    for (int w = 1; w < invasion_warning_count; w++) {
        if (rules[w].months_left == months_left) {
            return w;
        }
    }
    if (months_since_event_date(e) != 0 || months_left <= 1) {
        return -1;
    }
    return 0;
}

bool invasion_has_formation(int event_id) {
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        const formation *m = formation_get(i);
        if (m->in_use && !m->own_batalion && !m->is_herd && m->invasion_id == event_id) {
            return true;
        }
    }
    return false;
}

// OG invasion.c invasion_land_point / invasion_sea_point: route 1..8 = land point, 9..16 = sea point, 0 = random land.
void invasion_set_entry(invasion_opts_t &opts, int route, bool bedouin) {
    if (route >= MAX_INVASION_POINTS_LAND + 1 && !bedouin) {
        opts.via_sea = true;
        opts.sea_point_index = (int8_t)(route - MAX_INVASION_POINTS_LAND - 1);
        return;
    }
    if (route <= 0) {
        return; // random land point inside scenario_invasion_start
    }
    const auto &lands = g_scenario.invasion_points_land;
    int index = std::min(route - 1, MAX_INVASION_POINTS_LAND - 1);
    for (int tries = 0; tries < MAX_INVASION_POINTS_LAND; tries++) {
        if (index < (int)lands.size() && lands[index].valid()) {
            opts.invasion_point = lands[index];
            return;
        }
        if (++index >= MAX_INVASION_POINTS_LAND) {
            index = 0;
        }
    }
}

} // namespace

// OG scenario_events.c invasion_attack.
static void invasion_attack(event_ph_t &e) {
    const invasion_phrase_set &phrases = invasion_phrases(e.item.value);
    const bool bedouin = e.item.value == EVENT_INVADER_BEDUINS;

    invasion_opts_t opts;
    opts.mode = ATTACK_TYPE_ENEMIES;
    switch (e.item.value) {
    case EVENT_INVADER_ENEMY: opts.enemy_type = g_scenario.enemy_id; break;
    case EVENT_INVADER_EGYPT:
    case EVENT_INVADER_PHARAOH: opts.enemy_type = ENEMY_3_EGYPTIAN; break;
    default: opts.enemy_type = ENEMY_0_BARBARIAN; break;
    }
    opts.size = e.amount.value;
    opts.invasion_id = e.event_id;
    opts.attack_type = formation_attack_from_event_target(e.invasion_attack_target);
    opts.announce = false;
    invasion_set_entry(opts, e.location_fields[0], bedouin);

    e.is_active = true;
    const int seq = scenario_invasion_start(opts);
    e.event_state = e_event_state_already_fired;
    logs::info("[invasion-event] attack event=%d invader=%d size=%d route=%d seq=%d", e.event_id, e.item.value,
               e.amount.value, e.location_fields[0], seq);
    if (seq) {
        city_message_post_full(true, "message_attack_alert", &e, e.parent_id, phrases.title, phrases.alert,
                               phrases.text, seq, 0);
    } else {
        e.is_active = false;
    }
    g_scenario.events.process_event(e.on_completed_action, true, EVENT_ACTION_COMPLETED, e.event_id);
}

// OG scenario_events.c scenario_event_process_invasion.
void event_manager_t::process_invasion(event_ph_t &e) {
    if (invasion_fired(e) || !invasion_is_running(e)) {
        return;
    }

    if (invasion_parent_by_favour(e) && g_city.kingdome.rating >= invasion_bribe_kingdom) {
        messages::popup("message_attack_called_off", 0, 0);
        e.is_active = false;
        e.event_state = e_event_state_already_fired;
        logs::info("[invasion-event] called off event=%d rating=%d", e.event_id, g_city.kingdome.rating);
        return;
    }

    const int months_left = e.months_initial - months_since_event_date(e);
    if (months_left == 0) {
        invasion_attack(e);
        return;
    }

    const int w = invasion_warning_for(e, months_left);
    if (w < 0) {
        return;
    }
    const uint8_t shown = (uint8_t)(1 << w);
    if (e.invasion_warnings_shown & shown) {
        return;
    }
    e.invasion_warnings_shown |= shown;

    const int invader = std::clamp<int>(e.item.value, EVENT_INVADER_ENEMY, EVENT_INVADER_BEDUINS);
    const invasion_phrase_set &phrases = invasion_phrases(invader);
    const bool popup = months_since_event_date(e) == 0;
    const int text = invasion_parent_by_favour(e) ? phrases.text_by_favour : phrases.text;
    city_message_post_full(popup, invasion_warning_rules()[w].message[invader - EVENT_INVADER_ENEMY], &e, e.parent_id,
                           phrases.title, phrases.warning[w], text, e.event_id, 0);
    logs::info("[invasion-event] warning event=%d months_left=%d slot=%d", e.event_id, months_left, w);
}

void event_manager_t::process_invasions() {
    if (!og_invasions) {
        return;
    }
    for (int i = 0; i < events_count(); i++) {
        event_ph_t &e = g_scenario_events.event_list[i];
        if (e.type != EVENT_TYPE_INVASION) {
            continue;
        }
        // OG formation.c: the event stops being active once its last enemy formation is gone.
        if (e.is_active && invasion_fired(e) && !invasion_has_formation(e.event_id)) {
            e.is_active = false;
        }
        process_invasion(e);
        // OG event_manager.c scenario_events_rearm: a recurring invasion comes back the same years later.
        if (e.event_trigger_type == EVENT_TRIGGER_RECURRING && invasion_fired(e) && !e.is_active) {
            e.event_state = e_event_state_initial;
            e.invasion_warnings_shown = 0;
            e.parent_id = -1;
            e.time.year += game.simtime.years_since_start();
        }
    }
}

void event_manager_t::update_tick() {
    for (event_ph_t& e : g_scenario_events.event_list) {
        if (e.type == EVENT_TYPE_BLOOD_RIVER && e.data.sweep.countdown > 0 && --e.data.sweep.countdown == 0) {
            g_city.fishing_points.create();
        }
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

static void bind_event_ph(io_buffer *iob, event_ph_t &event) {
    iob->bind(BIND_SIGNATURE_INT16, &event.num_total_header);
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
    iob->bind_u16(event.tag_id); // original unk07; JS mission requests key off this
    iob->bind(BIND_SIGNATURE_INT16, &event.months_initial);
    iob->bind(BIND_SIGNATURE_INT16, &event.quest_months_left);
    iob->bind(BIND_SIGNATURE_INT8, &event.event_state);
    iob->bind(BIND_SIGNATURE_INT8, &event.is_overdue);
    iob->bind(BIND_SIGNATURE_INT8, &event.is_active);
    iob->bind(BIND_SIGNATURE_INT8, &event.can_comply_dialog_shown);
    iob->bind(BIND_SIGNATURE_INT16, &event.parent_id);
    iob->bind(BIND_SIGNATURE_INT8, &event.festival_deity);
    iob->bind(BIND_SIGNATURE_INT8, &event.reserved_unk12);
    iob->bind(BIND_SIGNATURE_INT8, &event.invasion_attack_target);
    iob->bind_bool(event.appear_dialgow_shown);
    iob->bind(BIND_SIGNATURE_INT16, &event.data.earthquake.duration);
    iob->bind(BIND_SIGNATURE_INT16, &event.data.earthquake.delay);
    iob->bind(BIND_SIGNATURE_INT16, &event.data.earthquake.ticks);
    for (int16_t& l : event.data.earthquake.locations) {
        iob->bind(BIND_SIGNATURE_INT16, &l);
    }
    iob->bind(BIND_SIGNATURE_INT16, &event.earthquake_step);
    iob->bind(BIND_SIGNATURE_INT16, &event.on_too_late_action);
    iob->bind(BIND_SIGNATURE_INT16, &event.on_defeat_action);
    iob->bind(BIND_SIGNATURE_INT8, &event.sender_faction);
    iob->bind(BIND_SIGNATURE_UINT8, &event.invasion_warnings_shown);
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

io_buffer* iob_scenario_events = new io_buffer([](io_buffer* iob, size_t version) {
    auto& data = g_scenario_events;

    if (iob->is_read_access()) {
        data.event_list.clear();
        event_ph_t first{};
        bind_event_ph(iob, first);
        int n = first.num_total_header;
        if (n < 1) {
            n = 1;
        }
        if (n > MAX_EVENTS) {
            n = MAX_EVENTS;
        }
        data.event_list.resize(n);
        data.event_list[0] = first;
        for (int i = 1; i < n; i++) {
            bind_event_ph(iob, data.event_list[i]);
        }
        return;
    }

    if (!data.event_list.empty()) {
        data.event_list.front().num_total_header = (int16_t)data.event_list.size();
    }
    const int n = std::min((int)data.event_list.size(), MAX_EVENTS);
    for (int i = 0; i < n; i++) {
        bind_event_ph(iob, data.event_list[i]);
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