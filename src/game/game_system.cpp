#include "game/game_system.h"

#include "js/js_game.h"

void game_system::emit(const bstring64& esname_str, const bvariant_map& args) {
    OZZY_PROFILER_SECTION(_, esname_str.c_str());
    js_call_event_handlers(esname_str.c_str(), args);
}

void game_system::emit(const bstring64& esname_str) {
    OZZY_PROFILER_SECTION(_, esname_str.c_str());
    emit(esname_str, {});
}

