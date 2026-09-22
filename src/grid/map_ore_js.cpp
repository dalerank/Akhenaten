#include "grid/clay.h"
#include "grid/copper.h"
#include "grid/gems.h"
#include "grid/golden.h"
#include "js/js_game.h"

int __map_get_copper(tile2i tile) {
    return map_get_copper(tile);
}
ANK_FUNCTION_1(__map_get_copper)

void __map_copper_deplete(tile2i tile, int amount) {
    map_copper_deplete(tile, amount);
}
ANK_FUNCTION_2(__map_copper_deplete)

int __map_get_golden(tile2i tile) {
    return map_get_golden(tile);
}
ANK_FUNCTION_1(__map_get_golden)

void __map_golden_deplete(tile2i tile, int amount) {
    map_golden_deplete(tile, amount);
}
ANK_FUNCTION_2(__map_golden_deplete)

int __map_get_gems(tile2i tile) {
    return map_get_gems(tile);
}
ANK_FUNCTION_1(__map_get_gems)

void __map_gems_deplete(tile2i tile, int amount) {
    map_gems_deplete(tile, amount);
}
ANK_FUNCTION_2(__map_gems_deplete)

int __map_get_clay(tile2i tile) {
    return map_get_clay(tile);
}
ANK_FUNCTION_1(__map_get_clay)

void __map_clay_deplete(tile2i tile, int amount) {
    map_clay_deplete(tile, amount);
}
ANK_FUNCTION_2(__map_clay_deplete)
