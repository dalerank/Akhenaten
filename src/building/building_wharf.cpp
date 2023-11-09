#include "building_plaza.h"

#include "building/building.h"
#include "city/object_info.h"
#include "figure/figure.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/boilerplate.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"
#include "game/game.h"

void building_wharf_draw_info(object_info &c) {
    painter ctx = game.painter();

    c.help_id = 84;
    window_building_play_sound(&c, snd::get_building_info_sound("wharf"));
    outer_panel_draw(c.x_offset, c.y_offset, c.width_blocks, c.height_blocks);
    lang_text_draw_centered(102, 0, c.x_offset, c.y_offset + 10, 16 * c.width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    ImageDraw::img_generic(ctx, image_id_resource_icon(RESOURCE_FIGS) + resource_image_offset(RESOURCE_FIGS, RESOURCE_IMAGE_ICON), c.x_offset + 10, c.y_offset + 10);

    building* b = building_get(c.building_id);

    if (!c.has_road_access) {
        window_building_draw_description(c, 69, 25);
    } else if (!b->data.industry.fishing_boat_id) {
        window_building_draw_description(c, 102, 2);
    } else {
        int text_id;
        switch (figure_get(b->data.industry.fishing_boat_id)->action_state) {
        case FIGURE_ACTION_191_FISHING_BOAT_GOING_TO_FISH:
        text_id = 3;
        break;
        case FIGURE_ACTION_192_FISHING_BOAT_FISHING:
        text_id = 4;
        break;
        case FIGURE_ACTION_193_FISHING_BOAT_GOING_TO_WHARF:
        text_id = 5;
        break;
        case FIGURE_ACTION_194_FISHING_BOAT_AT_WHARF:
        text_id = 6;
        break;
        case FIGURE_ACTION_195_FISHING_BOAT_RETURNING_WITH_FISH:
        text_id = 7;
        break;
        default:
        text_id = 8;
        break;
        }
        window_building_draw_description(c, 102, text_id);
    }

    inner_panel_draw(c.x_offset + 16, c.y_offset + 136, c.width_blocks - 2, 4);
    window_building_draw_employment(&c, 142);
}
