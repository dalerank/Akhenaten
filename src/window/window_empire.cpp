#include "window_empire.h"

#include "city/military.h"
#include "city/city.h"
#include "game/game_events.h"
#include "city/city_warnings.h"
#include "city/constants.h"
#include "empire/empire.h"
#include "empire/empire_city.h"
#include "empire/empire_map.h"
#include "empire/empire_object.h"
#include "empire/empire_traders.h"
#include "empire/trade_route.h"
#include "empire/type.h"
#include "scenario/distant_battle.h"
#include "game/settings.h"
#include "game/tutorial.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/image_button.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "input/mouse.h"
#include "input/scroll.h"
#include "scenario/empire.h"
#include "scenario/scenario_invasion.h"
#include "scenario/scenario.h"
#include "window/window_city.h"
#include "game/game_config.h"
#include "platform/renderer.h"
#include "game/game.h"
#include "core/profiler.h"
#include "js/js_game.h"
#include "graphics/elements/ui_js.h"
#include "dev/debug.h"

uint16_t empire_images_remap[32000] = {0};

using empire_object_tokens_t = token_holder<e_empire_object, EMPIRE_OBJECT_ORNAMENT, EMPIRE_OBJECT_COUNT>;
const empire_object_tokens_t ANK_CONFIG_ENUM(empire_object_tokens);

declare_console_var_bool(empire_window_draw_points, false) void ANK_REGISTER_CONFIG_ITERATOR(
  config_load_images_remap_config) {
    g_config_arch.r_array("empire_images_remap", [](archive arch) {
        int id = arch.r_int("id");
        int remap = arch.r_int("rid");
        empire_images_remap[id] = remap;
    });
}

int image_id_remap(int id) {
    int rimg = empire_images_remap[id];
    return rimg ? rimg : id;
}

struct object_trade_info {
    rect r;
    e_resource res;
};

empire_window g_empire_window;

struct empire_window_draw {
    vec2i draw_offset;
};
ANK_REGISTER_STRUCT_WRITER(empire_window_draw, draw_offset);

struct empire_window_draw_trader {
    int index;
};
ANK_REGISTER_STRUCT_WRITER(empire_window_draw_trader, index);

struct empire_window_init_event {
    vec2i pos;
};
ANK_REGISTER_STRUCT_WRITER(empire_window_init_event, pos);

struct empire_window_draw_background_evt {
    int pad = 0;
};
ANK_REGISTER_STRUCT_WRITER(empire_window_draw_background_evt, pad);

struct empire_window_object_info_empty {
    int unused = 0;
};
ANK_REGISTER_STRUCT_WRITER(empire_window_object_info_empty, unused);

struct empire_window_object_info_kingdome_army {
    int distant_battle_travel_months;
    int egyptian_months_to_travel_back;
    int egyptian_months_to_travel_forth;
    int kingdome_months_traveled;
};
ANK_REGISTER_STRUCT_WRITER(empire_window_object_info_kingdome_army, distant_battle_travel_months,
  egyptian_months_to_travel_back, egyptian_months_to_travel_forth, kingdome_months_traveled);

struct empire_window_object_info_enemy_army {
    int distant_battle_travel_months;
    int months_until_battle;
    int enemy_months_traveled;
};
ANK_REGISTER_STRUCT_WRITER(empire_window_object_info_enemy_army, distant_battle_travel_months, months_until_battle,
  enemy_months_traveled);

void empire_window::init() {
    int selected_object = g_empire_map.selected_object();
    g_empire_map.selected_city = selected_object ? g_empire.get_city_for_object(selected_object - 1) : 0;

    ui.begin_widget(pos);
    ui.event(empire_window_init_event{pos}, get_section(), "init");
    ui.end_widget();
}

void empire_window::archive_load(archive arch) {
    autoconfig_window::archive_load(arch);

    start_pos = arch.r_vec2i("start_pos");
    finish_pos = arch.r_vec2i("finish_pos");
    arch.r_desc("image", image);
    arch.r_desc("closed_trade_route_hl", closed_trade_route_hl);
    arch.r_desc("open_trade_route", open_trade_route);
    arch.r_desc("open_trade_route_hl", open_trade_route_hl);

    init();
}

