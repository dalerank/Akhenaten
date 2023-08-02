#include "figures.h"
#include <graphics/view/lookup.h>

#include "building/building.h"
#include "empire/city.h"
#include "figure/figure.h"
#include "figure/formation.h"
#include "figure/phrase.h"
#include "figure/trader.h"
#include "graphics/boilerplate.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "graphics/view/view.h"
#include "graphics/window.h"
#include "io/config/config.h"
#include "scenario/property.h"
#include "widget/city.h"

static void select_figure(int index, int param2);

static const int FIGURE_TYPE_TO_BIG_FIGURE_IMAGE[]
  = {8, 13, 13, 9, 4, 13, 8, 16, 7, 4, 18, 42, 26, 41, 8, 1, 33, 10, 11, 25, 8, 25, 15, 15, 15, 60, 12, 14, 5, 52, 52, 2, 3, 6, 6, 13, 8, 8, 17, 12, 58, 21, 50, 8, 8, 8, 28, 30, 23, 8, 8, 8, 34, 39, 33, 43, 27, 48, 63, 8, 8, 8, 8, 8, 53, 8, 38, 62, 54, 55, 56, 8, 8};

static generic_button figure_buttons[] = {
  {26, 46, 50, 50, select_figure, button_none, 0, 0},
  {86, 46, 50, 50, select_figure, button_none, 1, 0},
  {146, 46, 50, 50, select_figure, button_none, 2, 0},
  {206, 46, 50, 50, select_figure, button_none, 3, 0},
  {266, 46, 50, 50, select_figure, button_none, 4, 0},
  {326, 46, 50, 50, select_figure, button_none, 5, 0},
  {386, 46, 50, 50, select_figure, button_none, 6, 0},
};

static struct {
    int figure_images[7];
    int focus_button_id;
    building_info_context* context_for_callback;
} data;

