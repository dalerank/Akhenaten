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
#include "window/autoconfig_window.h"
#include "io/gamefiles/lang.h"

struct set_salary_window : public autoconfig_window_t<set_salary_window> {
    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void draw_foreground(UiFlags flags) override {}
    virtual int draw_background(UiFlags flags) override { return 0; }
    virtual void ui_draw_foreground(UiFlags flags) override;
    virtual int ui_handle_mouse(const mouse *m) override;
    virtual void init() override;

    static void show();
};

set_salary_window g_set_salary_window;

void set_salary_window::init() {
    autoconfig_window::init();

    // Set up cancel button
    ui["btn_cancel"].onclick([] {
        window_advisors_show();
    });

    // Set up salary rank buttons
    for (int rank = 0; rank < 11; rank++) {
        bstring32 btn_id("salary_rank_", rank);
        ui[btn_id].onclick([rank] {
            g_city.kingdome.set_salary_rank(rank);
            g_city.kingdome.update_explanation();
            window_advisors_show();
        });

        // Format: "Rank Name: Salary Amount Db"
        bstring128 full_text;
        pcstr rank_name = lang_get_string(52, rank + 4);
        int salary = g_city.kingdome.salary_for_rank(rank);
        pcstr currency = lang_get_string(6, 0); // "Db" or "Deben"
        full_text.printf("%s: %d %s", rank_name, salary, currency);

        ui[btn_id] = full_text;
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
        window_advisors_show();
    }

    return result;
}

void set_salary_window::show() {
    static window_type window = {
        WINDOW_SET_SALARY,
        window_draw_underlying_window,
        [] (int flags) { g_set_salary_window.ui_draw_foreground(flags); },
        [] (const mouse *m, const hotkeys *h) { g_set_salary_window.ui_handle_mouse(m); }
    };

    g_set_salary_window.init();
    window_show(&window);
}

void window_set_salary_show(void) {
    set_salary_window::show();
}
