#include "tutorial.h"

#include "building/building_menu.h"
#include "city/buildings.h"
#include "city/message.h"
#include "city/mission.h"
#include "city/population.h"
#include "city/city_resource.h"
#include "empire/empire_city.h"
#include "game/resource.h"
#include "io/io_buffer.h"
#include "platform/arguments.h"
#include "scenario/criteria.h"
#include "scenario/scenario.h"
#include "city/sentiment.h"
#include "game/game.h"

#include <algorithm>
#include "dev/debug.h"
#include <iostream>

tutorial_flags_t g_tutorials_flags;
const tutorial_stage_t tutorial_stage;

declare_console_command_p(runstage, game_cheat_tutorial_step);
void game_cheat_tutorial_step(std::istream &is, std::ostream &) {
    std::string args;
    is >> args;
    tutorial_update_step(args.c_str());
}

static void post_message(int message) {
    city_message_post(true, message, 0, 0);
}

static void set_all_tut_flags_null() {
    // tutorial 1
    g_tutorials_flags.tutorial_1.fire = 0;
    g_tutorials_flags.tutorial_1.population_150_reached = 0;
    g_tutorials_flags.tutorial_1.gamemeat_400_stored = 0;
    g_tutorials_flags.tutorial_1.collapse = 0;
    g_tutorials_flags.tutorial_1.started = 0;

    // tutorial 2
    g_tutorials_flags.tutorial_2.started = 0;
    g_tutorials_flags.tutorial_2.gold_mined_500 = 0;
    g_tutorials_flags.tutorial_2.temples_built = 0;

    // tutorial 3
    g_tutorials_flags.tutorial_3.started = 0;
    g_tutorials_flags.tutorial_3.figs_800_stored = 0;
    g_tutorials_flags.tutorial_3.pottery_made = 0;

    // tutorial 4
    g_tutorials_flags.tutorial_4.started = 0;
    g_tutorials_flags.tutorial_4.beer_made = 0;

    // tutorial 5
    g_tutorials_flags.tutorial_5.started = 0;
    g_tutorials_flags.tutorial_5.spacious_apartment = 0;
    g_tutorials_flags.tutorial_5.papyrus_made = 0;
    g_tutorials_flags.tutorial_5.bricks_bought = 0;

    // tutorial 6
    g_tutorials_flags.tutorial_6.started = 0;

    //
    g_tutorials_flags.pharaoh.tut7_start = 0;
    g_tutorials_flags.pharaoh.tut8_start = 0;

    for (int i = 0; i < 41; i++) {
        g_tutorials_flags.pharaoh.flags[i] = 0;
    }
}

template<class T>
void memset_if(bool ok, char v, T &t) {
    if (ok) {
        memset(&t, 1, sizeof(t));
    }
}

bool tutorial_init(bool clear_all_flags, bool custom) {
    if (clear_all_flags) {
        set_all_tut_flags_null();
    }

    if (custom) {
        return false;
    }

    int scenario_id = scenario_campaign_scenario_id();
    memset_if(0 < scenario_id, 1, g_tutorials_flags.tutorial_1);
    memset_if(1 < scenario_id, 1, g_tutorials_flags.tutorial_2);
    memset_if(2 < scenario_id, 1, g_tutorials_flags.tutorial_3);
    memset_if(3 < scenario_id, 1, g_tutorials_flags.tutorial_4);
    memset_if(4 < scenario_id, 1, g_tutorials_flags.tutorial_5);
    memset_if(5 < scenario_id, 1, g_tutorials_flags.tutorial_6);

    tutorial_map_update(scenario_id + 1);
    return tutorial_menu_update(scenario_id + 1);
}

e_availability mission_advisor_availability(e_advisor advisor, int mission) {
    svector<e_advisor, ADVISOR_MAX> advisors;
    switch (mission) {
    case 1:
        return NOT_AVAILABLE;
    case 2:
        advisors = {ADVISOR_ENTERTAINMENT, ADVISOR_RELIGION};
        break;
    case 3: 
        advisors = {ADVISOR_LABOR, ADVISOR_ENTERTAINMENT, ADVISOR_RELIGION};
        break;
    case 4:
        advisors = {ADVISOR_LABOR, ADVISOR_ENTERTAINMENT, ADVISOR_RELIGION, ADVISOR_FINANCIAL};
        break;
    case 5:
        advisors = {ADVISOR_LABOR, ADVISOR_IMPERIAL, ADVISOR_RATINGS, ADVISOR_POPULATION, ADVISOR_HEALTH, ADVISOR_ENTERTAINMENT, ADVISOR_RELIGION, ADVISOR_FINANCIAL, ADVISOR_CHIEF};
        if (g_tutorials_flags.tutorial_5.spacious_apartment) {
            advisors.push_back(ADVISOR_EDUCATION);
        }

        if (g_tutorials_flags.tutorial_5.papyrus_made) {
            advisors.push_back(ADVISOR_TRADE);
        }
        break;
    case 6:
        return AVAILABLE;
    }

    return advisors.empty() 
                ? AVAILABLE 
                : (std::find(advisors.begin(), advisors.end(), advisor) != advisors.end())
                    ? AVAILABLE
                    : NOT_AVAILABLE;
}

