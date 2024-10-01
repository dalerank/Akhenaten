#include "invasion.h"

#include "building/destruction.h"
#include "city/city.h"
#include "city/message.h"
#include "core/calc.h"
#include "core/random.h"
#include "empire/empire_object.h"
#include "figure/figure.h"
#include "figure/formation.h"
#include "figure/figure_names.h"
#include "game/difficulty.h"
#include "game/time.h"
#include "grid/grid.h"
#include "grid/terrain.h"
#include "scenario/map.h"
#include "scenario/scenario.h"

#include <string.h>

#define MAX_INVASION_WARNINGS 101

static const int ENEMY_ID_TO_ENEMY_TYPE[20] = {
    ENEMY_0_BARBARIAN, ENEMY_7_ETRUSCAN, ENEMY_7_ETRUSCAN, ENEMY_10_CARTHAGINIAN, ENEMY_8_GREEK,
    ENEMY_8_GREEK,     ENEMY_9_EGYPTIAN, ENEMY_5_PERGAMUM, ENEMY_6_SELEUCID,      ENEMY_3_CELT,
    ENEMY_3_CELT,      ENEMY_3_CELT,     ENEMY_2_GAUL,     ENEMY_2_GAUL,          ENEMY_4_GOTH,
    ENEMY_4_GOTH,      ENEMY_4_GOTH,     ENEMY_6_SELEUCID, ENEMY_1_NUMIDIAN,      ENEMY_6_SELEUCID
};

static const int LOCAL_UPRISING_NUM_ENEMIES[20] = {0, 0, 0, 0, 0, 3, 3, 3, 0, 6, 6, 6, 6, 6, 9, 9, 9, 9, 9, 9};

struct enemy_properties_t {
    int pct_type1;
    int pct_type2;
    int pct_type3;
    e_figure_type figure_types[3];
    int formation_layout;
};

static const enemy_properties_t ENEMY_PROPERTIES[12] = {
    { 100, 0, 0, {FIGURE_ENEMY49_FAST_SWORD, FIGURE_NONE, FIGURE_NONE}, FORMATION_ENEMY_MOB},          // barbarian
    { 40, 60, 0, {FIGURE_ENEMY49_FAST_SWORD, FIGURE_ENEMY51_SPEAR, FIGURE_NONE}, FORMATION_ENEMY_MOB}, // numidian
    { 50, 50, 0, {FIGURE_ENEMY50_SWORD, FIGURE_ENEMY53_AXE, FIGURE_NONE}, FORMATION_ENEMY_MOB},        // gaul
    { 80, 20, 0, {FIGURE_ENEMY50_SWORD, FIGURE_ENEMY48_CHARIOT, FIGURE_NONE}, FORMATION_ENEMY_MOB},    // celt
    { 50, 50, 0, {FIGURE_ENEMY49_FAST_SWORD, FIGURE_ENEMY52_MOUNTED_ARCHER, FIGURE_NONE}, FORMATION_ENEMY_MOB}, // goth
    { 30, 70, 0, {FIGURE_ENEMY44_SWORD, FIGURE_ENEMY43_SPEAR, FIGURE_NONE}, FORMATION_COLUMN},                  // pergamum
    { 50, 50, 0, {FIGURE_ENEMY44_SWORD, FIGURE_ENEMY43_SPEAR, FIGURE_NONE}, FORMATION_ENEMY_DOUBLE_LINE},       // seleucid
    { 50, 50, 0, {FIGURE_ENEMY45_SWORD, FIGURE_ENEMY43_SPEAR, FIGURE_NONE}, FORMATION_ENEMY_DOUBLE_LINE},       // etruscan
    { 80, 20, 0, {FIGURE_ENEMY45_SWORD, FIGURE_ENEMY43_SPEAR, FIGURE_NONE}, FORMATION_ENEMY_DOUBLE_LINE},       // greek
    { 80, 20, 0, {FIGURE_ENEMY44_SWORD, FIGURE_ENEMY46_CAMEL, FIGURE_NONE}, FORMATION_ENEMY_WIDE_COLUMN},       // egyptian
    { 90, 10, 0, {FIGURE_ENEMY45_SWORD, FIGURE_ENEMY47_ELEPHANT, FIGURE_NONE}, FORMATION_ENEMY_WIDE_COLUMN},                                                           // carthaginian
    { 100, 0, 0, {FIGURE_ENEMY_CAESAR_LEGIONARY, FIGURE_NONE, FIGURE_NONE}, FORMATION_COLUMN} // caesar
};

enum E_ATTACK_TYPE { ATTACK_TYPE_BARBARIAN, ATTACK_TYPE_CAESAR, ATTACK_TYPE_NATIVES };

