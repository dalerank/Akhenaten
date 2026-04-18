#include "advisor_chief.h"

#include "city/city_floods.h"
#include "scenario/request.h"

#include "city/city.h"
#include "city/military.h"
#include "scenario/distant_battle.h"
#include "city/city_population.h"
#include "core/calc.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/view/view.h"
#include "graphics/text.h"
#include "scenario/scenario_invasion.h"
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

    // military
    {
        std::pair<int, int> military_status;
        if (g_city.figures.kingdome_soldiers) { military_status = {170, FONT_NORMAL_YELLOW}; }
        else if (g_city.figures.enemies) { military_status = {170, FONT_NORMAL_YELLOW}; }
        else if (scenario_invasion_exists_upcoming()) { military_status = {170, FONT_NORMAL_YELLOW}; }
        else if (g_distant_battle.kingdome_army_is_traveling()) { military_status = {170, FONT_NORMAL_BLACK_ON_DARK}; }
        else if (g_distant_battle.battle.months_until_battle > 0) { military_status = {170, FONT_NORMAL_YELLOW}; }
        else if (g_city.figures.soldiers > 0) { military_status = {177, FONT_NORMAL_BLACK_ON_DARK}; }
        else { military_status = {171, FONT_NORMAL_BLACK_ON_DARK}; }

        ui["military_info"].text((pcstr)lang_get_string(61, military_status.first));
        ui["military_info"].font(military_status.second);
    }

    // kingdom
    {
        std::pair<int, int> kingdom_status;
        int requests = scenario_requests_active_count();
        if (requests == 0) { kingdom_status = {187, FONT_NORMAL_BLACK_ON_DARK}; }
        else if (requests == 1) { kingdom_status = {186, FONT_NORMAL_WHITE_ON_DARK}; }
        else if (requests == 2) { kingdom_status = {185, FONT_NORMAL_YELLOW}; }
        else { kingdom_status = {184, FONT_NORMAL_YELLOW}; }

        ui["kingdom_info"].text((pcstr)lang_get_string(61, kingdom_status.first));
        ui["kingdom_info"].font(kingdom_status.second);
    }

    // nilometr
    {
        std::pair<int, int> nilometr_status;
        int flood_quality = g_floods.expected_quality();
        if (flood_quality == 100) { nilometr_status = {197, FONT_NORMAL_BLACK_ON_DARK}; }
        else if (flood_quality > 75) { nilometr_status = {196, FONT_NORMAL_BLACK_ON_DARK}; }
        else if (flood_quality > 50) { nilometr_status = {195, FONT_NORMAL_BLACK_ON_DARK}; }
        else if (flood_quality > 25) { nilometr_status = {194, FONT_NORMAL_BLACK_ON_DARK}; }
        else if (flood_quality > 0) { nilometr_status = {193, FONT_NORMAL_YELLOW}; }
        else { nilometr_status = {192 + flood_quality, FONT_NORMAL_YELLOW}; }

        ui["nilometr_info"].text((pcstr)lang_get_string(61, nilometr_status.first));
        ui["nilometr_info"].font(nilometr_status.second);

        if (flood_quality > 0) {
            int flood_month = g_floods.expected_month();
            ui["nilometr_info2"].text((pcstr)lang_get_string(61, 204 + flood_month));
            ui["nilometr_info2"].font(FONT_NORMAL_BLACK_ON_DARK);
        } else {
            ui["nilometr_info2"].text("");
        }
    }

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
