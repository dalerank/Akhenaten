#include "advisor_entertainment.h"

#include "building/building_menu.h"
#include "scenario/scenario.h"
#include "city/coverage.h"
#include "city/city.h"
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

ui::advisor_entertainment_window g_advisor_entertainment_window;

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
        ui[_s("active")].text(font, bstring32(g_city.buildings.count_active(venue)));
        ui[_s("shows")].text(font, bstring32(shows));
        ui[_s("care")].text(font, bstring32().printf("%u %s", entertain_coeff * g_city.buildings.count_active(venue), ui::str(58, 5)));
        textid textcvg{ 57, 18 };
        if (coverage == 0) { textcvg = { 57, 7 };
        } else if (coverage < 100) { textcvg = { 57, 8 + coverage / 10 }; }

        ui[_s("cvg")].text(font, ui::str(textcvg));
    }
}

void ui::advisor_entertainment_window::ui_draw_foreground(UiFlags flags) {
    ui.begin_widget(pos);
    ui.draw();

    painter ctx = game.painter();
    g_city.religion.calculate_gods_mood_targets();
    g_city.avg_coverage.update();

    draw_entertainer(0, "booth", BUILDING_BOOTH, g_city.entertainment.booth_shows, g_city.coverage.booth, 400);
    draw_entertainer(1, "bandstand", BUILDING_BANDSTAND, g_city.entertainment.bandstand_shows, g_city.coverage.bandstand, 700);
    draw_entertainer(2, "pavilion", BUILDING_PAVILLION, g_city.entertainment.pavilion_shows, g_city.coverage.pavilion, 1200);
    draw_entertainer(3, "senet_house", BUILDING_SENET_HOUSE, g_city.entertainment.senet_house_plays, g_city.coverage.senet_house, 0);
    draw_entertainer(9, "zoo", BUILDING_ZOO, 0, 0, 0);

    ui["advice"] = ui::str(58, 7 + get_entertainment_advice());

    ui.end_widget();
}

int ui::advisor_entertainment_window::handle_mouse(const mouse* m) {
    return 0;
}

int ui::advisor_entertainment_window::get_tooltip_text() {
    //if (focus_button_id) {
    //    return 112;
    //}else {
    //    return 0;
    //}

    return 0;
}

advisor_window* ui::advisor_entertainment_window::instance() {
    return &g_advisor_entertainment_window;
}
