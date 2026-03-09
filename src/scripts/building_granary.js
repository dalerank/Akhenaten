log_info("akhenaten: building_granary started")

building_granary {
    animations {
        preview { pack:PACK_GENERAL, id:99 },
        base { pack:PACK_GENERAL, id:99 },
        work { pack:PACK_SPR_AMBIENT, id:47, max_frames:23 },
        resources {pack:PACK_GENERAL, id:99, offset:2},
        minimap {pack:PACK_GENERAL, id:149, offset:160},
    }

    min_houses_coverage : 100
    labor_category : LABOR_CATEGORY_INFRASTRUCTURE
    meta { help_id: 3, text_id: 98 }
    building_size : 4
    planner_update_rule {
        roads : true
    }

    flags {
        is_food: true
    }

    cost [ 50, 70, 100, 200, 300 ]
    laborers[20]
    fire_risk[0]
    damage_risk[5]
    desirability { value[-8], step[1], step_size[-2], range[4] }
    begin_spot_pos [110, -74]
    res_image_offsets [[0, 0], [16, 9], [35, 18], [51, 26], [-16, 7], [1, 16], [20, 26], [37, 35]]
    min_workers_percent_for_tasks : 50
    min_workers_percent_for_accepting :75
    min_workers_percent_for_getting : 100

    sound_channel : SOUND_CHANNEL_CITY_GRANARY
    overlay : OVERLAY_FOOD_STOCKS

    max_capacty_stored : 3200
    allow_food_types : 4
}

[es=(building_granary, on_place_checks)]
function building_granary_on_place_checks(ev) {
    var has_bazaar = city.count_active_buildings(BUILDING_BAZAAR) > 0
    city.warnings.show_if_not(has_bazaar, "#build_bazaars_to_distribute_food")
}
