log_info("akhenaten: ui police station info window started")

[es=building_info_window]
info_window_police_station {
    related_buildings [BUILDING_POLICE_STATION]
    ui : baseui(building_info_window, {
        weapon_icon     : resource_icon({ pos[32, 205], resource:RESOURCE_WEAPONS })
        weapon_stored   : text({ pos[55, 210], size[px(27), 20], font:FONT_NORMAL_BLACK_ON_LIGHT })
    })
}

[es=info_window_police_station_init]
function info_window_police_station_on_init(window) {
    var b = city.get_building(window.bid)
    var reason = { group: b.meta_text_id, id: 0 }
    if (b.has_road_access == false) {
        reason = { group: 69, id: 25 }
    } else if (b.num_workers <= 0) {
        reason.id = 9
    } else if (b.has_figure(0)) {
        reason.id = 2
    } else {
        reason.id = 3
    }

    var warning_text = __loc(b.meta_text_id, 1)
    if (reason.id) {
        warning_text += " " + __loc(reason)
    }
    window.warning_text.text = warning_text

    var workers_desc = approximate_value(b.worker_percentage / 100.0, [8, 7, 6, 5, 4])
    window.workers_desc.text = __loc(b.meta_text_id, workers_desc)

    var weapon_amount = b.stored_resource(RESOURCE_WEAPONS)
    window.weapon_stored.text = weapon_amount
}
