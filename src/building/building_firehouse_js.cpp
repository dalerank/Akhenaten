#include "building/building_firehouse.h"

#include "core/profiler.h"
#include "core/object_property.h"
#include "js/js_game.h"

std::optional<bvariant> __firehouse_get_property(int bid, pcstr property) {
    building_firehouse *firehouse = building_get(bid)->dcast_firehouse();
    if (!firehouse) {
        return {};
    }

    return firehouse->get_property(tags().building, property);
}
ANK_FUNCTION_2(__firehouse_get_property)
