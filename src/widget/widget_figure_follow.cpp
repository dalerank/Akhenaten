#include "widget_figure_follow.h"

#include "city/city_figures.h"
#include "city/city_warnings.h"
#include "game/game_events.h"
#include "core/log.h"
#include "core/profiler.h"
#include "core/system_time.h"
#include "dev/debug.h"
#include "figure/figure.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/ui.h"
#include "graphics/graphics.h"
#include "graphics/screen.h"
#include "input/mouse.h"
#include "input/hotkey.h"
#include "widget/widget_sidebar.h"
#include "window/window_city.h"

#include <algorithm>

declare_console_var_int(figure_follow_refresh_ms, 200)
declare_console_var_int(figure_follow_size, 160)
declare_console_var_int(figure_follow_offset_x, 0)
declare_console_var_int(figure_follow_offset_y, 0)

figure_follow_t g_figure_follow;

namespace {

    constexpr int k_panel_pad = 8;
    constexpr int k_panel_margin = 8;
    constexpr int k_panel_top_margin = 40;
    constexpr int k_panel_block = 16;
    constexpr int k_panel_header = 24;
    constexpr int k_panel_footer = 28;
    constexpr int k_min_snapshot_size = 48;
    constexpr int k_min_refresh_ms = 50;
    constexpr int k_slow_capture_ms = 8;
    constexpr uint32_t k_slow_log_cooldown_ms = 5000;

    int snapshot_size() {
        return std::max(k_min_snapshot_size, figure_follow_size());
    }

} // namespace

vec2i figure_follow_t::panel_size() const {
    const int s = snapshot_size();
    return {s + 2 * k_panel_pad, s + k_panel_header + k_panel_footer};
}

void figure_follow_t::ensure_panel_pos() {
    const vec2i sz = panel_size();
    const vec2i screen{screen_width(), screen_height()};
    const int sidebar_x = widget_sidebar_city_offset_x();

    // The position is derived from all three, so all three have to invalidate it: a
    // height-only resize leaves the sidebar where it was, and figure_follow_size can change
    // the panel size under a cached position.
    if (panel_pos_set_ && last_sidebar_x_ == sidebar_x && last_screen_size_ == screen
        && last_panel_size_ == sz) {
        return;
    }

    panel_pos_ = {sidebar_x - sz.x - k_panel_margin, screen.y - sz.y - k_panel_margin};
    // Keep the whole panel on screen, top-left last so it wins on a screen smaller than it.
    panel_pos_.x = std::min(panel_pos_.x, screen.x - sz.x - k_panel_margin);
    panel_pos_.y = std::min(panel_pos_.y, screen.y - sz.y - k_panel_margin);
    panel_pos_.x = std::max(panel_pos_.x, k_panel_margin);
    panel_pos_.y = std::max(panel_pos_.y, k_panel_top_margin);

    panel_pos_set_ = true;
    last_sidebar_x_ = sidebar_x;
    last_screen_size_ = screen;
    last_panel_size_ = sz;
}

rect figure_follow_t::panel_rect() {
    ensure_panel_pos();
    return {panel_pos_, panel_pos_ + panel_size()};
}

rect figure_follow_t::stop_button_rect() {
    ensure_panel_pos();
    const vec2i sz = panel_size();
    const vec2i pos = panel_pos_ + vec2i{k_panel_pad, sz.y - k_panel_footer + 2};
    // small_panel_draw() paints whole 16px blocks, so the clickable width has to be the width
    // that actually gets drawn -- otherwise the hit area sticks out past the button.
    return {pos, pos + vec2i{stop_button_blocks() * k_panel_block, 22}};
}

int figure_follow_t::stop_button_blocks() const {
    return std::max(1, (panel_size().x - 2 * k_panel_pad) / k_panel_block);
}

