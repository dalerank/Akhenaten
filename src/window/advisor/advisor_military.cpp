#include "advisor_military.h"

#include "city/city.h"
#include "city/military.h"
#include "figure/formation_batalion.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/scrollbar.h"
#include "graphics/text.h"
#include "graphics/view/view.h"
#include "graphics/window.h"
#include "grid/grid.h"
#include "scenario/scenario_invasion.h"
#include "window/window_city.h"
#include "game/game.h"

#include "js/js_game.h"
#include "graphics/elements/ui_js.h"

ui::advisor_military_window g_advisor_military_window;

struct advisor_military_window_draw { vec2i pos; };
struct advisor_military_window_init { vec2i pos; };
ANK_REGISTER_STRUCT_WRITER(advisor_military_window_init, pos);
ANK_REGISTER_STRUCT_WRITER(advisor_military_window_draw, pos);

void ui::advisor_military_window::init() {
    ui.event(advisor_military_window_init{ pos });
}

void ui::advisor_military_window::ui_draw_foreground(UiFlags flags) {
    ui.begin_widget(pos);
    ui.draw();
    ui.event(advisor_military_window_draw{ pos });
    ui.end_widget();
}

int ui::advisor_military_window::handle_mouse(const mouse* m) {
    return 0;
}

advisor_window* ui::advisor_military_window::instance() {
    return &g_advisor_military_window;
}
