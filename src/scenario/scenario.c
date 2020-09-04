#include "scenario.h"

#include "city/resource.h"
#include "empire/trade_route.h"
#include "game/difficulty.h"
#include "game/settings.h"
#include "scenario/data.h"
#include "core/game_environment.h"

struct scenario_t scenario;

int scenario_is_saved(void) {
    return scenario.is_saved;
}

void scenario_save_state(buffer *buf) {
    buffer_write_i16(buf, scenario.start_year);
    buffer_write_i16(buf, 0);
    buffer_write_i16(buf, scenario.empire.id);
    buffer_skip(buf, 8);

    // requests
    for (int i = 0; i < MAX_REQUESTS; i++) {
        buffer_write_i16(buf, scenario.requests[i].year);
    }
    for (int i = 0; i < MAX_REQUESTS; i++) {
        buffer_write_i16(buf, scenario.requests[i].resource);
    }
    for (int i = 0; i < MAX_REQUESTS; i++) {
        buffer_write_i16(buf, scenario.requests[i].amount);
    }
    for (int i = 0; i < MAX_REQUESTS; i++) {
        buffer_write_i16(buf, scenario.requests[i].deadline_years);
    }

    // invasions
    for (int i = 0; i < MAX_INVASIONS; i++) {
        buffer_write_i16(buf, scenario.invasions[i].year);
    }
    for (int i = 0; i < MAX_INVASIONS; i++) {
        buffer_write_i16(buf, scenario.invasions[i].type);
    }
    for (int i = 0; i < MAX_INVASIONS; i++) {
        buffer_write_i16(buf, scenario.invasions[i].amount);
    }
    for (int i = 0; i < MAX_INVASIONS; i++) {
        buffer_write_i16(buf, scenario.invasions[i].from);
    }
    for (int i = 0; i < MAX_INVASIONS; i++) {
        buffer_write_i16(buf, scenario.invasions[i].attack_type);
    }

    buffer_write_i16(buf, 0);
    buffer_write_i32(buf, scenario.initial_funds);
    buffer_write_i16(buf, scenario.enemy_id);
    buffer_write_i16(buf, 0);
    buffer_write_i16(buf, 0);
    buffer_write_i16(buf, 0);

    buffer_write_i32(buf, scenario.map.width);
    buffer_write_i32(buf, scenario.map.height);
    buffer_write_i32(buf, scenario.map.grid_start);
    buffer_write_i32(buf, scenario.map.grid_border_size);

    buffer_write_raw(buf, scenario.brief_description, MAX_BRIEF_DESCRIPTION);
    buffer_write_raw(buf, scenario.briefing, MAX_BRIEFING);

    for (int i = 0; i < MAX_REQUESTS; i++) {
        buffer_write_u8(buf, scenario.requests[i].can_comply_dialog_shown);
    }

    buffer_write_i16(buf, scenario.image_id);
    buffer_write_i16(buf, scenario.is_open_play);
    buffer_write_i16(buf, scenario.player_rank);

    for (int i = 0; i < MAX_HERD_POINTS; i++) {
        buffer_write_i16(buf, scenario.herd_points[i].x);
    }
    for (int i = 0; i < MAX_HERD_POINTS; i++) {
        buffer_write_i16(buf, scenario.herd_points[i].y);
    }

    // demand changes
    for (int i = 0; i < MAX_DEMAND_CHANGES; i++) {
        buffer_write_i16(buf, scenario.demand_changes[i].year);
    }
    for (int i = 0; i < MAX_DEMAND_CHANGES; i++) {
        buffer_write_u8(buf, scenario.demand_changes[i].month);
    }
    for (int i = 0; i < MAX_DEMAND_CHANGES; i++) {
        buffer_write_u8(buf, scenario.demand_changes[i].resource);
    }
    for (int i = 0; i < MAX_DEMAND_CHANGES; i++) {
        buffer_write_u8(buf, scenario.demand_changes[i].route_id);
    }
    for (int i = 0; i < MAX_DEMAND_CHANGES; i++) {
        buffer_write_u8(buf, scenario.demand_changes[i].is_rise);
    }

    // price changes
    for (int i = 0; i < MAX_PRICE_CHANGES; i++) {
        buffer_write_i16(buf, scenario.price_changes[i].year);
    }
    for (int i = 0; i < MAX_PRICE_CHANGES; i++) {
        buffer_write_u8(buf, scenario.price_changes[i].month);
    }
    for (int i = 0; i < MAX_PRICE_CHANGES; i++) {
        buffer_write_u8(buf, scenario.price_changes[i].resource);
    }
    for (int i = 0; i < MAX_PRICE_CHANGES; i++) {
        buffer_write_u8(buf, scenario.price_changes[i].amount);
    }
    for (int i = 0; i < MAX_PRICE_CHANGES; i++) {
        buffer_write_u8(buf, scenario.price_changes[i].is_rise);
    }

    buffer_write_i32(buf, scenario.gladiator_revolt.enabled);
    buffer_write_i32(buf, scenario.gladiator_revolt.year);
    buffer_write_i32(buf, scenario.emperor_change.enabled);
    buffer_write_i32(buf, scenario.emperor_change.year);

    // random events
    buffer_write_i32(buf, scenario.random_events.sea_trade_problem);
    buffer_write_i32(buf, scenario.random_events.land_trade_problem);
    buffer_write_i32(buf, scenario.random_events.raise_wages);
    buffer_write_i32(buf, scenario.random_events.lower_wages);
    buffer_write_i32(buf, scenario.random_events.contaminated_water);
    buffer_write_i32(buf, scenario.random_events.iron_mine_collapse);
    buffer_write_i32(buf, scenario.random_events.clay_pit_flooded);

    for (int i = 0; i < MAX_FISH_POINTS; i++) {
        buffer_write_i16(buf, scenario.fishing_points[i].x);
    }
    for (int i = 0; i < MAX_FISH_POINTS; i++) {
        buffer_write_i16(buf, scenario.fishing_points[i].y);
    }

    for (int i = 0; i < MAX_REQUESTS; i++) {
        buffer_write_u8(buf, scenario.requests[i].favor);
    }
    for (int i = 0; i < MAX_INVASIONS; i++) {
        buffer_write_u8(buf, scenario.invasions[i].month);
    }
    for (int i = 0; i < MAX_REQUESTS; i++) {
        buffer_write_u8(buf, scenario.requests[i].month);
    }
    for (int i = 0; i < MAX_REQUESTS; i++) {
        buffer_write_u8(buf, scenario.requests[i].state);
    }
    for (int i = 0; i < MAX_REQUESTS; i++) {
        buffer_write_u8(buf, scenario.requests[i].visible);
    }
    for (int i = 0; i < MAX_REQUESTS; i++) {
        buffer_write_u8(buf, scenario.requests[i].months_to_comply);
    }

    buffer_write_i32(buf, scenario.rome_supplies_wheat);

    // allowed buildings
    int MAX_ALLOWED_BUILDINGS = 50;
    if (GAME_ENV == ENGINE_ENV_PHARAOH)
        MAX_ALLOWED_BUILDINGS = 114;
    for (int i = 0; i < MAX_ALLOWED_BUILDINGS; i++) {
        buffer_write_i16(buf, scenario.allowed_buildings[i]);
    }

    // win criteria
    buffer_write_i32(buf, scenario.win_criteria.culture.goal);
    buffer_write_i32(buf, scenario.win_criteria.prosperity.goal);
    buffer_write_i32(buf, scenario.win_criteria.peace.goal);
    buffer_write_i32(buf, scenario.win_criteria.favor.goal);
    buffer_write_u8(buf, scenario.win_criteria.culture.enabled);
    buffer_write_u8(buf, scenario.win_criteria.prosperity.enabled);
    buffer_write_u8(buf, scenario.win_criteria.peace.enabled);
    buffer_write_u8(buf, scenario.win_criteria.favor.enabled);
    buffer_write_i32(buf, scenario.win_criteria.time_limit.enabled);
    buffer_write_i32(buf, scenario.win_criteria.time_limit.years);
    buffer_write_i32(buf, scenario.win_criteria.survival_time.enabled);
    buffer_write_i32(buf, scenario.win_criteria.survival_time.years);

    buffer_write_i32(buf, scenario.earthquake.severity);
    buffer_write_i32(buf, scenario.earthquake.year);

    buffer_write_i32(buf, scenario.win_criteria.population.enabled);
    buffer_write_i32(buf, scenario.win_criteria.population.goal);

    // map points
    buffer_write_i16(buf, scenario.earthquake_point.x);
    buffer_write_i16(buf, scenario.earthquake_point.y);
    buffer_write_i16(buf, scenario.entry_point.x);
    buffer_write_i16(buf, scenario.entry_point.y);
    buffer_write_i16(buf, scenario.exit_point.x);
    buffer_write_i16(buf, scenario.exit_point.y);

    for (int i = 0; i < MAX_INVASION_POINTS; i++) {
        buffer_write_i16(buf, scenario.invasion_points[i].x);
    }
    for (int i = 0; i < MAX_INVASION_POINTS; i++) {
        buffer_write_i16(buf, scenario.invasion_points[i].y);
    }

    buffer_write_i16(buf, scenario.river_entry_point.x);
    buffer_write_i16(buf, scenario.river_entry_point.y);
    buffer_write_i16(buf, scenario.river_exit_point.x);
    buffer_write_i16(buf, scenario.river_exit_point.y);

    buffer_write_i32(buf, scenario.rescue_loan);
    buffer_write_i32(buf, scenario.win_criteria.milestone25_year);
    buffer_write_i32(buf, scenario.win_criteria.milestone50_year);
    buffer_write_i32(buf, scenario.win_criteria.milestone75_year);

    buffer_write_i32(buf, scenario.native_images.hut);
    buffer_write_i32(buf, scenario.native_images.meeting);
    buffer_write_i32(buf, scenario.native_images.crops);

    buffer_write_u8(buf, scenario.climate);
    buffer_write_u8(buf, scenario.flotsam_enabled);

    buffer_write_i16(buf, 0);

    buffer_write_i32(buf, scenario.empire.is_expanded);
    buffer_write_i32(buf, scenario.empire.expansion_year);

    buffer_write_u8(buf, scenario.empire.distant_battle_roman_travel_months);
    buffer_write_u8(buf, scenario.empire.distant_battle_enemy_travel_months);
    buffer_write_u8(buf, scenario.open_play_scenario_id);
    buffer_write_u8(buf, 0);

    scenario.is_saved = 1;
}
void scenario_load_state(buffer *buf) {

    // header (14)
    scenario.start_year = buffer_read_i16(buf); // 2 bytes
    buffer_skip(buf, 2);
    scenario.empire.id = buffer_read_i16(buf); // 2 bytes
    buffer_skip(buf, 8);

    // requests (160)
    for (int i = 0; i < MAX_REQUESTS; i++)
        scenario.requests[i].year = buffer_read_i16(buf); // 40
    for (int i = 0; i < MAX_REQUESTS; i++)
        scenario.requests[i].resource = buffer_read_i16(buf); // 40
    for (int i = 0; i < MAX_REQUESTS; i++)
        scenario.requests[i].amount = buffer_read_i16(buf); // 40
    for (int i = 0; i < MAX_REQUESTS; i++)
        scenario.requests[i].deadline_years = buffer_read_i16(buf); // 40
    // invasions (200 + 2)
    for (int i = 0; i < MAX_INVASIONS; i++)
        scenario.invasions[i].year = buffer_read_i16(buf); // 40
    for (int i = 0; i < MAX_INVASIONS; i++)
        scenario.invasions[i].type = buffer_read_i16(buf); // 40
    for (int i = 0; i < MAX_INVASIONS; i++)
        scenario.invasions[i].amount = buffer_read_i16(buf); // 40
    for (int i = 0; i < MAX_INVASIONS; i++)
        scenario.invasions[i].from = buffer_read_i16(buf); // 40
    for (int i = 0; i < MAX_INVASIONS; i++)
        scenario.invasions[i].attack_type = buffer_read_i16(buf); // 40
    buffer_skip(buf, 2);

    // map info (614)
    // (12)
    scenario.initial_funds = buffer_read_i32(buf); // 4
    scenario.enemy_id = buffer_read_i16(buf); // 2
    buffer_skip(buf, 6);
    // (16)
    scenario.map.width = buffer_read_i32(buf); // 4
    scenario.map.height = buffer_read_i32(buf); // 4
    scenario.map.grid_start = buffer_read_i32(buf); // 4
    scenario.map.grid_border_size = buffer_read_i32(buf); // 4
    // (64 + 522 = 586)
    buffer_read_raw(buf, scenario.brief_description, MAX_BRIEF_DESCRIPTION);
    buffer_read_raw(buf, scenario.briefing, MAX_BRIEFING);

    // request can-comply dialog (20)
    for (int i = 0; i < MAX_REQUESTS; i++)
        scenario.requests[i].can_comply_dialog_shown = buffer_read_u8(buf); // 1

    // map info 2 (6)
    scenario.image_id = buffer_read_i16(buf); // 2
    scenario.is_open_play = buffer_read_i16(buf); // 2
    scenario.player_rank = buffer_read_i16(buf); // 2

    // data 3 (256)
    // animal herds (16)
    for (int i = 0; i < MAX_HERD_POINTS; i++) //                                                09 00 3C 00 00 00 00 00 35 00 1A 00 00
        scenario.herd_points[i].x = buffer_read_i16(buf); // 2                         00 00 00
    for (int i = 0; i < MAX_HERD_POINTS; i++) //
        scenario.herd_points[i].y = buffer_read_i16(buf); // 2
    // demand changes (120)
    for (int i = 0; i < MAX_DEMAND_CHANGES; i++) //                                             00 00 00 00 00 00 00 00 00 00 00 00 00
        scenario.demand_changes[i].year = buffer_read_i16(buf); // 2                   00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    for (int i = 0; i < MAX_DEMAND_CHANGES; i++) //                                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
        scenario.demand_changes[i].month = buffer_read_u8(buf); // 1                   00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    for (int i = 0; i < MAX_DEMAND_CHANGES; i++) //                                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
        scenario.demand_changes[i].resource = buffer_read_u8(buf); // 1                00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    for (int i = 0; i < MAX_DEMAND_CHANGES; i++) //                                    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
        scenario.demand_changes[i].route_id = buffer_read_u8(buf); // 1                00 00 00 00 00 00 00 00 00 00 00
    for (int i = 0; i < MAX_DEMAND_CHANGES; i++)
        scenario.demand_changes[i].is_rise = buffer_read_u8(buf); // 1
    // price changes (120)
    for (int i = 0; i < MAX_PRICE_CHANGES; i++) //                                                                      05 00 08 00 0F
        scenario.price_changes[i].year = buffer_read_i16(buf); // 2                    00 14 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    for (int i = 0; i < MAX_PRICE_CHANGES; i++) //                                     00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
        scenario.price_changes[i].month = buffer_read_u8(buf); // 1                    00 00 00 07 06 04 02 00 00 00 00 00 00 00 00 00
    for (int i = 0; i < MAX_PRICE_CHANGES; i++) //                                     00 00 00 00 00 00 00 03 0C 0E 0F 00 00 00 00 00
        scenario.price_changes[i].resource = buffer_read_u8(buf); // 1                 00 00 00 00 00 00 00 00 00 00 00 14 14 14 0F 00
    for (int i = 0; i < MAX_PRICE_CHANGES; i++) //                                     00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01
        scenario.price_changes[i].amount = buffer_read_u8(buf); // 1                   01 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    for (int i = 0; i < MAX_PRICE_CHANGES; i++) //                                     00 00 00
        scenario.price_changes[i].is_rise = buffer_read_u8(buf); // 1

    // info 4 (44)
    // events
    scenario.gladiator_revolt.enabled = buffer_read_i32(buf); // 4                              00 00 00 00 00 00 00 00 00 00 00 00 00
    scenario.gladiator_revolt.year = buffer_read_i32(buf); // 4                        00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    scenario.emperor_change.enabled = buffer_read_i32(buf); // 4                       00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    scenario.emperor_change.year = buffer_read_i32(buf); // 4
    scenario.random_events.sea_trade_problem = buffer_read_i32(buf); // 4
    scenario.random_events.land_trade_problem = buffer_read_i32(buf); // 4
    scenario.random_events.raise_wages = buffer_read_i32(buf); // 4
    scenario.random_events.lower_wages = buffer_read_i32(buf); // 4
    scenario.random_events.contaminated_water = buffer_read_i32(buf); // 4
    scenario.random_events.iron_mine_collapse = buffer_read_i32(buf); // 4
    scenario.random_events.clay_pit_flooded = buffer_read_i32(buf); // 4

    // fishing (32)
    for (int i = 0; i < MAX_FISH_POINTS; i++) //                                                                                    00
        scenario.fishing_points[i].x = buffer_read_i16(buf); // 2                      00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    for (int i = 0; i < MAX_FISH_POINTS; i++) //                                       00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
        scenario.fishing_points[i].y = buffer_read_i16(buf); // 2
    // other request data (120)
    for (int i = 0; i < MAX_REQUESTS; i++) //                                                                                       08
        scenario.requests[i].favor = buffer_read_u8(buf); // 1                         08 0A 0A 0A 0A 0A 0A 0A 0A 00 00 00 00 00 00 00
    for (int i = 0; i < MAX_INVASIONS; i++) //                                         00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
        scenario.invasions[i].month = buffer_read_u8(buf); // 1                        00 00 00 00 00 00 00 03 08 02 04 08 02 04 05 08
    for (int i = 0; i < MAX_REQUESTS; i++) //                                          08 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
        scenario.requests[i].month = buffer_read_u8(buf); // 1                         00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    for (int i = 0; i < MAX_REQUESTS; i++) //                                          00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
        scenario.requests[i].state = buffer_read_u8(buf); // 1                         00 00 00 18 18 18 18 18 18 18 18 18 18 00 00 00
    for (int i = 0; i < MAX_REQUESTS; i++) //                                          00 00 00 00 00 00 00
        scenario.requests[i].visible = buffer_read_u8(buf); // 1
    for (int i = 0; i < MAX_REQUESTS; i++)
        scenario.requests[i].months_to_comply = buffer_read_u8(buf); // 1

    // wheat??? (4)
    scenario.rome_supplies_wheat = buffer_read_i32(buf); // 4                                               00 00 00 00

    // allowed buildings (100 / 228)
    int MAX_ALLOWED_BUILDINGS = 50;
    if (GAME_ENV == ENGINE_ENV_PHARAOH)
        MAX_ALLOWED_BUILDINGS = 114;
    for (int i = 0; i < MAX_ALLOWED_BUILDINGS; i++) //                                                                  01 00 01 00 01
        scenario.allowed_buildings[i] = buffer_read_i16(buf); // 2                     00 01 00 01 00 00 00 01 00 01 00 01 00 01 00 00
                                                    //                                 00 01 00 01 00 01 00 01 00 00 00 01 00 01 00 01
                                                    //                                 00 01 00 01 00 01 00 01 00 01 00 01 00 01 00 01
                                                    //                                 00 00 00 00 00 00 00 01 00 01 00 01 00 01 00 01
                                                    //                                 00 00 00 01 00 00 00 01 00 01 00 01 00 01 00 01
                                                    //                                 00 01 00 00 00 01 00 00 00 00 00 01 00 01 00

    // win criteria (52 / 60)
    scenario.win_criteria.culture.goal = buffer_read_i32(buf); // 4                                                                 2D
    scenario.win_criteria.prosperity.goal = buffer_read_i32(buf); // 4                 00 00 00 19 00 00 00 1E 00 00 00 46 00 00 00 01
    scenario.win_criteria.peace.goal = buffer_read_i32(buf); // 4                      01 01 01 00 00 00 00 00 00 00 00 00 00 00 00 00
    scenario.win_criteria.favor.goal = buffer_read_i32(buf); // 4                      00 00 00 03 00 00 00 02 00 00 00 01 00 00 00 C4
    if (GAME_ENV == ENGINE_ENV_PHARAOH) { //                                           09 00 00
        scenario.win_criteria.ph_goal1.goal = buffer_read_i32(buf); // 4
        scenario.win_criteria.ph_goal2.goal = buffer_read_i32(buf); // 4
    }
    scenario.win_criteria.culture.enabled = buffer_read_u8(buf); // 1
    scenario.win_criteria.prosperity.enabled = buffer_read_u8(buf); // 1
    scenario.win_criteria.peace.enabled = buffer_read_u8(buf); // 1
    scenario.win_criteria.favor.enabled = buffer_read_u8(buf); // 1
    if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        scenario.win_criteria.ph_goal1.enabled = buffer_read_u8(buf); // 1
        scenario.win_criteria.ph_goal2.enabled = buffer_read_u8(buf); // 1
    }
    scenario.win_criteria.time_limit.enabled = buffer_read_i32(buf); // 4
    scenario.win_criteria.time_limit.years = buffer_read_i32(buf); // 4
    scenario.win_criteria.survival_time.enabled = buffer_read_i32(buf); // 4
    scenario.win_criteria.survival_time.years = buffer_read_i32(buf); // 4
    scenario.earthquake.severity = buffer_read_i32(buf); // 4
    if (GAME_ENV == ENGINE_ENV_C3) {
        scenario.earthquake.year = buffer_read_i32(buf); // 4
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH)
        buffer_skip(buf, 2); // 2
    scenario.win_criteria.population.enabled = buffer_read_i32(buf); // 4
    scenario.win_criteria.population.goal = buffer_read_i32(buf); // 4





    // map points (12)
    scenario.earthquake_point.x = buffer_read_i16(buf); // 2                                    20 00 09 00 00 00 1C 00 4F 00 29 00
    scenario.earthquake_point.y = buffer_read_i16(buf); // 2
    scenario.entry_point.x = buffer_read_i16(buf); // 2
    scenario.entry_point.y = buffer_read_i16(buf); // 2
    scenario.exit_point.x = buffer_read_i16(buf); // 2
    scenario.exit_point.y = buffer_read_i16(buf); // 2

    // data 5 (32)
    for (int i = 0; i < MAX_INVASION_POINTS; i++) //                                                                                FF
        scenario.invasion_points[i].x = buffer_read_i16(buf); // 2                     FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF
    for (int i = 0; i < MAX_INVASION_POINTS; i++) //                                   FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF
        scenario.invasion_points[i].y = buffer_read_i16(buf); // 2

    // info 6 (56)
    // (8)
    scenario.river_entry_point.x = buffer_read_i16(buf); // 2                                                                       00
    scenario.river_entry_point.y = buffer_read_i16(buf); // 2                          00 20 00 00 00 38 00
    scenario.river_exit_point.x = buffer_read_i16(buf); // 2
    scenario.river_exit_point.y = buffer_read_i16(buf); // 2
    // (32 + 2)
    scenario.rescue_loan = buffer_read_i32(buf); // 4                                                       70 17 00 00 0A 00 00 00 14
    scenario.win_criteria.milestone25_year = buffer_read_i32(buf); // 4                00 00 00 1E 00 00 00 0B 0B 00 00 0D 0B 00 00 44
    scenario.win_criteria.milestone50_year = buffer_read_i32(buf); // 4                0B 00 00 00 01 00 00
    scenario.win_criteria.milestone75_year = buffer_read_i32(buf); // 4
    scenario.native_images.hut = buffer_read_i32(buf); // 4
    scenario.native_images.meeting = buffer_read_i32(buf); // 4
    scenario.native_images.crops = buffer_read_i32(buf); // 4
    scenario.climate = buffer_read_u8(buf); // 1
    scenario.flotsam_enabled = buffer_read_u8(buf); // 1
    buffer_skip(buf, 2); //                                                                            00 00
    // (11 + 1)
    scenario.empire.is_expanded = buffer_read_i32(buf); // 4                                                      00 00 00 00 00 00 00
    scenario.empire.expansion_year = buffer_read_i32(buf); // 4                        00 00 00 32 41
    scenario.empire.distant_battle_roman_travel_months = buffer_read_u8(buf); // 1
    scenario.empire.distant_battle_enemy_travel_months = buffer_read_u8(buf); // 1
    scenario.open_play_scenario_id = buffer_read_u8(buf); // 1
    buffer_skip(buf, 1); //                                                                      00

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
        trade_route_init(1, RESOURCE_MARBLE, 15);
}

