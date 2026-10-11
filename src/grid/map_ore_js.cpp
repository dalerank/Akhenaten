#include "grid/clay.h"
#include "grid/copper.h"
#include "grid/gems.h"
#include "grid/golden.h"
#include "grid/granite.h"
#include "grid/limestone.h"
#include "grid/sandstone.h"
#include "grid/stone.h"
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

int __map_get_sandstone(tile2i tile) {
    return map_get_sandstone(tile);
}
ANK_FUNCTION_1(__map_get_sandstone)

void __map_sandstone_deplete(tile2i tile, int amount) {
    map_sandstone_deplete(tile, amount);
}
ANK_FUNCTION_2(__map_sandstone_deplete)

int __map_get_stone(tile2i tile) {
    return map_get_stone(tile);
}
ANK_FUNCTION_1(__map_get_stone)

void __map_stone_deplete(tile2i tile, int amount) {
    map_stone_deplete(tile, amount);
}
ANK_FUNCTION_2(__map_stone_deplete)

int __map_get_limestone(tile2i tile) {
    return map_get_limestone(tile);
}
ANK_FUNCTION_1(__map_get_limestone)

void __map_limestone_deplete(tile2i tile, int amount) {
    map_limestone_deplete(tile, amount);
}
ANK_FUNCTION_2(__map_limestone_deplete)

int __map_get_granite(tile2i tile) {
    return map_get_granite(tile);
}
ANK_FUNCTION_1(__map_get_granite)

void __map_granite_deplete(tile2i tile, int amount) {
    map_granite_deplete(tile, amount);
}
ANK_FUNCTION_2(__map_granite_deplete)
