#include "window_empire.h"

#include "city/military.h"
#include "city/city.h"
#include "city/city_resource_handle.h"
#include "game/game_events.h"
#include "city/city_warnings.h"
#include "city/constants.h"
#include "city/city_finance.h"
#include "empire/empire.h"
#include "empire/empire_city.h"
#include "empire/empire_map.h"
#include "empire/empire_object.h"
#include "empire/empire_traders.h"
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
#include "input/mouse.h"
#include "input/scroll.h"
#include "scenario/empire.h"
#include "scenario/scenario_invasion.h"
#include "scenario/scenario.h"
#include "window/advisors.h"
#include "window/window_city.h"
#include "window/message_dialog.h"
#include "window/popup_dialog.h"
#include "window/resource_settings.h"
#include "game/game_config.h"
#include "window/trade_opened.h"
#include "platform/renderer.h"
#include "game/game.h"

#include "js/js_game.h"
#include "js/js_events.h"
#include "dev/debug.h"

uint16_t empire_images_remap[32000] = {0};

declare_console_var_bool(empire_window_draw_points, false)
void ANK_REGISTER_CONFIG_ITERATOR(config_load_images_remap_config) {
    g_config_arch.r_array("empire_images_remap", [] (archive arch) {
        int id = arch.r_int("id");
        int remap = arch.r_int("rid");
        empire_images_remap[id] = remap;
    });
}

int image_id_remap(int id) {
    int rimg = empire_images_remap[id];
    return rimg ? rimg : id;
}

const static vec2i EMPIRE_SIZE{1200 + 32,  1600 + 136 + 20};

struct object_trade_info {
    rect r;
    e_resource res;
};

empire_window g_empire_window;

struct empire_window_draw { vec2i draw_offset; };
ANK_REGISTER_SCRIPT_EVENT(empire_window_draw, draw_offset);

void empire_window::init() {
    selected_button = 0;
    int selected_object = g_empire_map.selected_object();
    selected_city = selected_object ? g_empire.get_city_for_object(selected_object - 1) : 0;

    ui["city_want_sell_items"].ondraw([this] (ui::element *e, UiFlags flags) { draw_city_want_sell(e, flags); });
    ui["city_want_buy_items"].ondraw([this] (ui::element *e, UiFlags flags) { draw_city_want_buy(e, flags); });
    ui["city_sell_items"].ondraw([this] (ui::element *e, UiFlags flags) { draw_city_selling(e, flags); });
    ui["city_buy_items"].ondraw([this] (ui::element *e, UiFlags flags) { draw_city_buy(e, flags); });

    ui["button_help"].onclick([] { window_message_dialog_show("message_world_map", -1, 0); });
    ui["button_close"].onclick([] { window_city_show(); });
    ui["button_advisor"].onclick([] { window_advisors_show_advisor(ADVISOR_TRADE); });

    ui["button_open_trade"].onclick([] {
        popup_dialog::show_yesno("#popup_dialog_open_trade", [] {
            empire_city *city = g_empire.city(g_empire_window.selected_city);

            if (city && city->is_sieged()) {
                return;
            }
            
            g_city.finance.process_construction(city->cost_to_open);
            city->is_open = 1;
            window_trade_opened_show(g_empire_window.selected_city);
        });
    });

}

inline void empire_window::archive_load(archive arch) {
    autoconfig_window::archive_load(arch);

    trade_column_spacing = arch.r_int("trade_column_spacing");
    trade_row_spacing = arch.r_int("trade_row_spacing");
    info_y_traded = arch.r_int("info_y_traded");
    trade_button_offset_x = arch.r_int("trade_button_offset_x");
    info_y_city_desc = arch.r_int("info_y_city_desc");
    trade_resource_size = arch.r_int("trade_resource_size");
    trade_button_offset_y = arch.r_int("trade_button_offset_y");
    start_pos = arch.r_vec2i("start_pos");
    finish_pos = arch.r_vec2i("finish_pos");
    arch.r_desc("image", image);
    arch.r_desc("bottom_image", bottom_image);
    arch.r_desc("horizontal_bar", horizontal_bar);
    arch.r_desc("vertical_bar", vertical_bar);
    arch.r_desc("cross_bar", cross_bar);
    arch.r_desc("trade_amount", trade_amount);
    arch.r_desc("closed_trade_route_hl", closed_trade_route_hl);
    arch.r_desc("open_trade_route", open_trade_route);
    arch.r_desc("open_trade_route_hl", open_trade_route_hl);

    init();
}

