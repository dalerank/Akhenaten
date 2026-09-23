#pragma once

#include "graphics/color.h"
#include "core/string.h"
#include "core/hvector.h"
#include "core/typename.h"
#include "core/xfunction.h"
#include "core/xstring.h"
#include "graphics/image.h"
#include "graphics/view/view.h"
#include "graphics/font.h"
#include "core/core.h"
#include "input/hotkey.h"

#include "dev/console_io.h"

#include <functional>

struct painter;

struct event_draw_debug_properties{ int reserved; };

enum e_debug_render {
    e_debug_render_none = 0,
    e_debug_render_overlay_add = 1,

    e_debug_render_size
};

extern int g_debug_figure_id;
void set_debug_building_id(int bid);
int get_debug_building_id();
e_debug_render debug_render_mode();
void set_debug_render_mode(e_debug_render mode);
void set_debug_render_mode_name(const xstring &name);
xstring debug_render_mode_name();

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

bool get_debug_draw_option(int opt);
void set_debug_draw_option(int opt, bool e);

struct console_command {
    console_command(pcstr name, console_command_fn f);
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
#define declare_console_command_p(a) namespace console { bool cmd_##a; }; void cmd_ ##a ##_impl(console_args &, console_output &); console_command a(#a, cmd_ ##a ##_impl); void cmd_ ##a ##_impl(console_args &args, console_output &out)
#define declare_console_var_int(a, v) namespace console { bool var_##a; }; console_var_int a(#a, v);
#define declare_console_ref_int16(a, v) namespace console { bool var_##a; }; console_ref_int16 a(#a, v);
#define declare_console_ref_uint8(a, v) namespace console { bool var_##a; }; console_ref_uint8 a(#a, v);
#define declare_console_ref_int32(a, v) namespace console { bool var_##a; }; console_ref_int32 a(#a, v);
#define declare_console_ref_float(a, v) namespace console { bool var_##a; }; console_ref_float a(#a, v);
#define declare_console_var_bool(a, v) namespace console { bool var_##a; }; console_var_bool a(#a, v);
#define declare_console_ref_bool(a, v) namespace console { bool var_##a; }; console_ref_bool a(#a, v);

namespace debug {

using debug_iterator_function_cb = void(bool);
struct DebugModelTag {};
using PropertiesIterator = FuncLinkedList<debug_iterator_function_cb*, DebugModelTag>;

} // end namespace debug

struct game_debug_t {
    using screen_draw_cb = xfunction<void(painter &)>;
    using tile_draw_cb = xfunction<void(vec2i, tile2i, painter &)>;

    void init();
    void add_render_handler(const xstring &name, screen_draw_cb func);
    void draw_render_handlers(painter &ctx);
    void add_tile_render_handler(const xstring &name, tile_draw_cb func);
    void draw_tile_render_handlers(vec2i pixel, tile2i tile, painter &ctx);
    void for_each_render_mode_name(const xfunction<void(const xstring &)> &fn) const;
    void prepare_render_handlers();

    template<typename T>
    void add_render_handler(screen_draw_cb func) {
        type_name_holder<T> holder;
        add_render_handler(xstring(type_simplified_name(holder.value.data())), std::move(func));
    }

    template<typename T>
    void add_tile_render_handler(tile_draw_cb func) {
        type_name_holder<T> holder;
        add_tile_render_handler(xstring(type_simplified_name(holder.value.data())), std::move(func));
    }

private:
    struct screen_handler_t {
        xstring name;
        screen_draw_cb func;
    };
    struct tile_handler_t {
        xstring name;
        tile_draw_cb func;
    };
    hvector<screen_handler_t, 16> screen_render_handlers;
    hvector<tile_handler_t, 32> tile_render_handlers;

    screen_draw_cb *frame_screen_handler = nullptr;
    tile_draw_cb *frame_tile_handler = nullptr;
};

extern game_debug_t g_debug;

#define ANK_REGISTER_PROPS_ITERATOR(func) void func(bool); \
    namespace debug {int ANK_CONFIG_PULL_VAR_NAME(func) = 1;} \
    static debug::PropertiesIterator ANK_CONFIG_CC1(debug_handler, __LINE__)(func)

