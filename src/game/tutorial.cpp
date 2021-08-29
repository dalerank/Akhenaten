#include "tutorial.h"

#include "building/menu.h"
#include "city/buildings.h"
#include "city/message.h"
#include "city/mission.h"
#include "city/population.h"
#include "city/resource.h"
#include "game/resource.h"
#include "game/time.h"
#include "scenario/criteria.h"
#include "scenario/property.h"
#include "empire/city.h"

static tutorial_flags data;

tutorial_flags *give_me_da_tut_flags() {
    return &data;
}

static void post_message(int message) {
    city_message_post(true, message, 0, 0);
}

static void set_all_tut_flags_null() {
    data.pharaoh.fire = 0;
    data.pharaoh.population_150_reached = 0;
    data.pharaoh.gamemeat_400_stored = 0;
    data.pharaoh.collapse = 0;
    data.pharaoh.gold_mined_500 = 0;
    data.pharaoh.temples_built = 0;

    data.pharaoh.figs_800_stored = 0;

    data.pharaoh.pottery_made = 0;
    data.pharaoh.beer_made = 0;
    data.pharaoh.spacious_apartment = 0;

    data.pharaoh.papyrus_made = 0;
    data.pharaoh.bricks_bought = 0;

    data.pharaoh.tut1_start = 0;
    data.pharaoh.tut3_start = 0;
    data.pharaoh.tut4_start = 0;
    data.pharaoh.tut5_start = 0;
    data.pharaoh.tut6_start = 0;
    data.pharaoh.tut7_start = 0;
    data.pharaoh.tut8_start = 0;

    for (int i = 0; i < 41; i++)
        data.pharaoh.flags[i] = 0;
}

void tutorial_init(void) {
    set_all_tut_flags_null();

    int tut_passed[10];
    std::fill_n(tut_passed, 10, 1);

    for (int t = 1; t <= 10; t++) {
        if (scenario_is_tutorial(t))
            for (int i = t - 1; i < 10; i++)
                tut_passed[i] = 0;
    }

    if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        data.pharaoh.fire = tut_passed[0];
        data.pharaoh.collapse = tut_passed[0];
        data.pharaoh.disease = tut_passed[0];
        data.pharaoh.population_150_reached = tut_passed[0];
        data.pharaoh.gamemeat_400_stored = tut_passed[0];
        data.pharaoh.gold_mined_500 = tut_passed[1];
        data.pharaoh.temples_built = tut_passed[1];
        data.pharaoh.flags[6] = tut_passed[3];
        data.pharaoh.figs_800_stored = tut_passed[2];
        data.pharaoh.flags[8] = tut_passed[3];
        data.pharaoh.pottery_made = tut_passed[2];
        data.pharaoh.beer_made = tut_passed[3];
        data.pharaoh.spacious_apartment = tut_passed[4];

        data.pharaoh.papyrus_made = tut_passed[4];
        data.pharaoh.bricks_bought = tut_passed[4];

        //
        data.pharaoh.tut1_start = tut_passed[0];
        data.pharaoh.tut2_start = tut_passed[1];
        data.pharaoh.tut3_start = tut_passed[2];
        data.pharaoh.tut4_start = tut_passed[3];
        data.pharaoh.tut5_start = tut_passed[4];
        data.pharaoh.tut6_start = tut_passed[5];
        data.pharaoh.tut7_start = tut_passed[6];
        data.pharaoh.tut8_start = tut_passed[7];
        //
        data.pharaoh.flags[26] = tut_passed[0];
        data.pharaoh.flags[27] = tut_passed[2];

        data.pharaoh.flags[30] = tut_passed[3];

        data.pharaoh.flags[33] = tut_passed[0];
        data.pharaoh.flags[34] = tut_passed[3];

        data.pharaoh.flags[36] = tut_passed[1];
        data.pharaoh.flags[37] = tut_passed[1];
        data.pharaoh.flags[38] = tut_passed[3];
        data.pharaoh.flags[39] = tut_passed[3];

    } else if (GAME_ENV == ENGINE_ENV_C3) {
        data.tutorial1.fire = tut_passed[0];
        data.tutorial1.crime = tut_passed[0];
        data.tutorial1.collapse = tut_passed[0];
        data.tutorial1.senate_built = tut_passed[0];
        city_mission_tutorial_set_fire_message_shown(tut_passed[0]);

        data.tutorial2.granary_built = tut_passed[1];
        data.tutorial2.population_250_reached = tut_passed[1];
        data.tutorial2.population_450_reached = tut_passed[1];
        data.tutorial2.pottery_made = tut_passed[1];
        data.tutorial2.pottery_made_year = tut_passed[1];

        data.tutorial3.disease = tut_passed[2];
        city_mission_tutorial_set_disease_message_shown(tut_passed[2]);
    }
}