void empire_window::draw_trade_route(int route_id, e_empire_route_state effect) {
    painter ctx = game.painter();

    const map_route_object& obj = g_empire.get_route_object(route_id);
    if (!obj.in_use) {
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
        image_id = closed_trade_route_hl.tid();
        break;

    case ROUTE_OPEN: // open
        image_id = open_trade_route.tid();
        break;

    case ROUTE_OPEN_SELECTED: // highlighted, open
        image_id = open_trade_route_hl.tid();
        break;
    }

    for (int i = 0; i < obj.num_points; i++) {
        const auto &route_point = obj.points[i];

        // first corner in pair
        ctx.img_generic(image_id, draw_offset + route_point.p);

        // draw lines connecting the turns
        if (i < obj.num_points - 1) {
            auto nextup_route_point = obj.points[i + 1];
            vec2i d = nextup_route_point.p - route_point.p;
            float len = 0.2f * sqrtf(float(d.x * d.x) + float(d.y * d.y));

            float scaled_x = (float)d.x / len;
            float scaled_y = (float)d.y / len;

            float progress = 1.0;
            while (progress < len) {
                vec2i disp = draw_offset + route_point.p + vec2i{(int)(scaled_x * progress), (int)(scaled_y * progress)};
                ctx.img_generic(image_id, disp);
                progress += 1.0f;
            }

            if (empire_window_draw_points()) {
                ui::fill_rect(draw_offset + vec2i{ route_point.p.x - 4, route_point.p.y - 4 }, vec2i{ 8, 8 }, COLOR_BLACK);
            }
        }
    }
}

void empire_window::draw_trade_resource(UiFlags flags, e_resource resource, int trade_now, int trade_max, vec2i offset, e_font font) {
    ui.icon(offset + vec2i{ 1, 1 }, resource, UiFlags_Outline);
    ui.button("", offset - vec2i{ 2, 2 }, vec2i{ 105, 24 }, fonts_vec{}, flags|UiFlags_NoBody)
         .tooltip({23, resource})
         .onclick([resource] {
            window_resource_settings_show(resource);
         });

    bstring64 text;
    if (trade_now < 0) {
        text.printf("%d", trade_max);
    } else {
        text.printf("%d %s %d", trade_now, ui::str(sell_res_group, 12), trade_max);
    }
    ui.label(text.c_str(), offset + vec2i{ 40, 0 }, font);

    switch (trade_max) {
    case 1500: case 15: ui.image(trade_amount, offset + vec2i{21, -1}); break;
    case 2500: case 25: ui.image(trade_amount + 1, offset + vec2i{17, -1}); break;
    case 4000: case 40: ui.image(trade_amount + 2, offset + vec2i{13, -1}); break;
    }
}

void empire_window::draw_city_want_sell(ui::element *e, UiFlags flags) {
    int selected_object = g_empire_map.selected_object();
    const empire_object *object = g_empire.get_object(selected_object - 1);
    const empire_city *city = g_empire.city(selected_city);

    const auto &trade_route = city->get_route();
    const auto &item_sell = ui["city_want_sell_item"];

    int sell_index = 0;
    for (const auto &r : resource_list::all) {
        if (!g_empire.city_sells_resource(object->id, r.type, false))
            continue;

        city_resource_handle hresource{ r.type };
        int trade_max = trade_route.limit(r.type);
        trade_max = hresource.stack_proper_quantity(trade_max);
        draw_trade_resource(flags, r.type, -1, trade_max, e->pos + item_sell.size * sell_index, item_sell.font());
        sell_index++;
    }
}