struct invasion_warning_t {
    bool in_use;
    bool handled;
    int invasion_path_id;
    int warning_years;
    vec2i pos;
    int image_id;
    int empire_object_id;
    int year_notified;
    int month_notified;
    int months_to_go;
    int invasion_id;
};

invasion_warning_t g_invasion_warning;

struct invasion_data_t {
    int last_internal_invasion_id;
    invasion_warning_t warnings[MAX_INVASION_WARNINGS];
};

invasion_data_t g_invasion_data;

void scenario_invasion_clear(void) {
    auto &data = g_invasion_data;
    memset(data.warnings, 0, MAX_INVASION_WARNINGS * sizeof(invasion_warning_t));
}

void scenario_invasion_init(void) {
    auto &data = g_invasion_data;
    scenario_invasion_clear();
    int path_current = 1;
    int path_max = empire_object_get_max_invasion_path();
    if (path_max == 0)
        return;
    invasion_warning_t* warning = &data.warnings[1];
    for (int i = 0; i < MAX_INVASIONS; i++) {
        random_generate_next();
        if (!g_scenario_data.invasions[i].type)
            continue;

        g_scenario_data.invasions[i].month = 2 + (random_byte() & 7);
        if (g_scenario_data.invasions[i].type == INVASION_TYPE_LOCAL_UPRISING
            || g_scenario_data.invasions[i].type == INVASION_TYPE_DISTANT_BATTLE) {
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
            warning->months_to_go = 12 * g_scenario_data.invasions[i].year;
            warning->months_to_go += g_scenario_data.invasions[i].month;
            warning->months_to_go -= 12 * year;
            ++warning;
        }
        path_current++;
        if (path_current > path_max)
            path_current = 1;
    }
}

bool scenario_invasion_exists_upcoming(void) {
    auto &data = g_invasion_data;
    for (int i = 0; i < MAX_INVASION_WARNINGS; i++) {
        if (data.warnings[i].in_use && data.warnings[i].handled)
            return true;
    }
    return false;
}

void scenario_invasion_foreach_warning(std::function<void(vec2i, int)> callback) {
    auto &data = g_invasion_data;
    for (int i = 0; i < MAX_INVASION_WARNINGS; i++) {
        if (data.warnings[i].in_use && data.warnings[i].handled)
            callback(data.warnings[i].pos, data.warnings[i].image_id);
    }
}

