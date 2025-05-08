#include "records.h"

#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/scrollbar.h"
#include "graphics/view/view.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "content/vfs.h"
#include "game/player_data.h"
#include "game/game.h"

static void on_scroll(void);

#define LIST_X 32
#define LIST_Y 104
#define LIST_WIDTH 33
#define LIST_MAX_SIZE 21

static scrollbar_t g_records_scrollbar = {{LIST_X + LIST_WIDTH * 16, LIST_Y - 12}, (LIST_MAX_SIZE + 1) * 16, on_scroll};

struct records_data_t {
    const dir_listing* file_list;
};

records_data_t g_records_data;

void init() {
    highscores_load();
    g_records_scrollbar.init(0, highscores_count() - LIST_MAX_SIZE);
}

static void draw_background(int) {
    painter ctx = game.painter();
    ImageDraw::img_background(ctx, image_id_from_group(GROUP_SCORES_BACKGROUND));
}
static void draw_foreground(int) {
    graphics_set_to_dialog();

    outer_panel_draw(vec2i{0, 0}, 40, 30);
    inner_panel_draw({ LIST_X, LIST_Y - 12 }, { LIST_WIDTH, LIST_MAX_SIZE + 1 });

    // title
    lang_text_draw_centered(296, 0, 160, 20, 304, FONT_LARGE_BLACK_ON_LIGHT);

    // high scores
    e_font font = FONT_SMALL_SHADED;
    for (int i = 0; i < LIST_MAX_SIZE; i++) {
        const player_record* record = highscores_get(g_records_scrollbar.scroll_position + i);
        if (record->nonempty) {
            text_draw_number(record->score, '@', " ", LIST_X + 10, LIST_Y + 16 * i, font);
            text_draw_number(records_calc_score(record), '@', " ", LIST_X + 80, LIST_Y + 16 * i, font);
            text_draw_number(record->mission_idx, '@', " ", LIST_X + 150, LIST_Y + 16 * i, font);
            text_draw_number(record->rating_culture, '@', " ", LIST_X + 180, LIST_Y + 16 * i, font);
            text_draw_number(record->rating_prosperity, '@', " ", LIST_X + 220, LIST_Y + 16 * i, font);
            text_draw_number(record->rating_kingdom, '@', " ", LIST_X + 260, LIST_Y + 16 * i, font);
            text_draw_number(record->final_population, '@', " ", LIST_X + 310, LIST_Y + 16 * i, font);
            text_draw_number(record->final_funds, '@', " ", LIST_X + 360, LIST_Y + 16 * i, font);
            text_draw_number(record->completion_months, '@', " ", LIST_X + 410, LIST_Y + 16 * i, font);
            text_draw_number(record->difficulty, '@', " ", LIST_X + 440, LIST_Y + 16 * i, font);
            text_draw_number(record->unk09, '@', " ", LIST_X + 475, LIST_Y + 16 * i, font);
            if (record->score_is_valid)
                text_draw((uint8_t*)"V", LIST_X + 510, LIST_Y + 16 * i, font, 0);
            else
                text_draw((uint8_t*)"-", LIST_X + 510, LIST_Y + 16 * i, font, 0);
        }

        //        encoding_from_utf8(data.file_list->files[scrollbar.scroll_position + i], list_name, FILE_NAME_MAX);
        //        e_font font = FONT_NORMAL_BLACK_ON_DARK;
        //        text_ellipsize(list_name, font, MAX_FILE_WINDOW_TEXT_WIDTH);
        //        text_draw(list_name, 160, LIST_Y + 2 + (16 * i), FONT_NORMAL_BLACK_ON_DARK, 0);
    }

    // bottom text
    lang_text_draw_centered(31, 1, 160, 450, 304, FONT_NORMAL_BLACK_ON_LIGHT);

    scrollbar_draw(vec2i{0, 0}, &g_records_scrollbar);

    graphics_reset_dialog();
}

static void on_scroll(void) {
    //    data.message_not_exist_start_time = 0;
}

static void handle_input(const mouse* m, const hotkeys* h) {
    if (input_go_back_requested(m, h))
        window_go_back();

    const mouse* m_dialog = mouse_in_dialog(m);
    if (scrollbar_handle_mouse(vec2i{0, 0}, &g_records_scrollbar, m_dialog))
        return;
}

void window_records_show(void) {
    window_type window = {
        WINDOW_PLAYER_SELECTION,
        draw_background,
        draw_foreground,
        handle_input
    };
    init();
    window_show(&window);
}