void empire_window::draw_city_want_buy(ui::element *e, UiFlags flags) {
    int selected_object = g_empire_map.selected_object();
    const empire_object *object = g_empire.get_object(selected_object - 1);
    const empire_city *city = g_empire.city(selected_city);

    const auto &trade_route = city->get_route();
    const auto &item_buy = ui["city_want_buy_item"];

    int buy_index = 0;
    for (const auto &r : resource_list::all) {
        if (!g_empire.city_buys_resource(object->id, r.type, false))
            continue;

        city_resource_handle hresource{ r.type };
        int trade_max = trade_route.limit(r.type);
        trade_max = hresource.stack_proper_quantity(trade_max);
        draw_trade_resource(flags, r.type, -1, trade_max, e->pos + item_buy.size * buy_index, item_buy.font());
        buy_index++;
    }
}

void empire_window::draw_city_buy(ui::element *e, UiFlags flags) {
    int selected_object = g_empire_map.selected_object();
    const empire_object *object = g_empire.get_object(selected_object - 1);
    const empire_city *city = g_empire.city(selected_city);

    int index = 0;

    const auto &item_buy = ui["city_buy_item"];
    vec2i e_offset = e->pos;
    for (e_resource resource = RESOURCES_MIN; resource < RESOURCES_MAX; ++resource) {
        if (!g_empire.city_buys_resource(object->id, resource, false))
            continue;

        const auto &trade_route = city->get_route();
        int trade_max = trade_route.limit(resource);
        int trade_now = std::min(trade_max, trade_route.traded(resource));

        city_resource_handle hresource{ resource };
        trade_now = hresource.stack_proper_quantity(trade_now);
        trade_max = hresource.stack_proper_quantity(trade_max);

        vec2i local_offset = vec2i{ item_buy.size.x, 0 } * index;
        draw_trade_resource(flags, resource, trade_now, trade_max, e_offset + local_offset, item_buy.font());
        index++;

        if (local_offset.x > e->size.x) {
            e_offset.y += item_buy.size.y;
            index = 0;
        }
    }
}

void empire_window::draw_city_selling(ui::element *e, UiFlags flags) {
    int selected_object = g_empire_map.selected_object();
    const empire_object *object = g_empire.get_object(selected_object - 1);
    const empire_city *city = g_empire.city(selected_city);

    const auto &item_sell = ui["city_sell_item"];
    int index = 0;
    vec2i e_offset = e->pos;
    for (e_resource resource = RESOURCES_MIN; resource < RESOURCES_MAX; ++resource) {
        if (!g_empire.city_sells_resource(object->id, resource, false)) {
            continue;
        }

        const auto &trade_route = city->get_route();
        int trade_max = trade_route.limit(resource);
        int trade_now = std::min(trade_max, trade_route.traded(resource));

        city_resource_handle hresource{ resource };
        trade_now = hresource.stack_proper_quantity(trade_now);
        trade_max = hresource.stack_proper_quantity(trade_max);

        vec2i local_offset = vec2i{ item_sell.size.x, 0 } * index;
        draw_trade_resource(flags, resource, trade_now, trade_max, e_offset + local_offset, item_sell.font());
        index++;

        if(local_offset.x > e->size.x) {
            e_offset.y += item_sell.size.y;
            index = 0;
        }
    }
}
void empire_window::clear_city_info() {
    ui["city_sell_title"].enabled = false;
    ui["city_sell_items"].enabled = false;
    ui["city_buy_title"].enabled = false;
    ui["city_buy_items"].enabled = false;
    ui["city_want_sell_title"].enabled = false;
    ui["city_want_sell_items"].enabled = false;
    ui["city_want_buy_title"].enabled = false;
    ui["city_want_buy_items"].enabled = false;
}

