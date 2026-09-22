log_info("akhenaten: building_tax_collector started")

[es=(building_tax_collector, spawn_figure)]
function building_tax_collector_spawn_figure(ev) {
    var b = city.get_building(ev.bid)
    b.common_spawn_roamer(FIGURE_TAX_COLLECTOR, b.params.min_houses_coverage, ACTION_0_TAX_COLLECTOR_CREATED)
}

[es=(building_tax_collector, update_month)]
function building_tax_collector_update_month(ev) {
    if (!game_features.gameplay_change_new_tax_collection_system) {
        return
    }

    var b = city.get_building(ev.bid)
    if (b.has_figure(BUILDING_SLOT_CARTPUSHER)) {
        return
    }

    if (!b.has_road_access || b.deben_storage <= 100) {
        return
    }

    var may_send = Math.floor(b.deben_storage / 100) * 100
    if (may_send > 400) {
        may_send = 400
    }

    var fid = b.create_cartpusher(RESOURCE_GOLD, may_send, ACTION_20_CARTPUSHER_INITIAL, BUILDING_SLOT_CARTPUSHER)
    b.deben_storage -= may_send
    var f = city.get_figure(fid)
    if (f) {
        f.sender_building_id = b.id
    }
}
