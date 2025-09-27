#include "scenario_invasion.h"

#include "building/destruction.h"
#include "city/city.h"
#include "city/city_warnings.h"
#include "game/game_events.h"
#include "city/city_message.h"
#include "core/calc.h"
#include "core/random.h"
#include "empire/empire_object.h"
#include "figure/figure.h"
#include "figure/formation.h"
#include "figure/figure_names.h"
#include "game/difficulty.h"
#include "game/game.h"
#include "grid/grid.h"
#include "grid/terrain.h"
#include "scenario/map.h"
#include "scenario/scenario.h"
#include "dev/debug.h"
#include "js/js_game.h"

declare_console_command_p(start_invasion) {
    int enemy_type = parse_integer_from<bstring32>(is); // 0 type, 1 kingdome, 2 seth natives
    int size = parse_integer_from<bstring32>(is);
    int invasion_point = parse_integer_from<bstring32>(is);
    scenario_invasion_start_from_console(ATTACK_TYPE_ENEMIES, enemy_type, size, invasion_point);

    events::emit(event_city_warning{ "Started invasion" });
}

declare_console_command_p(start_invasion_fast) {
    tile2i tile = scenario_start_invasion_impl(ENEMY_0_BARBARIAN, 150, 8, FORMATION_ATTACK_FOOD_CHAIN, 23);
    if (tile.valid()) {
        events::emit(event_message{ true, MESSAGE_ENEMY_ARMY_ATTACK, g_invasions.last_internal_invasion_id, tile.grid_offset() });
    }
}

std::array<enemy_properties_t, ENEMY_COUNT> g_enemy_properties;

void ANK_REGISTER_CONFIG_ITERATOR(config_load_enemies) {
    g_config_arch.r("enemy_barbarian", g_enemy_properties[ENEMY_0_BARBARIAN]);
    g_config_arch.r("enemy_assyrian", g_enemy_properties[ENEMY_1_ASSYRIAN]);
    g_config_arch.r("enemy_canaanite", g_enemy_properties[ENEMY_2_CANAANITE]);
    g_config_arch.r("enemy_egyptian", g_enemy_properties[ENEMY_3_EGYPTIAN]);
    g_config_arch.r("enemy_hittite", g_enemy_properties[ENEMY_4_HITTITE]);
    g_config_arch.r("enemy_hyksos", g_enemy_properties[ENEMY_5_HYKSOS]);
    g_config_arch.r("enemy_kushite", g_enemy_properties[ENEMY_6_KUSHITE]);
    g_config_arch.r("enemy_libian", g_enemy_properties[ENEMY_7_LIBIAN]);
    g_config_arch.r("enemy_nubian", g_enemy_properties[ENEMY_8_NUBIAN]);
    g_config_arch.r("enemy_persian", g_enemy_properties[ENEMY_9_PERSIAN]);
    g_config_arch.r("enemy_phoenician", g_enemy_properties[ENEMY_10_PHOENICIAN]);
    g_config_arch.r("enemy_roman", g_enemy_properties[ENEMY_11_ROMAN]);
    g_config_arch.r("enemy_seapeople", g_enemy_properties[ENEMY_12_SEAPEOPLE]);
}

static const int LOCAL_UPRISING_NUM_ENEMIES[20] = {0, 0, 0, 0, 0, 3, 3, 3, 0, 6, 6, 6, 6, 6, 9, 9, 9, 9, 9, 9};

invasion_warning_t g_invasion_warning;
invasion_data_t ANK_VARIABLE_N(g_invasions, "invasions");

void scenario_invasion_clear(void) {
    auto &data = g_invasions;
    memset(data.warnings.data(), 0, data.warnings.size() * sizeof(invasion_warning_t));
}

void scenario_invasion_init() {
    auto &data = g_invasions;
    scenario_invasion_clear();
    int path_current = 1;
    int path_max = empire_object_get_max_invasion_path();
    if (path_max == 0)
        return;
    invasion_warning_t* warning = &data.warnings[1];
    for (int i = 0; i < MAX_INVASIONS; i++) {
        random_generate_next();
        if (!g_scenario.invasions[i].type) {
            continue;
        }

        g_scenario.invasions[i].month = 2 + (random_byte() & 7);
        if (g_scenario.invasions[i].type == INVASION_TYPE_LOCAL_UPRISING
            || g_scenario.invasions[i].type == INVASION_TYPE_DISTANT_BATTLE) {
            continue;
        }
        for (int year = 1; year < 8; year++) {
            const empire_object* obj = empire_object_get_battle_icon(path_current, year);
            if (!obj)
                continue;

            warning->in_use = 1;
            warning->invasion_path_id = obj->invasion_path_id;
            warning->warning_years = obj->invasion_years;
            warning->pos = obj->pos;
            warning->image_id = obj->image_id;
            warning->invasion_id = i;
            warning->empire_object_id = obj->id;
            warning->month_notified = 0;
            warning->year_notified = 0;
            warning->months_to_go = 12 * g_scenario.invasions[i].year;
            warning->months_to_go += g_scenario.invasions[i].month;
            warning->months_to_go -= 12 * year;
            ++warning;
        }
        path_current++;
        if (path_current > path_max)
            path_current = 1;
    }
}

