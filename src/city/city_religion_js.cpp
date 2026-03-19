#include "city/city_religion.h"

#include "core/profiler.h"
#include "game/game_events.h"
#include "js/js_game.h"
#include "city/city.h"

bool __city_god_is_known(int god_index) {
    return g_city.religion.is_god_known((e_god)god_index) != GOD_STATUS_UNKNOWN;
}
ANK_FUNCTION_1(__city_god_is_known)

void __city_god_set_known(int god_index, bool known) {
    const auto new_status = known ? GOD_STATUS_KNOWN : GOD_STATUS_UNKNOWN;
    events::emit(event_religion_god_status_update{ (e_god)god_index, new_status });
    g_city.religion.set_god_known((e_god)god_index, new_status);
}
ANK_FUNCTION_2(__city_god_set_known)

xstring __city_god_name(int god_index) {
    return e_god_tokens.name((e_god)god_index);
}
ANK_FUNCTION_1(__city_god_name)