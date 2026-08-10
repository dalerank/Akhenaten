log_info("akhenaten: ui military academy info window started")

[es=building_info_window]
info_window_milacademy {
    related_buildings [BUILDING_MILITARY_ACADEMY, BUILDING_MILITARY_ACADEMY_2, BUILDING_MILITARY_ACADEMY_3]
    ui : baseui(building_info_window, {
    })
}

[es=(info_window_milacademy, init)]
function info_window_milacademy_on_init(window) {
    var b = city.get_building(window.bid)
    var reason = { group: b.meta_text_id, id: 0 }
    if (b.has_road_access == false) {
        reason = { key: "#building_no_road_access" }
    } else if (b.num_workers <= 0) {
        reason.id = 2
    }

    window.warning_text.text = __loc(reason)

    var worker_desc = b.worker_percentage > 0 ? 1 : 3
    window.workers_desc.text = __loc(b.meta_text_id, worker_desc)
}
