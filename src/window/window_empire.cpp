#include "window_empire.h"

#include "city/military.h"
#include "city/warning.h"
#include "city/constants.h"
#include "city/finance.h"
#include "core/game_environment.h"
#include "empire/empire.h"
#include "empire/empire_city.h"
#include "empire/empire_map.h"
#include "empire/empire_object.h"
#include "empire/trade_route.h"
#include "empire/type.h"
#include "game/settings.h"
#include "game/tutorial.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/image_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/image_groups.h"
#include "graphics/screen.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "input/scroll.h"
#include "scenario/empire.h"
#include "scenario/invasion.h"
#include "scenario/scenario.h"
#include "window/advisors.h"
#include "window/window_city.h"
#include "window/message_dialog.h"
#include "window/popup_dialog.h"
#include "window/resource_settings.h"
#include "window/autoconfig_window.h"
#include "window/trade_opened.h"
#include "game/game.h"

#include "js/js_game.h"

int img_mapping[32000] = {0};
ANK_REGISTER_CONFIG_ITERATOR(config_load_images_remap_config);
void config_load_images_remap_config() {
    g_config_arch.r_array("empire_images_remap", [] (archive arch) {
        int id = arch.r_int("id");
        int remap = arch.r_int("rid");
        img_mapping[id] = remap;
    });
}

int image_id_remap(int id) {
    int rimg = img_mapping[id];
    return rimg ? rimg : id;
}

const static vec2i EMPIRE_SIZE{1200 + 32,  1600 + 136 + 20};
const static e_font FONT_OBJECT_INFO = FONT_NORMAL_BLACK_ON_LIGHT;

static void button_show_resource_window(int resource, int param2);


static int ADVISOR_BUTTON_X = 0;

static generic_button generic_button_trade_resource[] = {
  // NONE
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_GRAIN, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_MEAT, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_LETTUCE, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_CHICKPEAS, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_POMEGRANATES, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_FIGS, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_FISH, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_GAMEMEAT, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_STRAW, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_WEAPONS, 0},
  //
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_CLAY, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_BRICKS, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_POTTERY, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_BARLEY, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_BEER, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_FLAX, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_LINEN, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_GEMS, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_LUXURY_GOODS, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_TIMBER, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_GOLD, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_REEDS, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_PAPYRUS, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_STONE, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_LIMESTONE, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_GRANITE, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_UNUSED12, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_CHARIOTS, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_COPPER, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_SANDSTONE, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_OIL, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_HENNA, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_PAINT, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_LAMPS, 0},
  {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_MARBLE, 0},
  //        {0, 0, 101, 22, button_show_resource_window, button_none, RESOURCE_UNUSED16, 0},
};

struct object_trade_info {
    rect r;
    e_resource res;
};

struct empire_window : public autoconfig_window_t<empire_window> {
    int selected_button = 0;
    int selected_city = 1;
    vec2i min_pos, max_pos;
    vec2i draw_offset;
    int focus_button_id;
    int is_scrolling;
    int finished_scroll;
    int focus_resource;
    int trade_column_spacing;
    int trade_row_spacing;
    int info_y_traded;
    int trade_button_offset_x;
    int info_y_sells;
    int info_y_buys;
    int info_y_footer_1;
    int info_y_city_desc;
    int text_group_old_names;
    int text_group_new_names;
    int trade_resource_size;
    int trade_resource_offset;
    int sell_res_group;
    int trade_button_offset_y;
    vec2i start_pos, finish_pos;
    image_desc image, bottom_image, horizontal_bar, vertical_bar, cross_bar;
    svector<object_trade_info, 16> buying_goods;
    svector<object_trade_info, 16> selling_goods;

    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void draw_foreground() override {}
    virtual int draw_background() override;
    virtual void ui_draw_foreground() override;
    virtual int ui_handle_mouse(const mouse *m) override;
    virtual void init() override;

