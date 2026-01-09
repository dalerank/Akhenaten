#include "cheats.h"

#include "building/construction/build_planner.h"
#include "building/building_house.h"
#include "building/building_type.h"
#include "building/destruction.h"
#include "building/monuments.h"
#include "city/city_finance.h"
#include "city/city.h"
#include "game/game_events.h"
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
#include "scenario/scenario_invasion.h"
#include "window/window_building_info.h"
#include "window/window_city.h"
#include "window/console.h"
#include "dev/debug.h"

#include <string.h>
#include <iostream>

#ifndef _WIN32
#define stricmp strcasecmp
#endif

static void game_cheat_spawn_nobles(pcstr);
static void game_cheat_clear_progress(pcstr);

using cheat_command = void(pcstr);

struct cheat_command_handle {
    const char* name;
    cheat_command* command;
};

static cheat_command_handle g_cheat_commands[] = {{"spawnnobles", game_cheat_spawn_nobles},
                                                  {"clearprogress", game_cheat_clear_progress}
};

struct cheats_data_t {
    bool is_cheating;
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

void game_cheat_force_activate() {
    g_cheats_data.is_cheating = true;
}

bool game_cheat_is_active() {
    return g_cheats_data.is_cheating;
}

void game_cheat_activate() {
    if (window_is(WINDOW_BUILDING_INFO)) {
        g_cheats_data.is_cheating = (window_building_info_get_type() == BUILDING_WELL);
    } else {
        g_cheats_data.is_cheating = 0;
    }
}

static void game_cheat_clear_progress(pcstr args) {
    map_monuments_clear();
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
        buildings[i]->create_roaming_figure(FIGURE_NOBLES, (e_figure_action)ACTION_125_ROAMER_ROAMING, BUILDING_SLOT_SERVICE);
    }
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
    g_city.finance.treasury += money;
    events::emit(event_city_warning{ "Added money" });
}

declare_console_command_p(crashme) {
    events::emit(event_city_warning{ "Trying to crash the game" });
    const int *p = nullptr;
    std::cout << *p;
}

