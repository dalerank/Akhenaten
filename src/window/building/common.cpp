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

    vec2i view_size = g_camera.size_pixels;
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

pcstr get_employment_info_text_key(object_info* c, building* b, int consider_house_covering) {
    const int city_population = g_city.population.current;

    if (b->num_workers >= b->max_workers) {
        if (consider_house_covering && b->houses_covered < 40) {
            return "#building_poor_worker_access";
        }
        return "";
    }
    if (city_population <= 0) {
        return "#building_no_people_in_city";
    }
    if (!consider_house_covering) {
        return "#building_labor_could_shift";
    }
    if (b->houses_covered <= 0) {
        return "#building_no_workers_nearby";
    }
    if (b->houses_covered < 40) {
        return "#building_poor_worker_access";
    }
    return "#building_labor_could_shift";
}

void draw_employment_details(object_info* c, building* b, int y_offset, pcstr text_key) {
    painter ctx = game.painter();
    y_offset += c->offset.y;
    ctx.img_generic(image_id_from_group(GROUP_CONTEXT_ICONS) + 14, vec2i{c->offset.x + 40, y_offset + 6});
    if (text_key && *text_key) {
        int width = lang_text_draw_amount(8, 12, b->num_workers, c->offset.x + 60, y_offset + 10, FONT_NORMAL_BLACK_ON_DARK);
        width += text_draw_number(b->max_workers, '(', "", c->offset.x + 70 + width, y_offset + 10, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw(69, 0, c->offset.x + 70 + width, y_offset + 10, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw(lang_text_from_key(text_key), vec2i{c->offset.x + 70, y_offset + 26}, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        int width = lang_text_draw_amount(8, 12, b->num_workers, c->offset.x + 60, y_offset + 16, FONT_NORMAL_BLACK_ON_DARK);
        width += text_draw_number(b->max_workers, '(', "", c->offset.x + 70 + width, y_offset + 16, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw(69, 0, c->offset.x + 70 + width, y_offset + 16, FONT_NORMAL_BLACK_ON_DARK);
    }
}

void draw_employment_details_ui(ui::widget &ui, object_info &c, building* b, int text_id) {
    ui["workers_text"].text_var("%d %s (%d %s", b->num_workers, ui::str(8, 12), b->max_workers, ui::str(69, 0));
    pcstr text_key = nullptr;
    if (text_id < 0) {
        text_key = get_employment_info_text_key(&c, b, 1);
    }

    if (text_key && *text_key) {
        ui["workers_desc"] = lang_text_from_key(text_key);
    }
}

void window_building_draw_employment(object_info* c, int y_offset) {
    building* b = building_get(c->bid);
    pcstr text_key = get_employment_info_text_key(c, b, 1);
    draw_employment_details(c, b, y_offset, text_key);
}

void window_building_draw_employment_without_house_cover(object_info* c, int y_offset) {
    building* b = building_get(c->bid);
    pcstr text_key = get_employment_info_text_key(c, b, 0);
    draw_employment_details(c, b, y_offset, text_key);
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