static int big_people_image(int type) {
    int result = 0;
    if (GAME_ENV == ENGINE_ENV_C3) {
        result = image_id_from_group(GROUP_PORTRAITS) + FIGURE_TYPE_TO_BIG_FIGURE_IMAGE[type] - 1;
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        result = image_id_from_group(GROUP_PORTRAITS) + type;
    }
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

figure* figure::get_head_of_caravan() {
    figure* f = this;
    while (f->type == FIGURE_TRADE_CARAVAN_DONKEY) {
        f = figure_get(f->leading_figure_id);
    }
    return f;
}

static int name_group_id() { // TODO
    if (GAME_ENV == ENGINE_ENV_C3)
        return 65;
    else if (GAME_ENV == ENGINE_ENV_PHARAOH)
        return 254;
}

void figure::draw_trader(building_info_context* c) {
    figure* f = get_head_of_caravan();
    const empire_city* city = empire_city_get(f->empire_city_id);
    int width = lang_text_draw(64, f->type, c->x_offset + 40, c->y_offset + 110, FONT_NORMAL_BLACK_ON_DARK);
    lang_text_draw(21, city->name_id, c->x_offset + 40 + width, c->y_offset + 110, FONT_NORMAL_BLACK_ON_DARK);

    width = lang_text_draw(129, 1, c->x_offset + 40, c->y_offset + 132, FONT_NORMAL_BLACK_ON_DARK);
    lang_text_draw_amount(8,
                          10,
                          f->type == FIGURE_TRADE_SHIP ? 1200 : 800,
                          c->x_offset + 40 + width,
                          c->y_offset + 132,
                          FONT_NORMAL_BLACK_ON_DARK);

    int trader_id = f->trader_id;
    if (f->type == FIGURE_TRADE_SHIP) {
        int text_id;
        switch (f->action_state) {
        case FIGURE_ACTION_114_TRADE_SHIP_ANCHORED:
            text_id = 6;
            break;
        case FIGURE_ACTION_112_TRADE_SHIP_MOORED:
            text_id = 7;
            break;
        case FIGURE_ACTION_115_TRADE_SHIP_LEAVING:
            text_id = 8;
            break;
        default:
            text_id = 9;
            break;
        }
        lang_text_draw(129, text_id, c->x_offset + 40, c->y_offset + 154, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        int text_id;
        switch (f->action_state) {
        case FIGURE_ACTION_101_TRADE_CARAVAN_ARRIVING:
            text_id = 12;
            break;
        case FIGURE_ACTION_102_TRADE_CARAVAN_TRADING:
            text_id = 10;
            break;
        case FIGURE_ACTION_103_TRADE_CARAVAN_LEAVING:
            if (trader_has_traded(trader_id))
                text_id = 11;
            else
                text_id = 13;
            break;
        default:
            text_id = 11;
            break;
        }
        lang_text_draw(129, text_id, c->x_offset + 40, c->y_offset + 154, FONT_NORMAL_BLACK_ON_DARK);
    }
    if (trader_has_traded(trader_id)) {
        // bought
        int y_base = c->y_offset + 180;
        width = lang_text_draw(129, 4, c->x_offset + 40, y_base, FONT_NORMAL_BLACK_ON_DARK);
        for (int r = RESOURCE_MIN; r < RESOURCES_MAX; r++) {
            if (trader_bought_resources(trader_id, r)) {
                width += text_draw_number(trader_bought_resources(trader_id, r),
                                          '@',
                                          " ",
                                          c->x_offset + 40 + width,
                                          y_base,
                                          FONT_NORMAL_BLACK_ON_DARK);
                int image_id
                  = image_id_from_group(GROUP_RESOURCE_ICONS) + r + resource_image_offset(r, RESOURCE_IMAGE_ICON);
                ImageDraw::img_generic(image_id, c->x_offset + 40 + width, y_base - 3);
                width += 25;
            }
        }
        // sold
        y_base = c->y_offset + 210;
        width = lang_text_draw(129, 5, c->x_offset + 40, y_base, FONT_NORMAL_BLACK_ON_DARK);
        for (int r = RESOURCE_MIN; r < RESOURCES_MAX; r++) {
            if (trader_sold_resources(trader_id, r)) {
                width += text_draw_number(trader_sold_resources(trader_id, r),
                                          '@',
                                          " ",
                                          c->x_offset + 40 + width,
                                          y_base,
                                          FONT_NORMAL_BLACK_ON_DARK);
                int image_id
                  = image_id_from_group(GROUP_RESOURCE_ICONS) + r + resource_image_offset(r, RESOURCE_IMAGE_ICON);
                ImageDraw::img_generic(image_id, c->x_offset + 40 + width, y_base - 3);
                width += 25;
            }
        }
    } else { // nothing sold/bought (yet)
        // buying
        int y_base = c->y_offset + 180;
        width = lang_text_draw(129, 2, c->x_offset + 40, y_base, FONT_NORMAL_BLACK_ON_DARK);
        for (int r = RESOURCE_MIN; r < RESOURCES_MAX; r++) {
            if (city->buys_resource[r]) {
                int image_id
                  = image_id_from_group(GROUP_RESOURCE_ICONS) + r + resource_image_offset(r, RESOURCE_IMAGE_ICON);
                ImageDraw::img_generic(image_id, c->x_offset + 40 + width, y_base - 3);
                width += 25;
            }
        }
        // selling
        y_base = c->y_offset + 210;
        width = lang_text_draw(129, 3, c->x_offset + 40, y_base, FONT_NORMAL_BLACK_ON_DARK);
        for (int r = RESOURCE_MIN; r < RESOURCES_MAX; r++) {
            if (city->sells_resource[r]) {
                int image_id
                  = image_id_from_group(GROUP_RESOURCE_ICONS) + r + resource_image_offset(r, RESOURCE_IMAGE_ICON);
                ImageDraw::img_generic(image_id, c->x_offset + 40 + width, y_base - 3);
                width += 25;
            }
        }
    }
}
void figure::draw_enemy(building_info_context* c) {
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
    ImageDraw::img_generic(image_id_from_group(GROUP_PORTRAITS) + image_id - 1, c->x_offset + 28, c->y_offset + 112);

    lang_text_draw(name_group_id(), name, c->x_offset + 90, c->y_offset + 108, FONT_LARGE_BLACK_ON_DARK);
    lang_text_draw(37, scenario_property_enemy() + 20, c->x_offset + 92, c->y_offset + 149, FONT_NORMAL_BLACK_ON_DARK);
}
void figure::draw_animal(building_info_context* c) {
    ImageDraw::img_generic(big_people_image(type), c->x_offset + 28, c->y_offset + 112);
    lang_text_draw(64, type, c->x_offset + 92, c->y_offset + 139, FONT_NORMAL_BLACK_ON_DARK);
}
void figure::draw_cartpusher(building_info_context* c) {
    ImageDraw::img_generic(big_people_image(type), c->x_offset + 28, c->y_offset + 112);

    lang_text_draw(name_group_id(), name, c->x_offset + 90, c->y_offset + 108, FONT_LARGE_BLACK_ON_DARK);
    int width = 0;
    if (has_home())
        width += lang_text_draw(41, home()->type, c->x_offset + 92, c->y_offset + 139, FONT_NORMAL_BLACK_ON_DARK);
    width += lang_text_draw(64, type, c->x_offset + 92 + width, c->y_offset + 139, FONT_NORMAL_BLACK_ON_DARK);

    if (action_state != FIGURE_ACTION_132_DOCKER_IDLING && resource_id) {
        int resource = resource_id;
        ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_ICONS) + resource
                                 + resource_image_offset(resource, RESOURCE_IMAGE_ICON),
                               c->x_offset + 92,
                               c->y_offset + 154);

        width = text_draw_number(
          resource_amount_full, ' ', " ", c->x_offset + 108, c->y_offset + 154, FONT_NORMAL_BLACK_ON_DARK);
        width += lang_text_draw(129, 20, c->x_offset + 108 + width, c->y_offset + 154, FONT_NORMAL_BLACK_ON_DARK);
        width
          += lang_text_draw(23, resource_id, c->x_offset + 108 + width, c->y_offset + 154, FONT_NORMAL_BLACK_ON_DARK);
    }

    //    int phrase_height = lang_text_draw_multiline(130, 21 * c->figure.sound_id + c->figure.phrase_id + 1,
    //                                                 c->x_offset + 90, c->y_offset + 160, 16 * (c->width_blocks - 8),
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
    //        int x_base = c->x_offset + 40;
    //        int y_base = c->y_offset + 216;
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
void figure::draw_market_buyer(building_info_context* c) {
    ImageDraw::img_generic(big_people_image(type), c->x_offset + 28, c->y_offset + 112);

    lang_text_draw(name_group_id(), name, c->x_offset + 90, c->y_offset + 108, FONT_LARGE_BLACK_ON_DARK);
    int width = lang_text_draw(64, type, c->x_offset + 92, c->y_offset + 139, FONT_NORMAL_BLACK_ON_DARK);

    if (action_state == FIGURE_ACTION_145_MARKET_BUYER_GOING_TO_STORAGE) {
        width += lang_text_draw(129, 17, c->x_offset + 90 + width, c->y_offset + 139, FONT_NORMAL_BLACK_ON_DARK);
        int resource = inventory_to_resource_id(collecting_item_id);
        ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_ICONS) + resource
                                 + resource_image_offset(resource, RESOURCE_IMAGE_ICON),
                               c->x_offset + 90 + width,
                               c->y_offset + 135);
    } else if (action_state == FIGURE_ACTION_146_MARKET_BUYER_RETURNING) {
        width += lang_text_draw(129, 18, c->x_offset + 90 + width, c->y_offset + 139, FONT_NORMAL_BLACK_ON_DARK);
        int resource = inventory_to_resource_id(collecting_item_id);
        ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_ICONS) + resource
                                 + resource_image_offset(resource, RESOURCE_IMAGE_ICON),
                               c->x_offset + 90 + width,
                               c->y_offset + 135);
    }
    if (c->figure.phrase_id >= 0) {
        lang_text_draw_multiline(130,
                                 21 * c->figure.sound_id + c->figure.phrase_id + 1,
                                 c->x_offset + 90,
                                 c->y_offset + 160,
                                 16 * (c->width_blocks - 8),
                                 FONT_NORMAL_BLACK_ON_DARK);
    }
}
void figure::draw_normal_figure(building_info_context* c) {
    int image_id = big_people_image(type);
    if (action_state == FIGURE_ACTION_74_PREFECT_GOING_TO_FIRE || action_state == FIGURE_ACTION_75_PREFECT_AT_FIRE) {
        image_id = image_id_from_group(GROUP_PORTRAITS) + 18;
    }
    ImageDraw::img_generic(image_id, c->x_offset + 28, c->y_offset + 112);

    lang_text_draw(name_group_id(), name, c->x_offset + 90, c->y_offset + 108, FONT_LARGE_BLACK_ON_DARK);
    lang_text_draw(64, type, c->x_offset + 92, c->y_offset + 139, FONT_NORMAL_BLACK_ON_DARK);

    if (c->figure.phrase_id >= 0) {
        lang_text_draw_multiline(130,
                                 21 * c->figure.sound_id + c->figure.phrase_id + 1,
                                 c->x_offset + 90,
                                 c->y_offset + 160,
                                 16 * (c->width_blocks - 8),
                                 FONT_NORMAL_BLACK_ON_DARK);
    }
}

