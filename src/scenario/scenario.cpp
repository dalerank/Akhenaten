#include "scenario.h"

#include "io/io_buffer.h"
#include "city/city.h"
#include "city/city_resource.h"
#include "core/custom_span.hpp"
#include "empire/trade_route.h"
#include "earthquake.h"
#include "emperor_change.h"
#include "events.h"
#include "game/difficulty.h"
#include "game/settings.h"
#include "game/mission.h"

#include "js/js_game.h"

scenario_data_t g_scenario;

ANK_REGISTER_CONFIG_ITERATOR(config_load_scenario_load_meta_data);
void config_load_scenario_load_meta_data() {
    mission_id_t missionid(g_scenario.settings.campaign_scenario_id);

    scenario_load_meta_data(missionid);
    g_scenario.events.load_mission_metadata(missionid);
}

bool scenario_is_saved() {
    return g_scenario.is_saved;
}

void scenario_settings_init() {
    g_scenario.settings.campaign_scenario_id = 0;
    g_scenario.settings.campaign_mission_rank = 0;
    g_scenario.settings.scmode = e_scenario_normal;
    g_scenario.settings.starting_kingdom = difficulty_starting_kingdom();
    g_scenario.settings.starting_personal_savings = 0;
}

void scenario_settings_init_mission() {
    g_scenario.settings.starting_kingdom = difficulty_starting_kingdom();
    g_scenario.settings.starting_personal_savings = g_settings.personal_savings_for_mission(g_scenario.settings.campaign_mission_rank);
}

void scenario_load_meta_data(const mission_id_t &missionid) {
    g_config_arch.r_section(missionid, [] (archive arch) {
        g_scenario.meta.start_message = arch.r_int("start_message");
        g_scenario.env.has_animals = arch.r_bool("city_has_animals");
        g_scenario.env.gods_least_mood = arch.r_int("gods_least_mood", 0);
        g_scenario.win_criteria.next_mission = arch.r_int("next_mission", 0);
        int rank = std::min(arch.r_int("player_rank", -1), 10);
        if (rank >= 0) {
            g_city.kingdome.player_rank = rank;
        }

        memset(g_scenario.allowed_buildings, 0, sizeof(g_scenario.allowed_buildings));
        auto buildings = arch.r_array_num<e_building_type>("buildings");
        for (const auto &b : buildings) {
            g_scenario.allowed_buildings[b] = true;
        }

        g_scenario.init_resources.clear();
        arch.r_objects("resources", [] (pcstr key, archive rarch) {
            e_resource resource = rarch.r_type<e_resource>("type");
            bool allowed = rarch.r_bool("allow");
            g_scenario.init_resources.push_back({ resource, allowed });
        });

        g_scenario.extra_damage.clear();
        arch.r_objects("fire_damage", [&] (pcstr key, archive barch) {
            e_building_type type = barch.r_type<e_building_type>("type");
            int8_t fire = barch.r_int("fire");
            int8_t collapse = barch.r_int("collapse");
            g_scenario.extra_damage.push_back({ type, fire, collapse });
        });

        g_scenario.building_stages.clear();
        arch.r_objects("stages", [](pcstr key, archive sarch) {
            auto buildings = archive::r_array_num<e_building_type>(sarch);
            g_scenario.building_stages.push_back({key, buildings});
        });
    });
}

