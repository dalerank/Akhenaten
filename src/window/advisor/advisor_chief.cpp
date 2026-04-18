#include "advisor_chief.h"

#include "city/city.h"
#include "city/city_population.h"
#include "core/calc.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/view/view.h"
#include "graphics/text.h"
#include "scenario/scenario.h"
#include "game/game.h"
#include "graphics/elements/ui_js.h"
#include "io/gamefiles/lang.h"
#include "js/js_struct.h"

ui::advisor_chief_window g_advisor_chief_window;

struct advisor_chief_window_fg { vec2i pos; };
ANK_REGISTER_STRUCT_WRITER(advisor_chief_window_fg, pos);

static void draw_title(int y, int text_id) {
    painter ctx = game.painter();
    ctx.img_generic(image_id_from_group(PACK_GENERAL, 158), { 26, y + 1 });
    lang_text_draw(61, text_id, 44, y, FONT_NORMAL_WHITE_ON_DARK);
}

int ui::advisor_chief_window::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);
    return 0;
}

void ui::advisor_chief_window::ui_draw_foreground(UiFlags flags) {
    ui.begin_widget(pos);
    ui.draw();
    ui.event(advisor_chief_window_fg{ pos }, get_section(), "ui_draw_foreground");

    int y_line = 306;
    int text_b = 20;

    //    // housing capacity
    //    imagedrawnamespace::image_draw_namespace::image_draw(image_id_from_group(GROUP_BULLET), 32, y_line + 1);
    //    text_draw(translation_for(TR_HEADER_HOUSING), 52, y_line, FONT_NORMAL_WHITE, 0);
    //
    //    if (!city_population_open_housing_capacity())
    //        width = text_draw(translation_for(TR_ADVISOR_HOUSING_NO_ROOM), X_OFFSET, y_line, FONT_NORMAL_GREEN, 0);
    //    else {
    //        width = text_draw(translation_for(TR_ADVISOR_HOUSING_ROOM), X_OFFSET, y_line, FONT_NORMAL_GREEN, 0);
    //        text_draw_number(city_population_open_housing_capacity(), '@', " ", X_OFFSET + width, y_line,
    //        FONT_NORMAL_GREEN);
    //    }
    //    y_line += 20;

    //    // education
    //    house_demands *demands = city_houses_demands();
    //    draw_title(y_line, 8);
    //    if (demands->education == 1)
    //        lang_text_draw(61, 39, X_OFFSET, y_line, FONT_NORMAL_RED);
    //    else if (demands->education == 2)
    //        lang_text_draw(61, 40, X_OFFSET, y_line, FONT_NORMAL_RED);
    //    else if (demands->education == 3)
    //        lang_text_draw(61, 41, X_OFFSET, y_line, FONT_NORMAL_RED);
    //    else
    //        lang_text_draw(61, 42, X_OFFSET, y_line, FONT_NORMAL_GREEN);
    //    y_line += 20;

    //    // entertainment
    //    draw_title(y_line, 10);
    //    if (demands->entertainment == 1)
    //        lang_text_draw(61, 43, X_OFFSET, y_line, FONT_NORMAL_RED);
    //    else if (demands->entertainment == 2)
    //        lang_text_draw(61, 44, X_OFFSET, y_line, FONT_NORMAL_RED);
    //    else
    //        lang_text_draw(61, 45, X_OFFSET, y_line, FONT_NORMAL_GREEN);
    //    y_line += 20;

    ui.end_widget();
}

advisor_window* ui::advisor_chief_window::instance() {
    return &g_advisor_chief_window;
}
