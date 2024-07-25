#include "advisor_religion.h"

#include "city/constants.h"
#include "building/building_menu.h"
#include "city/buildings.h"
#include "game/time.h"
#include "scenario/scenario.h"
#include "window/popup_dialog.h"

#include "building/count.h"
#include "city/festival.h"
#include "city/gods.h"
#include "city/city.h"
#include "game/settings.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "game/game.h"

#include "window/advisors.h"
#include "window/hold_festival.h"

ui::advisor_religion_window g_advisor_religion_window;

ANK_REGISTER_CONFIG_ITERATOR(config_load_advisor_religion);
void config_load_advisor_religion() {
    g_config_arch.r_section("advisor_religion_window", [] (archive arch) {
        g_advisor_religion_window.load(arch);
    });
}

static void button_hold_festival(int param1, int param2);

static generic_button hold_festival_button[] = {
  {102, 280 + 68, 300, 20, button_hold_festival, button_none, 0, 0},
};

static int get_religion_advice() {
    int least_happy = city_god_least_happy();
    const house_demands &demands = g_city.houses;
    if (least_happy >= 0 && city_god_wrath_bolts(least_happy) > 4) {
        return 6 + least_happy;
    } else if (demands.religion == 1) {
        return demands.requiring.religion ? 1 : 0;
    } else if (demands.religion == 2) {
        return 2;
    } else if (demands.religion == 3) {
        return 3;
    } else if (!demands.requiring.religion) {
        return 4;
    } else if (least_happy >= 0) {
        return 6 + least_happy;
    } else {
        return 5;
    }
}
static int get_festival_advice(void) {
    int months_since_festival = city_festival_months_since_last();
    if (months_since_festival <= 1)
        return 0;
    else if (months_since_festival <= 6)
        return 1;
    else if (months_since_festival <= 12)
        return 2;
    else if (months_since_festival <= 18)
        return 3;
    else if (months_since_festival <= 24)
        return 4;
    else if (months_since_festival <= 30)
        return 5;
    else {
        return 6;
    }
}

static void draw_festival_info(int y_offset) {
    auto &ui = g_advisor_religion_window;
    painter ctx = game.painter();

    ui["fest_months_last"].text_var("%d %s %s", city_festival_months_since_last(), ui::str(8, 5), ui::str(58, 15));

    if (city_festival_is_planned()) {
        int size = city_festival_selected_size();
        int months_left = city_festival_months_till_next();
        int planned_month = gametime().month + months_left;
        int width = lang_text_draw(58, 34, 102, 284 + y_offset, FONT_NORMAL_WHITE_ON_DARK);
        lang_text_draw(160, planned_month, 102 + width, 284 + y_offset, FONT_NORMAL_WHITE_ON_DARK);
        switch (size) {
        case FESTIVAL_SMALL:
            size = 10;
            break;
        case FESTIVAL_LARGE:
            size = 20;
            break;
        case FESTIVAL_GRAND:
            size = 31;
            break;
        }
        lang_text_draw_multiline(295, size + months_left - 1, vec2i{56, 305 + y_offset}, 400, FONT_NORMAL_WHITE_ON_DARK);
    } else {
        lang_text_draw_centered(58, 16, 102, 284 + y_offset, 300, FONT_NORMAL_WHITE_ON_DARK);
        lang_text_draw_multiline(58, 18 + get_festival_advice(), vec2i{56, 305 + y_offset}, 400, FONT_NORMAL_WHITE_ON_DARK);
    }
}