    virtual void load(archive arch, pcstr section) override {
        autoconfig_window::load(arch, section);
    
        trade_column_spacing = arch.r_int("trade_column_spacing");
        trade_row_spacing = arch.r_int("trade_row_spacing");
        info_y_traded = arch.r_int("info_y_traded");
        trade_button_offset_x = arch.r_int("trade_button_offset_x");
        info_y_sells = arch.r_int("info_y_sells");
        info_y_buys = arch.r_int("info_y_buys");
        info_y_footer_1 = arch.r_int("info_y_footer_1");
        info_y_city_desc = arch.r_int("info_y_city_desc");
        text_group_old_names = arch.r_int("text_group_old_names");
        text_group_new_names = arch.r_int("text_group_new_names");
        trade_resource_size = arch.r_int("trade_resource_size");
        trade_resource_offset = arch.r_int("trade_resource_offset");
        sell_res_group = arch.r_int("sell_res_group");
        trade_button_offset_y = arch.r_int("trade_button_offset_y");
        start_pos = arch.r_vec2i("start_pos");
        finish_pos = arch.r_vec2i("finish_pos");
        arch.r_desc("image", image);
        arch.r_desc("bottom_image", bottom_image);
        arch.r_desc("horizontal_bar", horizontal_bar);
        arch.r_desc("vertical_bar", vertical_bar);
        arch.r_desc("cross_bar", cross_bar);
    }

    void draw_map();
    void draw_empire_object(const empire_object *obj);
    void draw_paneling();
    void draw_object_info();
    bool is_outside_map(int x, int y);
    void determine_selected_object(const mouse *m);
};

empire_window g_empire_window;

void empire_window::init() {
    selected_button = 0;
    int selected_object = g_empire_map.selected_object();
    selected_city = selected_object ? g_empire.get_city_for_object(selected_object - 1) : 0;
    focus_button_id = 0;
}

static void draw_trade_route(int route_id, e_empire_route_state effect) {
    auto &data = g_empire_window;
    painter ctx = game.painter();

    map_route_object* obj = empire_get_route_object(route_id);
    if (!obj->in_use) {
        return;
    }

    // get graphics ready..
    int image_id = 0;
    switch (effect) {
    case ROUTE_CLOSED: // closed
        return;
        //image_id = image_id_from_group(GROUP_MINIMAP_BUILDING) + 211;
        break;
    case ROUTE_CLOSED_SELECTED: // highlighted, closed
        image_id = image_group(IMG_EMPIRE_ROUTE_HL_CLOSED);
        break;
    case ROUTE_OPEN: // open
        image_id = image_group(IMG_EMPIRE_ROUTE_OPEN);
        break;
    case ROUTE_OPEN_SELECTED: // highlighted, open
        image_id = image_group(IMG_EMPIRE_ROUTE_HL_OPEN);
        break;
    }

    for (int i = 0; i < obj->num_points; i++) {
        const auto &route_point = obj->points[i];

        // first corner in pair
        ImageDraw::img_generic(ctx, image_id, data.draw_offset + route_point.p);

        // draw lines connecting the turns
        if (i < obj->num_points - 1) {
            auto nextup_route_point = obj->points[i + 1];
            vec2i d = nextup_route_point.p - route_point.p;
            float len = 0.2f * sqrtf(float(d.x * d.x) + float(d.y * d.y));

            float scaled_x = (float)d.x / len;
            float scaled_y = (float)d.y / len;

            float progress = 1.0;
            while (progress < len) {
                vec2i disp = data.draw_offset + route_point.p + vec2i{(int)(scaled_x * progress), (int)(scaled_y * progress)};
                ImageDraw::img_generic(ctx, image_id, disp);
                progress += 1.0f;
            }
        }
    }
}

static int column_idx(int index) {
    return index % 2;
}

static int row_idx(int index) {
    return index / 2;
}

static void draw_trade_resource(e_resource resource, int trade_max, vec2i offset, int mode) {
    auto &data = g_empire_window;
    painter ctx = game.painter();
    graphics_draw_inset_rect(offset, vec2i{data.trade_resource_size, data.trade_resource_size});
    int img_id = image_id_resource_icon(resource);
    ImageDraw::img_generic(ctx, img_id, offset + vec2i{1, 1});

    const image_t* img = image_get(img_id);
    if (mode) {
        data.selling_goods.push_back({{offset, offset + vec2i{img->width, img->height}}, resource});
    } else {
        data.buying_goods.push_back({{offset, offset + vec2i{img->width, img->height}}, resource});
    }

    if (data.focus_resource == resource) {
        button_border_draw(offset.x - 2, offset.y - 2, 101 + 4, 24, 1);
    }

    switch (trade_max) {
    case 1500:
    case 15:
        ImageDraw::img_generic(ctx, image_group(IMG_TRADE_AMOUNT), offset + vec2i{21, -1});
        break;

    case 2500:
    case 25:
        ImageDraw::img_generic(ctx, image_group(IMG_TRADE_AMOUNT) + 1, offset + vec2i{17, -1});
        break;

    case 4000:
    case 40:
        ImageDraw::img_generic(ctx, image_group(IMG_TRADE_AMOUNT) + 2, offset + vec2i{13, -1});
        break;
    }
}

