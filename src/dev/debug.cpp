#include "debug.h"

#include <cmath>
#include <vector>
#include <algorithm>

#include "core/string.h"
#include "graphics/text.h"

#include "graphics/graphics.h"
#include "widget/debug_console.h"
#include "imgui.h"
#include "imgui_internal.h"

#include "city/city.h"
#include "core/profiler.h"
#include "graphics/view/lookup.h"
#include "graphics/view/zoom.h"
#include "grid/building.h"
#include "grid/terrain.h"
#include "widget/city/building_ghost.h"
#include "game/game.h"

#include "building/construction/build_planner.h"
#include "city/coverage.h"
#include "game/game_events.h"
#include "sound/sound_city.h"
#include "sound/sound.h"
#include "core/random.h"
#include "figure/route.h"
#include "grid/figure.h"
#include "platform/renderer.h"
#include "overlays/city_overlay.h"
#include "scenario/scenario.h"
#include "figure/formation.h"
#include "core/calc.h"
#include "grid/grid.h"
#include "graphics/elements/tooltip.h"
#include "graphics/elements/ui.h"
#include "graphics/screen.h"
#include "city/city_figures.h"

#include "js/js_game.h"

int g_debug_figure_id = 0;

game_debug_t g_debug;

const token_holder<e_debug_render, e_debug_render_none, e_debug_render_size> ANK_CONFIG_ENUM(e_debug_render_tokens);

declare_console_var_int(debugrender, 0);
declare_console_var_int(debugbuildingid, 0);

static const uint8_t* font_test_str = (uint8_t*)(char*)"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!\"%*()-+=:;'?\\/,._äáàâëéèêïíìîöóòôüúùûçñæßÄÉÜÑÆŒœÁÂÀÊÈÍÎÌÓÔÒÖÚÛÙ¡¿^°ÅØåø";
static const uint8_t* font_test_str_ascii = (uint8_t*)(char*)"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!\"%*()-+=:;'?\\/,._";
static const uint8_t* font_test_str_extended = (uint8_t*)(char*)"äáàâëéèêïíìîöóòôüúùûçñæßÄÉÜÑÆŒœÁÂÀÊÈÍÎÌÓÔÒÖÚÛÙ¡¿^°ÅØåø";

static void debug_font_line(int* y, e_font font) {
    int line_height = font_definition_for(font)->line_height;
    if (line_height < 11)
        line_height = 11;
    line_height += 5;
    text_draw(font_test_str_ascii, 5, *y, font, COLOR_MASK_NONE);
    *y += line_height;
    //    text_draw(font_test_str_extended, 5, *y, font, COLOR_MASK_NONE); *y += line_height;
}

void debug_text(painter &ctx, pstr str, int x, int y, int indent, pcstr text, int value, color color, e_font font) {
    text_draw(ctx, (const uint8_t *)string_from_ascii(text), x, y, font, color);
    text_draw(ctx, (uint8_t*)bstring32(value).c_str(), x + indent, y, font, color);
}

void debug_text_a(painter &ctx, pstr str, int x, int y, int indent, pcstr text, color color, e_font font) {
    text_draw(ctx, (const uint8_t *)string_from_ascii(text), x, y, font, color);
}

void debug_text_float(int x, int y, int indent, pcstr text, float value, color color) {
    text_draw(string_from_ascii(text), x, y, FONT_SMALL_OUTLINED, color);
    bstring64 buffer;
    buffer.printf("%0.2f", value);
    text_draw(buffer.data(), x + indent, y, FONT_SMALL_OUTLINED, color);
}

void debug_text_dual_left(int x, int y, int indent, int indent2, pcstr text, int value1, int value2, color color) {
    text_draw(string_from_ascii(text), x, y, FONT_SMALL_OUTLINED, color);
    text_draw_left(bstring32(value1).c_str(), x + indent, y, FONT_SMALL_OUTLINED, color);
    text_draw_left(bstring32(value2).c_str(), x + indent + indent2, y, FONT_SMALL_OUTLINED, color);
}

void debug_draw_line_with_contour(int x_start, int x_end, int y_start, int y_end, color col) {
    g_render.draw_line(vec2i{x_start - 1, x_end - 1}, vec2i{x_start, y_end}, COLOR_BLACK);
    g_render.draw_line(vec2i{x_start + 1, x_end + 1}, vec2i{x_start, y_end}, COLOR_BLACK);
    g_render.draw_line(vec2i{x_start, x_end}, vec2i{y_start - 1, y_end - 1}, COLOR_BLACK);
    g_render.draw_line(vec2i{x_start, x_end}, vec2i{y_start + 1, y_end + 1}, COLOR_BLACK);
    g_render.draw_line(vec2i{x_start, x_end}, vec2i{y_start, y_end}, col);
}

