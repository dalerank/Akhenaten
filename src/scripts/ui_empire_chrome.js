log_info("akhenaten: ui empire chrome started")

[es=(empire_window, draw_pause_button), memory=frame]
function empire_window_draw_pause_button(window) {
    var btn = window.button_pause
    btn.tooltip = game.paused ? __loc("#TR_BUTTON_RESUME") : __loc("#TR_BUTTON_PAUSE")

    var p = btn.screen_pos
    var sz = btn.size
    if (game.paused) {
        var tri_h = 17
        var tri_w = ((tri_h + 1) / 2) | 0
        var x0 = p.x + (((sz.x - tri_w) / 2) | 0)
        var y0 = p.y + (((sz.y - tri_h) / 2) | 0)
        var half = ((tri_h - 1) / 2) | 0
        for (var r = 0; r < tri_h; r++) {
            var w = (r <= half) ? (r + 1) : (tri_h - r)
            ui.fill_rect({ x: x0, y: y0 + r }, { x: w, y: 1 }, COLOR_BLACK)
        }
    } else {
        var bar_w = 4
        var bar_h = 18
        var gap = 6
        var total_w = 2 * bar_w + gap
        var x0 = p.x + (((sz.x - total_w) / 2) | 0)
        var y0 = p.y + (((sz.y - bar_h) / 2) | 0)
        ui.fill_rect({ x: x0, y: y0 }, { x: bar_w, y: bar_h }, COLOR_BLACK)
        ui.fill_rect({ x: x0 + bar_w + gap, y: y0 }, { x: bar_w, y: bar_h }, COLOR_BLACK)
    }
}

function empire_window_draw_paneling(window) {
    var sb = empire_window.screen_bounds
    if (!sb.ready) {
        return
    }
    var min_pos = sb.min_pos
    var max_pos = sb.max_pos

    var bottom = get_image(empire_window.bottom_image)
    var hbar = get_image(empire_window.horizontal_bar)
    var vbar = get_image(empire_window.vertical_bar)
    var cross = get_image(empire_window.cross_bar)

    ui.set_clip_rectangle(min_pos, vec2i(max_pos).sub(min_pos))

    for (var x = min_pos.x; x < max_pos.x; x += 70) {
        ui.image(bottom, {x: x, y: max_pos.y - 140})
        ui.image(bottom, {x: x, y: max_pos.y - 100})
        ui.image(bottom, {x: x, y: max_pos.y - 60})
        ui.image(bottom, {x: x, y: max_pos.y - 20})
    }

    for (var x = min_pos.x; x < max_pos.x; x += 86) {
        ui.image(hbar, {x: x, y: min_pos.y})
        ui.image(hbar, {x: x, y: max_pos.y - 140})
        ui.image(hbar, {x: x, y: max_pos.y - 16})
    }

    for (var y = min_pos.y + 16; y < max_pos.y; y += 86) {
        ui.image(vbar, {x: min_pos.x, y: y})
        ui.image(vbar, {x: max_pos.x - 16, y: y})
    }

    ui.image(cross, {x: min_pos.x, y: min_pos.y})
    ui.image(cross, {x: min_pos.x, y: max_pos.y - 140})
    ui.image(cross, {x: min_pos.x, y: max_pos.y - 16})
    ui.image(cross, {x: max_pos.x - 16, y: min_pos.y})
    ui.image(cross, {x: max_pos.x - 16, y: max_pos.y - 140})
    ui.image(cross, {x: max_pos.x - 16, y: max_pos.y - 16})

    ui.reset_clip_rectangle()
}
