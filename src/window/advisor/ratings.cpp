#include "ratings.h"

#include "city/ratings.h"
#include "graphics/boilerplate.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "io/config/config.h"
#include "scenario/criteria.h"
#include "scenario/property.h"

#define ADVISOR_HEIGHT 27

static void button_rating(int rating, int param2);

static generic_button rating_buttons[] = {
  {80, 276, 120, 60, button_rating, button_none, SELECTED_RATING_CULTURE, 0},
  {200, 276, 120, 60, button_rating, button_none, SELECTED_RATING_PROSPERITY, 0},
  {320, 276, 120, 60, button_rating, button_none, SELECTED_RATING_MONUMENT, 0},
  {440, 276, 120, 60, button_rating, button_none, SELECTED_RATING_KINGDOM, 0},
};

static int focus_button_id;

static void draw_rating_column(int x_offset, int y_offset, int value, int has_reached) {
    int image_base = image_id_from_group(GROUP_RATINGS_COLUMN);
    int y = y_offset - image_get(image_base)->height;
    int value_to_draw = value * 0.75;
    if (config_get(CONFIG_UI_COMPLETE_RATING_COLUMNS)) {
        if (has_reached && value < 25)
            value_to_draw = 25;
    } else {
        // Default behaviour: not completing too small columns
        //        if (value < 30)
        //            has_reached = 0;
    }
    ImageDraw::img_generic(image_base, x_offset - 4, y);
    for (int i = 0; i < 2 * value_to_draw; i++)
        ImageDraw::img_generic(image_base + 1, x_offset + 11, --y);
    if (has_reached)
        ImageDraw::img_generic(image_base + 2, x_offset - 6, y - 50);
}

