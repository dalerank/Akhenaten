#include "scenario.h"

#include "io/io_buffer.h"
#include "city/city.h"
#include "city/city_resource.h"
#include "core/custom_span.hpp"
#include "empire/trade_route.h"
#include "earthquake.h"
#include "farao_change.h"
#include "scenario_event_manager.h"
#include "game/difficulty.h"
#include "game/settings.h"
#include "game/mission.h"
#include "dev/debug.h"

#include "js/js_game.h"

scenario_data_t g_scenario;

void ANK_REGISTER_CONFIG_ITERATOR(config_load_scenario_load_meta_data) {
    mission_id_t missionid(g_scenario.settings.campaign_scenario_id);

    g_scenario.load_metadata(missionid);
    js_register_mission_vars(g_scenario.vars);
}

void scenario_set_goal_tooltip(xstring text) {
    g_scenario.goal_tooltip = text;
}
ANK_FUNCTION_1(scenario_set_goal_tooltip)

void scenario_data_t::init() {
    settings.campaign_scenario_id = 0;
    settings.campaign_mission_rank = 0;
    settings.scmode = e_scenario_normal;
    settings.starting_kingdom = difficulty_starting_kingdom();
    settings.starting_personal_savings = 0;
}

void scenario_data_t::distant_battle_set_enemy_travel_months(int value) {
    empire.distant_battle_enemy_travel_months = value;
}

void scenario_data_t::init_mission() {
    settings.starting_kingdom = difficulty_starting_kingdom();
    settings.starting_personal_savings = g_settings.personal_savings_for_mission(settings.campaign_mission_rank);

    vars.clear();
}

int scenario_data_t::startup_funds() const {
    const int funds = meta.initial_funds[g_settings.difficulty()];
    if (funds > 0) {
        return funds;
    }

    return difficulty.adjust_money(finance.initial_funds);
}

int scenario_data_t::rescue_loan() const {
    const int loan = meta.rescue_loans[g_settings.difficulty()];
    if (loan > 0) {
        return loan;
    }

    return difficulty.loan_money(finance.rescue_loan);
}

int scenario_data_t::house_tax_multiplier(int v) const {
    const int multiplier = meta.house_tax_multipliers[g_settings.difficulty()];
    if (multiplier > 0) {
        return calc_adjust_with_percentage<int>(v, multiplier);
    }

    return difficulty.house_tax_multiplier(v);
}

void scenario_data_t::load_metadata(const mission_id_t &missionid) {
    g_config_arch.r_section(missionid, [this] (archive arch) {
        arch.r(meta);
        arch.r("env", env);

        int rank = std::min(arch.r_int("player_rank", -1), 10);
        if (rank >= 0) {
            g_city.kingdome.player_rank = rank;
        }

        memset(allowed_buildings, 0, sizeof(allowed_buildings));
        auto buildings = arch.r_array_num<e_building_type>("buildings");
        for (const auto &b : buildings) {
            allowed_buildings[b] = true;
        }

        init_resources.clear();
        arch.r("init_resources", init_resources);

        std::fill(extra_damage.begin(), extra_damage.end(), extra_damage_t{ BUILDING_NONE, 0, 0 });
        arch.r_stable_array("extra_damage", extra_damage);

        stages.clear();
        arch.r("stages", stages);

        arch.r("invasion_points_land", invasion_points_land);
        arch.r("invasion_points_sea", invasion_points_sea);
        arch.r("win_criteria", win_criteria);

        settings_vars_t newvars;
        arch.r("vars", newvars);
        vars.insert(newvars);
    });

    events.load_mission_metadata(missionid);
}

void scenario_data_t::bind_data(io_buffer *iob, size_t version, size_t size) {
    assert(size == 2000);
    char data[2000] = { 0 };
    if (iob->is_read_access()) {
        iob->bind(BIND_SIGNATURE_RAW, &data, sizeof(data));
        vars.load(data);
    } else {
        std::string save_data = vars.save();
        assert(save_data.size() < sizeof(data));
        memcpy(data, save_data.data(), save_data.size() + 1);
        iob->bind(BIND_SIGNATURE_RAW, &data, sizeof(data));
    }
}

bool scenario_building_allowed(e_building_type building_type) {
    return g_scenario.allowed_buildings[building_type];
}

void scenario_building_allow(e_building_type btype, bool allow) {
    g_scenario.allowed_buildings[btype] = allow;
}

int scenario_building_image_native_hut() {
    return g_scenario.native_images.hut;
}

