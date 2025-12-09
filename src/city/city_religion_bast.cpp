#include "city_religion_bast.h"

#include "city/city.h"
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

