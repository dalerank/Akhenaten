#include "figures.h"
#include <graphics/view/lookup.h>

#include "building/building.h"
#include "empire/empire_city.h"
#include "figure/figure.h"
#include "figure/formation.h"
#include "figure/figure_phrase.h"
#include "figure/trader.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "graphics/view/view.h"
#include "graphics/window.h"
#include "config/config.h"
#include "scenario/property.h"
#include "widget/city.h"
#include "game/game.h"

static void window_info_select_figure(int index, int param2);

static const int FIGURE_TYPE_TO_BIG_FIGURE_IMAGE[]
  = {8,  13, 13, 9,  4,  13, 8,  16, 7,  4, 18, 42, 26, 41, 8,  1,  33, 10, 11, 25, 8,  25, 15, 15, 15,
     60, 12, 14, 5,  52, 52, 2,  3,  6,  6, 13, 8,  8,  17, 12, 58, 21, 50, 8,  8,  8,  28, 30, 23, 8,
     8,  8,  34, 39, 33, 43, 27, 48, 63, 8, 8,  8,  8,  8,  53, 8,  38, 62, 54, 55, 56, 8,  8};

static generic_button figure_buttons[] = {
  {26, 46, 50, 50, window_info_select_figure, button_none, 0, 0},
  {86, 46, 50, 50, window_info_select_figure, button_none, 1, 0},
  {146, 46, 50, 50, window_info_select_figure, button_none, 2, 0},
  {206, 46, 50, 50, window_info_select_figure, button_none, 3, 0},
  {266, 46, 50, 50, window_info_select_figure, button_none, 4, 0},
  {326, 46, 50, 50, window_info_select_figure, button_none, 5, 0},
  {386, 46, 50, 50, window_info_select_figure, button_none, 6, 0},
};

struct building_figures_data_t {
    int figure_images[7];
    int focus_button_id;
    object_info* context_for_callback;
};

building_figures_data_t g_building_figures_data;

static int big_people_image(e_figure_type type) {
    int result = 0;
    int index = type;
    result = image_id_from_group(GROUP_PORTRAITS) + type;
    return result;
}

static int inventory_to_resource_id(int value) {
    switch (value) {
    case 0:
        return RESOURCE_GRAIN;
    case 1:
        return RESOURCE_MEAT;
    case 2:
        return RESOURCE_LETTUCE;
    case 3:
        return RESOURCE_FIGS;
    case INVENTORY_GOOD4:
        return RESOURCE_BEER;
    case INVENTORY_GOOD3:
        return RESOURCE_MEAT;
    case INVENTORY_GOOD2:
        return RESOURCE_LUXURY_GOODS;
    case INVENTORY_GOOD1:
        return RESOURCE_POTTERY;
    default:
        return RESOURCE_NONE;
    }
}

static int name_group_id() { // TODO
    return 254;
}

void figure::draw_enemy(object_info* c) {
    painter ctx = game.painter();
    int image_id = FIGURE_TYPE_TO_BIG_FIGURE_IMAGE[type];
    int enemy_type = formation_get(formation_id)->enemy_type;
    switch (type) {
    case FIGURE_ENEMY43_SPEAR:
        switch (enemy_type) {
        case ENEMY_5_PERGAMUM:
            image_id = 44;
            break;
        case ENEMY_6_SELEUCID:
            image_id = 46;
            break;
        case ENEMY_7_ETRUSCAN:
            image_id = 32;
            break;
        case ENEMY_8_GREEK:
            image_id = 36;
            break;
        }
        break;
    case FIGURE_ENEMY44_SWORD:
        switch (enemy_type) {
        case ENEMY_5_PERGAMUM:
            image_id = 45;
            break;
        case ENEMY_6_SELEUCID:
            image_id = 47;
            break;
        case ENEMY_9_EGYPTIAN:
            image_id = 29;
            break;
        }
        break;
    case FIGURE_ENEMY45_SWORD:
        switch (enemy_type) {
        case ENEMY_7_ETRUSCAN:
            image_id = 31;
            break;
        case ENEMY_8_GREEK:
            image_id = 37;
            break;
        case ENEMY_10_CARTHAGINIAN:
            image_id = 22;
            break;
        }
        break;
    case FIGURE_ENEMY49_FAST_SWORD:
        switch (enemy_type) {
        case ENEMY_0_BARBARIAN:
            image_id = 21;
            break;
        case ENEMY_1_NUMIDIAN:
            image_id = 20;
            break;
        case ENEMY_4_GOTH:
            image_id = 35;
            break;
        }
        break;
    case FIGURE_ENEMY50_SWORD:
        switch (enemy_type) {
        case ENEMY_2_GAUL:
            image_id = 40;
            break;
        case ENEMY_3_CELT:
            image_id = 24;
            break;
        }
        break;
    case FIGURE_ENEMY51_SPEAR:
        switch (enemy_type) {
        case ENEMY_1_NUMIDIAN:
            image_id = 20;
            break;
        }
        break;
    }
    ImageDraw::img_generic(ctx, image_id_from_group(GROUP_PORTRAITS) + image_id - 1, c->offset + vec2i{28, 112});

    lang_text_draw(name_group_id(), name, c->offset.x + 90, c->offset.y + 108, FONT_LARGE_BLACK_ON_DARK);
    lang_text_draw(37, scenario_property_enemy() + 20, c->offset.x + 92, c->offset.y + 149, FONT_NORMAL_BLACK_ON_DARK);
}

