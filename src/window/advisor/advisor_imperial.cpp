#include "advisor_imperial.h"

#include "city/city.h"
#include "game/resource.h"
#include "city/military.h"
#include "city/city_resource.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "scenario/request.h"
#include "scenario/distant_battle.h"
#include "window/popup_dialog.h"
#include "game/game.h"
#include "js/js_game.h"
#include "graphics/elements/ui_js.h"

ui::advisor_imperial_window g_advisor_imperial_window;

struct advisor_imperial_window_draw {
    vec2i pos;
};
ANK_REGISTER_STRUCT_WRITER(advisor_imperial_window_draw, pos)

void ui::advisor_imperial_window::ui_draw_foreground(UiFlags flags) {
    ui.begin_widget(pos);
    ui.draw();
    ui.event(advisor_imperial_window_draw{ pos });
    ui.end_widget();
}

advisor_window* ui::advisor_imperial_window::instance() {
    return &g_advisor_imperial_window;
}
