log_info("akhenaten: ui labor priority started")

window labor_priority_window = {
    pos: [(sw(0) - px(23))/2, (sh(0) - px(9))/2]
    ui: {
        background      : outer_panel({ size:[23, 9] })
        title           : header({ pos:[0, 20], size:[px(20), 20], text:{group:50, id:25}, align:"center" })

        btn_areas       : dummy({ pos:[16, 60] })
        btn_priority    : dummy({ pos:[34, 0], size:[30, 30], font:FONT_LARGE_BLACK_ON_LIGHT })

        no_priority     : button({ margin:{centerx:-140, bottom:-40}, text:{group:50, id:26}, size:[280, 25], param:0 })
    }
}
