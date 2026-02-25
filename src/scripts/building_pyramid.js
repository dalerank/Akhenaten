log_info("akhenaten: building mastaba started")

building_small_stepped_pyramid {
    animations {
      _pack { pack:PACK_STEPPED_PYRAMID }
      preview { id:2, offset:7 }
      base { id:2, offset:7 }
      base_bricks { path:"stepped_pyramid/stepped_pyramid_00103" }
      corner_bricks { path:"stepped_pyramid/stepped_pyramid_00001" }
      wall_bricks { path:"stepped_pyramid/stepped_pyramid_00005" }
      base_grounded { path:"stepped_pyramid/pyramid_phase_one_00013" }
      clear_land { id:2, offset:12 }
      image_stick { path:"stepped_pyramid/pyramid_phase_one_00021" }
      empty_land {path:"stepped_pyramid/stepped_pyramid_00109"}
      ditches_phase_1 { path:"stepped_pyramid/pyramid_phase_one_00022" }
      ditches_phase_2 { path:"stepped_pyramid/pyramid_phase_one_00031" }
      ditches_phase_3 { path:"stepped_pyramid/pyramid_phase_one_00040" }
      ditches_phase_4 { path:"stepped_pyramid/pyramid_phase_one_00049" }
      ground_phase_0 { path:"stepped_pyramid/pyramid_phase_one_00013" }
      basement { path:"stepped_pyramid/pyramid_phase_one_00058" }
      enter { path:"pharaoh_general/plazatiles_00064"}
    }
    build_menu_text : "Small Stepped Pyramid"
    building_size : 2
    info_title_id [198, 18]
    fire_proof :  true
    damage_proof : true
    meta { help_id:375, text_id:120 }
    init_tiles [8, 8]

    flags {
      is_monument: true
    }

    enter_offset : [1, 8]
    stair_0_0_offset : [2, 8]
    stair_0_1_offset : [4, 8]
    stair_0_4_offset : [6, 8]
    stair_0_4_corner_offset : [6, 6]
    stair_0_5_offset : [6, 5]
    stair_0_6_offset : [6, 4]

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
      base_bricks { path:"stepped_pyramid/stepped_pyramid_00103" }
      corner_bricks { path:"stepped_pyramid/stepped_pyramid_00001" }
      wall_bricks { path:"stepped_pyramid/stepped_pyramid_00005" }
      base_grounded { path:"stepped_pyramid/pyramid_phase_one_00013" }
      clear_land { id:2, offset:12 }
      image_stick { path:"stepped_pyramid/pyramid_phase_one_00021" }
      empty_land {path:"stepped_pyramid/stepped_pyramid_00109"}
      ditches_phase_1 { path:"stepped_pyramid/pyramid_phase_one_00022" }
      ditches_phase_2 { path:"stepped_pyramid/pyramid_phase_one_00031" }
      ditches_phase_3 { path:"stepped_pyramid/pyramid_phase_one_00040" }
      ditches_phase_4 { path:"stepped_pyramid/pyramid_phase_one_00049" }
      ground_phase_0 { path:"stepped_pyramid/pyramid_phase_one_00013" }
      basement { path:"stepped_pyramid/pyramid_phase_one_00058" }
      enter { path:"pharaoh_general/plazatiles_00064"}
      stair_0_2 { path:"stepped_pyramid/stepped_pyramid_00112" }
      stair_0_4 { path:"stepped_pyramid/stepped_pyramid_00110" }
      stair_0_4_corner { path:"stepped_pyramid/stepped_pyramid_00122" }
      stair_0_5 { path:"stepped_pyramid/stepped_pyramid_00114" }
      stair_0_6 { path:"stepped_pyramid/stepped_pyramid_00115" }
    }
    build_menu_text : "Medium Stepped Pyramid"
    building_size : 2
    info_title_id [198, 18]
    fire_proof :  true
    damage_proof : true
    meta { help_id:375, text_id:120 }
    init_tiles [12, 12]

    enter_offset : [2, 12]

    stairs [
      {
        phase : 7
        part : [2, 10]
        tex { path:"stepped_pyramid/stepped_pyramid_00110" }
        offset : [-15, 25]
      }

      {
        phase : 8
        part : [4, 10]
        tex { path:"stepped_pyramid/stepped_pyramid_00111" }
        offset : [-15, 25]
      }

      {
        phase : 9
        part : [6, 10]
        tex { path:"stepped_pyramid/stepped_pyramid_00112" }
        offset : [-15, 25]
      }

      {
        phase : 10
        part : [8, 10]
        tex { path:"stepped_pyramid/stepped_pyramid_00110" }
        offset : [15, -35]
      }

      {
        phase : 10
        part : [10, 10]
        tex { path:"stepped_pyramid/stepped_pyramid_00122" }
        offset : [15, -40]
      }

      {
        phase : 11
        part : [10, 8]
        tex { path:"stepped_pyramid/stepped_pyramid_00114" }
        offset : [25, -30]
      }

      {
        phase : 12
        part : [10, 6]
        tex { path:"stepped_pyramid/stepped_pyramid_00115" }
        offset : [20, -30]
      }

      {
        phase : 13
        part : [10, 4]
        tex { path:"stepped_pyramid/stepped_pyramid_00113" }
        offset : [0, -90]
      }

      {
        phase : 13
        part : [10, 2]
        tex { path:"stepped_pyramid/stepped_pyramid_00124" }
        offset : [0, -95]
      }

      {
        phase : 16
        part : [4, 8]
        tex { path:"stepped_pyramid/stepped_pyramid_00118" }
        offset : [-28, -155]
      }

      {
        phase : 17
        part : [6, 8]
        tex { path:"stepped_pyramid/stepped_pyramid_00111" }
        offset : [-48, -158]
      }

      {
        phase : 18
        part : [8, 8]
        tex { path:"stepped_pyramid/stepped_pyramid_00112" }
        offset : [-48, -158]
      }

      {
        phase : 19
        part : [8, 6]
        tex { path:"stepped_pyramid/stepped_pyramid_00113" }
        offset : [0, -180]
      }

      {
        phase : 20
        part : [8, 4]
        tex { path:"stepped_pyramid/stepped_pyramid_00124" }
        offset : [-0, -180]
      }

      {
        phase : 21
        part : [4, 6]
        tex { path:"stepped_pyramid/stepped_pyramid_00119" }
        offset : [-20, -175]
      }

      {
        phase : 21
        part : [6, 6]
        tex { path:"stepped_pyramid/stepped_pyramid_00112" }
        offset : [-40, -175]
      }

      {
        phase : 22
        part : [6, 4]
        tex { path:"stepped_pyramid/stepped_pyramid_00113" }
        offset : [10, -200]
      }
    ]

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