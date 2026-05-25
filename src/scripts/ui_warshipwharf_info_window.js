log_info("akhenaten: ui_warshipwharf_info_window.js loaded")

[es=building_info_window]
warshipwharf_info_window {
    first_advisor    : ADVISOR_MILITARY
    related_buildings [BUILDING_WARSHIP_WHARF]
    ui : baseui(building_info_window, {
        background   : outer_panel({size: [29, 16]}),
        resource_img : resource_icon({pos: [32, 56], resource: RESOURCE_TIMBER}),
        storage_desc : text({pos: [60, 60], size: [px(27), 20], font: FONT_NORMAL_BLACK_ON_LIGHT}),
    })
}

[es=(warshipwharf_info_window, init)]
function warshipwharf_info_window_on_init(window) {
    var b = city.get_building(window.bid)
    var gid = b.meta_text_id
    var reason = { group: gid, id: 0 }

    if (!b.has_road_access) {
        reason = { group: 69, id: 25 }
    } else if (!b.has_figure(BUILDING_SLOT_BOAT)) {
        reason = { group: gid, id: 2 }
    } else {
        var boat = b.get_figure(BUILDING_SLOT_BOAT)
        switch (boat.action_state) {
        case ACTION_203_WARSHIP_MOORED: reason.id = 2; break
        case ACTION_204_WARSHIP_ATTACK: reason.id = 3; break
        default: reason.id = 8; break
        }
    }

    window.warning_text.text = __loc(reason.group, reason.id)
    window.storage_desc.text = _format("Stored weapons {0}", b.stored_resource(RESOURCE_TIMBER))
}
