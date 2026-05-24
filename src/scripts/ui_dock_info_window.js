log_info("akhenaten: ui_dock_info_window.js loaded")

[es=building_info_window]
info_window_dock {
    related_buildings [BUILDING_DOCK]
    ui : baseui(building_info_window, {
        background   : outer_panel({size: [29, 16]}),
        orders       : button({margin:{left:100, bottom:-40}, size:[270, 25], text:"${98.5}", onclick_event: "open_orders_window" }),
    })
}

[es=(info_window_dock, init)]
function info_window_dock_on_init(window) {
    var dock = city.get_dock(window.bid)
    var meta_text_id = dock.meta_text_id

    window.warning_text.text = __loc(meta_text_id, 1)

    var reason = { group: 0, id: 0 }
    if (!dock.has_road_access) {
        reason = { group: 69, id: 25 }
    } else if (dock.has_trade_ship()) {
        reason.group = meta_text_id
        reason.id = Math.approximate_value(dock.worker_percentage / 100.0, [2, 3, 4, 5])
    } else {
        reason.group = meta_text_id
        reason.id = Math.approximate_value(dock.worker_percentage / 100.0, [6, 7, 8, 9])
    }

    if (reason.group) {
        window.workers_desc.text = __loc(reason.group, reason.id)
    }
}

[es=(info_window_dock, open_orders_window)]
function info_window_dock_on_open_orders_window(window) {
    emit event_show_window{ id: "dock_orders_window" }
}
