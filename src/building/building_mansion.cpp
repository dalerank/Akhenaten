#include "building_mansion.h"

#include "window/building/common.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/text.h"
#include "graphics/elements/button.h"
#include "graphics/elements/generic_button.h"
#include "city/emperor.h"
#include "city/victory.h"
#include "city/finance.h"
#include "city/ratings.h"
#include "widget/city/ornaments.h"
#include "graphics/image.h"

struct window_info_mansion {
    int focus_button_id;
};

static void button_set_salary(int rank, int param2) {
    if (!city_victory_has_won()) {
        city_emperor_set_salary_rank(rank);
        city_finance_update_salary();
        city_ratings_update_kingdom_explanation();
        //window_advisors_show();
    }
}

window_info_mansion g_window_info_mansion;

static generic_button imperial_buttons[] = {
    {40, 90, 400, 20, button_set_salary, button_none, 0, 0},
};

void building_mansion::window_info_background(object_info &c) {
    c.help_id = 78;
    c.go_to_advisor.left_a = ADVISOR_IMPERIAL;
    window_building_play_sound(&c, "wavs/gov_palace.wav");
    outer_panel_draw(c.offset, c.width_blocks, c.height_blocks);
    lang_text_draw_centered(103, 0, c.offset.x, c.offset.y + 10, 16 * c.width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    window_building_draw_description_at(c, 16 * c.height_blocks - 143, 103, 1);

    button_border_draw(c.offset.x + 40, c.offset.y + 90, 400, 20, g_window_info_mansion.focus_button_id == 2);
    int width = lang_text_draw(52, city_emperor_salary_rank() + 4, c.offset.x + 40, c.offset.y + 94, FONT_NORMAL_WHITE_ON_DARK);
    width += text_draw_number(city_emperor_salary_amount(), '@', " ", c.offset.x + 40 + width, c.offset.y + 94, FONT_NORMAL_WHITE_ON_DARK);
    lang_text_draw(52, 3, c.offset.x + 40 + width, c.offset.y + 94, FONT_NORMAL_WHITE_ON_DARK);
}

int building_mansion::window_info_handle_mouse(const mouse *m, object_info &c) {
    return 0;
}

bool building_mansion::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) {
    int max_workers = model()->laborers;
    int image_id;
    switch (type()) {
    case BUILDING_PERSONAL_MANSION:
        image_id = image_group(IMG_PERSONAL_MANSION);
        building_draw_normal_anim(ctx, point + vec2i{34, 2}, &base, tile, image_id, mask);
        break;
    }
    return true;
}
