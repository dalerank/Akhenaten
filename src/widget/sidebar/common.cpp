#include "common.h"

#include "city/view.h"
#include "graphics/image.h"
#include "graphics/screen.h"
#include "widget/minimap.h"
#include "core/game_environment.h"

int sidebar_common_get_x_offset_expanded(void) {
    return screen_width() - SIDEBAR_EXPANDED_WIDTH[GAME_ENV];
}
int sidebar_common_get_x_offset_collapsed(void) {
    return screen_width() - SIDEBAR_COLLAPSED_WIDTH;
}
int sidebar_common_get_height(void) {
    return screen_height() - TOP_MENU_HEIGHT[GAME_ENV];
}

void sidebar_common_draw_relief(int x_offset, int y_offset, int image, int is_collapsed) {
    // relief images below panel
    int image_base = image_id_from_group(image);
    int image_offset = image == GROUP_SIDE_PANEL ? 2 : 1;
    int y_max = screen_height();
    while (y_offset < y_max) {
        if (GAME_ENV == ENGINE_ENV_C3 && y_max - y_offset <= 120) {
            ImageDraw::img_generic(image_base + image_offset + is_collapsed, x_offset, y_offset);
            y_offset += 120;
        } else {
            ImageDraw::img_generic(image_base + image_offset + image_offset + is_collapsed, x_offset, y_offset + 6);
            y_offset += 285;
        }
    }
}
