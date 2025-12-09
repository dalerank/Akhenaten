#include "city_religion_ra.h"

#include "city/city.h"
#include "city/city_message.h"
#include "city/ratings.h"
#include "core/random.h"
#include "game/game_events.h"

god_ra_t god_ra;

void god_ra_t::perform_reduced_trading() {
    g_city.religion.ra_harshly_reduced_trading_months_left = 12;
    messages::popup("message_wrath_of_ra", 0, 0);
}

void god_ra_t::perform_lower_reputation() {
    g_city.kingdome.reduce_god_wrath(15);
    messages::popup("message_wrath_of_ra_2", 0, 0);
}

void god_ra_t::perform_no_traders() {
    g_city.religion.ra_no_traders_months_left = 12;
    messages::popup("message_wrath_of_ra_3", 0, 0);
}

void god_ra_t::perform_major_curse() {
    int rand_value = anti_scum_random_15bit() % 3;
    if (rand_value == 0) {
        // lowers commerce prices
        perform_reduced_trading();
    } else if (rand_value == 1) {
        // lowers reputation
        perform_lower_reputation();
    } else {
        // no trading ships/caravans for one year
        perform_no_traders();
    }
}

void god_ra_t::perform_slightly_reduced_trading() {
    g_city.religion.ra_slightly_reduced_trading_months_left = 12;
    events::emit(event_message_god{ GOD_RA, "message_ra_is_upset" });
}

void god_ra_t::perform_slightly_lower_reputation() {
    g_city.kingdome.reduce_god_wrath(5);
    events::emit(event_message_god{ GOD_RA, "message_ra_is_upset_2" });
}

void god_ra_t::perform_minor_curse() {
    if (anti_scum_random_bool()) {
        // lowers amount of traded goods
        perform_slightly_reduced_trading();
    } else {
        // lowers reputation
        perform_slightly_lower_reputation();
    }
}

