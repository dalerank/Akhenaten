#include <tgmath.h>
#include <city/floods.h>
#include <core/random.h>
#include "city.h"

#include "building/menu.h"
#include "city/message.h"
#include "city/view.h"
#include "city/warning.h"
#include "core/direction.h"
#include "core/game_environment.h"
#include "game/orientation.h"
#include "game/state.h"
#include "game/undo.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/image_button.h"
#include "graphics/lang_text.h"
#include "graphics/screen.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "map/orientation.h"
#include "scenario/property.h"
#include "widget/city.h"
#include "widget/minimap.h"
#include "widget/sidebar/common.h"
#include "widget/sidebar/extra.h"
#include "widget/sidebar/slide.h"
#include "window/advisors.h"
#include "window/build_menu.h"
#include "window/city.h"
#include "window/empire.h"
#include "window/message_dialog.h"
#include "window/message_list.h"
#include "window/mission_briefing.h"
#include "window/overlay_menu.h"

#define MINIMAP_Y_OFFSET 59

static void button_overlay(int param1, int param2);
static void button_collapse_expand(int param1, int param2);
static void button_build(int submenu, int param2);
static void button_undo(int param1, int param2);
static void button_messages(int param1, int param2);
static void button_help(int param1, int param2);
static void button_go_to_problem(int param1, int param2);
static void button_advisors(int param1, int param2);
static void button_empire(int param1, int param2);
static void button_mission_briefing(int param1, int param2);
static void button_rotate_north(int param1, int param2);
static void button_rotate(int clockwise, int param2);

static image_button buttons_overlays_collapse_sidebar[][2] = {
        {
                {127, 5, 31, 20, IB_NORMAL, 90,  0, button_collapse_expand, button_none, 0, 0, 1},
                {4, 3, 117, 31, IB_NORMAL, 93, 0, button_overlay, button_help, 0, MESSAGE_DIALOG_OVERLAYS, 1}
        },
        {
                {128, 0, 31, 20, IB_NORMAL, 176, 7, button_collapse_expand, button_none, 0, 0, 1},
//        {4 - 15 - 5, 2, 117, 20, IB_NORMAL, 93, 0, button_overlay, button_help, 0, MESSAGE_DIALOG_OVERLAYS, 1}
        }
};

static image_button button_expand_sidebar[][1] = {
        {
                {6, 4, 31, 20, IB_NORMAL, 90,  4,  button_collapse_expand, button_none, 0, 0, 1}
        },
        {
                {8, 0, 31, 20, IB_NORMAL, 176, 10, button_collapse_expand, button_none, 0, 0, 1}
        }
};

#define CL_ROW0 21 //22

static image_button buttons_build_collapsed[][20] = {
        {
                {2, 32,      39, 26, IB_NORMAL, GROUP_SIDEBAR_BUTTONS, 0,  button_build, button_none, BUILD_MENU_VACANT_HOUSE, 0, 1},
                {2, 67, 39, 26, IB_NORMAL, GROUP_SIDEBAR_BUTTONS, 8, button_build, button_none, BUILD_MENU_CLEAR_LAND, 0, 1},
                {2, 102, 39, 26, IB_NORMAL, GROUP_SIDEBAR_BUTTONS, 12, button_build, button_none, BUILD_MENU_ROAD, 0, 1},
                {2, 137, 39, 26, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 4, button_build, button_none, BUILD_MENU_WATER, 0, 1},
                {2, 172, 39, 26, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 40, button_build, button_none, BUILD_MENU_HEALTH, 0, 1},
                {2, 207, 39, 26, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 28, button_build, button_none, BUILD_MENU_RELIGION, 0, 1},
                {2, 242, 39, 26, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 24, button_build, button_none, BUILD_MENU_EDUCATION, 0, 1},
                {2, 277, 39, 26, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 20, button_build, button_none, BUILD_MENU_ENTERTAINMENT, 0, 1},
                {2, 312, 39, 26, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 16, button_build, button_none, BUILD_MENU_ADMINISTRATION, 0, 1},
                {2, 347, 39, 26, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 44, button_build, button_none, BUILD_MENU_ENGINEERING, 0, 1},
                {2, 382, 39, 26, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 36, button_build, button_none, BUILD_MENU_SECURITY, 0, 1},
                {2, 417, 39, 26, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 32, button_build, button_none, BUILD_MENU_INDUSTRY, 0, 1},
        },
        {
                {9, CL_ROW0, 36, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 90, button_build, button_none, BUILD_MENU_VACANT_HOUSE, 0, 1},
                {9, CL_ROW0 + 36, 36, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 94, button_build, button_none, BUILD_MENU_CLEAR_LAND, 0, 1},
                {9, CL_ROW0 + 71, 36, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 98, button_build, button_none, BUILD_MENU_ROAD, 0, 1},
                {9, CL_ROW0 + 108, 36, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 102, button_build, button_none, BUILD_MENU_FOOD, 0, 1},
                {9, CL_ROW0 + 142, 36, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 106, button_build, button_none, BUILD_MENU_INDUSTRY, 0, 1},
                {9, CL_ROW0 + 177, 36, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 110, button_build, button_none, BUILD_MENU_DISTRIBUTION, 0, 1},
                {9, CL_ROW0 + 212, 36, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 114, button_build, button_none, BUILD_MENU_ENTERTAINMENT, 0, 1},
                {9, CL_ROW0 + 245, 36, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 118, button_build, button_none, BUILD_MENU_RELIGION, 0, 1},
                {9, CL_ROW0 + 281, 36, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 122, button_build, button_none, BUILD_MENU_EDUCATION, 0, 1},
                {9, CL_ROW0 + 317, 36, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 126, button_build, button_none, BUILD_MENU_HEALTH, 0, 1},
                {9, CL_ROW0 + 353, 36, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 130, button_build, button_none, BUILD_MENU_ADMINISTRATION, 0, 1},
                {9, CL_ROW0 + 385, 36, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 134, button_build, button_none, BUILD_MENU_SECURITY, 0, 1},
        }
};

