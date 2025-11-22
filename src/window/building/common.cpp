#include "common.h"

#include "building/building.h"
#include "city/city_labor.h"
#include "city/city.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/lang_text.h"
#include "graphics/screen.h"
#include "graphics/text.h"
#include "graphics/view/view.h"
#include "sound/sound.h"
#include "game/game.h"

vec2i window_building_set_possible_position(vec2i offset, vec2i blocks) {
    int dialog_width = 16 * blocks.x;
    int dialog_height = 16 * blocks.y;
    vec2i view_pos, view_size;
    city_view_get_viewport(g_city_view, view_pos, view_size);
    view_size.x -= MARGIN_POSITION;

    if (offset.y + dialog_height > screen_height() - MARGIN_POSITION) {
        offset.y -= dialog_height;
    }

    offset.y = (offset.y < MIN_Y_POSITION) ? MIN_Y_POSITION : offset.y;
    
    if (offset.x + dialog_width > view_size.x) {
        offset.x = view_size.x - dialog_width;
    }

    return offset;
}

int window_building_get_vertical_offset(object_info* c, int new_window_height) {
    new_window_height = new_window_height * 16;
    int old_window_height = c->bgsize.y * 16;

    int center = (old_window_height / 2) + c->offset.y;
    int new_window_y = center - (new_window_height / 2);

    if (new_window_y < MIN_Y_POSITION) {
        new_window_y = MIN_Y_POSITION;
    } else {
        int height = screen_height() - MARGIN_POSITION;

        if (new_window_y + new_window_height > height)
            new_window_y = height - new_window_height;
    }

    return new_window_y;
}

textid get_employment_info_text_id(object_info* c, building* b, int consider_house_covering) {
    uint8_t text_id;
    const int city_population = g_city.population.current;

    if (b->num_workers >= b->max_workers)
        text_id = 0;
    else if (city_population <= 0)
        text_id = 16; // no people in city
    else if (!consider_house_covering)
        text_id = 19;
    else if (b->houses_covered <= 0)
        text_id = 17; // no employees nearby
    else if (b->houses_covered < 40)
        text_id = 20; // poor access to employees
    else if (g_city.labor.workers_allocated(b->labor_category) <= 0)
        text_id = 18; // no people allocated
    else {
        text_id = 19; // too few people allocated
    }

    if (!text_id && consider_house_covering && b->houses_covered < 40) {
        text_id = 20; // poor access to employees
    }

    return { 69, text_id };
}

void draw_employment_details(object_info* c, building* b, int y_offset, int text_id) {
    painter ctx = game.painter();
    y_offset += c->offset.y;
    ctx.img_generic(image_id_from_group(GROUP_CONTEXT_ICONS) + 14, vec2i{c->offset.x + 40, y_offset + 6});
    if (text_id) {
        int width = lang_text_draw_amount(8, 12, b->num_workers, c->offset.x + 60, y_offset + 10, FONT_NORMAL_BLACK_ON_DARK);
        width += text_draw_number(b->max_workers, '(', "", c->offset.x + 70 + width, y_offset + 10, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw(69, 0, c->offset.x + 70 + width, y_offset + 10, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw(69, text_id, c->offset.x + 70, y_offset + 26, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        int width = lang_text_draw_amount(8, 12, b->num_workers, c->offset.x + 60, y_offset + 16, FONT_NORMAL_BLACK_ON_DARK);
        width += text_draw_number(b->max_workers, '(', "", c->offset.x + 70 + width, y_offset + 16, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw(69, 0, c->offset.x + 70 + width, y_offset + 16, FONT_NORMAL_BLACK_ON_DARK);
    }
}

void draw_employment_details_ui(ui::widget &ui, object_info &c, building* b, int text_id) {
    ui["workers_text"].text_var("%d %s (%d %s", b->num_workers, ui::str(8, 12), b->max_workers, ui::str(69, 0));
    if (text_id < 0) {
        text_id = get_employment_info_text_id(&c, b, 1).id;
    } 

    if (text_id > 0) {
        ui["workers_desc"] = ui::str(69, text_id);
    }
}

void window_building_draw_employment(object_info* c, int y_offset) {
    building* b = building_get(c->bid);
    int text_id = get_employment_info_text_id(c, b, 1).id;
    draw_employment_details(c, b, y_offset, text_id);
}

void window_building_draw_employment_without_house_cover(object_info* c, int y_offset) {
    building* b = building_get(c->bid);
    int text_id = get_employment_info_text_id(c, b, 0).id;
    draw_employment_details(c, b, y_offset, text_id);
}

void window_building_draw_description(object_info* c, int text_group, int text_id) {
    lang_text_draw_multiline(text_group, text_id, c->offset + vec2i{32, 56}, 16 * (c->bgsize.x - 4), FONT_NORMAL_BLACK_ON_LIGHT);
}
void window_building_draw_description_at(object_info* c, int y_offset, int text_group, int text_id) {
    lang_text_draw_multiline(text_group, text_id, c->offset + vec2i{32, y_offset}, 16 * (c->bgsize.x - 4), FONT_NORMAL_BLACK_ON_LIGHT);
}

void window_building_play_sound(object_info* c, xstring sound_file) {
    if (c->can_play_sound) {
        g_sound.speech_play_file(sound_file, 255);
        c->can_play_sound = 0;
    }
}