static void draw_trade_city_info(const empire_object* object, const empire_city* city) {
    auto &data = g_empire_window;
    int x_offset = (data.min_pos.x + data.max_pos.x - 500) / 2;
    int y_offset = data.max_pos.y - 113;

    data.buying_goods.clear();
    data.selling_goods.clear();

    if (city->is_open) {
        e_font traded_font = FONT_SMALL_PLAIN;

        // city sells
        lang_text_draw(data.sell_res_group, 11, x_offset + 44, y_offset + data.info_y_traded - 2, FONT_OBJECT_INFO);
        int index = 0;
        for (e_resource resource = RESOURCE_MIN; resource < RESOURCES_MAX; ++resource) {
            if (!empire_object_city_sells_resource(object->id, resource))
                continue;

            int column_offset = data.trade_column_spacing * column_idx(index) - 150;
            int row_offset = data.trade_row_spacing * row_idx(index) + 20;

            const auto &trade_route = city->get_route();
            int trade_max = trade_route.limit(resource);
            draw_trade_resource(resource, trade_max, vec2i{x_offset + column_offset + 125, y_offset + data.info_y_traded + row_offset - 5}, 1);
            int trade_now = trade_route.traded(resource);

            if (trade_now > trade_max)
                trade_max = trade_now;
            
            trade_now = stack_proper_quantity(trade_now, resource);
            trade_max = stack_proper_quantity(trade_max, resource);

            int text_width = text_draw_number(trade_now, '@', "", x_offset + column_offset + 150, y_offset + data.info_y_traded + row_offset, traded_font);
            text_width += lang_text_draw(data.sell_res_group, 12, x_offset + column_offset + 148 + text_width, y_offset + data.info_y_traded + row_offset, traded_font);
            text_draw_number(trade_max, '@', "", x_offset + column_offset + 138 + text_width, y_offset + data.info_y_traded + row_offset,traded_font);
            index++;
        }
        // city buys
        lang_text_draw(data.sell_res_group, 10, x_offset + 44 + 350, y_offset + data.info_y_traded - 2, FONT_OBJECT_INFO);
        index = 0;

        for (e_resource resource = RESOURCE_MIN; resource < RESOURCES_MAX; ++resource) {
            if (!empire_object_city_buys_resource(object->id, resource))
                continue;

            int column_offset = data.trade_column_spacing * column_idx(index) + 200;
            int row_offset = data.trade_row_spacing * row_idx(index) + 20;

            const auto &trade_route = city->get_route();
            int trade_max = trade_route.limit(resource);
            draw_trade_resource(resource, trade_max, vec2i{x_offset + column_offset + 125, y_offset + data.info_y_traded + row_offset - 5}, 0);
            int trade_now = trade_route.traded(resource);

            if (trade_now > trade_max)
                trade_max = trade_now;
            
            trade_now = stack_proper_quantity(trade_now, resource);
            trade_max = stack_proper_quantity(trade_max, resource);

            int text_width = text_draw_number(trade_now, '@', "", x_offset + column_offset + 150, y_offset + data.info_y_traded + row_offset, traded_font);
            text_width += lang_text_draw(data.sell_res_group, 12, x_offset + column_offset + 148 + text_width, y_offset + data.info_y_traded + row_offset, traded_font);
            text_draw_number(trade_max, '@', "", x_offset + column_offset + 138 + text_width, y_offset + data.info_y_traded + row_offset, traded_font);
            index++;
        }
    } else { // trade is closed

        // selling
        int spacing = 0;
        lang_text_draw(data.sell_res_group, 5, x_offset + 30, y_offset + data.info_y_sells, FONT_OBJECT_INFO);
        const auto &trade_route = city->get_route();
        for (const auto &r: resource_list::all) {
            if (!empire_object_city_sells_resource(object->id, r.type))
                continue;

            int trade_max = trade_route.limit(r.type);
            trade_max = stack_proper_quantity(trade_max, r.type);
            draw_trade_resource(r.type, trade_max, vec2i{x_offset + spacing + 80, y_offset + data.info_y_sells - data.trade_resource_offset}, 1);
            spacing += 32;
        }

        // buying
        spacing = 0;
        lang_text_draw(data.sell_res_group, 4, x_offset + 30, y_offset + data.info_y_buys, FONT_OBJECT_INFO);
        for (const auto &r: resource_list::all) {
            if (!empire_object_city_buys_resource(object->id, r.type))
                continue;

            int trade_max = trade_route.limit(r.type);
            trade_max = stack_proper_quantity(trade_max, r.type);
            draw_trade_resource(r.type, trade_max, vec2i{x_offset + spacing + 80,y_offset + data.info_y_buys - data.trade_resource_offset}, 0);
            spacing += 32;
        }

        // trade open button
        spacing = lang_text_draw_amount(8, 0, city->cost_to_open, x_offset + 40, y_offset + data.info_y_footer_1, FONT_OBJECT_INFO);
        lang_text_draw(data.sell_res_group, 6 + city->is_sea_trade, x_offset + spacing + 40, y_offset + data.info_y_footer_1, FONT_OBJECT_INFO);
        int image_id = image_id_from_group(GROUP_EMPIRE_TRADE_ROUTE_TYPE) + 1 - city->is_sea_trade;
    }
}

