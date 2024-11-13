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
#include "window/mission_briefing.h"
#include "game/game.h"

static void button_start(int param1, int param2);

static const int BACKGROUND_IMAGE_OFFSET[] = {0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 0};

static const struct {
    int x_peaceful;
    int y_peaceful;
    int x_military;
    int y_military;
} CAMPAIGN_SELECTION[12] = {
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {292, 182, 353, 232},
  {118, 202, 324, 286},
  {549, 285, 224, 121},
  {173, 109, 240, 292},
  {576, 283, 19, 316},
  {97, 240, 156, 59},
  {127, 300, 579, 327},
  {103, 35, 410, 109},
  {191, 153, 86, 8},
  {200, 300, 400, 300},
};

static image_button image_button_start_mission = {0, 0, 27, 27, IB_NORMAL, GROUP_BUTTON_EXCLAMATION, 4, button_start, button_none, 1, 0, 1};

struct mission_next_t {
    int choice;
    int focus_button;
};

mission_next_t g_mission_next;

static void draw_background(int) {
    painter ctx = game.painter();
    int rank = scenario_campaign_rank();

    ImageDraw::img_background(ctx, image_id_from_group(GROUP_SELECT_MISSION_BACKGROUND));
    graphics_set_to_dialog();
    ImageDraw::img_generic(ctx, image_id_from_group(GROUP_NEXT_MISSION_SELECT) + BACKGROUND_IMAGE_OFFSET[rank], vec2i{0, 0});
    lang_text_draw(144, 1 + 3 * rank, 20, 410, FONT_LARGE_BLACK_ON_LIGHT);
    if (g_mission_next.choice)
        lang_text_draw_multiline(144, 1 + 3 * rank + g_mission_next.choice, vec2i{20, 440}, 560, FONT_NORMAL_BLACK_ON_LIGHT);
    else {
        lang_text_draw_multiline(144, 0, vec2i{20, 440}, 560, FONT_NORMAL_BLACK_ON_LIGHT);
    }
    graphics_reset_dialog();
}

static void draw_foreground(int) {
    painter ctx = game.painter();
    graphics_set_to_dialog();

    if (g_mission_next.choice > 0) {
        image_buttons_draw({580, 410}, &image_button_start_mission, 1);
    }

    int rank = scenario_campaign_rank();
    vec2i peaceful{CAMPAIGN_SELECTION[rank].x_peaceful - 4, CAMPAIGN_SELECTION[rank].y_peaceful - 4};
    vec2i military{CAMPAIGN_SELECTION[rank].x_military - 4, CAMPAIGN_SELECTION[rank].y_military - 4};
    int image_id = image_id_from_group(GROUP_SELECT_MISSION_BUTTON);
    if (g_mission_next.choice == 0) {
        ImageDraw::img_generic(ctx, g_mission_next.focus_button == 1 ? image_id + 1 : image_id, peaceful);
        ImageDraw::img_generic(ctx, g_mission_next.focus_button == 2 ? image_id + 1 : image_id, military);
    } else if (g_mission_next.choice == 1) {
        ImageDraw::img_generic(ctx, g_mission_next.focus_button == 1 ? image_id + 1 : image_id + 2, peaceful);
        ImageDraw::img_generic(ctx, g_mission_next.focus_button == 2 ? image_id + 1 : image_id, military);
    } else {
        ImageDraw::img_generic(ctx, g_mission_next.focus_button == 1 ? image_id + 1 : image_id, peaceful);
        ImageDraw::img_generic(ctx, g_mission_next.focus_button == 2 ? image_id + 1 : image_id + 2, military);
    }
    graphics_reset_dialog();
}

static int is_mouse_hit(const mouse* m, int x, int y, int size) {
    return x <= m->x && m->x < x + size && y <= m->y && m->y < y + size;
}
static void handle_input(const mouse* m, const hotkeys* h) {
    const mouse* m_dialog = mouse_in_dialog(m);

    int rank = scenario_campaign_rank();
    int x_peaceful = CAMPAIGN_SELECTION[rank].x_peaceful - 4;
    int y_peaceful = CAMPAIGN_SELECTION[rank].y_peaceful - 4;
    int x_military = CAMPAIGN_SELECTION[rank].x_military - 4;
    int y_military = CAMPAIGN_SELECTION[rank].y_military - 4;
    g_mission_next.focus_button = 0;
    if (is_mouse_hit(m_dialog, x_peaceful, y_peaceful, 44))
        g_mission_next.focus_button = 1;

    if (is_mouse_hit(m_dialog, x_military, y_military, 44))
        g_mission_next.focus_button = 2;

    if (g_mission_next.choice > 0) {
        if (image_buttons_handle_mouse(m_dialog, {580, 410}, &image_button_start_mission, 1, 0))
            return;

        if (m_dialog->right.went_up || h->escape_pressed) {
            g_mission_next.choice = 0;
        }
    } else if (h->escape_pressed)
        hotkey_handle_escape();

    if (m_dialog->left.went_up) {
        // TODO
        //        if (is_mouse_hit(m_dialog, x_peaceful, y_peaceful, 44)) {
        //            scenario_set_campaign_mission(game_mission_peaceful());
        //            data.choice = 1;
        //            if (m_dialog->left.double_click) {
        //                button_start(0, 0);
        //                return;
        //            }
        //            window_invalidate();
        //            sound_speech_play_file("Wavs/fanfare_nu1.wav");
        //        }
        //        if (is_mouse_hit(m_dialog, x_military, y_military, 44)) {
        //            scenario_set_campaign_mission(game_mission_military());
        //            data.choice = 2;
        //            if (m_dialog->left.double_click) {
        //                button_start(0, 0);
        //                return;
        //            }
        //            window_invalidate();
        //            sound_speech_play_file("Wavs/fanfare_nu5.wav");
        //        }
    }
}
static void button_start(int param1, int param2) {
    window_mission_briefing_show();
}

void window_mission_next_selection_show(void) {
    if (!game_mission_has_choice()) {
        int scenario_id = scenario_campaign_scenario_id();
        const mission_step_t* current_mission = get_scenario_step_data(scenario_id);
        const mission_step_t* next_mision = get_scenario_step_data(scenario_id + 1);
        if (current_mission->campaign_id == next_mision->campaign_id) {
            GamestateIO::load_mission(scenario_id + 1, true);
            return;
        }
        window_main_menu_show(true);
        return;
    }
    window_type window = {
        WINDOW_MISSION_SELECTION,
        draw_background,
        draw_foreground,
        handle_input
    };
    g_mission_next.choice = 0;
    g_mission_next.focus_button = 0;
    window_show(&window);
}
