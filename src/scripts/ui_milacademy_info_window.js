log_info("akhenaten: ui military academy info window started")

[es=building_info_window]
info_window_milacademy {
    first_advisor : ADVISOR_MILITARY
    related_buildings [BUILDING_MILITARY_ACADEMY, BUILDING_MILITARY_ACADEMY_2, BUILDING_MILITARY_ACADEMY_3]
    ui : baseui(building_info_window, {
    })
}

[es=(info_window_milacademy, init)]
function info_window_milacademy_on_init(window) {
    var b = city.get_building(window.bid)
    // OG group 135: 0 description (understaffed), 2 no staff, 3 training (full).
    var reason = { group: b.meta_text_id, id: 0 }
    if (b.has_road_access == false) {
        reason = { key: "#building_no_road_access" }
    } else if (b.num_workers < 1) {
        reason.id = 2
    } else if (b.num_workers >= b.max_workers) {
        reason.id = 3
    }

    window.warning_text.text = __loc(reason)

    var worker_desc = b.worker_percentage > 0 ? 1 : 3
    window.workers_desc.text = __loc(b.meta_text_id, worker_desc)
    building_info_window_setup_advisors(window)
}
