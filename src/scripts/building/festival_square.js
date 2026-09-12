log_info("akhenaten: building_festival_square started")

building_festival_square = {
  animations : {
    base : { pos:[0, 0], pack:PACK_GENERAL, id:49 },
    square : { pos:[0, 0], pack:PACK_GENERAL, id:49 },
  },
  building_size : 5,
  meta : { text_id: 188, help_link:"message_building_festival_square" }
  info_sound : "Wavs/prefecture.wav"
  fire_proof : true,
  damage_proof : true,
  planner_update_rule : {
    unique_building : true
  }
  cost : [ 100, 250, 500, 1000, 1500 ]
  desirability : { value:[16], step:[2], step_size:[-3], range: [5] }
  flags {
    is_religion: true
  }
}

[es=(building_festival_square, ghost_preview)]
function building_festival_square_ghost_preview(ev) {
    var pixel = ev.pixel
    var params = city.get_building_params_by_type(BUILDING_FESTIVAL_SQUARE)
    var size = params.building_size
    var tiles = size * size

    // Festival has a single road mask — orientation unused; matcher is can_place only.
    var orientation = __map_venue_build_orientation(ev.end, e_venue_mode_festival_square)
    if (orientation < 0) {
        city_planner.draw_flat_tiles(pixel, tiles)
        return
    }

    var square_id = params.first_img("square")
    var color = city.count_total_buildings(BUILDING_FESTIVAL_SQUARE) > 0
        ? COLOR_MASK_RED
        : COLOR_MASK_GREEN
    for (var i = 0; i < tiles; i++) {
        var col = i % size
        var row = Math.floor(i / size)
        city_planner.draw_isometric_ghost(
            { x: pixel.x + (col - row) * 30, y: pixel.y + (col + row) * 15 },
            square_id + i,
            color
        )
    }
}
