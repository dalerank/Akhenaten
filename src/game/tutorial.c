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

static struct {
    struct {
        int fire;
        int crime;
        int collapse;
        int senate_built;
    } tutorial1;
    struct {
        int granary_built;
        int population_250_reached;
        int population_450_reached;
        int pottery_made;
        int pottery_made_year;
    } tutorial2;
    struct {
        int disease;
    } tutorial3;
    struct {
        bool flags[41];
        //
        bool fire;
        bool population_150_reached;
        bool gamemeat_400_stored;
        bool gold_mined_enough;
        bool entertainment_msg;
        //
        bool housing_and_roads_msg;
        bool crime_and_gold_msg;


        bool collapse;


    } pharaoh;
} data;

static void post_message(int message) {
    city_message_post(1, message, 0, 0);
}

void tutorial_init(void) {
    int tut1_passed = 1, tut2_passed = 1, tut3_passed = 1;
    if (scenario_is_tutorial_1())
        tut1_passed = tut2_passed = 0;
    else if (scenario_is_tutorial_2())
        tut2_passed = 0;
    else if (scenario_is_tutorial_3())
        tut3_passed = 0;

    if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        data.pharaoh.fire = tut1_passed;
        data.pharaoh.housing_and_roads_msg = tut1_passed;
        data.pharaoh.population_150_reached = tut1_passed;
        data.pharaoh.crime_and_gold_msg = tut2_passed;
//        data.pharaoh.farming_msg = tut3_passed;

    } else if (GAME_ENV == ENGINE_ENV_C3) {
        data.tutorial1.fire = tut1_passed;
        data.tutorial1.crime = tut1_passed;
        data.tutorial1.collapse = tut1_passed;
        data.tutorial1.senate_built = tut1_passed;
        city_mission_tutorial_set_fire_message_shown(tut1_passed);

        data.tutorial2.granary_built = tut2_passed;
        data.tutorial2.population_250_reached = tut2_passed;
        data.tutorial2.population_450_reached = tut2_passed;
        data.tutorial2.pottery_made = tut2_passed;
        data.tutorial2.pottery_made_year = tut2_passed;

        data.tutorial3.disease = tut3_passed;
        city_mission_tutorial_set_disease_message_shown(tut3_passed);
    }
}

tutorial_availability tutorial_advisor_empire_availability(void) {
    if (scenario_is_tutorial_1())
        return NOT_AVAILABLE;
    else if (scenario_is_tutorial_2() && !data.tutorial2.population_250_reached)
        return NOT_AVAILABLE_YET;
    else {
        return AVAILABLE;
    }
}
//tutorial_build_buttons tutorial_get_build_buttons(void) {
//    if (GAME_ENV == ENGINE_ENV_C3) {
//        if (scenario_is_tutorial_1()) {
//            if (!data.tutorial1.fire && !data.tutorial1.crime)
//                return TUT1_BUILD_START;
//            else if (!data.tutorial1.collapse)
//                return TUT1_BUILD_FIREHOUSE;
//            else if (!data.tutorial1.senate_built)
//                return TUT1_BUILD_ARCHITECT;
//
//        } else if (scenario_is_tutorial_2()) {
//            if (!data.tutorial2.granary_built)
//                return TUT2_BUILD_START;
//            else if (!data.tutorial2.population_250_reached)
//                return TUT2_BUILD_UP_TO_250;
//            else if (!data.tutorial2.population_450_reached)
//                return TUT2_BUILD_UP_TO_450;
//            else if (!data.tutorial2.pottery_made)
//                return TUT2_BUILD_AFTER_450;
//
//        }
//        return TUT_BUILD_NORMAL;
//    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
//        if (scenario_is_tutorial_1()) {
//            if (!data.pharaoh.fire && !data.pharaoh.collapse && !data.pharaoh.population_150_reached)
//                return TUT1_BUILD_START;
//            else if (!data.pharaoh.collapse)
//                return TUT1_BUILD_FOOD;
//            else if (!data.pharaoh.population_150_reached)
//                return TUT1_BUILD_ARCHITECT;
//            else
//                return TUT1_BUILD_FOOD;
//
//        } else if (scenario_is_tutorial_2()) {
//            if (!data.tutorial2.granary_built)
//                return TUT2_BUILD_START;
//            else if (!data.tutorial2.population_250_reached)
//                return TUT2_BUILD_UP_TO_250;
//            else if (!data.tutorial2.population_450_reached)
//                return TUT2_BUILD_UP_TO_450;
//            else if (!data.tutorial2.pottery_made)
//                return TUT2_BUILD_AFTER_450;
//
//        }
//        return TUT_BUILD_NORMAL;
//    }
//}

