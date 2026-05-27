#include "building_shipyard.h"

#include "core/profiler.h"
#include "js/js_game.h"

std::optional<bvariant> __shipyard_get_property(int bid, pcstr property) {
    building_shipyard *shipyard = building_get(bid)->dcast_shipyard();
    if (!shipyard) {
        return {};
    }

    auto result = archive_helper::get(shipyard->runtime_data(), property, true);
    if (result.has_value()) {
        return result;
    }

    return archive_helper::get(shipyard->base, property, true);
}
ANK_FUNCTION_2(__shipyard_get_property)
