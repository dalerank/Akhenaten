log_info("akhenaten: water lift window started")

[es=building_info_window]
info_window_water_lift {
    related_buildings [BUILDING_WATER_LIFT]
    ui : baseui(building_info_window, {
        workers_desc  : text({ pos[70, 124 + 20], font: FONT_NORMAL_BLACK_ON_DARK, wrap:px(24), multiline:true })
        warning_text  : text({ pos[32, 46], wrap:px(26), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true })
    })
}

[es=info_window_water_lift_init]
function info_window_water_lift_init(window) {
    var b = city.get_building(window.bid)
    var reason = { group: b.meta_text_id, id: 0 }
    if (b.has_road_access == false) {
        reason = { group: 69, id: 25 }
    } else if (b.num_workers == 0) {
        reason.id = 9
    } else {
        reason.id = b.has_figure(0) ? 2 : 3
    }

    var warning_text = __loc(reason.group, 1)
    if (reason.id) {
        warning_text += " " + __loc(reason)
    }
    window.warning_text.text = warning_text

    var workers_desc = approximate_value(b.worker_percentage / 100.0, [4, 5, 6, 7])
    window.workers_desc.text = __loc(b.meta_text_id, workers_desc)
}
