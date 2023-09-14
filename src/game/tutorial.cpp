#include "tutorial.h"

#include "building/menu.h"
#include "city/buildings.h"
#include "city/message.h"
#include "city/mission.h"
#include "city/population.h"
#include "city/resource.h"
#include "empire/city.h"
#include "game/resource.h"
#include "game/time.h"
#include "io/io_buffer.h"
#include "platform/arguments.h"
#include "scenario/criteria.h"
#include "scenario/property.h"
#include "city/sentiment.h"

#include <algorithm>

static tutorial_flags_t g_tutorials_flags;

const tutorial_flags_t* tutorial_flags_struct() {
    return &g_tutorials_flags;
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

    // tutorial 2
    g_tutorials_flags.tutorial_2.gold_mined_500 = 0;
    g_tutorials_flags.tutorial_2.temples_built = 0;

    // tutorial 3
    g_tutorials_flags.tutorial_3.figs_800_stored = 0;
    g_tutorials_flags.tutorial_3.pottery_made = 0;

    g_tutorials_flags.tutorial_4.beer_made = 0;
    g_tutorials_flags.pharaoh.spacious_apartment = 0;

    g_tutorials_flags.pharaoh.papyrus_made = 0;
    g_tutorials_flags.pharaoh.bricks_bought = 0;

    g_tutorials_flags.pharaoh.tut1_start = 0;
    g_tutorials_flags.pharaoh.tut3_start = 0;
    g_tutorials_flags.pharaoh.tut4_start = 0;
    g_tutorials_flags.pharaoh.tut5_start = 0;
    g_tutorials_flags.pharaoh.tut6_start = 0;
    g_tutorials_flags.pharaoh.tut7_start = 0;
    g_tutorials_flags.pharaoh.tut8_start = 0;

    for (int i = 0; i < 41; i++) {
        g_tutorials_flags.pharaoh.flags[i] = 0;
    }
}

void tutorial_init(void) {
    set_all_tut_flags_null();

    if (scenario_is_custom())
        return;

    int scenario_id = scenario_campaign_scenario_id();
    bool tut_passed[10];

    for (int i = 0; i < 10; ++i) {
        tut_passed[i] = (i > scenario_id);
    }

    // tut1
    g_tutorials_flags.tutorial_1.fire = tut_passed[0];
    g_tutorials_flags.tutorial_1.collapse = tut_passed[0];
    g_tutorials_flags.tutorial_1.population_150_reached = tut_passed[0];
    g_tutorials_flags.tutorial_1.gamemeat_400_stored = tut_passed[0];
    // tut2
    g_tutorials_flags.tutorial_2.gold_mined_500 = tut_passed[1];
    g_tutorials_flags.tutorial_2.temples_built = tut_passed[1];
    g_tutorials_flags.tutorial_2.crime = tut_passed[1];
    // tut3
    g_tutorials_flags.tutorial_3.pottery_made = tut_passed[2];
    g_tutorials_flags.tutorial_3.figs_800_stored = tut_passed[2];
    g_tutorials_flags.tutorial_3.disease = tut_passed[2];
    // tut4
    g_tutorials_flags.tutorial_4.beer_made = tut_passed[3];

    g_tutorials_flags.pharaoh.flags[8] = tut_passed[4];
    g_tutorials_flags.pharaoh.spacious_apartment = tut_passed[4];
    g_tutorials_flags.pharaoh.papyrus_made = tut_passed[4];
    g_tutorials_flags.pharaoh.bricks_bought = tut_passed[4];

    //
    g_tutorials_flags.pharaoh.tut1_start = tut_passed[0];
    g_tutorials_flags.pharaoh.tut2_start = tut_passed[1];
    g_tutorials_flags.pharaoh.tut3_start = tut_passed[2];
    g_tutorials_flags.pharaoh.tut4_start = tut_passed[3];
    g_tutorials_flags.pharaoh.tut5_start = tut_passed[4];
    g_tutorials_flags.pharaoh.tut6_start = tut_passed[5];
    g_tutorials_flags.pharaoh.tut7_start = tut_passed[6];
    g_tutorials_flags.pharaoh.tut8_start = tut_passed[7];
    //
    g_tutorials_flags.pharaoh.flags[26] = tut_passed[0];
    g_tutorials_flags.pharaoh.flags[27] = tut_passed[2];

    g_tutorials_flags.pharaoh.flags[30] = tut_passed[3];

    g_tutorials_flags.pharaoh.flags[33] = tut_passed[0];
    g_tutorials_flags.pharaoh.flags[34] = tut_passed[3];

    g_tutorials_flags.pharaoh.flags[36] = tut_passed[1];
    g_tutorials_flags.pharaoh.flags[37] = tut_passed[1];
    g_tutorials_flags.pharaoh.flags[38] = tut_passed[3];
    g_tutorials_flags.pharaoh.flags[39] = tut_passed[3];


    tutorial_menu_update(scenario_id + 1);
}