tutorial_availability tutorial_advisor_availability(void) {
    if (GAME_ENV == ENGINE_ENV_C3) {
        if (scenario_is_tutorial(1))
            return NOT_AVAILABLE;
        else if (scenario_is_tutorial(2) && !data.tutorial2.population_250_reached)
            return NOT_AVAILABLE_YET;
        else
            return AVAILABLE;
    }
    else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        if (scenario_is_tutorial(1))
            return NOT_AVAILABLE;
        else
            return AVAILABLE;
    }
}
tutorial_availability tutorial_empire_availability(void) {
    if (GAME_ENV == ENGINE_ENV_C3) {
        if (scenario_is_tutorial(1))
            return NOT_AVAILABLE;
        else if (scenario_is_tutorial(2) && !data.tutorial2.population_250_reached)
            return NOT_AVAILABLE_YET;
        else
            return AVAILABLE;
    }
    else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        if (scenario_is_tutorial_before_mission_5())
            return NOT_AVAILABLE;
        else if (!data.pharaoh.tut5_can_trade_finally)
            return NOT_AVAILABLE_YET;
        else
            return AVAILABLE;
    }
}

void tutorial_menu_update(int tut) {
    if (GAME_ENV == ENGINE_ENV_C3) {
        if (tut == 1) {
            building_menu_update(BUILDSET_TUT1_START);
            if (data.tutorial1.fire || data.tutorial1.crime)
                building_menu_update(BUILDSET_TUT1_FIRE_C3);
            if (data.tutorial1.collapse)
                building_menu_update(BUILDSET_TUT1_COLLAPSE_C3);
        } else if (tut == 2) {
            building_menu_update(BUILDSET_TUT2_START);
            if (data.tutorial2.granary_built)
                building_menu_update(BUILDSET_TUT2_UP_TO_250);
            if (data.tutorial2.population_250_reached)
                building_menu_update(BUILDSET_TUT2_UP_TO_450);
            if (data.tutorial2.population_450_reached)
                building_menu_update(BUILDSET_TUT2_AFTER_450);
        }
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        if (tut == 1) {
            building_menu_update(BUILDSET_TUT1_START);
            if (data.pharaoh.population_150_reached)
                building_menu_update(BUILDSET_TUT1_FOOD);
            if (data.pharaoh.fire)
                building_menu_update(BUILDSET_TUT1_FIRE_PH);
            if (data.pharaoh.collapse)
                building_menu_update(BUILDSET_TUT1_COLLAPSE_PH);
            if (data.pharaoh.gamemeat_400_stored)
                building_menu_update(BUILDSET_TUT1_WATER);
        } else if (tut == 2) {
            building_menu_update(BUILDSET_TUT2_START);
            if (data.pharaoh.gold_mined_500)
                building_menu_update(BUILDSET_TUT2_GODS);
            if (data.pharaoh.temples_built)
                building_menu_update(BUILDSET_TUT2_ENTERTAINMENT);
        } else if (tut == 3) {
            building_menu_update(BUILDSET_TUT3_START);
            if (data.pharaoh.figs_800_stored)
                building_menu_update(BUILDSET_TUT3_INDUSTRY);
            if (data.pharaoh.pottery_made)
                building_menu_update(BUILDSET_TUT3_INDUSTRY);
            if (data.pharaoh.disease)
                building_menu_update(BUILDSET_TUT3_HEALTH);
        } else if (tut == 4) {
            building_menu_update(BUILDSET_TUT4_START);
            if (data.pharaoh.beer_made)
                building_menu_update(BUILDSET_TUT4_FINANCE);
        } else if (tut == 5) {
            building_menu_update(BUILDSET_TUT5_START);
            if (data.pharaoh.spacious_apartment)
                building_menu_update(BUILDSET_TUT5_EDUCATION);
            if (data.pharaoh.papyrus_made)
                building_menu_update(BUILDSET_TUT5_TRADING);
            if (data.pharaoh.bricks_bought)
                building_menu_update(BUILDING_MENU_MONUMENTS);
        } else if (tut == 6) {
            building_menu_update(BUILDSET_TUT6_START);
        } else if (tut == 7) {
            building_menu_update(BUILDSET_TUT7_START);
        } else if (tut == 8) {
            building_menu_update(BUILDSET_TUT8_START);
        }
    }
}

