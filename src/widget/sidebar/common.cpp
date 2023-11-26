#include "common.h"

#include "core/game_environment.h"
#include "graphics/boilerplate.h"
#include "graphics/screen.h"
#include "graphics/view/view.h"
#include "widget/minimap.h"
#include "game/game.h"

int sidebar_common_get_x_offset_expanded(void) {
    return screen_width() - SIDEBAR_EXPANDED_WIDTH;
}
int sidebar_common_get_x_offset_collapsed(void) {
    return screen_width() - SIDEBAR_COLLAPSED_WIDTH;
}
int sidebar_common_get_height(void) {
    return screen_height() - TOP_MENU_HEIGHT;
}

void sidebar_common_draw_relief(int x_offset, int y_offset, e_image_id img, bool is_collapsed) {
    painter ctx = game.painter();
    // relief images below panel

    image_desc desc = get_image_desc(img);
    int image_base = image_id_from_group(img);
    int image_offset = desc.id == 121 ? 2 : 1; // GROUP_SIDE_PANEL
    int y_max = screen_height();

    while (y_offset < y_max) {
        ImageDraw::img_generic(ctx, image_base + image_offset + image_offset + is_collapsed, x_offset, y_offset + 6);
        y_offset += 285;
    }
}
