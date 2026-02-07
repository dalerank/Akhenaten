log_info("akhenaten: building mastaba started")

building_small_stepped_pyramid {
    animations {
      _pack { pack:PACK_STEPPED_PYRAMID }
      preview { id:2, offset:7 }
      base { id:2, offset:7 }
      base_bricks { id:1, offset:0 }
      base_grounded { path:"stepped_pyramid/pyramid_phase_one_00013" }
      clear_land { id:2, offset:12 }
      image_stick { path:"stepped_pyramid/pyramid_phase_one_00021" }
      empty_land {path:"stepped_pyramid/stepped_pyramid_00109"}
      ditches_phase_1 { path:"stepped_pyramid/pyramid_phase_one_00022" }
      ditches_phase_2 { path:"stepped_pyramid/pyramid_phase_one_00031" }
      ditches_phase_3 { path:"stepped_pyramid/pyramid_phase_one_00040" }
      ditches_phase_4 { path:"stepped_pyramid/pyramid_phase_one_00049" }
      ground_phase_0 { path:"stepped_pyramid/pyramid_phase_one_00013" }
      enter {id:114}
    }
    build_menu_text : "Small Stepped Pyramid"
    building_size : 2
    info_title_id [198, 18]
    fire_proof :  true
    damage_proof : true
    meta { help_id:375, text_id:120 }
    init_tiles [10, 10]

    flags {
        is_monument: true
    }

    corner_type : BUILDING_SMALL_STEPPED_PYRAMID_CORNER
    wall_type : BUILDING_SMALL_STEPPED_PYRAMID_WALL
    cone_type : BUILDING_SMALL_STEPPED_PYRAMID_CONE
    filler_type : BUILDING_SMALL_STEPPED_PYRAMID
    // todo
  }

  // Pyramid part buildings - all parts use same config as main pyramid
  building_small_stepped_pyramid_corner = building_small_stepped_pyramid
  building_small_stepped_pyramid_wall = building_small_stepped_pyramid
  building_small_stepped_pyramid_cone = building_small_stepped_pyramid

  building_medium_stepped_pyramid {
    animations {
      _pack { pack:PACK_STEPPED_PYRAMID }
      preview { pack:PACK_STEPPED_PYRAMID, id:2, offset:7 }
      base { id:2, offset:7 }
      base_bricks { id:1, offset:0 }
      base_grounded { path:"stepped_pyramid/pyramid_phase_one_00013" }
      clear_land { id:2, offset:12 }
      image_stick { path:"stepped_pyramid/pyramid_phase_one_00021" }
      empty_land {path:"stepped_pyramid/stepped_pyramid_00109"}
      ditches_phase_1 { path:"stepped_pyramid/pyramid_phase_one_00022" }
      ditches_phase_2 { path:"stepped_pyramid/pyramid_phase_one_00031" }
      ditches_phase_3 { path:"stepped_pyramid/pyramid_phase_one_00040" }
      ditches_phase_4 { path:"stepped_pyramid/pyramid_phase_one_00049" }
      ground_phase_0 { path:"stepped_pyramid/pyramid_phase_one_00013" }
      enter {id:114}
    }
    build_menu_text : "Medium Stepped Pyramid"
    building_size : 2
    info_title_id [198, 18]
    fire_proof :  true
    damage_proof : true
    meta { help_id:375, text_id:120 }
    init_tiles [14, 14]

    flags {
        is_monument: true
    }

    corner_type : BUILDING_MEDIUM_STEPPED_PYRAMID_CORNER
    wall_type : BUILDING_MEDIUM_STEPPED_PYRAMID_WALL
    cone_type : BUILDING_MEDIUM_STEPPED_PYRAMID_CONE
    filler_type : BUILDING_MEDIUM_STEPPED_PYRAMID
    // todo
  }

  building_medium_stepped_pyramid_corner = building_medium_stepped_pyramid
  building_medium_stepped_pyramid_wall = building_medium_stepped_pyramid
  building_medium_stepped_pyramid_cone = building_medium_stepped_pyramid