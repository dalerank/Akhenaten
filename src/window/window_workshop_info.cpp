#include "graphics/elements/ui.h"

#include "window/building/common.h"
#include "window/window_building_info.h"
#include "sound/sound_building.h"
#include "game/game.h"
#include "city/object_info.h"
#include "city/city_resource.h"
#include "core/calc.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"
#include "js/js_game.h"

struct workshop_info_window : public building_info_window_t<workshop_info_window> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        building *b = c.building_get();
        return b->is_workshop();
    }
};

workshop_info_window workshop_infow;

void building_workshop_draw_foreground(object_info &c) {
    workshop_infow.draw();

    window_building_draw_employment(&c, 142);
}

void workshop_info_window::init(object_info& c) {
    building_info_window::init(c);

    building *b = c.building_get();
    if (!b->is_workshop()) {
        return;
    }
    
    window_building_play_sound(&c, b->get_sound());

    textid trouble_text{ c.group_id, 0 };
    if (!c.has_road_access) { trouble_text = {69, 25}; }
    else if (city_resource_is_mothballed(b->output_resource_first_id)) { trouble_text.id = 4; }
    else if (b->num_workers <= 0) { trouble_text.id = 5; }
    else if (!b->workshop_has_resources()) { trouble_text.id = 11; }
    else { trouble_text.id = approximate_value(c.worker_percentage / 100.f, make_array(10, 9, 8, 7, 6)); }

    ui["workers_desc"].text(trouble_text);

    fill_employment_details(c);
}

void building_workshop_draw_background(object_info& c, e_resource input_resource_a) {
    painter ctx = game.painter();
    building *b = building_get(c.building_id);
    const auto &params = b->dcast()->params();
    c.help_id = params.meta.help_id;
    int group_id = params.meta.text_id;

    window_building_play_sound(&c, snd::get_building_info_sound(b->type));

    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    ImageDraw::img_generic(ctx, image_id_resource_icon(b->output_resource_first_id), c.offset.x + 10, c.offset.y + 10);
    lang_text_draw_centered(group_id, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);

    int pct_done = calc_percentage<int>(b->data.industry.progress, 400);
    int width = lang_text_draw(group_id, 2, c.offset.x + 32, c.offset.y + 40, FONT_NORMAL_BLACK_ON_LIGHT);
    width += text_draw_percentage(pct_done, c.offset.x + 32 + width, c.offset.y + 40, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw(group_id, 3, c.offset.x + 32 + width, c.offset.y + 40, FONT_NORMAL_BLACK_ON_LIGHT);

    ImageDraw::img_generic(ctx, image_id_resource_icon(input_resource_a), c.offset.x + 32, c.offset.y + 56);
    width = lang_text_draw(group_id, 13, c.offset.x + 60, c.offset.y + 60, FONT_NORMAL_BLACK_ON_LIGHT);

    if (b->stored_amount(input_resource_a) < 100) {
        lang_text_draw_amount(8, 10, 0, c.offset.x + 60 + width, c.offset.y + 60, FONT_NORMAL_BLACK_ON_LIGHT);
    } else {
        lang_text_draw_amount(8, 10, b->stored_amount(input_resource_a), c.offset.x + 60 + width, c.offset.y + 60, FONT_NORMAL_BLACK_ON_LIGHT);
    }

    int y_offset = 80;
    e_resource input_resource_b = b->first_material_id;
    ImageDraw::img_generic(ctx, image_id_resource_icon(input_resource_b), c.offset.x + 32, c.offset.y + y_offset);
    width = lang_text_draw(group_id, 14, c.offset.x + 60, c.offset.y + y_offset + 4, FONT_NORMAL_BLACK_ON_LIGHT);

    if (b->stored_amount(input_resource_b) < 100) {
        lang_text_draw_amount(8, 10, 0, c.offset.x + 60 + width, c.offset.y + y_offset + 4, FONT_NORMAL_BLACK_ON_LIGHT);
    } else {
        lang_text_draw_amount(8, 10, b->stored_amount(input_resource_b), c.offset.x + 60 + width, c.offset.y + y_offset + 4, FONT_NORMAL_BLACK_ON_LIGHT);
    }

    y_offset = 110;
    if (!c.has_road_access)
        window_building_draw_description_at(c, y_offset, 69, 25);
    else if (city_resource_is_mothballed(b->output_resource_first_id))
        window_building_draw_description_at(c, y_offset, group_id, 4);
    else if (b->num_workers <= 0)
        window_building_draw_description_at(c, y_offset, group_id, 5);
    else if (b->workshop_has_resources())
        window_building_draw_description_at(c, y_offset, group_id, 11);
    else if (c.worker_percentage >= 100)
        window_building_draw_description_at(c, y_offset, group_id, 6);
    else if (c.worker_percentage >= 75)
        window_building_draw_description_at(c, y_offset, group_id, 7);
    else if (c.worker_percentage >= 50)
        window_building_draw_description_at(c, y_offset, group_id, 8);
    else if (c.worker_percentage >= 25)
        window_building_draw_description_at(c, y_offset, group_id, 9);
    else
        window_building_draw_description_at(c, y_offset, group_id, 10);

    inner_panel_draw(c.offset + vec2i{ 16, y_offset + 40 }, { c.bgsize.x - 2, 4 });
    window_building_draw_employment(&c, y_offset + 48);
}