e_availability mission_advisor_availability(e_advisor advisor, int tutorial) {
    auto is_available = [advisor] (const std::initializer_list<e_advisor> &advisors) {
        return (std::find(advisors.begin(), advisors.end(), advisor) != advisors.end())
                      ? AVAILABLE 
                      : NOT_AVAILABLE;
    };

    switch (tutorial) {
    case 1: return NOT_AVAILABLE;
    case 2: return is_available({ADVISOR_TRADE, ADVISOR_ENTERTAINMENT, ADVISOR_RELIGION});
    case 3: return is_available({ADVISOR_LABOR, ADVISOR_TRADE, ADVISOR_ENTERTAINMENT, ADVISOR_RELIGION});
    case 4: return is_available({ADVISOR_LABOR, ADVISOR_TRADE, ADVISOR_ENTERTAINMENT, ADVISOR_RELIGION, ADVISOR_FINANCIAL});
    case 5: return is_available({ADVISOR_LABOR, ADVISOR_TRADE, ADVISOR_ENTERTAINMENT, ADVISOR_RELIGION, ADVISOR_FINANCIAL});
    }

    return AVAILABLE;
}

e_availability mission_empire_availability() {
    if (scenario_is_tutorial_before_mission_5())
        return NOT_AVAILABLE;
    // TODO
    //    else if (!g_tutorials_flags.pharaoh.tut5_can_trade_finally)
    //        return NOT_AVAILABLE_YET;
    //    else
    return AVAILABLE;
}

