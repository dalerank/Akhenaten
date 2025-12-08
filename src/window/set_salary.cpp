#include "set_salary.h"

#include "city/city_kingdome_relations.h"
#include "city/city_finance.h"
#include "city/ratings.h"
#include "city/victory.h"
#include "city/city.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/ui.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "window/advisors.h"
#include "io/gamefiles/lang.h"

set_salary_window g_set_salary_window;

void set_salary_window::close() {
    if (close_callback) {
        close_callback();
    }
    window_go_back();
}

void set_salary_window::init() {
    autoconfig_window::init();

    // Set up cancel button
    ui["btn_cancel"].onclick([this] {
        this->close();
    });

    ui["background_image"].enabled = show_background;

    // Set up salary rank buttons
    for (int rank = 0; rank < 11; rank++) {
        bstring32 btn_id("salary_rank_", rank);
        ui[btn_id].onclick([this, rank] {
            g_city.kingdome.set_salary_rank(rank);
            g_city.kingdome.update_explanation();
            this->close();
        });

        // Format: "Rank Name: Salary Amount Db"
        // bstring128 full_text;
        // pcstr rank_name = lang_get_string(52, rank + 4);
        // int salary = g_city.kingdome.salary_for_rank(rank);
        // pcstr currency = lang_get_string(6, 0); // "Db" or "Deben"
        // full_text.printf("%s: %d %s", rank_name, salary, currency);

        // ui[btn_id] = full_text;
        ui[btn_id].readonly = g_city.victory_state.has_won();
    }

    // Update explanation text
    if (!g_city.victory_state.has_won()) {
        if (g_city.kingdome.salary_rank <= g_city.kingdome.player_rank) {
            ui["explanation_text"] = textid{ 52, 76 };
        } else {
            ui["explanation_text"] = textid{ 52, 71 };
        }
    } else {
        ui["explanation_text"] = textid{ 52, 77 };
    }
}

void set_salary_window::ui_draw_foreground(UiFlags flags) {
    ui.begin_widget(pos);
    ui.draw(flags);
    ui.end_widget();
}

int set_salary_window::ui_handle_mouse(const mouse *m) {
    int result = autoconfig_window::ui_handle_mouse(m);

    const hotkeys *h = hotkey_state();
    if (input_go_back_requested(m, h)) {
        close();
    }

    return result;
}

void set_salary_window::show(close_callback_t cb, bool show_bg) {
    static window_type window = {
        WINDOW_SET_SALARY,
        window_draw_underlying_window,
        [] (int flags) { g_set_salary_window.ui_draw_foreground(flags); },
        [] (const mouse *m, const hotkeys *h) { g_set_salary_window.ui_handle_mouse(m); }
    };

    g_set_salary_window.show_background = show_bg;
    g_set_salary_window.close_callback = cb;
    g_set_salary_window.init();

    window_show(&window);
}