bool scenario_invasion_exists_upcoming() {
    for (const auto& warning : g_invasions.warnings) {
        if (warning.in_use && warning.handled)
            return true;
    }
    return false;
}

void scenario_invasion_foreach_warning(std::function<void(vec2i, int)> callback) {
    for (const auto& warning : g_invasions.warnings) {
        if (warning.in_use && warning.handled)
            callback(warning.pos, warning.image_id);
    }
}

int scenario_invasion_count() {
    int num_invasions = 0;
    for (int i = 0; i < MAX_INVASIONS; i++) {
        if (g_scenario.invasions[i].type)
            num_invasions++;
    }
    return num_invasions;
}

static void determine_formations(int num_soldiers, int* num_formations, int soldiers_per_formation[]) {
    if (num_soldiers > 0) {
        if (num_soldiers <= 16) {
            *num_formations = 1;
            soldiers_per_formation[0] = num_soldiers;
        } else if (num_soldiers <= 32) {
            *num_formations = 2;
            soldiers_per_formation[1] = num_soldiers / 2;
            soldiers_per_formation[0] = num_soldiers - num_soldiers / 2;
        } else {
            *num_formations = 3;
            soldiers_per_formation[2] = num_soldiers / 3;
            soldiers_per_formation[1] = num_soldiers / 3;
            soldiers_per_formation[0] = num_soldiers - 2 * (num_soldiers / 3);
        }
    }
}

tile2i scenario_start_invasion_impl(int enemy_type, int amount, int invasion_point, int attack_type, int invasion_id) {
    auto &data = g_invasions;
    if (amount <= 0) {
        return tile2i::invalid;
    }

    int formations_per_type[3];
    int soldiers_per_formation[3][4];
    tile2i invasion_tile;

    amount = std::clamp<int>(difficulty_adjust_enemies(amount), data.min_invasion_amount, data.max_invasion_amount);

    data.last_internal_invasion_id++;
    if (data.last_internal_invasion_id > 32000) {
        data.last_internal_invasion_id = 1;
    }

    // calculate soldiers per type
    int num_type1 = calc_adjust_with_percentage(amount, g_enemy_properties[enemy_type].percentage_type1);
    int num_type2 = calc_adjust_with_percentage(amount, g_enemy_properties[enemy_type].percentage_type2);
    int num_type3 = calc_adjust_with_percentage(amount, g_enemy_properties[enemy_type].percentage_type3);
    num_type1 += amount - (num_type1 + num_type2 + num_type3); // assign leftovers to type1

    for (int t = 0; t < 3; t++) {
        formations_per_type[t] = 0;
        for (int f = 0; f < 4; f++) {
            soldiers_per_formation[t][f] = 0;
        }
    }

    // calculate number of formations
    determine_formations(num_type1, &formations_per_type[0], soldiers_per_formation[0]);
    determine_formations(num_type2, &formations_per_type[1], soldiers_per_formation[1]);
    determine_formations(num_type3, &formations_per_type[2], soldiers_per_formation[2]);

    // determine invasion point
    if (enemy_type == ENEMY_3_EGYPTIAN) {
        invasion_tile = scenario_map_entry();
    } else {
        if (invasion_point < 0) {
            auto& lands = g_scenario.invasion_points_land;
            svector<tile2i, 8> points;
            std::copy_if(lands.begin(), lands.end(), std::back_inserter(points), [] (auto& p) { return p.valid(); });
            invasion_tile = points.at(rand() % points.size());
        } else {
            invasion_tile = g_scenario.invasion_points_land[invasion_point];
        }
    }

    if (!invasion_tile.valid()) {
        invasion_tile = scenario_map_exit();
    }

    // determine orientation
    int orientation = DIR_4_BOTTOM_LEFT;
    // if (y == 0)
    //     orientation = DIR_4_BOTTOM_LEFT;
    // else if (y >= g_scenario.map.height - 1)
    //     orientation = DIR_0_TOP_RIGHT;
    // else if (x == 0)
    //     orientation = DIR_2_BOTTOM_RIGHT;
    // else if (x >= g_scenario.map.width - 1)
    //     orientation = DIR_6_TOP_LEFT;
    // else {
    //     orientation = DIR_4_BOTTOM_LEFT;
    // }
    
    // check terrain    
    if (map_terrain_is(invasion_tile, TERRAIN_ELEVATION | TERRAIN_ROCK | TERRAIN_TREE)) {
        return tile2i::invalid;
    }

    if (map_terrain_is(invasion_tile, TERRAIN_WATER)) {
        if (!map_terrain_is(invasion_tile, TERRAIN_ROAD)) { // bridge
            return tile2i::invalid;
        }
    } else if (map_terrain_is(invasion_tile, TERRAIN_BUILDING | TERRAIN_CANAL | TERRAIN_GATEHOUSE | TERRAIN_WALL)) {
        building_destroy_by_enemy(invasion_tile);
    }

    // spawn the lot!
    int seq = 0;
    for (int type = 0; type < 3; type++) {
        if (formations_per_type[type] <= 0)
            continue;

        e_figure_type figure_type = g_enemy_properties[enemy_type].figure_types[type];
        for (int i = 0; i < formations_per_type[type]; i++) {
            int formation_id = formation_create_enemy(figure_type,
                                                      invasion_tile,
                                                      g_enemy_properties[enemy_type].layout,
                                                      orientation,
                                                      enemy_type,
                                                      attack_type,
                                                      invasion_id,
                                                      data.last_internal_invasion_id);
            if (formation_id <= 0)
                continue;

            for (int fig = 0; fig < soldiers_per_formation[type][i]; fig++) {
                figure* f = figure_create(figure_type, invasion_tile, orientation);
                f->faction_id = 0;
                f->action_state = FIGURE_ACTION_151_ENEMY_INITIAL;
                f->wait_ticks = 200 * seq + 10 * fig + 10;
                f->formation_id = formation_id;
                f->name = figure_name_get(figure_type, enemy_type);
            }
            seq++;
        }
    }

    return invasion_tile;
}

