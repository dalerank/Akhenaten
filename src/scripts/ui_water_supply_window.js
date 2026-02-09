log_info("akhenaten: water supply window started")

[es=building_info_window]
info_window_water_supply {
    related_buildings [BUILDING_WATER_SUPPLY]
    ui : baseui(building_info_window, {
        workers_desc  : text({ pos[70, 124 + 20], font: FONT_NORMAL_BLACK_ON_DARK, wrap:px(24), multiline:true })
        warning_text  : text({ pos[32, 46], wrap:px(26), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true })
    })
}

[es=info_window_water_supply_init]
function info_window_water_supply_warning_text(window) {
    var b = city.get_building(window.bid)
    var reason = { group:b.meta_text_id, id:1 }
    var workers = { group:b.meta_text_id, id:0 }

    if (b.has_road_access == false) {
        reason = { group:69, id:25 }
    } else {
        workers.id = approximate_value(b.worker_percentage / 100.0, [7, 5, 4, 3, 2])
    }

    window.warning_text.text = __loc(reason.group, reason.id)
    window.workers_desc.text = __loc(workers.group, workers.id)

    // Set workers_text similar to draw_employment_details_ui
    var workers_text = b.num_workers + " " + __loc(8, 12) + " (" + b.max_workers + " " + __loc(69, 0) + ")"
    window.workers_text.text = workers_text
}
