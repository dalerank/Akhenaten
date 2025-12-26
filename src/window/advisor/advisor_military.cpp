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

ui::advisor_military_window g_advisor_military_window;

static void button_go_to_legion(int legion_id, int param2);
static void button_return_to_fort(int legion_id, int param2);
static void button_empire_service(int legion_id, int param2);
static void on_scroll();

static scrollbar_t g_advisor_mil_scrollbar = {{592, 70}, 272, on_scroll};

static generic_button fort_buttons[] = {
  {384, 83, 30, 30, button_go_to_legion, button_none, 1, 0},
  {464, 83, 30, 30, button_return_to_fort, button_none, 1, 0},
  {544, 83, 30, 30, button_empire_service, button_none, 1, 0},
  {384, 127, 30, 30, button_go_to_legion, button_none, 2, 0},
  {464, 127, 30, 30, button_return_to_fort, button_none, 2, 0},
  {544, 127, 30, 30, button_empire_service, button_none, 2, 0},
  {384, 171, 30, 30, button_go_to_legion, button_none, 3, 0},
  {464, 171, 30, 30, button_return_to_fort, button_none, 3, 0},
  {544, 171, 30, 30, button_empire_service, button_none, 3, 0},
  {384, 215, 30, 30, button_go_to_legion, button_none, 4, 0},
  {464, 215, 30, 30, button_return_to_fort, button_none, 4, 0},
  {544, 215, 30, 30, button_empire_service, button_none, 4, 0},
  {384, 259, 30, 30, button_go_to_legion, button_none, 5, 0},
  {464, 259, 30, 30, button_return_to_fort, button_none, 5, 0},
  {544, 259, 30, 30, button_empire_service, button_none, 5, 0},
  {384, 303, 30, 30, button_go_to_legion, button_none, 6, 0},
  {464, 303, 30, 30, button_return_to_fort, button_none, 6, 0},
  {544, 303, 30, 30, button_empire_service, button_none, 6, 0},
};

static int focus_button_id;
static int num_legions;

void ui::advisor_military_window::init() {
    num_legions = formation_get_num_forts();
    g_advisor_mil_scrollbar.init(0, num_legions - 6);
}

int ui::advisor_military_window::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

    int enemy_text_id = 8;
    if (g_city.figures.enemies) { enemy_text_id = 10; }
    else if (g_city.figures.kingdome_soldiers) { enemy_text_id = 11; }
    else if (scenario_invasion_exists_upcoming()) { enemy_text_id = 9; }

    int distant_battle_text_id = 12;
    if (city_military_distant_battle_kingdome_army_is_traveling_back()) { distant_battle_text_id = 15; }
    else if (g_city.distant_battle.kingdome_army_is_traveling_forth()) { distant_battle_text_id = 14; }
    else if (g_city.distant_battle.months_until_distant_battle() > 0) { distant_battle_text_id = 13; }

    int bullet_x = 60;
    int text_x = 80;
    image_desc group_bullet{PACK_GENERAL, 158};

    vec2i pos = ui["forts_area"].pos;
    if (num_legions <= 0) {
        ui["enemy_text"].pos.y = pos.y + 10;
        ui["distant_text"].pos.y = pos.y + 30;
    } else {
        // has forts
        ui["enemy_text"].pos.y = pos.y + 20;
        ui["distant_text"].pos.y = pos.y + 40;

        ui["forts_text"].text_var("%s %u %s %s %u", ui::str(8, 46), g_city.military.total_soldiers, 
                                                    ui::str(51, 7), ui::str(8, 48), g_city.military.total_batalions);
    }

    ui["enemy_text"] = ui::str(51, enemy_text_id);
    ui["distant_text"] = ui::str(51, distant_battle_text_id);

    ui["no_legions"].enabled = (num_legions <= 0);

    return 0;
}