void figure::draw_animal(object_info* c) {
    painter ctx = game.painter();
    ImageDraw::img_generic(ctx, big_people_image(type), c->offset + vec2i{28, 112});
    lang_text_draw(64, type, c->offset.x + 92, c->offset.y + 139, FONT_NORMAL_BLACK_ON_DARK);
}

void figure::draw_cartpusher(object_info* c) {
    painter ctx = game.painter();
    ImageDraw::img_generic(ctx, big_people_image(type), c->offset + vec2i{28, 112});

    lang_text_draw(name_group_id(), name, c->offset.x + 90, c->offset.y + 108, FONT_LARGE_BLACK_ON_DARK);
    int width = 0;
    if (has_home())
        width += lang_text_draw(41, home()->type, c->offset.x + 92, c->offset.y + 139, FONT_NORMAL_BLACK_ON_DARK);
    width += lang_text_draw(64, type, c->offset.x + 92 + width, c->offset.y + 139, FONT_NORMAL_BLACK_ON_DARK);

    if (action_state != FIGURE_ACTION_132_DOCKER_IDLING && resource_id) {
        int resource = resource_id;
        ImageDraw::img_generic(ctx, image_id_resource_icon(resource) + resource_image_offset(resource, RESOURCE_IMAGE_ICON), c->offset + vec2i{92, 154});

        width = text_draw_number(resource_amount_full, ' ', " ", c->offset.x + 108, c->offset.y + 154, FONT_NORMAL_BLACK_ON_DARK);
        width += lang_text_draw(129, 20, c->offset.x + 108 + width, c->offset.y + 154, FONT_NORMAL_BLACK_ON_DARK);
        width += lang_text_draw(23, resource_id, c->offset.x + 108 + width, c->offset.y + 154, FONT_NORMAL_BLACK_ON_DARK);
    }

    //    int phrase_height = lang_text_draw_multiline(130, 21 * c->figure.sound_id + c->figure.phrase_id + 1,
    //                                                 c->offset.x + 90, c->offset.y + 160, 16 * (c->width_blocks - 8),
    //                                                 FONT_NORMAL_GREEN);

    if (!has_home())
        return;
    building* source_building = home();
    building* target_building = destination();
    bool is_returning = false;
    switch (action_state) {
    case ACTION_11_RETURNING_EMPTY:
    case FIGURE_ACTION_27_CARTPUSHER_RETURNING:
    case FIGURE_ACTION_53_WAREHOUSEMAN_RETURNING_EMPTY:
    case FIGURE_ACTION_56_WAREHOUSEMAN_RETURNING_WITH_FOOD:
    case FIGURE_ACTION_59_WAREHOUSEMAN_RETURNING_WITH_RESOURCE:
    case FIGURE_ACTION_134_DOCKER_EXPORT_QUEUE:
    case FIGURE_ACTION_137_DOCKER_EXPORT_RETURNING:
    case FIGURE_ACTION_138_DOCKER_IMPORT_RETURNING:
        is_returning = true;
        break;
    }
    //    if (action_state != FIGURE_ACTION_132_DOCKER_IDLING) {
    //        int x_base = c->offset.x + 40;
    //        int y_base = c->offset.y + 216;
    //        if (phrase_height > 60)
    //            y_base += 8;
    //
    //        if (is_returning) {
    //            width = lang_text_draw(129, 16, x_base, y_base, FONT_NORMAL_GREEN);
    //            width += lang_text_draw(41, source_building->type, x_base + width, y_base, FONT_NORMAL_GREEN);
    //            width += lang_text_draw(129, 14, x_base + width, y_base, FONT_NORMAL_GREEN);
    //            lang_text_draw(41, target_building->type, x_base + width, y_base, FONT_NORMAL_GREEN);
    //        } else {
    //            width = lang_text_draw(129, 15, x_base, y_base, FONT_NORMAL_GREEN);
    //            width += lang_text_draw(41, target_building->type, x_base + width, y_base, FONT_NORMAL_GREEN);
    //            width += lang_text_draw(129, 14, x_base + width, y_base, FONT_NORMAL_GREEN);
    //            lang_text_draw(41, source_building->type, x_base + width, y_base, FONT_NORMAL_GREEN);
    //        }
    //    }
}

