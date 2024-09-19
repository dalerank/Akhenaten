#include "mission_briefing.h"

#include "city/mission.h"
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
#include "js/js_game.h"

ui::mission_briefing_window g_mission_briefing;

void ui::mission_briefing_window::init() {
    rich_text_reset(0);

    // load map!
    if (!g_mission_briefing.campaign_mission_loaded) {
        g_mission_briefing.campaign_mission_loaded = 1;
    }
}

int ui::mission_briefing_window::draw_background() {
    auto &data = g_mission_briefing;
    window_draw_underlying_window();

    int text_id = 200 + scenario_campaign_scenario_id();
    const lang_message* msg = lang_get_message(text_id);

    auto &ui = g_mission_briefing;

    ui["title"].text((pcstr)msg->title.text);
    ui["subtitle"].text((pcstr)msg->subtitle.text);
    ui["difficulty_label"].text(ui::str(153, g_settings.difficulty + 1));

    const pcstr widgets[] = {"goal_0", "goal_1", "goal_2", "goal_3", "goal_4", "goal_5"};
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

    int immediate_goal_text = tutorial_get_immediate_goal_text();
    if (immediate_goal_text) {
        ui["goal_immediate"].text(ui::str(62, immediate_goal_text));
    }

    ui["description_text"] = (pcstr)msg->content.text;

    ui["back"].enabled = !ui.is_review && game_mission_has_choice();
    ui["back"].onclick([] {
        if (!g_mission_briefing.is_review) {
            g_sound.speech_stop();
            window_mission_next_selection_show();
        }
    });

    ui["start_mission"].onclick([] {
        g_sound.speech_stop();
        g_sound.music_update(/*force*/true);
        window_city_show();
        city_mission_reset_save_start();
    });

    ui["dec_difficulty"].enabled = !ui.is_review;
    ui["dec_difficulty"].onclick([] {
        g_settings.decrease_difficulty();
        window_invalidate();
    });

    ui["inc_difficulty"].enabled = !ui.is_review;
    ui["inc_difficulty"].onclick([] {
        g_settings.increase_difficulty();
        window_invalidate();
    });

    return 0;
}

static void show(void) {
    static window_type window = {
        WINDOW_MISSION_BRIEFING,
        [] () { g_mission_briefing.draw_background(); },
        [] () { g_mission_briefing.ui_draw_foreground(); },
        [] (const mouse *m, const hotkeys *h) { g_mission_briefing.ui_handle_mouse(m); }
    };
    
    g_mission_briefing.init();
    window_show(&window);
}

void window_mission_briefing_show() {
    auto &data = g_mission_briefing;
    data.is_review = 0;
    data.campaign_mission_loaded = 0;
    window_intermezzo_show(INTERMEZZO_MISSION_BRIEFING, show);
}

void window_mission_briefing_show_review() {
    auto &data = g_mission_briefing;
    data.is_review = 1;
    data.campaign_mission_loaded = 1;
    window_intermezzo_show(INTERMEZZO_MISSION_BRIEFING, show);
}
