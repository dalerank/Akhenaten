#include "city/city_festival.h"

#include "city/city.h"
#include "js/js_game.h"

std::optional<bvariant> __city_get_festival_property(pcstr property) {
    return archive_helper::get(g_city.festival, property, true);
}
ANK_FUNCTION_1(__city_get_festival_property)