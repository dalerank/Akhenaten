log_info("akhenaten: ui stonemason guild info window started")

[es=building_info_window]
stonemason_guild_info_window {
    related_buildings [BUILDING_STONEMASONS_GUILD]
    ui : baseui(workshop_info_window, {

    })
}

[es=(stonemason_guild_info_window, init)]
function stonemason_guild_info_window_on_init(window) {
    __log_marker("window_show:stonemason_guild_info_window")
    var b = city.get_building(window.bid)
    var g = b.meta_text_id
    var reason = { group: g, id: 0 }
    if (!b.has_road_access) {
        reason = { group: 69, id: 25 }
    } else if (city.resources.bricks.mothballed) {
        reason.id = 4
    } else if (b.num_workers <= 0) {
        reason.id = 5
    } else if (b.stored_resource(RESOURCE_NONE) < 100) {
        reason.id = 11
    } else {
        reason.id = Math.approximate_value(b.worker_percentage / 100.0, [10, 9, 8, 7, 6])
    }
    window.workers_desc.text = __loc(reason.group, reason.id)
}
