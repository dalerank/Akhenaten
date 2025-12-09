#include "city_religion_seth.h"

#include "city/city.h"
#include "city/city_message.h"
#include "city/city_figures.h"
#include "figure/figure.h"
#include "figure/formation_batalion.h"
#include "figure/figure_type.h"
#include "scenario/scenario_invasion.h"
#include "scenario/scenario.h"
#include "game/game_events.h"
#include "core/random.h"
#include "figuretype/water.h"

god_seth_t god_seth;

void god_seth_t::sink_all_ships() {
    figure_valid_do([] (figure &f) {
        if (f.is_boat()) {
            f.dcast()->kill();
        }
    });
}

void god_seth_t::ships_destruction() {
    sink_all_ships();
}

bool god_seth_t::formation_legion_curse() {
    return formation_batalion_curse() != 0;
}

int god_seth_t::invasion_start_from_seth() {
    auto &data = g_invasions;
    int mission = g_scenario.campaign_scenario_id();
    if (mission < 0 || mission > 19) {
        return 0;
    }

    int amount = LOCAL_UPRISING_NUM_ENEMIES[mission];
    if (amount <= 0) {
        return 0;
    }

    tile2i invasion_tile = scenario_start_invasion_impl(ENEMY_0_BARBARIAN, amount, 8, FORMATION_ATTACK_FOOD_CHAIN, 23);
    if (invasion_tile.grid_offset()) {
        events::emit(event_message_god{ GOD_SETH, "message_local_wrath_of_seth" });
    }

    return 1;
}

void god_seth_t::perform_major_curse() {
    if (anti_scum_random_bool()) {
        ships_destruction();
        events::emit(event_message_god{ GOD_SETH, "message_wrath_of_seth" });
    } else {
        perform_hailstorm();
        events::emit(event_message_god{ GOD_SETH, "message_hailstorm_wrath_of_seth" });
    }    
}

void god_seth_t::perform_hailstorm() {
    if (formation_legion_curse()) {
        events::emit(event_message_god{ GOD_SETH, "message_wrath_of_seth_2" });
        invasion_start_from_seth();
    } else {
        events::emit(event_message_god{ GOD_SETH, "message_curse_seth_noeffect" });
    }
}

bool god_seth_t::perform_fort_destruction() {
    // TODO: implement fort destruction
    //            formation_legion_curse();
    return false;
}

void god_seth_t::perform_minor_curse() {
    // destroys the best fort
    bool success = perform_fort_destruction();
    if (success) {
        events::emit(event_message_god{ GOD_SETH, "message_seth_is_upset" });
    } else {
        events::emit(event_message_god{ GOD_SETH, "message_seth_is_upset_noeffect" });
    }
}