static void draw_figure_info(building_info_context* c, int figure_id) {
    button_border_draw(c->x_offset + 24, c->y_offset + 102, 16 * (c->width_blocks - 3), 138, 0);

    figure* f = figure_get(figure_id);
    int type = f->type;
    if (type == FIGURE_TRADE_CARAVAN || type == FIGURE_TRADE_CARAVAN_DONKEY || type == FIGURE_TRADE_SHIP)
        f->draw_trader(c);
    else if (type >= FIGURE_ENEMY43_SPEAR && type <= FIGURE_ENEMY53_AXE)
        f->draw_enemy(c);
    else if (type == FIGURE_FISHING_BOAT || type == FIGURE_SHIPWRECK || f->is_herd())
        f->draw_animal(c);
    else if (type == FIGURE_CART_PUSHER || type == FIGURE_WAREHOUSEMAN || type == FIGURE_DOCKER)
        f->draw_cartpusher(c);
    else if (type == FIGURE_MARKET_BUYER)
        f->draw_market_buyer(c);
    else
        f->draw_normal_figure(c);
}

void window_building_draw_figure_list(building_info_context* c) {
    inner_panel_draw(c->x_offset + 16, c->y_offset + 40, c->width_blocks - 2, 13);
    if (c->figure.count <= 0)
        lang_text_draw_centered(70, 0, c->x_offset, c->y_offset + 120, 16 * c->width_blocks, FONT_NORMAL_BLACK_ON_DARK);
    else {
        for (int i = 0; i < c->figure.count; i++) {
            button_border_draw(c->x_offset + 60 * i + 25, c->y_offset + 45, 52, 52, i == c->figure.selected_index);
            graphics_draw_from_texture(data.figure_images[i], c->x_offset + 27 + 60 * i, c->y_offset + 47, 48, 48);
            //            graphics_draw_from_buffer(c->x_offset + 27 + 60 * i, c->y_offset + 47, 48, 48,
            //            data.figure_images[i]);
        }
        draw_figure_info(c, c->figure.figure_ids[c->figure.selected_index]);
    }
    c->figure.drawn = 1;
}

