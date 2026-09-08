log_info("akhenaten: ui_fishing_wharf_info_window.js loaded")

[es=building_info_window]
info_window_fishing_wharf {
    related_buildings [BUILDING_FISHING_WHARF]
    ui : baseui(building_info_window, {
        resource_img : resource_icon({pos: [32, 186], resource: RESOURCE_FISH}),
        storage_desc : text({pos: [62, 188], size: [px(27), 20], font: FONT_NORMAL_BLACK_ON_LIGHT}),
    })
}

[es=(info_window_fishing_wharf, init)]
function info_window_fishing_wharf_on_init(window) {
    var b = city.get_building(window.bid)
    var gid = b.meta_text_id
    var reason = { group: gid, id: 0 }

    if (!b.has_road_access) {
        reason = { key: "#building_no_road_access" }
    } else if (!b.has_figure(BUILDING_SLOT_BOAT)) {
        reason = { group: gid, id: 2 }
    } else {
        var boat = b.get_figure(BUILDING_SLOT_BOAT)
        switch (boat.action_state) {
        case ACTION_1_FISHING_BOAT_GOING_TO_FISH: reason.id = 3; break
        case ACTION_2_FISHING_BOAT_FISHING: reason.id = 4; break
        case ACTION_3_FISHING_BOAT_GOING_TO_WHARF: reason.id = 5; break
        case ACTION_4_FISHING_BOAT_AT_WHARF: reason.id = 6; break
        case ACTION_5_FISHING_BOAT_RETURNING_WITH_FISH: reason.id = 7; break
        default: reason.id = 8; break
        }
    }

    window.warning_text.text = __loc(reason)
    window.storage_desc.text = _format("Stored fish {0}", b.stored_resource(RESOURCE_FISH))
    building_info_window_setup_advisors(window)
}
