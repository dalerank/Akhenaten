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

static void button_go_to_legion(int legion_id, int param2);
static void button_return_to_fort(int legion_id, int param2);
static void button_empire_service(int legion_id, int param2);

struct advisor_military_window_draw { vec2i pos; };
ANK_REGISTER_STRUCT_WRITER(advisor_military_window_draw, pos);

void ui::advisor_military_window::init() {
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

    int num_legions = formation_get_num_forts();
    if (num_legions > 0) {
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
    ui.draw(advisor_military_window_draw{ pos });
    ui.end_widget();
}

int ui::advisor_military_window::handle_mouse(const mouse* m) {
    return 0;
}

static void button_go_to_legion(int legion_id, int param2) {
    const formation* m = formation_get(g_formations.get_battalion_id_from_index(legion_id));
    camera_go_to_mappoint(m->home);
    window_city_show();
}

static void button_return_to_fort(int legion_id, int param2) {
    formation* m = formation_get(g_formations.get_battalion_id_from_index(legion_id));
    if (!m->in_distant_battle) {
        formation_batalion_return_home(m);
    }
}

static void button_empire_service(int legion_id, int param2) {
    int formation_id = g_formations.get_battalion_id_from_index(legion_id);
    formation_toggle_empire_service(formation_id);
    formation_calculate_figures();
}

advisor_window* ui::advisor_military_window::instance() {
    return &g_advisor_military_window;
}
