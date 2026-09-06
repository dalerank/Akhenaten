#pragma once

#include "core/system_time.h"
#include "figure/figure_type.h"
#include "grid/point.h"
#include "widget/figure_snapshot.h"

struct mouse;
struct hotkeys;

// Picture-in-picture panel that follows one walker over the city view: keeps a fresh snapshot
// of it and stops on its own once the walker is gone.
struct figure_follow_t {
    // Starting on the walker already followed toggles the panel off. Returns true when a new
    // follow began.
    bool start(int figure_id);
    void stop(bool toast_lost = false);

    bool enabled() const { return enabled_; }
    int figure_id() const { return figure_id_; }
    int texture_id() const { return snapshot_.texture_id(); }

    // Refreshes the snapshot once the refresh interval elapsed. Must be called from the city
    // draw path -- see figure_snapshot.
    void capture_if_due();

    void draw_panel();
    bool handle_mouse(const mouse* m);
    bool handle_escape(const hotkeys* h);

private:
    bool target_still_valid() const;
    vec2i panel_size() const;
    void ensure_panel_pos();
    rect panel_rect();
    rect stop_button_rect();

    figure_snapshot snapshot_;
    bool enabled_ = false;
    int figure_id_ = 0;
    e_figure_type type_ = FIGURE_NONE;
    time_millis last_capture_ms_ = 0;
    time_millis last_slow_log_ms_ = 0;
    vec2i panel_pos_ = {-1, -1};
    bool panel_pos_set_ = false;
    int last_sidebar_x_ = -1;
};

extern figure_follow_t g_figure_follow;
