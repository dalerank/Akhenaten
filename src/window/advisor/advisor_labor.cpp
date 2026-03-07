#include "advisor_labor.h"

#include "graphics/elements/ui.h"
#include "graphics/elements/ui_js.h"
#include "js/js_game.h"

ui::advisor_labors_window g_advisor_labor_window;

advisor_window* ui::advisor_labors_window::instance() {
    return &g_advisor_labor_window;
}
