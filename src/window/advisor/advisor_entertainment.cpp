#include "advisor_entertainment.h"

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

void ui::advisor_entertainment_window::draw_entertainer(int type, pcstr prefix, e_building_type venue, int shows, int coverage, int entertain_coeff) {
    e_font font = building_menu_is_building_enabled(venue) ? FONT_NORMAL_WHITE_ON_DARK : FONT_NORMAL_YELLOW;

    auto _s = [prefix] (pcstr key) { return bstring32(prefix, "_", key); };
    if (!building_menu_is_building_enabled(venue)) {
        ui[_s("total")].text(font, ui::str(58, 47 + type));
        ui[_s("active")].text(font, ui::str(58, 51));
        ui[_s("shows")].text(font, ui::str(58, 51));
        ui[_s("care")].text(font, ui::str(58, 51));
        ui[_s("cvg")].text(font, ui::str(57, 7));
    } else {
        ui[_s("total")].text(font, ui::str(58, 47 + type));
        ui[_s("active")].text(font, bstring32(building_count_active(venue)));
        ui[_s("shows")].text(font, bstring32(shows));
        ui[_s("care")].text(font, bstring32().printf("%u %s", entertain_coeff * building_count_active(venue), ui::str(58, 5)));
        textid textcvg{ 57, 18 };
        if (coverage == 0) { textcvg = { 57, 7 };
        } else if (coverage < 100) { textcvg = { 57, 8 + coverage / 10 }; }

        ui[_s("cvg")].text(font, ui::str(textcvg));
    }
}

int ui::advisor_entertainment_window::draw_background() {
    return 0;
}

int ui::advisor_entertainment_window::ui_handle_mouse(const mouse *m) {
    ui.begin_widget(screen_dialog_offset());
    int result = advisor_window::ui_handle_mouse(m);
    ui.end_widget();

    return result;
}

void ui::advisor_entertainment_window::ui_draw_foreground() {
    ui.begin_widget(screen_dialog_offset());
    ui.draw();

    painter ctx = game.painter();
    g_city.religion.calculate_gods_mood_targets();
    g_city.avg_coverage.update();

    draw_entertainer(0, "booth", BUILDING_BOOTH, g_city.entertainment.booth_shows, g_coverage.booth, 400);
    draw_entertainer(1, "bandstand", BUILDING_BANDSTAND, g_city.entertainment.bandstand_shows, g_coverage.bandstand, 700);
    draw_entertainer(2, "pavilion", BUILDING_PAVILLION, g_city.entertainment.pavilion_shows, g_coverage.pavilion, 1200);
    draw_entertainer(3, "senet_house", BUILDING_SENET_HOUSE, g_city.entertainment.senet_house_plays, g_coverage.senet_house, 0);
    draw_entertainer(9, "zoo", BUILDING_ZOO, 0, 0, 0);

    ui["advice"] = ui::str(58, 7 + get_entertainment_advice());

    ui.end_widget();
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