#define COL1 9
#define COL2 COL1 + 34 + 3
#define COL3 COL2 + 36 + 4
#define COL4 COL3 + 34 + 5

#define ROW1 251
#define ROW2 ROW1 + 48 + 1
#define ROW3 ROW2 + 50 + 1
#define ROW4 ROW3 + 49 + 4

static image_button buttons_build_expanded[][20] = {
        {
                {13, 277,    39, 26, IB_NORMAL, GROUP_SIDEBAR_BUTTONS, 0, button_build, button_none, BUILD_MENU_VACANT_HOUSE, 0, 1},
                {63, 277,    39, 26, IB_NORMAL, GROUP_SIDEBAR_BUTTONS, 8, button_build, button_none, BUILD_MENU_CLEAR_LAND, 0, 1},
                {113, 277,   39, 26, IB_NORMAL, GROUP_SIDEBAR_BUTTONS, 12, button_build, button_none, BUILD_MENU_ROAD,       0, 1},
                {13, 313,    39, 26, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 4,  button_build, button_none, BUILD_MENU_WATER, 0, 1},
                {63, 313,    39, 26, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 40, button_build, button_none, BUILD_MENU_HEALTH,   0, 1},
                {113, 313,   39, 26, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 28, button_build, button_none, BUILD_MENU_RELIGION,     0, 1},
                {13, 349,    39, 26, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 24, button_build, button_none, BUILD_MENU_EDUCATION,     0, 1},
                {63, 349,    39, 26, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 20, button_build, button_none, BUILD_MENU_ENTERTAINMENT, 0, 1},
                {113, 349,   39, 26, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 16, button_build, button_none, BUILD_MENU_ADMINISTRATION, 0, 1},
                {13, 385,    39, 26, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 44, button_build, button_none, BUILD_MENU_ENGINEERING, 0, 1},
                {63, 385,    39, 26, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 36, button_build, button_none, BUILD_MENU_SECURITY,       0, 1},
                {113, 385,   39, 26, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 32, button_build, button_none, BUILD_MENU_INDUSTRY, 0, 1},
                {13, 421,    39, 26, IB_NORMAL, GROUP_SIDEBAR_BUTTONS, 48, button_undo, button_none, 0, 0, 1},
                {63, 421,    39, 26, IB_NORMAL, GROUP_MESSAGE_ICON,    18, button_messages, button_help, 0, MESSAGE_DIALOG_MESSAGES, 1},
                {113, 421,   39, 26, IB_NORMAL, GROUP_MESSAGE_ICON,    22, button_go_to_problem, button_none, 0, 0, 1},
        },
        {
                {COL1, ROW1, 34, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 0, button_build, button_none, BUILD_MENU_VACANT_HOUSE, 0, 1},
                {COL1, ROW2, 34, 50, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 4, button_build, button_none, BUILD_MENU_ROAD,       0, 1},
                {COL1, ROW3, 34, 49, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 8,  button_build, button_none, BUILD_MENU_CLEAR_LAND, 0, 1},

                {COL2, ROW1, 36, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 12, button_build, button_none, BUILD_MENU_FOOD,  0, 1},
                {COL2, ROW2, 36, 50, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 16, button_build, button_none, BUILD_MENU_INDUSTRY, 0, 1},
                {COL2, ROW3, 36, 49, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 20, button_build, button_none, BUILD_MENU_DISTRIBUTION, 0, 1},

                {COL3, ROW1, 34, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 24, button_build, button_none, BUILD_MENU_ENTERTAINMENT, 0, 1},
                {COL3, ROW2, 34, 50, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 28, button_build, button_none, BUILD_MENU_RELIGION,      0, 1},
                {COL3, ROW3, 34, 49, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 32, button_build, button_none, BUILD_MENU_EDUCATION,      0, 1},

                {COL4, ROW1, 34, 48, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 36, button_build, button_none, BUILD_MENU_HEALTH,      0, 1},
                {COL4, ROW2, 34, 50, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 40, button_build, button_none, BUILD_MENU_ADMINISTRATION, 0, 1},
                {COL4, ROW3, 34, 49, IB_BUILD, GROUP_SIDEBAR_BUTTONS, 44, button_build, button_none, BUILD_MENU_SECURITY, 0, 1},

                {COL1, ROW4, 35, 45, IB_NORMAL, GROUP_SIDEBAR_BUTTONS, 48, button_undo, button_none, 0, 0, 1},
                {COL2, ROW4, 38, 45, IB_NORMAL, GROUP_SIDEBAR_BUTTONS, 52, button_messages, button_help, 0, MESSAGE_DIALOG_MESSAGES, 1},
                {COL3, ROW4, 28, 45, IB_NORMAL, GROUP_SIDEBAR_BUTTONS, 56, button_go_to_problem, button_none, 0, 0, 1},
//        {COL4 - 9, ROW4, 43, 45, IB_NORMAL, GROUP_SIDEBAR_BUTTONS, 60, button_mission_briefing, button_none, 0, 0, 1},
        }
};