int scenario_building_image_native_meeting() {
    return g_scenario.native_images.meeting;
}

int scenario_building_image_native_crops() {
    return g_scenario.native_images.crops;
}


// fancy lambdas! probably gonna create many problems down the road. :3
io_buffer* iob_scenario_mission_id = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_INT8, &g_scenario.settings.campaign_scenario_id);
});

e_scenario_mode scenario_data_t::mode() {
    return g_scenario.settings.scmode;
}

void scenario_data_t::set_campaign_rank(int rank) {
    settings.campaign_mission_rank = rank;
}

int scenario_data_t::campaign_scenario_id() {
    return settings.campaign_scenario_id;
}

void scenario_data_t::set_campaign_scenario(int scenario_id) {
    settings.campaign_scenario_id = scenario_id;
}

bool scenario_data_t::is_scenario_id(custom_span<int> missions) {
    const bool is_custom_map = settings.scmode != e_scenario_normal;
    if (is_custom_map) {
        return false;
    }

    for (const int rank : missions) {
        if (g_scenario.settings.campaign_scenario_id == rank - 1) {
            return true;
        }
    }

    return false;
}

int scenario_additional_damage(e_building_type type, e_damage_type damage) {
    const auto &dmg = g_scenario.extra_damage;
    auto it = std::find_if(dmg.begin(), dmg.end(), [type] (auto &i) { return i.type == type; });
    return (it != dmg.end()) ? (damage == e_damage_collapse ? it->collapse : it->fire) : 0;
}

int scenario_data_t::is_before_mission(int mission) {
    const bool is_custom_map = (mode() != e_scenario_normal);
    return !is_custom_map && settings.campaign_mission_rank < mission;
}

int scenario_starting_kingdom() {
    return g_scenario.settings.starting_kingdom;
}
int scenario_starting_personal_savings() {
    return g_scenario.settings.starting_personal_savings;
}

void scenario_set_name(const uint8_t* name) {
    string_copy(name, g_scenario.scenario_name, MAX_SCENARIO_NAME);
}

int scenario_is_open_play() {
    return g_scenario.is_open_play;
}
int scenario_open_play_id() {
    return g_scenario.open_play_scenario_id;
}

int scenario_property_climate() {
    return g_scenario.climate;
}

int scenario_property_enemy() {
    return g_scenario.enemy_id;
}
int scenario_property_player_rank() {
    return g_scenario.player_rank;
}

const uint8_t* scenario_subtitle() {
    return g_scenario.subtitle;
}

int scenario_property_monuments_is_enabled(void) {
    return (g_scenario.monuments.first > 0 || g_scenario.monuments.second > 0
            || g_scenario.monuments.third > 0);
}
int scenario_property_monument(int field) {
    switch (field) {
    case 0:
        return g_scenario.monuments.first;
    case 1:
        return g_scenario.monuments.second;
    case 2:
        return g_scenario.monuments.third;
    }
    return -1;
}

void scenario_set_monument(int field, int m) {
    switch (field) {
    case 0:
        g_scenario.monuments.first = m;
        break;
    case 1:
        g_scenario.monuments.second = m;
        break;
    case 2:
        g_scenario.monuments.third = m;
        break;
    }
}

