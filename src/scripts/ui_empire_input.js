log_info("akhenaten: ui empire input started")

function empire_window_consume_scroll_remainder(axis) {
    var rem = (axis == "x") ? empire_window.scroll_remainder_x : empire_window.scroll_remainder_y
    var step = (rem >= 0) ? Math.floor(rem) : Math.ceil(rem)
    if (axis == "x") {
        empire_window.scroll_remainder_x = rem - step
    } else {
        empire_window.scroll_remainder_y = rem - step
    }
    return step
}

function empire_window_apply_map_scroll_delta(dx, dy, scale) {
    var s = Math.max(0.001, scale)
    empire_window.scroll_remainder_x += dx / s
    empire_window.scroll_remainder_y += dy / s
    var map_delta = {
        x: empire_window_consume_scroll_remainder("x"),
        y: empire_window_consume_scroll_remainder("y")
    }
    if (map_delta.x || map_delta.y) {
        __empire_map_scroll_map(map_delta)
        // Scroll changed: keep camera.draw_origin in sync for the rest of the frame.
        if (empire_window.camera.valid) {
            empire_window_rebuild_camera()
        }
    }
}

function empire_window_determine_selected_object() {
    var cam = empire_window_camera()
    if (!cam) {
        return
    }
    if (!__mouse.left.went_up || empire_window.finished_scroll || empire_window_is_outside_map(__mouse.x, __mouse.y)) {
        return
    }

    __empire_map_select_object({
        x: Math.max(0, Math.round((__mouse.x - cam.base.x) / cam.scale_safe)),
        y: Math.max(0, Math.round((__mouse.y - cam.base.y) / cam.scale_safe))
    })
}

[es=(empire_window, ui_handle_mouse)]
function empire_window_ui_handle_mouse(window) {
    if (!empire_window.screen_bounds.ready) {
        return
    }
    empire_window_rebuild_camera()
    var m = __mouse
    var scale = empire_window_map_scale()

    if (!m.is_touch && m.left.went_down && !empire_window_is_outside_map(m.x, m.y)) {
        empire_window.left_panning = true
        empire_window.left_pan_travel = 0
        empire_window_set_xy(empire_window.left_pan_last_pos, m.x, m.y)
    }

    if (!m.is_touch && empire_window.left_panning && m.left.is_down) {
        var last = empire_window.left_pan_last_pos
        var dx = m.x - last.x
        var dy = m.y - last.y
        if (dx || dy) {
            empire_window_apply_map_scroll_delta(-dx, -dy, scale)
            empire_window.left_pan_travel += Math.abs(dx) + Math.abs(dy)
            empire_window_set_xy(empire_window.left_pan_last_pos, m.x, m.y)
        }
    }

    if (!m.is_touch && m.left.went_up) {
        empire_window.finished_scroll = empire_window.left_pan_travel > __scroll_config.drag_min_delta ? 1 : 0
        empire_window.left_panning = false
        empire_window.left_pan_travel = 0
    }

    if (!empire_window.left_panning) {
        var position = __scroll_get_delta_empire()
        if (position.x || position.y) {
            empire_window_apply_map_scroll_delta(position.x, position.y, scale)
        }
    }

    if (game_features.gameopt_middle_mouse_camera_pan
        && m.middle.went_down && !empire_window_is_outside_map(m.x, m.y)) {
        __scroll_drag_start(empire_window.drag_source_middle_mouse_pan)
    }

    if (m.is_touch) {
        var tp = __touch_earliest_current()
        if (!empire_window_is_outside_map(tp.x, tp.y)) {
            if (__touch_earliest_has_started()) {
                __scroll_drag_start(empire_window.drag_source_touch)
            }
        }
        if (__touch_earliest_has_ended()) {
            empire_window.finished_scroll = __touch_earliest_was_click() ? 0 : 1
            __scroll_drag_end()
        }
    }

    if (m.middle.went_up) {
        __scroll_drag_end()
    }

    empire_window_determine_selected_object()
    empire_window.finished_scroll = 0
}
