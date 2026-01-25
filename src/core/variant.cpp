#include "core/variant.h"

#include "game/game_pool.h"

game_permanent_memory_pool<bvariant_map, 32> g_bvariant_map_pool;

bvariant_map* bvariant_map::acquire_from_pool() {
    return g_bvariant_map_pool.create();
}

void bvariant_map::return_to_pool(bvariant_map *p) {
    g_bvariant_map_pool.destroy(p);
}
