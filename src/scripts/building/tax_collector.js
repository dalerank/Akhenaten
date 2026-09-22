log_info("akhenaten: building_tax_collector started")

function building_tax_collector_spawn_figure(ev) {
    var b = city.get_building(ev.bid)
    b.common_spawn_roamer(FIGURE_TAX_COLLECTOR, b.params.min_houses_coverage, ACTION_0_TAX_COLLECTOR_CREATED)
}

[es=(building_tax_collector, spawn_figure)]
function building_tax_collector_on_spawn_figure(ev) {
    building_tax_collector_spawn_figure(ev)
}

[es=(building_tax_collector_up, spawn_figure)]
function building_tax_collector_up_on_spawn_figure(ev) {
    building_tax_collector_spawn_figure(ev)
}
