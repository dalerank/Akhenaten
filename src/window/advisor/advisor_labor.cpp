#include "advisor_labor.h"

#include "city/finance.h"
#include "city/city.h"
#include "core/calc.h"
#include "graphics/elements/ui.h"
#include "graphics/view/view.h"
#include "graphics/window.h"
#include "window/labor_priority.h"
#include "game/game.h"

ui::advisor_labors_window g_advisor_labor_window;

static void arrow_button_wages(int is_down) {
    g_city.labor.change_wages(is_down ? -1 : 1);
    city_finance_estimate_wages();
    city_finance_calculate_totals();
}

int ui::advisor_labors_window::draw_background(UiFlags flags) {
    bstring256 employed_text;
    employed_text.printf("%u %s %u %s %u%%)", g_city.labor.workers_employed, ui::str(50, 12), 
                                              g_city.labor.workers_unemployed, ui::str(50, 13),
                                              g_city.labor.unemployment_percentage);
    ui["employed"] = employed_text;
    ui["wages_value"].text_var("%u %s %s %u)", g_city.labor.wages, ui::str(50, 15), ui::str(50, 18), g_city.labor.wages_kingdome);
    ui["wages_estimated"].text_var("%s %u", ui::str(50, 19), city_finance_estimated_wages());

    ui["dec_wages"].onclick([] {
        arrow_button_wages(true);
    });

    ui["inc_wages"].onclick([] {
        arrow_button_wages(false);
    });
    return 0;
}

void ui::advisor_labors_window::ui_draw_foreground(UiFlags flags) {
    ui.begin_widget(pos);
    ui.draw();

    for (int i = 0; i < 9; i++) {
        int y_offset = 82 + 25 * i;
        ui.button("", vec2i(40, 77 + 25 * i), vec2i{560, 20})
            .onclick([category = i] {
                window_labor_priority_show(category);
            });

        const labor_category_data* cat = city_labor_category(i);
        if (cat->priority) {
            ui.image(image_desc{ PACK_GENERAL, 94 }, vec2i{ 70, y_offset - 2 });
            ui.label(bstring32(cat->priority), vec2i{ 90, y_offset }, FONT_NORMAL_WHITE_ON_DARK);
        }
        ui.label(ui::str(50, i + 1), vec2i{ 170, y_offset }, FONT_NORMAL_WHITE_ON_DARK);
        ui.label(bstring32(cat->workers_needed), vec2i{ 410, y_offset }, FONT_NORMAL_WHITE_ON_DARK);

        e_font font = cat->workers_needed != cat->workers_allocated ? FONT_NORMAL_WHITE_ON_DARK : FONT_NORMAL_YELLOW;
        ui.label(bstring32(cat->workers_allocated), vec2i{ 510, y_offset }, font);
    }
    ui.end_widget();
}

advisor_window* ui::advisor_labors_window::instance() {
    return &g_advisor_labor_window;
}
