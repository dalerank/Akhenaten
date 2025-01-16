#include "mission_next.h"

#include "game/mission.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/image_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/view/view.h"
#include "graphics/image_groups.h"
#include "graphics/window.h"
#include "io/gamestate/boilerplate.h"
#include "scenario/scenario.h"
#include "window/main_menu.h"
#include "window/window_mission_briefing.h"
#include "game/game.h"
#include "city/city.h"
#include "dev/debug.h"

#include <utility>

ui::mission_choice_window g_mission_next;

declare_console_command_p(update_mission_next, ui_update_mission_next);
void ui_update_mission_next(std::istream &is, std::ostream &) {
    std::string args; is >> args;
    int scenario_id = atoi(args.empty() ? (pcstr)"0" : args.c_str());

    mission_id_t missionid(scenario_id);
    mission_choice_t choice = load_mission_choice(missionid);
    g_mission_next.choice = choice;
    g_mission_next.init();
}

void ui::mission_choice_window::init() {
    ui["background"].image(choice.background);
    ui["image1"].image(choice.image1);
    ui["image1"].pos = choice.image1_pos;
    ui["image2"].image(choice.image2);
    ui["image2"].pos = choice.image2_pos;
    ui["title"] = choice.title;

    for (auto &point: choice.points) {
        bstring64 pid;
        size_t index = std::distance(&choice.points[0], &point);
        pid.printf("point%d", index);
        auto &elm = ui[pid];
        elm.pos = point.pos;
        elm.tooltip(point.tooltip);
        elm.image(point.image);

        elm.onclick([this, name = point.name, id = point.id] {
            window_mission_briefing_show(id);
        });
    }
}

void window_mission_next_selection_show(int scenario_id) {
    const mission_step_t* mission = get_scenario_step_data(scenario_id);
    if (mission->campaign_id <= 0) {
        window_main_menu_show(true);
        return;
    }

    mission_id_t missionid(scenario_id);
    mission_choice_t choice = load_mission_choice(missionid);
    if (choice.points.empty()) {
        GamestateIO::load_mission(scenario_id, true);
        return;
    }

    window_type window = {
        WINDOW_MISSION_SELECTION,
        [] (int) { g_mission_next.draw_foreground(0); },
        [] (int flags) { 
            g_mission_next.format_all<city_t>(nullptr);
            g_mission_next.ui_draw_foreground(flags); 
        },
        [] (const mouse *m, const hotkeys *h) { g_mission_next.ui_handle_mouse(m); }
    };

    g_mission_next.choice = choice;
    g_mission_next.init();
    window_show(&window);
}