static void draw_city_info(const empire_object* object) {
    auto &data = g_empire_window;
    int x_offset = (data.min_pos.x + data.max_pos.x - 240) / 2;
    int y_offset = data.max_pos.y - 88;

    const empire_city* city = g_empire.city(data.selected_city);

    switch (city->type) {
    case EMPIRE_CITY_OURS:
        lang_text_draw_centered(data.sell_res_group, 1, x_offset, y_offset + data.info_y_city_desc, 240, FONT_NORMAL_BLACK_ON_LIGHT);
        break;

    case EMPIRE_CITY_PHARAOH:
        lang_text_draw_centered(data.sell_res_group, 19, x_offset, y_offset + data.info_y_city_desc, 240, FONT_NORMAL_BLACK_ON_LIGHT);
        break;

    case EMPIRE_CITY_EGYPTIAN:
        lang_text_draw_centered(data.sell_res_group, 13, x_offset, y_offset + data.info_y_city_desc, 240, FONT_NORMAL_BLACK_ON_LIGHT);
        break;

    case EMPIRE_CITY_FOREIGN:
        lang_text_draw_centered(data.sell_res_group, 0, x_offset, y_offset + data.info_y_city_desc, 240, FONT_NORMAL_BLACK_ON_LIGHT);
        break;

    case EMPIRE_CITY_PHARAOH_TRADING:
    case EMPIRE_CITY_EGYPTIAN_TRADING:
    case EMPIRE_CITY_FOREIGN_TRADING:
        draw_trade_city_info(object, city);
        break;
    }
}

static void draw_kingdome_army_info(const empire_object* object) {
    auto &data = g_empire_window;
    if (city_military_distant_battle_kingdome_army_is_traveling()) {
        if (city_military_distant_battle_kingdome_months_traveled() == object->distant_battle_travel_months) {
            vec2i offset{(data.min_pos.x + data.max_pos.x - 240) / 2, data.max_pos.y - 68};
            int text_id;
            if (city_military_distant_battle_kingdome_army_is_traveling_forth())
                text_id = 15;
            else {
                text_id = 16;
            }
            lang_text_draw_multiline(data.sell_res_group, text_id, offset, 240, FONT_OBJECT_INFO);
        }
    }
}

static void draw_enemy_army_info(const empire_object* object) {
    auto &data = g_empire_window;
    if (city_military_months_until_distant_battle() > 0) {
        if (city_military_distant_battle_enemy_months_traveled() == object->distant_battle_travel_months) {
            lang_text_draw_multiline(data.sell_res_group, 14, vec2i{(data.min_pos.x + data.max_pos.x - 240) / 2, data.max_pos.y - 68}, 240, FONT_OBJECT_INFO);
        }
    }
}

void empire_window::draw_object_info() {
    int selected_object = g_empire_map.selected_object();
    if (selected_object) {
        const empire_object* object = empire_object_get(selected_object - 1);
        switch (object->type) {
        case EMPIRE_OBJECT_CITY:
            draw_city_info(object);
            break;

        case EMPIRE_OBJECT_KINGDOME_ARMY:
            draw_kingdome_army_info(object);
            break;

        case EMPIRE_OBJECT_ENEMY_ARMY:
            draw_enemy_army_info(object);
            break;
        }
    } else {
        lang_text_draw_centered(sell_res_group, 9, min_pos.x, max_pos.y - 68, max_pos.x - min_pos.x, FONT_OBJECT_INFO);
    }
}

