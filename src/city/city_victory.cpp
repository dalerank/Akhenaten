#include "city/city_victory.h"

#include "city/city.h"
#include "js/js_game.h"
#include "core/profiler.h"

void city_victory_t::reset() {
    state = e_victory_state_none;
    force_win = false;
    force_lost = false;
    emit(js_helpers::es_hash_str(esid(), __func__));
}

void city_victory_t::victory_check() {
    emit(js_helpers::es_hash_str(esid(), __func__));
}
