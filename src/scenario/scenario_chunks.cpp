#include "scenario/scenario_chunks.h"

#include "scenario/scenario.h"
#include "io/io_buffer.h"
#include "city/city.h"

void scenario_mission_index_chunk::bind_data(io_buffer* iob, size_t version) {
    // Chunk is 4 bytes; INT8 truncated custom mission ids > 127 (e.g. mission
    // 129).
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.campaign_scenario_id);
}

void scenario_info_chunk::bind_data(io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_INT16, &g_scenario.start_year);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_INT16, &g_scenario.empire.id);
    iob->bind____skip(4);
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
    iob->bind(BIND_SIGNATURE_XSTR, g_scenario.subtitle, MAX_SUBTITLE);
    iob->bind(BIND_SIGNATURE_XSTR, g_scenario.brief_description, MAX_BRIEF_DESCRIPTION);

    iob->bind(BIND_SIGNATURE_INT16, &g_scenario.image_id);
    iob->bind(BIND_SIGNATURE_INT16, &g_scenario.is_open_play);
    iob->bind(BIND_SIGNATURE_INT16, &g_scenario.player_rank);

    iob->bind_hvector_point_tiles_xy_u16(g_scenario.herd_points_predator);

    iob->bind_hvector_tiles_xy_u16(g_scenario.fishing_points, MAX_FISH_POINTS);

    iob->bind(BIND_SIGNATURE_UINT16, &g_scenario.alt_predator_type);

    for (int i = 0; i < MAX_PREDATOR_HERD_POINTS; i++) {
        iob->bind(BIND_SIGNATURE_UINT16, &g_scenario.herd_points_predator[i].type);
    }
    iob->bind____skip(34);

    iob->bind_hvector_tiles_xy_u16(g_scenario.invasion_points_land, MAX_INVASION_POINTS_LAND);
    iob->bind_hvector_tiles_xy_u16(g_scenario.invasion_points_sea, MAX_INVASION_POINTS_SEA);

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

    int tmp = 0;
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &g_scenario.player_faction);

    // junk 4f
    iob->bind____skip(1); // -1 or -31
    iob->bind____skip(1); // -1

    iob->bind_hvector_point_tiles_xy_i32(g_scenario.herd_points_prey);
    for (int i = 0; i < scenario_data_t::SCENARIO_PAK_RESERVED_INT16S; i++) {
        iob->bind(BIND_SIGNATURE_INT16, &g_scenario.pak_reserved[i]);
    }

    iob->bind_hvector_tiles_xy_i32(g_scenario.disembark_points, MAX_DISEMBARK_POINTS);

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
}

void scenario_carry_settings_chunk::bind_data(io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.settings.starting_kingdom);
    iob->bind____skip(4); // legacy starting_personal_savings (mission
                          // scripts set kingdome savings)
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.campaign_mission_rank);
}

void scenario_is_custom_chunk::bind_data(io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_UINT8, &g_scenario.scmode);
    iob->bind____skip(3);
}

void scenario_map_name_chunk::bind_data(io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_XSTR, g_scenario.scenario_name, MAX_SCENARIO_NAME);
}