int tutorial_get_population_cap(int current_cap) {
    return current_cap; //temp
    if (scenario_is_tutorial(1)) {
        if (!data.tutorial1.fire ||
            !data.tutorial1.collapse ||
            !data.tutorial1.senate_built) {
            return 80;
        }
    } else if (scenario_is_tutorial(2)) {
        if (!data.tutorial2.granary_built)
            return 150;
        else if (!data.tutorial2.pottery_made)
            return 520;

    }
    return current_cap;
}
int tutorial_get_immediate_goal_text(void) {
    if (GAME_ENV == ENGINE_ENV_C3) {
        if (scenario_is_tutorial(1)) {
            if (!data.tutorial1.fire && !data.tutorial1.crime)
                return 17;
            else if (!data.tutorial1.collapse)
                return 18;
            else if (!data.tutorial1.senate_built)
                return 19;
            else
                return 20;
        } else if (scenario_is_tutorial(2)) {
            if (!data.tutorial2.granary_built)
                return 21;
            else if (!data.tutorial2.population_250_reached)
                return 22;
            else if (!data.tutorial2.population_450_reached)
                return 23;
            else if (!data.tutorial2.pottery_made)
                return 24;
            else
                return 25;
        }
        return 0;
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        if (scenario_is_tutorial(1)) {
            if (!data.pharaoh.population_150_reached)
                return 21;
            else if (!data.pharaoh.gamemeat_400_stored)
                return 19;
            else
                return 20;
        } else if (scenario_is_tutorial(2)) {
            if (!data.pharaoh.gold_mined_500)
                return 24;
            else if (!data.pharaoh.temples_built)
                return 23;
            else
                return 22;
        } else if (scenario_is_tutorial(3)) {
            if (!data.pharaoh.figs_800_stored)
                return 28;
            else if (!data.pharaoh.pottery_made)
                return 27;
            else
                return 26;
        } else if (scenario_is_tutorial(4)) {
            if (!data.pharaoh.beer_made)
                return 33;
        } else if (scenario_is_tutorial(5)) {
            if (!data.pharaoh.spacious_apartment)
                return 31;
            else if (!data.pharaoh.papyrus_made)
                return 30;
            else if (!data.pharaoh.bricks_bought)
                return 29;
            else
                return 34;
        }
        return 0;
    }
}
int tutorial_adjust_request_year(int *year) {
    if (scenario_is_tutorial(2)) {
        if (!data.tutorial2.pottery_made)
            return 0;

        *year = data.tutorial2.pottery_made_year;
    }
    return 1;
}
int tutorial_extra_fire_risk(void) {
    return !data.tutorial1.fire &&
        scenario_is_tutorial(1); // Fix for extra fire risk in late tutorials
}
int tutorial_extra_damage_risk(void) {
    return data.tutorial1.fire &&
        !data.tutorial1.collapse &&
        scenario_is_tutorial(1); // Fix for extra damage risk in late tutorials
}
int tutorial_handle_fire(void) {
    if (data.tutorial1.fire || data.pharaoh.fire)
        return 0;

    data.tutorial1.fire = 1;
    data.pharaoh.fire = 1;
    if (GAME_ENV == ENGINE_ENV_C3) {
        building_menu_update(BUILDSET_TUT1_FIRE_C3);
        post_message(MESSAGE_TUTORIAL_FIRE);
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        building_menu_update(BUILDSET_TUT1_FIRE_PH);
        post_message(MESSAGE_TUTORIAL_FIRE_IN_THE_VILLAGE);
    }
    return 1;
}
int tutorial_handle_collapse(void) {
    if (data.tutorial1.collapse || data.pharaoh.collapse)
        return 0;

    data.tutorial1.collapse = 1;
    data.pharaoh.collapse = 1;
    if (GAME_ENV == ENGINE_ENV_C3) {
        building_menu_update(BUILDSET_TUT1_COLLAPSE_C3);
        post_message(MESSAGE_TUTORIAL_COLLAPSE);
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        building_menu_update(BUILDSET_TUT1_COLLAPSE_PH);
        post_message(MESSAGE_TUTORIAL_COLLAPSED_BUILDING);
    }
    return 1;
}

