#pragma once

#include "graphics/color.h"
#include "core/string.h"
#include "graphics/image.h"
#include "graphics/view/view.h"
#include "graphics/font.h"
#include "core/core.h"
#include "input/hotkey.h"

#include <functional>
#include <iosfwd>
#include <iomanip>

extern int debug_range_1;
extern int debug_range_2;
extern int debug_range_3;
extern int debug_range_4;

enum e_debug_option {
    e_debug_show_floods,
    e_debug_show_properties,
    e_debug_show_console,
    e_debug_make_screenshot,
    e_debug_make_full_screenshot,
    e_debug_write_video,

    e_debug_opt_size,
};

enum e_debug_render {
    e_debug_render_none = 0,
    e_debug_render_building = 1,
    e_debug_render_tilesize = 2,
    e_debug_render_roads = 3,
    e_debug_render_routing_dist = 4,
    e_debug_render_routing_grid = 5,
    e_debug_render_moisture = 6,
    e_debug_render_grass_level = 7,
    e_debug_render_grass_soil_depletion = 8,
    e_debug_render_grass_flood_order = 9,
    e_debug_render_grass_flood_flags = 10,
    e_debug_render_labor = 11,
    e_debug_render_sprite_frames = 12,
    e_debug_render_terrain_bits = 13,
    e_debug_render_image = 14,
    e_debug_render_image_alt = 15,
    e_debug_render_marshland = 16,
    e_debug_render_terrain_type = 17,
    e_debug_render_soil = 18,
    e_debug_render_unk_19,
    e_debug_render_tile_pos = 20,
    e_debug_render_floodplain_shore = 21,
    e_debug_render_tile_toph = 22,
    e_debug_render_monuments = 23,
    e_debug_render_figures = 24,
    e_debug_render_height = 25,
    e_debug_render_vegetation_growth = 26,
    e_debug_render_damage = 27,
    e_debug_render_desirability = 28,
    e_debug_render_river_shore = 29,
    e_debug_render_overall_entertainment = 30,
    e_debug_render_canals = 31,
    e_debug_render_overlay_add = 32,
    e_debug_render_gardens = 33,
    e_debug_render_routing_noncitizen = 34,
    e_debug_render_routing_amphibia = 35,
    e_debug_render_routing_water = 36,
    e_debug_render_invasion_point = 37,
    e_debug_render_tile_random = 38,
    e_debug_render_soldier_strength = 39,
    e_debug_render_malaria_risk = 40,
    e_debug_render_animal_spawn = 41,
    e_debug_render_animal_spawn_area = 42,
    e_debug_render_sandstone = 43,
    e_debug_render_stone = 44,

    e_debug_render_size
};

extern int g_debug_figure_id;
void set_debug_building_id(int bid);
int get_debug_building_id();
e_debug_render debug_render_mode();
void set_debug_render_mode(e_debug_render mode);

bstring256 get_terrain_type(pcstr def, tile2i tile);
bstring256 get_terrain_type(pcstr def, int type);

void debug_text(painter &ctx, pstr str, int x, int y, int indent, pcstr text, int value, color color = COLOR_WHITE, e_font font = FONT_SMALL_OUTLINED);
void debug_text_a(painter &ctx, pstr str, int x, int y, int indent, pcstr text, color color = COLOR_WHITE, e_font font = FONT_SMALL_OUTLINED);
void debug_text_float(int x, int y, int indent, pcstr text, float value, color color = COLOR_WHITE);
void debug_text_dual_left(int x, int y, int indent, int indent2, pcstr text, int value1, int value2, color color = COLOR_WHITE);

void debug_draw_line_with_contour(int x_start, int x_end, int y_start, int y_end, color col);
void debug_draw_rect_with_contour(int x, int y, int w, int h, color col);

void debug_draw_crosshair(int x, int y);
void debug_draw_sprite_box(int x, int y, const image_t* img, float scale, color color_mask);
void debug_draw_tile_box(int x, int y, color rect, color bb, int tile_size_x = 1, int tile_size_y = 1);
void debug_draw_tile_top_bb(int x, int y, int height, color color, int size = 1);

void draw_debug_tile(vec2i pixel, tile2i point, painter &ctx);
void draw_debug_animal_spawn_areas(painter &ctx);

void draw_debug_ui(int x, int y);

bool get_debug_draw_option(int opt);
void set_debug_draw_option(int opt, bool e);

struct console_command {
    console_command(pcstr name, std::function<void(std::istream &is, std::ostream &os)> f);
};

struct console_var_int {
    int value;
    console_var_int(pcstr name, int init);
    int operator()() const { return value; }
};

struct console_ref_int16 {
    int16_t *value;
    console_ref_int16(pcstr name, int16_t &v);
    int operator()() const { return *value; }
};

struct console_ref_uint8 {
    uint8_t *value;
    console_ref_uint8(pcstr name, uint8_t &v);
    int operator()() const { return *value; }
};

struct console_ref_int32 {
    int *value;
    console_ref_int32(pcstr name, int &v);
    int operator()() const { return *value; }
};

struct console_ref_float {
    float *value;
    console_ref_float(pcstr name, float &v);
    float operator()() const { return *value; }
};

struct console_var_bool {
    bool value;
    console_var_bool(pcstr name, bool init);
    bool operator()() const { return value; }
    bool operator!() const { return !value; }
};

struct console_ref_bool {
    bool *value;
    console_ref_bool(pcstr name, bool &var);
    bool operator()() const { return *value; }
};

#define declare_console_command(a, ...) namespace console { bool cmd_##a; }; console_command a(#a, __VA_ARGS__);
#define declare_console_command_p(a) namespace console { bool cmd_##a; }; void cmd_ ##a ##_impl(std::istream &, std::ostream &); console_command a(#a, cmd_ ##a ##_impl); void cmd_ ##a ##_impl(std::istream &is, std::ostream &os)
#define declare_console_var_int(a, v) namespace console { bool var_##a; }; console_var_int a(#a, v);
#define declare_console_ref_int16(a, v) namespace console { bool var_##a; }; console_ref_int16 a(#a, v);
#define declare_console_ref_uint8(a, v) namespace console { bool var_##a; }; console_ref_uint8 a(#a, v);
#define declare_console_ref_int32(a, v) namespace console { bool var_##a; }; console_ref_int32 a(#a, v);
#define declare_console_ref_float(a, v) namespace console { bool var_##a; }; console_ref_float a(#a, v);
#define declare_console_var_bool(a, v) namespace console { bool var_##a; }; console_var_bool a(#a, v);
#define declare_console_ref_bool(a, v) namespace console { bool var_##a; }; console_ref_bool a(#a, v);

inline std::istream& operator>>(std::istream& is, bstring128& arg) {
    char tmp[bstring128::capacity];
    is >> std::setw(bstring128::capacity) >> tmp;
    arg = tmp;
    return is;
}

namespace debug {

using debug_iterator_function_cb = void(bool);
using PropertiesIterator = FuncLinkedList<debug_iterator_function_cb*>;

} // end namespace debug

struct game_debug_t {
    void init();
};

extern game_debug_t g_debug;

#define ANK_REGISTER_PROPS_ITERATOR(func) void func(bool); \
    namespace debug {int ANK_CONFIG_PULL_VAR_NAME(func) = 1;} \
    static debug::PropertiesIterator ANK_CONFIG_CC1(debug_handler, __LINE__)(func)

