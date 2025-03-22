#include "tutorial.h"

#include "building/building_menu.h"
#include "building/building_granary.h"
#include "city/buildings.h"
#include "city/city.h"
#include "city/message.h"
#include "city/city_population.h"
#include "city/city_resource.h"
#include "empire/empire_city.h"
#include "game/resource.h"
#include "io/io_buffer.h"
#include "platform/arguments.h"
#include "scenario/criteria.h"
#include "scenario/scenario.h"
#include "game/game.h"
#include "io/gamefiles/lang.h"

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
    tutorial_1::reset();
    tutorial_2::reset();
    tutorial_3::reset();
    tutorial_4::reset();
    tutorial_5::reset();

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

int tutorial_3_adjust_request_year(int *year) {
    if (scenario_is_mission_rank(2)) {
        //if (!g_tutorials_flags.tutorial_3.pottery_made) {
        //    return 0;
        //}

        *year = g_tutorials_flags.tutorial_3.pottery_made_year;
    }
    return 1;
}

bool tutorial_menu_update(int tut) {
    if (tut == 1) {
        tutorial_1::init();
        return true;
    } 
    
    if (tut == 2) {
        tutorial_2::init();
        return true;
    } 
    
    if (tut == 3) {
        tutorial_3::init();
        return true;
    } 
    
    if (tut == 4) {
        tutorial_4::init();
        return true;
    } 
    
    if (tut == 5) {
        tutorial_5::init();
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

xstring tutorial_get_immediate_goal_text() {
    if (scenario_is_mission_rank(1))  return tutorial_1::goal_text();
    if (scenario_is_mission_rank(2))  return tutorial_2::goal_text();
    if (scenario_is_mission_rank(3))  return tutorial_3::goal_text();
    if (scenario_is_mission_rank(4))  return tutorial_4::goal_text();
    if (scenario_is_mission_rank(5))  return tutorial_5::goal_text();

    return "#unknown_tutoral_goal";
}

void tutorial_flags_t::on_crime() {
    if (!g_tutorials_flags.pharaoh.crime) {
        g_tutorials_flags.pharaoh.crime = 1;
        building_menu_update(tutorial_stage.tutorial_crime);
    }
}

void tutorial_update_step(xstring s) {
    tutorial_1::update_step(s);
    tutorial_2::update_step(s);
    tutorial_3::update_step(s);
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

io_buffer* iob_tutorial_flags = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_UINT16, &g_tutorials_flags.pharaoh.last_action);
    // tut 1
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_1.fire);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_1.population_150_reached);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_1.gamemeat_400_stored);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_1.collapse);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_1.architector_built);
    // tut 2
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_2.gold_mined_500);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_2.temples_built);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_2.crime); 
    // tut 3
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_3.figs_800_stored);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_3.pottery_made_1);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_3.pottery_made_2);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_3.disease);
    // tut 4
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_4.beer_made);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.tutorial_4.tax_collector_built);
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
});