log_info("akhenaten: building obelisk started")

function building_obelisk_has_unfinished() {
    for (var i = 1; i <= MAX_BUILDINGS; i++) {
        var m = city.get_monument(i)
        if (!m) {
            continue
        }
        if (m.type != BUILDING_SMALL_OBELISK && m.type != BUILDING_LARGE_OBELISK) {
            continue
        }
        if (m.phase() !== -1) {
            return true
        }
    }
    return false
}

function building_obelisk_placement_granite_need(type) {
    var cfg = get_building_config_by_id(type)
    var list = cfg && cfg.placement_resources
    if (!list) {
        return 0
    }
    for (var i = 0; i < list.length; i++) {
        if (list[i].resource == RESOURCE_GRANITE) {
            return list[i].count
        }
    }
    return 0
}

function building_obelisk_can_place(ev) {
    if (ev.state != CAN_PLACE && ev.state != CAN_NOT_BUT_GREEN) {
        city_planner.finalize_check_result = ev.state
        return
    }
    if (building_obelisk_has_unfinished()) {
        city_planner.set_warning("#only_one_obelisk_at_a_time")
        city_planner.finalize_check_result = CAN_NOT_PLACE
        return
    }
    var need = building_obelisk_placement_granite_need(city_planner.build_type)
    if (need > 0 && city.yards_stored_staffed(RESOURCE_GRANITE) < need) {
        var lang_id = (city_planner.build_type == BUILDING_LARGE_OBELISK) ? 84 : 83
        var tmpl = __loc(19, lang_id)
        city_planner.set_warning(tmpl.replace("%d", "" + need))
        city_planner.finalize_check_result = CAN_NOT_BUT_GREEN
        return
    }
    city_planner.finalize_check_result = ev.state
}

function building_obelisk_on_place_checks(ev) {
    var b = city.get_building(ev.bid)
    if (!b) {
        return
    }
    var need = building_obelisk_placement_granite_need(b.type)
    if (need > 0) {
        emit event_storageyards_remove_resource{ resource: RESOURCE_GRANITE, amount: need, staffed_only: true }
    }
}
