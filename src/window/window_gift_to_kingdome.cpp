#include "window_gift_to_kingdome.h"

#include "city/city.h"
#include "game/resource.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/view/view.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "graphics/screen.h"
#include "input/input.h"
#include "window/advisors.h"
#include "game/game.h"
#include "js/js_game.h"

ui::gift_to_kingdome_window g_gift_to_kingdome_window;

void ui::gift_to_kingdome_window::init() {
    autoconfig_window::init();
    g_city.kingdome.update_gifts();

    if (selected_gift_size == GIFT_LAVISH && !g_city.kingdome.can_send_gift(GIFT_LAVISH)) {
        selected_gift_size = GIFT_GENEROUS;
    }

    if (selected_gift_size == GIFT_GENEROUS && !g_city.kingdome.can_send_gift(GIFT_GENEROUS)) {
        selected_gift_size = GIFT_MODEST;
    }

    ui["button_close"].onclick([] { window_go_back(); });

    const bool can_send_gift = g_city.kingdome.can_send_gift(GIFT_MODEST);
    const auto *mod_gift = g_city.kingdome.get_gift(GIFT_MODEST);
    ui["link_modest"].enabled = can_send_gift;
    ui["link_modest"] = bstring128().printf("%s (%d db)", ui::str(52, 51 + mod_gift->id), mod_gift->cost);
    ui["link_modest"].onclick([this] { select_link(GIFT_MODEST); });
    ui["lb_modest"].enabled = can_send_gift;

    ui["cant_send_gifts"].enabled = !can_send_gift;

    ui["send_gift"].readonly = !can_send_gift;
    ui["send_gift"].onclick([this] {
        if (g_city.kingdome.can_send_gift(selected_gift_size)) {
            events::emit(event_send_gift_to_kingdome{ selected_gift_size });
            window_advisors_show();
        }
    });

    const bool can_send_gen_gift = g_city.kingdome.can_send_gift(GIFT_GENEROUS);
    const auto *gen_gift = g_city.kingdome.get_gift(GIFT_GENEROUS);
    ui["link_generous"] = can_send_gen_gift
                            ? bstring128().printf("%s (%d db)", ui::str(52, 55 + gen_gift->id), gen_gift->cost)
                            : bstring128(ui::str(52, 48));
    ui["link_generous"].onclick([this] { select_link(GIFT_GENEROUS); });
    ui["link_generous"].enabled = can_send_gift;
    ui["link_generous"].readonly = !can_send_gen_gift;
    ui["lb_generous"].enabled = can_send_gift;

    const bool can_send_lavish_gift = g_city.kingdome.can_send_gift(GIFT_LAVISH);
    const auto *lavish_gift = g_city.kingdome.get_gift(GIFT_LAVISH);
    ui["link_lavish"] = can_send_lavish_gift 
                            ? bstring128().printf("%s (%d db)", ui::str(52, 59 + lavish_gift->id), lavish_gift->cost)
                            : bstring128(ui::str(52, 48));
    ui["link_lavish"].onclick([this] { select_link(GIFT_LAVISH); });
    ui["link_lavish"].enabled = can_send_gift;
    ui["link_lavish"].readonly = !can_send_lavish_gift;
    ui["lb_lavish"].enabled = can_send_gift;
}

void ui::gift_to_kingdome_window::select_link(int new_gift) {
    selected_gift_size = new_gift;
    constexpr pcstr links[] = { "link_modest", "link_generous", "link_lavish" };
    for (const auto n: links) {
        ui[n].select(false);
    }

    const pcstr selected = links[selected_gift_size];
    ui[selected].select(true);
}

bool ui::gift_to_kingdome_window::can_buy_gift(int size) {
    if (g_city.kingdome.get_gift_cost(size) <= g_city.kingdome.personal_savings) {
        selected_gift_size = size;
        return true;
    }

    return false;
}

int ui::gift_to_kingdome_window::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

    ui["send_gift"] = ui::str(52, 66 + selected_gift_size);
    ui.format_all(&g_city);

    return 0;
}

int ui::gift_to_kingdome_window::ui_handle_mouse(const mouse* m) {
    autoconfig_window::ui_handle_mouse(m);

    const hotkeys *h = hotkey_state();
    if (input_go_back_requested(m, h)) {

        window_go_back();
    }

    return 0;
}

void ui::gift_to_kingdome_window::show() {
    static window_type window = {
        WINDOW_GIFT_TO_EMPEROR,
        [] (int flags) { g_gift_to_kingdome_window.draw_background(flags); },
        [] (int flags) { g_gift_to_kingdome_window.ui_draw_foreground(flags); },
        [] (const mouse *m, const hotkeys *h) { g_gift_to_kingdome_window.ui_handle_mouse(m); },
    };
    g_gift_to_kingdome_window.init();
    window_show(&window);
}

void window_gift_to_kingdome_show() { ui::gift_to_kingdome_window::show(); }
ANK_FUNCTION(window_gift_to_kingdome_show)
