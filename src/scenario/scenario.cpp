#include <city/data_private.h>
#include <city/gods.h>
#include "scenario.h"

#include "city/resource.h"
#include "empire/trade_route.h"
#include "game/difficulty.h"
#include "game/settings.h"
#include "scenario/data.h"
#include "events.h"

struct scenario_t scenario;

bool scenario_is_saved(void) {
    return scenario.is_saved;
}

void scenario_save_state(scenario_data_buffers *SCENARIO) {

    // PRIMARY DATA
    if (GAME_ENV == ENGINE_ENV_C3)
            SCENARIO->mission_index->write_i32(scenario.settings.campaign_mission);
    else if (GAME_ENV == ENGINE_ENV_PHARAOH)
            SCENARIO->mission_index->write_i8(scenario.settings.campaign_mission);

    SCENARIO->map_settings->write_i32(scenario.settings.starting_favor);
    SCENARIO->map_settings->write_i32(scenario.settings.starting_personal_savings);
    SCENARIO->map_settings->write_i32(scenario.settings.campaign_rank);

    SCENARIO->is_custom->write_i32(scenario.settings.is_custom);

    for (int i = 0; i < MAX_PLAYER_NAME; i++)
        SCENARIO->player_name->write_u8(0);
    SCENARIO->player_name->write_raw(scenario.settings.player_name, MAX_PLAYER_NAME);
    SCENARIO->map_name->write_raw(scenario.scenario_name, MAX_SCENARIO_NAME);


    // header
    if (SCENARIO->header) {
        SCENARIO->header->write_i16(scenario.start_year);
        SCENARIO->header->write_i16(0);
        SCENARIO->header->write_i16(scenario.empire.id);
        SCENARIO->header->skip(8);
    }

    // requests
    if (SCENARIO->requests) {
        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
            SCENARIO->requests->write_i16(scenario.requests[i].year);
        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
            SCENARIO->requests->write_i16(scenario.requests[i].resource);
        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
            SCENARIO->requests->write_i16(scenario.requests[i].amount);
        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
            SCENARIO->requests->write_i16(scenario.requests[i].deadline_years);
    }

    // invasions
    if (SCENARIO->invasions) {
        for (int i = 0; i < MAX_INVASIONS[GAME_ENV]; i++)
            SCENARIO->invasions->write_i16(scenario.invasions[i].year);
        for (int i = 0; i < MAX_INVASIONS[GAME_ENV]; i++)
            SCENARIO->invasions->write_i16(scenario.invasions[i].type);
        for (int i = 0; i < MAX_INVASIONS[GAME_ENV]; i++)
            SCENARIO->invasions->write_i16(scenario.invasions[i].amount);
        for (int i = 0; i < MAX_INVASIONS[GAME_ENV]; i++)
            SCENARIO->invasions->write_i16(scenario.invasions[i].from);
        for (int i = 0; i < MAX_INVASIONS[GAME_ENV]; i++)
            SCENARIO->invasions->write_i16(scenario.invasions[i].attack_type);
    }
//    buf->invasions->write_i16(0);

    // info 1
    if (SCENARIO->info1) {
        SCENARIO->info1->write_i32(scenario.initial_funds);
        SCENARIO->info1->write_i16(scenario.enemy_id);
        SCENARIO->info1->write_i16(0);
        SCENARIO->info1->write_i16(0);
        SCENARIO->info1->write_i16(0);
        SCENARIO->info1->write_i32(scenario.map.width);
        SCENARIO->info1->write_i32(scenario.map.height);
        SCENARIO->info1->write_i32(scenario.map.grid_start);
        SCENARIO->info1->write_i32(scenario.map.grid_border_size);
        SCENARIO->info1->write_raw(scenario.subtitle, MAX_SUBTITLE);
        SCENARIO->info1->write_raw(scenario.brief_description, MAX_BRIEF_DESCRIPTION);
    }

    // request comply dialog
    if (SCENARIO->request_comply_dialogs)
        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
            SCENARIO->request_comply_dialogs->write_u8(scenario.requests[i].can_comply_dialog_shown);

    // info 2
    if (SCENARIO->info2) {
        SCENARIO->info2->write_i16(scenario.image_id);
        SCENARIO->info2->write_i16(scenario.is_open_play);
        SCENARIO->info2->write_i16(scenario.player_rank);
    }

    // herds
    if (SCENARIO->herds) {
        for (int i = 0; i < MAX_HERD_POINTS[GAME_ENV]; i++)
            SCENARIO->herds->write_i16(scenario.herd_points[i].x);
        for (int i = 0; i < MAX_HERD_POINTS[GAME_ENV]; i++)
            SCENARIO->herds->write_i16(scenario.herd_points[i].y);
    }

    // demand changes
    if (SCENARIO->demands) {
        for (int i = 0; i < MAX_DEMAND_CHANGES[GAME_ENV]; i++)
            SCENARIO->demands->write_i16(scenario.demand_changes[i].year);
        for (int i = 0; i < MAX_DEMAND_CHANGES[GAME_ENV]; i++)
            SCENARIO->demands->write_u8(scenario.demand_changes[i].month);
        for (int i = 0; i < MAX_DEMAND_CHANGES[GAME_ENV]; i++)
            SCENARIO->demands->write_u8(scenario.demand_changes[i].resource);
        for (int i = 0; i < MAX_DEMAND_CHANGES[GAME_ENV]; i++)
            SCENARIO->demands->write_u8(scenario.demand_changes[i].route_id);
        for (int i = 0; i < MAX_DEMAND_CHANGES[GAME_ENV]; i++)
            SCENARIO->demands->write_u8(scenario.demand_changes[i].is_rise);
    }

    // price changes
    if (SCENARIO->price_changes) {
        for (int i = 0; i < MAX_PRICE_CHANGES[GAME_ENV]; i++)
            SCENARIO->price_changes->write_i16(scenario.price_changes[i].year);
        for (int i = 0; i < MAX_PRICE_CHANGES[GAME_ENV]; i++)
            SCENARIO->price_changes->write_u8(scenario.price_changes[i].month);
        for (int i = 0; i < MAX_PRICE_CHANGES[GAME_ENV]; i++)
            SCENARIO->price_changes->write_u8(scenario.price_changes[i].resource);
        for (int i = 0; i < MAX_PRICE_CHANGES[GAME_ENV]; i++)
            SCENARIO->price_changes->write_u8(scenario.price_changes[i].amount);
        for (int i = 0; i < MAX_PRICE_CHANGES[GAME_ENV]; i++)
            SCENARIO->price_changes->write_u8(scenario.price_changes[i].is_rise);
    }

    // events
    if (SCENARIO->events) {
        SCENARIO->events->write_i32(scenario.gladiator_revolt.enabled);
        SCENARIO->events->write_i32(scenario.gladiator_revolt.year);
        SCENARIO->events->write_i32(scenario.emperor_change.enabled);
        SCENARIO->events->write_i32(scenario.emperor_change.year);
        SCENARIO->events->write_i32(scenario.random_events.sea_trade_problem);
        SCENARIO->events->write_i32(scenario.random_events.land_trade_problem);
        SCENARIO->events->write_i32(scenario.random_events.raise_wages);
        SCENARIO->events->write_i32(scenario.random_events.lower_wages);
        SCENARIO->events->write_i32(scenario.random_events.contaminated_water);
        SCENARIO->events->write_i32(scenario.random_events.iron_mine_collapse);
        SCENARIO->events->write_i32(scenario.random_events.clay_pit_flooded);
    }

    // fishing points
    if (SCENARIO->fishing_points) {
        for (int i = 0; i < MAX_FISH_POINTS[GAME_ENV]; i++)
            SCENARIO->fishing_points->write_i16(scenario.fishing_points[i].x);
        for (int i = 0; i < MAX_FISH_POINTS[GAME_ENV]; i++)
            SCENARIO->fishing_points->write_i16(scenario.fishing_points[i].y);
    }

    // requests extra
    if (SCENARIO->request_extra) {
        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
            SCENARIO->request_extra->write_u8(scenario.requests[i].favor);
        for (int i = 0; i < MAX_INVASIONS[GAME_ENV]; i++)
            SCENARIO->request_extra->write_u8(scenario.invasions[i].month);
        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
            SCENARIO->request_extra->write_u8(scenario.requests[i].month);
        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
            SCENARIO->request_extra->write_u8(scenario.requests[i].state);
        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
            SCENARIO->request_extra->write_u8(scenario.requests[i].visible);
        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
            SCENARIO->request_extra->write_u8(scenario.requests[i].months_to_comply);
    }

    // rome wheat supplies enabled
    if (SCENARIO->wheat)
        SCENARIO->wheat->write_i32(scenario.rome_supplies_wheat);

    // allowed buildings
    if (SCENARIO->allowed_builds)
        for (int i = 0; i < MAX_ALLOWED_BUILDINGS[GAME_ENV]; i++)
            SCENARIO->allowed_builds->write_i16(scenario.allowed_buildings[i]);

    // win criteria
    if (SCENARIO->win_criteria) {
        SCENARIO->win_criteria->write_i32(scenario.win_criteria.culture.goal);
        SCENARIO->win_criteria->write_i32(scenario.win_criteria.prosperity.goal);
        SCENARIO->win_criteria->write_i32(scenario.win_criteria.peace.goal);
        SCENARIO->win_criteria->write_i32(scenario.win_criteria.favor.goal);
        if (GAME_ENV == ENGINE_ENV_PHARAOH) {
            SCENARIO->win_criteria->write_i32(scenario.win_criteria.ph_goal1.goal);
            SCENARIO->win_criteria->write_i32(scenario.win_criteria.ph_goal2.goal);
        }
        SCENARIO->win_criteria->write_u8(scenario.win_criteria.culture.enabled);
        SCENARIO->win_criteria->write_u8(scenario.win_criteria.prosperity.enabled);
        SCENARIO->win_criteria->write_u8(scenario.win_criteria.peace.enabled);
        SCENARIO->win_criteria->write_u8(scenario.win_criteria.favor.enabled);
        if (GAME_ENV == ENGINE_ENV_PHARAOH) {
            SCENARIO->win_criteria->write_u8(scenario.win_criteria.ph_goal1.enabled);
            SCENARIO->win_criteria->write_u8(scenario.win_criteria.ph_goal2.enabled);
        }
        SCENARIO->win_criteria->write_i32(scenario.win_criteria.time_limit.enabled);
        SCENARIO->win_criteria->write_i32(scenario.win_criteria.time_limit.years);
        SCENARIO->win_criteria->write_i32(scenario.win_criteria.survival_time.enabled);
        SCENARIO->win_criteria->write_i32(scenario.win_criteria.survival_time.years);
        SCENARIO->win_criteria->write_i32(scenario.earthquake.severity);
        if (GAME_ENV == ENGINE_ENV_C3)
            SCENARIO->win_criteria->write_i32(scenario.earthquake.year);
        else if (GAME_ENV == ENGINE_ENV_PHARAOH)
            SCENARIO->win_criteria->write_i16(0);
        SCENARIO->win_criteria->write_i32(scenario.win_criteria.population.enabled);
        SCENARIO->win_criteria->write_i32(scenario.win_criteria.population.goal);
    }

    // map points
    if (SCENARIO->map_points) {
        SCENARIO->map_points->write_i16(scenario.earthquake_point.x);
        SCENARIO->map_points->write_i16(scenario.earthquake_point.y);
        SCENARIO->map_points->write_i16(scenario.entry_point.x);
        SCENARIO->map_points->write_i16(scenario.entry_point.y);
        SCENARIO->map_points->write_i16(scenario.exit_point.x);
        SCENARIO->map_points->write_i16(scenario.exit_point.y);
    }

    // invasion points
    if (SCENARIO->invasion_points) {
        for (int i = 0; i < MAX_INVASION_POINTS[GAME_ENV]; i++)
            SCENARIO->invasion_points->write_i16(scenario.invasion_points[i].x);
        for (int i = 0; i < MAX_INVASION_POINTS[GAME_ENV]; i++)
            SCENARIO->invasion_points->write_i16(scenario.invasion_points[i].y);
    }

    // river points
    if (SCENARIO->river_points) {
        SCENARIO->river_points->write_i16(scenario.river_entry_point.x);
        SCENARIO->river_points->write_i16(scenario.river_entry_point.y);
        SCENARIO->river_points->write_i16(scenario.river_exit_point.x);
        SCENARIO->river_points->write_i16(scenario.river_exit_point.y);
    }

    // info 3
    if (SCENARIO->info3) {
        SCENARIO->info3->write_i32(scenario.rescue_loan);
        SCENARIO->info3->write_i32(scenario.win_criteria.milestone25_year);
        SCENARIO->info3->write_i32(scenario.win_criteria.milestone50_year);
        SCENARIO->info3->write_i32(scenario.win_criteria.milestone75_year);
        SCENARIO->info3->write_i32(scenario.native_images.hut);
        SCENARIO->info3->write_i32(scenario.native_images.meeting);
        SCENARIO->info3->write_i32(scenario.native_images.crops);
        SCENARIO->info3->write_u8(scenario.climate);
        SCENARIO->info3->write_u8(scenario.flotsam_enabled);
        SCENARIO->info3->write_i16(0);
    }

    // empire
    if (SCENARIO->empire) {
        SCENARIO->empire->write_i32(scenario.empire.is_expanded);
        SCENARIO->empire->write_i32(scenario.empire.expansion_year);
        SCENARIO->empire->write_u8(scenario.empire.distant_battle_roman_travel_months);
        SCENARIO->empire->write_u8(scenario.empire.distant_battle_enemy_travel_months);
        SCENARIO->empire->write_u8(scenario.open_play_scenario_id);
        SCENARIO->empire->write_u8(0);
    }

    scenario.is_saved = true;
}
void scenario_load_state(scenario_data_buffers *SCENARIO) {

    // PRIMARY DATA
    if (GAME_ENV == ENGINE_ENV_C3)
        scenario.settings.campaign_mission = SCENARIO->mission_index->read_i32();
    else if (GAME_ENV == ENGINE_ENV_PHARAOH)
        scenario.settings.campaign_mission = SCENARIO->mission_index->read_u8();

    scenario.settings.starting_favor = SCENARIO->map_settings->read_i32();
    scenario.settings.starting_personal_savings = SCENARIO->map_settings->read_i32();
    scenario.settings.campaign_rank = SCENARIO->map_settings->read_i32();

    scenario.settings.is_custom = SCENARIO->is_custom->read_i32();

    SCENARIO->player_name->skip(MAX_PLAYER_NAME); // first field is adversary name? unused?
    SCENARIO->player_name->read_raw(scenario.settings.player_name, MAX_PLAYER_NAME);

    SCENARIO->map_name->read_raw(scenario.scenario_name, MAX_SCENARIO_NAME);

    // C3:
    // 1. header
    // 2. requests/invasions
    // 3. map info 1
    // 4. request can-comply dialog
    // 5. map info 2
    // 6. herds
    // 7. demands
    // 8. random events
    // 9. fishing
    // 10. other request buf
    // 11. wheat
    // 12. allowed buildings
    // 13. win criteria
    // 14. map points
    // 15. invasion entry points
    // 16. river entry points
    // 17. map info 3
    // 18. empire info

    // 1. header (32)
    if (SCENARIO->header->is_valid(1)) {
        scenario.start_year = SCENARIO->header->read_i16(); // 2 bytes
        SCENARIO->header->skip(2);
        scenario.empire.id = SCENARIO->header->read_i16(); // 2 bytes
        SCENARIO->header->skip(4);
        if (GAME_ENV == ENGINE_ENV_PHARAOH) {
            for (int i = 0; i < MAX_GODS; i++)
                city_data.religion.gods[i].is_known = SCENARIO->header->read_i16();
            SCENARIO->header->skip(10);
            SCENARIO->header->skip(2); // 2 bytes ???        03 00
        }
    }

    // 3. map info 1 (614)
    if (SCENARIO->info1->is_valid(1)) { // (12)
        scenario.initial_funds = SCENARIO->info1->read_i32(); // 4
        scenario.enemy_id = SCENARIO->info1->read_i16(); // 2
        SCENARIO->info1->skip(6);
        // (16)
        scenario.map.width = SCENARIO->info1->read_i32(); // 4
        scenario.map.height = SCENARIO->info1->read_i32(); // 4
        scenario.map.grid_start = SCENARIO->info1->read_i32(); // 4
        scenario.map.grid_border_size = SCENARIO->info1->read_i32(); // 4
        // (64 + 522 = 576)
        SCENARIO->info1->read_raw(scenario.subtitle, MAX_SUBTITLE);
        SCENARIO->info1->read_raw(scenario.brief_description, MAX_BRIEF_DESCRIPTION);
    }

    // 5. map info 2 (6)
    if (SCENARIO->info2->is_valid(1)) {
        scenario.image_id = SCENARIO->info2->read_i16(); // 2
        scenario.is_open_play = SCENARIO->info2->read_i16(); // 2
        scenario.player_rank = SCENARIO->info2->read_i16(); // 2
    }

    // 17. map info 3 (30 + 2)
    if (SCENARIO->info3->is_valid(1)) {
        scenario.rescue_loan = SCENARIO->info3->read_i32(); // 4
        scenario.win_criteria.milestone25_year = SCENARIO->info3->read_i32(); // 4
        scenario.win_criteria.milestone50_year = SCENARIO->info3->read_i32(); // 4
        scenario.win_criteria.milestone75_year = SCENARIO->info3->read_i32(); // 4
        scenario.native_images.hut = SCENARIO->info3->read_i32(); // 4
        scenario.native_images.meeting = SCENARIO->info3->read_i32(); // 4
        scenario.native_images.crops = SCENARIO->info3->read_i32(); // 4
        scenario.climate = SCENARIO->info3->read_u8(); // 1
        scenario.flotsam_enabled = SCENARIO->info3->read_u8(); // 1
        SCENARIO->info3->skip(2);
    }

    // 8. random events (44)
    // events
    if (SCENARIO->events->is_valid(1)) {
        scenario.gladiator_revolt.enabled = SCENARIO->events->read_i32(); // 4
        scenario.gladiator_revolt.year = SCENARIO->events->read_i32(); // 4
        scenario.emperor_change.enabled = SCENARIO->events->read_i32(); // 4
        scenario.emperor_change.year = SCENARIO->events->read_i32(); // 4
        scenario.random_events.sea_trade_problem = SCENARIO->events->read_i32(); // 4
        scenario.random_events.land_trade_problem = SCENARIO->events->read_i32(); // 4
        scenario.random_events.raise_wages = SCENARIO->events->read_i32(); // 4
        scenario.random_events.lower_wages = SCENARIO->events->read_i32(); // 4
        scenario.random_events.contaminated_water = SCENARIO->events->read_i32(); // 4
        scenario.random_events.iron_mine_collapse = SCENARIO->events->read_i32(); // 4
        scenario.random_events.clay_pit_flooded = SCENARIO->events->read_i32(); // 4
    }

    // 13. win criteria (52 / 60)
    if (SCENARIO->win_criteria->is_valid(1)) {
        scenario.win_criteria.culture.goal = SCENARIO->win_criteria->read_i32(); // 4
        scenario.win_criteria.prosperity.goal = SCENARIO->win_criteria->read_i32(); // 4
        scenario.win_criteria.peace.goal = SCENARIO->win_criteria->read_i32(); // 4
        scenario.win_criteria.favor.goal = SCENARIO->win_criteria->read_i32(); // 4
        if (GAME_ENV == ENGINE_ENV_PHARAOH) {
            scenario.win_criteria.ph_goal1.goal = SCENARIO->win_criteria->read_i32(); // 4
            scenario.win_criteria.ph_goal2.goal = SCENARIO->win_criteria->read_i32(); // 4
        }
        scenario.win_criteria.culture.enabled = SCENARIO->win_criteria->read_u8(); // 1
        scenario.win_criteria.prosperity.enabled = SCENARIO->win_criteria->read_u8(); // 1
        scenario.win_criteria.peace.enabled = SCENARIO->win_criteria->read_u8(); // 1
        scenario.win_criteria.favor.enabled = SCENARIO->win_criteria->read_u8(); // 1
        if (GAME_ENV == ENGINE_ENV_PHARAOH) {
            scenario.win_criteria.ph_goal1.enabled = SCENARIO->win_criteria->read_u8(); // 1
            scenario.win_criteria.ph_goal2.enabled = SCENARIO->win_criteria->read_u8(); // 1
        }
        scenario.win_criteria.time_limit.enabled = SCENARIO->win_criteria->read_i32(); // 4
        scenario.win_criteria.time_limit.years = SCENARIO->win_criteria->read_i32(); // 4
        scenario.win_criteria.survival_time.enabled = SCENARIO->win_criteria->read_i32(); // 4
        scenario.win_criteria.survival_time.years = SCENARIO->win_criteria->read_i32(); // 4
        scenario.earthquake.severity = SCENARIO->win_criteria->read_i32(); // 4
        if (GAME_ENV == ENGINE_ENV_C3)
            scenario.earthquake.year = SCENARIO->win_criteria->read_i32(); // 4
        else if (GAME_ENV == ENGINE_ENV_PHARAOH)
            SCENARIO->win_criteria->skip(2); // 2
        scenario.win_criteria.population.enabled = SCENARIO->win_criteria->read_i32(); // 4
        scenario.win_criteria.population.goal = SCENARIO->win_criteria->read_i32(); // 4
    }

    // 14. map points (12)
    if (SCENARIO->map_points->is_valid(1)) {
        scenario.earthquake_point.x = SCENARIO->map_points->read_i16(); // 2
        scenario.earthquake_point.y = SCENARIO->map_points->read_i16(); // 2
        scenario.entry_point.x = SCENARIO->map_points->read_i16(); // 2
        scenario.entry_point.y = SCENARIO->map_points->read_i16(); // 2
        scenario.exit_point.x = SCENARIO->map_points->read_i16(); // 2
        scenario.exit_point.y = SCENARIO->map_points->read_i16(); // 2
    }

    // 16. river entry points (8)
    if (SCENARIO->map_points->is_valid(1)) {
        scenario.river_entry_point.x = SCENARIO->river_points->read_i16(); // 2
        scenario.river_entry_point.y = SCENARIO->river_points->read_i16(); // 2
        scenario.river_exit_point.x = SCENARIO->river_points->read_i16(); // 2
        scenario.river_exit_point.y = SCENARIO->river_points->read_i16(); // 2
    }

    // 18. empire (11 + 1)
    if (SCENARIO->empire->is_valid(1)) {
        scenario.empire.is_expanded = SCENARIO->empire->read_i32(); // 4
        scenario.empire.expansion_year = SCENARIO->empire->read_i32(); // 4
        scenario.empire.distant_battle_roman_travel_months = SCENARIO->empire->read_u8(); // 1
        scenario.empire.distant_battle_enemy_travel_months = SCENARIO->empire->read_u8(); // 1
        scenario.open_play_scenario_id = SCENARIO->empire->read_u8(); // 1
        SCENARIO->empire->skip(1);
    }

    // 11. wheat??? (4)
    if (SCENARIO->wheat->is_valid(1))
        scenario.rome_supplies_wheat = SCENARIO->wheat->read_i32(); // 4

    // 2. requests (160)
    if (SCENARIO->requests->is_valid(1)) {
        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
            scenario.requests[i].year = SCENARIO->requests->read_i16(); // 40
        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
            scenario.requests[i].resource = SCENARIO->requests->read_i16(); // 40
        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
            scenario.requests[i].amount = SCENARIO->requests->read_i16(); // 40
        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
            scenario.requests[i].deadline_years = SCENARIO->requests->read_i16(); // 40
    }
    // 2b. invasions (200 + 2)
    if (SCENARIO->invasions->is_valid(1)) {
        for (int i = 0; i < MAX_INVASIONS[GAME_ENV]; i++)
            scenario.invasions[i].year = SCENARIO->invasions->read_i16(); // 40
        for (int i = 0; i < MAX_INVASIONS[GAME_ENV]; i++)
            scenario.invasions[i].type = SCENARIO->invasions->read_i16(); // 40
        for (int i = 0; i < MAX_INVASIONS[GAME_ENV]; i++)
            scenario.invasions[i].amount = SCENARIO->invasions->read_i16(); // 40
        for (int i = 0; i < MAX_INVASIONS[GAME_ENV]; i++)
            scenario.invasions[i].from = SCENARIO->invasions->read_i16(); // 40
        for (int i = 0; i < MAX_INVASIONS[GAME_ENV]; i++)
            scenario.invasions[i].attack_type = SCENARIO->invasions->read_i16(); // 40
        SCENARIO->invasions->skip(2);
    }

    // 15. invasion entry points (32)
    if (SCENARIO->invasion_points->is_valid(1)) {
        for (int i = 0; i < MAX_INVASION_POINTS[GAME_ENV]; i++)
            scenario.invasion_points[i].x = SCENARIO->invasion_points->read_i16(); // 2
        for (int i = 0; i < MAX_INVASION_POINTS[GAME_ENV]; i++)
            scenario.invasion_points[i].y = SCENARIO->invasion_points->read_i16(); // 2
    }

    // 4. request can-comply dialog (20)
    if (SCENARIO->request_comply_dialogs->is_valid(1))
        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
            scenario.requests[i].can_comply_dialog_shown = SCENARIO->request_comply_dialogs->read_u8(); // 1

    // 6. animal herds (16 : 32)
    if (SCENARIO->herds->is_valid(1)) {
        if (GAME_ENV == ENGINE_ENV_C3) {
            for (int i = 0; i < MAX_HERD_POINTS[GAME_ENV]; i++)
                scenario.herd_points[i].x = SCENARIO->herds->read_i16(); // 2
            for (int i = 0; i < MAX_HERD_POINTS[GAME_ENV]; i++)
                scenario.herd_points[i].y = SCENARIO->herds->read_i16(); // 2
        } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
            for (int i = 0; i < MAX_HERD_POINTS[GAME_ENV]; i++)
                scenario.herd_points[i].x = SCENARIO->herds->read_i32(); // 4
            for (int i = 0; i < MAX_HERD_POINTS[GAME_ENV]; i++)
                scenario.herd_points[i].y = SCENARIO->herds->read_i32(); // 4
        }
    }

    // 7. demands (240)
    // demand changes (120)
    if (SCENARIO->demands->is_valid(1)) {
        for (int i = 0; i < MAX_DEMAND_CHANGES[GAME_ENV]; i++)
            scenario.demand_changes[i].year = SCENARIO->demands->read_i16(); // 2
        for (int i = 0; i < MAX_DEMAND_CHANGES[GAME_ENV]; i++)
            scenario.demand_changes[i].month = SCENARIO->demands->read_u8(); // 1
        for (int i = 0; i < MAX_DEMAND_CHANGES[GAME_ENV]; i++)
            scenario.demand_changes[i].resource = SCENARIO->demands->read_u8(); // 1
        for (int i = 0; i < MAX_DEMAND_CHANGES[GAME_ENV]; i++)
            scenario.demand_changes[i].route_id = SCENARIO->demands->read_u8(); // 1
        for (int i = 0; i < MAX_DEMAND_CHANGES[GAME_ENV]; i++)
            scenario.demand_changes[i].is_rise = SCENARIO->demands->read_u8(); // 1
    }
    // 7b. price changes (120)
    if (SCENARIO->price_changes->is_valid(1)) {
        for (int i = 0; i < MAX_PRICE_CHANGES[GAME_ENV]; i++)
            scenario.price_changes[i].year = SCENARIO->price_changes->read_i16(); // 2
        for (int i = 0; i < MAX_PRICE_CHANGES[GAME_ENV]; i++)
            scenario.price_changes[i].month = SCENARIO->price_changes->read_u8(); // 1
        for (int i = 0; i < MAX_PRICE_CHANGES[GAME_ENV]; i++)
            scenario.price_changes[i].resource = SCENARIO->price_changes->read_u8(); // 1
        for (int i = 0; i < MAX_PRICE_CHANGES[GAME_ENV]; i++)
            scenario.price_changes[i].amount = SCENARIO->price_changes->read_u8(); // 1
        for (int i = 0; i < MAX_PRICE_CHANGES[GAME_ENV]; i++)
            scenario.price_changes[i].is_rise = SCENARIO->price_changes->read_u8(); // 1
    }

    // 9. fishing (32)
    if (SCENARIO->fishing_points->is_valid(1)) {
        for (int i = 0; i < MAX_FISH_POINTS[GAME_ENV]; i++)
            scenario.fishing_points[i].x = SCENARIO->fishing_points->read_i16(); // 2
        for (int i = 0; i < MAX_FISH_POINTS[GAME_ENV]; i++)
            scenario.fishing_points[i].y = SCENARIO->fishing_points->read_i16(); // 2
    }

    // 10. other request buf (120)
    if (SCENARIO->request_extra->is_valid(1)) {
        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
            scenario.requests[i].favor = SCENARIO->request_extra->read_u8(); // 1
        for (int i = 0; i < MAX_INVASIONS[GAME_ENV]; i++)
            scenario.invasions[i].month = SCENARIO->request_extra->read_u8(); // 1
        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
            scenario.requests[i].month = SCENARIO->request_extra->read_u8(); // 1
        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
            scenario.requests[i].state = SCENARIO->request_extra->read_u8(); // 1
        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
            scenario.requests[i].visible = SCENARIO->request_extra->read_u8(); // 1
        for (int i = 0; i < MAX_REQUESTS[GAME_ENV]; i++)
            scenario.requests[i].months_to_comply = SCENARIO->request_extra->read_u8(); // 1
    }
    // 12. allowed buildings (100 / 228)
    if (SCENARIO->allowed_builds->is_valid(1))
        for (int i = 0; i < MAX_ALLOWED_BUILDINGS[GAME_ENV]; i++)
            scenario.allowed_buildings[i] = SCENARIO->allowed_builds->read_i16(); // 2

    // Pharaoh scenario events
    if (SCENARIO->events_ph->is_valid(1))
        scenario_events_load_state(SCENARIO->events_ph);

    scenario.is_saved = true;
}

void scenario_settings_init(void) {
    scenario.settings.campaign_mission = 0;
    scenario.settings.campaign_rank = 0;
    scenario.settings.is_custom = 0;
    scenario.settings.starting_favor = difficulty_starting_favor();
    scenario.settings.starting_personal_savings = 0;
}
void scenario_settings_init_mission(void) {
    scenario.settings.starting_favor = difficulty_starting_favor();
    scenario.settings.starting_personal_savings = setting_personal_savings_for_mission(scenario.settings.campaign_rank);
}

void scenario_fix_patch_trade(int mission_id) { // todo: only C3
    // Damascus, allow import of marble
    if (mission_id == 15)
        trade_route_init(1, RESOURCE_MARBLE_C3, 15);
}