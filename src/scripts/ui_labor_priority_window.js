log_info("akhenaten: ui labor priority started")

function show_labor_priority_window(category) {
    labor_priority_window.category = category
    emit event_show_window { id: "labor_priority_window" }
}

[es=modal_window]
labor_priority_window {
    pos: [(sw(0) - px(23))/2, (sh(0) - px(9))/2]
    draw_underlying: true
    allow_rmb_goback: true
    category: 0

    ui: {
        background      : outer_panel({ size:[23, 9] })
        title           : header({ pos:[0, 20], size:[px(20), 20], text:{group:50, id:25}, align:"center" })

        btn_areas       : dummy({ pos:[16, 60] })
        btn_priority    : dummy({ pos:[34, 0], size:[30, 30], font:FONT_LARGE_BLACK_ON_LIGHT })

        no_priority     : button({ margin:{centerx:-140, bottom:-40}, text:{group:50, id:26}, size:[280, 25] })
    }
}

[es=(labor_priority_window, init)]
function labor_priority_window_init(window) {
    window.category = labor_priority_window.category

    window.no_priority.onclick = function() {
        city.labor.set_priority(window.category, 0)
        window_go_back()
    }
}

[es=(labor_priority_window, ui_draw_foreground)]
function labor_priority_window_draw(window) {
    var category = window.category
    var max_items = city.labor.max_selectable_priority(category)
    var areas = window.btn_areas.screen_pos
    var btn = window.btn_priority
    var size = btn.size

    for (var i = 0; i < LABOR_CATEGORY_SIZE; i++) {
        var pos = { x: areas.x + btn.pos.x * i, y: areas.y + btn.pos.y }
        var flags = UiFlags_NoBody | UiFlags_ThinBorder
        if (i >= max_items) {
            flags = flags | UiFlags_Darkened
        }

        if (__ui_draw_button(String(i + 1), pos, size, btn.font, flags, "")) {
            city.labor.set_priority(category, i + 1)
            window_go_back()
        }

        ui.border({ x: pos.x - 1, y: pos.y - 1 }, { x: size.x + 2, y: size.y + 2 }, 2, COLOR_BLACK, UiFlags_None)
    }
}
