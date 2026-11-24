#include "city/city_monuments.h"
#include "city/city.h"
#include "game/sim_schedule.h"

#include "game/game_events.h"
#include "js/js_register.h"

void city_monuments_t::update_month() {

}

void city_monuments_t::advance_year() {
    emit(esid(__func__));
}

ANK_SIM_STEP(monuments_year, SIM_PHASE_YEAR, -1, 80, SIM_AREA_MONUMENTS) {
    g_city.monuments.advance_year();
}
