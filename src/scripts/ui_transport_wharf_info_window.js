log_info("akhenaten: ui_transport_wharf_info_window.js loaded")

// OG window_building_draw_transport_wharf / draw_wharf: road check + description (lang 174 id 1) + workers.

[es=building_info_window]
transport_wharf_info_window {
    first_advisor    : ADVISOR_MILITARY
    related_buildings [BUILDING_TRANSPORT_WHARF]
    ui : baseui(building_info_window, {
        background   : outer_panel({size: [29, 16]}),
    })
}

[es=(transport_wharf_info_window, init)]
function transport_wharf_info_window_on_init(window) {
    var b = city.get_building(window.bid)
    var gid = b.meta_text_id
    var reason = { group: gid, id: 1 }

    if (!b.has_road_access) {
        reason = { key: "#building_no_road_access" }
    }

    window.warning_text.text = __loc(reason)
    building_info_window_setup_advisors(window)
}
