#include "window_mission_briefing.h"

#include "game/mission.h"
#include "game/tutorial.h"
#include "graphics/graphics.h"
#include "graphics/elements/image_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/rich_text.h"
#include "graphics/image_groups.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "io/gamefiles/lang.h"
#include "io/gamestate/boilerplate.h"
#include "scenario/criteria.h"
#include "scenario/scenario.h"
#include "sound/music.h"
#include "sound/sound.h"
#include "window/window_city.h"
#include "window/intermezzo.h"
#include "window/mission_next.h"
#include "game/settings.h"
#include "city/city.h"

ui::mission_briefing_window g_mission_briefing;

void ui::mission_briefing_window::init() {
    rich_text_reset(0);

    mission_has_choice = game_mission_has_choice(scenario_id);

    ui["back"].enabled = !is_review && mission_has_choice;
    ui["dec_difficulty"].enabled = !is_review;
    ui["inc_difficulty"].enabled = !is_review;

    // load map!
    if (!g_mission_briefing.campaign_mission_loaded) {
        g_mission_briefing.campaign_mission_loaded = 1;
    }

    ui["dec_difficulty"].onclick([] {
        g_settings.difficulty.decrease();
    });

    if (!g_mission_briefing.is_review) {
        ui["back"].onclick([sid = scenario_id] {
            g_sound.speech_stop();
            ui::mission_choice_window::show(sid);
        });
    }

    ui["inc_difficulty"].onclick([] {
        g_settings.difficulty.increase();
    });

    ui["start_mission"].onclick([this] {
        if (!is_review) {
            GamestateIO::load_mission(scenario_id, true);
        }

        g_sound.speech_stop();
        g_sound.music_update(/*force*/true);
        window_city_show();
        g_city.mission.start_message_shown = true;
    });

    int text_id = 200 + scenario_id; 
    const lang_message& msg = lang_get_message(text_id);

    ui["title"] = msg.title.text;
    ui["subtitle"] = msg.subtitle.text;
    ui["difficulty_label"] = ui::str(153, g_settings.difficulty() + 1);

    const pcstr widgets[] = { "goal_0", "goal_1", "goal_2", "goal_3", "goal_4", "goal_5" };
    auto goal_label = widgets;

    auto setup_goal = [&] (int group, int tid, bool enabled, int value) {
        ui[*goal_label].enabled = enabled;
        if (enabled) {
            ui[*goal_label++].text_var("%s: %u", ui::str(group, tid), value);
        }
    };

    setup_goal(62, 11, winning_population() > 0, winning_population());
    setup_goal(29, 20 + winning_houselevel(), winning_housing() > 0, winning_housing());
    setup_goal(62, 12, winning_culture() > 0, winning_culture());
    setup_goal(62, 13, winning_prosperity() > 0, winning_prosperity());
    setup_goal(62, 14, winning_monuments() > 0, winning_monuments());
    setup_goal(62, 15, winning_kingdom() > 0, winning_kingdom());

    xstring immediate_goal_text = tutorial_get_immediate_goal_text();
    ui["goal_immediate"].enabled = !!immediate_goal_text;
    ui["goal_immediate"] = immediate_goal_text;

    ui["description_text"] = msg.content.text;
}

int ui::mission_briefing_window::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);
    window_draw_underlying_window(UiFlags_None);
    return 0;
}

void window_mission_briefing_show_impl() {
    static window_type window = {
        WINDOW_MISSION_BRIEFING,
        [] (int flags) { g_mission_briefing.draw_background(flags); },
        [] (int flags) { g_mission_briefing.ui_draw_foreground(flags); },
        [] (const mouse *m, const hotkeys *h) { g_mission_briefing.ui_handle_mouse(m); }
    };
    
    g_mission_briefing.init();
    window_show(&window);
}

void ui::mission_briefing_window::mission_start(int scenario_id) {
    auto &data = g_mission_briefing;
    data.scenario_id = scenario_id;
    data.is_review = false;
    data.campaign_mission_loaded = false;
    window_intermezzo_show(scenario_id, INTERMEZZO_MISSION_BRIEFING, window_mission_briefing_show_impl);
}

void ui::mission_briefing_window::mission_review() {
    auto &data = g_mission_briefing;
    data.scenario_id = g_scenario.campaign_scenario_id();
    data.is_review = true;
    data.campaign_mission_loaded = true;
    window_intermezzo_show(data.scenario_id, INTERMEZZO_MISSION_BRIEFING, window_mission_briefing_show_impl);
}
