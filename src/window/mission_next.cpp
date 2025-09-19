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

declare_console_command_p(update_mission_next) {
    std::string args; is >> args;
    int scenario_id = atoi(args.empty() ? (pcstr)"0" : args.c_str());

    mission_id_t missionid(scenario_id);
    mission_choice_t choice = load_mission_choice(missionid);
    g_mission_next.choice = choice;
    g_mission_next.init();
}

void ui::mission_choice_window::init() {
    ui["background"].image(choice.choice_background);
    ui["image1"].image(choice.choice_image1);
    ui["image1"].pos = choice.choice_image1_pos;
    ui["image2"].image(choice.choice_image2);
    ui["image2"].pos = choice.choice_image2_pos;
    ui["title"] = choice.choice_title;

    for (auto &point: choice.choice) {
        bstring64 pid;
        size_t index = std::distance(&choice.choice[0], &point);
        pid.printf("point%d", index);
        auto &elm = ui[pid];
        elm.pos = point.pos;
        elm.tooltip(point.tooltip);
        elm.image(point.image);

        elm.onclick([id = point.id] {
            mission_briefing_window::mission_start(id);
        });
    }
}

void ui::mission_choice_window::show(int scenario_id) {
    const mission_step_t* mission = get_scenario_step_data(scenario_id);

    const bool mission_valid = mission && mission->campaign_id >= 0;
    if (!mission_valid) {
        main_menu_screen::show(/*restart_music*/true);
        return;
    }

    mission_id_t missionid(scenario_id);
    mission_choice_t choice = load_mission_choice(missionid);
    if (choice.choice.empty()) {
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
