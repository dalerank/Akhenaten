#include "city_religion_bast.h"

#include "city/city.h"
#include "city/city_festival.h"
#include "city/city_message.h"
#include "core/random.h"
#include "game/game_events.h"

god_bast_t god_bast;

bool god_bast_t::perform_houses_destruction() {
    return g_city.religion.BAST_houses_destruction();
}

void god_bast_t::perform_major_curse() {
    // destroy some of the best houses
    perform_houses_destruction();
    messages::popup("message_wrath_of_bast", 0, 0);
}

void god_bast_t::perform_malaria_plague() {
    // TODO: implement malaria plague
    //            city_sentiment_set_max_happiness(50);
    //            city_sentiment_change_happiness(-5);
    //            city_health_change(-10);
    //            city_sentiment_update();
}

void god_bast_t::perform_minor_curse() {
    // plague
    perform_malaria_plague();
    events::emit(event_message_god{ GOD_BAST, "message_bast_is_upset" });
}

void god_bast_t::perform_festival_for_other_gods() {
    // throws a festival for the other gods
    g_city.festival.planned.god = GOD_OSIRIS;
    g_city.festival.planned.size = FESTIVAL_BAST_SPECIAL;
    g_city.festival.planned.months_to_go = 1;
    g_city.festival.first_festival_effect_months = 1;

    g_city.religion.gods[GOD_RA].months_since_festival = 0;
    g_city.religion.gods[GOD_PTAH].months_since_festival = 0;
    g_city.religion.gods[GOD_SETH].months_since_festival = 0;
    messages::popup("message_small_blessing_from_bast", 0, 0);
}

void god_bast_t::perform_minor_blessing() {
    // throws a festival for the other gods
    perform_festival_for_other_gods();
}