e_availability mission_empire_availability(int mission) {
    if (g_scenario_data.settings.is_custom) {
        return NOT_AVAILABLE;
    }

    if (mission < 5) {
        return NOT_AVAILABLE;
    }

    if (mission == 5) {
        return (g_tutorials_flags.tutorial_5.papyrus_made)
                    ? AVAILABLE
                    : NOT_AVAILABLE;
    }
    // TODO
    //    else if (!g_tutorials_flags.pharaoh.tut5_can_trade_finally)
    //        return NOT_AVAILABLE_YET;
    //    else
    return AVAILABLE;
}

void tutorial_map_update(int tut) {
    if (tut == 1) {
        g_scenario_data.env.has_animals = true;
    } else if (tut == 2) {
        g_scenario_data.env.has_animals = true;
    }
}

bool tutorial_menu_update(int tut) {
    if (tut == 1) {
        if (g_tutorials_flags.tutorial_1.fire) building_menu_update(tutorial_stage.tutorial_fire);
        if (g_tutorials_flags.tutorial_1.population_150_reached)  building_menu_update(tutorial_stage.tutorial_food);
        if (g_tutorials_flags.tutorial_1.collapse) building_menu_update(tutorial_stage.tutorial_collapse);
        if (g_tutorials_flags.tutorial_1.gamemeat_400_stored) building_menu_update(tutorial_stage.tutorial_water);

        return true;
    } 
    
    if (tut == 2) {
        if (g_tutorials_flags.tutorial_2.gold_mined_500) building_menu_update(tutorial_stage.tutorial_gods);
        if (g_tutorials_flags.tutorial_2.temples_built) building_menu_update(tutorial_stage.tutorial_entertainment);

        return true;
    } 
    
    if (tut == 3) {            
        if (g_tutorials_flags.tutorial_3.figs_800_stored) building_menu_update(tutorial_stage.tutorial_industry);
        if (g_tutorials_flags.tutorial_3.pottery_made) building_menu_update(tutorial_stage.tutorial_industry);
        if (g_tutorials_flags.tutorial_3.disease) building_menu_update(tutorial_stage.tutorial_health);
        if (g_tutorials_flags.tutorial_3.pottery_made) building_menu_update(tutorial_stage.tutorial_gardens);

        return true;
    } 
    
    if (tut == 4) {
        if (g_tutorials_flags.tutorial_4.beer_made) building_menu_update(tutorial_stage.tutorial_finance);
        return true;
    } 
    
    if (tut == 5) {
        if (g_tutorials_flags.tutorial_5.spacious_apartment) building_menu_update(tutorial_stage.tutorial_education);
        if (g_tutorials_flags.tutorial_5.papyrus_made) building_menu_update(tutorial_stage.tutorial_trading);
        if (g_tutorials_flags.tutorial_5.bricks_bought) building_menu_update(tutorial_stage.tutorial_monuments);

        return true;
    } 
    
    if (tut == 6) {
        return true;
    } 
    
    if (tut == 7) {
        return true;
    } 
    
    if (tut == 8) {
        return true;
    }

    return false;
}

int tutorial_get_population_cap(int current_cap) {
    return current_cap; // temp
    if (scenario_is_mission_rank(1)) {
        if (!g_tutorials_flags.tutorial_1.fire || !g_tutorials_flags.tutorial_1.collapse) {
            return 80;
        }
    } else if (scenario_is_mission_rank(2)) {
        if (!g_tutorials_flags.tutorial_2.granary_built) {
            return 150;
        }
    } else if (scenario_is_mission_rank(3)) {
        if (!g_tutorials_flags.tutorial_3.pottery_made) {
            return 520;
        }
    }
    return current_cap;
}

