#include "utility.h"

#include "building/building_roadblock.h"
#include "graphics/graphics.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/image.h"
#include "graphics/window.h"
#include "grid/water_supply.h"
#include "window/building/common.h"
#include "window/window_building_info.h"

void window_building_draw_burning_ruin(object_info* c) {
    c->help_id = 0;
    window_building_play_sound(c, "wavs/ruin.wav");
    outer_panel_draw(c->offset, c->bgsize.x, c->bgsize.y);
    lang_text_draw_centered(111, 0, c->offset.x, c->offset.y + 10, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);

    lang_text_draw(41, c->rubble_building_type, c->offset.x + 32, c->offset.y + 16 * c->bgsize.y - 173, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw_multiline(111, 1, c->offset + vec2i{32, 16 * c->bgsize.y - 143}, 16 * (c->bgsize.x - 4), FONT_NORMAL_BLACK_ON_LIGHT);
}
void window_building_draw_rubble(object_info* c) {
    c->help_id = 0;
    window_building_play_sound(c, "wavs/ruin.wav");
    outer_panel_draw(c->offset, c->bgsize.x, c->bgsize.y);
    lang_text_draw_centered(140, 0, c->offset.x, c->offset.y + 10, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);

    lang_text_draw(41, c->rubble_building_type, c->offset.x + 32, c->offset.y + 16 * c->bgsize.y - 173, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw_multiline(140, 1, c->offset + vec2i{32, 16 * c->bgsize.y - 143}, 16 * (c->bgsize.x - 4), FONT_NORMAL_BLACK_ON_LIGHT);
}

void window_building_draw_aqueduct(object_info* c) {
    c->help_id = 60;
    window_building_play_sound(c, "wavs/aquaduct.wav");
    outer_panel_draw(c->offset, c->bgsize.x, c->bgsize.y);
    lang_text_draw_centered(141, 0, c->offset.x, c->offset.y + 10, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    window_building_draw_description_at(c, 16 * c->bgsize.y - 144, 141, c->aqueduct_has_water ? 1 : 2);
}

void window_building_draw_fountain(object_info* c) {
    c->help_id = 61;
    window_building_play_sound(c, "wavs/fountain.wav");
    outer_panel_draw(c->offset, c->bgsize.x, c->bgsize.y);
    lang_text_draw_centered(108, 0, c->offset.x, c->offset.y + 10, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    int text_id;
    building* b = building_get(c->building_id);
    if (b->has_water_access) {
        if (b->num_workers > 0)
            text_id = 1;
        else
            text_id = 2;
    } else if (c->has_reservoir_pipes)
        text_id = 2;
    else
        text_id = 3;
    window_building_draw_description(c, 108, text_id);
    inner_panel_draw(c->offset.x + 16, c->offset.y + 166, c->bgsize.x - 2, 4);
    window_building_draw_employment_without_house_cover(c, 172);
}

void window_building_draw_mission_post(object_info* c) {
    c->help_id = 8;
    window_building_play_sound(c, "wavs/mission.wav");
    outer_panel_draw(c->offset, c->bgsize.x, c->bgsize.y);
    lang_text_draw_centered(134, 0, c->offset.x, c->offset.y + 10, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    window_building_draw_description(c, 134, 1);
    inner_panel_draw(c->offset.x + 16, c->offset.y + 136, c->bgsize.x - 2, 4);
    window_building_draw_employment_without_house_cover(c, 142);
}

static void draw_native(object_info* c, int group_id) {
    c->help_id = 0;
    window_building_play_sound(c, "wavs/empty_land.wav");
    outer_panel_draw(c->offset, c->bgsize.x, c->bgsize.y);
    lang_text_draw_centered(group_id, 0, c->offset.x, c->offset.y + 10, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    window_building_draw_description_at(c, 106, group_id, 1);
}

void window_building_draw_native_hut(object_info* c) {
    draw_native(c, 131);
}
void window_building_draw_native_meeting(object_info* c) {
    draw_native(c, 132);
}
void window_building_draw_native_crops(object_info* c) {
    draw_native(c, 133);
}
