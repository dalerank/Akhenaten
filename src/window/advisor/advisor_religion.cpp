#include "advisor_religion.h"

#include "city/constants.h"
#include "city/buildings.h"
#include "scenario/scenario.h"
#include "window/popup_dialog.h"
#include "city/city.h"
#include "game/settings.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/screen.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "game/game.h"
#include "window/hold_festival.h"

ui::advisor_religion_window g_advisor_religion_window;

int ui::advisor_religion_window::get_advice() {
    e_god least_happy = g_city.religion.least_happy_god;
    const house_demands &demands = g_city.houses;
    if (least_happy >= 0 && g_city.religion.god_wrath_bolts(least_happy) > 4) {
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

void ui::advisor_religion_window::draw_god_row(e_god god, int y_offset, e_building_type temple, e_building_type complex, e_building_type shrine) {
    e_god_status is_known = g_city.religion.is_god_known(god);
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
        bcount.printf("%d", g_city.buildings.count_active(complex));
    }

    const int active_temples = g_city.buildings.count_active(temple);
    const int total_temples = g_city.buildings.count_total(temple);
    const int active_shrines = g_city.buildings.count_active(shrine);
    ui[_t("complex")].text(bcount.c_str());
    ui[_t("temple")].text_var("%d (%d)", active_temples, total_temples);
    ui[_t("shrine")].text_var("%d", active_shrines);
    ui[_t("fest")].text_var("%d", g_city.religion.months_since_festival(god));
    ui[_t("mood")].text(ui::str(59, 20 + g_city.religion.god_happiness(god) / 10));

    auto &bolt = ui[_t("bolt")];
    for (int i = 0; i < g_city.religion.god_wrath_bolts(god) / 20; i++) {
        ui.image(bolt.image(), bolt.pos + vec2i(i * 10, 0));
    }

    auto &angel = ui[_t("angel")];
    for (int i = 0; i < g_city.religion.god_happy_angels(god) / 20; i++) {
        ui.image(angel.image(), angel.pos + vec2i(i * 10, 0));
    }
}

int ui::advisor_religion_window::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

    g_city.religion.calculate_least_happy_god();
    if (!g_settings.gods_enabled) {
        ui["nogods_text"].enabled = true;
        return 27;
    }

    ui["nogods_text"].enabled = false;
    ui["advice_text"].text(ui::str(59, 9 + get_advice()));

    ui["fest_months_last"].text_var("%d %s %s", g_city.festival.months_since_festival, ui::str(8, 5), ui::str(58, 15));

    if (g_city.festival.is_planned()) {
        int size = g_city.festival.selected_size;
        int months_left = g_city.festival.months_till_next();
        int planned_month = (game.simtime.month + months_left) % simulation_time_t::months_in_year;
        int festival_text_iffs[] = { 0, 10, 20, 31 };

        ui["hold_festival_btn"].enabled = false;
        ui["planed_festival"].text_var("%s %s", ui::str(58, 34), ui::str(160, planned_month));
        ui["festival_advice"] = ui::str(295, festival_text_iffs[size] + months_left - 1);
    } else {
        ui["hold_festival_btn"].enabled = true;
        ui["hold_festival_btn"] = ui::str(58, 16);
        ui["hold_festival_btn"].onclick([] {
            int has_square = g_city.buildings.count_total(BUILDING_FESTIVAL_SQUARE);
            if (!has_square) {
                return popup_dialog::show_ok("#popup_dialog_no_festival_square");
            }

            if (!g_city.festival.is_planned()) {
                ui::hold_festival_window::show(true);
            }
        });
        ui["festival_advice"] = ui::str(58, 18 + g_city.festival.get_advice());
    }

    return 27;
}

void ui::advisor_religion_window::ui_draw_foreground(UiFlags flags) {
    ui.begin_widget(pos);
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

    ui.end_widget();
}

int  ui::advisor_religion_window::get_tooltip_text() {
    //auto &ui = g_advisor_religion_window;
    //if (ui.focus_button_id) {
    //    return 112;
    //} else {
    //    return 0;
    //}

    return 0;
}

advisor_window* ui::advisor_religion_window::instance() {
    return &g_advisor_religion_window;
}