void empire_window::draw_trade_route(int route_id, e_empire_route_state effect) {
    const map_route_object& obj = g_empire.get_route_object(route_id);
    if (!obj.in_use) {
        return;
    }

    // get graphics ready..
    int image_id = 0;
    switch (effect) {
    case ROUTE_CLOSED: // closed
        return;
        // image_id = image_id_from_group(GROUP_MINIMAP_BUILDING) + 211;
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
        const auto& route_point = obj.points[i];

        // first corner in pair — enqueue so flush draws above the empire map bitmap
        ui::image_abs(image_id, draw_offset + route_point.p);

        // draw lines connecting the turns
        if (i < obj.num_points - 1) {
            auto nextup_route_point = obj.points[i + 1];
            vec2i d = nextup_route_point.p - route_point.p;
            float len = 0.2f * sqrtf(float(d.x * d.x) + float(d.y * d.y));

            float scaled_x = (float)d.x / len;
            float scaled_y = (float)d.y / len;

            float progress = 1.0;
            while (progress < len) {
                vec2i disp
                  = draw_offset + route_point.p + vec2i{(int)(scaled_x * progress), (int)(scaled_y * progress)};
                ui::image_abs(image_id, disp);
                progress += 1.0f;
            }

            if (empire_window_draw_points()) {
                ui::fill_rect(draw_offset + vec2i{route_point.p.x - 4, route_point.p.y - 4}, vec2i{8, 8}, COLOR_BLACK);
            }
        }
    }
}

void empire_window::draw_object_info() {
    const int selected_object = g_empire_map.selected_object();
    if (selected_object <= 0) {
        ui.event(empire_window_object_info_empty{}, get_section(), "draw_object_info", "none");
        return;
    }

    const empire_object* object = g_empire.get_object(selected_object - 1);
    if (!object) {
        ui.event(empire_window_object_info_empty{}, get_section(), "draw_object_info", "none");
        return;
    }

    const e_empire_object ot = (e_empire_object)object->type;

    switch (ot) {
    case EMPIRE_OBJECT_KINGDOME_ARMY: {
        const auto& battle = g_distant_battle.battle;
        empire_window_object_info_kingdome_army info;
        info.distant_battle_travel_months = object->distant_battle_travel_months;
        info.egyptian_months_to_travel_back = battle.egyptian_months_to_travel_back;
        info.egyptian_months_to_travel_forth = battle.egyptian_months_to_travel_forth;
        info.kingdome_months_traveled = city_military_distant_battle_kingdome_months_traveled();
        ui.event(info, get_section(), "draw_object_info", empire_object_tokens.name(ot));
        break;
    }
    case EMPIRE_OBJECT_ENEMY_ARMY: {
        const auto& battle = g_distant_battle.battle;
        empire_window_object_info_enemy_army info;
        info.distant_battle_travel_months = object->distant_battle_travel_months;
        info.months_until_battle = battle.months_until_battle;
        info.enemy_months_traveled = g_distant_battle.enemy_months_traveled();
        ui.event(info, get_section(), "draw_object_info", empire_object_tokens.name(ot));
        break;
    }
    default:
        ui.event(empire_window_object_info_empty{}, get_section(), "draw_object_info", empire_object_tokens.name(ot));
        break;
    }
}

void empire_window::determine_selected_object(const mouse* m) {
    if (!m->left.went_up || finished_scroll || is_outside_map(m->x, m->y)) {
        finished_scroll = 0;
        return;
    }

    g_empire_map.select_object(vec2i{m->x, m->y} - min_pos - vec2i{16, 16});
}

bool empire_window::is_outside_map(int x, int y) {
    return (x < min_pos.x + 16 || x >= max_pos.x - 16 || y < min_pos.y + 16 || y >= max_pos.y - 120);
}

