#include "building/building_pavilion.h"

#include "building/count.h"
#include "graphics/image.h"
#include "widget/city/ornaments.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"
#include "graphics/elements/ui.h"
#include "city/labor.h"
#include "grid/image.h"
#include "js/js_game.h"

struct pavilion_model : public buildings::model_t<building_pavilion> {
    int base = 0;
} pavilion_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_pavilion);
void config_load_building_pavilion() {
    pavilion_m.load();
    pavilion_m.base = pavilion_m.anim["base"].first_img();
}

bool building_pavilion::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (map_image_at(tile) == pavilion_m.base) {
        building* main = base.main();
        if (main->data.entertainment.days3_or_play) {
            int base_id = building_impl::params(BUILDING_PAVILLION).anim["base"].first_img();
            building_draw_normal_anim(ctx, point + vec2i{64, 0}, &base, tile, image_id_from_group(GROUP_DANCERS_SHOW) - 1, color_mask, base_id);
        }
    }

    return true;
}

void building_pavilion::update_count() const {
    building_increase_type_count(type(), num_workers() > 0);
    building_increase_type_count(BUILDING_BANDSTAND, num_workers() > 0);
    building_increase_type_count(BUILDING_BOOTH, num_workers() > 0);
}

void building_pavilion::spawn_figure() {
    if (!is_main()) {
        return;
    }

    if (common_spawn_figure_trigger(100)) {
        if (data.entertainment.days1 > 0)
            base.create_roaming_figure(FIGURE_JUGGLER, FIGURE_ACTION_94_ENTERTAINER_ROAMING);
        if (data.entertainment.days2 > 0)
            base.create_roaming_figure(FIGURE_MUSICIAN, FIGURE_ACTION_94_ENTERTAINER_ROAMING);
        if (data.entertainment.days3_or_play > 0)
            base.create_roaming_figure(FIGURE_DANCER, FIGURE_ACTION_94_ENTERTAINER_ROAMING);
    }
}

void building_pavilion::window_info_background(object_info &c) {
    c.help_id = 73;
    window_building_play_sound(&c, "wavs/colloseum.wav");
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(74, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    building* b = building_get(c.building_id);

    if (!c.has_road_access)
        window_building_draw_description(c, 69, 25);
    else if (b->num_workers <= 0)
        window_building_draw_description(c, 74, 6);
    else if (!b->data.entertainment.num_shows)
        window_building_draw_description(c, 74, 2);
    else if (b->data.entertainment.num_shows == 2)
        window_building_draw_description(c, 74, 3);
    else if (b->data.entertainment.days1)
        window_building_draw_description(c, 74, 5);
    else if (b->data.entertainment.days2)
        window_building_draw_description(c, 74, 4);

    inner_panel_draw(c.offset.x + 16, c.offset.y + 136, c.bgsize.x - 2, 6);
    window_building_draw_employment(&c, 138);
    if (b->data.entertainment.days1 > 0) {
        int width = lang_text_draw(74, 8, c.offset.x + 32, c.offset.y + 182, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw_amount(8, 44, 2 * b->data.entertainment.days1, c.offset.x + width + 32, c.offset.y + 182, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        lang_text_draw(74, 7, c.offset.x + 32, c.offset.y + 182, FONT_NORMAL_BLACK_ON_DARK);
    }
    if (b->data.entertainment.days2 > 0) {
        int width = lang_text_draw(74, 10, c.offset.x + 32, c.offset.y + 202, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw_amount(8, 44, 2 * b->data.entertainment.days2, c.offset.x + width + 32, c.offset.y + 202, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        lang_text_draw(74, 9, c.offset.x + 32, c.offset.y + 202, FONT_NORMAL_BLACK_ON_DARK);
    }
}
