log_info("akhenaten: ui farm info window started")

[es=(info_window_farm, init)]
function info_window_farm_on_init(window) {
    var b = city.get_building(window.bid)
    var gid = b.meta_text_id
    var reason = { group: gid, id: 0 }
    if (!b.num_workers) {
        reason = { group: 177, id: 5 }
    } else {
        if (!b.has_road_access) {
            reason = { group: 69, id: 25 }
        } else if (__city_resource_is_mothballed(b.output_resource_id)) {
            reason.id = 4
        } else if (b.curse_days_left > 4) {
            reason.id = 11
        } else {
            reason.id = Math.approximate_value(b.worker_percentage / 100.0, [10, 9, 8, 7, 6])
        }
    }
    window.workers_desc.text = __loc(reason.group, reason.id)

    var farm = city.get_farm(window.bid)
    if (farm.is_floodplain) {
        var month_id = 8 // TODO: fetch flood info
        window.flood_info.text = __loc(177, 2) + " " + __loc(160, month_id)
        var is_not_irrigated = 0 // TODO: fetch irrigation info
        window.farm_state.text = __loc(177, is_not_irrigated)
        window.farm_desc.text = __loc(gid, 1)
    } else {
        window.farm_state.text = __loc(gid, 1)
    }
}