int empire_window::ui_handle_mouse(const mouse* m) {
    const hotkeys* h = hotkey_state();

    vec2i position;
    last_mouse_pos = {m->x, m->y};
    if (scroll_get_delta(m, &position, SCROLL_TYPE_EMPIRE)) {
        g_empire_map.scroll_map(position);
    }

    if (m->is_touch) {
        const touch_t* t = get_earliest_touch();
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
        const empire_object* obj = g_empire.get_object(selected_object - 1);
        if (obj->type == EMPIRE_OBJECT_CITY) {
            g_empire_map.selected_city = g_empire.get_city_for_object(selected_object - 1);
        }

        if (input_go_back_requested(m, h)) {
            g_empire_map.clear_selected_object();
            return 0;
        }
    } else if (input_go_back_requested(m, h)) {
        window_city_show();
        return 0;
    }

    ui.begin_widget({0, 0});
    ui.handle_mouse(m);
    ui.end_widget();

    return 0;
}

void empire_window::draw_empire_object(int object_index, const empire_object& obj) {
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
        const image_t* img = ui::eimage(image_id, draw_pos);
        int empire_city_id = g_empire.get_city_for_object(object_index);
        const empire_city* city = g_empire.city(empire_city_id);

        // draw siege icon if city is under siege
        if (city && city->is_sieged()) {
            image_desc siege_icon_desc = image_desc_from_name("pharaoh_general/empire_bits_00001");
            if (siege_icon_desc.pack != PACK_NONE) {
                const image_t* siege_icon = image_get(siege_icon_desc);
                if (siege_icon) {
                    vec2i siege_icon_pos
                      = draw_pos + vec2i{img->width / 2 - siege_icon->width / 2, -siege_icon->height - 5};
                    ui::eimage(siege_icon_desc, siege_icon_pos);
                }
            }
        }

        // draw routes! (highlighted path for the selected city is deferred to the end of draw_map)
        if (city->type == EMPIRE_CITY_EGYPTIAN_TRADING || city->type == EMPIRE_CITY_FOREIGN_TRADING
            || city->type == EMPIRE_CITY_PHARAOH_TRADING) {
            e_empire_route_state state = ROUTE_CLOSED;
            if (city->is_open) {
                state = (g_empire_map.selected_object()
                          && g_empire_map.selected_city == g_empire.get_city_for_object(object_index))
                          ? ROUTE_OPEN_SELECTED
                          : ROUTE_OPEN;
            } else {
                state = (g_empire_map.selected_object()
                          && g_empire_map.selected_city == g_empire.get_city_for_object(object_index))
                          ? ROUTE_CLOSED_SELECTED
                          : ROUTE_CLOSED;
            }
            if (state == ROUTE_OPEN_SELECTED || state == ROUTE_CLOSED_SELECTED) {
                deferred_selected_trade_route_id = city->route_id;
                deferred_selected_trade_route_state = state;
            } else {
                draw_trade_route(city->route_id, state);
            }
        }

        const int letter_height = font_definition_for(FONT_SMALL_PLAIN)->line_height;
        vec2i text_pos = draw_offset + pos + vec2i{img->width, (img->height - letter_height) / 2};

        tooltip_text = city->name_str;

        switch (obj.text_align) {
        case 0:
            ui::label_colored(tooltip_text, text_pos, FONT_SMALL_PLAIN, COLOR_FONT_DARK_RED, obj.width);
            break;
        case 1:
            ui::label_colored(tooltip_text, text_pos, FONT_SMALL_PLAIN, COLOR_FONT_DARK_RED, obj.width);
            break;
        case 2:
            ui::label_colored(tooltip_text, text_pos, FONT_SMALL_PLAIN, COLOR_FONT_DARK_RED, obj.width);
            break;
        case 3:
            ui::label_colored(tooltip_text, text_pos, FONT_SMALL_PLAIN, COLOR_FONT_DARK_RED, obj.width);
            break;
        }

        // draw "under siege" text if city is under siege
        if (city && city->is_sieged()) {
            vec2i siege_text_pos = text_pos + vec2i{0, letter_height + 2};
            ui::label_colored("under siege", siege_text_pos, FONT_SMALL_PLAIN, COLOR_FONT_RED, obj.width);
        }

    } else if (obj.type == EMPIRE_OBJECT_TEXT) {
        const full_empire_object* full = g_empire.get_full_object(object_index);
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
        if (g_distant_battle.battle.months_until_battle <= 0)
            return;

        if (g_distant_battle.enemy_months_traveled() != obj.distant_battle_travel_months)
            return;
    }

    if (obj.type == EMPIRE_OBJECT_KINGDOME_ARMY) {
        if (!g_distant_battle.kingdome_army_is_traveling())
            return;

        if (city_military_distant_battle_kingdome_months_traveled() != obj.distant_battle_travel_months)
            return;
    }

    if (obj.type == EMPIRE_OBJECT_TRADER) {
        return;
    }

    {
        const image_t* img = ui::eimage(image_id, draw_pos);
        if (last_mouse_pos.x > draw_pos.x && last_mouse_pos.y > draw_pos.y && last_mouse_pos.x < draw_pos.x + img->width
            && last_mouse_pos.y < draw_pos.y + img->height) {
            hovered_object_tooltip = tooltip_text;
        }

        if (img && img->animation.speed_id) {
            int new_animation = g_empire.update_animation(object_index, obj, image_id);
            ui::eimage(image_id + new_animation, draw_pos + img->animation.sprite_offset);
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

    g_empire.foreach_object(
      [this](int object_index, const empire_object& obj) { draw_empire_object(object_index, obj); });

    scenario_invasion_foreach_warning([&](vec2i pos, int image_id) { ui::eimage(image_id, draw_offset + pos); });

    for (auto& trader : g_empire_traders.traders) {
        if (!trader.is_active) {
            continue;
        }
        ui.event(empire_window_draw_trader{trader.id}, get_section(), __func__,
          empire_object_tokens.name(EMPIRE_OBJECT_TRADER));
    }

    ui.event(empire_window_draw{draw_offset}, get_section(), __func__,
      empire_object_tokens.name(EMPIRE_OBJECT_DISTANT_BATTLE_ROUTE));

    if (deferred_selected_trade_route_id >= 0) {
        draw_trade_route(deferred_selected_trade_route_id, deferred_selected_trade_route_state);
    }

    ui.begin_widget(pos);
    ui.event(empire_window_draw{draw_offset}, get_section(), __func__);
    ui.end_widget();

    graphics_reset_clip_rectangle();
}

void empire_window::draw_paneling() {
    ui.event(empire_window_draw{pos}, get_section(), __func__);
}

void empire_window::ui_draw_foreground(UiFlags flags) {
    draw_map();

    const empire_city* city = nullptr;
    int selected_object = g_empire_map.selected_object();
    if (selected_object) {
        const empire_object* object = g_empire.get_object(selected_object - 1);
        if (object->type == EMPIRE_OBJECT_CITY) {
            g_empire_map.selected_city = g_empire.get_city_for_object(selected_object - 1);
            city = g_empire.city(g_empire_map.selected_city);
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
        ui["button_open_trade"].text_var("%s %d %s", ui::str(8, 0), city->cost_to_open,
          ui::str(sell_res_group, 6 + city->is_sea_trade));
    }

    draw_paneling();

    ui.begin_widget({0, 0});
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

void empire_window::draw_tooltip(tooltip_context* c) {
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
    const tooltip_context& uitooltip = ui::get_tooltip();
    if (!!uitooltip.text) {
        c->text = uitooltip.text;
    }
}

void window_empire_show() {
    static window_type window = {"window_empire", [](int flags) { g_empire_window.draw_background(flags); },
      [](int flags) { g_empire_window.ui_draw_foreground(flags); },
      [](const mouse* m, const hotkeys* h) { g_empire_window.ui_handle_mouse(m); },
      [](tooltip_context* c) { g_empire_window.draw_tooltip(c); }};

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
        events::emit(event_city_warning{text});
    }
}
ANK_FUNCTION(window_empire_show_checked)

void __empire_window_set_map_bounds(int min_x, int min_y, int max_x, int max_y) {
    g_empire_window.min_pos = {min_x, min_y};
    g_empire_window.max_pos = {max_x, max_y};
}
ANK_FUNCTION_4(__empire_window_set_map_bounds)