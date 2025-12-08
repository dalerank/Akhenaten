#include "advisor_financial.h"

#include "city/city.h"
#include "core/calc.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/arrow_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "game/game.h"

#include "js/js_game.h"

ui::advisor_financial_window_t ANK_VARIABLE(advisor_financial_window)

void ui::advisor_financial_window_t::draw_row(pcstr text, int &y, int value_last_year, int value_this_year) {
    auto ftext = ui::format(&g_city, text);

    ui.label(ftext, vec2i{ row_text_x, y }, FONT_NORMAL_BLACK_ON_LIGHT);
    ui.label(bstring32(value_last_year), vec2i{ row_last_year_x, y }, FONT_NORMAL_BLACK_ON_LIGHT);
    ui.label(bstring32(value_this_year), vec2i{ row_this_year_x, y }, FONT_NORMAL_BLACK_ON_LIGHT);
    y += 15;
}

void ui::advisor_financial_window_t::archive_load(archive arch) {
    autoconfig_window::archive_load(arch);

    row_last_year_x = arch.r_int("row_last_year_x");
    row_this_year_x = arch.r_int("row_this_year_x");
    line_start_x = arch.r_int("line_start_x");
    line_size_x = arch.r_int("line_size_x");
}

int ui::advisor_financial_window_t::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

    const int treasury = g_city.finance.treasury;

    pcstr prefix = (treasury < 0) ? ui::str(60, 3) : ui::str(60, 2);
    e_font font = (treasury < 0) ? FONT_NORMAL_YELLOW : FONT_NORMAL_WHITE_ON_DARK;
    ui["treasury"].text_var("%s %d", prefix, std::abs(treasury));
    ui["treasury"].font(font);

    ui["dec_tax"].onclick([] { events::emit(event_finance_change_tax{ -1 }); });
    ui["inc_tax"].onclick([] { events::emit(event_finance_change_tax{ +1 }); });

    return 0;
}

void ui::advisor_financial_window_t::ui_draw_foreground(UiFlags flags) {
    ui.begin_widget(pos);
    ui.draw();

    const finance_overview& last_year = g_city.finance.last_year;
    const finance_overview& this_year = g_city.finance.this_year;

    // tax percentage and estimated income
    struct row {
        pcstr text;
        int last_year;
        int this_year;
        bool line = false;
        vec2i pos{0, 0};
    };

    int line_y = ui["incomes_base"].pos.y;
    auto draw_rows = [this, &line_y] (const auto &rows) {
        for (const auto r : rows) {
            if (r.line) {
                ui.line(true, vec2i{ r.pos.x, line_y }, line_size_x);
                line_y += 5;
            } else {
                draw_row(r.text, line_y, r.last_year, r.this_year);
            }
        }
    };

    ///////// INCOMES
    svector<row, 32> rows_incomes = {
        {ui::str(60, 8) , last_year.income.taxes, this_year.income.taxes},
        {ui::str(60, 9) ,  last_year.income.exports, this_year.income.exports},
        {ui::str(60, 20) , last_year.income.donated, this_year.income.donated},
        {ui::str(60, 24) , (int)last_year.income.gold_delivered, (int)this_year.income.gold_delivered},
        {"", 0, 0, true, vec2i{line_start_x, 0} }, // sum lines
        {ui::str(60, 10) , (int)last_year.income.total, (int)this_year.income.total }
    };

    draw_rows(rows_incomes);

    bstring128 interest;
    interest.printf("%s 10%%", ui::str(60, 14));
    int last_year_others = last_year.expenses.festivals + last_year.expenses.kingdome + last_year.expenses.disasters;
    int this_year_others = this_year.expenses.festivals + this_year.expenses.kingdome + this_year.expenses.disasters;
    svector<row, 32> rows_expenses = {
        {rows.imports.c_str(), last_year.expenses.imports, this_year.expenses.imports},
        {ui::str(60, 12), last_year.expenses.wages, this_year.expenses.wages},
        {ui::str(60, 13), last_year.expenses.construction, this_year.expenses.construction},
        {interest, last_year.expenses.interest, last_year.expenses.interest},
        {ui::str(60, 15), last_year.expenses.mayour_salary, this_year.expenses.mayour_salary},
        {ui::str(60, 16), last_year.expenses.stolen, this_year.expenses.stolen},
        {ui::str(60, 21), last_year.expenses.tribute, this_year.expenses.tribute},
        {ui::str(60, 22), last_year_others, this_year_others},
        {"", 0, 0, true, vec2i{line_start_x, 0} }, // sum lines
        {ui::str(60, 17), last_year.expenses.total, this_year.expenses.total},
        {ui::str(60, 18), last_year.net_in_out, this_year.net_in_out},
        {ui::str(60, 19), last_year.balance, this_year.balance}
    };

    line_y = ui["expenses_base"].pos.y;
    draw_rows(rows_expenses);    
    ui.end_widget();
}

int ui::advisor_financial_window_t::get_tooltip_text() {
    return 0;
}

advisor_window* ui::advisor_financial_window_t::instance() {
    return &advisor_financial_window;
}