int tutorial_get_immediate_goal_text(void) {
    if (scenario_is_mission_rank(1)) {
        if (!g_tutorials_flags.tutorial_1.population_150_reached)
            return 21;
        else if (!g_tutorials_flags.tutorial_1.gamemeat_400_stored)
            return 19;
        else
            return 20;
    } else if (scenario_is_mission_rank(2)) {
        if (!g_tutorials_flags.tutorial_2.gold_mined_500) {
            return 24;
        } else if (!g_tutorials_flags.tutorial_2.temples_built) {
            return 23;
        } else {
            return 22;
        }
    } else if (scenario_is_mission_rank(3)) {
        if (!g_tutorials_flags.tutorial_3.figs_800_stored) {
            return 28;
        } else if (!g_tutorials_flags.tutorial_3.pottery_made) {
            return 27;
        } else {
            return 26;
        }
    } else if (scenario_is_mission_rank(4)) {
        if (!g_tutorials_flags.tutorial_4.beer_made) {
            return 33;
        }
    } else if (scenario_is_mission_rank(5)) {
        if (!g_tutorials_flags.tutorial_5.spacious_apartment) {
            return 31;
        } else if (!g_tutorials_flags.tutorial_5.papyrus_made) {
            return 30;
        } else if (!g_tutorials_flags.tutorial_5.bricks_bought) {
            return 29;
        } else {
            return 34;
        }
    } else if (scenario_is_mission_rank(6)) {

    }
    return 0;
}

int tutorial_adjust_request_year(int* year) {
    if (scenario_is_mission_rank(2)) {
        if (!g_tutorials_flags.tutorial_3.pottery_made) {
            return 0;
        }

        *year = g_tutorials_flags.tutorial_3.pottery_made_year;
    }
    return 1;
}

int tutorial_extra_fire_risk(void) {
    return !g_tutorials_flags.tutorial_1.fire
           && scenario_is_mission_rank(1); // Fix for extra fire risk in late tutorials
}

int tutorial_extra_damage_risk(void) {
    return g_tutorials_flags.tutorial_1.fire && !g_tutorials_flags.tutorial_1.collapse
           && scenario_is_mission_rank(1); // Fix for extra damage risk in late tutorials
}

int tutorial_handle_fire() {
    if (g_tutorials_flags.tutorial_1.fire) {
        return 0;
    }

    g_tutorials_flags.tutorial_1.fire = 1;
    building_menu_update(tutorial_stage.tutorial_fire);
    post_message(MESSAGE_TUTORIAL_FIRE_IN_THE_VILLAGE);
    return 1;
}

int tutorial_handle_collapse(void) {
    if (g_tutorials_flags.tutorial_1.collapse)
        return 0;

    g_tutorials_flags.tutorial_1.collapse = 1;
    building_menu_update(tutorial_stage.tutorial_collapse);
    post_message(MESSAGE_TUTORIAL_COLLAPSED_BUILDING);
    return 1;
}

void tutorial_flags_t::on_crime() {
    if (!g_tutorials_flags.pharaoh.crime) {
        g_tutorials_flags.pharaoh.crime = 1;
        building_menu_update(tutorial_stage.tutorial_crime);
    }
}

void tutorial_on_disease() {
    if (scenario_is_mission_rank(3) && !g_tutorials_flags.tutorial_3.disease) {
        g_tutorials_flags.tutorial_3.disease = true;
        building_menu_update(tutorial_stage.tutorial_health);
        post_message(MESSAGE_TUTORIAL_BASIC_HEALTHCARE);
    }
}

void tutorial_on_filled_granary(int quantity) {
    if (scenario_is_mission_rank(1) && !g_tutorials_flags.tutorial_1.gamemeat_400_stored && quantity >= 400) {
        g_tutorials_flags.tutorial_1.gamemeat_400_stored = 1;
        building_menu_update(tutorial_stage.tutorial_water);
        post_message(MESSAGE_TUTORIAL_CLEAN_WATER);
    }

    if (scenario_is_mission_rank(3) && !g_tutorials_flags.tutorial_3.figs_800_stored && quantity >= 800) {
        g_tutorials_flags.tutorial_3.figs_800_stored = 1;
        building_menu_update(tutorial_stage.tutorial_industry);
        post_message(MESSAGE_TUTORIAL_INDUSTRY);
    }
}

