#include "common.h"
#include "sound/sound_speech.h"

#include "building/building.h"
#include "city/city_labor.h"
#include "city/city.h"
#include "city/city_population.h"
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
    const int population = city_population().current;

    if (b->num_workers >= b->max_workers) {
        if (consider_house_covering && b->houses_covered < 40) {
            return "#building_poor_worker_access";
        }
        return "";
    }
    if (population <= 0) {
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

void draw_employment_details_ui(ui::widget &ui, object_info &c, building* b, int text_id) {
    ui["workers_text"].text_var("%d %s (%d %s", b->num_workers, ui::str(8, 12), b->max_workers, ui::str(69, 0));
    pcstr text_key = nullptr;
    if (text_id < 0) {
        text_key = get_employment_info_text_key(&c, b, 1);
    }

    if (text_key && *text_key) {
        ui["workers_desc"] = localization().text_from_key(text_key);
    }
}

void window_building_play_sound(object_info* c, xstring sound_file) {
    if (c->can_play_sound) {
        sound_speech().play_file(sound_file);
        c->can_play_sound = 0;
    }
}