void scenario_settings_save_state(buffer *part1, buffer *part2, buffer *part3, buffer *player_name, buffer *scenario_name)
{
    switch (GAME_ENV) {
        case ENGINE_ENV_C3:
            buffer_write_i32(part1, scenario.settings.campaign_mission);
            break;
        case ENGINE_ENV_PHARAOH:
            buffer_write_i8(part1, scenario.settings.campaign_mission);
            break;
    }

    buffer_write_i32(part2, scenario.settings.starting_favor);
    buffer_write_i32(part2, scenario.settings.starting_personal_savings);
    buffer_write_i32(part2, scenario.settings.campaign_rank);

    buffer_write_i32(part3, scenario.settings.is_custom);

    for (int i = 0; i < MAX_PLAYER_NAME; i++) {
        buffer_write_u8(player_name, 0);
    }
    buffer_write_raw(player_name, scenario.settings.player_name, MAX_PLAYER_NAME);
    buffer_write_raw(scenario_name, scenario.scenario_name, MAX_SCENARIO_NAME);
}
void scenario_settings_load_state(buffer *part1, buffer *part2, buffer *part3, buffer *player_name, buffer *scenario_name)
{
    switch (GAME_ENV) {
        case ENGINE_ENV_C3:
            scenario.settings.campaign_mission = buffer_read_i32(part1);
            break;
        case ENGINE_ENV_PHARAOH:
            scenario.settings.campaign_mission = buffer_read_i8(part1);
            break;
    }

    scenario.settings.starting_favor = buffer_read_i32(part2);
    scenario.settings.starting_personal_savings = buffer_read_i32(part2);
    scenario.settings.campaign_rank = buffer_read_i32(part2);

    scenario.settings.is_custom = buffer_read_i32(part3);

    buffer_skip(player_name, MAX_PLAYER_NAME);
    buffer_read_raw(player_name, scenario.settings.player_name, MAX_PLAYER_NAME);
    buffer_read_raw(scenario_name, scenario.scenario_name, MAX_SCENARIO_NAME);
}
