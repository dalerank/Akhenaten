log_info("akhenaten: ui health info window started")

[es=building_info_window]
health_info_window {
    first_advisor    : ADVISOR_HEALTH
    related_buildings [BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_DENTIST, BUILDING_MORTUARY]
    ui : baseui(building_info_window, {
    })
}

[es=health_info_window_init]
function health_info_window_on_init(window) {
    var b = city.get_building(window.bid)
    var reason = { group: b.meta_text_id, id: 6 }
    if (b.has_road_access == false) {
        reason = { group: 69, id: 25 }
    } else if (b.has_figure(0)) {
        reason.id = 1
    } else if (b.num_workers <= 0) {
        reason.id = 2
    }

    window.warning_text.text = __loc(reason.group, reason.id)

    var worker_desc = b.worker_percentage > 0 ? 3 : 2
    window.workers_desc.text = __loc(b.meta_text_id, worker_desc)
}
