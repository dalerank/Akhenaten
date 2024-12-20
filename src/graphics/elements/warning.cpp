#include "warning.h"

#include "city/warning.h"
#include "game/state.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/view/view.h"
#include "graphics/screen.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "panel.h"
#include "game/game.h"

static const int TOP_OFFSETS[] = {30, 55, 80, 105, 130};

static int determine_width(pcstr text) {
    int width = text_get_width(text, FONT_NORMAL_BLACK_ON_LIGHT);

    if (width <= 100) return 200;
    else if (width <= 200) return 300;
    else if (width <= 300) return 400;

    return 460;
}

void warning_draw() {
    if (!window_is(WINDOW_CITY) && !window_is(WINDOW_EDITOR_MAP)) {
        city_warning_clear_all();
        return;
    }

    painter ctx = game.painter();
    int center = (screen_width() - 180) / 2;
    for (int i = 0; i < 5; i++) {
        pcstr text = city_warning_get(i);
        if (!text) {
            continue;
        }

        int top_offset = TOP_OFFSETS[i];
        if (game.paused) {
            top_offset += 70;
        }

        int box_width = determine_width(text);
        small_panel_draw(center - box_width / 2 + 1, top_offset, box_width / 16 + 1, 1);
        if (box_width < 460) {
            // ornaments at the side
            ImageDraw::img_generic(ctx, image_id_from_group(GROUP_CONTEXT_ICONS) + 15, center - box_width / 2 + 2, top_offset + 2);
            ImageDraw::img_generic(ctx, image_id_from_group(GROUP_CONTEXT_ICONS) + 15, center + box_width / 2 - 30, top_offset + 2);
        }
        text_draw_centered((const uint8_t*)text, center - box_width / 2 + 1, top_offset + 4, box_width, FONT_NORMAL_WHITE_ON_DARK, 0);
    }
    city_warning_clear_outdated();
}