void empire_window::draw_city_info(const empire_object* object) {
    const empire_city* city = g_empire.city(selected_city);

    clear_city_info();
    switch (city->type) {
    case EMPIRE_CITY_OURS:
        ui["info_tooltip"] = ui::str(sell_res_group, 1);
        break;

    case EMPIRE_CITY_PHARAOH:
        ui["info_tooltip"] = ui::str(sell_res_group, 19);
        break;

    case EMPIRE_CITY_EGYPTIAN:
        ui["info_tooltip"] = ui::str(sell_res_group, 13);
        break;

    case EMPIRE_CITY_FOREIGN:
        ui["info_tooltip"] = ui::str(sell_res_group, 0);
        break;

    case EMPIRE_CITY_PHARAOH_TRADING:
    case EMPIRE_CITY_EGYPTIAN_TRADING:
    case EMPIRE_CITY_FOREIGN_TRADING:
        ui["info_tooltip"] = "";
        ui["city_sell_title"].enabled = city->is_open;
        ui["city_sell_items"].enabled = city->is_open;
        ui["city_buy_title"].enabled = city->is_open;
        ui["city_buy_items"].enabled = city->is_open;
        ui["city_want_sell_title"].enabled = !city->is_open;
        ui["city_want_sell_items"].enabled = !city->is_open;
        ui["city_want_buy_title"].enabled = !city->is_open;
        ui["city_want_buy_items"].enabled = !city->is_open;
        break;

    default:
        assert(false);
    }
}

void empire_window::draw_kingdome_army_info(const empire_object* object) {
    if (g_city.distant_battle.kingdome_army_is_traveling()) {
        if (city_military_distant_battle_kingdome_months_traveled() == object->distant_battle_travel_months) {
            vec2i offset{(min_pos.x + max_pos.x - 240) / 2, max_pos.y - 68};
            int text_id;
            if (g_city.distant_battle.kingdome_army_is_traveling_forth())
                text_id = 15;
            else {
                text_id = 16;
            }

            lang_text_draw_multiline(sell_res_group, text_id, offset, 240, FONT_NORMAL_BLACK_ON_LIGHT);
        }
    }
}

void empire_window::draw_enemy_army_info(const empire_object* object) {
    if (g_city.distant_battle.months_until_distant_battle() > 0) {
        if (g_city.distant_battle.enemy_months_traveled() == object->distant_battle_travel_months) {
            lang_text_draw_multiline(sell_res_group, 14, vec2i{(min_pos.x + max_pos.x - 240) / 2, max_pos.y - 68}, 240, FONT_NORMAL_BLACK_ON_LIGHT);
        }
    }
}

void empire_window::draw_object_info() {
    int selected_object = g_empire_map.selected_object();
    if (selected_object) {
        ui["info_tooltip"] = "";
        const empire_object* object = g_empire.get_object(selected_object - 1);
        switch (object->type) {
        case EMPIRE_OBJECT_CITY: draw_city_info(object); break;
        case EMPIRE_OBJECT_KINGDOME_ARMY: draw_kingdome_army_info(object); break;
        case EMPIRE_OBJECT_ENEMY_ARMY: draw_enemy_army_info(object); break;
        }
    } else {
        clear_city_info();
        ui["info_tooltip"] = ui::str(47, 9);
    }
}

void empire_window::determine_selected_object(const mouse *m) {
    if (!m->left.went_up || finished_scroll || is_outside_map(m->x, m->y)) {
        finished_scroll = 0;
        return;
    }

    g_empire_map.select_object(vec2i{ m->x, m->y } - min_pos - vec2i{ 16, 16 });
}

bool empire_window::is_outside_map(int x, int y) {
    return (x < min_pos.x + 16 || x >= max_pos.x - 16 || y < min_pos.y + 16 || y >= max_pos.y - 120);
}