void figure::draw_market_buyer(object_info* c) {
    painter ctx = game.painter();
    ImageDraw::img_generic(ctx, big_people_image(type), c->offset + vec2i{28, 112});

    lang_text_draw(name_group_id(), name, c->offset.x + 90, c->offset.y + 108, FONT_LARGE_BLACK_ON_DARK);
    int width = lang_text_draw(64, type, c->offset.x + 92, c->offset.y + 139, FONT_NORMAL_BLACK_ON_DARK);

    if (action_state == FIGURE_ACTION_145_MARKET_BUYER_GOING_TO_STORAGE) {
        width += lang_text_draw(129, 17, c->offset.x + 90 + width, c->offset.y + 139, FONT_NORMAL_BLACK_ON_DARK);
        int resource = inventory_to_resource_id(collecting_item_id);
        ImageDraw::img_generic(ctx, image_id_resource_icon(resource) + resource_image_offset(resource, RESOURCE_IMAGE_ICON), c->offset + vec2i{90 + width, 135});
    } else if (action_state == FIGURE_ACTION_146_MARKET_BUYER_RETURNING) {
        width += lang_text_draw(129, 18, c->offset.x + 90 + width, c->offset.y + 139, FONT_NORMAL_BLACK_ON_DARK);
        int resource = inventory_to_resource_id(collecting_item_id);
        ImageDraw::img_generic(ctx, image_id_resource_icon(resource) + resource_image_offset(resource, RESOURCE_IMAGE_ICON), c->offset + vec2i{90 + width, 135});
    }

    if (c->figure.phrase_group > 0 && c->figure.phrase_id >= 0) {
        lang_text_draw_multiline(c->figure.phrase_group, c->figure.phrase_id, c->offset + vec2i{90, 160}, 16 * (c->width_blocks - 8), FONT_NORMAL_BLACK_ON_DARK);
    }
}

void figure::draw_normal_figure(object_info* c) {
    painter ctx = game.painter();
    int image_id = big_people_image(type);
    if (action_state == FIGURE_ACTION_74_FIREMAN_GOING_TO_FIRE || action_state == FIGURE_ACTION_75_FIREMAN_AT_FIRE) {
        image_id = image_id_from_group(GROUP_PORTRAITS) + 18;
    }

    ImageDraw::img_generic(ctx, image_id, c->offset + vec2i{28, 112});

    lang_text_draw(name_group_id(), name, c->offset.x + 90, c->offset.y + 108, FONT_LARGE_BLACK_ON_DARK);
    lang_text_draw(64, type, c->offset.x + 92, c->offset.y + 139, FONT_NORMAL_BLACK_ON_DARK);

    if (c->figure.phrase_group > 0 && c->figure.phrase_id >= 0) {
        lang_text_draw_multiline(c->figure.phrase_group, c->figure.phrase_id, c->offset + vec2i{90, 160}, 16 * (c->width_blocks - 8), FONT_NORMAL_BLACK_ON_DARK);
    }
}

