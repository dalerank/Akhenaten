#include "building_plaza.h"

#include "building/building.h"
#include "city/object_info.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/view/view.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"
#include "game/game.h"
#include "building_shrine.h"

static void building_shrine_draw_info(object_info& c, const char* type, int text_id, int image_offset) {
    painter ctx = game.painter();
    c.help_id = 67;
    window_building_play_sound(&c, snd::get_building_info_sound(type));
    outer_panel_draw(c.offset, c.width_blocks, c.height_blocks);
    lang_text_draw_centered(161, text_id, c.offset.x, c.offset.y + 12, 16 * c.width_blocks, FONT_LARGE_BLACK_ON_LIGHT);

    if (c.has_road_access) {
        ImageDraw::img_generic(ctx, image_offset + image_id_from_group(GROUP_PANEL_WINDOWS), c.offset.x + 190, c.offset.y + 16 * c.height_blocks - 148);
    } else {
        window_building_draw_description_at(c, 16 * c.height_blocks - 128, 69, 25);
    }
}

void building_shrine::window_info_background(object_info &ctx) {
    switch (base.type) {
    case BUILDING_SHRINE_OSIRIS:
        building_shrine_draw_info(ctx, "shrine_osiris", 0, 21);
        break;
    case BUILDING_SHRINE_RA:
        building_shrine_draw_info(ctx, "shrine_ra", 2, 22);
        break;
    case BUILDING_SHRINE_PTAH:
        building_shrine_draw_info(ctx, "shrine_ptah", 4, 23);
        break;
    case BUILDING_SHRINE_SETH:
        building_shrine_draw_info(ctx, "shrine_seth", 6, 24);
        break;
    case BUILDING_SHRINE_BAST:
        building_shrine_draw_info(ctx, "shrine_bast", 8, 25);
        break;
    }
}
