#include "entertainment.h"

#include "building/building_menu.h"
#include "scenario/scenario.h"

#include "building/count.h"
#include "city/coverage.h"
#include "city/city.h"
#include "city/houses.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/generic_button.h"
#include "graphics/view/view.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "window/hold_festival.h"
#include "game/game.h"

#define ADVISOR_HEIGHT 20 // 23

#define PEOPLE_OFFSET 330
#define COVERAGE_OFFSET 470
#define COVERAGE_WIDTH 130

ui::advisor_entertainment_window g_advisor_entertainment_window;

static void button_hold_festival(int param1, int param2);

static generic_button hold_festival_button[] = {
  {102, 280, 300, 20, button_hold_festival, button_none, 0, 0},
};

static int focus_button_id;

static int get_entertainment_advice(void) {
    const house_demands &demands = g_city.houses;
    if (demands.missing.entertainment > demands.missing.more_entertainment) {
        return 3;
    } else if (!demands.missing.more_entertainment) {
        return g_city.avg_coverage.average_entertainment ? 1 : 0;
    } else if (g_city.entertainment.venue_needing_shows) {
        return 3 + g_city.entertainment.venue_needing_shows;
    } else {
        return 2;
    }
}

static void draw_entertainer(int type, int y_offset, e_building_type venue, int shows, int coverage, int entertain_coeff) {
    e_font font = FONT_NORMAL_WHITE_ON_DARK;

    if (!building_menu_is_building_enabled(venue)) {
        font = FONT_NORMAL_YELLOW;
        lang_text_draw(58, 47 + type, 40, y_offset, font);
        lang_text_draw_centered(58, 51, 150, y_offset, 100, font);
        lang_text_draw_centered(58, 51, 230, y_offset, 100, font);

        lang_text_draw(58, 51, PEOPLE_OFFSET + 5, y_offset, font);
        //        lang_text_draw(58, 51, COVERAGE_OFFSET, y_offset, font);
        lang_text_draw_centered(57, 7, COVERAGE_OFFSET, y_offset, COVERAGE_WIDTH, font);
    } else {
        lang_text_draw(58, 47 + type, 40, y_offset, font);
        text_draw_number_centered(building_count_active(venue), 150, y_offset, 100, font);
        text_draw_number_centered(shows, 230, y_offset, 100, font);
        int width = text_draw_number(entertain_coeff * building_count_active(venue), '_', " ", PEOPLE_OFFSET, y_offset, font);
        lang_text_draw(58, 5, PEOPLE_OFFSET + width, y_offset, font);
        if (coverage == 0) {
            lang_text_draw_centered(57, 7, COVERAGE_OFFSET, y_offset, COVERAGE_WIDTH, font);
        } else if (coverage < 100) {
            lang_text_draw_centered(57, 8 + coverage / 10, COVERAGE_OFFSET, y_offset, COVERAGE_WIDTH, font);
        } else {
            lang_text_draw_centered(57, 18, COVERAGE_OFFSET, y_offset, COVERAGE_WIDTH, font);
        }
    }
}

int ui::advisor_entertainment_window::draw_background() {
    painter ctx = game.painter();
    g_city.religion.calculate_gods_mood_targets();
    g_city.avg_coverage.update();

    outer_panel_draw(vec2i{0, 0}, 40, ADVISOR_HEIGHT);
    ImageDraw::img_generic(ctx, image_id_from_group(GROUP_ADVISOR_ICONS) + 8, vec2i{10, 10});

    lang_text_draw(58, 0, 60, 12, FONT_LARGE_BLACK_ON_LIGHT);

    // headers
    lang_text_draw(58, 1, 180, 42, FONT_NORMAL_BLACK_ON_LIGHT);                                      // working
    lang_text_draw(58, 55, 180, 56, FONT_NORMAL_BLACK_ON_LIGHT);                                     // stages
    lang_text_draw(58, 2, 260, 56, FONT_NORMAL_BLACK_ON_LIGHT);                                      // shows
    lang_text_draw(58, 3, PEOPLE_OFFSET + 10, 56, FONT_NORMAL_BLACK_ON_LIGHT);                       // can entertain
    lang_text_draw_centered(58, 4, COVERAGE_OFFSET, 56, COVERAGE_WIDTH, FONT_NORMAL_BLACK_ON_LIGHT); // city coverage

    inner_panel_draw(32, 70, 36, 8); // 5

    // theaters, jugglers
    int y_offset = 77;
    int y_dist = 23;

    draw_entertainer(0, y_offset, BUILDING_BOOTH, g_city.entertainment.booth_shows, g_coverage.booth, 400);
    draw_entertainer(1, y_offset + y_dist, BUILDING_BANDSTAND, g_city.entertainment.bandstand_shows, g_coverage.bandstand, 700);
    draw_entertainer(2, y_offset + y_dist * 2, BUILDING_PAVILLION, g_city.entertainment.pavilion_shows, g_coverage.pavilion, 1200);
    draw_entertainer(3, y_offset + y_dist * 3, BUILDING_SENET_HOUSE, g_city.entertainment.senet_house_plays, g_coverage.senet_house, 0);
    draw_entertainer(9, y_offset + y_dist * 4, BUILDING_ZOO, 0, 0, 0);

    lang_text_draw_multiline(58, 7 + get_entertainment_advice(), vec2i{60, 208}, 512, FONT_NORMAL_BLACK_ON_LIGHT);

    return ADVISOR_HEIGHT;
}

void ui::advisor_entertainment_window::draw_foreground() {
    //    if (!city_festival_is_planned())
    //        button_border_draw(102, 280, 300, 20, focus_button_id == 1);
}

int ui::advisor_entertainment_window::handle_mouse(const mouse* m) {
    return generic_buttons_handle_mouse(m, {0, 0}, hold_festival_button, 1, &focus_button_id);
}

static void button_hold_festival(int param1, int param2) {
    //    if (!city_festival_is_planned())
    //        window_hold_festival_show();
}

int ui::advisor_entertainment_window::get_tooltip_text() {
    if (focus_button_id) {
        return 112;
    }else {
        return 0;
    }
}

void ui::advisor_entertainment_window::init() {
    focus_button_id = 0;
}

advisor_window* ui::advisor_entertainment_window::instance() {
    return &g_advisor_entertainment_window;
}
