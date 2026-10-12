log_info("akhenaten: ui ferry info window started")

[es=building_info_window]
info_window_ferry {
    related_buildings [BUILDING_FERRY]
    ui : baseui(building_info_window, {
        background : outer_panel({size: [29, 20]}),
    })
}

[es=(info_window_ferry, init)]
function info_window_ferry_on_init(window) {
    var b = city.get_building(window.bid)
    if (!b) {
        return
    }

    var gid = b.meta_text_id
    var partner_id = __ferry_partner_id(b.id)
    var reason_id = 0

    if (!partner_id) {
        reason_id = 1
    } else {
        var partner = city.get_building(partner_id)
        if (!b.has_road_access || !partner.has_road_access) {
            reason_id = 2
        } else if (b.num_workers <= 0 || partner.num_workers <= 0) {
            reason_id = 3
        }
    }

    if (reason_id) {
        window.warning_text.text = __loc(gid, reason_id)
    }

    building_info_window_setup_advisors(window)
}