io_buffer *iob_scenario_info = new io_buffer([] (io_buffer *iob, size_t version) {
    iob->bind(BIND_SIGNATURE_INT16, &g_scenario.start_year);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_INT16, &g_scenario.empire.id);
    iob->bind(BIND_SIGNATURE_UINT8, &g_scenario.meta.start_message_shown);
    iob->bind____skip(3);
    for (int i = 0; i < MAX_GODS; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &g_city.religion.gods[i].is_known);
        iob->bind____skip(1);
    }
    iob->bind____skip(10);
    iob->bind____skip(2); // 2 bytes ???        03 00

    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.finance.initial_funds);
    iob->bind(BIND_SIGNATURE_INT16, &g_scenario.enemy_id);
    iob->bind____skip(6);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.map.width);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.map.height);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.map.start_offset);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.map.border_size);
    iob->bind(BIND_SIGNATURE_RAW, &g_scenario.subtitle, MAX_SUBTITLE);
    iob->bind(BIND_SIGNATURE_RAW, &g_scenario.brief_description, MAX_BRIEF_DESCRIPTION);

    iob->bind(BIND_SIGNATURE_INT16, &g_scenario.image_id);
    iob->bind(BIND_SIGNATURE_INT16, &g_scenario.is_open_play);
    iob->bind(BIND_SIGNATURE_INT16, &g_scenario.player_rank);

    if (iob->is_read_access()) {
        for (int i = 0; i < MAX_FISH_POINTS; i++) { g_scenario.fishing_points[i].invalidate_offset(); }
        for (int i = 0; i < MAX_PREDATOR_HERD_POINTS; i++) { g_scenario.herd_points_animals[i].invalidate_offset(); }
    }

    for (int i = 0; i < MAX_PREDATOR_HERD_POINTS; i++) { iob->bind(BIND_SIGNATURE_UINT16, g_scenario.herd_points_animals[i].private_access(_X)); }
    for (int i = 0; i < MAX_PREDATOR_HERD_POINTS; i++) { iob->bind(BIND_SIGNATURE_UINT16, g_scenario.herd_points_animals[i].private_access(_Y)); }

    for (int i = 0; i < MAX_FISH_POINTS; i++) { iob->bind(BIND_SIGNATURE_UINT16, g_scenario.fishing_points[i].private_access(_X)); }
    for (int i = 0; i < MAX_FISH_POINTS; i++) { iob->bind(BIND_SIGNATURE_UINT16, g_scenario.fishing_points[i].private_access(_Y)); }

    iob->bind(BIND_SIGNATURE_UINT16, &g_scenario.alt_predator_type);

    for (int i = 0; i < MAX_PREDATOR_HERD_POINTS; i++) { iob->bind(BIND_SIGNATURE_UINT16, &g_scenario.herd_type_animals[i]); }
    iob->bind____skip(34);

    if (iob->is_read_access()) {
        auto& lands = g_scenario.invasion_points_land;
        auto& sea = g_scenario.invasion_points_land;
        std::fill(lands.begin(), lands.end(), tile2i::invalid);
        std::fill(sea.begin(), sea.end(), tile2i::invalid);
    }

    for (int i = 0; i < MAX_INVASION_POINTS_LAND; i++) { iob->bind(BIND_SIGNATURE_UINT16, g_scenario.invasion_points_land[i].private_access(_X)); }
    for (int i = 0; i < MAX_INVASION_POINTS_SEA; i++) { iob->bind(BIND_SIGNATURE_UINT16, g_scenario.invasion_points_sea[i].private_access(_X)); }

    for (int i = 0; i < MAX_INVASION_POINTS_LAND; i++) { iob->bind(BIND_SIGNATURE_UINT16, g_scenario.invasion_points_land[i].private_access(_Y)); }
    for (int i = 0; i < MAX_INVASION_POINTS_SEA; i++) { iob->bind(BIND_SIGNATURE_UINT16, g_scenario.invasion_points_sea[i].private_access(_Y)); }

    iob->bind____skip(36); // 18 * 2

    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.culture.goal);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.prosperity.goal);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.monuments.goal);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.kingdom.goal);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.housing_count.goal);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.housing_level.goal);

    iob->bind(BIND_SIGNATURE_UINT8, &g_scenario.win_criteria.culture.enabled);
    iob->bind(BIND_SIGNATURE_UINT8, &g_scenario.win_criteria.prosperity.enabled);
    iob->bind(BIND_SIGNATURE_UINT8, &g_scenario.win_criteria.monuments.enabled);
    iob->bind(BIND_SIGNATURE_UINT8, &g_scenario.win_criteria.kingdom.enabled);
    iob->bind(BIND_SIGNATURE_UINT8, &g_scenario.win_criteria.housing_count.enabled);
    iob->bind(BIND_SIGNATURE_UINT8, &g_scenario.win_criteria.housing_level.enabled);

    iob->bind____skip(6); // ???
                          //    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.earthquake.severity);
                          //    iob->bind(BIND_SIGNATURE_INT16, g_scenario.earthquake.private_access(_Y)ear); // ??

    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.time_limit.enabled);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.time_limit.years);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.survival_time.enabled);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.survival_time.years);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.population.enabled);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.population.goal);

    iob->bind(BIND_SIGNATURE_UINT32, g_scenario.earthquake_point);

    *g_scenario.entry_point.private_access(_GRID_OFFSET) = -1;
    iob->bind(BIND_SIGNATURE_UINT32, g_scenario.entry_point);

    *g_scenario.exit_point.private_access(_GRID_OFFSET) = -1;
    iob->bind(BIND_SIGNATURE_UINT32, g_scenario.exit_point);

    // junk 4a
    iob->bind____skip(28); // 14 * 2
    iob->bind____skip(4);  // 2 * 2 (58, 64)

    iob->bind(BIND_SIGNATURE_UINT32, g_scenario.river_entry_point);
    iob->bind(BIND_SIGNATURE_UINT32, g_scenario.river_exit_point);

    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.finance.rescue_loan);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.milestone25_year);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.milestone50_year);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.win_criteria.milestone75_year);

    // junk 4b
    iob->bind____skip(10); // 3 * 4 (usually go n, n+2, n+1497)
    iob->bind(BIND_SIGNATURE_UINT8, &g_scenario.env.has_animals);
    iob->bind(BIND_SIGNATURE_UINT8, &g_scenario.env.flotsam_enabled);
    iob->bind(BIND_SIGNATURE_UINT8, &g_scenario.climate);

    // junk 4e
    iob->bind____skip(1);
    iob->bind____skip(1); // used?
    iob->bind____skip(1); // used?
    iob->bind____skip(8);

    iob->bind(BIND_SIGNATURE_UINT8, &g_scenario.monuments.monuments_set);
    iob->bind(BIND_SIGNATURE_UINT8, &g_scenario.player_faction);

    // junk 4f
    iob->bind____skip(1); // -1 or -31
    iob->bind____skip(1); // -1

    if (iob->is_read_access()) {
        for (int i = 0; i < MAX_PREY_HERD_POINTS; i++) { 
            g_scenario.herd_points_prey[i].invalidate_offset(); 
        }
    }

    for (int i = 0; i < MAX_PREY_HERD_POINTS; i++) { iob->bind(BIND_SIGNATURE_INT32, g_scenario.herd_points_prey[i].private_access(_X)); }
    for (int i = 0; i < MAX_PREY_HERD_POINTS; i++) { iob->bind(BIND_SIGNATURE_INT32, g_scenario.herd_points_prey[i].private_access(_Y)); }
    // 114
    int16_t reserved_data = 0;
    for (int i = 0; i < 114; i++) {
        iob->bind(BIND_SIGNATURE_INT16, &reserved_data);
    }

    if (iob->is_read_access()) {
        for (int i = 0; i < MAX_DISEMBARK_POINTS; ++i) {
            g_scenario.disembark_points[i].invalidate_offset();
        }
    }

    for (int i = 0; i < MAX_DISEMBARK_POINTS; ++i) {
        iob->bind(BIND_SIGNATURE_INT32, g_scenario.disembark_points[i].private_access(_X));
    }

    for (int i = 0; i < MAX_DISEMBARK_POINTS; ++i) {
        iob->bind(BIND_SIGNATURE_INT32, g_scenario.disembark_points[i].private_access(_Y));
    }

    iob->bind(BIND_SIGNATURE_UINT32, &g_scenario.debt_interest_rate);

    iob->bind(BIND_SIGNATURE_UINT16, &g_scenario.monuments.first);
    iob->bind(BIND_SIGNATURE_UINT16, &g_scenario.monuments.second);
    iob->bind(BIND_SIGNATURE_UINT16, &g_scenario.monuments.third);

    // junk 6a
    iob->bind____skip(2);

    for (int i = 0; i < RESOURCES_MAX; ++i)
        iob->bind(BIND_SIGNATURE_UINT32, &g_scenario.monuments.burial_provisions[i].required);
    for (int i = 0; i < RESOURCES_MAX; ++i)
        iob->bind(BIND_SIGNATURE_UINT32, &g_scenario.monuments.burial_provisions[i].dispatched);

    iob->bind(BIND_SIGNATURE_UINT32, &g_scenario.current_pharaoh);
    iob->bind(BIND_SIGNATURE_UINT32, &g_scenario.player_incarnation);

    ///

    g_scenario.is_saved = true;
});

io_buffer* iob_scenario_carry_settings = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.settings.starting_kingdom);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.settings.starting_personal_savings);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.settings.campaign_mission_rank);
});

io_buffer* iob_scenario_is_custom = new io_buffer([](io_buffer* iob, size_t version) { 
    iob->bind(BIND_SIGNATURE_UINT8, &g_scenario.settings.scmode); 
    iob->bind____skip(3);
});

io_buffer* iob_scenario_map_name = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_RAW, &g_scenario.scenario_name, MAX_SCENARIO_NAME);
});

void scenario_data_t::update() {
    scenario_earthquake_process();
    //scenario_gladiator_revolt_process();
    scenario_kingdome_change_process();
}
