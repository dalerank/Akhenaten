log_info("akhenaten: building_booth started")

building_booth {
    animations {
        booth { pack:PACK_GENERAL, id:114 },
        square { pack:PACK_GENERAL, id:112 },
        juggler { pos [35, 17], pack:PACK_SPR_AMBIENT, id:7, offset:-1 },
    }

    min_houses_coverage : 100
    labor_category : LABOR_CATEGORY_ENTERTAINMENT
    meta { help_id:71, text_id:72 }
    info_sound : "Wavs/jugger_r.wav"
    building_size : 2
    cost [ 10, 20, 40, 80, 150 ]
    desirability { value[2], step[1], step_size[-1], range[2] }

    laborers[8]
    fire_risk[4]
    damage_risk[2]
    flags {
        is_entertainment: true
    }
}

[es=(building_booth, on_place_checks)]
function building_booth_on_place_checks(ev) {
    var has_juggler_school = city.count_active_buildings(BUILDING_JUGGLER_SCHOOL) > 0
    city.warnings.show_if_not(has_juggler_school, "#build_juggling_school")
}