void debug_draw_rect_with_contour(int x, int y, int w, int h, color col) {
    g_render.draw_rect(vec2i{x - 1, y - 1}, vec2i{w, h}, COLOR_BLACK);
    g_render.draw_rect(vec2i{x + 1, y + 1}, vec2i{w, h}, COLOR_BLACK);
    g_render.draw_rect(vec2i{x, y}, vec2i{w - 1, h - 1}, COLOR_BLACK);
    g_render.draw_rect(vec2i{x, y}, vec2i{w + 1, h + 1}, COLOR_BLACK);
    g_render.draw_rect(vec2i{x, y}, vec2i{w, h}, col);
}

void debug_draw_crosshair(int x, int y) {
    g_render.draw_line(vec2i{x, y}, vec2i{x + 10, y}, COLOR_GREEN);
    g_render.draw_line(vec2i{x, y}, vec2i{x, y + 10}, COLOR_RED);
}

void debug_draw_sprite_box(int x, int y, const image_t* img, float scale, color color_mask) {
    int x2 = x - img->animation.sprite_offset.x;
    int y2 = y - img->animation.sprite_offset.y;
    g_render.draw_rect(vec2i(x2 * scale, y2 * scale), vec2i(img->width * scale, img->height * scale), color_mask);
    debug_draw_crosshair((x2 + img->animation.sprite_offset.x) * scale, (y2 + img->animation.sprite_offset.y) * scale);
}

void debug_draw_tile_box(int x, int y, color rect, color bb, int tile_size_x, int tile_size_y) {
    float scale = g_zoom.get_scale();

    int left_x = x;
    int left_y = y + HALF_TILE_HEIGHT_PIXELS;

    int top_x = left_x + (tile_size_y * HALF_TILE_WIDTH_PIXELS);
    int top_y = left_y - (tile_size_y * HALF_TILE_HEIGHT_PIXELS);

    int right_x = top_x + (tile_size_x * HALF_TILE_WIDTH_PIXELS);
    int right_y = top_y + (tile_size_x * HALF_TILE_HEIGHT_PIXELS);

    int bottom_x = left_x + (tile_size_x * HALF_TILE_WIDTH_PIXELS);
    int bottom_y = left_y + (tile_size_x * HALF_TILE_HEIGHT_PIXELS);

    if (rect != COLOR_NULL) {
        g_render.draw_rect(vec2i(x * scale, y * scale), vec2i(TILE_WIDTH_PIXELS * scale, TILE_HEIGHT_PIXELS * scale), rect);
    }

    if (bb != COLOR_NULL) {
        g_render.draw_line(vec2i(left_x * scale, left_y * scale), vec2i(top_x * scale, top_y * scale), bb);
        g_render.draw_line(vec2i(top_x * scale, top_y * scale), vec2i(right_x * scale, right_y * scale), bb);
        g_render.draw_line(vec2i(right_x * scale, right_y * scale), vec2i(bottom_x * scale, bottom_y * scale), bb);
        g_render.draw_line(vec2i(bottom_x * scale, bottom_y * scale), vec2i(left_x * scale, left_y * scale), bb);
    }
}

void debug_draw_tile_top_bb(int x, int y, int height, color color, int size) {
    float scale = g_zoom.get_scale();

    int left_x = x;
    int left_bottom = y + HALF_TILE_HEIGHT_PIXELS;

    int right_x = left_x + (size * HALF_TILE_WIDTH_PIXELS);
    int right_bottom = left_bottom - (size * HALF_TILE_HEIGHT_PIXELS);

    int left_top = left_bottom - height;
    int right_top = right_bottom - height;

    g_render.draw_line(vec2i(left_x * scale, right_x * scale), vec2i(left_bottom * scale, right_bottom * scale), color);
    g_render.draw_line(vec2i(left_x * scale, right_x * scale), vec2i(left_top * scale, right_top * scale), color);

    g_render.draw_line(vec2i(left_x * scale, left_x * scale), vec2i(left_bottom * scale, left_top * scale), color);
    g_render.draw_line(vec2i(right_x * scale, right_x * scale), vec2i(right_bottom * scale, right_top * scale), color);
}

void draw_debug_tile(vec2i pixel, tile2i point, painter &ctx) {
    OZZY_PROFILER_FUNCTION();
    g_debug.draw_tile_render_handlers(pixel, point, ctx);
}

