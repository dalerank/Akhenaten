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

    // junk 2
    iob->bind____skip(48); // 24 * 2
    iob->bind____skip(44);
    iob->bind____skip(64); // 32 * 2
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

    iob->bind(BIND_SIGNATURE_INT32, &scenario_data.win_criteria.time_limit.enabled);
    iob->bind(BIND_SIGNATURE_INT32, &scenario_data.win_criteria.time_limit.years);
    iob->bind(BIND_SIGNATURE_INT32, &scenario_data.win_criteria.survival_time.enabled);
    iob->bind(BIND_SIGNATURE_INT32, &scenario_data.win_criteria.survival_time.years);
    iob->bind(BIND_SIGNATURE_INT32, &scenario_data.earthquake.severity);
    iob->bind(BIND_SIGNATURE_INT16, &scenario_data.earthquake.year); // ??
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
    iob->bind____skip(2);
    iob->bind____skip(2);

    for (int i = 0; i < MAX_HERD_POINTS[GAME_ENV]; i++)
        iob->bind(BIND_SIGNATURE_INT32, &scenario_data.herd_points[i].x);
    for (int i = 0; i < MAX_HERD_POINTS[GAME_ENV]; i++)
        iob->bind(BIND_SIGNATURE_INT32, &scenario_data.herd_points[i].y);

    for (int i = 0; i < MAX_ALLOWED_BUILDINGS[GAME_ENV]; i++)
        iob->bind(BIND_SIGNATURE_INT16, &scenario_data.allowed_buildings[i]);

    // junk 5
    iob->bind____skip(24); // 12 * 2
    iob->bind____skip(4);

    iob->bind(BIND_SIGNATURE_UINT16, &scenario_data.monuments.first);
    iob->bind(BIND_SIGNATURE_UINT16, &scenario_data.monuments.second);
    iob->bind(BIND_SIGNATURE_UINT16, &scenario_data.monuments.third);

    // junk 6
    iob->bind____skip(290);
    iob->bind____skip(4);
    iob->bind____skip(4);
    iob->bind____skip(4);

