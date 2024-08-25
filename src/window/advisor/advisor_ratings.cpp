#include "advisor_ratings.h"

#include "city/city.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/view/view.h"
#include "graphics/elements/ui.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "config/config.h"
#include "scenario/criteria.h"
#include "scenario/scenario.h"
#include "game/game.h"

#include "js/js_game.h"

static void button_rating(int rating, int param2);
ui::advisor_ratings_window g_advisor_rating_window;

ANK_REGISTER_CONFIG_ITERATOR(config_load_advisor_rating);
void config_load_advisor_rating() {
    g_config_arch.r_section("advisor_rating_window", [] (archive arch) {
        auto &ui = g_advisor_rating_window;

        ui.load(arch);
        ui.column_offset = arch.r_vec2i("column_offset");
    });
}

static generic_button rating_buttons[] = {
  {80, 276, 120, 60, button_rating, button_none,  e_selected_rating_culture, 0},
  {200, 276, 120, 60, button_rating, button_none, e_selected_rating_prosperity, 0},
  {320, 276, 120, 60, button_rating, button_none, e_selected_rating_monument, 0},
  {440, 276, 120, 60, button_rating, button_none, e_selected_rating_kingdom, 0},
};

static void draw_rating_column(int x_offset, int y_offset, int value, int has_reached) {
    painter ctx = game.painter();
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

    ImageDraw::img_generic(ctx, image_base, x_offset - 4, y);
    for (int i = 0; i < 2 * value_to_draw; i++) {
        ImageDraw::img_generic(ctx, image_base + 1, x_offset + 11, --y);
    }

    if (has_reached) {
        ImageDraw::img_generic(ctx, image_base + 2, x_offset - 6, y - 50);
    }
}