void tutorial_on_crime(void) {
    if (!data.tutorial1.crime) {
        data.tutorial1.crime = 1;
        building_menu_update(BUILDSET_TUT1_CRIME);
    }
}
void tutorial_on_disease(void) {
    data.tutorial3.disease = 1;
}
void tutorial_on_filled_granary(int quantity) {
    if (GAME_ENV == ENGINE_ENV_C3 && !data.tutorial2.granary_built && quantity > 400) {
        data.tutorial2.granary_built = 1;
        building_menu_update(BUILDSET_TUT2_UP_TO_250);
        post_message(MESSAGE_TUTORIAL_WATER);
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        if (scenario_is_tutorial(1) && !data.pharaoh.gamemeat_400_stored && quantity >= 400) {
            data.pharaoh.gamemeat_400_stored = 1;
            building_menu_update(BUILDSET_TUT1_WATER);
            post_message(MESSAGE_TUTORIAL_CLEAN_WATER);
        }
        if (scenario_is_tutorial(3) && !data.pharaoh.figs_800_stored && quantity >= 800) {
            data.pharaoh.figs_800_stored = 1;
            building_menu_update(BUILDSET_TUT3_INDUSTRY);
            post_message(MESSAGE_TUTORIAL_INDUSTRY);
        }
    }
}
void tutorial_on_add_to_warehouse(void) {
    if (!data.tutorial2.pottery_made && city_resource_count(RESOURCE_POTTERY_C3) >= 1) {
        data.tutorial2.pottery_made = 1;
        data.tutorial2.pottery_made_year = game_time_year();
        building_menu_update(BUILDSET_NORMAL);
        post_message(MESSAGE_TUTORIAL_TRADE);
    }
    else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        if (!data.pharaoh.pottery_made && city_resource_count(RESOURCE_POTTERY_PH) >= 2) {
            data.pharaoh.pottery_made = 1;
            building_menu_update(BUILDSET_TUT3_GARDENS);
            post_message(MESSAGE_TUTORIAL_MUNICIPAL_STRUCTURES);
        }
        if (!data.pharaoh.beer_made && city_resource_count(RESOURCE_BEER) >= 3) {
            data.pharaoh.beer_made = 1;
            building_menu_update(BUILDSET_TUT4_FINANCE);
            post_message(MESSAGE_TUTORIAL_FINANCES);
        }
        if (!data.pharaoh.papyrus_made && city_resource_count(RESOURCE_PAPYRUS) >= 1) {
            data.pharaoh.papyrus_made = 1;
//            building_menu_update(BUILDSET_TUT5_TRADING);
            post_message(MESSAGE_TUTORIAL_TRADE_WITH_OTHER_CITIES);
        }
        if (!data.pharaoh.bricks_bought && city_resource_count(RESOURCE_BRICKS) >= 1) {
            data.pharaoh.bricks_bought = 1;
            building_menu_update(BUILDSET_TUT5_MONUMENTS);
            post_message(MESSAGE_TUTORIAL_MONUMENTS);
        }
    }
}
void tutorial_on_gold_extracted() {
    if (!data.pharaoh.gold_mined_500) {
        data.pharaoh.gold_mined_500 = 1;
        building_menu_update(BUILDSET_TUT2_GODS);
        post_message(MESSAGE_TUTORIAL_GODS_OF_EGYPT);
    }
}
void tutorial_on_religion() {
    if (!data.pharaoh.temples_built) {
        data.pharaoh.temples_built = 1;
        building_menu_update(BUILDSET_TUT2_ENTERTAINMENT);
        post_message(MESSAGE_TUTORIAL_ENTERTAINMENT);
    }
}
void tutorial_on_house_evolve(int level) {
    if (!data.pharaoh.spacious_apartment && level == 9) {
        data.pharaoh.spacious_apartment = 1;
        building_menu_update(BUILDSET_TUT5_EDUCATION);
        post_message(MESSAGE_TUTORIAL_EDUCATION);
    }
}
void tutorial_starting_message() {
    if (scenario_is_tutorial(1) && !data.pharaoh.tut1_start) {
        post_message(MESSAGE_TUTORIAL_HOUSING_AND_ROADS);
        data.pharaoh.tut1_start = 1;
    }
    if (scenario_is_tutorial(2) && !data.pharaoh.tut2_start) {
        post_message(MESSAGE_TUTORIAL_GOLD_AND_CRIME);
        data.pharaoh.tut2_start = 1;
    }
    if (scenario_is_tutorial(3) && !data.pharaoh.tut3_start) {
        post_message(MESSAGE_TUTORIAL_FARMING_ALONG_THE_NILE);
        data.pharaoh.tut3_start = 1;
    }
    if (scenario_is_tutorial(4) && !data.pharaoh.tut4_start) {
        post_message(MESSAGE_TUTORIAL_DEVELOPING_CULTURE);
        data.pharaoh.tut4_start = 1;
    }
    if (scenario_is_tutorial(5) && !data.pharaoh.tut5_start) {
        post_message(MESSAGE_TUTORIAL_GETTING_STARTED);
        data.pharaoh.tut5_start = 1;
    }
    if (scenario_is_tutorial(6) && !data.pharaoh.tut6_start) {
        post_message(MESSAGE_TUTORIAL_SOLDIERS_AND_FORT);
        data.pharaoh.tut6_start = 1;
    }
    if (scenario_is_tutorial(7) && !data.pharaoh.tut7_start) {
        if (scenario_campaign_mission() == 6)
            post_message(MESSAGE_TUTORIAL_AT_WATERS_EDGE);
        else
            post_message(MESSAGE_TUTORIAL_AT_WATERS_EDGE_2);
        data.pharaoh.tut7_start = 1;
    }
    if (scenario_is_tutorial(8) && !data.pharaoh.tut8_start) {
        post_message(MESSAGE_TUTORIAL_THE_FINER_THINGS);
        data.pharaoh.tut8_start = 1;
    }
}
void tutorial_on_day_tick(void) {
    if (data.tutorial1.fire || data.pharaoh.fire)
        city_mission_tutorial_set_fire_message_shown(1);

    if (GAME_ENV == ENGINE_ENV_C3) {
        if (data.tutorial3.disease && city_mission_tutorial_show_disease_message())
            post_message(MESSAGE_TUTORIAL_HEALTH);
        if (data.tutorial2.granary_built) {
            if (!data.tutorial2.population_250_reached && city_population() >= 250) {
                data.tutorial2.population_250_reached = 1;
                building_menu_update(BUILDSET_TUT2_UP_TO_450);
                post_message(MESSAGE_TUTORIAL_GROWING_YOUR_CITY);
            }
        }
        if (data.tutorial2.population_250_reached) {
            if (!data.tutorial2.population_450_reached && city_population() >= 450) {
                data.tutorial2.population_450_reached = 1;
                building_menu_update(BUILDSET_TUT2_AFTER_450);
                post_message(MESSAGE_TUTORIAL_TAXES_INDUSTRY);
            }
        }
        if (data.tutorial1.fire && !data.tutorial1.senate_built) {
            int population_almost = city_population() >= winning_population() - 20;
            if (!game_time_day() || population_almost) {
                if (city_buildings_has_palace())
                    city_mission_tutorial_add_senate();
                if (city_mission_tutorial_has_senate() || population_almost) {
                    data.tutorial1.senate_built = 1;
                    building_menu_update(BUILDSET_NORMAL);
                    post_message(MESSAGE_TUTORIAL_RELIGION);
                }
            }
        }
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        if (scenario_is_tutorial(1)) {
            if (!data.pharaoh.population_150_reached && city_population() >= 150) {
                data.pharaoh.population_150_reached = 1;
                building_menu_update(BUILDSET_TUT1_FOOD);
                post_message(MESSAGE_TUTORIAL_FOOD_OR_FAMINE);
            }
        }
    }
}
void tutorial_on_month_tick(void) {
    if (scenario_is_tutorial(3)) {
        if (game_time_month() == 5)
            city_message_post_with_message_delay(MESSAGE_CAT_TUTORIAL3, 1, MESSAGE_TUTORIAL_HUNGER_HALTS_IMMIGRANTS,
                                                 1200);
    }
}
void tutorial_save_state(buffer *buf1, buffer *buf2, buffer *buf3) {
    buf1->write_i32(data.tutorial1.fire);
    buf1->write_i32(data.tutorial1.crime);
    buf1->write_i32(data.tutorial1.collapse);
    buf1->write_i32(data.tutorial2.granary_built);
    buf1->write_i32(data.tutorial2.population_250_reached);
    buf1->write_i32(data.tutorial1.senate_built);
    buf1->write_i32(data.tutorial2.population_450_reached);
    buf1->write_i32(data.tutorial2.pottery_made);

    buf2->write_i32(data.tutorial2.pottery_made_year);

    buf3->write_i32(data.tutorial3.disease);
}
void tutorial_load_state(buffer *buf1, buffer *buf2, buffer *buf3) {
    if (GAME_ENV == ENGINE_ENV_C3) {
        data.tutorial1.fire = buf1->read_i32();
        data.tutorial1.crime = buf1->read_i32();
        data.tutorial1.collapse = buf1->read_i32();
        data.tutorial2.granary_built = buf1->read_i32();
        data.tutorial2.population_250_reached = buf1->read_i32();
        data.tutorial1.senate_built = buf1->read_i32();
        data.tutorial2.population_450_reached = buf1->read_i32();
        data.tutorial2.pottery_made = buf1->read_i32();
        data.tutorial2.pottery_made_year = buf2->read_i32();
        data.tutorial3.disease = buf3->read_i32();
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        data.pharaoh.fire = buf1->read_u8();
        data.pharaoh.population_150_reached = buf1->read_u8();
        data.pharaoh.gamemeat_400_stored = buf1->read_u8();
        data.pharaoh.collapse = buf1->read_u8();
        data.pharaoh.gold_mined_500 = buf1->read_u8();
        data.pharaoh.temples_built = buf1->read_u8();
        data.pharaoh.flags[6] = buf1->read_u8(); // ????
        data.pharaoh.figs_800_stored = buf1->read_u8();
        data.pharaoh.flags[8] = buf1->read_u8(); // ????
        data.pharaoh.pottery_made = buf1->read_u8();
        data.pharaoh.beer_made = buf1->read_u8();
        data.pharaoh.spacious_apartment = buf1->read_u8();
        data.pharaoh.flags[12] = buf1->read_u8();
        data.pharaoh.flags[13] = buf1->read_u8();
        data.pharaoh.flags[14] = buf1->read_u8();

        data.pharaoh.tut1_start = buf1->read_u8();
        data.pharaoh.tut2_start = buf1->read_u8();
        data.pharaoh.tut3_start = buf1->read_u8();
        data.pharaoh.tut4_start = buf1->read_u8();
        data.pharaoh.tut5_start = buf1->read_u8();
        data.pharaoh.tut6_start = buf1->read_u8();
        data.pharaoh.tut7_start = buf1->read_u8();
        data.pharaoh.tut8_start = buf1->read_u8();
        data.pharaoh.flags[23] = buf1->read_u8();
        data.pharaoh.flags[24] = buf1->read_u8();
        data.pharaoh.flags[25] = buf1->read_u8();
        data.pharaoh.flags[26] = buf1->read_u8(); // goal: bazaar
        data.pharaoh.flags[27] = buf1->read_u8(); // goal: pottery
        data.pharaoh.flags[28] = buf1->read_u8();
        data.pharaoh.flags[29] = buf1->read_u8();
        data.pharaoh.flags[30] = buf1->read_u8(); // tut4 ???
        data.pharaoh.flags[31] = buf1->read_u8();
        data.pharaoh.flags[32] = buf1->read_u8();
        data.pharaoh.flags[33] = buf1->read_u8(); // goal: water supply
        data.pharaoh.flags[34] = buf1->read_u8(); // tut4 ???
        data.pharaoh.flags[35] = buf1->read_u8();
        data.pharaoh.flags[36] = buf1->read_u8(); // goal: entertainment
        data.pharaoh.flags[37] = buf1->read_u8(); // goal: temples
        data.pharaoh.flags[38] = buf1->read_u8();
        data.pharaoh.flags[39] = buf1->read_u8();
        data.pharaoh.flags[40] = buf1->read_u8();
    }
}