void tutorial_check_resources_on_storageyard() {
    if (!g_tutorials_flags.tutorial_3.pottery_made && city_resource_warehouse_stored(RESOURCE_POTTERY) >= 1) {
        g_tutorials_flags.tutorial_3.pottery_made = true;
        g_tutorials_flags.tutorial_3.pottery_made_year = game.simtime.year;
        //building_menu_update(BUILDSET_NORMAL);
        post_message(MESSAGE_TUTORIAL_TRADE);
    } else if (!g_tutorials_flags.tutorial_3.pottery_made && city_resource_warehouse_stored(RESOURCE_POTTERY) >= 2) {
        g_tutorials_flags.tutorial_3.pottery_made = true;
        building_menu_update(tutorial_stage.tutorial_gardens);
        post_message(MESSAGE_TUTORIAL_MUNICIPAL_STRUCTURES);
    } else if (!g_tutorials_flags.tutorial_4.beer_made && city_resource_warehouse_stored(RESOURCE_BEER) >= 3) {
        g_tutorials_flags.tutorial_4.beer_made = true;
        building_menu_update(tutorial_stage.tutorial_finance);
        post_message(MESSAGE_TUTORIAL_FINANCES);
    } if (!g_tutorials_flags.tutorial_5.papyrus_made && city_resource_warehouse_stored(RESOURCE_PAPYRUS) >= 1) {
        g_tutorials_flags.tutorial_5.papyrus_made = 1;
        building_menu_update(tutorial_stage.tutorial_trading);
        post_message(MESSAGE_TUTORIAL_TRADE_WITH_OTHER_CITIES);
    } if (!g_tutorials_flags.tutorial_5.bricks_bought && city_resource_warehouse_stored(RESOURCE_BRICKS) >= 1) {
        g_tutorials_flags.tutorial_5.bricks_bought = 1;
        building_menu_update(tutorial_stage.tutorial_monuments);
        post_message(MESSAGE_TUTORIAL_MONUMENTS);
    }
}

void tutorial_on_gold_extracted() {
    if (scenario_is_mission_rank(2) && !g_tutorials_flags.tutorial_2.gold_mined_500) {
        g_tutorials_flags.tutorial_2.gold_mined_500 = true;
        building_menu_update(tutorial_stage.tutorial_gods);
        post_message(MESSAGE_TUTORIAL_GODS_OF_EGYPT);
    }
}

void tutorial_on_religion() {
    if (!scenario_is_mission_rank(2)) {
        return;
    }
    
    if (!g_tutorials_flags.tutorial_2.temples_built) {
        return;
    }
    
    g_tutorials_flags.tutorial_2.temples_built = true;
    building_menu_update(tutorial_stage.tutorial_entertainment);
    post_message(MESSAGE_TUTORIAL_ENTERTAINMENT);
}

void tutorial_on_house_evolve(e_house_level level) {
    if (!g_tutorials_flags.tutorial_5.spacious_apartment && level >= HOUSE_SPACIOUS_APARTMENT) {
        g_tutorials_flags.tutorial_5.spacious_apartment = true;
        building_menu_update(tutorial_stage.tutorial_education);
        post_message(MESSAGE_TUTORIAL_EDUCATION);
    }
}

void tutorial_update_step(pcstr s) {
    const xstring step(s);
    if (step == tutorial_stage.tutorial_fire) {
        g_tutorials_flags.tutorial_1.fire = false;
        tutorial_handle_fire();
    } else if (step == tutorial_stage.tutorial_food) {
        building_menu_update(step);
        post_message(MESSAGE_TUTORIAL_FOOD_OR_FAMINE);
    } else if (step == tutorial_stage.tutorial_water) {
        building_menu_update(step);
        post_message(MESSAGE_TUTORIAL_CLEAN_WATER);
    } else if (step == tutorial_stage.tutorial_collapse) {
        g_tutorials_flags.tutorial_1.collapse = false;
        tutorial_handle_collapse();
    } else if (step == tutorial_stage.tutorial_gods) {
        building_menu_update(step);
        post_message(MESSAGE_TUTORIAL_GODS_OF_EGYPT);
    } else if (step == tutorial_stage.tutorial_entertainment) {
        building_menu_update(step);
    } else if (step == tutorial_stage.tutorial_industry) {
        building_menu_update(step);
        post_message(MESSAGE_TUTORIAL_INDUSTRY);
    } else if (step == tutorial_stage.tutorial_health) {
        building_menu_update(step);
        post_message(MESSAGE_TUTORIAL_BASIC_HEALTHCARE);
    } else if (step == tutorial_stage.tutorial_gardens) {
        building_menu_update(step);
        post_message(MESSAGE_TUTORIAL_MUNICIPAL_STRUCTURES);
    }
}

