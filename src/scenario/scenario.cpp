#include <city/data_private.h>
#include <city/gods.h>
#include <game/io/io_buffer.h>
#include "scenario.h"

#include "city/resource.h"
#include "empire/trade_route.h"
#include "game/difficulty.h"
#include "game/settings.h"
#include "scenario/data.h"
#include "events.h"

struct scenario_t scenario_data;

bool scenario_is_saved(void) {
    return scenario_data.is_saved;
}

void scenario_settings_init(void) {
    scenario_data.settings.campaign_scenario_id = 0;
    scenario_data.settings.campaign_mission_rank = 0;
    scenario_data.settings.is_custom = 0;
    scenario_data.settings.starting_kingdom = difficulty_starting_favor();
    scenario_data.settings.starting_personal_savings = 0;
}
void scenario_settings_init_mission(void) {
    scenario_data.settings.starting_kingdom = difficulty_starting_favor();
    scenario_data.settings.starting_personal_savings = setting_personal_savings_for_mission(scenario_data.settings.campaign_mission_rank);
}

// fancy lambdas! probably gonna create many problems down the road. :3
io_buffer *iob_scenario_mission_id = new io_buffer([](io_buffer *iob) {
    iob->bind(BIND_SIGNATURE_INT8, &scenario_data.settings.campaign_scenario_id);
});
io_buffer *iob_scenario_info = new io_buffer([](io_buffer *iob) {

    iob->bind(BIND_SIGNATURE_INT16, &scenario_data.start_year);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_INT16, &scenario_data.empire.id);
    iob->bind____skip(4);
    for (int i = 0; i < MAX_GODS; i++)
        iob->bind(BIND_SIGNATURE_INT16, &city_data.religion.gods[i].is_known);
    iob->bind____skip(10);
    iob->bind____skip(2); // 2 bytes ???        03 00

    iob->bind(BIND_SIGNATURE_INT32, &scenario_data.initial_funds);
    iob->bind(BIND_SIGNATURE_INT16, &scenario_data.enemy_id);
    iob->bind____skip(6);
    iob->bind(BIND_SIGNATURE_INT32, &scenario_data.map.width);
    iob->bind(BIND_SIGNATURE_INT32, &scenario_data.map.height);
    iob->bind(BIND_SIGNATURE_INT32, &scenario_data.map.grid_start);
    iob->bind(BIND_SIGNATURE_INT32, &scenario_data.map.grid_border_size);
    iob->bind(BIND_SIGNATURE_RAW, &scenario_data.subtitle, MAX_SUBTITLE);
    iob->bind(BIND_SIGNATURE_RAW, &scenario_data.brief_description, MAX_BRIEF_DESCRIPTION);

    iob->bind(BIND_SIGNATURE_INT16, &scenario_data.image_id);
    iob->bind(BIND_SIGNATURE_INT16, &scenario_data.is_open_play);
    iob->bind(BIND_SIGNATURE_INT16, &scenario_data.player_rank);

    for (int i = 0; i < MAX_PREDATOR_HERD_POINTS; i++)
        iob->bind(BIND_SIGNATURE_UINT16, &scenario_data.herd_points_predator[i].x);
    for (int i = 0; i < MAX_PREDATOR_HERD_POINTS; i++)
        iob->bind(BIND_SIGNATURE_UINT16, &scenario_data.herd_points_predator[i].y);

    for (int i = 0; i < MAX_FISH_POINTS; i++)
        iob->bind(BIND_SIGNATURE_UINT16, &scenario_data.fishing_points[i].x);
    for (int i = 0; i < MAX_FISH_POINTS; i++)
        iob->bind(BIND_SIGNATURE_UINT16, &scenario_data.fishing_points[i].y);

    iob->bind(BIND_SIGNATURE_UINT16, &scenario_data.alt_predator_type);

    iob->bind____skip(42);

    for (int i = 0; i < MAX_INVASION_POINTS_LAND; i++)
        iob->bind(BIND_SIGNATURE_UINT16, &scenario_data.invasion_points_land[i].x);
    for (int i = 0; i < MAX_INVASION_POINTS_SEA; i++)
        iob->bind(BIND_SIGNATURE_UINT16, &scenario_data.invasion_points_land[i].x);
    for (int i = 0; i < MAX_INVASION_POINTS_LAND; i++)
        iob->bind(BIND_SIGNATURE_UINT16, &scenario_data.invasion_points_land[i].y);
    for (int i = 0; i < MAX_INVASION_POINTS_SEA; i++)
        iob->bind(BIND_SIGNATURE_UINT16, &scenario_data.invasion_points_land[i].y);

    iob->bind____skip(36); // 18 * 2

    iob->bind(BIND_SIGNATURE_INT32, &scenario_data.win_criteria.culture.goal);
    iob->bind(BIND_SIGNATURE_INT32, &scenario_data.win_criteria.prosperity.goal);
    iob->bind(BIND_SIGNATURE_INT32, &scenario_data.win_criteria.monuments.goal);
    iob->bind(BIND_SIGNATURE_INT32, &scenario_data.win_criteria.kingdom.goal);
    iob->bind(BIND_SIGNATURE_INT32, &scenario_data.win_criteria.houses.goal);
    iob->bind(BIND_SIGNATURE_INT32, &scenario_data.win_criteria.house_level.goal);

    iob->bind(BIND_SIGNATURE_UINT8, &scenario_data.win_criteria.culture.enabled);
    iob->bind(BIND_SIGNATURE_UINT8, &scenario_data.win_criteria.prosperity.enabled);
    iob->bind(BIND_SIGNATURE_UINT8, &scenario_data.win_criteria.monuments.enabled);
    iob->bind(BIND_SIGNATURE_UINT8, &scenario_data.win_criteria.kingdom.enabled);
    iob->bind(BIND_SIGNATURE_UINT8, &scenario_data.win_criteria.houses.enabled);
    iob->bind(BIND_SIGNATURE_UINT8, &scenario_data.win_criteria.house_level.enabled);

    iob->bind____skip(6); // ???
//    iob->bind(BIND_SIGNATURE_INT32, &scenario_data.earthquake.severity);
//    iob->bind(BIND_SIGNATURE_INT16, &scenario_data.earthquake.year); // ??

    iob->bind(BIND_SIGNATURE_INT32, &scenario_data.win_criteria.time_limit.enabled);
    iob->bind(BIND_SIGNATURE_INT32, &scenario_data.win_criteria.time_limit.years);
    iob->bind(BIND_SIGNATURE_INT32, &scenario_data.win_criteria.survival_time.enabled);
    iob->bind(BIND_SIGNATURE_INT32, &scenario_data.win_criteria.survival_time.years);
    iob->bind(BIND_SIGNATURE_INT32, &scenario_data.win_criteria.population.enabled);
    iob->bind(BIND_SIGNATURE_INT32, &scenario_data.win_criteria.population.goal);

    // junk 3
    iob->bind____skip(4); // ??? -1

    iob->bind(BIND_SIGNATURE_INT16, &scenario_data.map.entry_flag.x);
    iob->bind(BIND_SIGNATURE_INT16, &scenario_data.map.entry_flag.y);
    iob->bind(BIND_SIGNATURE_INT16, &scenario_data.map.exit_flag.x);
    iob->bind(BIND_SIGNATURE_INT16, &scenario_data.map.exit_flag.y);

    // junk 4a
    iob->bind____skip(40); // 20 * 2
    iob->bind____skip(4);
    iob->bind____skip(12); // 3 * 4
    iob->bind____skip(12); // 3 * 4

    iob->bind(BIND_SIGNATURE_INT16, &scenario_data.climate);

    // junk 4e
    iob->bind____skip(10);

    iob->bind(BIND_SIGNATURE_UINT16, &scenario_data.monuments.monuments_set);

    // junk 4f
    iob->bind____skip(2);

    for (int i = 0; i < MAX_PREY_HERD_POINTS; i++)
        iob->bind(BIND_SIGNATURE_INT32, &scenario_data.herd_points_prey[i].x);
    for (int i = 0; i < MAX_PREY_HERD_POINTS; i++)
        iob->bind(BIND_SIGNATURE_INT32, &scenario_data.herd_points_prey[i].y);

    for (int i = 0; i < MAX_ALLOWED_BUILDINGS; i++)
        iob->bind(BIND_SIGNATURE_INT16, &scenario_data.allowed_buildings[i]);

    for (int i = 0; i < MAX_DISEMBARK_POINTS; ++i)
        iob->bind(BIND_SIGNATURE_INT32, &scenario_data.disembark_points[i].x);
    for (int i = 0; i < MAX_DISEMBARK_POINTS; ++i)
        iob->bind(BIND_SIGNATURE_INT32, &scenario_data.disembark_points[i].y);

    iob->bind(BIND_SIGNATURE_UINT32, &scenario_data.settings.debt_interest_rate);

    iob->bind(BIND_SIGNATURE_UINT16, &scenario_data.monuments.first);
    iob->bind(BIND_SIGNATURE_UINT16, &scenario_data.monuments.second);
    iob->bind(BIND_SIGNATURE_UINT16, &scenario_data.monuments.third);

    // junk 6a
    iob->bind____skip(2);

    for (int i = 0; i < RESOURCES_MAX; ++i)
        iob->bind(BIND_SIGNATURE_UINT32, &scenario_data.monuments.burial_provisions[i]);

    iob->bind____skip(144); // ??? something related to resources like the above

    iob->bind(BIND_SIGNATURE_UINT32, &scenario_data.current_pharaoh);
    iob->bind(BIND_SIGNATURE_UINT32, &scenario_data.player_incarnation);

    // junk 8b
    iob->bind____skip(4);

    ///

    scenario_data.is_saved = true;
});
io_buffer *iob_scenario_starting_rank = new io_buffer([](io_buffer *iob) {
    iob->bind(BIND_SIGNATURE_INT32, &scenario_data.settings.starting_kingdom);
    iob->bind(BIND_SIGNATURE_INT32, &scenario_data.settings.starting_personal_savings);
    iob->bind(BIND_SIGNATURE_INT32, &scenario_data.settings.campaign_mission_rank);
});
io_buffer *iob_scenario_is_custom = new io_buffer([](io_buffer *iob) {
    iob->bind(BIND_SIGNATURE_INT32, &scenario_data.settings.is_custom);
});
io_buffer *iob_scenario_map_name = new io_buffer([](io_buffer *iob) {
    iob->bind(BIND_SIGNATURE_RAW, &scenario_data.scenario_name, MAX_SCENARIO_NAME);
});