static void draw_rating(int id, int value, int open_play, int goal) {
    auto &w = g_advisor_rating_window;
    //    int value = city_rating_culture();
    int enabled = !open_play && goal;
    button_border_draw(rating_buttons[id].x, rating_buttons[id].y, rating_buttons[id].width, rating_buttons[id].height, w.focus_button_id == e_selected_rating_culture);
    lang_text_draw_centered(53, 1 + id, rating_buttons[id].x, rating_buttons[id].y + 8, rating_buttons[id].width, FONT_NORMAL_BLACK_ON_LIGHT);
    text_draw_number_centered(value, rating_buttons[id].x, rating_buttons[id].y + 21, rating_buttons[id].width, FONT_LARGE_BLACK_ON_LIGHT);
    int width = text_draw_number(enabled ? goal : 0, '@', " ", rating_buttons[id].x + 5, rating_buttons[id].y + 45, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw(53, 5, rating_buttons[id].x + 5 + width, rating_buttons[id].y + 45, FONT_NORMAL_BLACK_ON_LIGHT);
    int has_reached = !enabled || value >= goal;
    draw_rating_column(rating_buttons[id].x + w.column_offset.x, rating_buttons[id].y + w.column_offset.y, value, has_reached);
}

int ui::advisor_ratings_window::draw_background() {
    bstring128 caption = (pcstr)ui::str(53, 7);
    if (!(!winning_population() || scenario_is_open_play())) {
        caption = (pcstr)ui::str(53, 6);
        caption.append("%u", winning_population());
    }
    ui["population_label"].text(caption);

    return 0;
}

void ui::advisor_ratings_window::draw_foreground() {
    ui.draw();

    int open_play = scenario_is_open_play();

    // culture
    draw_rating(0, g_city.ratings.culture, open_play, winning_culture());
    draw_rating(1, g_city.ratings.prosperity, open_play, winning_prosperity());
    draw_rating(2, g_city.ratings.monument, open_play, winning_monuments());
    draw_rating(3, g_city.ratings.kingdom, open_play, winning_kingdom());

    // bottom info box
    int box_x = 44;
    int box_y = 340;
    int box_w = 520;
    inner_panel_draw(box_x, box_y, 35, 5);
    switch (g_city.ratings.selected) {
    case e_selected_rating_culture:
        lang_text_draw(53, 1, box_x + 8, box_y + 4, FONT_NORMAL_WHITE_ON_DARK);
        if (g_city.ratings.culture <= 90) {
            lang_text_draw_multiline(53, 9 + g_city.ratings.selected_explanation(), vec2i{box_x + 8, box_y + 22}, box_w, FONT_NORMAL_WHITE_ON_DARK);
        } else
            lang_text_draw_multiline(53, 50, vec2i{box_x + 8, box_y + 22}, box_w, FONT_NORMAL_WHITE_ON_DARK);
        break;

    case e_selected_rating_prosperity:
        lang_text_draw(53, 2, box_x + 8, box_y + 4, FONT_NORMAL_WHITE_ON_DARK);
        if (g_city.ratings.prosperity <= 90) {
            lang_text_draw_multiline(53, 16 + g_city.ratings.selected_explanation(), vec2i{box_x + 8, box_y + 22}, box_w, FONT_NORMAL_WHITE_ON_DARK);
        } else
            lang_text_draw_multiline(53, 51, vec2i{box_x + 8, box_y + 22}, box_w, FONT_NORMAL_WHITE_ON_DARK);
        break;
    case e_selected_rating_monument:
        lang_text_draw(53, 3, box_x + 8, box_y + 4, FONT_NORMAL_WHITE_ON_DARK);
        if (g_city.ratings.monument <= 90) {
            lang_text_draw_multiline(53, 41 + g_city.ratings.selected_explanation(), vec2i{box_x + 8, box_y + 22}, box_w, FONT_NORMAL_WHITE_ON_DARK);
        } else
            lang_text_draw_multiline(53, 52, vec2i{box_x + 8, box_y + 22}, box_w, FONT_NORMAL_WHITE_ON_DARK);
        break;

    case e_selected_rating_kingdom:
        lang_text_draw(53, 4, box_x + 8, box_y + 4, FONT_NORMAL_WHITE_ON_DARK);
        if (g_city.ratings.kingdom <= 90) {
            lang_text_draw_multiline(53, 27 +g_city.ratings.selected_explanation(), vec2i{box_x + 8, box_y + 22}, box_w, FONT_NORMAL_WHITE_ON_DARK);
        } else
            lang_text_draw_multiline(53, 53, vec2i{box_x + 8, box_y + 22}, box_w, FONT_NORMAL_WHITE_ON_DARK);
        break;

    default:
        lang_text_draw_centered(53, 8, box_x + 8, 380, box_w, FONT_NORMAL_WHITE_ON_DARK);
        break;
    }

    button_border_draw(rating_buttons[0].x, rating_buttons[0].y, rating_buttons[0].width, rating_buttons[0].height, focus_button_id == e_selected_rating_culture);
    button_border_draw(rating_buttons[1].x, rating_buttons[1].y, rating_buttons[1].width, rating_buttons[1].height, focus_button_id == e_selected_rating_prosperity);
    button_border_draw(rating_buttons[2].x, rating_buttons[2].y, rating_buttons[2].width, rating_buttons[2].height, focus_button_id == e_selected_rating_monument);
    button_border_draw(rating_buttons[3].x, rating_buttons[3].y, rating_buttons[3].width, rating_buttons[3].height, focus_button_id == e_selected_rating_kingdom);
}

int ui::advisor_ratings_window::handle_mouse(const mouse* m) {
    return generic_buttons_handle_mouse(m, {0, 0}, rating_buttons, 4, &focus_button_id);
}

static void button_rating(int rating, int param2) {
    g_city.ratings.selected = rating;
    window_invalidate();
}

int ui::advisor_ratings_window::get_tooltip_text(void) {
    switch (g_advisor_rating_window.focus_button_id) {
    case e_selected_rating_culture:
        return 102;
    case e_selected_rating_prosperity:
        return 103;
    case e_selected_rating_monument:
        return 104;
    case e_selected_rating_kingdom:
        return 105;
    default:
        return 0;
    }
}

advisor_window* ui::advisor_ratings_window::instance() {
    return &g_advisor_rating_window;
}
