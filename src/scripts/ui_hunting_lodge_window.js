log_info("akhenaten: ui hunting lodge window started")

[es=building_info_window]
info_window_hunting_lodge {
    related_buildings [BUILDING_HUNTING_LODGE]
    ui : baseui(building_info_window, {
        background     : outer_panel({size: [29, 20]}),
        resource       : resource_icon({ pos:[10, 10], resource:RESOURCE_GAMEMEAT }),
        resource_amount : text({ pos:[62, 186 + 2], font: FONT_NORMAL_BLACK_ON_LIGHT }),
    })
}

[es=info_window_hunting_lodge_init]
function info_window_hunting_lodge_on_init(window) {
    var b = city.get_building(window.bid)
    var reason = { group: b.meta_text_id, id: 0 }
    if (b.has_road_access == false) {
        reason = { group: 69, id: 25 }
    } else if (b.num_workers <= 0) {
        reason.id = 5
    } else if (__city_resource_is_mothballed(RESOURCE_GAMEMEAT)) {
        reason.id = 4
    } else if (b.stored_resource(RESOURCE_GAMEMEAT) <= 0) {
        reason.id = 11
    }

    window.warning_text.text = __loc(reason.group, reason.id)

    var workers_desc = approximate_value(b.worker_percentage / 100.0, [10, 9, 8, 7, 6])
    window.workers_desc.text = __loc(b.meta_text_id, workers_desc)

    var meat_stored = b.stored_resource(RESOURCE_GAMEMEAT)
    window.resource_amount.text = __loc(b.meta_text_id, 13) + " " + meat_stored
}
