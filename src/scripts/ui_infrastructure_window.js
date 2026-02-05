log_info("akhenaten: ui_infrastructure_window.js loaded")

[es=building_info_window]
infrastructure_common_info_window {
    related_buildings [BUILDING_FIREHOUSE]
    ui : baseui(building_info_window, {

    })
}

[es=infrastructure_common_info_window_init]
function infrastructure_common_info_window_init(window) {
    var b = city.get_building(window.bid)
    var meta_text_id = b.meta_text_id
    var reason = { group: 0, id: 0 }

    window.warning_text.text = __loc(meta_text_id, 1)

    if (b.has_road_access == false) {
        reason = { group: 69, id: 25 }
    } else if (b.num_workers <= 0) {
        reason = { group: meta_text_id, id: 9 }
    } else {
        reason.group = meta_text_id
        reason.id = approximate_value(b.worker_percentage / 100.0, [8, 7, 6, 5, 4])
    }

    if (reason.group) {
        window.workers_desc.text = ""
        window.workers_desc.text = __loc(reason.group, reason.id)
    }
}