#include "set_salary.h"

#include "city/city_kingdome_relations.h"
#include "city/city_finance.h"
#include "city/ratings.h"
#include "city/victory.h"
#include "city/city.h"
#include "game/resource.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/view/view.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "window/advisors.h"
#include "game/game.h"

#define MIN_DIALOG_WIDTH 384

static void button_cancel(int param1, int param2);
static void button_set_salary(int rank, int param2);

static generic_button buttons[] = {
  {240, 395, 160, 20, button_cancel, button_none, 0, 0},
  {144, 85, 352, 20, button_set_salary, button_none, 0, 0},
  {144, 105, 352, 20, button_set_salary, button_none, 1, 0},
  {144, 125, 352, 20, button_set_salary, button_none, 2, 0},
  {144, 145, 352, 20, button_set_salary, button_none, 3, 0},
  {144, 165, 352, 20, button_set_salary, button_none, 4, 0},
  {144, 185, 352, 20, button_set_salary, button_none, 5, 0},
  {144, 205, 352, 20, button_set_salary, button_none, 6, 0},
  {144, 225, 352, 20, button_set_salary, button_none, 7, 0},
  {144, 245, 352, 20, button_set_salary, button_none, 8, 0},
  {144, 265, 352, 20, button_set_salary, button_none, 9, 0},
  {144, 285, 352, 20, button_set_salary, button_none, 10, 0},
};

static int focus_button_id;

static int get_dialog_width() {
    int dialog_width = 16 + lang_text_get_width(52, 15, FONT_LARGE_BLACK_ON_LIGHT);
    if (dialog_width < MIN_DIALOG_WIDTH)
        dialog_width = MIN_DIALOG_WIDTH;
    if (dialog_width % 16 != 0) {
        // make sure the width is a multiple of 16
        dialog_width += 16 - dialog_width % 16;
    }
    return dialog_width;
}

static void draw_foreground(int) {
    painter ctx = game.painter();

    graphics_set_to_dialog();

    int dialog_width = get_dialog_width();
    int dialog_x = 128 - (dialog_width - MIN_DIALOG_WIDTH) / 2;
    outer_panel_draw(vec2i{dialog_x, 32}, dialog_width / 16, 25);
    ImageDraw::img_generic(ctx, image_id_resource_icon(RESOURCE_DEBEN), vec2i{dialog_x + 16, 48});
    lang_text_draw_centered(52, 15, dialog_x + 48, 48, dialog_width - 64, FONT_LARGE_BLACK_ON_LIGHT);

    inner_panel_draw({ 144, 80 }, { 22, 15 });

    for (int rank = 0; rank < 11; rank++) {
        e_font font = focus_button_id == rank + 2 ? FONT_NORMAL_YELLOW : FONT_NORMAL_WHITE_ON_DARK;
        int width = lang_text_draw(52, rank + 4, 176, 90 + 20 * rank, font);
        text_draw_money(g_city.kingdome.salary_for_rank(rank), 176 + width, 90 + 20 * rank, font);
    }

    if (!g_city.victory_state.has_won()) {
        if (g_city.kingdome.salary_rank <= g_city.kingdome.player_rank)
            lang_text_draw_multiline(52, 76, vec2i{152, 336}, 336, FONT_NORMAL_BLACK_ON_LIGHT);
        else
            lang_text_draw_multiline(52, 71, vec2i{152, 336}, 336, FONT_NORMAL_BLACK_ON_LIGHT);
    } else {
        lang_text_draw_multiline(52, 77, vec2i{152, 336}, 336, FONT_NORMAL_BLACK_ON_LIGHT);
    }
    button_border_draw(240, 395, 160, 20, focus_button_id == 1);
    lang_text_draw_centered(13, 4, 176, 400, 288, FONT_NORMAL_BLACK_ON_LIGHT);

    graphics_reset_dialog();
}

static void handle_input(const mouse* m, const hotkeys* h) {
    if (generic_buttons_handle_mouse(mouse_in_dialog(m), {0, 0}, buttons, 12, &focus_button_id))
        return;

    if (input_go_back_requested(m, h))
        window_advisors_show();
}

static void button_cancel(int param1, int param2) {
    window_advisors_show();
}

static void button_set_salary(int rank, int param2) {
    if (!g_city.victory_state.has_won()) {
        g_city.kingdome.set_salary_rank(rank);
        g_city.kingdome.update_explanation();
        window_advisors_show();
    }
}

static void draw_background(int) {
    painter ctx = game.painter();
    ImageDraw::img_background(ctx, image_id_from_group(PACK_UNLOADED, 11));
}

void window_set_salary_show(void) {
    static window_type window = {
        WINDOW_SET_SALARY, 
        draw_background,
        draw_foreground, 
        handle_input
    };
    window_show(&window);
}
