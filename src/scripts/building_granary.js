log_info("akhenaten: building_granary started")

[es=(building_granary, on_place_checks)]
function building_granary_on_place_checks(ev) {
    log_info("building_granary_on_place_checks: " + building_granary.min_houses_coverage)
    var has_bazaar = city.count_active_buildings(BUILDING_BAZAAR) > 0
    city.warnings.show_if_not(has_bazaar, "#build_bazaars_to_distribute_food")
}