static image_button buttons_top_expanded[][10] = {
        {
                {7, 155, 71, 23, IB_NORMAL, GROUP_SIDEBAR_ADVISORS_EMPIRE, 0, button_advisors, button_none, 0, 0, 1},
                {84, 155, 71, 23, IB_NORMAL, GROUP_SIDEBAR_ADVISORS_EMPIRE, 3, button_empire, button_help, 0, MESSAGE_DIALOG_EMPIRE_MAP, 1},
                {7, 184,   33, 22, IB_NORMAL, GROUP_SIDEBAR_BRIEFING_ROTATE_BUTTONS, 0, button_mission_briefing, button_none, 0, 0, 1},
                {46, 184, 33, 22, IB_NORMAL, GROUP_SIDEBAR_BRIEFING_ROTATE_BUTTONS, 3, button_rotate_north, button_none, 0, 0, 1},
                {84, 184, 33, 22, IB_NORMAL, GROUP_SIDEBAR_BRIEFING_ROTATE_BUTTONS, 6, button_rotate, button_none, 0, 0, 1},
                {123, 184, 33, 22, IB_NORMAL, GROUP_SIDEBAR_BRIEFING_ROTATE_BUTTONS, 9, button_rotate, button_none, 1, 0, 1},
        },
        {
                {COL1 + 7, 143, 60, 36, IB_NORMAL, GROUP_SIDEBAR_BUTTONS, 64, button_advisors, button_none, 0, 0, 1},
                {COL3 + 4, 143, 62, 36, IB_NORMAL, GROUP_SIDEBAR_BUTTONS, 68, button_empire, button_help, 0, MESSAGE_DIALOG_EMPIRE_MAP, 1},
//        {COL1, 184, 33, 22, IB_NORMAL, GROUP_SIDEBAR_BRIEFING_ROTATE_BUTTONS, 0, button_mission_briefing, button_none, 0, 0, 1},
                {COL4 - 9, ROW4, 43, 45, IB_NORMAL, GROUP_SIDEBAR_BUTTONS, 60, button_mission_briefing, button_none, 0, 0, 1},
//        {COL2, 184, 33, 22, IB_NORMAL, GROUP_SIDEBAR_BRIEFING_ROTATE_BUTTONS, 3, button_rotate_north, button_none, 0, 0, 1},
//        {COL3, 184, 33, 22, IB_NORMAL, GROUP_SIDEBAR_BRIEFING_ROTATE_BUTTONS, 6, button_rotate, button_none, 0, 0, 1},
//        {COL4, 184, 33, 22, IB_NORMAL, GROUP_SIDEBAR_BRIEFING_ROTATE_BUTTONS, 9, button_rotate, button_none, 1, 0, 1},
        }
};

