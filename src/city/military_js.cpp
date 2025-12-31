#include "military.h"

#include "js/js_game.h"
#include "city/city.h"

std::optional<bvariant> __city_get_military_property(pcstr property) {
    return archive_helper::get(g_city.military, property, true);
}
ANK_FUNCTION_1(__city_get_military_property)