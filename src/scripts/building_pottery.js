log_info("akhenaten: building_pottery started")

building_pottery {
    animations {
        preview { pos[-1, -1], pack:PACK_GENERAL, id:125 }
        base { pos[-1, -1], pack:PACK_GENERAL, id:125 }
        work { pos[36, -4], pack:PACK_GENERAL, id:125, offset:1, max_frames:18, duration:12 }
        clay { pos[60, 30], pack:PACK_GENERAL, id:205, offset:9 }
    }

    input {
        resource : RESOURCE_CLAY
    }

    output {
        resource : RESOURCE_POTTERY
    }

    production_rate : 20
    labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE
    building_size : 2
    meta { help_id:1, text_id:126 }
    cost [ 12, 20, 30, 40, 50 ]
    desirability {
        value[-4]
        step[1]
        step_size[1]
        range[4]
    }
    laborers[12]
    fire_risk[4]
    damage_risk[3]
    flags {
        is_workshop: true
        is_industry: true
    }
}


[es=(building_pottery, place_checks)]
function building_pottery_on_place_checks(ev) {
    if (city.resources.clay.count_active_industry > 0)
        return

    if (city.resources.clay.yards_stored > 0)
        return

    city.warnings.show("#building_needs_clay")
    if (!city.resources.clay.can_produce) {
        city.warnings.show("#build_clay_pit")
    }

    if (!city.resources.clay.can_import) {
        city.warnings.show("#setup_trade_route_to_import")
    }

    if (city.resources.clay.trade_status != TRADE_STATUS_IMPORT) {
        city.warnings.show("#overseer_of_commerce_to_import")
    }
}