static struct {
    int focus_button_for_tooltip;
} data;

#include "game/time.h"
#include "city/data_private.h"
#include "city/data_private.h"
#include "game/tutorial.h"
#include "core/string.h"

static void draw_debug_ui(int x, int y) {
    auto time = give_me_da_time();
    uint8_t str[100];

    /////// TIME
    if (true) {
        draw_debug_line(str, x, y + 15, 50, "tick:", time->tick); draw_debug_line(str, x + 80, y + 15, 50, "iscycle:", game_time_absolute_tick() % 25 == 0);
        draw_debug_line(str, x, y + 25, 50, "day:", time->day);
        draw_debug_line(str, x, y + 35, 50, "month:", time->month);
        draw_debug_line(str, x, y + 45, 50, "year:", time->year);
        draw_debug_line(str, x, y + 55, 60, "abs. tick:", game_time_absolute_tick()); // absolute day of the year
        draw_debug_line(str, x, y + 65, 60, "abs. day:", game_time_absolute_day()); // absolute day of the year
        y += 70;
    }

    /////// RANDOM
    if (false) {
        auto randm = give_me_da_random_data();

        int cl = 60;
        draw_debug_line(str, x, y + 15, cl, "iv1:", randm->iv1);
        draw_debug_line(str, x, y + 25, cl, "iv2:", randm->iv2);
        draw_debug_line(str, x, y + 35, cl, "1_3b:", randm->random1_3bit);
        draw_debug_line(str, x, y + 45, cl, "1_7b:", randm->random1_7bit);
        draw_debug_line(str, x, y + 55, cl, "1_15b:", randm->random1_15bit);
        draw_debug_line(str, x, y + 65, cl, "2_3b:", randm->random2_3bit);
        draw_debug_line(str, x, y + 75, cl, "2_7b:", randm->random2_7bit);
        draw_debug_line(str, x, y + 85, cl, "2_15b:", randm->random2_15bit);
        y += 90;
    }

    /////// FLOODS
    if (false) {
        auto floods = give_me_da_floods_data();

        int c_curr = floodplains_current_cycle();
        int c_start = floodplains_flooding_start_cycle();
        int c_end = floodplains_flooding_end_cycle();
        int c_hh = floodplains_flooding_rest_period_cycle();
        int c_minus49 = c_start - 49;
        int c_minus27 = c_start - 27;
        int c_first_rest = c_start + c_hh;
        int c_second_rest = c_end - c_hh;
        int c_plus28 = c_end + 28;

        int cl = 60;
        draw_debug_line(str, x, y + 15, cl, "current:", c_curr); // current cycle
        draw_debug_line(str, x, y + 25, cl, "t-49:", c_minus49); // 49 days prior
        draw_debug_line(str, x, y + 35, cl, "t-27:", c_minus27); // 27 days prior
        draw_debug_line(str, x, y + 45, cl, "start:", c_start); // flood start
        draw_debug_line(str, x, y + 55, cl, "rest-1:", c_first_rest); // first rest period
        draw_debug_line(str, x, y + 65, cl, "rest-2:", c_second_rest); // second rest period
        draw_debug_line(str, x, y + 75, cl, "end:", c_end); // flood end
        draw_debug_line(str, x, y + 85, cl, "final:", c_plus28); // lands farmable again

        cl = 100;
        draw_debug_line(str, x, y + 105, cl, "season_initial:", floods->season_initial);
        draw_debug_line(str, x, y + 115, cl, "duration_initial:", floods->duration_initial);
        draw_debug_line(str, x, y + 125, cl, "quality_initial:", floods->quality_initial);
        draw_debug_line(str, x, y + 135, cl, "season:", floods->season);
        draw_debug_line(str, x, y + 145, cl, "duration:", floods->duration);
        draw_debug_line(str, x, y + 155, cl, "quality:", floods->quality);
        draw_debug_line(str, x, y + 165, cl, "(unk00):", floods->unk00);
        draw_debug_line(str, x, y + 175, cl, "quality_next:", floods->quality_next);
        draw_debug_line(str, x, y + 185, cl, "quality_last:", floods->quality_last);

        cl = 60;
        draw_debug_line(str, x, y + 205, cl, "dat_30:", floods->flood_progress); // status 30 (???)
        draw_debug_line(str, x, y + 215, cl, "(unk01):", floods->unk01); // ???
        draw_debug_line(str, x, y + 225, cl, "state:", floods->state); // floodplains state
        draw_debug_line(str, x, y + 235, cl, "dat_10:", floods->floodplain_width); // status 10 (???)
        draw_debug_line(str, x, y + 245, cl, "(unk02):", floods->floodplain_width); // status 10 (???)
        y += 350;
    }

    /////// CAMERA
    if (false) {
        int tx, ty;
        int px, py;
        city_view_get_camera_tile(&tx, &ty);
        city_view_get_camera_pixel_offset(&px, &py);

        view_data* viewdata = city_view_data_unsafe();
        int real_max_x;
        int real_max_y;
        city_view_get_camera_max_tile(&real_max_x, &real_max_y);

        int max_x_pixel_offset;
        int max_y_pixel_offset;
        city_view_get_camera_max_pixel_offset(&max_x_pixel_offset, &max_y_pixel_offset);

        draw_debug_line_double_left(str, x, y + 15, 90, 40, "camera:", viewdata->camera.position.x, viewdata->camera.position.y);
        draw_debug_line_double_left(str, x, y + 25, 90, 40, "---min:", SCROLLABLE_X_MIN_TILE(), SCROLLABLE_Y_MIN_TILE());
        draw_debug_line_double_left(str, x, y + 35, 90, 40, "tile:", tx, ty);
        draw_debug_line_double_left(str, x, y + 45, 90, 40, "---max:", real_max_x, real_max_y);

        draw_debug_line_double_left(str, x, y + 65, 90, 40, "---min:", 0, 0);
        draw_debug_line_double_left(str, x, y + 75, 90, 40, "pixel:", px, py);
        draw_debug_line_double_left(str, x, y + 85, 90, 40, "---max:", max_x_pixel_offset, max_y_pixel_offset);

        draw_debug_line_double_left(str, x, y + 105, 90, 40, "v.tiles:", viewdata->viewport.width_pixels / 60, viewdata->viewport.height_pixels / 30);
        draw_debug_line_double_left(str, x, y + 115, 90, 40, "v.pixels:", viewdata->viewport.width_pixels, viewdata->viewport.height_pixels);
        y += 120;
    }

    /////// TUTORIAL
    if (false) {auto flags = give_me_da_tut_flags();
        const char* const flagnames[41] = {
                "fire","pop_150","meat_400","collapse","gold_500","temples_done","disease","figs_800","???","pottery_200",
                "beer_300","","","","","tut1 start","tut2 start","tut3 start","tut4 start","tut5 start",
                "tut6 start","tut7 start","tut8 start","","","","// bazaar","// pottery","","",
                "// tut4 ???","// tut5 ???","","// water supply","// tut4 ???","","// entertainment","// temples","// taxes","// mansion",
                "",
        };
        for (int i = 0; i < 41; i++) {
            int f = flags->pharaoh.flags[i];
            switch (i) {
                case 0: f = flags->pharaoh.fire; break;
                case 1: f = flags->pharaoh.population_150_reached; break;
                case 2: f = flags->pharaoh.gamemeat_400_stored; break;
                case 3: f = flags->pharaoh.collapse; break;
                case 4: f = flags->pharaoh.gold_mined_500; break;
                case 5: f = flags->pharaoh.temples_built; break;
//            case 6: ??? crime?
                case 7: f = flags->pharaoh.figs_800_stored; break;
                case 8: f = flags->pharaoh.disease; break;
                case 9: f = flags->pharaoh.pottery_made; break;
                case 10: f = flags->pharaoh.beer_made; break;
                case 11: f = flags->pharaoh.spacious_apartment; break;
                    //
                case 15: f = flags->pharaoh.tut1_start; break;
                case 16: f = flags->pharaoh.tut2_start; break;
                case 17: f = flags->pharaoh.tut3_start; break;
                case 18: f = flags->pharaoh.tut4_start; break;
                case 19: f = flags->pharaoh.tut5_start; break;
                case 20: f = flags->pharaoh.tut6_start; break;
                case 21: f = flags->pharaoh.tut7_start; break;
                case 22: f = flags->pharaoh.tut8_start; break;
            }

            int color = COLOR_WHITE;
            if (f)
                color = COLOR_GREEN;
            string_from_int(str, i, 0);
            text_draw_shadow(str, x + 3, y + 115 + i * 10, color);
            text_draw_shadow((uint8_t *) string_from_ascii(":"), x + 3 + 20, y + 115 + i * 10, color);
            string_from_int(str, f, 0);
            text_draw_shadow(str, x + 3 + 30, y + 115 + i * 10, color);
            text_draw_shadow((uint8_t *) string_from_ascii(flagnames[i]), x + 3 + 45, y + 115 + i * 10, color);
        }
    }
}