int tutorial_get_population_cap(int current_cap) {
    return current_cap; //temp
    if (scenario_is_tutorial_1()) {
        if (!data.tutorial1.fire ||
            !data.tutorial1.collapse ||
            !data.tutorial1.senate_built) {
            return 80;
        }
    } else if (scenario_is_tutorial_2()) {
        if (!data.tutorial2.granary_built)
            return 150;
        else if (!data.tutorial2.pottery_made)
            return 520;

    }
    return current_cap;
}
int tutorial_get_immediate_goal_text(void) {
    if (GAME_ENV == ENGINE_ENV_C3) {
        if (scenario_is_tutorial_1()) {
            if (!data.tutorial1.fire && !data.tutorial1.crime)
                return 17;
            else if (!data.tutorial1.collapse)
                return 18;
            else if (!data.tutorial1.senate_built)
                return 19;
            else
                return 20;
        } else if (scenario_is_tutorial_2()) {
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
        if (scenario_is_tutorial_1()) {
            if (!data.pharaoh.population_150_reached)
                return 21;
            else if (!data.pharaoh.gamemeat_400_stored)
                return 19;
            else
                return 20;
        } else if (scenario_is_tutorial_2()) {

        } else if (scenario_is_tutorial_3()) {

        }
        return 0;
    }
}
int tutorial_adjust_request_year(int *year) {
    if (scenario_is_tutorial_2()) {
        if (!data.tutorial2.pottery_made)
            return 0;

        *year = data.tutorial2.pottery_made_year;
    }
    return 1;
}
int tutorial_extra_fire_risk(void) {
    return !data.tutorial1.fire;
}
int tutorial_extra_damage_risk(void) {
    return data.tutorial1.fire && !data.tutorial1.collapse;
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
void tutorial_on_filled_granary(void) {
    if (!data.tutorial2.granary_built) {
        data.tutorial2.granary_built = 1;
        building_menu_update(BUILDSET_TUT2_UP_TO_250);
        post_message(MESSAGE_TUTORIAL_WATER);
    }
}
void tutorial_on_add_to_warehouse(void) {
    if (!data.tutorial2.pottery_made && city_resource_count(RESOURCE_POTTERY_C3) >= 1) {
        data.tutorial2.pottery_made = 1;
        data.tutorial2.pottery_made_year = game_time_year();
        building_menu_update(BUILDSET_NORMAL);
        post_message(MESSAGE_TUTORIAL_TRADE);
    }
}
void tutorial_starting_message() {
    if (scenario_is_tutorial_1() && !data.pharaoh.housing_and_roads_msg) {
        post_message(MESSAGE_TUTORIAL_HOUSING_AND_ROADS);
        data.pharaoh.housing_and_roads_msg = 1;
    }
    if (scenario_is_tutorial_2() && !data.pharaoh.crime_and_gold_msg) {
        post_message(MESSAGE_TUTORIAL_GOLD_AND_CRIME);
        data.pharaoh.crime_and_gold_msg = 1;
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
                if (city_buildings_has_senate())
                    city_mission_tutorial_add_senate();
                if (city_mission_tutorial_has_senate() || population_almost) {
                    data.tutorial1.senate_built = 1;
                    building_menu_update(BUILDSET_NORMAL);
                    post_message(MESSAGE_TUTORIAL_RELIGION);
                }
            }
        }
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        if (data.pharaoh.housing_and_roads_msg) {
            if (!data.pharaoh.population_150_reached && city_population() >= 150) {
                data.pharaoh.population_150_reached = 1;
                building_menu_update(BUILDSET_TUT1_FOOD);
                post_message(MESSAGE_TUTORIAL_FOOD_OR_FAMINE);
            }
        }
    }
}
void tutorial_on_month_tick(void) {
    if (scenario_is_tutorial_3()) {
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
        data.pharaoh.flags[3] = buf1->read_u8();
        data.pharaoh.gold_mined_enough = buf1->read_u8();
        data.pharaoh.entertainment_msg = buf1->read_u8();
        data.pharaoh.flags[6] = buf1->read_u8();
        data.pharaoh.flags[7] = buf1->read_u8();
        data.pharaoh.flags[8] = buf1->read_u8();
        data.pharaoh.flags[9] = buf1->read_u8();
        data.pharaoh.flags[10] = buf1->read_u8();
        data.pharaoh.flags[11] = buf1->read_u8();
        data.pharaoh.flags[12] = buf1->read_u8();
        data.pharaoh.flags[13] = buf1->read_u8();
        data.pharaoh.flags[14] = buf1->read_u8();

        data.pharaoh.housing_and_roads_msg = buf1->read_u8();
        data.pharaoh.crime_and_gold_msg = buf1->read_u8();
        data.pharaoh.flags[17] = buf1->read_u8();
        data.pharaoh.flags[18] = buf1->read_u8();
        data.pharaoh.flags[19] = buf1->read_u8();
        data.pharaoh.flags[20] = buf1->read_u8();
        data.pharaoh.flags[21] = buf1->read_u8();
        data.pharaoh.flags[22] = buf1->read_u8();
        data.pharaoh.flags[23] = buf1->read_u8();
        data.pharaoh.flags[24] = buf1->read_u8();
        data.pharaoh.flags[25] = buf1->read_u8();
        data.pharaoh.flags[26] = buf1->read_u8(); // ??
        data.pharaoh.flags[27] = buf1->read_u8();
        data.pharaoh.flags[28] = buf1->read_u8();
        data.pharaoh.flags[29] = buf1->read_u8();
        data.pharaoh.flags[30] = buf1->read_u8();
        data.pharaoh.flags[31] = buf1->read_u8();
        data.pharaoh.flags[32] = buf1->read_u8();
        data.pharaoh.flags[33] = buf1->read_u8(); // ??
        data.pharaoh.flags[34] = buf1->read_u8();
        data.pharaoh.flags[35] = buf1->read_u8();
        data.pharaoh.flags[36] = buf1->read_u8(); // goal: entertainment
        data.pharaoh.flags[37] = buf1->read_u8(); // goal: temples
        data.pharaoh.flags[38] = buf1->read_u8();
        data.pharaoh.flags[39] = buf1->read_u8();
        data.pharaoh.flags[40] = buf1->read_u8();
    }
}
