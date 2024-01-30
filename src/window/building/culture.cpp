#include "culture.h"

#include "building/building.h"
#include "graphics/graphics.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "io/gamefiles/lang.h"
#include "window/building/common.h"

void window_building_draw_oracle(object_info* c) {
    c->help_id = 67;
    window_building_play_sound(c, "wavs/oracle.wav");
    outer_panel_draw(c->offset, c->width_blocks, c->height_blocks);
    lang_text_draw_centered(110, 0, c->offset.x, c->offset.y + 12, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    window_building_draw_description_at(c, 16 * c->height_blocks - 158, 110, 1);
}

void window_building_draw_pavilion(object_info* c) {
    c->help_id = 73;
    window_building_play_sound(c, "wavs/colloseum.wav");
    outer_panel_draw(c->offset, c->width_blocks, c->height_blocks);
    lang_text_draw_centered(74, 0, c->offset.x, c->offset.y + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    building* b = building_get(c->building_id);

    if (!c->has_road_access)
        window_building_draw_description(c, 69, 25);
    else if (b->num_workers <= 0)
        window_building_draw_description(c, 74, 6);
    else if (!b->data.entertainment.num_shows)
        window_building_draw_description(c, 74, 2);
    else if (b->data.entertainment.num_shows == 2)
        window_building_draw_description(c, 74, 3);
    else if (b->data.entertainment.days1)
        window_building_draw_description(c, 74, 5);
    else if (b->data.entertainment.days2)
        window_building_draw_description(c, 74, 4);

    inner_panel_draw(c->offset.x + 16, c->offset.y + 136, c->width_blocks - 2, 6);
    window_building_draw_employment(c, 138);
    if (b->data.entertainment.days1 > 0) {
        int width = lang_text_draw(74, 8, c->offset.x + 32, c->offset.y + 182, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw_amount(8, 44, 2 * b->data.entertainment.days1, c->offset.x + width + 32, c->offset.y + 182, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        lang_text_draw(74, 7, c->offset.x + 32, c->offset.y + 182, FONT_NORMAL_BLACK_ON_DARK);
    }
    if (b->data.entertainment.days2 > 0) {
        int width = lang_text_draw(74, 10, c->offset.x + 32, c->offset.y + 202, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw_amount(8, 44, 2 * b->data.entertainment.days2, c->offset.x + width + 32, c->offset.y + 202, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        lang_text_draw(74, 9, c->offset.x + 32, c->offset.y + 202, FONT_NORMAL_BLACK_ON_DARK);
    }
}

void window_building_draw_senet_house(object_info* c) {
    c->help_id = 74;
    window_building_play_sound(c, "wavs/hippodrome.wav");
    outer_panel_draw(c->offset, c->width_blocks, c->height_blocks);
    lang_text_draw_centered(73, 0, c->offset.x, c->offset.y + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    building* b = building_get(c->building_id);
    if (!c->has_road_access)
        window_building_draw_description(c, 69, 25);
    else if (b->num_workers <= 0)
        window_building_draw_description(c, 73, 4);
    else if (!b->data.entertainment.num_shows)
        window_building_draw_description(c, 73, 2);
    else if (b->data.entertainment.days1)
        window_building_draw_description(c, 73, 3);

    inner_panel_draw(c->offset.x + 16, c->offset.y + 136, c->width_blocks - 2, 6);
    window_building_draw_employment(c, 138);
    if (b->data.entertainment.days1 > 0) {
        int width = lang_text_draw(73, 6, c->offset.x + 32, c->offset.y + 202, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw_amount(8, 44, 2 * b->data.entertainment.days1, c->offset.x + width + 32, c->offset.y + 202, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        lang_text_draw(73, 5, c->offset.x + 32, c->offset.y + 202, FONT_NORMAL_BLACK_ON_DARK);
    }
}

// TODO: fix festival square panel
void window_building_draw_festival_square(object_info* c) {
    const int32_t group_id = 188;
    c->help_id = 75;
    window_building_play_sound(c, "wavs/prefecture.wav"); // TODO: change to festival square

    outer_panel_draw(c->offset, c->width_blocks, c->height_blocks);
    lang_text_draw_centered(group_id, 0, c->offset.x, c->offset.y + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
}