int scenario_invasion_count(void) {
    int num_invasions = 0;
    for (int i = 0; i < MAX_INVASIONS; i++) {
        if (g_scenario_data.invasions[i].type)
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

static int start_invasion(int enemy_type, int amount, int invasion_point, int attack_type, int invasion_id) {
    auto &data = g_invasion_data;
    if (amount <= 0)
        return -1;

    int formations_per_type[3];
    int soldiers_per_formation[3][4];
    int x, y;
    int orientation;

    amount = difficulty_adjust_enemies(amount);
    if (amount >= 150)
        amount = 150;

    data.last_internal_invasion_id++;
    if (data.last_internal_invasion_id > 32000)
        data.last_internal_invasion_id = 1;

    // calculate soldiers per type
    int num_type1 = calc_adjust_with_percentage(amount, ENEMY_PROPERTIES[enemy_type].pct_type1);
    int num_type2 = calc_adjust_with_percentage(amount, ENEMY_PROPERTIES[enemy_type].pct_type2);
    int num_type3 = calc_adjust_with_percentage(amount, ENEMY_PROPERTIES[enemy_type].pct_type3);
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
    if (enemy_type == ENEMY_11_CAESAR) {
        map_point entry_point = scenario_map_entry();
        x = entry_point.x();
        y = entry_point.y();
    } else {
        int num_points = 0;
        for (int i = 0; i < MAX_INVASION_POINTS_LAND; i++) {
            if (g_scenario_data.invasion_points_land[i].grid_offset() != -1)
                num_points++;
        }
        if (invasion_point == MAX_INVASION_POINTS_LAND) { // random
            if (num_points <= 2)
                invasion_point = random_byte() & 1;
            else if (num_points <= 4)
                invasion_point = random_byte() & 3;
            else {
                invasion_point = random_byte() & 7;
            }
        }
        if (num_points > 0) {
            while (g_scenario_data.invasion_points_land[invasion_point].grid_offset() == -1) {
                invasion_point++;
                if (invasion_point >= MAX_INVASION_POINTS_LAND)
                    invasion_point = 0;
            }
        }
        x = g_scenario_data.invasion_points_land[invasion_point].x();
        y = g_scenario_data.invasion_points_land[invasion_point].y();
    }
    if (x == -1 || y == -1) {
        map_point exit_point = scenario_map_exit();
        x = exit_point.x();
        y = exit_point.y();
    }
    // determine orientation
    if (y == 0)
        orientation = DIR_4_BOTTOM_LEFT;
    else if (y >= g_scenario_data.map.height - 1)
        orientation = DIR_0_TOP_RIGHT;
    else if (x == 0)
        orientation = DIR_2_BOTTOM_RIGHT;
    else if (x >= g_scenario_data.map.width - 1)
        orientation = DIR_6_TOP_LEFT;
    else {
        orientation = DIR_4_BOTTOM_LEFT;
    }
    // check terrain
    int grid_offset = MAP_OFFSET(x, y);
    if (map_terrain_is(grid_offset, TERRAIN_ELEVATION | TERRAIN_ROCK | TERRAIN_TREE)) {
        return -1;
    }

    if (map_terrain_is(grid_offset, TERRAIN_WATER)) {
        if (!map_terrain_is(grid_offset, TERRAIN_ROAD)) { // bridge
            return -1;
        }
    } else if (map_terrain_is(grid_offset, TERRAIN_BUILDING | TERRAIN_CANAL | TERRAIN_GATEHOUSE | TERRAIN_WALL)) {
        building_destroy_by_enemy(map_point(grid_offset));
    }

    // spawn the lot!
    int seq = 0;
    for (int type = 0; type < 3; type++) {
        if (formations_per_type[type] <= 0)
            continue;

        e_figure_type figure_type = ENEMY_PROPERTIES[enemy_type].figure_types[type];
        for (int i = 0; i < formations_per_type[type]; i++) {
            int formation_id = formation_create_enemy(figure_type,
                                                      tile2i{x, y},
                                                      ENEMY_PROPERTIES[enemy_type].formation_layout,
                                                      orientation,
                                                      enemy_type,
                                                      attack_type,
                                                      invasion_id,
                                                      data.last_internal_invasion_id);
            if (formation_id <= 0)
                continue;

            for (int fig = 0; fig < soldiers_per_formation[type][i]; fig++) {
                figure* f = figure_create(figure_type, map_point(x, y), orientation);
                f->faction_id = 0;
                f->is_friendly = false;
                f->action_state = FIGURE_ACTION_151_ENEMY_INITIAL;
                f->wait_ticks = 200 * seq + 10 * fig + 10;
                f->formation_id = formation_id;
                f->name = figure_name_get(figure_type, enemy_type);
            }
            seq++;
        }
    }
    return grid_offset;
}

void scenario_invasion_process() {
    auto &data = g_invasion_data;
    int enemy_id = g_scenario_data.enemy_id;
    for (int i = 0; i < MAX_INVASION_WARNINGS; i++) {
        if (!data.warnings[i].in_use)
            continue;

        // update warnings
        invasion_warning_t* warning = &data.warnings[i];
        warning->months_to_go--;
        if (warning->months_to_go <= 0) {
            if (warning->handled != 1) {
                warning->handled = 1;
                warning->year_notified = gametime().year;
                warning->month_notified = gametime().month;
                if (warning->warning_years > 2)
                    city_message_post(false, MESSAGE_DISTANT_BATTLE, 0, 0);
                else if (warning->warning_years > 1)
                    city_message_post(false, MESSAGE_ENEMIES_CLOSING, 0, 0);
                else {
                    city_message_post(false, MESSAGE_ENEMIES_AT_THE_DOOR, 0, 0);
                }
            }
        }

        if (gametime().year >= g_scenario_data.start_year + g_scenario_data.invasions[warning->invasion_id].year
            && gametime().month >= g_scenario_data.invasions[warning->invasion_id].month) {
            // invasion attack time has passed
            warning->in_use = 0;
            if (warning->warning_years > 1)
                continue;

            // enemy invasions
            if (g_scenario_data.invasions[warning->invasion_id].type == INVASION_TYPE_ENEMY_ARMY) {
                int grid_offset = start_invasion(ENEMY_ID_TO_ENEMY_TYPE[enemy_id],
                                                 g_scenario_data.invasions[warning->invasion_id].amount,
                                                 g_scenario_data.invasions[warning->invasion_id].from,
                                                 g_scenario_data.invasions[warning->invasion_id].attack_type,
                                                 warning->invasion_id);
                if (grid_offset > 0) {
                    if (ENEMY_ID_TO_ENEMY_TYPE[enemy_id] > 4)
                        city_message_post(true, MESSAGE_ENEMY_ARMY_ATTACK, data.last_internal_invasion_id, grid_offset);
                    else {
                        city_message_post(true, MESSAGE_BARBARIAN_ATTACK, data.last_internal_invasion_id, grid_offset);
                    }
                }
            }
            if (g_scenario_data.invasions[warning->invasion_id].type == INVASION_TYPE_CAESAR) {
                int grid_offset = start_invasion(ENEMY_11_CAESAR,
                                                 g_scenario_data.invasions[warning->invasion_id].amount,
                                                 g_scenario_data.invasions[warning->invasion_id].from,
                                                 g_scenario_data.invasions[warning->invasion_id].attack_type,
                                                 warning->invasion_id);
                if (grid_offset > 0)
                    city_message_post(true, MESSAGE_CAESAR_ARMY_ATTACK, data.last_internal_invasion_id, grid_offset);
            }
        }
    }
    // local uprisings
    for (int i = 0; i < MAX_INVASIONS; i++) {
        if (g_scenario_data.invasions[i].type == INVASION_TYPE_LOCAL_UPRISING) {
            if (gametime().year == g_scenario_data.start_year + g_scenario_data.invasions[i].year
                && gametime().month == g_scenario_data.invasions[i].month) {
                int grid_offset = start_invasion(ENEMY_0_BARBARIAN,
                                                 g_scenario_data.invasions[i].amount,
                                                 g_scenario_data.invasions[i].from,
                                                 g_scenario_data.invasions[i].attack_type,
                                                 i);
                if (grid_offset > 0)
                    city_message_post(true, MESSAGE_LOCAL_UPRISING, data.last_internal_invasion_id, grid_offset);
            }
        }
    }
}

int scenario_invasion_start_from_mars() {
    auto &data = g_invasion_data;
    int mission = scenario_campaign_scenario_id();
    if (mission < 0 || mission > 19)
        return 0;

    int amount = LOCAL_UPRISING_NUM_ENEMIES[mission];
    if (amount <= 0)
        return 0;

    int grid_offset = start_invasion(ENEMY_0_BARBARIAN, amount, 8, FORMATION_ATTACK_FOOD_CHAIN, 23);
    if (grid_offset)
        city_message_post(true, MESSAGE_LOCAL_UPRISING_MARS, data.last_internal_invasion_id, grid_offset);

    return 1;
}

int scenario_invasion_start_from_caesar(int size) {
    auto &data = g_invasion_data;
    int grid_offset = start_invasion(ENEMY_11_CAESAR, size, 0, FORMATION_ATTACK_BEST_BUILDINGS, 24);
    if (grid_offset > 0) {
        city_message_post(true, MESSAGE_CAESAR_ARMY_ATTACK, data.last_internal_invasion_id, grid_offset);
        return 1;
    }
    return 0;
}

void scenario_invasion_start_from_cheat() {
    auto &data = g_invasion_data;
    int enemy_id = g_scenario_data.enemy_id;
    int grid_offset = start_invasion(ENEMY_ID_TO_ENEMY_TYPE[enemy_id], 150, 8, FORMATION_ATTACK_FOOD_CHAIN, 23);
    if (grid_offset) {
        if (ENEMY_ID_TO_ENEMY_TYPE[enemy_id] > 4)
            city_message_post(true, MESSAGE_ENEMY_ARMY_ATTACK, data.last_internal_invasion_id, grid_offset);
        else {
            city_message_post(true, MESSAGE_BARBARIAN_ATTACK, data.last_internal_invasion_id, grid_offset);
        }
    }
}

void scenario_invasion_start_from_console(int attack_type, int size, int invasion_point) {
    auto &data = g_invasion_data;
    switch (attack_type) {
    case ATTACK_TYPE_BARBARIAN: {
        int enemy_id = g_scenario_data.enemy_id;
        int grid_offset
          = start_invasion(ENEMY_ID_TO_ENEMY_TYPE[enemy_id], size, invasion_point, FORMATION_ATTACK_RANDOM, 23);
        if (grid_offset) {
            if (ENEMY_ID_TO_ENEMY_TYPE[enemy_id] > 4)
                city_message_post(true, MESSAGE_ENEMY_ARMY_ATTACK, data.last_internal_invasion_id, grid_offset);
            else {
                city_message_post(true, MESSAGE_BARBARIAN_ATTACK, data.last_internal_invasion_id, grid_offset);
            }
        }
        break;
    }
    case ATTACK_TYPE_CAESAR: {
        g_city.kingdome.force_attack(size);
        break;
    }
    case ATTACK_TYPE_NATIVES: {
        int grid_offset = start_invasion(ENEMY_0_BARBARIAN, size, 8, FORMATION_ATTACK_FOOD_CHAIN, 23);
        if (grid_offset)
            city_message_post(true, MESSAGE_LOCAL_UPRISING_MARS, data.last_internal_invasion_id, grid_offset);

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