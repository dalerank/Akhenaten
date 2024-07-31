#include "graphics/elements/ui.h"

#include "window/building/common.h"
#include "sound/sound_building.h"
#include "game/game.h"
#include "city/object_info.h"
#include "city/city_resource.h"
#include "core/calc.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"

struct workshop_info_window : ui::widget {};

workshop_info_window g_workshop_info_window;

ANK_REGISTER_CONFIG_ITERATOR(config_load_workshop_info_window);
void config_load_workshop_info_window() {
    g_config_arch.r_section("workshop_info_window", [] (archive arch) {
        g_workshop_info_window.load(arch);
    });
}

void building_workshop_draw_foreground(object_info &c) {
    g_workshop_info_window.draw();

    window_building_draw_employment(&c, 142);
}

void building_workshop_draw_background(object_info& c, pcstr type, e_resource resource, e_resource input_resource) {
    auto &ui = g_workshop_info_window;

    building *b = building_get(c.building_id);
    const auto &params = b->dcast()->params();
    c.help_id = params.meta.help_id;
    window_building_play_sound(&c, snd::get_building_info_sound(type));

    int pct_done = calc_percentage<int>(b->data.industry.progress, 400);
    int group_id = params.meta.text_id;
    ui["background"].size = c.bgsize;
    ui["produce_icon"].image(resource);
    ui["title"].size.x = c.bgwidth_px();
    ui["title"].text((pcstr)lang_get_string(group_id, 0));
    ui["ready_prod"].text_var("%s %u%% %s", (pcstr)lang_get_string(group_id, 2), pct_done, (pcstr)lang_get_string(group_id, 3));
    ui["resource_icon"].image(input_resource);
    ui["resource_stored"].text_var("%s %u", (pcstr)lang_get_string(group_id, 12), b->stored_amount());

    std::pair<int, int> trouble_text{0, 0};
    if (!c.has_road_access) { trouble_text = {69, 25}; }
    else if (city_resource_is_mothballed(resource)) { trouble_text = {group_id, 4}; }
    else if (b->num_workers <= 0) { trouble_text = {group_id, 5}; }
    else if (!b->workshop_has_resources()) { trouble_text = {group_id, 11}; }
    else if (c.worker_percentage >= 100) { trouble_text = {group_id, 6}; }
    else if (c.worker_percentage >= 75) { trouble_text = {group_id, 7}; }
    else if (c.worker_percentage >= 50) { trouble_text = {group_id, 8}; }
    else if (c.worker_percentage >= 25) { trouble_text = {group_id, 9}; }
    else { trouble_text = {group_id, 10}; }

    ui["warning_text"].width(c.bgwidth_px() - 40);
    ui["warning_text"].text((pcstr)lang_get_string(trouble_text.first, trouble_text.second));

    ui["workers_panel"].size.x = c.bgsize.x - 2;
}

void building_workshop_draw_background(object_info& c, pcstr type, e_resource resource, e_resource input_resource_a, e_resource input_resource_b) {

    painter ctx = game.painter();
    building *b = building_get(c.building_id);
    const auto &params = b->dcast()->params();
    c.help_id = params.meta.help_id;
    int group_id = params.meta.text_id;

    window_building_play_sound(&c, snd::get_building_info_sound(type));

    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    ImageDraw::img_generic(ctx, image_id_resource_icon(resource), c.offset.x + 10, c.offset.y + 10);
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
    else if (city_resource_is_mothballed(resource))
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

    inner_panel_draw(c.offset.x + 16, c.offset.y + y_offset + 40, c.bgsize.x - 2, 4);
    window_building_draw_employment(&c, y_offset + 48);
}