void empire_window::determine_selected_object(const mouse *m) {
    if (!m->left.went_up || finished_scroll || is_outside_map(m->x, m->y)) {
        finished_scroll = 0;
        return;
    }
    g_empire_map.select_object(vec2i{ m->x, m->y } - min_pos - vec2i{ 16, 16 });
    window_invalidate();
}

bool empire_window::is_outside_map(int x, int y) {
    return (x < min_pos.x + 16 || x >= max_pos.x - 16 || y < min_pos.y + 16 || y >= max_pos.y - 120);
}

int empire_window::ui_handle_mouse(const mouse *m) {
    const hotkeys *h = hotkey_state();

    vec2i position;
    if (scroll_get_delta(m, &position, SCROLL_TYPE_EMPIRE)) {
        g_empire_map.scroll_map(position);
    }

    if (m->is_touch) {
        const touch *t = get_earliest_touch();
        if (!is_outside_map(t->current_point.x, t->current_point.y)) {
            if (t->has_started) {
                is_scrolling = 1;
                scroll_drag_start(1);
            }
        }

        if (t->has_ended) {
            is_scrolling = 0;
            finished_scroll = !touch_was_click(t);
            scroll_drag_end();
        }
    }

    focus_button_id = 0;
    focus_resource = 0;
    int button_id;

    determine_selected_object(m);
    int selected_object = g_empire_map.selected_object();
    if (selected_object) {
        const empire_object *obj = empire_object_get(selected_object - 1);
        if (obj->type == EMPIRE_OBJECT_CITY) {
            selected_city = g_empire.get_city_for_object(selected_object - 1);
            const empire_city *city = g_empire.city(selected_city);

            if ((city->type == EMPIRE_CITY_PHARAOH_TRADING || city->type == EMPIRE_CITY_EGYPTIAN_TRADING || city->type == EMPIRE_CITY_FOREIGN_TRADING)) {
                if (city->is_open) {
                    int x_offset = (min_pos.x + max_pos.x - 500) / 2;
                    int y_offset = max_pos.y - 113;
                    int index_sell = 0;
                    int index_buy = 0;

                    // we only want to handle resource buttons that the selected city trades
                    for (e_resource resource = RESOURCE_MIN; resource < RESOURCES_MAX; ++resource) {
                        if (empire_object_city_sells_resource(obj->id, resource)) {
                            int column_offset = trade_column_spacing * column_idx(index_sell) - 150;
                            int row_offset = trade_row_spacing * row_idx(index_sell) + 20;
                            generic_buttons_handle_mouse(m, { x_offset + column_offset + 125, y_offset + info_y_traded + row_offset - 7 }, generic_button_trade_resource + resource - 1, 1, &button_id);
                            index_sell++;
                        } else if (empire_object_city_buys_resource(obj->id, resource)) {
                            int column_offset = trade_column_spacing * column_idx(index_buy) + 200;
                            int row_offset = trade_row_spacing * row_idx(index_buy) + 20;
                            generic_buttons_handle_mouse(m, { x_offset + column_offset + 125, y_offset + info_y_traded + row_offset - 7 }, generic_button_trade_resource + resource - 1, 1, &button_id);
                            index_buy++;
                        }

                        if (button_id) {
                            focus_resource = resource;
                            // if we're focusing any button we can skip further checks
                            break;
                        }
                    }
                }
            }
        }

        if (input_go_back_requested(m, h)) {
            g_empire_map.clear_selected_object();
            window_invalidate();
            return 0;
        }
    } else if (input_go_back_requested(m, h)) {
        window_city_show();
        return 0;
    }

    ui.begin_widget({ 0, 0 });
    ui.handle_mouse(m);
    ui.end_widget();

    return 0;
}

