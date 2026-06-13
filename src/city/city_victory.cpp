#include "city/city_victory.h"

#include "city/city.h"
#include "scenario/scenario.h"
#include "js/js_game.h"
#include "core/profiler.h"

std::unordered_map<xstring, bool> g_victory_reasons;

void city_set_victory_reason(xstring reason, bool value) {
    g_victory_reasons[reason] = value;
}
ANK_FUNCTION_2(city_set_victory_reason)

void city_victory_t::reset() {
    state = e_victory_state_none;
    force_win = false;
    force_lost = false;
    g_victory_reasons.clear();
}

void city_victory_t::victory_check() {
    emit(js_helpers::es_hash_str("city_victory", "victory_check"));
}

void city_victory_t::update_months_to_govern() {
    if (g_scenario.has_won) {
        g_scenario.continue_months_left--;
    }
}

const std::unordered_map<xstring, bool> &get_victory_reasons() {
    return g_victory_reasons;
}