static void draw_overlay_text(int x_offset) {
    if (GAME_ENV == ENGINE_ENV_C3) {
        if (game_state_overlay())
            lang_text_draw_centered(14, game_state_overlay(), x_offset, 32, 117, FONT_NORMAL_GREEN);
        else
            lang_text_draw_centered(6, 4, x_offset, 32, 117, FONT_NORMAL_GREEN);
    }
    if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        if (game_state_overlay())
            lang_text_draw_centered(14, game_state_overlay(), x_offset - 15, 30, 117, FONT_NORMAL_GREEN);
        else
            lang_text_draw_centered(6, 4, x_offset - 15, 30, 117, FONT_NORMAL_GREEN);
    }
}
static void draw_sidebar_remainder(int x_offset, bool is_collapsed) {
    int width = SIDEBAR_EXPANDED_WIDTH[GAME_ENV];
    if (is_collapsed)
        width = SIDEBAR_COLLAPSED_WIDTH;
    int available_height = sidebar_common_get_height() - SIDEBAR_MAIN_SECTION_HEIGHT;
    int extra_height = sidebar_extra_draw_background(x_offset, SIDEBAR_MAIN_SECTION_HEIGHT + TOP_MENU_HEIGHT[GAME_ENV], 162, available_height, is_collapsed, SIDEBAR_EXTRA_DISPLAY_ALL);
    sidebar_extra_draw_foreground();
    int relief_y_offset =
            SIDEBAR_MAIN_SECTION_HEIGHT + TOP_MENU_HEIGHT[0] + extra_height; // + (GAME_ENV == ENGINE_ENV_PHARAOH) * 6;
    sidebar_common_draw_relief(x_offset, relief_y_offset, GROUP_SIDE_PANEL, is_collapsed);
}
static void draw_number_of_messages(int x_offset) {
    int messages = city_message_count();
    buttons_build_expanded[GAME_ENV][13].enabled = messages > 0;
    buttons_build_expanded[GAME_ENV][14].enabled = city_message_problem_area_count();
    if (messages) {
        text_draw_number_centered_colored(messages, x_offset + 74, 452, 32, FONT_SMALL_PLAIN, COLOR_BLACK);
        text_draw_number_centered_colored(messages, x_offset + 73, 453, 32, FONT_SMALL_PLAIN, COLOR_WHITE);
    }
}