void empire_window::draw_empire_object(const empire_object* obj) {
    auto &data = g_empire_window;
    if (obj->type == EMPIRE_OBJECT_LAND_TRADE_ROUTE || obj->type == EMPIRE_OBJECT_SEA_TRADE_ROUTE) {
        if (!g_empire.is_trade_route_open(obj->trade_route_id)) {
            return;
        }
    }

    vec2i pos;
    int image_id;
    if (scenario_empire_is_expanded()) {
        pos = obj->expanded.pos;
        image_id = obj->expanded.image_id;
    } else {
        pos = obj->pos;
        image_id = obj->image_id;
    }

    if (obj->type == EMPIRE_OBJECT_CITY) {
        int empire_city_id = g_empire.get_city_for_object(obj->id);
        const empire_city* city = g_empire.city(empire_city_id);

        // draw routes!
        if (city->type == EMPIRE_CITY_EGYPTIAN_TRADING || city->type == EMPIRE_CITY_FOREIGN_TRADING || city->type == EMPIRE_CITY_PHARAOH_TRADING) {
            e_empire_route_state state = ROUTE_CLOSED;
            if (city->is_open) {
                state = (g_empire_map.selected_object() && data.selected_city == g_empire.get_city_for_object(obj->id))
                              ? ROUTE_OPEN_SELECTED 
                              : ROUTE_OPEN;
            } else {
                state = (g_empire_map.selected_object() && data.selected_city == g_empire.get_city_for_object(obj->id))
                              ? ROUTE_CLOSED_SELECTED
                              : ROUTE_CLOSED;
            }
            draw_trade_route(city->route_id, state);
        }

        int text_group = (g_settings.city_names_style == CITIES_OLD_NAMES) 
                              ? data.text_group_old_names
                              : data.text_group_new_names;

        int letter_height = get_letter_height((const uint8_t*)"H", FONT_SMALL_PLAIN);
        vec2i text_pos = data.draw_offset + pos + vec2i{0, -letter_height};

        switch (obj->text_align) {
        case 0:
            lang_text_draw_centered_colored(text_group, city->name_id, text_pos.x, text_pos.y, obj->width, FONT_SMALL_PLAIN, COLOR_FONT_DARK_RED);
            break;

        case 1:
            lang_text_draw_centered_colored(text_group, city->name_id, text_pos.x, text_pos.y, obj->width, FONT_SMALL_PLAIN, COLOR_FONT_DARK_RED);
            break;

        case 2:
            lang_text_draw_centered_colored(text_group, city->name_id, text_pos.x, text_pos.y, obj->width, FONT_SMALL_PLAIN, COLOR_FONT_DARK_RED);
            break;

        case 3:
            lang_text_draw_centered_colored(text_group, city->name_id, text_pos.x, text_pos.y, obj->width, FONT_SMALL_PLAIN, COLOR_FONT_DARK_RED);
            break;
        }
    } else if (obj->type == EMPIRE_OBJECT_TEXT) {
        const full_empire_object* full = empire_get_full_object(obj->id);
        vec2i text_pos = data.draw_offset + pos;

        lang_text_draw_centered_colored(196, full->city_name_id, text_pos.x - 5, text_pos.y, 100, FONT_SMALL_PLAIN, COLOR_FONT_SHITTY_BROWN);
        return;
    }

    if (obj->type == EMPIRE_OBJECT_BATTLE_ICON) {
        // handled later
        return;
    }

    if (obj->type == EMPIRE_OBJECT_ENEMY_ARMY) {
        if (city_military_months_until_distant_battle() <= 0)
            return;
        if (city_military_distant_battle_enemy_months_traveled() != obj->distant_battle_travel_months)
            return;
    }
    
    if (obj->type == EMPIRE_OBJECT_KINGDOME_ARMY) {
        if (!city_military_distant_battle_kingdome_army_is_traveling())
            return;
        if (city_military_distant_battle_kingdome_months_traveled() != obj->distant_battle_travel_months)
            return;
    }

    painter ctx = game.painter();
    image_id = image_id_remap(image_id);
    const image_t* img = image_get(PACK_GENERAL, image_id);
    ImageDraw::img_generic(ctx, PACK_GENERAL, image_id, data.draw_offset + pos);

    if (img && img->animation.speed_id) {
        int new_animation = empire_object_update_animation(obj, image_id);
        ImageDraw::img_generic(ctx, PACK_GENERAL, image_id + new_animation, data.draw_offset + pos + img->animation.sprite_offset);
    }
}

void empire_window::draw_map() {
    painter ctx = game.painter();

    graphics_set_clip_rectangle(min_pos + start_pos, vec2i{max_pos - min_pos} - finish_pos);

    g_empire_map.set_viewport(max_pos - min_pos - finish_pos);

    draw_offset = min_pos + start_pos;
    draw_offset = g_empire_map.adjust_scroll(draw_offset);

    ImageDraw::img_generic(ctx, image_group(image), draw_offset);

    empire_object_foreach([this] (const empire_object *obj) {
        draw_empire_object(obj);
    });

    scenario_invasion_foreach_warning([&] (vec2i pos, int image_id) {
        ImageDraw::img_generic(ctx, image_id, draw_offset + pos);
    });

    graphics_reset_clip_rectangle();
}

