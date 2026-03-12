#pragma once

#include "core/vec2i.h"
#include "graphics/color.h"
#include <type_traits>
#include <vector>
#include "core/hvector.h"
#include "graphics/font.h"
#include "graphics/animkeys.h"

struct painter;
struct image_t;
struct image_desc;

void graphics_set_to_dialog();
void graphics_in_dialog_with_size(int width, int height);
void graphics_reset_dialog();

void graphics_set_clip_rectangle(vec2i pos, vec2i size);
bool graphics_inside_clip_rectangle(vec2i pos);
rect graphics_clip_rectangle();
void graphics_reset_clip_rectangle();

void graphics_draw_line(vec2i start, vec2i end, color color);
void graphics_draw_vertical_line(vec2i start, int ny, color color);
void graphics_draw_horizontal_line(vec2i start, int nx, color color);
void graphics_draw_pixel(vec2i pixel, color color);
void graphics_draw_rect(vec2i start, vec2i size, color color);
void graphics_draw_inset_rect(vec2i start, vec2i size);

void graphics_shade_rect(vec2i start, vec2i size, int darkness);

int graphics_save_to_texture(int image_id, vec2i pos, vec2i size);
void graphics_clear_saved_texture(int image_id, color clr);
void graphics_delete_saved_texture(int image_id);
void graphics_draw_from_texture(int image_id, vec2i pos, vec2i size);

enum ImgFlag_ {
    ImgFlag_None = 0,
    ImgFlag_Alpha = (1 << 1),
    ImgFlag_Grayscale = (1 << 2),
    ImgFlag_Mirrored = (1 << 3),
    ImgFlag_InternalOffset = (1 << 4),
    ImgFlag_Debug = (1 << 5),
};

using ImgFlags = uint32_t;

struct render_command_t {
    enum e_render_type : uint8_t {
        ert_none = 0,
        ert_drawtile = 1,
        ert_drawtile_top = 2,
        ert_drawtile_full = 3,
        ert_generic = 4,
        ert_sprite = 5,
        ert_ornament = 6,
        ert_from_below = 7,
        ert_draw_rect = 8,
    };
    e_render_type rtype = ert_none;
    bool use_sort_pixel = false;
    int32_t image_id = 0;
    int32_t base_id = 0;
    vec2i size = {};
    uint32_t mask = COLOR_MASK_NONE;
    float scale = 1.f;
    uint32_t flags = 0;
    uint32_t id = 0;
    uint32_t tag = 0;
    vec2i pixel = {};
    vec2i sort_pixel = {};
    pcstr location = nullptr;

    int start_subcommand = -1;
    int finish_subcommand = -1;
};
static_assert(std::is_trivially_copyable_v<render_command_t>, "render_command_t must be trivially copyable");

namespace render_cmd {
    struct Pixel { vec2i value; };
    struct SortPixel { vec2i value; };
    struct Size { vec2i value; };
    struct ImageId { int32_t value; };
    struct BaseId { int32_t value; };
    struct Mask { uint32_t value; };
    struct Scale { float value; };
    struct Flags { uint32_t value; };
    struct Location { pcstr value; };
    struct UseSortPixel { bool value; };
    struct StartSubcommand { int value; };
    struct FinishSubcommand { int value; };
}

namespace ImageDraw {

void img_background(painter &ctx, int image_id, float scale = 1.0f, vec2i offset = {0, 0});

void apply_render_commands(painter& ctx, std::string_view p);
void execute_render_command(painter& ctx, const render_command_t& command);
void finalize_render(painter &ctx);
void clear_render_commands();
render_command_t& create_command(painter& ctx, render_command_t::e_render_type rt);
render_command_t& create_dcommand(render_command_t::e_render_type rt);
render_command_t& active_command(painter& ctx);
render_command_t& create_subcommand(painter& ctx, render_command_t::e_render_type rt);

inline void apply(render_command_t& cmd, const render_cmd::Pixel& p) { cmd.pixel = p.value; }
inline void apply(render_command_t& cmd, const render_cmd::SortPixel& p) { cmd.sort_pixel = p.value; }
inline void apply(render_command_t& cmd, const render_cmd::Size& s) { cmd.size = s.value; }
inline void apply(render_command_t& cmd, const render_cmd::ImageId& id) { cmd.image_id = id.value; }
inline void apply(render_command_t& cmd, const render_cmd::BaseId& id) { cmd.base_id = id.value; }
inline void apply(render_command_t& cmd, const render_cmd::Mask& m) { cmd.mask = m.value; }
inline void apply(render_command_t& cmd, const render_cmd::Scale& s) { cmd.scale = s.value; }
inline void apply(render_command_t& cmd, const render_cmd::Flags& f) { cmd.flags = f.value; }
inline void apply(render_command_t& cmd, const render_cmd::Location& loc) { cmd.location = loc.value; }
inline void apply(render_command_t& cmd, const render_cmd::UseSortPixel& u) { cmd.use_sort_pixel = u.value; }
inline void apply(render_command_t& cmd, const render_cmd::StartSubcommand& s) { cmd.start_subcommand = s.value; }
inline void apply(render_command_t& cmd, const render_cmd::FinishSubcommand& f) { cmd.finish_subcommand = f.value; }

template<typename... Args>
render_command_t& push(painter& ctx, render_command_t::e_render_type rt, const Args&... args) {
    render_command_t& cmd = create_command(ctx, rt);
    (apply(cmd, args), ...);
    return cmd;
}

template<typename... Args>
render_command_t &push_sub(painter &ctx, render_command_t::e_render_type rt, const Args&... args) {
    render_command_t &cmd = create_subcommand(ctx, rt);
    (apply(cmd, args), ...);
    return cmd;
}

template<typename... Args>
render_command_t &push_d(render_command_t::e_render_type rt, const Args&... args) {
    render_command_t &cmd = create_dcommand(rt);
    (apply(cmd, args), ...);
    return cmd;
}

template<typename... Args>
render_command_t& sprite(painter& ctx, const Args&... args) {
    return push(ctx, render_command_t::ert_sprite, args...);
}

template<typename... Args>
render_command_t& generic_sub(painter& ctx, const Args&... args) {
    return push_sub(ctx, render_command_t::ert_generic, args...);
}

using render_command_vec = std::vector<render_command_t>;
using render_command_block = hvector<render_command_vec, 32>;
/// Merge per-block buffers into g_render_commands/g_render_subcommands (fixes subcommand indices). Call from main thread after workers finish.
void merge_block_commands_into_global(const render_command_block& block_commands,
                                      const render_command_block & block_subcommands);

} // namespace ImageDraw