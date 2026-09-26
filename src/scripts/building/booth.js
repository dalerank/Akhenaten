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
    meta { text_id:72, help_link:"message_building_booth" }
    info_sound : "Wavs/jugger_r.wav"
    building_size : 2
    cost [ 10, 20, 40, 80, 150 ]
    desirability { value[2], step[1], step_size[-1], range[2] }

    laborers[8]
    fire_risk[4]
    damage_risk[2]
    flags {
        is_entertainment: true
        keeps_visitor_paths: true
    }
}

[es=(building_booth, ghost_allow_tile)]
function building_booth_ghost_allow_tile(ev) {
    city_planner.preview_allow_result = terrain.is(ev.tile, TERRAIN_ROAD) || !__map_has_figure_at(ev.tile)
}

[es=(building_booth, setup_preview_graphics)]
function building_booth_setup_preview_graphics(ev) {
    var size = building_booth.building_size
    city_planner.init_tiles(size, size)
}

[es=(building_booth, on_place_checks)]
function building_booth_on_place_checks(ev) {
    var has_juggler_school = city.count_active_buildings(BUILDING_JUGGLER_SCHOOL) > 0
    city.warnings.show_if_not(has_juggler_school, "#build_juggling_school")
}

[es=(building_booth, update_day)]
function building_booth_update_day(ev) {
    var b = city.get_entertainment_building(ev.bid)
    if (!b) {
        return
    }
    b.num_shows = 0
    if (b.juggler_visited > 0) {
        b.juggler_visited = b.juggler_visited - 1
        b.num_shows = b.num_shows + 1
    }
}

[es=(building_booth, update_month)]
function building_booth_update_month(ev) {
    var b = city.get_entertainment_building(ev.bid)
    if (!b) {
        return
    }
    b.play_index = Math.floor(Math.random() * 10)
}

[es=(building_booth, draw_usable_paths)]
function building_booth_draw_usable_paths(ev) {
    city.get_building(ev.bid).draw_usable_paths()
}

[es=(building_booth, ghost_preview)]
function building_booth_ghost_preview(ev) {
    var pixel = ev.pixel
    var params = city.get_building_params_by_type(BUILDING_BOOTH)
    var building_size = params.building_size

    var orientation = __map_venue_build_orientation(ev.end, e_venue_mode_booth)
    if (orientation < 0) {
        city_planner.draw_flat_tiles(pixel, building_size * building_size)
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
        city_planner.draw_isometric_ghost(tile_pixel, square_id + i, COLOR_MASK_GREEN)
    }

    var booth_id = params.first_img("booth")
    var off = building_booth.preview_booth_offsets[Math.floor(orientation / 2)]
    city_planner.draw_ghost({ x: pixel.x + off[0], y: pixel.y + off[1] }, booth_id)
}