void set_debug_building_id(int bid) {
    debugbuildingid.value = bid;
}

int get_debug_building_id() {
    return debugbuildingid();
}

static xstring g_debug_render_mode_name;

static xstring debug_render_token_leaf(pcstr name) {
    if (!name) {
        return xstring();
    }
    pcstr sep = strstr(name, "::");
    return sep ? sep + 2 : name;
}

e_debug_render debug_render_mode() {
    return (e_debug_render)debugrender.value;
}

void set_debug_render_mode(e_debug_render mode) {
    debugrender.value = mode;
    pcstr name = (mode != e_debug_render_none) ? e_debug_render_tokens.name(mode) : nullptr;
    g_debug_render_mode_name = name ? debug_render_token_leaf(name) : xstring();
}

void set_debug_render_mode_name(const xstring &name) {
    g_debug_render_mode_name = name;
    int mode_id = (int)e_debug_render_none;
    if (!name.empty()) {
        for (int i = e_debug_render_none + 1; i < e_debug_render_size; ++i) {
            pcstr token_name = e_debug_render_tokens.name((e_debug_render)i);
            if (token_name && name == debug_render_token_leaf(token_name)) {
                mode_id = i;
                break;
            }
        }
    }
    debugrender.value = mode_id;
}

xstring debug_render_mode_name() {
    if (!g_debug_render_mode_name.empty()) {
        return g_debug_render_mode_name;
    }

    const e_debug_render mode = debug_render_mode();
    if (mode == e_debug_render_none) {
        return xstring();
    }

    return debug_render_token_leaf(e_debug_render_tokens.name(mode));
}

bstring256 get_terrain_type(pcstr def, tile2i tile) {
    int type = map_terrain_get(tile.grid_offset());

    bstring256 buffer = get_terrain_type(def, type);
    if (type & TERRAIN_BUILDING) {
        bstring32 bstr;
        building *b = building_get(map_building_at(tile));
        bstr.printf("bld:%d,", b ? b->type : -1);
        buffer.append(bstr);
    }

    return buffer;
}

bstring256 get_terrain_type(pcstr def, int type) {
    bstring256 buffer;
    buffer.append(def);
    if (type & TERRAIN_DUNE) buffer.append("dune,");
    if (type & TERRAIN_TREE) buffer.append("tree,");
    if (type & TERRAIN_ROCK) buffer.append("rock,");
    if (type & TERRAIN_WATER) buffer.append("water,");

    if (type & TERRAIN_SHRUB) buffer.append("shrub,");
    if (type & TERRAIN_GARDEN) buffer.append("garden,");
    if (type & TERRAIN_ROAD) buffer.append("road,");
    if (type & TERRAIN_GROUNDWATER) buffer.append("grdwater,");
    if (type & TERRAIN_CANAL) buffer.append("canal,");
    if (type & TERRAIN_ELEVATION) buffer.append("elevat,");
    if (type & TERRAIN_ACCESS_RAMP) buffer.append("ramp,");
    if (type & TERRAIN_MEADOW) buffer.append("meadow,");
    if (type & TERRAIN_RUBBLE) buffer.append("rubble,");
    if (type & TERRAIN_FOUNTAIN_RANGE) buffer.append("fountain,");
    if (type & TERRAIN_WALL) buffer.append("wall,");
    if (type & TERRAIN_GATEHOUSE) buffer.append("gate,");
    if (type & TERRAIN_FLOODPLAIN) buffer.append("flood,");
    if (type & TERRAIN_FERRY_ROUTE) buffer.append("wtrroute,");

    return buffer;
}