void ui::advisor_military_window::ui_draw_foreground(UiFlags flags) {
    ui.begin_widget(pos);
    ui.draw();

    if (num_legions > 0) {
        for (int i = 0; i < 6 && i < num_legions; i++) {
            const formation *form = formation_get(formation_for_legion(i + 1 + g_advisor_mil_scrollbar.scroll_position));
            ui.button("", vec2i{ 22, 77 + 44 * i }, vec2i{ 560, 40 }, fonts_vec{ FONT_NORMAL_BLACK_ON_DARK });
            ui.image({ PACK_GENERAL, 127, form->batalion_id }, vec2i{ 32, 82 + 44 * i });
            ui.label(ui::str(138, form->batalion_id), vec2i{ 84, 83 + 44 * i }, FONT_NORMAL_WHITE_ON_DARK);

            pcstr type_str = "";
            switch (form->figure_type) {
            case FIGURE_INFANTRY: type_str = ui::str(138, 33); break;
            case FIGURE_FCHARIOTEER: type_str = ui::str(138, 34); break;
            case FIGURE_ARCHER: type_str = ui::str(138, 35); break;
            }
            ui.label(bstring64().printf("%u %s", form->num_figures, type_str), vec2i{ 84, 100 + 44 * i }, FONT_NORMAL_BLACK_ON_DARK);
            ui.label(ui::str(138, 37 + form->morale / 5), vec2i{224, 91 + 44 * i}, FONT_NORMAL_BLACK_ON_DARK, UiFlags_AlignCentered, 150);

            image_desc image{ PACK_GENERAL, 222 };
            ui.button("", vec2i{ 384, 83 + 44 * i }, vec2i{ 30, 30 }, fonts_vec{ FONT_NORMAL_BLACK_ON_DARK });
            ui.image(image + 0, vec2i{ 387, 86 + 44 * i });

            ui.button("", vec2i{ 464, 83 + 44 * i }, vec2i{ 30, 30 });
            ui.image(image + (form->is_at_fort ? 2 : 1), vec2i{ 467, 86 + 44 * i });

            ui.button("", vec2i{ 544, 83 + 44 * i }, vec2i{ 30, 30 });
            ui.image(image + (form->empire_service ? 3 : 4), vec2i{ 547, 86 + 44 * i });
        }
    }
    ui.end_widget();

    scrollbar_draw(vec2i{0, 0}, &g_advisor_mil_scrollbar);
    //num_legions = formation_get_num_forts();
    //for (int i = 0; i < 6 && i < num_legions; i++) {
    //    button_border_draw(384, 83 + 44 * i, 30, 30, focus_button_id == 3 * i + 1);
    //    button_border_draw(464, 83 + 44 * i, 30, 30, focus_button_id == 3 * i + 2);
    //    button_border_draw(544, 83 + 44 * i, 30, 30, focus_button_id == 3 * i + 3);
    //}
}

int ui::advisor_military_window::handle_mouse(const mouse* m) {
    if (scrollbar_handle_mouse(vec2i{0, 0}, &g_advisor_mil_scrollbar, m)) {
        return 1;
    }

    return 0;
}

static void button_go_to_legion(int legion_id, int param2) {
    const formation* m = formation_get(formation_for_legion(legion_id + g_advisor_mil_scrollbar.scroll_position));
    camera_go_to_mappoint(m->home);
    window_city_show();
}

static void button_return_to_fort(int legion_id, int param2) {
    formation* m = formation_get(formation_for_legion(legion_id + g_advisor_mil_scrollbar.scroll_position));
    if (!m->in_distant_battle) {
        formation_batalion_return_home(m);
    }
}

static void button_empire_service(int legion_id, int param2) {
    int formation_id = formation_for_legion(legion_id + g_advisor_mil_scrollbar.scroll_position);
    formation_toggle_empire_service(formation_id);
    formation_calculate_figures();
}

static void on_scroll(void) {

}

advisor_window* ui::advisor_military_window::instance() {
    return &g_advisor_military_window;
}
