#include "building_palace.h"

#include "building/building.h"
#include "city/object_info.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/view/view.h"
#include "graphics/boilerplate.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "sound/sound_building.h"

void building_palace_draw_info(object_info& c) {
    view_context ctx = view_context_main();
    c.can_go_to_advisor = true;
    c.help_id = e_text_building_palace;

    window_building_play_sound(&c, snd::get_building_info_sound("palace"));
    outer_panel_draw(c.x_offset, c.y_offset, c.width_blocks, c.height_blocks);
    lang_text_draw_centered(105, 0, c.x_offset, c.y_offset + 10, 16 * c.width_blocks, FONT_LARGE_BLACK_ON_LIGHT);

    ImageDraw::img_generic(ctx, image_id_resource_icon(RESOURCE_DEBEN), c.x_offset + 16, c.y_offset + 36);

    building* b = building_get(c.building_id);
    int width = lang_text_draw(105, 2, c.x_offset + 44, c.y_offset + 43, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw_amount(8, 0, b->tax_income_or_storage, c.x_offset + 44 + width, c.y_offset + 43, FONT_NORMAL_BLACK_ON_LIGHT);

    if (!c.has_road_access)
        window_building_draw_description(c, 69, 25);
    else if (b->num_workers <= 0)
        window_building_draw_description_at(c, 72, 106, 10);
    else if (c.worker_percentage >= 100)
        window_building_draw_description_at(c, 72, 106, 5);
    else if (c.worker_percentage >= 75)
        window_building_draw_description_at(c, 72, 106, 6);
    else if (c.worker_percentage >= 50)
        window_building_draw_description_at(c, 72, 106, 7);
    else if (c.worker_percentage >= 25)
        window_building_draw_description_at(c, 72, 106, 8);
    else {
        window_building_draw_description_at(c, 72, 106, 9);
    }

    inner_panel_draw(c.x_offset + 16, c.y_offset + 136, c.width_blocks - 2, 4);
    window_building_draw_employment(&c, 142);

    lang_text_draw(105, 3, c.x_offset + 60, c.y_offset + 220, FONT_NORMAL_BLACK_ON_LIGHT);
}
