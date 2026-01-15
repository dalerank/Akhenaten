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
#include "graphics/elements/ui_js.h"
#include "js/js_events.h"

ui::advisor_financial_window_t advisor_financial_window;

struct advisor_financial_window_draw { vec2i pos; };
ANK_REGISTER_STRUCT_WRITER(advisor_financial_window_draw, pos);

void ui::advisor_financial_window_t::archive_load(archive arch) {
    autoconfig_window::archive_load(arch);
}

void ui::advisor_financial_window_t::ui_draw_foreground(UiFlags flags) {
    ui.begin_widget(pos);
    ui.event(advisor_financial_window_draw{ pos });
    ui.draw();
    ui.end_widget();
}

advisor_window* ui::advisor_financial_window_t::instance() {
    return &advisor_financial_window;
}
