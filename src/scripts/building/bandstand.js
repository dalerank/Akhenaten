log_info("akhenaten: building_bandstand started")

building_bandstand {
  animations {
    _pack { pack: PACK_GENERAL }
    booth { id:114 }
    square { id:58}
    stand_sn_s { id:92, offset:0 }
    stand_sn_n { id:92, offset:1 }
    stand_we_w { id:92, offset:2 }
    stand_we_e { id:92, offset:3 }

    juggler { pos[35, 15], pack:PACK_SPR_AMBIENT, id:7, max_frames:26, duration:2, internal_offset:true }
    musician_sn { pos[-10, -36], pack:PACK_SPR_AMBIENT, id:10, max_frames : 11, duration:3 }
    musician_we { pos[30, 10], pack:PACK_SPR_AMBIENT, id:9, max_frames : 11, duration:3, internal_offset:true }
  }

  overlay : OVERLAY_BANDSTAND
  labor_category : LABOR_CATEGORY_ENTERTAINMENT
  min_houses_coverage : 100
  fire_proof: true
  meta { text_id:71, help_link:"message_building_bandstand" }
  info_sound : "Wavs/music_r.wav"
  building_size : 3
  cost [ 30, 50, 100, 150, 200 ]
  desirability { value[4], step[1], step_size[-1], range[4] }
  laborers[12], fire_risk[4], damage_risk[3]
  flags {
    is_entertainment: true
  }
}

[es=(building_bandstand, ghost_allow_tile)]
function building_bandstand_ghost_allow_tile(ev) {
    city_planner.preview_allow_result = terrain.is(ev.tile, TERRAIN_ROAD) || !__map_has_figure_at(ev.tile)
}

[es=(building_bandstand, setup_preview_graphics)]
function building_bandstand_setup_preview_graphics(ev) {
    var size = building_bandstand.building_size
    city_planner.init_tiles(size, size)
}
