log_info("akhenaten: ui labor priority started")

function show_labor_priority_window(category) {
    labor_priority_window.category = category
    emit event_show_window { id: "labor_priority_window" }
}

[es=modal_window]
labor_priority_window {
    pos: [(sw(0) - px(26))/2, (sh(0) - px(9))/2]
    draw_underlying: true
    allow_rmb_goback: true
    category: 0

    ui: {
        background      : outer_panel({ size:[26, 9] })
        title           : header({ pos:[0, 20], size:[px(20), 20], text:{group:50, id:25}, align:"center" })

        btn_areas       : dummy({ pos:[24, 60] })
        btn_priority    : dummy({ pos:[34, 0], size:[30, 30], font:FONT_LARGE_BLACK_ON_LIGHT })

        no_priority     : button({ margin:{centerx:-140, bottom:-40}, text:{group:50, id:26}, size:[280, 25], onclick_event: "no_priority"})
    }
}

[es=(labor_priority_window, no_priority)]
function no_priority_event() {
    city.labor.set_priority(labor_priority_window.category, 0)
    window_go_back()
}

[es=(labor_priority_window, init)]
function labor_priority_window_init(window) {
}

[es=(labor_priority_window, ui_draw_foreground)]
function labor_priority_window_draw(window) {
    var max_items = city.labor.max_selectable_priority(labor_priority_window.category)
    var areas = window.btn_areas.pos
    var btn = window.btn_priority
    var size = btn.size

    for (var i = 0; i < LABOR_CATEGORY_SIZE; i++) {
        var pos = { x: areas.x + btn.pos.x * i, y: areas.y + btn.pos.y }
        var flags = UiFlags_NoBody | UiFlags_ThinBorder
        if (i >= max_items) {
            flags = flags | UiFlags_Darkened
            flags = flags | UiFlags_Readonly
        }

        if (ui.button({ text: String(i + 1), pos: pos, size: size, font: btn.font, flags: flags }) == ui.button_clicked) {
            city.labor.set_priority(labor_priority_window.category, i + 1)
            window_go_back()
        }

        ui.border({ x: pos.x - 1, y: pos.y - 1 }, { x: size.x + 2, y: size.y + 2 }, 2, COLOR_BLACK, UiFlags_None)
    }
}