static void draw_rating(int id, int value, int open_play, int goal) {
    //    int value = city_rating_culture();
    int enabled = !open_play && goal;
    button_border_draw(rating_buttons[id].x,
                       rating_buttons[id].y,
                       rating_buttons[id].width,
                       rating_buttons[id].height,
                       focus_button_id == SELECTED_RATING_CULTURE);
    lang_text_draw_centered(53, 1 + id, rating_buttons[id].x, rating_buttons[id].y + 8, rating_buttons[id].width, FONT_NORMAL_BLACK_ON_LIGHT);
    text_draw_number_centered(value, rating_buttons[id].x, rating_buttons[id].y + 21, rating_buttons[id].width, FONT_LARGE_BLACK_ON_LIGHT);
    int width = text_draw_number(enabled ? goal : 0, '@', " ", rating_buttons[id].x + 5, rating_buttons[id].y + 45, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw(53, 5, rating_buttons[id].x + 5 + width, rating_buttons[id].y + 45, FONT_NORMAL_BLACK_ON_LIGHT);
    int has_reached = !enabled || value >= goal;
    draw_rating_column(rating_buttons[id].x + 30, rating_buttons[id].y, value, has_reached);
}

static int draw_background(void) {
    outer_panel_draw(0, 0, 40, ADVISOR_HEIGHT);
    ImageDraw::img_generic(image_id_from_group(GROUP_ADVISOR_ICONS) + 3, 10, 10);
    int width = lang_text_draw(53, 0, 60, 12, FONT_LARGE_BLACK_ON_LIGHT);
    if (!winning_population() || scenario_is_open_play()) {
        lang_text_draw(53, 7, 80 + width, 17, FONT_NORMAL_BLACK_ON_LIGHT);
    } else {
        width += lang_text_draw(53, 6, 80 + width, 17, FONT_NORMAL_BLACK_ON_LIGHT);
        text_draw_number(winning_population(), '@', ")", 80 + width, 17, FONT_NORMAL_BLACK_ON_LIGHT);
    }
    ImageDraw::img_generic(image_id_from_group(GROUP_ADVISOR_RATINGS_BACKGROUND), 60, 48 - 10);

    int open_play = scenario_is_open_play();

    // culture
    draw_rating(0, city_rating_culture(), open_play, winning_culture());
    draw_rating(1, city_rating_prosperity(), open_play, winning_prosperity());
    draw_rating(2, city_rating_monument(), open_play, winning_monuments());
    draw_rating(3, city_rating_kingdom(), open_play, winning_kingdom());

    // bottom info box
    int box_x = 44;
    int box_y = 340;
    int box_w = 520;
    inner_panel_draw(box_x, box_y, 35, 5);
    switch (city_rating_selected()) {
    case SELECTED_RATING_CULTURE:
        lang_text_draw(53, 1, box_x + 8, box_y + 4, FONT_NORMAL_WHITE_ON_DARK);
        if (city_rating_culture() <= 90) {
            lang_text_draw_multiline(
              53, 9 + city_rating_selected_explanation(), box_x + 8, box_y + 22, box_w, FONT_NORMAL_WHITE_ON_DARK);
        } else
            lang_text_draw_multiline(53, 50, box_x + 8, box_y + 22, box_w, FONT_NORMAL_WHITE_ON_DARK);
        break;
    case SELECTED_RATING_PROSPERITY:
        lang_text_draw(53, 2, box_x + 8, box_y + 4, FONT_NORMAL_WHITE_ON_DARK);
        if (city_rating_prosperity() <= 90) {
            lang_text_draw_multiline(
              53, 16 + city_rating_selected_explanation(), box_x + 8, box_y + 22, box_w, FONT_NORMAL_WHITE_ON_DARK);
        } else
            lang_text_draw_multiline(53, 51, box_x + 8, box_y + 22, box_w, FONT_NORMAL_WHITE_ON_DARK);
        break;
    case SELECTED_RATING_MONUMENT:
        lang_text_draw(53, 3, box_x + 8, box_y + 4, FONT_NORMAL_WHITE_ON_DARK);
        if (city_rating_monument() <= 90) {
            lang_text_draw_multiline(
              53, 41 + city_rating_selected_explanation(), box_x + 8, box_y + 22, box_w, FONT_NORMAL_WHITE_ON_DARK);
        } else
            lang_text_draw_multiline(53, 52, box_x + 8, box_y + 22, box_w, FONT_NORMAL_WHITE_ON_DARK);
        break;
    case SELECTED_RATING_KINGDOM:
        lang_text_draw(53, 4, box_x + 8, box_y + 4, FONT_NORMAL_WHITE_ON_DARK);
        if (city_rating_kingdom() <= 90) {
            lang_text_draw_multiline(
              53, 27 + city_rating_selected_explanation(), box_x + 8, box_y + 22, box_w, FONT_NORMAL_WHITE_ON_DARK);
        } else
            lang_text_draw_multiline(53, 53, box_x + 8, box_y + 22, box_w, FONT_NORMAL_WHITE_ON_DARK);
        break;
    default:
        lang_text_draw_centered(53, 8, box_x + 8, 380, box_w, FONT_NORMAL_WHITE_ON_DARK);
        break;
    }

    return ADVISOR_HEIGHT;
}
static void draw_foreground(void) {
    button_border_draw(rating_buttons[0].x,
                       rating_buttons[0].y,
                       rating_buttons[0].width,
                       rating_buttons[0].height,
                       focus_button_id == SELECTED_RATING_CULTURE);
    button_border_draw(rating_buttons[1].x,
                       rating_buttons[1].y,
                       rating_buttons[1].width,
                       rating_buttons[1].height,
                       focus_button_id == SELECTED_RATING_PROSPERITY);
    button_border_draw(rating_buttons[2].x,
                       rating_buttons[2].y,
                       rating_buttons[2].width,
                       rating_buttons[2].height,
                       focus_button_id == SELECTED_RATING_MONUMENT);
    button_border_draw(rating_buttons[3].x,
                       rating_buttons[3].y,
                       rating_buttons[3].width,
                       rating_buttons[3].height,
                       focus_button_id == SELECTED_RATING_KINGDOM);
}

static int handle_mouse(const mouse* m) {
    return generic_buttons_handle_mouse(m, 0, 0, rating_buttons, 4, &focus_button_id);
}

static void button_rating(int rating, int param2) {
    city_rating_select(rating);
    window_invalidate();
}

static int get_tooltip_text(void) {
    switch (focus_button_id) {
    case SELECTED_RATING_CULTURE:
        return 102;
    case SELECTED_RATING_PROSPERITY:
        return 103;
    case SELECTED_RATING_MONUMENT:
        return 104;
    case SELECTED_RATING_KINGDOM:
        return 105;
    default:
        return 0;
    }
}

const advisor_window_type* window_advisor_ratings(void) {
    static const advisor_window_type window = {draw_background, draw_foreground, handle_mouse, get_tooltip_text};
    return &window;
}
