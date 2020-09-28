#include "scenario.h"

#include "city/resource.h"
#include "empire/trade_route.h"
#include "game/difficulty.h"
#include "game/settings.h"
#include "scenario/data.h"

struct scenario_t scenario;

int scenario_is_saved(void) {
    return scenario.is_saved;
}

void scenario_save_state(scenario_data_buffers *data) {
    // header
    if (data->header) {
        data->header->write_i16(scenario.start_year);
        data->header->write_i16(0);
        data->header->write_i16(scenario.empire.id);
        data->header->skip(8);
    }

    // requests
    if (data->requests) {
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            data->requests->write_i16(scenario.requests[i].year);
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            data->requests->write_i16(scenario.requests[i].resource);
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            data->requests->write_i16(scenario.requests[i].amount);
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            data->requests->write_i16(scenario.requests[i].deadline_years);
    }

    // invasions
    if (data->invasions) {
        for (int i = 0; i < env_sizes().MAX_INVASIONS; i++)
            data->invasions->write_i16(scenario.invasions[i].year);
        for (int i = 0; i < env_sizes().MAX_INVASIONS; i++)
            data->invasions->write_i16(scenario.invasions[i].type);
        for (int i = 0; i < env_sizes().MAX_INVASIONS; i++)
            data->invasions->write_i16(scenario.invasions[i].amount);
        for (int i = 0; i < env_sizes().MAX_INVASIONS; i++)
            data->invasions->write_i16(scenario.invasions[i].from);
        for (int i = 0; i < env_sizes().MAX_INVASIONS; i++)
            data->invasions->write_i16(scenario.invasions[i].attack_type);
    }
//    data->invasions->write_i16(0);

    // info 1
    if (data->info1) {
        data->info1->write_i32(scenario.initial_funds);
        data->info1->write_i16(scenario.enemy_id);
        data->info1->write_i16(0);
        data->info1->write_i16(0);
        data->info1->write_i16(0);
        data->info1->write_i32(scenario.map.width);
        data->info1->write_i32(scenario.map.height);
        data->info1->write_i32(scenario.map.grid_start);
        data->info1->write_i32(scenario.map.grid_border_size);
        data->info1->write_raw(scenario.brief_description, env_sizes().MAX_BRIEF_DESCRIPTION);
        data->info1->write_raw(scenario.briefing, env_sizes().MAX_BRIEFING);
    }

    // request comply dialog
    if (data->request_comply_dialogs)
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            data->request_comply_dialogs->write_u8(scenario.requests[i].can_comply_dialog_shown);

    // info 2
    if (data->info2) {
        data->info2->write_i16(scenario.image_id);
        data->info2->write_i16(scenario.is_open_play);
        data->info2->write_i16(scenario.player_rank);
    }

    // herds
    if (data->herds) {
        for (int i = 0; i < env_sizes().MAX_HERD_POINTS; i++)
            data->herds->write_i16(scenario.herd_points[i].x);
        for (int i = 0; i < env_sizes().MAX_HERD_POINTS; i++)
            data->herds->write_i16(scenario.herd_points[i].y);
    }

    // demand changes
    if (data->demands) {
        for (int i = 0; i < env_sizes().MAX_DEMAND_CHANGES; i++)
            data->demands->write_i16(scenario.demand_changes[i].year);
        for (int i = 0; i < env_sizes().MAX_DEMAND_CHANGES; i++)
            data->demands->write_u8(scenario.demand_changes[i].month);
        for (int i = 0; i < env_sizes().MAX_DEMAND_CHANGES; i++)
            data->demands->write_u8(scenario.demand_changes[i].resource);
        for (int i = 0; i < env_sizes().MAX_DEMAND_CHANGES; i++)
            data->demands->write_u8(scenario.demand_changes[i].route_id);
        for (int i = 0; i < env_sizes().MAX_DEMAND_CHANGES; i++)
            data->demands->write_u8(scenario.demand_changes[i].is_rise);
    }

    // price changes
    if (data->price_changes) {
        for (int i = 0; i < env_sizes().MAX_PRICE_CHANGES; i++)
            data->price_changes->write_i16(scenario.price_changes[i].year);
        for (int i = 0; i < env_sizes().MAX_PRICE_CHANGES; i++)
            data->price_changes->write_u8(scenario.price_changes[i].month);
        for (int i = 0; i < env_sizes().MAX_PRICE_CHANGES; i++)
            data->price_changes->write_u8(scenario.price_changes[i].resource);
        for (int i = 0; i < env_sizes().MAX_PRICE_CHANGES; i++)
            data->price_changes->write_u8(scenario.price_changes[i].amount);
        for (int i = 0; i < env_sizes().MAX_PRICE_CHANGES; i++)
            data->price_changes->write_u8(scenario.price_changes[i].is_rise);
    }

    // events
    if (data->events) {
        data->events->write_i32(scenario.gladiator_revolt.enabled);
        data->events->write_i32(scenario.gladiator_revolt.year);
        data->events->write_i32(scenario.emperor_change.enabled);
        data->events->write_i32(scenario.emperor_change.year);
        data->events->write_i32(scenario.random_events.sea_trade_problem);
        data->events->write_i32(scenario.random_events.land_trade_problem);
        data->events->write_i32(scenario.random_events.raise_wages);
        data->events->write_i32(scenario.random_events.lower_wages);
        data->events->write_i32(scenario.random_events.contaminated_water);
        data->events->write_i32(scenario.random_events.iron_mine_collapse);
        data->events->write_i32(scenario.random_events.clay_pit_flooded);
    }

    // fishing points
    if (data->fishing_points) {
        for (int i = 0; i < env_sizes().MAX_FISH_POINTS; i++)
            data->fishing_points->write_i16(scenario.fishing_points[i].x);
        for (int i = 0; i < env_sizes().MAX_FISH_POINTS; i++)
            data->fishing_points->write_i16(scenario.fishing_points[i].y);
    }

    // requests extra
    if (data->request_extra) {
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            data->request_extra->write_u8(scenario.requests[i].favor);
        for (int i = 0; i < env_sizes().MAX_INVASIONS; i++)
            data->request_extra->write_u8(scenario.invasions[i].month);
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            data->request_extra->write_u8(scenario.requests[i].month);
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            data->request_extra->write_u8(scenario.requests[i].state);
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            data->request_extra->write_u8(scenario.requests[i].visible);
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            data->request_extra->write_u8(scenario.requests[i].months_to_comply);
    }

    // rome wheat supplies enabled
    if (data->wheat)
        data->wheat->write_i32(scenario.rome_supplies_wheat);

    // allowed buildings
    if (data->allowed_builds)
        for (int i = 0; i < env_sizes().MAX_ALLOWED_BUILDINGS; i++)
            data->allowed_builds->write_i16(scenario.allowed_buildings[i]);

    // win criteria
    if (data->win_criteria) {
        data->win_criteria->write_i32(scenario.win_criteria.culture.goal);
        data->win_criteria->write_i32(scenario.win_criteria.prosperity.goal);
        data->win_criteria->write_i32(scenario.win_criteria.peace.goal);
        data->win_criteria->write_i32(scenario.win_criteria.favor.goal);
        if (GAME_ENV == ENGINE_ENV_PHARAOH) {
            data->win_criteria->write_i32(scenario.win_criteria.ph_goal1.goal);
            data->win_criteria->write_i32(scenario.win_criteria.ph_goal2.goal);
        }
        data->win_criteria->write_u8(scenario.win_criteria.culture.enabled);
        data->win_criteria->write_u8(scenario.win_criteria.prosperity.enabled);
        data->win_criteria->write_u8(scenario.win_criteria.peace.enabled);
        data->win_criteria->write_u8(scenario.win_criteria.favor.enabled);
        if (GAME_ENV == ENGINE_ENV_PHARAOH) {
            data->win_criteria->write_u8(scenario.win_criteria.ph_goal1.enabled);
            data->win_criteria->write_u8(scenario.win_criteria.ph_goal2.enabled);
        }
        data->win_criteria->write_i32(scenario.win_criteria.time_limit.enabled);
        data->win_criteria->write_i32(scenario.win_criteria.time_limit.years);
        data->win_criteria->write_i32(scenario.win_criteria.survival_time.enabled);
        data->win_criteria->write_i32(scenario.win_criteria.survival_time.years);
        data->win_criteria->write_i32(scenario.earthquake.severity);
        if (GAME_ENV == ENGINE_ENV_C3)
            data->win_criteria->write_i32(scenario.earthquake.year);
        else if (GAME_ENV == ENGINE_ENV_PHARAOH)
            data->win_criteria->write_i16(0);
        data->win_criteria->write_i32(scenario.win_criteria.population.enabled);
        data->win_criteria->write_i32(scenario.win_criteria.population.goal);
    }

    // map points
    if (data->map_points) {
        data->map_points->write_i16(scenario.earthquake_point.x);
        data->map_points->write_i16(scenario.earthquake_point.y);
        data->map_points->write_i16(scenario.entry_point.x);
        data->map_points->write_i16(scenario.entry_point.y);
        data->map_points->write_i16(scenario.exit_point.x);
        data->map_points->write_i16(scenario.exit_point.y);
    }

    // invasion points
    if (data->invasion_points) {
        for (int i = 0; i < env_sizes().MAX_INVASION_POINTS; i++)
            data->invasion_points->write_i16(scenario.invasion_points[i].x);
        for (int i = 0; i < env_sizes().MAX_INVASION_POINTS; i++)
            data->invasion_points->write_i16(scenario.invasion_points[i].y);
    }

    // river points
    if (data->river_points) {
        data->river_points->write_i16(scenario.river_entry_point.x);
        data->river_points->write_i16(scenario.river_entry_point.y);
        data->river_points->write_i16(scenario.river_exit_point.x);
        data->river_points->write_i16(scenario.river_exit_point.y);
    }

    // info 3
    if (data->info3) {
        data->info3->write_i32(scenario.rescue_loan);
        data->info3->write_i32(scenario.win_criteria.milestone25_year);
        data->info3->write_i32(scenario.win_criteria.milestone50_year);
        data->info3->write_i32(scenario.win_criteria.milestone75_year);
        data->info3->write_i32(scenario.native_images.hut);
        data->info3->write_i32(scenario.native_images.meeting);
        data->info3->write_i32(scenario.native_images.crops);
        data->info3->write_u8(scenario.climate);
        data->info3->write_u8(scenario.flotsam_enabled);
        data->info3->write_i16(0);
    }

    // empire
    if (data->empire) {
        data->empire->write_i32(scenario.empire.is_expanded);
        data->empire->write_i32(scenario.empire.expansion_year);
        data->empire->write_u8(scenario.empire.distant_battle_roman_travel_months);
        data->empire->write_u8(scenario.empire.distant_battle_enemy_travel_months);
        data->empire->write_u8(scenario.open_play_scenario_id);
        data->empire->write_u8(0);
    }

    scenario.is_saved = 1;
}
void scenario_load_state(scenario_data_buffers *data) {

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
    // 10. other request data
    // 11. wheat
    // 12. allowed buildings
    // 13. win criteria
    // 14. map points
    // 15. invasion entry points
    // 16. river entry points
    // 17. map info 3
    // 18. empire info

    // 1. header (14)
    if (data->header->is_valid(1)) {
        scenario.start_year = data->header->read_i16(); // 2 bytes
        data->header->skip(2);
        scenario.empire.id = data->header->read_i16(); // 2 bytes
        data->header->skip(8);
    }

    // 3. map info 1 (614)
    if (data->info1->is_valid(1)) { // (12)
        scenario.initial_funds = data->info1->read_i32(); // 4
        scenario.enemy_id = data->info1->read_i16(); // 2
        data->info1->skip(6);
        // (16)
        scenario.map.width = data->info1->read_i32(); // 4
        scenario.map.height = data->info1->read_i32(); // 4
        scenario.map.grid_start = data->info1->read_i32(); // 4
        scenario.map.grid_border_size = data->info1->read_i32(); // 4
        // (64 + 522 = 576)
        data->info1->read_raw(scenario.brief_description, env_sizes().MAX_BRIEF_DESCRIPTION);
        data->info1->read_raw(scenario.briefing, env_sizes().MAX_BRIEFING);
    }

    // 5. map info 2 (6)
    if (data->info2->is_valid(1)) {
        scenario.image_id = data->info2->read_i16(); // 2
        scenario.is_open_play = data->info2->read_i16(); // 2
        scenario.player_rank = data->info2->read_i16(); // 2
    }

    // 17. map info 3 (30 + 2)
    if (data->info3->is_valid(1)) {
        scenario.rescue_loan = data->info3->read_i32(); // 4
        scenario.win_criteria.milestone25_year = data->info3->read_i32(); // 4
        scenario.win_criteria.milestone50_year = data->info3->read_i32(); // 4
        scenario.win_criteria.milestone75_year = data->info3->read_i32(); // 4
        scenario.native_images.hut = data->info3->read_i32(); // 4
        scenario.native_images.meeting = data->info3->read_i32(); // 4
        scenario.native_images.crops = data->info3->read_i32(); // 4
        scenario.climate = data->info3->read_u8(); // 1
        scenario.flotsam_enabled = data->info3->read_u8(); // 1
        data->info3->skip(2);
    }

    // 8. random events (44)
    // events
    if (data->events->is_valid(1)) {
        scenario.gladiator_revolt.enabled = data->events->read_i32(); // 4
        scenario.gladiator_revolt.year = data->events->read_i32(); // 4
        scenario.emperor_change.enabled = data->events->read_i32(); // 4
        scenario.emperor_change.year = data->events->read_i32(); // 4
        scenario.random_events.sea_trade_problem = data->events->read_i32(); // 4
        scenario.random_events.land_trade_problem = data->events->read_i32(); // 4
        scenario.random_events.raise_wages = data->events->read_i32(); // 4
        scenario.random_events.lower_wages = data->events->read_i32(); // 4
        scenario.random_events.contaminated_water = data->events->read_i32(); // 4
        scenario.random_events.iron_mine_collapse = data->events->read_i32(); // 4
        scenario.random_events.clay_pit_flooded = data->events->read_i32(); // 4
    }

    // 13. win criteria (52 / 60)
    if (data->win_criteria->is_valid(1)) {
        scenario.win_criteria.culture.goal = data->win_criteria->read_i32(); // 4
        scenario.win_criteria.prosperity.goal = data->win_criteria->read_i32(); // 4
        scenario.win_criteria.peace.goal = data->win_criteria->read_i32(); // 4
        scenario.win_criteria.favor.goal = data->win_criteria->read_i32(); // 4
        if (GAME_ENV == ENGINE_ENV_PHARAOH) {
            scenario.win_criteria.ph_goal1.goal = data->win_criteria->read_i32(); // 4
            scenario.win_criteria.ph_goal2.goal = data->win_criteria->read_i32(); // 4
        }
        scenario.win_criteria.culture.enabled = data->win_criteria->read_u8(); // 1
        scenario.win_criteria.prosperity.enabled = data->win_criteria->read_u8(); // 1
        scenario.win_criteria.peace.enabled = data->win_criteria->read_u8(); // 1
        scenario.win_criteria.favor.enabled = data->win_criteria->read_u8(); // 1
        if (GAME_ENV == ENGINE_ENV_PHARAOH) {
            scenario.win_criteria.ph_goal1.enabled = data->win_criteria->read_u8(); // 1
            scenario.win_criteria.ph_goal2.enabled = data->win_criteria->read_u8(); // 1
        }
        scenario.win_criteria.time_limit.enabled = data->win_criteria->read_i32(); // 4
        scenario.win_criteria.time_limit.years = data->win_criteria->read_i32(); // 4
        scenario.win_criteria.survival_time.enabled = data->win_criteria->read_i32(); // 4
        scenario.win_criteria.survival_time.years = data->win_criteria->read_i32(); // 4
        scenario.earthquake.severity = data->win_criteria->read_i32(); // 4
        if (GAME_ENV == ENGINE_ENV_C3)
            scenario.earthquake.year = data->win_criteria->read_i32(); // 4
        else if (GAME_ENV == ENGINE_ENV_PHARAOH)
            data->win_criteria->skip(2); // 2
        scenario.win_criteria.population.enabled = data->win_criteria->read_i32(); // 4
        scenario.win_criteria.population.goal = data->win_criteria->read_i32(); // 4
    }

    // 14. map points (12)
    if (data->map_points->is_valid(1)) {
        scenario.earthquake_point.x = data->map_points->read_i16(); // 2
        scenario.earthquake_point.y = data->map_points->read_i16(); // 2
        scenario.entry_point.x = data->map_points->read_i16(); // 2
        scenario.entry_point.y = data->map_points->read_i16(); // 2
        scenario.exit_point.x = data->map_points->read_i16(); // 2
        scenario.exit_point.y = data->map_points->read_i16(); // 2
    }

    // 16. river entry points (8)
    if (data->map_points->is_valid(1)) {
        scenario.river_entry_point.x = data->river_points->read_i16(); // 2
        scenario.river_entry_point.y = data->river_points->read_i16(); // 2
        scenario.river_exit_point.x = data->river_points->read_i16(); // 2
        scenario.river_exit_point.y = data->river_points->read_i16(); // 2
    }

    // 18. empire (11 + 1)
    if (data->empire->is_valid(1)) {
        scenario.empire.is_expanded = data->empire->read_i32(); // 4
        scenario.empire.expansion_year = data->empire->read_i32(); // 4
        scenario.empire.distant_battle_roman_travel_months = data->empire->read_u8(); // 1
        scenario.empire.distant_battle_enemy_travel_months = data->empire->read_u8(); // 1
        scenario.open_play_scenario_id = data->empire->read_u8(); // 1
        data->empire->skip(1);
    }

    // 11. wheat??? (4)
    if (data->wheat->is_valid(1))
        scenario.rome_supplies_wheat = data->wheat->read_i32(); // 4

    // 2. requests (160)
    if (data->requests->is_valid(1)) {
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            scenario.requests[i].year = data->requests->read_i16(); // 40
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            scenario.requests[i].resource = data->requests->read_i16(); // 40
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            scenario.requests[i].amount = data->requests->read_i16(); // 40
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            scenario.requests[i].deadline_years = data->requests->read_i16(); // 40
    }
    // 2b. invasions (200 + 2)
    if (data->invasions->is_valid(1)) {
        for (int i = 0; i < env_sizes().MAX_INVASIONS; i++)
            scenario.invasions[i].year = data->invasions->read_i16(); // 40
        for (int i = 0; i < env_sizes().MAX_INVASIONS; i++)
            scenario.invasions[i].type = data->invasions->read_i16(); // 40
        for (int i = 0; i < env_sizes().MAX_INVASIONS; i++)
            scenario.invasions[i].amount = data->invasions->read_i16(); // 40
        for (int i = 0; i < env_sizes().MAX_INVASIONS; i++)
            scenario.invasions[i].from = data->invasions->read_i16(); // 40
        for (int i = 0; i < env_sizes().MAX_INVASIONS; i++)
            scenario.invasions[i].attack_type = data->invasions->read_i16(); // 40
        data->invasions->skip(2);
    }

    // 15. invasion entry points (32)
    if (data->invasion_points->is_valid(1)) {
        for (int i = 0; i < env_sizes().MAX_INVASION_POINTS; i++)
            scenario.invasion_points[i].x = data->invasion_points->read_i16(); // 2
        for (int i = 0; i < env_sizes().MAX_INVASION_POINTS; i++)
            scenario.invasion_points[i].y = data->invasion_points->read_i16(); // 2
    }

    // 4. request can-comply dialog (20)
    if (data->request_comply_dialogs->is_valid(1))
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            scenario.requests[i].can_comply_dialog_shown = data->request_comply_dialogs->read_u8(); // 1

    // 6. animal herds (16)
    if (data->herds->is_valid(1)) {
        for (int i = 0; i < env_sizes().MAX_HERD_POINTS; i++)
            scenario.herd_points[i].x = data->herds->read_i16(); // 2
        for (int i = 0; i < env_sizes().MAX_HERD_POINTS; i++)
            scenario.herd_points[i].y = data->herds->read_i16(); // 2
    }

    // 7. demands (240)
    // demand changes (120)
    if (data->demands->is_valid(1)) {
        for (int i = 0; i < env_sizes().MAX_DEMAND_CHANGES; i++)
            scenario.demand_changes[i].year = data->demands->read_i16(); // 2
        for (int i = 0; i < env_sizes().MAX_DEMAND_CHANGES; i++)
            scenario.demand_changes[i].month = data->demands->read_u8(); // 1
        for (int i = 0; i < env_sizes().MAX_DEMAND_CHANGES; i++)
            scenario.demand_changes[i].resource = data->demands->read_u8(); // 1
        for (int i = 0; i < env_sizes().MAX_DEMAND_CHANGES; i++)
            scenario.demand_changes[i].route_id = data->demands->read_u8(); // 1
        for (int i = 0; i < env_sizes().MAX_DEMAND_CHANGES; i++)
            scenario.demand_changes[i].is_rise = data->demands->read_u8(); // 1
    }
    // 7b. price changes (120)
    if (data->price_changes->is_valid(1)) {
        for (int i = 0; i < env_sizes().MAX_PRICE_CHANGES; i++)
            scenario.price_changes[i].year = data->price_changes->read_i16(); // 2
        for (int i = 0; i < env_sizes().MAX_PRICE_CHANGES; i++)
            scenario.price_changes[i].month = data->price_changes->read_u8(); // 1
        for (int i = 0; i < env_sizes().MAX_PRICE_CHANGES; i++)
            scenario.price_changes[i].resource = data->price_changes->read_u8(); // 1
        for (int i = 0; i < env_sizes().MAX_PRICE_CHANGES; i++)
            scenario.price_changes[i].amount = data->price_changes->read_u8(); // 1
        for (int i = 0; i < env_sizes().MAX_PRICE_CHANGES; i++)
            scenario.price_changes[i].is_rise = data->price_changes->read_u8(); // 1
    }

    // 9. fishing (32)
    if (data->fishing_points->is_valid(1)) {
        for (int i = 0; i < env_sizes().MAX_FISH_POINTS; i++)
            scenario.fishing_points[i].x = data->fishing_points->read_i16(); // 2
        for (int i = 0; i < env_sizes().MAX_FISH_POINTS; i++)
            scenario.fishing_points[i].y = data->fishing_points->read_i16(); // 2
    }

    // 10. other request data (120)
    if (data->request_extra->is_valid(1)) {
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            scenario.requests[i].favor = data->request_extra->read_u8(); // 1
        for (int i = 0; i < env_sizes().MAX_INVASIONS; i++)
            scenario.invasions[i].month = data->request_extra->read_u8(); // 1
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            scenario.requests[i].month = data->request_extra->read_u8(); // 1
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            scenario.requests[i].state = data->request_extra->read_u8(); // 1
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            scenario.requests[i].visible = data->request_extra->read_u8(); // 1
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            scenario.requests[i].months_to_comply = data->request_extra->read_u8(); // 1
    }
    // 12. allowed buildings (100 / 228)
    if (data->allowed_builds->is_valid(1))
        for (int i = 0; i < env_sizes().MAX_ALLOWED_BUILDINGS; i++)
            scenario.allowed_buildings[i] = data->allowed_builds->read_i16(); // 2

    scenario.is_saved = 1;
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

void
scenario_settings_save_state(buffer *part1, buffer *part2, buffer *part3, buffer *player_name, buffer *scenario_name) {
    switch (GAME_ENV) {
        case ENGINE_ENV_C3:
            part1->write_i32(scenario.settings.campaign_mission);
            break;
        case ENGINE_ENV_PHARAOH:
            part1->write_i8(scenario.settings.campaign_mission);
            break;
    }

    part2->write_i32(scenario.settings.starting_favor);
    part2->write_i32(scenario.settings.starting_personal_savings);
    part2->write_i32(scenario.settings.campaign_rank);

    part3->write_i32(scenario.settings.is_custom);

    for (int i = 0; i < env_sizes().MAX_PLAYER_NAME; i++) {
        player_name->write_u8(0);
    }
    player_name->write_raw(scenario.settings.player_name, env_sizes().MAX_PLAYER_NAME);
    scenario_name->write_raw(scenario.scenario_name, env_sizes().MAX_SCENARIO_NAME);
}
void
scenario_settings_load_state(buffer *part1, buffer *part2, buffer *part3, buffer *player_name, buffer *scenario_name) {
    switch (GAME_ENV) {
        case ENGINE_ENV_C3:
            scenario.settings.campaign_mission = part1->read_i32();
            break;
        case ENGINE_ENV_PHARAOH:
            scenario.settings.campaign_mission = part1->read_i8();
            break;
    }

    scenario.settings.starting_favor = part2->read_i32();
    scenario.settings.starting_personal_savings = part2->read_i32();
    scenario.settings.campaign_rank = part2->read_i32();

    scenario.settings.is_custom = part3->read_i32();

    player_name->skip(env_sizes().MAX_PLAYER_NAME);
    player_name->read_raw(scenario.settings.player_name, env_sizes().MAX_PLAYER_NAME);
    scenario_name->read_raw(scenario.scenario_name, env_sizes().MAX_SCENARIO_NAME);
}
