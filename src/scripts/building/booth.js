log_info("akhenaten: building_booth started")

building_booth {
    animations {
        booth { pack:PACK_GENERAL, id:114 },
        square { pack:PACK_GENERAL, id:112 },
        juggler { pos [35, 17], pack:PACK_SPR_AMBIENT, id:7, offset:-1 },
    }

    preview_booth_offsets : [
        [0, 0], [30, 15], [0, 30], [-30, 15]
    ]

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

[es=(building_booth, ghost_preview)]
function building_booth_ghost_preview(ev) {
    var pixel = ev.pixel
    var params = city.get_building_params_by_type(BUILDING_BOOTH)
    var building_size = params.building_size

    var orientation = __map_venue_build_orientation(ev.end, e_venue_mode_booth)
    if (orientation < 0) {
        city.planner.draw_flat_tiles(pixel, building_size * building_size)
        return
    }

    var square_id = params.first_img("square")
    for (var i = 0; i < building_size * building_size; i++) {
        var col = i % building_size
        var row = Math.floor(i / building_size)
        var tile_pixel = {
            x: pixel.x + (col - row) * 30,
            y: pixel.y + (col + row) * 15 - 15
        }
        city.planner.draw_isometric_ghost(tile_pixel, square_id + i)
    }

    var booth_id = params.first_img("booth")
    var off = building_booth.preview_booth_offsets[Math.floor(orientation / 2)]
    city.planner.draw_ghost({ x: pixel.x + off[0], y: pixel.y + off[1] }, booth_id)
}