static void draw_buttons_collapsed(int x_offset) {
    image_buttons_draw(x_offset, TOP_MENU_HEIGHT[GAME_ENV], button_expand_sidebar[GAME_ENV], 1);
    image_buttons_draw(x_offset, TOP_MENU_HEIGHT[GAME_ENV], buttons_build_collapsed[GAME_ENV], 12);
}
static void draw_buttons_expanded(int x_offset) {
    buttons_build_expanded[GAME_ENV][12].enabled = game_can_undo();
    if (GAME_ENV == ENGINE_ENV_C3) {
        image_buttons_draw(x_offset, TOP_MENU_HEIGHT[GAME_ENV], buttons_overlays_collapse_sidebar[GAME_ENV], 2);
        image_buttons_draw(x_offset, TOP_MENU_HEIGHT[GAME_ENV], buttons_build_expanded[GAME_ENV], 15);
        image_buttons_draw(x_offset, TOP_MENU_HEIGHT[GAME_ENV], buttons_top_expanded[GAME_ENV], 6);
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        image_buttons_draw(x_offset, TOP_MENU_HEIGHT[GAME_ENV], buttons_overlays_collapse_sidebar[GAME_ENV], 1);
        image_buttons_draw(x_offset, TOP_MENU_HEIGHT[GAME_ENV], buttons_build_expanded[GAME_ENV], 15);
        image_buttons_draw(x_offset, TOP_MENU_HEIGHT[GAME_ENV], buttons_top_expanded[GAME_ENV], 3);
    }
}

