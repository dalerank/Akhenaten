#include "building_bandstand.h"

#include "building/building.h"
#include "building/count.h"
#include "city/object_info.h"
#include "city/labor.h"
#include "game/resource.h"
#include "grid/property.h"
#include "grid/image.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "widget/city/ornaments.h"
#include "building/building_entertainment.h"
#include "sound/sound_building.h"

buildings::model_t<building_bandstand> bandstand_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_bandstand_config);
void config_load_building_bandstand_config() {
    bandstand_m.load();
}

void building_bandstand::on_create(int orientation) {
    base.fire_proof = 1;
}

void building_bandstand::spawn_figure() {
    if (!is_main())
        return;

    if (common_spawn_figure_trigger(100)) {
        if (data.entertainment.days1 > 0) {
            create_roaming_figure(FIGURE_JUGGLER,
                                  FIGURE_ACTION_94_ENTERTAINER_ROAMING,
                                  BUILDING_SLOT_SERVICE);
        }

        if (data.entertainment.days2 > 0) {
            create_roaming_figure(FIGURE_MUSICIAN,
                                  FIGURE_ACTION_94_ENTERTAINER_ROAMING,
                                  BUILDING_SLOT_SERVICE);
        }
    }
}

void building_bandstand::window_info_background(object_info &c) {
    c.help_id = 72;

    window_building_play_sound(&c, snd::get_building_info_sound("bandstand"));
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(71, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    building* b = building_get(c.building_id);

    if (!c.has_road_access) {
        window_building_draw_description(c, 69, 25);
    } else if (b->num_workers <= 0) {
        window_building_draw_description(c, 71, 6);
    } else if (!b->data.entertainment.num_shows) {
        window_building_draw_description(c, 71, 2);
    } else if (b->data.entertainment.num_shows == 2) {
        window_building_draw_description(c, 71, 3);
    } else if (b->data.entertainment.days1) {
        window_building_draw_description(c, 71, 4);
    } else if (b->data.entertainment.days2) {
        window_building_draw_description(c, 71, 5);
    }

    inner_panel_draw(c.offset.x + 16, c.offset.y + 136, c.bgsize.x - 2, 7);
    window_building_draw_employment(&c, 138);
    if (b->data.entertainment.days1 > 0) {
        int width = lang_text_draw(71, 8, c.offset.x + 32, c.offset.y + 182, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw_amount(8, 44, 2 * b->data.entertainment.days1, c.offset.x + width + 32, c.offset.y + 182, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        lang_text_draw(71, 7, c.offset.x + 32, c.offset.y + 182, FONT_NORMAL_BLACK_ON_DARK);
    }

    if (b->data.entertainment.days2 > 0) {
        int width = lang_text_draw(71, 10, c.offset.x + 32, c.offset.y + 202, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw_amount(8, 44, 2 * b->data.entertainment.days2, c.offset.x + width + 32, c.offset.y + 202, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw(72, 7 + b->data.entertainment.days3_or_play, c.offset.x + 32, c.offset.y + 222, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        lang_text_draw(71, 9, c.offset.x + 32, c.offset.y + 202, FONT_NORMAL_BLACK_ON_DARK);
    }
}

void building_bandstand::draw_shows_musicians(painter &ctx, vec2i pixel, int direction, color color_mask) {
    building* main = base.main();
    if (main->data.entertainment.days2) {
        building* next_tile = base.next();
        switch (direction) {
        case 0:
        {
            const animation_t &anim = bandstand_m.anim["musician_sn"];
            building_draw_normal_anim(ctx, pixel, &base, tile(), anim, color_mask);
        }
        break;

        case 1:
        {
            const animation_t &anim = bandstand_m.anim["musician_we"];
            building_draw_normal_anim(ctx, pixel, &base, tile(), anim, color_mask);
        }
        break;
        }
    }
}

void building_bandstand::update_count() const {
    building_increase_type_count(type(), num_workers() > 0);
    building_increase_type_count(BUILDING_BOOTH, num_workers() > 0);
}

bool building_bandstand::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) {
    int color_mask = 0;
    if (drawing_building_as_deleted(&base) || map_property_is_deleted(tile)) {
        color_mask = COLOR_MASK_RED;
    }

    int grid_offset = tile.grid_offset();
    if (map_image_at(grid_offset) == image_group(IMG_BANDSTAND_SN_N)) {
        draw_shows_musicians(ctx, point, 1, color_mask);
    } else if (map_image_at(grid_offset) == image_group(IMG_BANDSTAND_WE_W)) {
        draw_shows_musicians(ctx, point, 0, color_mask);
    }

    if (map_image_at(grid_offset) == image_group(IMG_BOOTH)) {
        building_entertainment_draw_show_jugglers(ctx, &base, point, color_mask);
        const animation_t &anim = bandstand_m.anim["juggler"];

        building* main = base.main();
        if (main->data.entertainment.days1) {
            building_draw_normal_anim(ctx, point, &base, tile, anim, mask);
        }
    }

    return false;
}