void empire_window::draw_paneling() {
    painter ctx = game.painter();
    // bottom panel background
    graphics_set_clip_rectangle(min_pos, max_pos - min_pos);

    for (int x = min_pos.x; x < max_pos.x; x += 70) {
        ImageDraw::img_generic(ctx, bottom_image, vec2i{x, max_pos.y - 140});
        ImageDraw::img_generic(ctx, bottom_image, vec2i{x, max_pos.y - 100});
        ImageDraw::img_generic(ctx, bottom_image, vec2i{x, max_pos.y - 60});
        ImageDraw::img_generic(ctx, bottom_image, vec2i{x, max_pos.y - 20});
    }

    // horizontal bar borders
    for (int x = min_pos.x; x < max_pos.x; x += 86) {
        ImageDraw::img_generic(ctx, horizontal_bar, vec2i{x, min_pos.y});
        ImageDraw::img_generic(ctx, horizontal_bar, vec2i{x, max_pos.y - 140});
        ImageDraw::img_generic(ctx, horizontal_bar, vec2i{x, max_pos.y - 16});
    }

    // vertical bar borders
    for (int y = min_pos.y + 16; y < max_pos.y; y += 86) {
        ImageDraw::img_generic(ctx, vertical_bar, vec2i{min_pos.x, y});
        ImageDraw::img_generic(ctx, vertical_bar, vec2i{max_pos.x - 16, y});
    }

    // crossbars
    ImageDraw::img_generic(ctx, cross_bar, vec2i{min_pos.x, min_pos.y});
    ImageDraw::img_generic(ctx, cross_bar, vec2i{min_pos.x, max_pos.y - 140});
    ImageDraw::img_generic(ctx, cross_bar, vec2i{min_pos.x, max_pos.y - 16});
    ImageDraw::img_generic(ctx, cross_bar, vec2i{max_pos.x - 16, min_pos.y});
    ImageDraw::img_generic(ctx, cross_bar, vec2i{max_pos.x - 16, max_pos.y - 140});
    ImageDraw::img_generic(ctx, cross_bar, vec2i{max_pos.x - 16, max_pos.y - 16});

    graphics_reset_clip_rectangle();
}

int empire_window::draw_background() {
    auto &data = g_empire_window;
    int s_width = screen_width();
    int s_height = screen_height();
    data.min_pos.x = s_width <= EMPIRE_SIZE.x ? 0 : (s_width - EMPIRE_SIZE.x) / 2;
    data.max_pos.x = s_width <= EMPIRE_SIZE.x ? s_width : data.min_pos.x + EMPIRE_SIZE.x;
    data.min_pos.y = s_height <= EMPIRE_SIZE.y ? 0 : (s_height - EMPIRE_SIZE.y) / 2;
    data.max_pos.y = s_height <= EMPIRE_SIZE.y ? s_height : data.min_pos.y + EMPIRE_SIZE.y;

    if (data.min_pos.x || data.min_pos.y) {
        graphics_clear_screen();
    }

    ui["button_help"].onclick([] {
        window_message_dialog_show(MESSAGE_DIALOG_EMPIRE_MAP, -1, 0);
    });

    ui["button_close"].onclick([] {
        window_city_show();
    });

    ui["button_advisor"].onclick([] {
        window_advisors_show_advisor(ADVISOR_TRADE);
    });

    ui["button_open_trade"].onclick([] {
        window_yes_dialog_show("#popup_dialog_open_trade", [] {
            empire_city *city = g_empire.city(g_empire_window.selected_city);
            city_finance_process_construction(city->cost_to_open);
            city->is_open = 1;
            window_trade_opened_show(g_empire_window.selected_city);
        });
    });

    return 0;
}

