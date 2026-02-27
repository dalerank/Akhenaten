#include "building_farm.h"
#include "js/js_game.h"

std::optional<bvariant> __farm_get_property(int bid, pcstr property) {
    building_farm* farm = building_get(bid)->dcast_farm();
    if (!farm) {
        return {};
    }

    auto result = archive_helper::get(farm->runtime_data(), property, true);
    if (result.has_value()) {
        return result;
    }

    return archive_helper::get(farm->base, property, true);
}
ANK_FUNCTION_2(__farm_get_property)

void __farm_set_worker(int bid, int action, vec2i coords) {
    building_farm* farm = building_get(bid)->dcast_farm();
    if (farm) {
        farm->runtime_data().worker_tile = coords;
        farm->runtime_data().worker_action = action;
    }
}
ANK_FUNCTION_3(__farm_set_worker)