void tutorial_menu_update(int tut) {
    if (tut == 1) {
        building_menu_update(BUILDSET_TUT1_START);
            
        if (g_tutorials_flags.tutorial_1.population_150_reached)  building_menu_update(BUILDSET_TUT1_FOOD);
        if (g_tutorials_flags.tutorial_1.fire) building_menu_update(BUILDSET_TUT1_FIRE_PH);
        if (g_tutorials_flags.tutorial_1.collapse) building_menu_update(BUILDSET_TUT1_COLLAPSE_PH);
        if (g_tutorials_flags.tutorial_1.gamemeat_400_stored) building_menu_update(BUILDSET_TUT1_WATER);
    } else if (tut == 2) {
        building_menu_update(BUILDSET_TUT2_START);

        if (g_tutorials_flags.tutorial_2.gold_mined_500) building_menu_update(BUILDSET_TUT2_GODS);
        if (g_tutorials_flags.tutorial_2.temples_built) building_menu_update(BUILDSET_TUT2_ENTERTAINMENT);
    } else if (tut == 3) {
        building_menu_update(BUILDSET_TUT3_START);
            
        if (g_tutorials_flags.tutorial_3.figs_800_stored) building_menu_update(BUILDSET_TUT3_INDUSTRY);
        if (g_tutorials_flags.tutorial_3.pottery_made) building_menu_update(BUILDSET_TUT3_INDUSTRY);
        if (g_tutorials_flags.tutorial_3.disease) building_menu_update(BUILDSET_TUT3_HEALTH);
        if (g_tutorials_flags.tutorial_3.pottery_made) building_menu_update(BUILDSET_TUT3_GARDENS);
    } else if (tut == 4) {
        building_menu_update(BUILDSET_TUT4_START);

        if (g_tutorials_flags.tutorial_4.beer_made) building_menu_update(BUILDSET_TUT4_FINANCE);
    } else if (tut == 5) {
        building_menu_update(BUILDSET_TUT5_START);
        if (g_tutorials_flags.pharaoh.spacious_apartment) building_menu_update(BUILDSET_TUT5_EDUCATION);
        if (g_tutorials_flags.pharaoh.papyrus_made) building_menu_update(BUILDSET_TUT5_TRADING);
        if (g_tutorials_flags.pharaoh.bricks_bought) building_menu_update(BUILDING_MENU_MONUMENTS);
    } else if (tut == 6) {
        building_menu_update(BUILDSET_TUT6_START);
    } else if (tut == 7) {
        building_menu_update(BUILDSET_TUT7_START);
    } else if (tut == 8) {
        building_menu_update(BUILDSET_TUT8_START);
    }
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
    //if (GAME_ENV == ENGINE_ENV_C3) {
    //    if (scenario_is_mission_rank(1)) {
    //        if (!g_tutorials_flags.tutorial1.fire && !g_tutorials_flags.tutorial1.crime)
    //            return 17;
    //        else if (!g_tutorials_flags.tutorial1.collapse)
    //            return 18;
    //        else if (!g_tutorials_flags.tutorial1.senate_built)
    //            return 19;
    //        else
    //            return 20;
    //    } else if (scenario_is_mission_rank(2)) {
    //        if (!g_tutorials_flags.tutorial2.granary_built)
    //            return 21;
    //        else if (!g_tutorials_flags.tutorial2.population_250_reached)
    //            return 22;
    //        else if (!g_tutorials_flags.tutorial2.population_450_reached)
    //            return 23;
    //        else if (!g_tutorials_flags.tutorial2.pottery_made)
    //            return 24;
    //        else
    //            return 25;
    //    }
    //    return 0;
    //} else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
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
        if (!g_tutorials_flags.pharaoh.spacious_apartment)
            return 31;
        else if (!g_tutorials_flags.pharaoh.papyrus_made)
            return 30;
        else if (!g_tutorials_flags.pharaoh.bricks_bought)
            return 29;
        else
            return 34;
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
int tutorial_handle_fire(void) {
    if (g_tutorials_flags.tutorial_1.fire)
        return 0;

    g_tutorials_flags.tutorial_1.fire = 1;
    building_menu_update(BUILDSET_TUT1_FIRE_PH);
    post_message(MESSAGE_TUTORIAL_FIRE_IN_THE_VILLAGE);
    return 1;
}
int tutorial_handle_collapse(void) {
    if (g_tutorials_flags.tutorial_1.collapse)
        return 0;

    g_tutorials_flags.tutorial_1.collapse = 1;
    building_menu_update(BUILDSET_TUT1_COLLAPSE_PH);
    post_message(MESSAGE_TUTORIAL_COLLAPSED_BUILDING);
    return 1;
}

void tutorial_on_crime(void) {
    if (!g_tutorials_flags.pharaoh.crime) {
        g_tutorials_flags.pharaoh.crime = 1;
        building_menu_update(BUILDSET_TUT1_CRIME);
    }
}
void tutorial_on_disease(void) {
    g_tutorials_flags.tutorial_3.disease = true;
}
void tutorial_on_filled_granary(int quantity) {
    if (scenario_is_mission_rank(1) && !g_tutorials_flags.tutorial_1.gamemeat_400_stored && quantity >= 400) {
        g_tutorials_flags.tutorial_1.gamemeat_400_stored = 1;
        building_menu_update(BUILDSET_TUT1_WATER);
        post_message(MESSAGE_TUTORIAL_CLEAN_WATER);
    }

    if (scenario_is_mission_rank(3) && !g_tutorials_flags.tutorial_3.figs_800_stored && quantity >= 800) {
        g_tutorials_flags.tutorial_3.figs_800_stored = 1;
        building_menu_update(BUILDSET_TUT3_INDUSTRY);
        post_message(MESSAGE_TUTORIAL_INDUSTRY);
    }
}
void tutorial_on_add_to_storageyard() {
    if (!g_tutorials_flags.tutorial_3.pottery_made && city_resource_count(RESOURCE_POTTERY) >= 1) {
        g_tutorials_flags.tutorial_3.pottery_made = true;
        g_tutorials_flags.tutorial_3.pottery_made_year = game_time_year();
        building_menu_update(BUILDSET_NORMAL);
        post_message(MESSAGE_TUTORIAL_TRADE);
    } else if (!g_tutorials_flags.tutorial_3.pottery_made && city_resource_count(RESOURCE_POTTERY) >= 2) {
        g_tutorials_flags.tutorial_3.pottery_made = true;
        building_menu_update(BUILDSET_TUT3_GARDENS);
        post_message(MESSAGE_TUTORIAL_MUNICIPAL_STRUCTURES);
    } else if (!g_tutorials_flags.tutorial_4.beer_made && city_resource_count(RESOURCE_BEER) >= 3) {
        g_tutorials_flags.tutorial_4.beer_made = true;
        building_menu_update(BUILDSET_TUT4_FINANCE);
        post_message(MESSAGE_TUTORIAL_FINANCES);
    } if (!g_tutorials_flags.pharaoh.papyrus_made && city_resource_count(RESOURCE_PAPYRUS) >= 1) {
        g_tutorials_flags.pharaoh.papyrus_made = 1;
        //            building_menu_update(BUILDSET_TUT5_TRADING);
        post_message(MESSAGE_TUTORIAL_TRADE_WITH_OTHER_CITIES);
    } if (!g_tutorials_flags.pharaoh.bricks_bought && city_resource_count(RESOURCE_BRICKS) >= 1) {
        g_tutorials_flags.pharaoh.bricks_bought = 1;
        building_menu_update(BUILDSET_TUT5_MONUMENTS);
        post_message(MESSAGE_TUTORIAL_MONUMENTS);
    }
}
void tutorial_on_gold_extracted() {
    if (scenario_is_mission_rank(2) && !g_tutorials_flags.tutorial_2.gold_mined_500) {
        g_tutorials_flags.tutorial_2.gold_mined_500 = true;
        building_menu_update(BUILDSET_TUT2_GODS);
        post_message(MESSAGE_TUTORIAL_GODS_OF_EGYPT);
    }
}
void tutorial_on_religion() {
    if (!g_tutorials_flags.tutorial_2.temples_built) {
        g_tutorials_flags.tutorial_2.temples_built = true;
        building_menu_update(BUILDSET_TUT2_ENTERTAINMENT);
        post_message(MESSAGE_TUTORIAL_ENTERTAINMENT);
    }
}
void tutorial_on_house_evolve(int level) {
    if (!g_tutorials_flags.pharaoh.spacious_apartment && level == 9) {
        g_tutorials_flags.pharaoh.spacious_apartment = 1;
        building_menu_update(BUILDSET_TUT5_EDUCATION);
        post_message(MESSAGE_TUTORIAL_EDUCATION);
    }
}
void tutorial_starting_message() {
    if (scenario_is_mission_rank(1) && !g_tutorials_flags.pharaoh.tut1_start) {
        post_message(MESSAGE_TUTORIAL_HOUSING_AND_ROADS);
        g_tutorials_flags.pharaoh.tut1_start = 1;
    }
    if (scenario_is_mission_rank(2) && !g_tutorials_flags.pharaoh.tut2_start) {
        post_message(MESSAGE_TUTORIAL_GOLD_AND_CRIME);
        g_tutorials_flags.pharaoh.tut2_start = 1;
    }
    if (scenario_is_mission_rank(3) && !g_tutorials_flags.pharaoh.tut3_start) {
        post_message(MESSAGE_TUTORIAL_FARMING_ALONG_THE_NILE);
        g_tutorials_flags.pharaoh.tut3_start = 1;
    }
    if (scenario_is_mission_rank(4) && !g_tutorials_flags.pharaoh.tut4_start) {
        post_message(MESSAGE_TUTORIAL_DEVELOPING_CULTURE);
        g_tutorials_flags.pharaoh.tut4_start = 1;
    }
    if (scenario_is_mission_rank(5) && !g_tutorials_flags.pharaoh.tut5_start) {
        post_message(MESSAGE_TUTORIAL_GETTING_STARTED);
        g_tutorials_flags.pharaoh.tut5_start = 1;
    }
    if (scenario_is_mission_rank(6) && !g_tutorials_flags.pharaoh.tut6_start) {
        post_message(MESSAGE_TUTORIAL_SOLDIERS_AND_FORT);
        g_tutorials_flags.pharaoh.tut6_start = 1;
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
void tutorial_on_day_tick(void) {
    if (g_tutorials_flags.tutorial_1.fire) {
        city_mission_tutorial_set_fire_message_shown(1);
    }

    //if (GAME_ENV == ENGINE_ENV_C3) {
    //    if (g_tutorials_flags.tutorial3.disease && city_mission_tutorial_show_disease_message())
    //        post_message(MESSAGE_TUTORIAL_HEALTH);
    //    if (g_tutorials_flags.tutorial2.granary_built) {
    //        if (!g_tutorials_flags.tutorial2.population_250_reached && city_population() >= 250) {
    //            g_tutorials_flags.tutorial2.population_250_reached = 1;
    //            building_menu_update(BUILDSET_TUT2_UP_TO_450);
    //            post_message(MESSAGE_TUTORIAL_GROWING_YOUR_CITY);
    //        }
    //    }
    //    if (g_tutorials_flags.tutorial2.population_250_reached) {
    //        if (!g_tutorials_flags.tutorial2.population_450_reached && city_population() >= 450) {
    //            g_tutorials_flags.tutorial2.population_450_reached = 1;
    //            building_menu_update(BUILDSET_TUT2_AFTER_450);
    //            post_message(MESSAGE_TUTORIAL_TAXES_INDUSTRY);
    //        }
    //    }
    //    if (g_tutorials_flags.tutorial1.fire && !g_tutorials_flags.tutorial1.senate_built) {
    //        int population_almost = city_population() >= winning_population() - 20;
    //        if (!game_time_day() || population_almost) {
    //            if (city_buildings_has_palace())
    //                city_mission_tutorial_add_senate();
    //            if (city_mission_tutorial_has_senate() || population_almost) {
    //                g_tutorials_flags.tutorial1.senate_built = 1;
    //                building_menu_update(BUILDSET_NORMAL);
    //                post_message(MESSAGE_TUTORIAL_RELIGION);
    //            }
    //        }
    //    }
    //} else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
    if (scenario_is_mission_rank(1)) {
        if (!g_tutorials_flags.tutorial_1.population_150_reached && city_population() >= 150) {
            g_tutorials_flags.tutorial_1.population_150_reached = 1;
            building_menu_update(BUILDSET_TUT1_FOOD);
            post_message(MESSAGE_TUTORIAL_FOOD_OR_FAMINE);
        }
    }
}
void tutorial_on_month_tick(void) {
    if (scenario_is_mission_rank(3)) {
        if (game_time_month() == 5)
            city_message_post_with_message_delay(MESSAGE_CAT_TUTORIAL3,
                                                 1,
                                                 MESSAGE_TUTORIAL_HUNGER_HALTS_IMMIGRANTS,
                                                 1200);
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
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.spacious_apartment);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[12]);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[13]);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.flags[14]);

    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.tut1_start);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.tut2_start);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.tut3_start);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.tut4_start);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.tut5_start);
    iob->bind(BIND_SIGNATURE_UINT8, &g_tutorials_flags.pharaoh.tut6_start);
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