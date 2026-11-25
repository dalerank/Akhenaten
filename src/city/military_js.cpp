#include "military.h"
#include "city/military.h"

#include "js/js_game.h"
#include "city/city.h"
#include "core/profiler.h"

std::optional<bvariant> __city_get_military_property(pcstr property) {
    return archive_helper::get(city_military(), property, true);
}
ANK_FUNCTION_1(__city_get_military_property)

void __city_military_clear_kingdome_service() {
    city_military().clear_kingdome_service_batalions();
}
ANK_FUNCTION(__city_military_clear_kingdome_service)