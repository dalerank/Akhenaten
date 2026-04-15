#include "city/city_monuments.h"

#include "game/game_events.h"
#include "js/js_game.h"

void city_monuments_t::update_month() {

}

void city_monuments_t::advance_year() {
    emit(esid(__func__));
}