static void draw_figure_in_city(int figure_id, pixel_coordinate* coord) {
    map_point camera_tile = city_view_get_camera_mappoint();

    int grid_offset = figure_get(figure_id)->tile.grid_offset();
    //    int x, y;
    //    screen_tile screen = mappoint_to_viewtile(map_point(grid_offset));

    //    city_view_go_to_tile(x - 2, y - 6);

    widget_city_draw_for_figure(figure_id, coord);

    //    city_view_go_to_tile(x_cam, y_cam);
}

void window_building_prepare_figure_list(building_info_context* c) {
    if (c->figure.count > 0) {
        pixel_coordinate coord = {0, 0};
        for (int i = 0; i < c->figure.count; i++) {
            draw_figure_in_city(c->figure.figure_ids[i], &coord);
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
        widget_city_draw();
    }
}

int window_building_handle_mouse_figure_list(const mouse* m, building_info_context* c) {
    data.context_for_callback = c;
    int button_id = generic_buttons_handle_mouse(
      m, c->x_offset, c->y_offset, figure_buttons, c->figure.count, &data.focus_button_id);
    data.context_for_callback = 0;
    return button_id;
}

static void select_figure(int index, int param2) {
    data.context_for_callback->figure.selected_index = index;
    window_building_play_figure_phrase(data.context_for_callback);
    window_invalidate();
}

void window_building_play_figure_phrase(building_info_context* c) {
    int figure_id = c->figure.figure_ids[c->figure.selected_index];
    figure* f = figure_get(figure_id);
    c->figure.sound_id = f->figure_phrase_play();
    c->figure.phrase_id = f->phrase_id;
}