void scenario_invasion_process() {
    int enemy_id = g_scenario.enemy_id;
    for (auto& warning : g_invasions.warnings) {
        if (!warning.in_use)
            continue;

        // update warnings
        warning.months_to_go--;
        if (warning.months_to_go <= 0) {
            if (warning.handled != 1) {
                warning.handled = 1;
                warning.year_notified = game.simtime.year;
                warning.month_notified = game.simtime.month;
                if (warning.warning_years > 2)
                    events::emit(event_message{ false, MESSAGE_DISTANT_BATTLE, 0, 0 });
                else if (warning.warning_years > 1)
                    events::emit(event_message{ false, MESSAGE_ENEMIES_CLOSING, 0, 0 });
                else {
                    events::emit(event_message{ false, MESSAGE_ENEMIES_AT_THE_DOOR, 0, 0 });
                }
            }
        }

        if (game.simtime.year >= g_scenario.start_year + g_scenario.invasions[warning.invasion_id].year
            && game.simtime.month >= g_scenario.invasions[warning.invasion_id].month) {
            // invasion attack time has passed
            warning.in_use = 0;
            if (warning.warning_years > 1) {
                continue;
            }

            // enemy invasions
            if (g_scenario.invasions[warning.invasion_id].type == INVASION_TYPE_ENEMY_ARMY) {
                tile2i invasion_tile = scenario_start_invasion_impl(enemy_id,
                                                 g_scenario.invasions[warning.invasion_id].amount,
                                                 g_scenario.invasions[warning.invasion_id].from,
                                                 g_scenario.invasions[warning.invasion_id].attack_type,
                                                 warning.invasion_id);
                if (invasion_tile.valid()) {
                    events::emit(event_message{ true, MESSAGE_ENEMY_ARMY_ATTACK, g_invasions.last_internal_invasion_id, invasion_tile.grid_offset() });
                }
            }
            if (g_scenario.invasions[warning.invasion_id].type == INVASION_TYPE_KNGDOME) {
                tile2i invasion_tile = scenario_start_invasion_impl(ENEMY_3_EGYPTIAN,
                                                 g_scenario.invasions[warning.invasion_id].amount,
                                                 g_scenario.invasions[warning.invasion_id].from,
                                                 g_scenario.invasions[warning.invasion_id].attack_type,
                                                 warning.invasion_id);
                if (invasion_tile.valid()) {
                    events::emit(event_message{ true, MESSAGE_KINGDOME_ARMY_ATTACK, g_invasions.last_internal_invasion_id, invasion_tile.grid_offset() });
                }
            }
        }
    }
    // local uprisings
    for (int i = 0; i < MAX_INVASIONS; i++) {
        if (g_scenario.invasions[i].type == INVASION_TYPE_LOCAL_UPRISING) {
            if (game.simtime.year == g_scenario.start_year + g_scenario.invasions[i].year
                && game.simtime.month == g_scenario.invasions[i].month) {
                tile2i invasion_tile = scenario_start_invasion_impl(ENEMY_0_BARBARIAN,
                                                 g_scenario.invasions[i].amount,
                                                 g_scenario.invasions[i].from,
                                                 g_scenario.invasions[i].attack_type,
                                                 i);
                if (invasion_tile.valid()) {
                    events::emit(event_message{ true, MESSAGE_LOCAL_UPRISING, g_invasions.last_internal_invasion_id, invasion_tile.grid_offset() });
                }
            }
        }
    }
}