static void refresh_build_menu_buttons(void) {
    int num_buttons = 12;
    for (int i = 0; i < num_buttons; i++) {
        buttons_build_expanded[GAME_ENV][i].enabled = 1;
        if (building_menu_count_items(buttons_build_expanded[GAME_ENV][i].parameter1) <= 0)
            buttons_build_expanded[GAME_ENV][i].enabled = 0;

        buttons_build_collapsed[GAME_ENV][i].enabled = 1;
        if (building_menu_count_items(buttons_build_collapsed[GAME_ENV][i].parameter1) <= 0)
            buttons_build_collapsed[GAME_ENV][i].enabled = 0;
    }
}
static void draw_collapsed_background(void) {
    int x_offset = sidebar_common_get_x_offset_collapsed();
    if (GAME_ENV == ENGINE_ENV_C3)
        image_draw(image_id_from_group(GROUP_SIDE_PANEL), x_offset, TOP_MENU_HEIGHT[GAME_ENV]);
    else if (GAME_ENV == ENGINE_ENV_PHARAOH)
        image_draw(image_id_from_group(GROUP_SIDE_PANEL) + 1, x_offset, TOP_MENU_HEIGHT[GAME_ENV]);
    draw_buttons_collapsed(x_offset);
    draw_sidebar_remainder(x_offset, true);
}
static void draw_expanded_background(int x_offset) {
    if (GAME_ENV == ENGINE_ENV_C3) {
        image_draw(image_id_from_group(GROUP_SIDE_PANEL) + 1, x_offset, TOP_MENU_HEIGHT[GAME_ENV]);
        image_draw(window_build_menu_image(), x_offset + 6, 225 + TOP_MENU_HEIGHT[GAME_ENV]);
        widget_minimap_draw(x_offset + 8, MINIMAP_Y_OFFSET, MINIMAP_WIDTH, MINIMAP_HEIGHT, 1);
        draw_number_of_messages(x_offset);
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        image_draw(image_id_from_group(GROUP_SIDE_PANEL), x_offset, TOP_MENU_HEIGHT[GAME_ENV]);
        image_draw(window_build_menu_image(), x_offset + 11, 181 + TOP_MENU_HEIGHT[GAME_ENV]);
        widget_minimap_draw(x_offset + 12, MINIMAP_Y_OFFSET, MINIMAP_WIDTH, MINIMAP_HEIGHT, 1);

        // extra bar spacing on the right
        int block_height = 702;
        int s_end = 768;
        int s_num = ceil((float) (screen_height() - s_end) / (float) block_height);
        int s_start = s_num * block_height;
        for (int i = 0; i < s_num; i++)
            image_draw(image_id_from_group(GROUP_SIDE_PANEL) + 2, x_offset + 162, s_start + i * block_height);
        image_draw(image_id_from_group(GROUP_SIDE_PANEL) + 2, x_offset + 162, 0);
        draw_number_of_messages(x_offset - 26);
    }
    draw_buttons_expanded(x_offset);
    draw_overlay_text(x_offset + 4);

    draw_sidebar_remainder(x_offset, false);
}
void widget_sidebar_city_draw_background(void) {
    if (city_view_is_sidebar_collapsed())
        draw_collapsed_background();
    else
        draw_expanded_background(sidebar_common_get_x_offset_expanded());
}
void widget_sidebar_city_draw_foreground(void) {
    if (building_menu_has_changed())
        refresh_build_menu_buttons();

    if (city_view_is_sidebar_collapsed()) {
        int x_offset = sidebar_common_get_x_offset_collapsed();
        draw_buttons_collapsed(x_offset);
    } else {
        int x_offset = sidebar_common_get_x_offset_expanded();
        draw_buttons_expanded(x_offset);
        draw_overlay_text(x_offset + 4);

        if (GAME_ENV == ENGINE_ENV_C3) {
            widget_minimap_draw(x_offset + 8, MINIMAP_Y_OFFSET, MINIMAP_WIDTH, MINIMAP_HEIGHT, 0);
            draw_number_of_messages(x_offset);
        } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
            widget_minimap_draw(x_offset + 12, MINIMAP_Y_OFFSET, MINIMAP_WIDTH, MINIMAP_HEIGHT, 0);
            draw_number_of_messages(x_offset - 26);
        }

    }
    sidebar_extra_draw_foreground();

    window_request_refresh();
    draw_debug_ui(10, 30);
}
void widget_sidebar_city_draw_foreground_military(void) {
    widget_minimap_draw(sidebar_common_get_x_offset_expanded() + 8, MINIMAP_Y_OFFSET, MINIMAP_WIDTH, MINIMAP_HEIGHT, 1);
}
int widget_sidebar_city_handle_mouse(const mouse *m) {
    if (widget_city_has_input())
        return false;

    bool handled = false;
    int button_id;
    data.focus_button_for_tooltip = 0;
    if (city_view_is_sidebar_collapsed()) {
        int x_offset = sidebar_common_get_x_offset_collapsed();
        handled |= image_buttons_handle_mouse(m, x_offset, 24, button_expand_sidebar[GAME_ENV], 1, &button_id);
        if (button_id)
            data.focus_button_for_tooltip = 12;

        handled |= image_buttons_handle_mouse(m, x_offset, 24, buttons_build_collapsed[GAME_ENV], 12, &button_id);
        if (button_id)
            data.focus_button_for_tooltip = button_id + 19;

    } else {
        if (widget_minimap_handle_mouse(m))
            return true;

        int x_offset = sidebar_common_get_x_offset_expanded();
        handled |= image_buttons_handle_mouse(m, x_offset, 24, buttons_overlays_collapse_sidebar[GAME_ENV], 2,
                                              &button_id);
        if (button_id)
            data.focus_button_for_tooltip = button_id + 9;

        handled |= image_buttons_handle_mouse(m, x_offset, 24, buttons_build_expanded[GAME_ENV], 15, &button_id);
        if (button_id)
            data.focus_button_for_tooltip = button_id + 19;

        handled |= image_buttons_handle_mouse(m, x_offset, 24, buttons_top_expanded[GAME_ENV], 6, &button_id);
        if (button_id)
            data.focus_button_for_tooltip = button_id + 39;

        handled |= sidebar_extra_handle_mouse(m);
    }
//    return 0;
    return handled;
}
int widget_sidebar_city_handle_mouse_build_menu(const mouse *m) {
    if (city_view_is_sidebar_collapsed())
        return image_buttons_handle_mouse(m, sidebar_common_get_x_offset_collapsed(), 24,
                                          buttons_build_collapsed[GAME_ENV], 12, 0);
    else
        return image_buttons_handle_mouse(m, sidebar_common_get_x_offset_expanded(), 24,
                                          buttons_build_expanded[GAME_ENV], 15, 0);
}
int widget_sidebar_city_get_tooltip_text(void) {
    return data.focus_button_for_tooltip;
}

