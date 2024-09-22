#include "common.h"

#include "core/game_environment.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/screen.h"
#include "graphics/view/view.h"
#include "game/game.h"

int sidebar_common_get_height() {
    return screen_height() - TOP_MENU_HEIGHT;
}

void sidebar_common_draw_relief(int x_offset, int y_offset, image_desc desc, bool is_collapsed) {
    painter ctx = game.painter();
    // relief images below panel

    int image_base = image_group(desc);
    int image_offset = desc.id == 121 ? 2 : 1; // GROUP_SIDE_PANEL
    int y_max = screen_height();

    while (y_offset < y_max) {
        ImageDraw::img_generic(ctx, image_base + image_offset + image_offset + is_collapsed, x_offset, y_offset + 6);
        y_offset += 285;
    }
}
