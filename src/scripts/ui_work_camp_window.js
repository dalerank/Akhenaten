log_info("akhenaten: work camp window started")


[es=building_info_window]
info_window_work_camp {
    related_buildings [BUILDING_WORK_CAMP]
    ui : baseui(building_info_window, {
        workers_desc  : text({ pos[70, 124 + 20], font: FONT_NORMAL_BLACK_ON_DARK, wrap:px(24), multiline:true })
        warning_text  : text({ pos[32, 46], wrap:px(26), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true })
    })
}

[es=info_window_work_camp_init]
function info_window_work_camp_warning_text(window) {
    var b = city.get_building(window.bid)
    var reason = { group:b.meta_text_id, id:0 }
    if (b.has_road_access == false) {
        reason = { group:69, id:25 }
    } else if (b.num_workers == 0) {
        reason.id = 2
    } else if (b.has_figure(0)) {
        var f = b.get_figure(0)
        var dest = f.destination

        if (dest.is_farm) { reason.id = 5 }// working on floodplains
        else if (dest.is_monument) { reason.id = 6 } // working on monuments
        else { reason.id = 4 }
    } else {
        reason.id = 3
    }

    var warning_text = __loc( reason.group, 1)
    if (reason.id) {
        warning_text += __loc(reason)
    }
    window.warning_text.text = warning_text

    var workers_desc = approximate_value(b.worker_percentage / 100.0, [8, 7, 6, 5, 4])
    window.workers_desc.text = __loc(179, workers_desc)
}