static void draw_god_row(e_god god, int y_offset, e_building_type temple, e_building_type complex, e_building_type shrine) {
    auto &ui = g_advisor_religion_window;
    painter ctx = game.painter();

    e_god_status is_known = city_gods_is_known(god);
    e_font font = (is_known == GOD_STATUS_UNKNOWN) ? FONT_NORMAL_WHITE_ON_DARK : FONT_NORMAL_YELLOW;

    auto _t = [god] (pcstr w) { return bstring32().printf("god_%d_%s", god, w); };
    ui[_t("name")].text(font, ui::str(157, god));
    ui[_t("known")].text(font, ui::str(187, is_known));

    ui[_t("desc")].text(ui::str(158, god));

    ui[_t("complex")].text(font, "-");
    ui[_t("temple")].text(font, "-");
    ui[_t("shrine")].text(font, "-");
    ui[_t("fest")].text(font, "-");
    ui[_t("mood")].text(font, "-");

    if (is_known == GOD_STATUS_UNKNOWN) {
        return;
    } 

    bstring32 bcount = "-";
    if (scenario_building_allowed(complex)) {
        bcount.printf("%d", building_count_active(complex));
    }

    ui[_t("complex")].text(bcount.c_str());
    ui[_t("temple")].text_var("%d", building_count_active(temple));
    ui[_t("shrine")].text_var("%d", building_count_active(shrine));
    ui[_t("fest")].text_var("%d", city_god_months_since_festival(god));
    ui[_t("mood")].text(ui::str(59, 20 + city_god_happiness(god) / 10));

    auto &bolt = ui[_t("bolt")];
    for (int i = 0; i < city_god_wrath_bolts(god) / 20; i++) {
        ui.image(bolt.image(), bolt.pos + vec2i(i * 10, 0));
    }

    auto &angel = ui[_t("angel")];
    for (int i = 0; i < city_god_happy_angels(god) / 20; i++) {
        ui.image(angel.image(), angel.pos + vec2i(i * 10, 0));
    }
}

int ui::advisor_religion_window::draw_background() {
    auto &ui = g_advisor_religion_window;

    painter ctx = game.painter();
    if (!g_settings.gods_enabled) {
        ui["nogods_text"].enabled = true;
        return 27;
    }

    ui["nogods_text"].enabled = false;
    ui["advice_text"].text(ui::str(59, 9 + get_religion_advice()));

    return 27;
}

void ui::advisor_religion_window::draw_foreground() {
    auto &ui = g_advisor_religion_window;

    ui.draw();

    if (!g_settings.gods_enabled) {
        return;
    }
    // todo: god description when clicking on god name
    // god rows
    draw_god_row(GOD_OSIRIS, 66, BUILDING_TEMPLE_OSIRIS, BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_SHRINE_OSIRIS);
    draw_god_row(GOD_RA, 106, BUILDING_TEMPLE_RA, BUILDING_TEMPLE_COMPLEX_RA, BUILDING_SHRINE_RA);
    draw_god_row(GOD_PTAH, 146, BUILDING_TEMPLE_PTAH, BUILDING_TEMPLE_COMPLEX_PTAH, BUILDING_SHRINE_PTAH);
    draw_god_row(GOD_SETH, 186, BUILDING_TEMPLE_SETH, BUILDING_TEMPLE_COMPLEX_SETH, BUILDING_SHRINE_SETH);
    draw_god_row(GOD_BAST, 226, BUILDING_TEMPLE_BAST, BUILDING_TEMPLE_COMPLEX_BAST, BUILDING_SHRINE_BAST);

    city_gods_calculate_least_happy();

    draw_festival_info(68);

    if (!city_festival_is_planned()) {
        button_border_draw(102, 280 + 68, 300, 20, g_advisor_religion_window.focus_button_id == 1);
    }
}

static void confirm_nothing(bool accepted) {
}

static void button_hold_festival(int param1, int param2) {
    int has_square = building_count_total(BUILDING_FESTIVAL_SQUARE);
    if (!has_square) {
        return window_ok_dialog_show("#popup_dialog_no_festival_square");
    }

    if (!city_festival_is_planned()) {
        window_hold_festival_show();
    }
}

int ui::advisor_religion_window::handle_mouse(const mouse* m) {
    return generic_buttons_handle_mouse(m, {0, 0}, hold_festival_button, 1, &g_advisor_religion_window.focus_button_id);
}

int  ui::advisor_religion_window::get_tooltip_text() {
    auto &ui = g_advisor_religion_window;
    if (ui.focus_button_id) {
        return 112;
    } else {
        return 0;
    }
}

advisor_window* ui::advisor_religion_window::instance() {
    return &g_advisor_religion_window;
}