int empire_window::ui_handle_mouse(const mouse *m) {
    const hotkeys *h = hotkey_state();

    vec2i position;
    last_mouse_pos = { m->x, m->y };
    if (scroll_get_delta(m, &position, SCROLL_TYPE_EMPIRE)) {
        g_empire_map.scroll_map(position);
    }

    if (m->is_touch) {
        const touch_t *t = get_earliest_touch();
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

    determine_selected_object(m);

    int selected_object = g_empire_map.selected_object();
    if (selected_object) {
        const empire_object *obj = g_empire.get_object(selected_object - 1);
        if (obj->type == EMPIRE_OBJECT_CITY) {
            selected_city = g_empire.get_city_for_object(selected_object - 1);
        }

        if (input_go_back_requested(m, h)) {
            g_empire_map.clear_selected_object();
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

void empire_window::draw_empire_object(const empire_object &obj) {
    if (obj.type == EMPIRE_OBJECT_LAND_TRADE_ROUTE || obj.type == EMPIRE_OBJECT_SEA_TRADE_ROUTE) {
        if (!g_empire.is_trade_route_open(obj.trade_route_id)) {
            return;
        }
    }

    vec2i pos;
    int image_id;
    pcstr tooltip_text = "";
    if (scenario_empire_is_expanded()) {
        pos = obj.expanded.pos;
        image_id = obj.expanded.image_id;
    } else {
        pos = obj.pos;
        image_id = obj.image_id;
    }

    image_id = image_id_remap(image_id);
    const vec2i draw_pos = draw_offset + pos;

    if (obj.type == EMPIRE_OBJECT_CITY) {
        const image_t *img = ui::eimage(image_id, draw_pos);
        int empire_city_id = g_empire.get_city_for_object(obj.id);
        const empire_city* city = g_empire.city(empire_city_id);

        // draw siege icon if city is under siege
        if (city && city->is_sieged()) {
            image_desc siege_icon_desc = image_desc_from_name("pharaoh_general/empire_bits_00001");
            if (siege_icon_desc.pack != PACK_NONE) {
                const image_t *siege_icon = image_get(siege_icon_desc);
                if (siege_icon) {
                    vec2i siege_icon_pos = draw_pos + vec2i{img->width / 2 - siege_icon->width / 2, -siege_icon->height - 5};
                    ui::eimage(siege_icon_desc, siege_icon_pos);
                }
            }
        }

        // draw routes!
        if (city->type == EMPIRE_CITY_EGYPTIAN_TRADING || city->type == EMPIRE_CITY_FOREIGN_TRADING || city->type == EMPIRE_CITY_PHARAOH_TRADING) {
            e_empire_route_state state = ROUTE_CLOSED;
            if (city->is_open) {
                state = (g_empire_map.selected_object() && selected_city == g_empire.get_city_for_object(obj.id))
                              ? ROUTE_OPEN_SELECTED 
                              : ROUTE_OPEN;
            } else {
                state = (g_empire_map.selected_object() && selected_city == g_empire.get_city_for_object(obj.id))
                              ? ROUTE_CLOSED_SELECTED
                              : ROUTE_CLOSED;
            }
            draw_trade_route(city->route_id, state);
        }

        const int letter_height = font_definition_for(FONT_SMALL_PLAIN)->line_height;
        vec2i text_pos = draw_offset + pos + vec2i{img->width, (img->height - letter_height)/2};

        tooltip_text = city->name_str;

        switch (obj.text_align) {
        case 0: ui::label_colored(tooltip_text, text_pos, FONT_SMALL_PLAIN, COLOR_FONT_DARK_RED, obj.width); break;
        case 1: ui::label_colored(tooltip_text, text_pos, FONT_SMALL_PLAIN, COLOR_FONT_DARK_RED, obj.width); break;
        case 2: ui::label_colored(tooltip_text, text_pos, FONT_SMALL_PLAIN, COLOR_FONT_DARK_RED, obj.width); break;
        case 3: ui::label_colored(tooltip_text, text_pos, FONT_SMALL_PLAIN, COLOR_FONT_DARK_RED, obj.width); break;
        }

        // draw "under siege" text if city is under siege
        if (city && city->is_sieged()) {
            vec2i siege_text_pos = text_pos + vec2i{0, letter_height + 2};
            ui::label_colored("under siege", siege_text_pos, FONT_SMALL_PLAIN, COLOR_FONT_RED, obj.width);
        }

    } else if (obj.type == EMPIRE_OBJECT_TEXT) {
        const full_empire_object* full = g_empire.get_full_object(obj.id);
        vec2i text_pos = draw_offset + pos;

        tooltip_text = ui::str(196, full->city_name_id);
        ui::label_colored(tooltip_text, text_pos - vec2i{5, 0}, FONT_SMALL_PLAIN, COLOR_FONT_SHITTY_BROWN, 100);
        return;
    }

    if (obj.type == EMPIRE_OBJECT_BATTLE_ICON) {
        // handled later
        return;
    }

    if (obj.type == EMPIRE_OBJECT_ENEMY_ARMY) {
        if (g_city.distant_battle.months_until_distant_battle() <= 0)
            return;

        if (g_city.distant_battle.enemy_months_traveled() != obj.distant_battle_travel_months)
            return;
    }
    
    if (obj.type == EMPIRE_OBJECT_KINGDOME_ARMY) {
        if (!g_city.distant_battle.kingdome_army_is_traveling())
            return;

        if (city_military_distant_battle_kingdome_months_traveled() != obj.distant_battle_travel_months)
            return;
    }

    {
        const image_t *img = ui::eimage(image_id, draw_pos);
        if (last_mouse_pos.x > draw_pos.x && last_mouse_pos.y > draw_pos.y
            && last_mouse_pos.x < draw_pos.x + img->width && last_mouse_pos.y < draw_pos.y + img->height) {
            hovered_object_tooltip = tooltip_text;
        }

        if (img && img->animation.speed_id) {
            int new_animation = g_empire.update_animation(obj, image_id);
            ui::eimage({ PACK_GENERAL, int16_t(image_id + new_animation) }, draw_pos + img->animation.sprite_offset);
        }
    }
}

void empire_window::draw_map() {
    graphics_set_clip_rectangle(min_pos + start_pos, vec2i{max_pos - min_pos} - finish_pos);

    g_empire_map.set_viewport(max_pos - min_pos - finish_pos);

    draw_offset = min_pos + start_pos;
    draw_offset = g_empire_map.adjust_scroll(draw_offset);
    hovered_object_tooltip = "";

    ui::eimage(image, draw_offset);

    g_empire.foreach_object([this] (const empire_object &obj) {
        draw_empire_object(obj);
    });

    scenario_invasion_foreach_warning([&] (vec2i pos, int image_id) {
        ui::eimage(image_id, draw_offset + pos);
    });    

    for (auto &trader: g_empire_traders.traders) {
        if (!trader.is_active) {
            continue;
        }

        const int image_id = image_id_from_group(PACK_GENERAL, 179) + (trader.is_ship ? 0 : 1);
        const vec2i draw_pos = draw_offset + trader.current_position;
        ui::eimage(image_id, draw_pos);
    }

    ui.draw(empire_window_draw{ draw_offset });

    graphics_reset_clip_rectangle();
}

void empire_window::draw_paneling() {
    painter ctx = game.painter();
    // bottom panel background
    graphics_set_clip_rectangle(min_pos, max_pos - min_pos);

    for (int x = min_pos.x; x < max_pos.x; x += 70) {
        ctx.img_generic(bottom_image, vec2i{x, max_pos.y - 140});
        ctx.img_generic(bottom_image, vec2i{x, max_pos.y - 100});
        ctx.img_generic(bottom_image, vec2i{x, max_pos.y - 60});
        ctx.img_generic(bottom_image, vec2i{x, max_pos.y - 20});
    }

    // horizontal bar borders
    for (int x = min_pos.x; x < max_pos.x; x += 86) {
        ctx.img_generic(horizontal_bar, vec2i{x, min_pos.y});
        ctx.img_generic(horizontal_bar, vec2i{x, max_pos.y - 140});
        ctx.img_generic(horizontal_bar, vec2i{x, max_pos.y - 16});
    }

    // vertical bar borders
    for (int y = min_pos.y + 16; y < max_pos.y; y += 86) {
        ctx.img_generic(vertical_bar, vec2i{min_pos.x, y});
        ctx.img_generic(vertical_bar, vec2i{max_pos.x - 16, y});
    }

    // crossbars
    ctx.img_generic(cross_bar, vec2i{min_pos.x, min_pos.y});
    ctx.img_generic(cross_bar, vec2i{min_pos.x, max_pos.y - 140});
    ctx.img_generic(cross_bar, vec2i{min_pos.x, max_pos.y - 16});
    ctx.img_generic(cross_bar, vec2i{max_pos.x - 16, min_pos.y});
    ctx.img_generic(cross_bar, vec2i{max_pos.x - 16, max_pos.y - 140});
    ctx.img_generic(cross_bar, vec2i{max_pos.x - 16, max_pos.y - 16});

    graphics_reset_clip_rectangle();
}

int empire_window::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

    auto &data = g_empire_window;
    int s_width = screen_width();
    int s_height = screen_height();
    data.min_pos.x = s_width <= EMPIRE_SIZE.x ? 0 : (s_width - EMPIRE_SIZE.x) / 2;
    data.max_pos.x = s_width <= EMPIRE_SIZE.x ? s_width : data.min_pos.x + EMPIRE_SIZE.x;
    data.min_pos.y = s_height <= EMPIRE_SIZE.y ? 0 : (s_height - EMPIRE_SIZE.y) / 2;
    data.max_pos.y = s_height <= EMPIRE_SIZE.y ? s_height : data.min_pos.y + EMPIRE_SIZE.y;

    if (data.min_pos.x || data.min_pos.y) {
        g_render.clear_screen();
    }

    return 0;
}

void empire_window::ui_draw_foreground(UiFlags flags) {
    draw_map();

    const empire_city* city = nullptr;
    int selected_object = g_empire_map.selected_object();
    if (selected_object) {
        const empire_object *object = g_empire.get_object(selected_object - 1);
        if (object->type == EMPIRE_OBJECT_CITY) {
            selected_city = g_empire.get_city_for_object(object->id);
            city = g_empire.city(selected_city);
        }
    }

    ui["city_name"] = "";
    ui["button_help"].enabled = !!city;
    ui["button_close"].enabled = !!city;
    ui["button_advisor"].enabled = !!city;
    ui["city_name"] = city ? city->name_str : "";

    const bool may_open_trade = city && !city->is_open && city->can_trade();
    ui["button_open_trade"].enabled = may_open_trade;
    if (may_open_trade) {
        ui["button_open_trade"].text_var("%s %d %s", ui::str(8, 0), city->cost_to_open, ui::str(sell_res_group, 6 + city->is_sea_trade));
    }

    draw_paneling();

    ui.begin_widget({ 0, 0 });
    ui.draw(flags);
    
    draw_object_info();
    draw_object_tooltip();

    ui.end_widget();
}

void empire_window::draw_object_tooltip() {
    if (!!hovered_object_tooltip) {
        ui::set_tooltip(hovered_object_tooltip);
    }
}

void empire_window::draw_tooltip(tooltip_context *c) {
    // First check for button tooltips (goods icons)
    int button_id = ui::button_hover(&mouse::get());
    if (button_id > 0) {
        pcstr tooltip = ui::button_tooltip(button_id - 1);
        if (tooltip && *tooltip) {
            c->text = tooltip;
            return;
        }
    }
    
    // Fall back to UI tooltip (set by draw_object_tooltip for city names, etc.)
    const tooltip_context &uitooltip = ui::get_tooltip();
    if (!!uitooltip.text) {
        c->text = uitooltip.text;
    }
}

void window_empire_show() {
    static window_type window = {
        WINDOW_EMPIRE,
        [] (int flags) { g_empire_window.draw_background(flags); },
        [] (int flags) { g_empire_window.ui_draw_foreground(flags); },
        [] (const mouse *m, const hotkeys *h) { g_empire_window.ui_handle_mouse(m); },
        [] (tooltip_context *c) { g_empire_window.draw_tooltip(c); }
    };

    g_empire_window.init();
    window_show(&window);
}

void window_empire_show_checked() {
    e_availability avail = mission_empire_availability(g_scenario.campaign_scenario_id() + 1);
    
    const bool is_custom_map = (g_scenario.mode() != e_scenario_normal);
    if (avail == AVAILABLE || is_custom_map) {
        window_empire_show();
    } else {
        pcstr text = (avail == NOT_AVAILABLE ? "#not_available_in_this_assignment" : "#not_available_yet");
        events::emit(event_city_warning{ text });
    }
}
ANK_FUNCTION(window_empire_show_checked)