bool scenario_building_allowed(int building_type) {
    return g_scenario.allowed_buildings[building_type];
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

int scenario_campaign_rank() {
    return g_scenario.settings.campaign_mission_rank;
}
void scenario_set_campaign_rank(int rank) {
    g_scenario.settings.campaign_mission_rank = rank;
}
int scenario_campaign_scenario_id() {
    return g_scenario.settings.campaign_scenario_id;
}
void scenario_set_campaign_scenario(int scenario_id) {
    g_scenario.settings.campaign_scenario_id = scenario_id;
}

bool scenario_data_t::is_mission_rank(custom_span<int> missions) {
    const bool is_custom_map = settings.scmode != e_scenario_normal;
    if (!is_custom_map) {
        return false;
    }

    for (const int rank : missions) {
        if (g_scenario.settings.campaign_mission_rank == rank - 1) {
            return true;
        }
    }

    return false;
}

int scenario_additional_damage(e_building_type type, int damage) {
    const auto &dmg = g_scenario.extra_damage;
    auto it = std::find_if(dmg.begin(), dmg.end(), [type] (auto &i) { return i.type == type; });
    return (it != dmg.end()) ? (damage == 0 ? it->collapse : it->fire) : 0;
}

int scenario_is_before_mission(int mission) {
    const bool is_custom_map = (g_scenario.mode() != e_scenario_normal);
    return !is_custom_map && g_scenario.settings.campaign_mission_rank < mission;
}

int scenario_starting_kingdom() {
    return g_scenario.settings.starting_kingdom;
}
int scenario_starting_personal_savings() {
    return g_scenario.settings.starting_personal_savings;
}

const uint8_t* scenario_name() {
    return g_scenario.scenario_name;
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

int scenario_property_start_year() {
    return g_scenario.start_year;
}
int scenario_property_kingdom_supplies_grain() {
    return g_scenario.kingdom_supplies_grain;
}
int scenario_property_enemy() {
    return g_scenario.enemy_id;
}
int scenario_property_player_rank() {
    return g_scenario.player_rank;
}
int scenario_image_id() {
    return g_scenario.image_id;
}

const uint8_t* scenario_subtitle() {
    return g_scenario.subtitle;
}

int scenario_initial_funds() {
    return g_scenario.initial_funds;
}
int scenario_rescue_loan() {
    return g_scenario.rescue_loan;
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
        iob->bind(BIND_SIGNATURE_INT16, &g_city.religion.gods[i].is_known);
    }
    iob->bind____skip(10);
    iob->bind____skip(2); // 2 bytes ???        03 00

    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.initial_funds);
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
        for (int i = 0; i < MAX_PREDATOR_HERD_POINTS; i++) { g_scenario.herd_points_predator[i].invalidate_offset(); }
    }

    for (int i = 0; i < MAX_PREDATOR_HERD_POINTS; i++) { iob->bind(BIND_SIGNATURE_UINT16, g_scenario.herd_points_predator[i].private_access(_X)); }
    for (int i = 0; i < MAX_PREDATOR_HERD_POINTS; i++) { iob->bind(BIND_SIGNATURE_UINT16, g_scenario.herd_points_predator[i].private_access(_Y)); }

    for (int i = 0; i < MAX_FISH_POINTS; i++) { iob->bind(BIND_SIGNATURE_UINT16, g_scenario.fishing_points[i].private_access(_X)); }
    for (int i = 0; i < MAX_FISH_POINTS; i++) { iob->bind(BIND_SIGNATURE_UINT16, g_scenario.fishing_points[i].private_access(_Y)); }

    iob->bind(BIND_SIGNATURE_UINT16, &g_scenario.alt_predator_type);

    iob->bind____skip(42);

    if (iob->is_read_access()) {
        for (int i = 0; i < MAX_INVASION_POINTS_LAND; i++) { g_scenario.invasion_points_land[i].invalidate_offset(); }
        for (int i = 0; i < MAX_INVASION_POINTS_SEA; i++) { g_scenario.invasion_points_land[i].invalidate_offset(); }
    }

    for (int i = 0; i < MAX_INVASION_POINTS_LAND; i++) { iob->bind(BIND_SIGNATURE_UINT16, g_scenario.invasion_points_land[i].private_access(_X)); }
    for (int i = 0; i < MAX_INVASION_POINTS_SEA; i++) { iob->bind(BIND_SIGNATURE_UINT16, g_scenario.invasion_points_land[i].private_access(_X)); }

    for (int i = 0; i < MAX_INVASION_POINTS_LAND; i++) { iob->bind(BIND_SIGNATURE_UINT16, g_scenario.invasion_points_land[i].private_access(_Y)); }
    for (int i = 0; i < MAX_INVASION_POINTS_SEA; i++) { iob->bind(BIND_SIGNATURE_UINT16, g_scenario.invasion_points_land[i].private_access(_Y)); }

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

    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.rescue_loan);
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

    // junk 8b
    iob->bind____skip(4);

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
