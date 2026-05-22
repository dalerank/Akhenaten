log_info("akhenaten: ui tower info window started")

[es=building_info_window]
info_window_tower {
    related_buildings [BUILDING_MUD_TOWER, BUILDING_BRICK_TOWER]
    ui : baseui(building_info_window, {
    })
}

[es=(info_window_tower, init)]
function info_window_tower_on_init(window) {
    var b = city.get_building(window.bid)
    var gid = b.meta_text_id

    var reason = { group: gid, id: 0 }
    if (b.has_road_access == false) {
        reason = { group: 69, id: 25 }
    } else if (b.num_workers <= 0) {
        reason.id = 2
    } else if (b.has_figure(0)) {
        reason.id = 3
    } else {
        reason.id = 4
    }

    var worker_desc = b.worker_percentage > 0 ? 3 : 2
    window.workers_desc.text = __loc(gid, worker_desc)
    window.warning_text.text = __loc(reason.group, reason.id)
}