//    // 17. map info 3 (30 + 2)
//    if (SCENARIO->info3->is_valid(1)) {
//        scenario_data.rescue_loan = SCENARIO->info3->read_i32(); // 4
//        scenario_data.win_criteria.milestone25_year = SCENARIO->info3->read_i32(); // 4
//        scenario_data.win_criteria.milestone50_year = SCENARIO->info3->read_i32(); // 4
//        scenario_data.win_criteria.milestone75_year = SCENARIO->info3->read_i32(); // 4
//        scenario_data.native_images.hut = SCENARIO->info3->read_i32(); // 4
//        scenario_data.native_images.meeting = SCENARIO->info3->read_i32(); // 4
//        scenario_data.native_images.crops = SCENARIO->info3->read_i32(); // 4
//        scenario_data.climate = SCENARIO->info3->read_u8(); // 1
//        scenario_data.flotsam_enabled = SCENARIO->info3->read_u8(); // 1
//        SCENARIO->info3->skip(2);
//    }
//
//    // 8. random events (44)
//    // events
//    if (SCENARIO->events->is_valid(1)) {
//        scenario_data.gladiator_revolt.enabled = SCENARIO->events->read_i32(); // 4
//        scenario_data.gladiator_revolt.year = SCENARIO->events->read_i32(); // 4
//        scenario_data.emperor_change.enabled = SCENARIO->events->read_i32(); // 4
//        scenario_data.emperor_change.year = SCENARIO->events->read_i32(); // 4
//        scenario_data.random_events.sea_trade_problem = SCENARIO->events->read_i32(); // 4
//        scenario_data.random_events.land_trade_problem = SCENARIO->events->read_i32(); // 4
//        scenario_data.random_events.raise_wages = SCENARIO->events->read_i32(); // 4
//        scenario_data.random_events.lower_wages = SCENARIO->events->read_i32(); // 4
//        scenario_data.random_events.contaminated_water = SCENARIO->events->read_i32(); // 4
//        scenario_data.random_events.iron_mine_collapse = SCENARIO->events->read_i32(); // 4
//        scenario_data.random_events.clay_pit_flooded = SCENARIO->events->read_i32(); // 4
//    }
//
//    // 14. map points (12)
//    if (SCENARIO->map_points->is_valid(1)) {
//        scenario_data.earthquake_point.x = SCENARIO->map_points->read_i16(); // 2
//        scenario_data.earthquake_point.y = SCENARIO->map_points->read_i16(); // 2
//        scenario_data.entry_point.x = SCENARIO->map_points->read_i16(); // 2
//        scenario_data.entry_point.y = SCENARIO->map_points->read_i16(); // 2
//        scenario_data.exit_point.x = SCENARIO->map_points->read_i16(); // 2
//        scenario_data.exit_point.y = SCENARIO->map_points->read_i16(); // 2
//    }
//
//    // 16. river entry points (8)
//    if (SCENARIO->map_points->is_valid(1)) {
//        scenario_data.river_entry_point.x = SCENARIO->river_points->read_i16(); // 2
//        scenario_data.river_entry_point.y = SCENARIO->river_points->read_i16(); // 2
//        scenario_data.river_exit_point.x = SCENARIO->river_points->read_i16(); // 2
//        scenario_data.river_exit_point.y = SCENARIO->river_points->read_i16(); // 2
//    }
//
//    // 18. empire (11 + 1)
//    if (SCENARIO->empire->is_valid(1)) {
//        scenario_data.empire.is_expanded = SCENARIO->empire->read_i32(); // 4
//        scenario_data.empire.expansion_year = SCENARIO->empire->read_i32(); // 4
//        scenario_data.empire.distant_battle_roman_travel_months = SCENARIO->empire->read_u8(); // 1
//        scenario_data.empire.distant_battle_enemy_travel_months = SCENARIO->empire->read_u8(); // 1
//        scenario_data.open_play_scenario_id = SCENARIO->empire->read_u8(); // 1
//        SCENARIO->empire->skip(1);
//    }
//
//    // 11. wheat??? (4)
//    if (SCENARIO->wheat->is_valid(1))
//        scenario_data.rome_supplies_wheat = SCENARIO->wheat->read_i32(); // 4
//
//    // 2. requests (160)
//    if (SCENARIO->requests->is_valid(1)) {
//        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
//            scenario_data.requests[i].year = SCENARIO->requests->read_i16(); // 40
//        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
//            scenario_data.requests[i].resource = SCENARIO->requests->read_i16(); // 40
//        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
//            scenario_data.requests[i].amount = SCENARIO->requests->read_i16(); // 40
//        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
//            scenario_data.requests[i].deadline_years = SCENARIO->requests->read_i16(); // 40
//    }
//    // 2b. invasions (200 + 2)
//    if (SCENARIO->invasions->is_valid(1)) {
//        for (int i = 0; i < MAX_INVASIONS[GAME_ENV]; i++)
//            scenario_data.invasions[i].year = SCENARIO->invasions->read_i16(); // 40
//        for (int i = 0; i < MAX_INVASIONS[GAME_ENV]; i++)
//            scenario_data.invasions[i].type = SCENARIO->invasions->read_i16(); // 40
//        for (int i = 0; i < MAX_INVASIONS[GAME_ENV]; i++)
//            scenario_data.invasions[i].amount = SCENARIO->invasions->read_i16(); // 40
//        for (int i = 0; i < MAX_INVASIONS[GAME_ENV]; i++)
//            scenario_data.invasions[i].from = SCENARIO->invasions->read_i16(); // 40
//        for (int i = 0; i < MAX_INVASIONS[GAME_ENV]; i++)
//            scenario_data.invasions[i].attack_type = SCENARIO->invasions->read_i16(); // 40
//        SCENARIO->invasions->skip(2);
//    }
//
//    // 15. invasion entry points (32)
//    if (SCENARIO->invasion_points->is_valid(1)) {
//        for (int i = 0; i < MAX_INVASION_POINTS[GAME_ENV]; i++)
//            scenario_data.invasion_points[i].x = SCENARIO->invasion_points->read_i16(); // 2
//        for (int i = 0; i < MAX_INVASION_POINTS[GAME_ENV]; i++)
//            scenario_data.invasion_points[i].y = SCENARIO->invasion_points->read_i16(); // 2
//    }
//
//    // 4. request can-comply dialog (20)
//    if (SCENARIO->request_comply_dialogs->is_valid(1))
//        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
//            scenario_data.requests[i].can_comply_dialog_shown = SCENARIO->request_comply_dialogs->read_u8(); // 1
//
//    // 7. demands (240)
//    // demand changes (120)
//    if (SCENARIO->demands->is_valid(1)) {
//        for (int i = 0; i < MAX_DEMAND_CHANGES[GAME_ENV]; i++)
//            scenario_data.demand_changes[i].year = SCENARIO->demands->read_i16(); // 2
//        for (int i = 0; i < MAX_DEMAND_CHANGES[GAME_ENV]; i++)
//            scenario_data.demand_changes[i].month = SCENARIO->demands->read_u8(); // 1
//        for (int i = 0; i < MAX_DEMAND_CHANGES[GAME_ENV]; i++)
//            scenario_data.demand_changes[i].resource = SCENARIO->demands->read_u8(); // 1
//        for (int i = 0; i < MAX_DEMAND_CHANGES[GAME_ENV]; i++)
//            scenario_data.demand_changes[i].route_id = SCENARIO->demands->read_u8(); // 1
//        for (int i = 0; i < MAX_DEMAND_CHANGES[GAME_ENV]; i++)
//            scenario_data.demand_changes[i].is_rise = SCENARIO->demands->read_u8(); // 1
//    }
//    // 7b. price changes (120)
//    if (SCENARIO->price_changes->is_valid(1)) {
//        for (int i = 0; i < MAX_PRICE_CHANGES[GAME_ENV]; i++)
//            scenario_data.price_changes[i].year = SCENARIO->price_changes->read_i16(); // 2
//        for (int i = 0; i < MAX_PRICE_CHANGES[GAME_ENV]; i++)
//            scenario_data.price_changes[i].month = SCENARIO->price_changes->read_u8(); // 1
//        for (int i = 0; i < MAX_PRICE_CHANGES[GAME_ENV]; i++)
//            scenario_data.price_changes[i].resource = SCENARIO->price_changes->read_u8(); // 1
//        for (int i = 0; i < MAX_PRICE_CHANGES[GAME_ENV]; i++)
//            scenario_data.price_changes[i].amount = SCENARIO->price_changes->read_u8(); // 1
//        for (int i = 0; i < MAX_PRICE_CHANGES[GAME_ENV]; i++)
//            scenario_data.price_changes[i].is_rise = SCENARIO->price_changes->read_u8(); // 1
//    }
//
//    // 9. fishing (32)
//    if (SCENARIO->fishing_points->is_valid(1)) {
//        for (int i = 0; i < MAX_FISH_POINTS[GAME_ENV]; i++)
//            scenario_data.fishing_points[i].x = SCENARIO->fishing_points->read_i16(); // 2
//        for (int i = 0; i < MAX_FISH_POINTS[GAME_ENV]; i++)
//            scenario_data.fishing_points[i].y = SCENARIO->fishing_points->read_i16(); // 2
//    }
//
//    // 10. other request buf (120)
//    if (SCENARIO->request_extra->is_valid(1)) {
//        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
//            scenario_data.requests[i].favor = SCENARIO->request_extra->read_u8(); // 1
//        for (int i = 0; i < MAX_INVASIONS[GAME_ENV]; i++)
//            scenario_data.invasions[i].month = SCENARIO->request_extra->read_u8(); // 1
//        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
//            scenario_data.requests[i].month = SCENARIO->request_extra->read_u8(); // 1
//        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
//            scenario_data.requests[i].state = SCENARIO->request_extra->read_u8(); // 1
//        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
//            scenario_data.requests[i].visible = SCENARIO->request_extra->read_u8(); // 1
//        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
//            scenario_data.requests[i].months_to_comply = SCENARIO->request_extra->read_u8(); // 1
//    }

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