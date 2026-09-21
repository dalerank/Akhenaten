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

[es=(info_window_hunting_lodge, init)]
function info_window_hunting_lodge_on_init(window) {
    var b = city.get_building(window.bid)
    var reason = "#hunting_lodge_info"
    if (b.has_road_access == false) {
        reason = "#building_no_road_access"
    } else if (b.num_workers <= 0) {
        reason = "#hunting_lodge_no_workers"
    } else if (__city_resource_is_mothballed(RESOURCE_GAMEMEAT)) {
        reason = "#hunting_lodge_mothballed"
    } else if (b.stored_resource(RESOURCE_GAMEMEAT) <= 0) {
        reason = "#hunting_lodge_hunters_seeking"
    }

    window.warning_text.text = __loc(reason)

    var workers_desc = Math.approximate_value(b.worker_percentage / 100.0, [
        "#hunting_lodge_workers_hardly",
        "#hunting_lodge_workers_few",
        "#hunting_lodge_workers_understaffed",
        "#hunting_lodge_workers_below_max",
        "#hunting_lodge_workers_full"
    ])
    window.workers_desc.text = __loc(workers_desc)

    var meat_stored = b.stored_resource(RESOURCE_GAMEMEAT)
    window.resource_amount.text = __loc("#hunting_lodge_stored_meat") + " " + meat_stored
}