bool figure_follow_t::target_still_valid() const {
    if (!enabled_ || figure_id_ <= 0) {
        return false;
    }

    figure* f = figure_get(figure_id_);
    return f && f->is_alive() && f->type == type_;
}

void figure_follow_t::stop(bool toast_lost) {
    if (!enabled_ && !snapshot_.valid()) {
        return;
    }

    snapshot_.reset();
    enabled_ = false;
    figure_id_ = 0;
    type_ = FIGURE_NONE;
    last_capture_ms_ = 0;
    panel_pos_set_ = false;
    last_sidebar_x_ = -1;

    if (toast_lost) {
        events::emit(event_city_warning{"#warning_follow_walker_lost"});
    }
}

bool figure_follow_t::start(int figure_id) {
    figure* f = figure_get(figure_id);
    if (!f || !f->is_alive()) {
        return false;
    }

    const bool same_target = (enabled_ && figure_id_ == figure_id);
    stop(false);
    if (same_target) {
        return false;
    }

    enabled_ = true;
    figure_id_ = figure_id;
    type_ = f->type;
    // The snapshot itself is taken from the city draw path, never from input handling.
    return true;
}

void figure_follow_t::capture_if_due() {
    if (!enabled_) {
        return;
    }

    if (!target_still_valid()) {
        stop(true);
        return;
    }

    const time_millis now = time_get_millis();
    const time_millis refresh = (time_millis)std::max(k_min_refresh_ms, figure_follow_refresh_ms());
    if (last_capture_ms_ && (now - last_capture_ms_) < refresh) {
        return;
    }

    OZZY_PROFILER_FUNCTION();
    const int size = snapshot_size();
    const vec2i offset
      = figure_snapshot::centered_offset(size) + vec2i{figure_follow_offset_x(), figure_follow_offset_y()};
    snapshot_.capture(figure_id_, size, offset);

    last_capture_ms_ = time_get_millis();
    const time_millis dt = last_capture_ms_ - now;
    if (dt > (time_millis)k_slow_capture_ms && (last_capture_ms_ - last_slow_log_ms_) > k_slow_log_cooldown_ms) {
        logs::info("figure_follow: capture %d ms", (int)dt);
        last_slow_log_ms_ = last_capture_ms_;
    }
}

void figure_follow_t::draw_panel() {
    if (!enabled_ || !window_is_city_view()) {
        return;
    }

    if (!target_still_valid()) {
        stop(true);
        return;
    }

    if (!snapshot_.valid()) {
        return;
    }

    ensure_panel_pos();
    const vec2i sz = panel_size();
    const int img = snapshot_size();

    outer_panel_draw_exact(panel_pos_, sz);
    graphics_draw_from_texture(snapshot_.texture_id(), panel_pos_ + vec2i{k_panel_pad, k_panel_header}, {img, img});

    figure* f = figure_get(figure_id_);
    if (f) {
        ui::label(f->name.c_str(), panel_pos_ + vec2i{k_panel_pad, 6}, FONT_NORMAL_BLACK_ON_LIGHT);
    }

    const rect stop_button = stop_button_rect();
    small_panel_draw(stop_button.mn, stop_button_blocks(), 1);
    ui::label(lang_text_from_key("#stop_following"), stop_button.mn + vec2i{4, 4}, FONT_NORMAL_BLACK_ON_DARK);
}

bool figure_follow_t::handle_mouse(const mouse* m) {
    if (!enabled_ || !m || !window_is_city_view()) {
        return false;
    }

    const vec2i mp{m->x, m->y};
    if (!panel_rect().inside(mp)) {
        return false;
    }

    if (m->left.went_up && stop_button_rect().inside(mp)) {
        stop(false);
    }

    // Any pointer activity over the panel must not fall through to the city.
    return true;
}

bool figure_follow_t::handle_escape(const hotkeys* h) {
    if (!h || !h->escape_pressed || !enabled_ || !window_is_city_view()) {
        return false;
    }

    stop(false);
    return true;
}