ANK_REGISTER_PROPS_ITERATOR(config_show_debug_render_properties);
void config_show_debug_render_properties(bool header) {
    if (header) {
        return;
    }

    xstring current_name = debug_render_mode_name();
    hvector<xstring, 16> mode_names;
    auto add_mode = [&](const xstring &name) {
        if (name.empty()) {
            return;
        }
        for (const auto &existing : mode_names) {
            if (existing == name) {
                return;
            }
        }
        mode_names.push_back(name);
    };

    g_debug.for_each_render_mode_name([&](const xstring &name) {
        add_mode(name);
    });

    for (int i = e_debug_render_none + 1; i < e_debug_render_size; ++i) {
        xstring name = debug_render_token_leaf(e_debug_render_tokens.name((e_debug_render)i));
        if (!name.empty()) {
            add_mode(name);
        }
    }

    int current_index = -1;
    for (int i = 0; i < (int)mode_names.size(); ++i) {
        if (!!current_name && mode_names[i] == current_name) {
            current_index = i;
            break;
        }
    }

    const char *preview = (current_index >= 0) ? mode_names[current_index].c_str() : "None";

    if (ImGui::BeginCombo("Render Mode", preview)) {
        bool is_none_selected = (current_index < 0);
        if (ImGui::Selectable("None", is_none_selected)) {
            set_debug_render_mode(e_debug_render_none);
        }
        if (is_none_selected) {
            ImGui::SetItemDefaultFocus();
        }

        for (int i = 0; i < (int)mode_names.size(); ++i) {
            bool is_selected = (current_index == i);
            if (ImGui::Selectable(mode_names[i].c_str(), is_selected)) {
                set_debug_render_mode_name(mode_names[i]);
            }
            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();
    }
}

console_command::console_command(pcstr name, console_command_fn f) {
    bind_debug_command(name, f);
}

console_var_int::console_var_int(pcstr name, int v) : value(v) {
    bind_debug_console_var_int(name, value);
}

console_ref_int16::console_ref_int16(pcstr name, int16_t &v) : value(&v) {
    bind_debug_console_var_int16(name, v);
}

console_ref_uint8::console_ref_uint8(pcstr name, uint8_t &v) : value(&v) {
    bind_debug_console_var_uint8(name, v);
}

console_ref_int32::console_ref_int32(pcstr name, int &v) : value(&v) {
    bind_debug_console_var_int(name, v);
}

console_ref_float::console_ref_float(pcstr name, float &v) : value(&v) {
    bind_debug_console_var_float(name, v);
}

console_var_bool::console_var_bool(pcstr name, bool v) : value(v) {
    bind_debug_console_var_bool(name, value);
}

console_ref_bool::console_ref_bool(pcstr name, bool &v) : value(&v) {
    bind_debug_console_var_bool(name, v);
}

void game_debug_t::prepare_render_handlers() {
    frame_screen_handler = nullptr;
    frame_tile_handler = nullptr;

    xstring mode_name = debug_render_mode_name();
    if (!mode_name) {
        return;
    }

    auto screen_it = std::find_if(screen_render_handlers.begin(), screen_render_handlers.end(), [mode_name](const screen_handler_t &h) { return h.name == mode_name && h.func; });
    if (screen_it != screen_render_handlers.end()) {
        frame_screen_handler = &screen_it->func;
    }

    auto tile_it = std::find_if(tile_render_handlers.begin(), tile_render_handlers.end(), [mode_name](const tile_handler_t &h) { return h.name == mode_name && h.func; });
    if (tile_it != tile_render_handlers.end()) {
        frame_tile_handler = &tile_it->func;
    }
}

void game_debug_t::add_render_handler(const xstring &name, screen_draw_cb func) {
    if (!func || name.empty()) {
        return;
    }
    for (auto &handler : screen_render_handlers) {
        if (handler.name == name) {
            handler.func = std::move(func);
            return;
        }
    }
    screen_render_handlers.push_back({name, std::move(func)});
}

void game_debug_t::draw_render_handlers(painter &ctx) {
    OZZY_PROFILER_FUNCTION();
    if (frame_screen_handler) {
        (*frame_screen_handler)(ctx);
    }
}

void game_debug_t::add_tile_render_handler(const xstring &name, tile_draw_cb func) {
    if (!func || name.empty()) {
        return;
    }
    for (auto &handler : tile_render_handlers) {
        if (handler.name == name) {
            handler.func = std::move(func);
            return;
        }
    }
    tile_render_handlers.push_back({name, std::move(func)});
}

void game_debug_t::draw_tile_render_handlers(vec2i pixel, tile2i tile, painter &ctx) {
    if (frame_tile_handler) {
        (*frame_tile_handler)(pixel, tile, ctx);
    }
}

void game_debug_t::for_each_render_mode_name(const xfunction<void(const xstring &)> &fn) const {
    for (const auto &handler : screen_render_handlers) {
        if (!handler.name.empty()) {
            fn(handler.name);
        }
    }
    for (const auto &handler : tile_render_handlers) {
        if (!handler.name.empty()) {
            fn(handler.name);
        }
    }
}

void game_debug_t::init() {
    events::subscribe([] (event_debug_render_change ev) {
        int mode = debugrender.value + ev.value;
        if (mode < e_debug_render_none) {
            mode = e_debug_render_size - 1;
        } else if (mode >= e_debug_render_size) {
            mode = e_debug_render_none;
        }
        set_debug_render_mode((e_debug_render)mode);
    });
}