int map_invasion_point(tile2i point) {
    auto &lands = g_scenario.invasion_points_land;
    const auto it_land = std::find_if(lands.begin(), lands.end(), [point] (auto &p) { return p == point; });
    if (it_land != lands.end()) {
        return 1;
    }

    auto &sea = g_scenario.invasion_points_sea;
    const auto it_sea = std::find_if(sea.begin(), sea.end(), [point] (auto &p) { return p == point; });
    if (it_sea != sea.end()) {
        return 2;
    }

    return 0;
}

int scenario_invasion_start_from_seth() {
    auto &data = g_invasions;
    int mission = scenario_campaign_scenario_id();
    if (mission < 0 || mission > 19)
        return 0;

    int amount = LOCAL_UPRISING_NUM_ENEMIES[mission];
    if (amount <= 0)
        return 0;

    tile2i invasion_tile = scenario_start_invasion_impl(ENEMY_0_BARBARIAN, amount, 8, FORMATION_ATTACK_FOOD_CHAIN, 23);
    if (invasion_tile.grid_offset()) {
        events::emit(event_message{ true, MESSAGE_LOCAL_UPRISING_SETH, data.last_internal_invasion_id, invasion_tile.grid_offset() });
    }

    return 1;
}

bool scenario_invasion_start_from_kingdome(int size) {
    auto &data = g_invasions;
    tile2i invasion_tile = scenario_start_invasion_impl(ENEMY_3_EGYPTIAN, size, 0, FORMATION_ATTACK_BEST_BUILDINGS, 24);
    if (invasion_tile.valid()) {
        events::emit(event_message{ true, MESSAGE_KINGDOME_ARMY_ATTACK, data.last_internal_invasion_id, invasion_tile.grid_offset()});
        return true;
    }
    return false;
}

void scenario_invasion_start_from_console(int attack_type, int enemy_type, int size, int invasion_point) {
    auto &data = g_invasions;
    switch (attack_type) {
    case ATTACK_TYPE_ENEMIES: {
        tile2i invasion_tile = scenario_start_invasion_impl(enemy_type, size, invasion_point, FORMATION_ATTACK_RANDOM, 23);
        if (invasion_tile.valid()) {
            events::emit(event_message{ true, MESSAGE_ENEMY_ARMY_ATTACK, data.last_internal_invasion_id, invasion_tile.grid_offset() });
        }
        break;
    }
    case ATTACK_TYPE_KINGDOME: {
        g_city.kingdome.force_attack(size);
        break;
    }
    case ATTACK_TYPE_NATIVES: {
        tile2i invasion_tile = scenario_start_invasion_impl(ENEMY_0_BARBARIAN, size, 8, FORMATION_ATTACK_FOOD_CHAIN, 23);
        if (invasion_tile.valid())
            events::emit(event_message{ true, MESSAGE_LOCAL_UPRISING_SETH, data.last_internal_invasion_id, invasion_tile.grid_offset()});

        break;
    }
    default:
        break;
    }
}

io_buffer* iob_invasion_warnings = new io_buffer([](io_buffer* iob, size_t version) {
    //    data.last_internal_invasion_id = invasion_id->read_u16();

    //    for (int i = 0; i < MAX_INVASION_WARNINGS; i++) {
    //        invasion_warning *w = &data.warnings[i];
    //        w->in_use = warnings->read_u8();
    //        w->handled = warnings->read_u8();
    //        w->invasion_path_id = warnings->read_u8();
    //        w->warning_years = warnings->read_u8();
    //        w->x = warnings->read_i16();
    //        w->y = warnings->read_i16();
    //        w->image_id = warnings->read_i16();
    //        w->empire_object_id = warnings->read_i16();
    //        w->month_notified = warnings->read_i16();
    //        w->year_notified = warnings->read_i16();
    //        w->months_to_go = warnings->read_i32();
    //        w->invasion_id = warnings->read_u8();
    //        warnings->skip(11);
    //    }

    // TODO
});