void empire_window::ui_draw_foreground() {
    draw_map();

    const empire_city* city = nullptr;
    int selected_object = g_empire_map.selected_object();
    if (selected_object) {
        const empire_object *object = empire_object_get(selected_object - 1);
        if (object->type == EMPIRE_OBJECT_CITY) {
            selected_city = g_empire.get_city_for_object(object->id);
            city = g_empire.city(selected_city);
        }
    }

    ui["city_name"] = "";
    ui["button_help"].enabled = !!city;
    ui["button_close"].enabled = !!city;
    ui["button_advisor"].enabled = !!city;
    ui["button_open_trade"].enabled = city && !city->is_open && city->can_trade();
    if (city) {
        int text_group = g_settings.city_names_style == CITIES_OLD_NAMES ? text_group_old_names : text_group_new_names;
        ui["city_name"] = ui::str(text_group, city->name_id);
    }

    draw_paneling();

    ui.begin_widget({ 0, 0 });
    ui.draw();
    

    draw_object_info();

    ui.end_widget();
}

template<typename T>
static e_resource resource_from_mouse_pos(tooltip_context* c, const T& arr) {
    vec2i m = c->mpos;
    for (const auto &c: arr) {
        if (c.r.inside(m)) {
            return c.res;
        }
    }
    return RESOURCE_NONE;
}

static e_resource get_tooltip_resource(tooltip_context* c) {
    auto &data = g_empire_window;
    const empire_city* city = g_empire.city(data.selected_city);
    // we only want to check tooltips on our own closed cities.
    // open city resource tooltips are handled by their respective buttons directly
    if (city->is_open
        || (city->type != EMPIRE_CITY_PHARAOH_TRADING && city->type != EMPIRE_CITY_EGYPTIAN_TRADING && city->type != EMPIRE_CITY_FOREIGN_TRADING)) {
        return RESOURCE_NONE;
    }

    e_resource res = resource_from_mouse_pos(c, data.selling_goods);
    if (res == RESOURCE_NONE) {
        res = resource_from_mouse_pos(c, data.buying_goods);
    }
    
    return res;
}

static void get_tooltip_trade_route_type(tooltip_context* c) {
    //auto &data = g_empire_window;
    //int selected_object = g_empire_map.selected_object();
    //if (!selected_object || empire_object_get(selected_object - 1)->type != EMPIRE_OBJECT_CITY)
    //    return;
    //
    //data.selected_city = g_empire.get_city_for_object(selected_object - 1);
    //const empire_city* city = g_empire.city(data.selected_city);
    //if (city->type != EMPIRE_CITY_PHARAOH || city->is_open)
    //    return;
    //
    //int x_offset = (data.min_pos.x + data.max_pos.x + 300) / 2;
    //int y_offset = data.max_pos.y - 41;
    //int y_offset_max = y_offset + 22 - 2 * city->is_sea_trade;
    //if (c->mpos.x >= x_offset && c->mpos.x < x_offset + 32 && c->mpos.y >= y_offset && c->mpos.y < y_offset_max) {
    //    c->type = TOOLTIP_BUTTON;
    //    c->text.group = 44;
    //    c->text.id = 28 + city->is_sea_trade;
    //}
}

static void window_empire_get_tooltip(tooltip_context* c) {
    //auto &data = g_empire_window;
    //int resource = data.focus_resource ? data.focus_resource : get_tooltip_resource(c);
    //if (resource) {
    //    c->type = TOOLTIP_BUTTON;
    //    c->text.group = 23;
    //    c->text.id = resource;
    //} else if (data.focus_button_id) {
    //    c->type = TOOLTIP_BUTTON;
    //    switch (data.focus_button_id) {
    //    case 1:
    //        c->text.id = 1;
    //        break;
    //    case 2:
    //        c->text.id = 2;
    //        break;
    //    case 3:
    //        c->text.id = 70;
    //        break;
    //    }
    //} else {
    //    get_tooltip_trade_route_type(c);
    //}
}

static void button_show_resource_window(int resource, int param2) {
    window_resource_settings_show((e_resource)resource);
}

void window_empire_show() {
    static window_type window = {
        WINDOW_EMPIRE,
        [] { g_empire_window.draw_background(); },
        [] { g_empire_window.ui_draw_foreground(); },
        [] (const mouse *m, const hotkeys *h) { g_empire_window.ui_handle_mouse(m); },
        window_empire_get_tooltip
    };

    g_empire_window.init();
    window_show(&window);
}

void window_empire_show_checked() {
    e_availability avail = mission_empire_availability(scenario_campaign_scenario_id() + 1);
    
    if (avail == AVAILABLE || scenario_is_custom()) {
        window_empire_show();
    } else {
        city_warning_show(avail == NOT_AVAILABLE ? WARNING_NOT_AVAILABLE : WARNING_NOT_AVAILABLE_YET);
    }
}
