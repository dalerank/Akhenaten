#include "city/city_warnings.h"

#include "game/game_events.h"

city_warnings::~city_warnings() {
    for (const xstring& id : warnings) {
        events::emit(event_construction_warning{id});
    }
}
