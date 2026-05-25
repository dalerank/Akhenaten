#include "building/building_roadblock.h"

#include "js/js_game.h"
#include "core/profiler.h"

bool __roadblock_get_permission(int bid, int permission) {
    building *b = building_get(bid);
    building_roadblock *roadblock = b ? b->dcast_roadblock() : nullptr;
    return roadblock && roadblock->get_permission((e_permission)permission);
}
ANK_FUNCTION_2(__roadblock_get_permission)

void __roadblock_toggle_permission(int bid, int permission) {
    building *b = building_get(bid);
    building_roadblock *roadblock = b ? b->dcast_roadblock() : nullptr;
    if (roadblock) {
        roadblock->set_permission((e_permission)permission);
    }
}
ANK_FUNCTION_2(__roadblock_toggle_permission)
