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

void scenario_save_state(scenario_data_buffers *buf) {
    // header
    if (buf->header) {
        buf->header->write_i16(scenario.start_year);
        buf->header->write_i16(0);
        buf->header->write_i16(scenario.empire.id);
        buf->header->skip(8);
    }

    // requests
    if (buf->requests) {
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            buf->requests->write_i16(scenario.requests[i].year);
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            buf->requests->write_i16(scenario.requests[i].resource);
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            buf->requests->write_i16(scenario.requests[i].amount);
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            buf->requests->write_i16(scenario.requests[i].deadline_years);
    }

    // invasions
    if (buf->invasions) {
        for (int i = 0; i < env_sizes().MAX_INVASIONS; i++)
            buf->invasions->write_i16(scenario.invasions[i].year);
        for (int i = 0; i < env_sizes().MAX_INVASIONS; i++)
            buf->invasions->write_i16(scenario.invasions[i].type);
        for (int i = 0; i < env_sizes().MAX_INVASIONS; i++)
            buf->invasions->write_i16(scenario.invasions[i].amount);
        for (int i = 0; i < env_sizes().MAX_INVASIONS; i++)
            buf->invasions->write_i16(scenario.invasions[i].from);
        for (int i = 0; i < env_sizes().MAX_INVASIONS; i++)
            buf->invasions->write_i16(scenario.invasions[i].attack_type);
    }
//    buf->invasions->write_i16(0);

    // info 1
    if (buf->info1) {
        buf->info1->write_i32(scenario.initial_funds);
        buf->info1->write_i16(scenario.enemy_id);
        buf->info1->write_i16(0);
        buf->info1->write_i16(0);
        buf->info1->write_i16(0);
        buf->info1->write_i32(scenario.map.width);
        buf->info1->write_i32(scenario.map.height);
        buf->info1->write_i32(scenario.map.grid_start);
        buf->info1->write_i32(scenario.map.grid_border_size);
        buf->info1->write_raw(scenario.brief_description, env_sizes().MAX_BRIEF_DESCRIPTION);
        buf->info1->write_raw(scenario.briefing, env_sizes().MAX_BRIEFING);
    }

    // request comply dialog
    if (buf->request_comply_dialogs)
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            buf->request_comply_dialogs->write_u8(scenario.requests[i].can_comply_dialog_shown);

    // info 2
    if (buf->info2) {
        buf->info2->write_i16(scenario.image_id);
        buf->info2->write_i16(scenario.is_open_play);
        buf->info2->write_i16(scenario.player_rank);
    }

    // herds
    if (buf->herds) {
        for (int i = 0; i < env_sizes().MAX_HERD_POINTS; i++)
            buf->herds->write_i16(scenario.herd_points[i].x);
        for (int i = 0; i < env_sizes().MAX_HERD_POINTS; i++)
            buf->herds->write_i16(scenario.herd_points[i].y);
    }

    // demand changes
    if (buf->demands) {
        for (int i = 0; i < env_sizes().MAX_DEMAND_CHANGES; i++)
            buf->demands->write_i16(scenario.demand_changes[i].year);
        for (int i = 0; i < env_sizes().MAX_DEMAND_CHANGES; i++)
            buf->demands->write_u8(scenario.demand_changes[i].month);
        for (int i = 0; i < env_sizes().MAX_DEMAND_CHANGES; i++)
            buf->demands->write_u8(scenario.demand_changes[i].resource);
        for (int i = 0; i < env_sizes().MAX_DEMAND_CHANGES; i++)
            buf->demands->write_u8(scenario.demand_changes[i].route_id);
        for (int i = 0; i < env_sizes().MAX_DEMAND_CHANGES; i++)
            buf->demands->write_u8(scenario.demand_changes[i].is_rise);
    }

    // price changes
    if (buf->price_changes) {
        for (int i = 0; i < env_sizes().MAX_PRICE_CHANGES; i++)
            buf->price_changes->write_i16(scenario.price_changes[i].year);
        for (int i = 0; i < env_sizes().MAX_PRICE_CHANGES; i++)
            buf->price_changes->write_u8(scenario.price_changes[i].month);
        for (int i = 0; i < env_sizes().MAX_PRICE_CHANGES; i++)
            buf->price_changes->write_u8(scenario.price_changes[i].resource);
        for (int i = 0; i < env_sizes().MAX_PRICE_CHANGES; i++)
            buf->price_changes->write_u8(scenario.price_changes[i].amount);
        for (int i = 0; i < env_sizes().MAX_PRICE_CHANGES; i++)
            buf->price_changes->write_u8(scenario.price_changes[i].is_rise);
    }

    // events
    if (buf->events) {
        buf->events->write_i32(scenario.gladiator_revolt.enabled);
        buf->events->write_i32(scenario.gladiator_revolt.year);
        buf->events->write_i32(scenario.emperor_change.enabled);
        buf->events->write_i32(scenario.emperor_change.year);
        buf->events->write_i32(scenario.random_events.sea_trade_problem);
        buf->events->write_i32(scenario.random_events.land_trade_problem);
        buf->events->write_i32(scenario.random_events.raise_wages);
        buf->events->write_i32(scenario.random_events.lower_wages);
        buf->events->write_i32(scenario.random_events.contaminated_water);
        buf->events->write_i32(scenario.random_events.iron_mine_collapse);
        buf->events->write_i32(scenario.random_events.clay_pit_flooded);
    }

    // fishing points
    if (buf->fishing_points) {
        for (int i = 0; i < env_sizes().MAX_FISH_POINTS; i++)
            buf->fishing_points->write_i16(scenario.fishing_points[i].x);
        for (int i = 0; i < env_sizes().MAX_FISH_POINTS; i++)
            buf->fishing_points->write_i16(scenario.fishing_points[i].y);
    }

    // requests extra
    if (buf->request_extra) {
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            buf->request_extra->write_u8(scenario.requests[i].favor);
        for (int i = 0; i < env_sizes().MAX_INVASIONS; i++)
            buf->request_extra->write_u8(scenario.invasions[i].month);
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            buf->request_extra->write_u8(scenario.requests[i].month);
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            buf->request_extra->write_u8(scenario.requests[i].state);
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            buf->request_extra->write_u8(scenario.requests[i].visible);
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            buf->request_extra->write_u8(scenario.requests[i].months_to_comply);
    }

    // rome wheat supplies enabled
    if (buf->wheat)
        buf->wheat->write_i32(scenario.rome_supplies_wheat);

    // allowed buildings
    if (buf->allowed_builds)
        for (int i = 0; i < env_sizes().MAX_ALLOWED_BUILDINGS; i++)
            buf->allowed_builds->write_i16(scenario.allowed_buildings[i]);

    // win criteria
    if (buf->win_criteria) {
        buf->win_criteria->write_i32(scenario.win_criteria.culture.goal);
        buf->win_criteria->write_i32(scenario.win_criteria.prosperity.goal);
        buf->win_criteria->write_i32(scenario.win_criteria.peace.goal);
        buf->win_criteria->write_i32(scenario.win_criteria.favor.goal);
        if (GAME_ENV == ENGINE_ENV_PHARAOH) {
            buf->win_criteria->write_i32(scenario.win_criteria.ph_goal1.goal);
            buf->win_criteria->write_i32(scenario.win_criteria.ph_goal2.goal);
        }
        buf->win_criteria->write_u8(scenario.win_criteria.culture.enabled);
        buf->win_criteria->write_u8(scenario.win_criteria.prosperity.enabled);
        buf->win_criteria->write_u8(scenario.win_criteria.peace.enabled);
        buf->win_criteria->write_u8(scenario.win_criteria.favor.enabled);
        if (GAME_ENV == ENGINE_ENV_PHARAOH) {
            buf->win_criteria->write_u8(scenario.win_criteria.ph_goal1.enabled);
            buf->win_criteria->write_u8(scenario.win_criteria.ph_goal2.enabled);
        }
        buf->win_criteria->write_i32(scenario.win_criteria.time_limit.enabled);
        buf->win_criteria->write_i32(scenario.win_criteria.time_limit.years);
        buf->win_criteria->write_i32(scenario.win_criteria.survival_time.enabled);
        buf->win_criteria->write_i32(scenario.win_criteria.survival_time.years);
        buf->win_criteria->write_i32(scenario.earthquake.severity);
        if (GAME_ENV == ENGINE_ENV_C3)
            buf->win_criteria->write_i32(scenario.earthquake.year);
        else if (GAME_ENV == ENGINE_ENV_PHARAOH)
            buf->win_criteria->write_i16(0);
        buf->win_criteria->write_i32(scenario.win_criteria.population.enabled);
        buf->win_criteria->write_i32(scenario.win_criteria.population.goal);
    }

    // map points
    if (buf->map_points) {
        buf->map_points->write_i16(scenario.earthquake_point.x);
        buf->map_points->write_i16(scenario.earthquake_point.y);
        buf->map_points->write_i16(scenario.entry_point.x);
        buf->map_points->write_i16(scenario.entry_point.y);
        buf->map_points->write_i16(scenario.exit_point.x);
        buf->map_points->write_i16(scenario.exit_point.y);
    }

    // invasion points
    if (buf->invasion_points) {
        for (int i = 0; i < env_sizes().MAX_INVASION_POINTS; i++)
            buf->invasion_points->write_i16(scenario.invasion_points[i].x);
        for (int i = 0; i < env_sizes().MAX_INVASION_POINTS; i++)
            buf->invasion_points->write_i16(scenario.invasion_points[i].y);
    }

    // river points
    if (buf->river_points) {
        buf->river_points->write_i16(scenario.river_entry_point.x);
        buf->river_points->write_i16(scenario.river_entry_point.y);
        buf->river_points->write_i16(scenario.river_exit_point.x);
        buf->river_points->write_i16(scenario.river_exit_point.y);
    }

    // info 3
    if (buf->info3) {
        buf->info3->write_i32(scenario.rescue_loan);
        buf->info3->write_i32(scenario.win_criteria.milestone25_year);
        buf->info3->write_i32(scenario.win_criteria.milestone50_year);
        buf->info3->write_i32(scenario.win_criteria.milestone75_year);
        buf->info3->write_i32(scenario.native_images.hut);
        buf->info3->write_i32(scenario.native_images.meeting);
        buf->info3->write_i32(scenario.native_images.crops);
        buf->info3->write_u8(scenario.climate);
        buf->info3->write_u8(scenario.flotsam_enabled);
        buf->info3->write_i16(0);
    }

    // empire
    if (buf->empire) {
        buf->empire->write_i32(scenario.empire.is_expanded);
        buf->empire->write_i32(scenario.empire.expansion_year);
        buf->empire->write_u8(scenario.empire.distant_battle_roman_travel_months);
        buf->empire->write_u8(scenario.empire.distant_battle_enemy_travel_months);
        buf->empire->write_u8(scenario.open_play_scenario_id);
        buf->empire->write_u8(0);
    }

    scenario.is_saved = 1;
}
void scenario_load_state(scenario_data_buffers *buf) {

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

    // 1. header (14)
    if (buf->header->is_valid(1)) {
        scenario.start_year = buf->header->read_i16(); // 2 bytes
        buf->header->skip(2);
        scenario.empire.id = buf->header->read_i16(); // 2 bytes
        buf->header->skip(8);
    }

    // 3. map info 1 (614)
    if (buf->info1->is_valid(1)) { // (12)
        scenario.initial_funds = buf->info1->read_i32(); // 4
        scenario.enemy_id = buf->info1->read_i16(); // 2
        buf->info1->skip(6);
        // (16)
        scenario.map.width = buf->info1->read_i32(); // 4
        scenario.map.height = buf->info1->read_i32(); // 4
        scenario.map.grid_start = buf->info1->read_i32(); // 4
        scenario.map.grid_border_size = buf->info1->read_i32(); // 4
        // (64 + 522 = 576)
        buf->info1->read_raw(scenario.brief_description, env_sizes().MAX_BRIEF_DESCRIPTION);
        buf->info1->read_raw(scenario.briefing, env_sizes().MAX_BRIEFING);
    }

    // 5. map info 2 (6)
    if (buf->info2->is_valid(1)) {
        scenario.image_id = buf->info2->read_i16(); // 2
        scenario.is_open_play = buf->info2->read_i16(); // 2
        scenario.player_rank = buf->info2->read_i16(); // 2
    }

    // 17. map info 3 (30 + 2)
    if (buf->info3->is_valid(1)) {
        scenario.rescue_loan = buf->info3->read_i32(); // 4
        scenario.win_criteria.milestone25_year = buf->info3->read_i32(); // 4
        scenario.win_criteria.milestone50_year = buf->info3->read_i32(); // 4
        scenario.win_criteria.milestone75_year = buf->info3->read_i32(); // 4
        scenario.native_images.hut = buf->info3->read_i32(); // 4
        scenario.native_images.meeting = buf->info3->read_i32(); // 4
        scenario.native_images.crops = buf->info3->read_i32(); // 4
        scenario.climate = buf->info3->read_u8(); // 1
        scenario.flotsam_enabled = buf->info3->read_u8(); // 1
        buf->info3->skip(2);
    }

    // 8. random events (44)
    // events
    if (buf->events->is_valid(1)) {
        scenario.gladiator_revolt.enabled = buf->events->read_i32(); // 4
        scenario.gladiator_revolt.year = buf->events->read_i32(); // 4
        scenario.emperor_change.enabled = buf->events->read_i32(); // 4
        scenario.emperor_change.year = buf->events->read_i32(); // 4
        scenario.random_events.sea_trade_problem = buf->events->read_i32(); // 4
        scenario.random_events.land_trade_problem = buf->events->read_i32(); // 4
        scenario.random_events.raise_wages = buf->events->read_i32(); // 4
        scenario.random_events.lower_wages = buf->events->read_i32(); // 4
        scenario.random_events.contaminated_water = buf->events->read_i32(); // 4
        scenario.random_events.iron_mine_collapse = buf->events->read_i32(); // 4
        scenario.random_events.clay_pit_flooded = buf->events->read_i32(); // 4
    }

    // 13. win criteria (52 / 60)
    if (buf->win_criteria->is_valid(1)) {
        scenario.win_criteria.culture.goal = buf->win_criteria->read_i32(); // 4
        scenario.win_criteria.prosperity.goal = buf->win_criteria->read_i32(); // 4
        scenario.win_criteria.peace.goal = buf->win_criteria->read_i32(); // 4
        scenario.win_criteria.favor.goal = buf->win_criteria->read_i32(); // 4
        if (GAME_ENV == ENGINE_ENV_PHARAOH) {
            scenario.win_criteria.ph_goal1.goal = buf->win_criteria->read_i32(); // 4
            scenario.win_criteria.ph_goal2.goal = buf->win_criteria->read_i32(); // 4
        }
        scenario.win_criteria.culture.enabled = buf->win_criteria->read_u8(); // 1
        scenario.win_criteria.prosperity.enabled = buf->win_criteria->read_u8(); // 1
        scenario.win_criteria.peace.enabled = buf->win_criteria->read_u8(); // 1
        scenario.win_criteria.favor.enabled = buf->win_criteria->read_u8(); // 1
        if (GAME_ENV == ENGINE_ENV_PHARAOH) {
            scenario.win_criteria.ph_goal1.enabled = buf->win_criteria->read_u8(); // 1
            scenario.win_criteria.ph_goal2.enabled = buf->win_criteria->read_u8(); // 1
        }
        scenario.win_criteria.time_limit.enabled = buf->win_criteria->read_i32(); // 4
        scenario.win_criteria.time_limit.years = buf->win_criteria->read_i32(); // 4
        scenario.win_criteria.survival_time.enabled = buf->win_criteria->read_i32(); // 4
        scenario.win_criteria.survival_time.years = buf->win_criteria->read_i32(); // 4
        scenario.earthquake.severity = buf->win_criteria->read_i32(); // 4
        if (GAME_ENV == ENGINE_ENV_C3)
            scenario.earthquake.year = buf->win_criteria->read_i32(); // 4
        else if (GAME_ENV == ENGINE_ENV_PHARAOH)
            buf->win_criteria->skip(2); // 2
        scenario.win_criteria.population.enabled = buf->win_criteria->read_i32(); // 4
        scenario.win_criteria.population.goal = buf->win_criteria->read_i32(); // 4
    }

    // 14. map points (12)
    if (buf->map_points->is_valid(1)) {
        scenario.earthquake_point.x = buf->map_points->read_i16(); // 2
        scenario.earthquake_point.y = buf->map_points->read_i16(); // 2
        scenario.entry_point.x = buf->map_points->read_i16(); // 2
        scenario.entry_point.y = buf->map_points->read_i16(); // 2
        scenario.exit_point.x = buf->map_points->read_i16(); // 2
        scenario.exit_point.y = buf->map_points->read_i16(); // 2
    }

    // 16. river entry points (8)
    if (buf->map_points->is_valid(1)) {
        scenario.river_entry_point.x = buf->river_points->read_i16(); // 2
        scenario.river_entry_point.y = buf->river_points->read_i16(); // 2
        scenario.river_exit_point.x = buf->river_points->read_i16(); // 2
        scenario.river_exit_point.y = buf->river_points->read_i16(); // 2
    }

    // 18. empire (11 + 1)
    if (buf->empire->is_valid(1)) {
        scenario.empire.is_expanded = buf->empire->read_i32(); // 4
        scenario.empire.expansion_year = buf->empire->read_i32(); // 4
        scenario.empire.distant_battle_roman_travel_months = buf->empire->read_u8(); // 1
        scenario.empire.distant_battle_enemy_travel_months = buf->empire->read_u8(); // 1
        scenario.open_play_scenario_id = buf->empire->read_u8(); // 1
        buf->empire->skip(1);
    }

    // 11. wheat??? (4)
    if (buf->wheat->is_valid(1))
        scenario.rome_supplies_wheat = buf->wheat->read_i32(); // 4

    // 2. requests (160)
    if (buf->requests->is_valid(1)) {
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            scenario.requests[i].year = buf->requests->read_i16(); // 40
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            scenario.requests[i].resource = buf->requests->read_i16(); // 40
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            scenario.requests[i].amount = buf->requests->read_i16(); // 40
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            scenario.requests[i].deadline_years = buf->requests->read_i16(); // 40
    }
    // 2b. invasions (200 + 2)
    if (buf->invasions->is_valid(1)) {
        for (int i = 0; i < env_sizes().MAX_INVASIONS; i++)
            scenario.invasions[i].year = buf->invasions->read_i16(); // 40
        for (int i = 0; i < env_sizes().MAX_INVASIONS; i++)
            scenario.invasions[i].type = buf->invasions->read_i16(); // 40
        for (int i = 0; i < env_sizes().MAX_INVASIONS; i++)
            scenario.invasions[i].amount = buf->invasions->read_i16(); // 40
        for (int i = 0; i < env_sizes().MAX_INVASIONS; i++)
            scenario.invasions[i].from = buf->invasions->read_i16(); // 40
        for (int i = 0; i < env_sizes().MAX_INVASIONS; i++)
            scenario.invasions[i].attack_type = buf->invasions->read_i16(); // 40
        buf->invasions->skip(2);
    }

    // 15. invasion entry points (32)
    if (buf->invasion_points->is_valid(1)) {
        for (int i = 0; i < env_sizes().MAX_INVASION_POINTS; i++)
            scenario.invasion_points[i].x = buf->invasion_points->read_i16(); // 2
        for (int i = 0; i < env_sizes().MAX_INVASION_POINTS; i++)
            scenario.invasion_points[i].y = buf->invasion_points->read_i16(); // 2
    }

    // 4. request can-comply dialog (20)
    if (buf->request_comply_dialogs->is_valid(1))
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            scenario.requests[i].can_comply_dialog_shown = buf->request_comply_dialogs->read_u8(); // 1

    // 6. animal herds (16 : 32)
    if (buf->herds->is_valid(1)) {
        if (GAME_ENV == ENGINE_ENV_C3) {
            for (int i = 0; i < env_sizes().MAX_HERD_POINTS; i++)
                scenario.herd_points[i].x = buf->herds->read_i16(); // 2
            for (int i = 0; i < env_sizes().MAX_HERD_POINTS; i++)
                scenario.herd_points[i].y = buf->herds->read_i16(); // 2
        } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
            for (int i = 0; i < env_sizes().MAX_HERD_POINTS; i++)
                scenario.herd_points[i].x = buf->herds->read_i32(); // 4
            for (int i = 0; i < env_sizes().MAX_HERD_POINTS; i++)
                scenario.herd_points[i].y = buf->herds->read_i32(); // 4
        }
    }

    // 7. demands (240)
    // demand changes (120)
    if (buf->demands->is_valid(1)) {
        for (int i = 0; i < env_sizes().MAX_DEMAND_CHANGES; i++)
            scenario.demand_changes[i].year = buf->demands->read_i16(); // 2
        for (int i = 0; i < env_sizes().MAX_DEMAND_CHANGES; i++)
            scenario.demand_changes[i].month = buf->demands->read_u8(); // 1
        for (int i = 0; i < env_sizes().MAX_DEMAND_CHANGES; i++)
            scenario.demand_changes[i].resource = buf->demands->read_u8(); // 1
        for (int i = 0; i < env_sizes().MAX_DEMAND_CHANGES; i++)
            scenario.demand_changes[i].route_id = buf->demands->read_u8(); // 1
        for (int i = 0; i < env_sizes().MAX_DEMAND_CHANGES; i++)
            scenario.demand_changes[i].is_rise = buf->demands->read_u8(); // 1
    }
    // 7b. price changes (120)
    if (buf->price_changes->is_valid(1)) {
        for (int i = 0; i < env_sizes().MAX_PRICE_CHANGES; i++)
            scenario.price_changes[i].year = buf->price_changes->read_i16(); // 2
        for (int i = 0; i < env_sizes().MAX_PRICE_CHANGES; i++)
            scenario.price_changes[i].month = buf->price_changes->read_u8(); // 1
        for (int i = 0; i < env_sizes().MAX_PRICE_CHANGES; i++)
            scenario.price_changes[i].resource = buf->price_changes->read_u8(); // 1
        for (int i = 0; i < env_sizes().MAX_PRICE_CHANGES; i++)
            scenario.price_changes[i].amount = buf->price_changes->read_u8(); // 1
        for (int i = 0; i < env_sizes().MAX_PRICE_CHANGES; i++)
            scenario.price_changes[i].is_rise = buf->price_changes->read_u8(); // 1
    }

    // 9. fishing (32)
    if (buf->fishing_points->is_valid(1)) {
        for (int i = 0; i < env_sizes().MAX_FISH_POINTS; i++)
            scenario.fishing_points[i].x = buf->fishing_points->read_i16(); // 2
        for (int i = 0; i < env_sizes().MAX_FISH_POINTS; i++)
            scenario.fishing_points[i].y = buf->fishing_points->read_i16(); // 2
    }

    // 10. other request buf (120)
    if (buf->request_extra->is_valid(1)) {
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            scenario.requests[i].favor = buf->request_extra->read_u8(); // 1
        for (int i = 0; i < env_sizes().MAX_INVASIONS; i++)
            scenario.invasions[i].month = buf->request_extra->read_u8(); // 1
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            scenario.requests[i].month = buf->request_extra->read_u8(); // 1
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            scenario.requests[i].state = buf->request_extra->read_u8(); // 1
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            scenario.requests[i].visible = buf->request_extra->read_u8(); // 1
        for (int i = 0; i < env_sizes().MAX_REQUESTS; i++)
            scenario.requests[i].months_to_comply = buf->request_extra->read_u8(); // 1
    }
    // 12. allowed buildings (100 / 228)
    if (buf->allowed_builds->is_valid(1))
        for (int i = 0; i < env_sizes().MAX_ALLOWED_BUILDINGS; i++)
            scenario.allowed_buildings[i] = buf->allowed_builds->read_i16(); // 2

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

void scenario_settings_save_state(buffer *part1, buffer *part2, buffer *part3, buffer *player_name, buffer *scenario_name) {
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

    for (int i = 0; i < env_sizes().MAX_PLAYER_NAME; i++)
        player_name->write_u8(0);
    player_name->write_raw(scenario.settings.player_name, env_sizes().MAX_PLAYER_NAME);
    scenario_name->write_raw(scenario.scenario_name, env_sizes().MAX_SCENARIO_NAME);
}
void scenario_settings_load_state(buffer *part1, buffer *part2, buffer *part3, buffer *player_name, buffer *scenario_name) {
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
