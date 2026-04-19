log_info("akhenaten: ui_courthouse_window.js loaded")

[es=building_info_window]
info_window_courthouse {
    related_buildings [BUILDING_COURTHOUSE]
    ui : baseui(building_info_window, {
        background    : outer_panel({size: [29, 17]}),
        vaults_hold   : text({pos: [44, 54], font: FONT_NORMAL_BLACK_ON_LIGHT }),
        state         : text({margin:{left:20, bottom: -80} , font: FONT_NORMAL_BLACK_ON_DARK}),
    })
}


[es=(info_window_courthouse, init)]
function info_window_courthouse_on_init(window) {
    var b = city.get_building(window.bid)
    var gid = b.meta_text_id

    var reason = { group: gid, id: 0 }
    if (b.has_road_access == false) {
        reason = { group: 69, id: 25 }
    } else if (b.num_workers <= 0) {
        reason.id = 2
    } else {
        reason.id = Math.approximate_value(b.worker_percentage / 100.0, [4, 5, 6])
    }
    window.workers_desc.text = __loc(reason.group, reason.id)

    var magistrate_state = { group: 58, id: 51 }
    if (b.num_workers > 0) {
        if (!b.has_figure(BUILDING_SLOT_SERVICE)) {
            magistrate_state = { group: gid, id: 8 }
        } else {
            magistrate_state = { group: gid, id: 7 }
        }
    }
    window.state.text = __loc(magistrate_state.group, magistrate_state.id)

    window.warning_text.text = __loc(gid, 1)
}
