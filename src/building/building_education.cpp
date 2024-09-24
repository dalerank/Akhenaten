#include "building_education.h"

#include "building/building.h"
#include "city/object_info.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "grid/road_access.h"
#include "figure/figure.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"
#include "game/game.h"

#include "js/js_game.h"

void building_education_draw_info(object_info& c, e_figure_type ftype, e_resource resource, vec2i icon_res, vec2i text_res) {
    painter ctx = game.painter();

    building *b = building_get(c.building_id);
    const auto &meta = b->dcast()->get_info();

    c.help_id = meta.help_id;
    window_building_play_sound(&c, b->get_sound());
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(meta.text_id, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);

    if (resource != RESOURCE_NONE) {
        ImageDraw::img_generic(ctx, image_id_resource_icon(resource), c.offset + icon_res);
        int width = lang_text_draw(23, 77, c.offset + text_res, FONT_NORMAL_BLACK_ON_LIGHT);
        lang_text_draw_amount(8, 10, b->stored_amount(), c.offset + text_res + vec2i{width, 0}, FONT_NORMAL_BLACK_ON_LIGHT);
    }

    if (ftype != FIGURE_NONE && b->has_figure_of_type(BUILDING_SLOT_SERVICE, ftype)) {
        window_building_draw_description(c, meta.text_id, e_text_figure_on_patrol);
    } else if (!c.has_road_access) {
        window_building_draw_description(c, e_text_building, e_text_building_no_roads);
    } else if (building_get(c.building_id)->num_workers <= 0) {
        window_building_draw_description(c, meta.text_id, e_text_no_workers);
    } else {
        window_building_draw_description(c, meta.text_id, e_text_works_fine);
    }

    inner_panel_draw(c.offset + vec2i{ 16, 136 }, { c.bgsize.x - 2, 4 });
    window_building_draw_employment(&c, 142);
}