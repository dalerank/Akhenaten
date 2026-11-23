#include "view.h"

#include "js/js_game.h"

void __city_camera_go_to(tile2i tile) {
    g_camera.go_to_mappoint(tile);
}
ANK_FUNCTION_1(__city_camera_go_to)
