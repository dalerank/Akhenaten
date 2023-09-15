#include "cheats.h"

#include "building/construction/build_planner.h"
#include "building/building_type.h"
#include "city/finance.h"
#include "city/gods.h"
#include "city/victory.h"
#include "city/warning.h"
#include "core/string.h"
#include "figure/figure.h"
#include "game/tick.h"
#include "graphics/color.h"
#include "graphics/font.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "scenario/invasion.h"
#include "window/building_info.h"
#include "window/city.h"
#include "window/console.h"

#include <string.h>

#ifndef _WIN32
#define stricmp strcasecmp
#endif

static void game_cheat_add_money(uint8_t*);
static void game_cheat_start_invasion(uint8_t*);
static void game_cheat_advance_year(uint8_t*);
static void game_cheat_cast_blessing(uint8_t*);
static void game_cheat_show_tooltip(uint8_t*);
static void game_cheat_kill_all(uint8_t*);
static void game_cheat_victory(uint8_t*);
static void game_cheat_cast_upset(uint8_t*);

using cheat_command = void(uint8_t* args);

struct cheat_command_handle {
    const char* name;
    cheat_command* command;
};

static cheat_command_handle g_cheat_commands[] = {{"addmoney", game_cheat_add_money},
                                                  {"startinvasion", game_cheat_start_invasion},
                                                  {"nextyear", game_cheat_advance_year},
                                                  {"blessing", game_cheat_cast_blessing},
                                                  {"godupset", game_cheat_cast_upset},
                                                  {"showtooltip", game_cheat_show_tooltip},
                                                  {"killall", game_cheat_kill_all},
                                                  {"victory", game_cheat_victory}};

struct cheats_data_t {
    bool is_cheating;
    int tooltip_enabled;
};

cheats_data_t g_cheats_data;

static int parse_word(uint8_t* string, uint8_t* word) {
    int count = 0;
    while (*string && *string != ' ') {
        *word = *string;
        word++;
        string++;
        count++;
    }
    *word = 0;
    return count + 1;
}

// return value is next argument index
static int parse_integer(uint8_t* string, int* value) {
    uint8_t copy[MAX_COMMAND_SIZE];
    int count = 0;
    while (*string && *string != ' ') {
        copy[count] = *string;
        count++;
        string++;
    }
    copy[count] = 0;
    *value = string_to_int(copy);
    return count + 1;
}

void game_cheat_activate(void) {
    if (window_is(WINDOW_BUILDING_INFO))
        g_cheats_data.is_cheating = window_building_info_get_int() == BUILDING_WELL;
    else if (g_cheats_data.is_cheating && window_is(WINDOW_MESSAGE_DIALOG)) {
        g_cheats_data.is_cheating = true;
        scenario_invasion_start_from_cheat();
    } else {
        g_cheats_data.is_cheating = 0;
    }
}

int game_cheat_tooltip_enabled(void) {
    return g_cheats_data.tooltip_enabled;
}

void game_cheat_money(void) {
    if (g_cheats_data.is_cheating) {
        city_finance_process_cheat();
        window_invalidate();
    }
}

void game_cheat_victory(uint8_t*) {
    if (g_cheats_data.is_cheating) {
        city_victory_force_win();
    }
}

void game_cheat_breakpoint() {
    if (g_cheats_data.is_cheating) {
        //
    }
}

void game_cheat_console(bool force) {
    g_cheats_data.is_cheating |= force;
    if (g_cheats_data.is_cheating) {
        Planner.reset();
        window_city_show();
        window_console_show();
    }
}

static void game_cheat_add_money(uint8_t* args) {
    int money = 0;
    parse_integer(args, &money);
    city_finance_process_console(money);
    window_invalidate();

    city_warning_show_console((uint8_t*)"Added money");
}

static void game_cheat_start_invasion(uint8_t* args) {
    int attack_type = 0;
    int size = 0;
    int invasion_point = 0;
    int index = parse_integer(args, &attack_type); // 0 barbarians, 1 caesar, 2 mars natives
    index = parse_integer(args + index, &size);
    parse_integer(args + index, &invasion_point);
    scenario_invasion_start_from_console(attack_type, size, invasion_point);

    city_warning_show_console((uint8_t*)"Started invasion");
}

static void game_cheat_advance_year(uint8_t* args) {
    game_tick_cheat_year();

    city_warning_show_console((uint8_t*)"Year advanced");
}

static void game_cheat_cast_blessing(uint8_t* args) {
    int god_id = 0;
    parse_integer(args, &god_id);
    city_god_blessing_cheat((e_god)god_id);

    city_warning_show_console((uint8_t*)"Casted blessing");
}

static void game_cheat_cast_upset(uint8_t* args) {
    int god_id = 0;
    parse_integer(args, &god_id);
    city_god_upset_cheat((e_god)god_id);

    city_warning_show_console((uint8_t*)"Casted upset");
}

static void game_cheat_show_tooltip(uint8_t* args) {
    parse_integer(args, &g_cheats_data.tooltip_enabled);

    city_warning_show_console((uint8_t*)"Show tooltip toggled");
}

static void game_cheat_kill_all(uint8_t* args) {
    figure_kill_all();
    city_warning_show_console((uint8_t*)"Killed all walkers");
}

void game_cheat_parse_command(uint8_t* command) {
    uint8_t command_to_call[MAX_COMMAND_SIZE];
    int next_arg = parse_word(command, command_to_call);
    for (auto& handle : g_cheat_commands) {
        if (stricmp((char*)command_to_call, handle.name) == 0) {
            uint8_t *args = next_arg >= strlen((const char *)handle.name) ? (command + next_arg) : nullptr;
            handle.command(args);
        }
    }
}
