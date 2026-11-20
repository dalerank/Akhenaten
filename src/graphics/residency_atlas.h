#pragma once

#include "core/vec2i.h"

struct SDL_Texture;
struct SDL_Rect;

namespace res_atlas {

namespace detail {
extern bool g_enabled;
extern bool g_redirect;
} // namespace detail

inline bool enabled() {
    return detail::g_enabled;
}

inline bool render_enabled() {
    return detail::g_redirect;
}

bool resolve(SDL_Texture* src, vec2i offset, vec2i size, SDL_Texture*& out_tex, SDL_Rect& out_src);

void register_source(SDL_Texture *tex);
void forget_source(SDL_Texture *tex);

void enable(int size);
void disable();
void reset();
void invalidate();
void set_preview(bool on);
void set_render(bool on);
void set_page_linear(bool linear);
bool page_linear();

void frame_pre_present();

double fill_percent();
double frame_time_ms();

void log_stats();
void dump(const char *filename);

} // namespace res_atlas
