#include "advisor_health.h"

#include "building/count.h"
#include "city/coverage.h"
#include "city/health.h"
#include "city/city.h"
#include "city/population.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "game/game.h"

#define ADVISOR_HEIGHT 18

ui::advisor_health_window g_advisor_health_window;

static int get_health_advice() {
    house_demands &demands = g_city.houses;
    switch (demands.health) {
    case 1:
        return demands.requiring.water_supply ? 1 : 0;
    case 2:
        return demands.requiring.dentist ? 3 : 2;
    case 3:
        return demands.requiring.physician ? 5 : 4;
    case 4:
        return 6;
    default:
        return 7;
    }
}

void ui::advisor_health_window::draw_foreground() {
    outer_panel_draw(vec2i{ 0, 0 }, 40, ADVISOR_HEIGHT);
    painter ctx = game.painter();
    ImageDraw::img_generic(ctx, image_id_from_group(GROUP_ADVISOR_ICONS) + 6, 10, 10);

    lang_text_draw(56, 0, 60, 12, FONT_LARGE_BLACK_ON_LIGHT);
    if (city_population() >= 200) {
        lang_text_draw_multiline(56, g_city.health.value / 10 + 16, vec2i{ 60, 46 }, 512, FONT_NORMAL_BLACK_ON_LIGHT);
    } else {
        lang_text_draw_multiline(56, 15, vec2i{ 60, 46 }, 512, FONT_NORMAL_BLACK_ON_LIGHT);
    }
    lang_text_draw(56, 3, 180, 94, FONT_SMALL_PLAIN);
    lang_text_draw(56, 4, 290, 94, FONT_SMALL_PLAIN);
    lang_text_draw_centered(56, 5, 440, 94, 160, FONT_SMALL_PLAIN);

    inner_panel_draw(32, 108, 36, 5);

    // apothecary
    lang_text_draw_amount(8, 24, building_count_total(BUILDING_APOTHECARY), 40, 112, FONT_NORMAL_BLACK_ON_DARK);
    text_draw_number_centered(building_count_active(BUILDING_APOTHECARY), 150, 112, 100, FONT_NORMAL_BLACK_ON_DARK);
    lang_text_draw_centered(56, 2, 290, 112, 120, FONT_NORMAL_BLACK_ON_DARK);
    lang_text_draw_centered(56, 2, 440, 112, 160, FONT_NORMAL_BLACK_ON_DARK);

    // dentist
    lang_text_draw_amount(8, 26, building_count_total(BUILDING_DENTIST), 40, 132, FONT_NORMAL_BLACK_ON_DARK);
    text_draw_number_centered(building_count_active(BUILDING_DENTIST), 150, 132, 100, FONT_NORMAL_BLACK_ON_DARK);
    lang_text_draw_centered(56, 2, 290, 132, 120, FONT_NORMAL_BLACK_ON_DARK);
    lang_text_draw_centered(56, 2, 440, 132, 160, FONT_NORMAL_BLACK_ON_DARK);

    // mortuary
    lang_text_draw_amount(8, 28, building_count_total(BUILDING_MORTUARY), 40, 152, FONT_NORMAL_BLACK_ON_DARK);
    text_draw_number_centered(building_count_active(BUILDING_MORTUARY), 150, 152, 100, FONT_NORMAL_BLACK_ON_DARK);
    lang_text_draw_centered(56, 2, 290, 152, 120, FONT_NORMAL_BLACK_ON_DARK);
    lang_text_draw_centered(56, 2, 440, 152, 160, FONT_NORMAL_BLACK_ON_DARK);

    // physicians
    lang_text_draw_amount(8, 30, building_count_total(BUILDING_PHYSICIAN), 40, 172, FONT_NORMAL_BLACK_ON_DARK);
    text_draw_number_centered(building_count_active(BUILDING_PHYSICIAN), 150, 172, 100, FONT_NORMAL_BLACK_ON_DARK);

    int width = text_draw_number(1000 * building_count_active(BUILDING_MORTUARY), '@', " ", 280, 172, FONT_NORMAL_BLACK_ON_DARK);
    lang_text_draw(56, 6, 280 + width, 172, FONT_NORMAL_BLACK_ON_DARK);

    int pct_physician = g_coverage.physician;
    if (pct_physician == 0) {
        lang_text_draw_centered(57, 10, 440, 172, 160, FONT_NORMAL_BLACK_ON_DARK);
    } else if (pct_physician < 100) {
        lang_text_draw_centered(57, pct_physician / 10 + 11, 440, 172, 160, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        lang_text_draw_centered(57, 21, 440, 172, 160, FONT_NORMAL_BLACK_ON_DARK);
    }

    lang_text_draw_multiline(56, 7 + get_health_advice(), vec2i{ 60, 194 }, 512, FONT_NORMAL_BLACK_ON_LIGHT);

}

int ui::advisor_health_window::draw_background() {
    
    return ADVISOR_HEIGHT;
}

advisor_window* ui::advisor_health_window::instance() {
    return &g_advisor_health_window;
}
