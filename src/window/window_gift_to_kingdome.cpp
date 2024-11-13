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

static void button_set_gift(int gift_id, int param2);
static void button_send_gift(int param1, int param2);

static void window_gift_to_kingdome_init(void) {
    g_city.kingdome.init_selected_gift();
}

static void window_gift_to_kingdome_draw_background(int) {
    ui::begin_widget(screen_dialog_offset());
    ui::panel({96, 144}, {30, 15}, UiFlags_PanelOuter);
    ui::panel({112, 208}, {28, 5}, UiFlags_PanelInner);

    ui::icon(vec2i{112, 160}, RESOURCE_DEBEN);

    ui::label(ui::str(52, 69), {144, 160}, FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_AlignCentered, 462);
    ui::label(bstring128().printf("%s %d %s", ui::str(52, 50), g_city.kingdome.months_since_gift, ui::str(8, 4)),
                                  {144, 304}, FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_AlignCentered, 46);

    if (!g_city.kingdome.can_send_gift(GIFT_MODEST)) {
        ui::label(ui::str(52, 70), vec2i{160, 224}, FONT_NORMAL_WHITE_ON_DARK, UiFlags_LabelMultiline, 352);  
    } else {
        ui::button(ui::str(52, 66 + g_city.kingdome.selected_gift_size), {118, 336}, {260, 20})
            .onclick([] (int, int) {
            button_send_gift(2, 0);
        });
    }

    if (g_city.kingdome.can_send_gift(GIFT_MODEST)) {
        const auto* gift = g_city.kingdome.get_gift(GIFT_MODEST);
        ui::label(ui::str(52, 63), {128, 218}, FONT_NORMAL_WHITE_ON_DARK);
        ui::link(bstring128().printf("%s (%d db)", ui::str(52, 51 + gift->id), gift->cost), {224, 218}, {300, 20})
            .onclick([] (int, int) {
                button_send_gift(0, 0);
            });
    }

    if (g_city.kingdome.can_send_gift(GIFT_GENEROUS)) {
        const auto* gift = g_city.kingdome.get_gift(GIFT_GENEROUS);
        ui::label(ui::str(52, 64), {128, 238}, FONT_NORMAL_WHITE_ON_DARK);
        ui::link(bstring128().printf("%s (%d db)", ui::str(52, 55 + gift->id), gift->cost), {224, 238}, {300, 20})
            .onclick([] (int, int) {
                button_send_gift(2, 0);
            });
    }

    if (g_city.kingdome.can_send_gift(GIFT_LAVISH)) {
        const auto* gift = g_city.kingdome.get_gift(GIFT_LAVISH);
        ui::label(ui::str(52, 65), {128, 258}, FONT_NORMAL_WHITE_ON_DARK);
        ui::link(bstring128().printf("%s (%d db)", ui::str(52, 59 + gift->id), gift->cost), {224, 258}, {300, 20})
            .onclick([] (int, int) {
                button_send_gift(3, 0);
            });
    }

    ui::button(ui::str(13, 4), {400, 336}, {160, 20})
        .onclick([] (int, int) {
            window_advisors_show();
        });
    ui::end_widget();
}

static void window_gift_to_kingdome_handle_input(const mouse* m, const hotkeys* h) {
    bool button_id = ui::handle_mouse(m);

    if (input_go_back_requested(m, h)) {
        window_advisors_show();
    }
}

static void button_set_gift(int gift_id, int param2) {
    g_city.kingdome.set_gift_size(gift_id - 1);
}

static void button_send_gift(int param1, int param2) {
    if (g_city.kingdome.can_send_gift(GIFT_MODEST)) {
        g_city.kingdome.send_gift();
        window_advisors_show();
    }
}

void window_gift_to_kingdome_show(void) {
    static window_type window = {
        WINDOW_GIFT_TO_EMPEROR,
        window_gift_to_kingdome_draw_background,
        [] (int) {},
        window_gift_to_kingdome_handle_input
    };
    window_gift_to_kingdome_init();
    window_show(&window);
}
