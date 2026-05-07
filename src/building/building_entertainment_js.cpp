#include "building_entertainment.h"

#include "core/profiler.h"
#include "js/js_game.h"

std::optional<bvariant> __entertainment_building_get_property(int bid, pcstr property) {
    building_entertainment *ent = building_get(bid)->dcast_entertainment();
    if (!ent) {
        return {};
    }

    auto result = archive_helper::get(ent->runtime_data(), property, true);
    if (result.has_value()) {
        return result;
    }

    return archive_helper::get(ent->base, property, true);
}
ANK_FUNCTION_2(__entertainment_building_get_property)