static void draw_figure_info(object_info* c, int figure_id) {
    button_border_draw(c->offset.x + 24, c->offset.y + 102, 16 * (c->width_blocks - 3), 138, 0);

    figure* f = figure_get(figure_id);
    int type = f->type;
    bool custom_window = f->dcast()->window_info_background(*c);
    if (custom_window) {
        return;
    }

    if (type == FIGURE_TRADE_SHIP) {
        //f->draw_trader(c); //TODO: need fixes
    } else if (type >= FIGURE_ENEMY43_SPEAR && type <= FIGURE_ENEMY53_AXE)
        f->draw_enemy(c);
    else if (type == FIGURE_FISHING_BOAT || type == FIGURE_SHIPWRECK || f->is_herd())
        f->draw_animal(c);
    else if (type == FIGURE_CART_PUSHER || type == FIGURE_STORAGEYARD_CART || type == FIGURE_DOCKER)
        f->draw_cartpusher(c);
    else if (type == FIGURE_MARKET_BUYER)
        f->draw_market_buyer(c);
    else
        f->draw_normal_figure(c);
}

void window_building_draw_figure_list(object_info* c) {
    inner_panel_draw(c->offset.x + 16, c->offset.y + 40, c->width_blocks - 2, 13);
    if (c->figure.count <= 0) {
        lang_text_draw_centered(70, 0, c->offset.x, c->offset.y + 120, 16 * c->width_blocks, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        for (int i = 0; i < c->figure.count; i++) {
            button_border_draw(c->offset.x + 60 * i + 25, c->offset.y + 45, 52, 52, i == c->figure.selected_index);
            graphics_draw_from_texture(g_building_figures_data.figure_images[i], c->offset.x + 27 + 60 * i, c->offset.y + 47, 48, 48);
            //            graphics_draw_from_buffer(c->offset.x + 27 + 60 * i, c->offset.y + 47, 48, 48,
            //            data.figure_images[i]);
        }
        draw_figure_info(c, c->figure.figure_ids[c->figure.selected_index]);
    }
    c->figure.drawn = 1;
}

static void draw_figure_in_city(int figure_id, vec2i* coord, painter &ctx) {
    map_point camera_tile = city_view_get_camera_mappoint();

    int grid_offset = figure_get(figure_id)->tile.grid_offset();
    //    int x, y;
    //    screen_tile screen = mappoint_to_viewtile(map_point(grid_offset));

    //    city_view_go_to_tile(x - 2, y - 6);

    widget_city_draw_for_figure(ctx, figure_id, coord);

    //    city_view_go_to_tile(x_cam, y_cam);
}

void window_building_prepare_figure_list(object_info* c) {
    auto &data = g_building_figures_data;
    painter ctx = game.painter();
    if (c->figure.count > 0) {
        vec2i coord = {0, 0};
        for (int i = 0; i < c->figure.count; i++) {
            draw_figure_in_city(c->figure.figure_ids[i], &coord, ctx);
            data.figure_images[i] = graphics_save_to_texture(data.figure_images[i], coord.x, coord.y, 48, 48);
        }
        //        if (config_get(CONFIG_UI_ZOOM))
        //            graphics_set_active_canvas(CANVAS_CITY);
        //
        //        for (int i = 0; i < c->figure.count; i++) {
        //            draw_figure_in_city(c->figure.figure_ids[i], &coord);
        //            graphics_save_to_buffer(coord.x - 25, coord.y - 45, 48, 48, data.figure_images[i]);
        //        }
        //        graphics_set_active_canvas(CANVAS_UI);
        widget_city_draw(ctx);
    }
}

int window_building_handle_mouse_figure_list(const mouse* m, object_info* c) {
    auto& data = g_building_figures_data;
    data.context_for_callback = c;
    int button_id = generic_buttons_handle_mouse(m, c->offset.x, c->offset.y, figure_buttons, c->figure.count, &data.focus_button_id);
    data.context_for_callback = 0;
    return button_id;
}

static void window_info_select_figure(int index, int param2) {
    auto& data = g_building_figures_data;
    data.context_for_callback->figure.selected_index = index;
    window_building_play_figure_phrase(data.context_for_callback);
    window_invalidate();
}

static int window_info_show_overlay(figure *f) {
    switch (f->type) {
    case FIGURE_CONSTABLE: return OVERLAY_CRIME;
    case FIGURE_MAGISTRATE: return OVERLAY_COUTHOUSE;
    default:
        return f->dcast()->get_overlay();
    }

    return OVERLAY_NONE;
}

void window_building_play_figure_phrase(object_info* c) {
    int figure_id = c->figure.figure_ids[c->figure.selected_index];
    figure* f = figure_get(figure_id);
    f->figure_phrase_play();
    c->show_overlay = window_info_show_overlay(f);
    c->figure.phrase_group = f->phrase_group;
    c->figure.phrase_id = f->phrase_id;
    c->figure.phrase_key = f->phrase_key;
}
