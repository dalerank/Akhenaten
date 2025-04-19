#include "cheats.h"

#include "building/construction/build_planner.h"
#include "building/building_house.h"
#include "building/building_type.h"
#include "building/destruction.h"
#include "building/monuments.h"
#include "city/finance.h"
#include "city/city.h"
#include "city/city_events.h"
#include "city/victory.h"
#include "city/city_warnings.h"
#include "city/city_health.h"
#include "city/city_resource.h"
#include "core/string.h"
#include "figure/figure.h"
#include "game/tutorial.h"
#include "graphics/color.h"
#include "graphics/font.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "scenario/invasion.h"
#include "window/window_building_info.h"
#include "window/window_city.h"
#include "window/console.h"
#include "figure/formation_herd.h"
#include "dev/debug.h"

#include <string.h>
#include <iostream>

#ifndef _WIN32
#define stricmp strcasecmp
#endif

static void game_cheat_start_invasion(pcstr);
static void game_cheat_show_tooltip(pcstr);
static void game_cheat_pop_milestone(pcstr);
static void game_cheat_spawn_nobles(pcstr);
static void game_cheat_clear_progress(pcstr);
static void game_cheat_add_clay(pcstr);

using cheat_command = void(pcstr);

struct cheat_command_handle {
    const char* name;
    cheat_command* command;
};

static cheat_command_handle g_cheat_commands[] = {{"startinvasion", game_cheat_start_invasion},
                                                  {"addclay", game_cheat_add_clay},
                                                  {"showtooltip", game_cheat_show_tooltip},
                                                  {"popmilestone", game_cheat_pop_milestone},
                                                  {"spawnnobles", game_cheat_spawn_nobles},
                                                  {"clearprogress", game_cheat_clear_progress}
};

struct cheats_data_t {
    bool is_cheating;
    int tooltip_enabled;
};

cheats_data_t g_cheats_data;

static int parse_word(pcstr string, pstr word) {
    int count = 0;
    while (*string && *string != ' ') {
        *word = *string;
        word++;
        string++;
        count++;
    }
    *word = '\0';
    return count + 1;
}

// return value is next argument index
int parse_integer(pcstr string, int &value) {
    bstring64 copy;
    int count = 0;
    while (*string && *string != ' ') {
        copy.data()[count] = *string;
        count++;
        string++;
    }
    copy.data()[count] = '\0';
    value = string_to_int(copy);
    return count + 1;
}

void game_cheat_activate() {
    if (window_is(WINDOW_BUILDING_INFO)) {
        g_cheats_data.is_cheating = (window_building_info_get_type() == BUILDING_WELL);
    } else if (g_cheats_data.is_cheating && window_is(WINDOW_MESSAGE_DIALOG)) {
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
        g_city_planner.reset();
        window_city_show();
        window_console_show();
    }
}

static void game_cheat_clear_progress(pcstr args) {
    map_monuments_clear();
}

static void game_cheat_add_clay(pcstr args) {
    int clay = 0;
    parse_integer(args ? args : (pcstr )"100", clay);
    city_resource_add_items(RESOURCE_CLAY, clay);

    events::emit(event_city_warning{ "Added clay" });
}

static void game_cheat_pop_milestone(pcstr args) {
    g_city.population.reached_milestone(true);
}

static void game_cheat_start_invasion(pcstr args) {
    int attack_type = 0;
    int size = 0;
    int invasion_point = 0;
    int index = parse_integer(args, attack_type); // 0 barbarians, 1 caesar, 2 mars natives
    index = parse_integer(args + index, size);
    parse_integer(args + index, invasion_point);
    scenario_invasion_start_from_console(attack_type, size, invasion_point);

    events::emit(event_city_warning{ "Started invasion" });
}

static void game_cheat_spawn_nobles(pcstr args) {
    int count = 0;
    parse_integer(args ? args : "10", count);

    svector<building *, 1000> buildings;
    buildings_house_do([&] (auto house) {
        if (house->house_population() > 0) {
            buildings.push_back(&house->base);
        }
    });
    
    int step = std::max<int>(1, (int)buildings.size() / count);
    for (int i = 0; i < buildings.size(); i += step) {
        if (!buildings[i]->has_road_access) {
            continue;
        }
        buildings[i]->create_roaming_figure(FIGURE_NOBLES, FIGURE_ACTION_125_ROAMING);
    }
}

static void game_cheat_show_tooltip(pcstr args) {
    parse_integer(args, g_cheats_data.tooltip_enabled);

    events::emit(event_city_warning{ "Show tooltip toggled" });
}

void game_cheat_parse_command(pcstr command) {
    bstring256 command_to_call;
    int next_arg = parse_word(command, command_to_call);

    for (auto& handle : g_cheat_commands) {
        if (stricmp((char*)command_to_call, handle.name) == 0) {
            pcstr args = (next_arg >= strlen((const char *)command)) ? nullptr : (command + next_arg);
            handle.command(args);
        }
    }
}

declare_console_command_p(addmoney) {
    std::string args; is >> args;
    int money = 0;
    parse_integer(args.empty() ? (pcstr )"100" : args.c_str(), money);
    city_finance_process_console(money);
    events::emit(event_city_warning{ "Added money" });
}

declare_console_command_p(crashme) {
    events::emit(event_city_warning{ "Trying to crash the game" });
    const int *p = nullptr;
    std::cout << *p;
}