void tutorial_flags_t::update_starting_message() {
    if (!g_scenario_data.meta.start_message_shown) {
        if (g_scenario_data.meta.start_message) {
            post_message(g_scenario_data.meta.start_message);
        }
        g_scenario_data.meta.start_message_shown = true;
    }

    if (scenario_is_mission_rank(1) && !g_tutorials_flags.tutorial_1.started) {
        g_tutorials_flags.tutorial_1.started = 1;
    }
    if (scenario_is_mission_rank(2) && !g_tutorials_flags.tutorial_2.started) {
        g_tutorials_flags.tutorial_2.started = 1;
    }
    if (scenario_is_mission_rank(3) && !g_tutorials_flags.tutorial_3.started) {
        g_tutorials_flags.tutorial_3.started = 1;
    }
    if (scenario_is_mission_rank(4) && !g_tutorials_flags.tutorial_4.started) {
        post_message(MESSAGE_TUTORIAL_DEVELOPING_CULTURE);
        g_tutorials_flags.tutorial_4.started = 1;
    }
    if (scenario_is_mission_rank(5) && !g_tutorials_flags.tutorial_5.started) {
        post_message(MESSAGE_TUTORIAL_GETTING_STARTED);
        g_tutorials_flags.tutorial_5.started = 1;
    }
    if (scenario_is_mission_rank(6) && !g_tutorials_flags.tutorial_6.started) {
        g_tutorials_flags.tutorial_6.started = 1;
    }

    if (scenario_is_mission_rank(7) && !g_tutorials_flags.pharaoh.tut7_start) {
        if (scenario_campaign_scenario_id() == 6)
            post_message(MESSAGE_TUTORIAL_AT_WATERS_EDGE);
        else
            post_message(MESSAGE_TUTORIAL_AT_WATERS_EDGE_2);
        g_tutorials_flags.pharaoh.tut7_start = 1;
    }

    if (scenario_is_mission_rank(8) && !g_tutorials_flags.pharaoh.tut8_start) {
        post_message(MESSAGE_TUTORIAL_THE_FINER_THINGS);
        g_tutorials_flags.pharaoh.tut8_start = 1;
    }
}

void tutorial_on_day_tick() {
    if (scenario_is_mission_rank(1) && g_tutorials_flags.tutorial_1.fire) {
        city_mission_tutorial_set_fire_message_shown(1);
    }

    if (scenario_is_mission_rank(1)) {
        if (!g_tutorials_flags.tutorial_1.population_150_reached && city_population() >= 150) {
            g_tutorials_flags.tutorial_1.population_150_reached = 1;
            building_menu_update(tutorial_stage.tutorial_food);
            post_message(MESSAGE_TUTORIAL_FOOD_OR_FAMINE);
        }
    }

    tutorial_check_resources_on_storageyard();
}

void tutorial_on_month_tick() {
    if (scenario_is_mission_rank(3)) {
        if (game.simtime.month == 5) {
            city_message_post_with_message_delay(MESSAGE_CAT_TUTORIAL3, 1, MESSAGE_TUTORIAL_HUNGER_HALTS_IMMIGRANTS, 1200);
        }
    }
}

io_buffer* iob_tutorial_flags = new io_buffer([](io_buffer* iob, size_t version) {
    // tut 1
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_1.fire);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_1.population_150_reached);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_1.gamemeat_400_stored);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_1.collapse);
    // tut 2
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_2.gold_mined_500);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_2.temples_built);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_2.crime); 
    // tut 3
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_3.figs_800_stored);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[8]); // ????
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_3.pottery_made);
    // tut 4
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_4.beer_made);
    // tut 5
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_5.spacious_apartment);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_5.papyrus_made);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_5.bricks_bought);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[14]);

    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_1.started);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_2.started);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_3.started);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_4.started);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_5.started);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_6.started);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.tut7_start);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.tut8_start);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[23]);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[24]);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[25]);

    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[26]); // goal: bazaar
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[27]); // goal: pottery
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[28]);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[29]);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[30]); // tut4 ???
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[31]);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[32]);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[33]); // goal: water supply
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[34]); // tut4 ???
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[35]);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[36]); // goal: entertainment
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[37]); // goal: temples
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[38]);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[39]);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[40]);
});