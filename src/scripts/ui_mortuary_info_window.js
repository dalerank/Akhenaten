log_info("akhenaten: mortuary info window started")

mortuary_info_window {
    ui : baseui(building_info_window, {
        warning_text   : text({ pos:[28, 40], wrap:px(27), font: FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),
        resource_icon  : resource_icon({ pos:[32, 56], resource:RESOURCE_LINEN }),
        resource_stored : text({ pos:[60, 60], size:[px(27), 20], font: FONT_NORMAL_BLACK_ON_LIGHT }),
        workers_desc   : text({ pos:[70, 116 + 16], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(24) }),
    })
}

[es=building_info_window]
info_window_mortuary {
    related_buildings [BUILDING_MORTUARY]
    ui : baseui(mortuary_info_window, {
    })
}

[es=info_window_mortuary_init]
function info_window_mortuary_on_init(window) {
    var b = city.get_building(window.bid)
    var group = b.meta_text_id

    window.warning_text.text = __loc(group, 1)

    window.resource_icon.image = RESOURCE_LINEN

    var linen_stored = b.first_material_stored != null ? b.first_material_stored : 0
    window.resource_stored.text = __loc(group, 7) + " " + linen_stored

    var reason = { group: group, id: 0 }
    if (b.has_road_access == false) {
        reason = { group: 69, id: 25 }
    } else if (b.num_workers <= 0) {
        reason.id = 4
    } else if (linen_stored < 100) {
        reason.id = 2
    } else {
        reason.id = 3
    }

    window.workers_desc.text = __loc(reason.group, reason.id)
}