void widget_sidebar_city_release_build_buttons() {
    image_buttons_release_press(buttons_build_expanded[GAME_ENV], 20);
    image_buttons_release_press(buttons_build_collapsed[GAME_ENV], 20);
}

static void slide_finished(void) {
    city_view_toggle_sidebar();
    window_city_show();
    window_draw(1);
}

static void button_overlay(int param1, int param2) {
    window_overlay_menu_show();
}
static void button_collapse_expand(int param1, int param2) {
    city_view_start_sidebar_toggle();
    sidebar_slide(!city_view_is_sidebar_collapsed(), draw_collapsed_background, draw_expanded_background,
                  slide_finished);
}
static void button_build(int submenu, int param2) {
    window_build_menu_show(submenu);
}
static void button_undo(int param1, int param2) {
    game_undo_perform();
    window_invalidate();
}
static void button_messages(int param1, int param2) {
    window_message_list_show();
}
static void button_help(int param1, int param2) {
    window_message_dialog_show(param2, -1, window_city_draw_all);
}
static void button_go_to_problem(int param1, int param2) {
    int grid_offset = city_message_next_problem_area_grid_offset();
    if (grid_offset) {
        city_view_go_to_grid_offset(grid_offset);
        window_city_show();
    } else {
        window_invalidate();
    }
}
static void button_advisors(int param1, int param2) {
    window_advisors_show_checked();
}
static void button_empire(int param1, int param2) {
    window_empire_show_checked();
}
static void button_mission_briefing(int param1, int param2) {
    if (!scenario_is_custom())
        window_mission_briefing_show_review();

}
static void button_rotate_north(int param1, int param2) {
    game_orientation_rotate_north();
    window_invalidate();
}
static void button_rotate(int clockwise, int param2) {
    if (clockwise)
        game_orientation_rotate_right();

    else {
        game_orientation_rotate_left();
    }
    window_invalidate();
}
