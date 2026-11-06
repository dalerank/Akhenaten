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
      ramps {path:"stepped_pyramid/stepped_pyramid_00110"}
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
    build_menu_text : "Small Stepped Pyramid"
    building_size : 2
    info_title_id [198, 8]
    fire_proof :  true
    damage_proof : true
    meta { text_id:178, help_link:"message_building_stepped_pyramid" }
    init_tiles [8, 8]

    flags {
      is_monument: true
      non_deletable: true
    }

    enter_offset : [1, 8]

    // 8×8 parts on even grid (south y=6, east x=6). Tier-0 south→SE→east, then
    // tier-1 ledge (side 4). Pixel offsets tuned from medium, shortened path.
    stairs [
      {
        phase : 7
        part : [2, 6]
        tex { path:"stepped_pyramid/stepped_pyramid_00110" }
        offset : [-15, 25]
      }

      {
        phase : 8
        part : [4, 6]
        tex { path:"stepped_pyramid/stepped_pyramid_00111" }
        offset : [-15, 25]
      }

      {
        phase : 9
        part : [6, 6]
        tex { path:"stepped_pyramid/stepped_pyramid_00122" }
        offset : [15, -40]
      }

      {
        phase : 10
        part : [6, 4]
        tex { path:"stepped_pyramid/stepped_pyramid_00114" }
        offset : [25, -30]
      }

      {
        phase : 11
        part : [6, 2]
        tex { path:"stepped_pyramid/stepped_pyramid_00115" }
        offset : [20, -30]
      }

      {
        phase : 16
        part : [2, 4]
        tex { path:"stepped_pyramid/stepped_pyramid_00118" }
        offset : [-28, -155]
      }

      {
        phase : 17
        part : [4, 4]
        tex { path:"stepped_pyramid/stepped_pyramid_00112" }
        offset : [-40, -158]
      }

      {
        phase : 18
        part : [4, 2]
        tex { path:"stepped_pyramid/stepped_pyramid_00113" }
        offset : [10, -180]
      }
    ]

    corner_type : BUILDING_SMALL_STEPPED_PYRAMID_CORNER
    wall_type : BUILDING_SMALL_STEPPED_PYRAMID_WALL
    cone_type : BUILDING_SMALL_STEPPED_PYRAMID_CONE
    filler_type : BUILDING_SMALL_STEPPED_PYRAMID
  }

  // Parts are 2?2 blocks on the init_tiles grid ? without building_size they stay
  // size 0 and never claim map tiles (edges/corners missing). Alias main so they
  // also inherit brick animations used by get_bricks_image.
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
      ramps {path:"stepped_pyramid/stepped_pyramid_00110"}
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
    info_title_id [198, 9]
    fire_proof :  true
    damage_proof : true
    meta { text_id:178, help_link:"message_building_stepped_pyramid" }
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
        non_deletable: true
    }

    corner_type : BUILDING_MEDIUM_STEPPED_PYRAMID_CORNER
    wall_type : BUILDING_MEDIUM_STEPPED_PYRAMID_WALL
    cone_type : BUILDING_MEDIUM_STEPPED_PYRAMID_CONE
    filler_type : BUILDING_MEDIUM_STEPPED_PYRAMID
  }

  building_medium_stepped_pyramid_corner = building_medium_stepped_pyramid
  building_medium_stepped_pyramid_wall = building_medium_stepped_pyramid
  building_medium_stepped_pyramid_cone = building_medium_stepped_pyramid

  // Large stepped pyramid (20x20, id 250). Same PACK_STEPPED_PYRAMID render pipeline as
  // small/medium; only footprint (init_tiles) differs. Stairs: ascending ramp from
  // enter_offset up the south face to the tier-1 ledge (one layer ? TILE_HEIGHT*3 = 90px).
  building_large_stepped_pyramid {
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
      ramps {path:"stepped_pyramid/stepped_pyramid_00110"}
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
    build_menu_text : "Large Stepped Pyramid"
    building_size : 2
    info_title_id [198, 10]
    fire_proof :  true
    damage_proof : true
    meta { text_id:178, help_link:"message_building_stepped_pyramid" }
    init_tiles [20, 20]

    enter_offset : [2, 20]

    // 20×20 multi-tier L-ramp (south → SE → east climb, then upper ledges).
    // Keep in sync with building_stepped_pyramid_complex. Optional: L4 stairs / eye-tune offsets.
    stairs [
      {
        phase : 7
        part : [4, 18]
        tex { path:"stepped_pyramid/stepped_pyramid_00110" }
        offset : [-20, 20]
      }

      {
        phase : 8
        part : [6, 18]
        tex { path:"stepped_pyramid/stepped_pyramid_00111" }
        offset : [-25, 20]
      }

      {
        phase : 9
        part : [8, 18]
        tex { path:"stepped_pyramid/stepped_pyramid_00112" }
        offset : [-20, 20]
      }

      {
        phase : 10
        part : [12, 18]
        tex { path:"stepped_pyramid/stepped_pyramid_00110" }
        offset : [0, -40]
      }

      {
        phase : 11
        part : [14, 18]
        tex { path:"stepped_pyramid/stepped_pyramid_00111" }
        offset : [-5, -40]
      }

      {
        phase : 12
        part : [16, 18]
        tex { path:"stepped_pyramid/stepped_pyramid_00112" }
        offset : [-5, -45]
      }

      {
        phase : 13
        part : [18, 14]
        tex { path:"stepped_pyramid/stepped_pyramid_00113" }
        offset : [10, -100]
      }

      {
        phase : 14
        part : [18, 12]
        tex { path:"stepped_pyramid/stepped_pyramid_00114" }
        offset : [0, -100]
      }

      {
        phase : 15
        part : [18, 10]
        tex { path:"stepped_pyramid/stepped_pyramid_00115" }
        offset : [-5, -100]
      }

      {
        phase : 16
        part : [18, 8]
        tex { path:"stepped_pyramid/stepped_pyramid_00113" }
        offset : [0, -170]
      }

      {
        phase : 17
        part : [18, 6]
        tex { path:"stepped_pyramid/stepped_pyramid_00114" }
        offset : [0, -170]
      }

      {
        phase : 18
        part : [18, 4]
        tex { path:"stepped_pyramid/stepped_pyramid_00125" }
        offset : [-5, -170]
      }

      {
        phase : 19
        part : [12, 16]
        tex { path:"stepped_pyramid/stepped_pyramid_00110" }
        offset : [15, -200]
      }

      {
        phase : 20
        part : [14, 16]
        tex { path:"stepped_pyramid/stepped_pyramid_00111" }
        offset : [10, -200]
      }

      {
        phase : 20
        part : [16, 16]
        tex { path:"stepped_pyramid/stepped_pyramid_00123" }
        offset : [15, -205]
      }

      {
        phase : 21
        part : [16, 14]
        tex { path:"stepped_pyramid/stepped_pyramid_00115" }
        offset : [20, -200]
      }

      {
        phase : 22
        part : [14, 10]
        tex { path:"stepped_pyramid/stepped_pyramid_00113" }
        offset : [20, -210]
      }

      {
        phase : 23
        part : [14, 8]
        tex { path:"stepped_pyramid/stepped_pyramid_00114" }
        offset : [20, -210]
      }

      // --- Layer 2 (third tier): L2 south y=14 (begin+4, size 12); SE [14,14].
      {
        phase : 24
        part : [14, 6]
        tex { path:"stepped_pyramid/stepped_pyramid_00115" }
        offset : [15, -210]
      }

      {
        phase : 24
        part : [14, 4]
        tex { path:"stepped_pyramid/stepped_pyramid_00127" }
        offset : [10, -220]
      }

      {
        phase : 25
        part : [8, 14]
        tex { path:"stepped_pyramid/stepped_pyramid_00110" }
        offset : [0, -300]
      }

      {
        phase : 26
        part : [10, 14]
        tex { path:"stepped_pyramid/stepped_pyramid_00111" }
        offset : [0, -300]
      }

      {
        phase : 27
        part : [12, 14]
        tex { path:"stepped_pyramid/stepped_pyramid_00112" }
        offset : [0, -300]
      }

      {
        phase : 28
        part : [12, 10]
        tex { path:"stepped_pyramid/stepped_pyramid_00113" }
        offset : [20, -300]
      }

      {
        phase : 29
        part : [12, 8]
        tex { path:"stepped_pyramid/stepped_pyramid_00114" }
        offset : [15, -300]
      }

      {
        phase : 30
        part : [12, 6]
        tex { path:"stepped_pyramid/stepped_pyramid_00127" }
        offset : [15, -300]
      }

      {
        phase : 31
        part : [10, 12]
        tex { path:"stepped_pyramid/stepped_pyramid_00110" }
        offset : [0, -390]
      }

      {
        phase : 32
        part : [12, 12]
        tex { path:"stepped_pyramid/stepped_pyramid_00122" }
        offset : [0, -400]
      }

      {
        phase : 33
        part : [10, 12]
        tex { path:"stepped_pyramid/stepped_pyramid_00114" }
        offset : [0, -400]
      }
    ]

    flags {
        is_monument: true
        non_deletable: true
    }

    corner_type : BUILDING_LARGE_STEPPED_PYRAMID_CORNER
    wall_type : BUILDING_LARGE_STEPPED_PYRAMID_WALL
    cone_type : BUILDING_LARGE_STEPPED_PYRAMID_CONE
    filler_type : BUILDING_LARGE_STEPPED_PYRAMID
  }

  building_large_stepped_pyramid_corner = building_large_stepped_pyramid
  building_large_stepped_pyramid_wall = building_large_stepped_pyramid
  building_large_stepped_pyramid_cone = building_large_stepped_pyramid

  // Complex = plain 20x20 (same as large; causeway/temples not yet built).
  // Keep stairs/animations in sync with building_large_stepped_pyramid (titles differ).
  building_stepped_pyramid_complex {
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
      ramps {path:"stepped_pyramid/stepped_pyramid_00110"}
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
    build_menu_text : "Stepped Pyramid Complex"
    building_size : 2
    info_title_id [198, 11]
    fire_proof :  true
    damage_proof : true
    meta { text_id:178, help_link:"message_building_stepped_pyramid" }
    init_tiles [20, 20]

    enter_offset : [2, 20]

    // Same 20×20 multi-tier stairs as building_large_stepped_pyramid — keep in sync.
    stairs [
      {
        phase : 7
        part : [4, 18]
        tex { path:"stepped_pyramid/stepped_pyramid_00110" }
        offset : [-20, 20]
      }

      {
        phase : 8
        part : [6, 18]
        tex { path:"stepped_pyramid/stepped_pyramid_00111" }
        offset : [-25, 20]
      }

      {
        phase : 9
        part : [8, 18]
        tex { path:"stepped_pyramid/stepped_pyramid_00112" }
        offset : [-20, 20]
      }

      {
        phase : 10
        part : [12, 18]
        tex { path:"stepped_pyramid/stepped_pyramid_00110" }
        offset : [0, -40]
      }

      {
        phase : 11
        part : [14, 18]
        tex { path:"stepped_pyramid/stepped_pyramid_00111" }
        offset : [-5, -40]
      }

      {
        phase : 12
        part : [16, 18]
        tex { path:"stepped_pyramid/stepped_pyramid_00112" }
        offset : [-5, -45]
      }

      {
        phase : 13
        part : [18, 14]
        tex { path:"stepped_pyramid/stepped_pyramid_00113" }
        offset : [10, -100]
      }

      {
        phase : 14
        part : [18, 12]
        tex { path:"stepped_pyramid/stepped_pyramid_00114" }
        offset : [0, -100]
      }

      {
        phase : 15
        part : [18, 10]
        tex { path:"stepped_pyramid/stepped_pyramid_00115" }
        offset : [-5, -100]
      }

      {
        phase : 16
        part : [18, 8]
        tex { path:"stepped_pyramid/stepped_pyramid_00113" }
        offset : [0, -170]
      }

      {
        phase : 17
        part : [18, 6]
        tex { path:"stepped_pyramid/stepped_pyramid_00114" }
        offset : [0, -170]
      }

      {
        phase : 18
        part : [18, 4]
        tex { path:"stepped_pyramid/stepped_pyramid_00125" }
        offset : [-5, -170]
      }

      {
        phase : 19
        part : [12, 16]
        tex { path:"stepped_pyramid/stepped_pyramid_00110" }
        offset : [15, -200]
      }

      {
        phase : 20
        part : [14, 16]
        tex { path:"stepped_pyramid/stepped_pyramid_00111" }
        offset : [10, -200]
      }

      {
        phase : 20
        part : [16, 16]
        tex { path:"stepped_pyramid/stepped_pyramid_00123" }
        offset : [15, -205]
      }

      {
        phase : 21
        part : [16, 14]
        tex { path:"stepped_pyramid/stepped_pyramid_00115" }
        offset : [20, -200]
      }

      {
        phase : 22
        part : [14, 10]
        tex { path:"stepped_pyramid/stepped_pyramid_00113" }
        offset : [20, -210]
      }

      {
        phase : 23
        part : [14, 8]
        tex { path:"stepped_pyramid/stepped_pyramid_00114" }
        offset : [20, -210]
      }

      // --- Layer 2 (third tier): L2 south y=14 (begin+4, size 12) ? SE [14,14].
      // Offsets ~two tiers up (? -180..-270).
      {
        phase : 24
        part : [14, 6]
        tex { path:"stepped_pyramid/stepped_pyramid_00115" }
        offset : [15, -210]
      }

      {
        phase : 24
        part : [14, 4]
        tex { path:"stepped_pyramid/stepped_pyramid_00127" }
        offset : [10, -220]
      }

      {
        phase : 25
        part : [8, 14]
        tex { path:"stepped_pyramid/stepped_pyramid_00110" }
        offset : [0, -300]
      }

      {
        phase : 26
        part : [10, 14]
        tex { path:"stepped_pyramid/stepped_pyramid_00111" }
        offset : [0, -300]
      }

      {
        phase : 27
        part : [12, 14]
        tex { path:"stepped_pyramid/stepped_pyramid_00112" }
        offset : [0, -300]
      }

      {
        phase : 28
        part : [12, 10]
        tex { path:"stepped_pyramid/stepped_pyramid_00113" }
        offset : [20, -300]
      }

      {
        phase : 29
        part : [12, 8]
        tex { path:"stepped_pyramid/stepped_pyramid_00114" }
        offset : [15, -300]
      }

      {
        phase : 30
        part : [12, 6]
        tex { path:"stepped_pyramid/stepped_pyramid_00127" }
        offset : [15, -300]
      }

      {
        phase : 31
        part : [10, 12]
        tex { path:"stepped_pyramid/stepped_pyramid_00110" }
        offset : [0, -390]
      }

      {
        phase : 32
        part : [12, 12]
        tex { path:"stepped_pyramid/stepped_pyramid_00122" }
        offset : [0, -400]
      }

      {
        phase : 33
        part : [10, 12]
        tex { path:"stepped_pyramid/stepped_pyramid_00114" }
        offset : [0, -400]
      }
    ]

    flags {
        is_monument: true
        non_deletable: true
    }

    corner_type : BUILDING_LARGE_STEPPED_PYRAMID_CORNER
    wall_type : BUILDING_LARGE_STEPPED_PYRAMID_WALL
    cone_type : BUILDING_LARGE_STEPPED_PYRAMID_CONE
    filler_type : BUILDING_LARGE_STEPPED_PYRAMID
  }


  // Grand stepped — same on-land 20x20; own TYPE for weight 44 + east-only causeway.
  building_grand_stepped_pyramid_complex {
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
      ramps {path:"stepped_pyramid/stepped_pyramid_00110"}
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
    build_menu_text : "Grand Stepped Pyramid Complex"
    building_size : 2
    info_title_id [198, 12]
    fire_proof :  true
    damage_proof : true
    meta { text_id:178, help_link:"message_building_stepped_pyramid" }
    init_tiles [20, 20]

    enter_offset : [2, 20]

    // Same 20×20 multi-tier stairs as building_large_stepped_pyramid — keep in sync.
    stairs [
      {
        phase : 7
        part : [4, 18]
        tex { path:"stepped_pyramid/stepped_pyramid_00110" }
        offset : [-20, 20]
      }

      {
        phase : 8
        part : [6, 18]
        tex { path:"stepped_pyramid/stepped_pyramid_00111" }
        offset : [-25, 20]
      }

      {
        phase : 9
        part : [8, 18]
        tex { path:"stepped_pyramid/stepped_pyramid_00112" }
        offset : [-20, 20]
      }

      {
        phase : 10
        part : [12, 18]
        tex { path:"stepped_pyramid/stepped_pyramid_00110" }
        offset : [0, -40]
      }

      {
        phase : 11
        part : [14, 18]
        tex { path:"stepped_pyramid/stepped_pyramid_00111" }
        offset : [-5, -40]
      }

      {
        phase : 12
        part : [16, 18]
        tex { path:"stepped_pyramid/stepped_pyramid_00112" }
        offset : [-5, -45]
      }

      {
        phase : 13
        part : [18, 14]
        tex { path:"stepped_pyramid/stepped_pyramid_00113" }
        offset : [10, -100]
      }

      {
        phase : 14
        part : [18, 12]
        tex { path:"stepped_pyramid/stepped_pyramid_00114" }
        offset : [0, -100]
      }

      {
        phase : 15
        part : [18, 10]
        tex { path:"stepped_pyramid/stepped_pyramid_00115" }
        offset : [-5, -100]
      }

      {
        phase : 16
        part : [18, 8]
        tex { path:"stepped_pyramid/stepped_pyramid_00113" }
        offset : [0, -170]
      }

      {
        phase : 17
        part : [18, 6]
        tex { path:"stepped_pyramid/stepped_pyramid_00114" }
        offset : [0, -170]
      }

      {
        phase : 18
        part : [18, 4]
        tex { path:"stepped_pyramid/stepped_pyramid_00125" }
        offset : [-5, -170]
      }

      {
        phase : 19
        part : [12, 16]
        tex { path:"stepped_pyramid/stepped_pyramid_00110" }
        offset : [15, -200]
      }

      {
        phase : 20
        part : [14, 16]
        tex { path:"stepped_pyramid/stepped_pyramid_00111" }
        offset : [10, -200]
      }

      {
        phase : 20
        part : [16, 16]
        tex { path:"stepped_pyramid/stepped_pyramid_00123" }
        offset : [15, -205]
      }

      {
        phase : 21
        part : [16, 14]
        tex { path:"stepped_pyramid/stepped_pyramid_00115" }
        offset : [20, -200]
      }

      {
        phase : 22
        part : [14, 10]
        tex { path:"stepped_pyramid/stepped_pyramid_00113" }
        offset : [20, -210]
      }

      {
        phase : 23
        part : [14, 8]
        tex { path:"stepped_pyramid/stepped_pyramid_00114" }
        offset : [20, -210]
      }

      // --- Layer 2 (third tier): L2 south y=14 (begin+4, size 12) ? SE [14,14].
      // Offsets ~two tiers up (? -180..-270).
      {
        phase : 24
        part : [14, 6]
        tex { path:"stepped_pyramid/stepped_pyramid_00115" }
        offset : [15, -210]
      }

      {
        phase : 24
        part : [14, 4]
        tex { path:"stepped_pyramid/stepped_pyramid_00127" }
        offset : [10, -220]
      }

      {
        phase : 25
        part : [8, 14]
        tex { path:"stepped_pyramid/stepped_pyramid_00110" }
        offset : [0, -300]
      }

      {
        phase : 26
        part : [10, 14]
        tex { path:"stepped_pyramid/stepped_pyramid_00111" }
        offset : [0, -300]
      }

      {
        phase : 27
        part : [12, 14]
        tex { path:"stepped_pyramid/stepped_pyramid_00112" }
        offset : [0, -300]
      }

      {
        phase : 28
        part : [12, 10]
        tex { path:"stepped_pyramid/stepped_pyramid_00113" }
        offset : [20, -300]
      }

      {
        phase : 29
        part : [12, 8]
        tex { path:"stepped_pyramid/stepped_pyramid_00114" }
        offset : [15, -300]
      }

      {
        phase : 30
        part : [12, 6]
        tex { path:"stepped_pyramid/stepped_pyramid_00127" }
        offset : [15, -300]
      }

      {
        phase : 31
        part : [10, 12]
        tex { path:"stepped_pyramid/stepped_pyramid_00110" }
        offset : [0, -390]
      }

      {
        phase : 32
        part : [12, 12]
        tex { path:"stepped_pyramid/stepped_pyramid_00122" }
        offset : [0, -400]
      }

      {
        phase : 33
        part : [10, 12]
        tex { path:"stepped_pyramid/stepped_pyramid_00114" }
        offset : [0, -400]
      }
    ]

    flags {
        is_monument: true
        non_deletable: true
    }

    corner_type : BUILDING_LARGE_STEPPED_PYRAMID_CORNER
    wall_type : BUILDING_LARGE_STEPPED_PYRAMID_WALL
    cone_type : BUILDING_LARGE_STEPPED_PYRAMID_CONE
    filler_type : BUILDING_GRAND_STEPPED_PYRAMID_COMPLEX
  }


  // --- Bent pyramids (Snofru's, mission 14 South Dahshur) --------------------
  // The bent_pyramid image pack is structurally identical to stepped_pyramid
  // (159 "Bent_pyramid_*" main sprites at the same indices as "stepped_pyramid_*",
  // plus the shared "pyramid phase one_*" and "Pyramid buildings_*" groups). So the
  // config mirrors the stepped one with the pack + two path stems swapped, which
  // yields the real bent-pyramid art through the shared stepped render pipeline.
  building_small_bent_pyramid {
    animations {
      _pack { pack:PACK_BENT_PYRAMID }
      preview { id:2, offset:7 }
      base { id:2, offset:7 }
      base_bricks { path:"bent_pyramid/Bent_pyramid_00103" }
      corner_bricks { path:"bent_pyramid/Bent_pyramid_00001" }
      wall_bricks { path:"bent_pyramid/Bent_pyramid_00005" }
      base_grounded { path:"bent_pyramid/pyramid_phase_one_00013" }
      clear_land { id:2, offset:12 }
      image_stick { path:"bent_pyramid/pyramid_phase_one_00021" }
      empty_land {path:"bent_pyramid/Bent_pyramid_00109"}
      ramps {path:"bent_pyramid/Bent_pyramid_00110"}
      ditches_phase_1 { path:"bent_pyramid/pyramid_phase_one_00022" }
      ditches_phase_2 { path:"bent_pyramid/pyramid_phase_one_00031" }
      ditches_phase_3 { path:"bent_pyramid/pyramid_phase_one_00040" }
      ditches_phase_4 { path:"bent_pyramid/pyramid_phase_one_00049" }
      ground_phase_0 { path:"bent_pyramid/pyramid_phase_one_00013" }
      basement { path:"bent_pyramid/pyramid_phase_one_00058" }
      enter { path:"pharaoh_general/plazatiles_00064"}
    }
    build_menu_text : "Small Bent Pyramid"
    building_size : 2
    info_title_id [198, 1]
    fire_proof :  true
    damage_proof : true
    meta { text_id:178, help_link:"message_bent_pyramid" }
    init_tiles [8, 8]

    flags {
      is_monument: true
      non_deletable: true
    }

    enter_offset : [1, 8]
    stair_0_0_offset : [2, 8]
    stair_0_1_offset : [4, 8]
    stair_0_4_offset : [6, 8]
    stair_0_4_corner_offset : [6, 6]
    stair_0_5_offset : [6, 5]
    stair_0_6_offset : [6, 4]

    corner_type : BUILDING_SMALL_BENT_PYRAMID_CORNER
    wall_type : BUILDING_SMALL_BENT_PYRAMID_WALL
    cone_type : BUILDING_SMALL_BENT_PYRAMID_CONE
    filler_type : BUILDING_SMALL_BENT_PYRAMID
  }

  building_small_bent_pyramid_corner = building_small_bent_pyramid
  building_small_bent_pyramid_wall = building_small_bent_pyramid
  building_small_bent_pyramid_cone = building_small_bent_pyramid

  building_medium_bent_pyramid {
    animations {
      _pack { pack:PACK_BENT_PYRAMID }
      preview { pack:PACK_BENT_PYRAMID, id:2, offset:7 }
      base { id:2, offset:7 }
      base_bricks { path:"bent_pyramid/Bent_pyramid_00103" }
      corner_bricks { path:"bent_pyramid/Bent_pyramid_00001" }
      wall_bricks { path:"bent_pyramid/Bent_pyramid_00005" }
      base_grounded { path:"bent_pyramid/pyramid_phase_one_00013" }
      clear_land { id:2, offset:12 }
      image_stick { path:"bent_pyramid/pyramid_phase_one_00021" }
      empty_land {path:"bent_pyramid/Bent_pyramid_00109"}
      ramps {path:"bent_pyramid/Bent_pyramid_00110"}
      ditches_phase_1 { path:"bent_pyramid/pyramid_phase_one_00022" }
      ditches_phase_2 { path:"bent_pyramid/pyramid_phase_one_00031" }
      ditches_phase_3 { path:"bent_pyramid/pyramid_phase_one_00040" }
      ditches_phase_4 { path:"bent_pyramid/pyramid_phase_one_00049" }
      ground_phase_0 { path:"bent_pyramid/pyramid_phase_one_00013" }
      basement { path:"bent_pyramid/pyramid_phase_one_00058" }
      enter { path:"pharaoh_general/plazatiles_00064"}
      stair_0_2 { path:"bent_pyramid/Bent_pyramid_00112" }
      stair_0_4 { path:"bent_pyramid/Bent_pyramid_00110" }
      stair_0_4_corner { path:"bent_pyramid/Bent_pyramid_00122" }
      stair_0_5 { path:"bent_pyramid/Bent_pyramid_00114" }
      stair_0_6 { path:"bent_pyramid/Bent_pyramid_00115" }
    }
    build_menu_text : "Medium Bent Pyramid"
    building_size : 2
    info_title_id [198, 2]
    fire_proof :  true
    damage_proof : true
    meta { text_id:178, help_link:"message_bent_pyramid" }
    init_tiles [12, 12]

    enter_offset : [2, 12]

    stairs [
      {
        phase : 7
        part : [2, 10]
        tex { path:"bent_pyramid/Bent_pyramid_00110" }
        offset : [-15, 25]
      }

      {
        phase : 8
        part : [4, 10]
        tex { path:"bent_pyramid/Bent_pyramid_00111" }
        offset : [-15, 25]
      }

      {
        phase : 9
        part : [6, 10]
        tex { path:"bent_pyramid/Bent_pyramid_00112" }
        offset : [-15, 25]
      }

      {
        phase : 10
        part : [8, 10]
        tex { path:"bent_pyramid/Bent_pyramid_00110" }
        offset : [15, -35]
      }

      {
        phase : 10
        part : [10, 10]
        tex { path:"bent_pyramid/Bent_pyramid_00122" }
        offset : [15, -40]
      }

      {
        phase : 11
        part : [10, 8]
        tex { path:"bent_pyramid/Bent_pyramid_00114" }
        offset : [25, -30]
      }

      {
        phase : 12
        part : [10, 6]
        tex { path:"bent_pyramid/Bent_pyramid_00115" }
        offset : [20, -30]
      }

      {
        phase : 13
        part : [10, 4]
        tex { path:"bent_pyramid/Bent_pyramid_00113" }
        offset : [0, -90]
      }

      {
        phase : 13
        part : [10, 2]
        tex { path:"bent_pyramid/Bent_pyramid_00124" }
        offset : [0, -95]
      }

      {
        phase : 16
        part : [4, 8]
        tex { path:"bent_pyramid/Bent_pyramid_00118" }
        offset : [-28, -155]
      }

      {
        phase : 17
        part : [6, 8]
        tex { path:"bent_pyramid/Bent_pyramid_00111" }
        offset : [-48, -158]
      }

      {
        phase : 18
        part : [8, 8]
        tex { path:"bent_pyramid/Bent_pyramid_00112" }
        offset : [-48, -158]
      }

      {
        phase : 19
        part : [8, 6]
        tex { path:"bent_pyramid/Bent_pyramid_00113" }
        offset : [0, -180]
      }

      {
        phase : 20
        part : [8, 4]
        tex { path:"bent_pyramid/Bent_pyramid_00124" }
        offset : [-0, -180]
      }

      {
        phase : 21
        part : [4, 6]
        tex { path:"bent_pyramid/Bent_pyramid_00119" }
        offset : [-20, -175]
      }

      {
        phase : 21
        part : [6, 6]
        tex { path:"bent_pyramid/Bent_pyramid_00112" }
        offset : [-40, -175]
      }

      {
        phase : 22
        part : [6, 4]
        tex { path:"bent_pyramid/Bent_pyramid_00113" }
        offset : [10, -200]
      }
    ]

    flags {
        is_monument: true
        non_deletable: true
    }

    corner_type : BUILDING_MEDIUM_BENT_PYRAMID_CORNER
    wall_type : BUILDING_MEDIUM_BENT_PYRAMID_WALL
    cone_type : BUILDING_MEDIUM_BENT_PYRAMID_CONE
    filler_type : BUILDING_MEDIUM_BENT_PYRAMID
  }

  building_medium_bent_pyramid_corner = building_medium_bent_pyramid
  building_medium_bent_pyramid_wall = building_medium_bent_pyramid
  building_medium_bent_pyramid_cone = building_medium_bent_pyramid
  // --- True (smooth) pyramids — PACK_PYRAMID + limestone + polish ---
  // Same layout as stepped/bent (159 Pyramid_* + phase one + buildings). Polish
  // casing continues at Pyramid_00049 (OG offsets 48..88; finished row is 00089).
  building_small_pyramid {
    animations {
      _pack { pack:PACK_PYRAMID }
      preview { id:2, offset:7 }
      base { id:2, offset:7 }
      base_bricks { path:"Pyramid/Pyramid_00103" }
      corner_bricks { path:"Pyramid/Pyramid_00001" }
      wall_bricks { path:"Pyramid/Pyramid_00005" }
      // Rows after the 6 brick courses: OG (11-blocks)*8 for blocks 5..0.
      base_polish { path:"Pyramid/Pyramid_00103" }
      corner_polish { path:"Pyramid/Pyramid_00049" }
      wall_polish { path:"Pyramid/Pyramid_00053" }
      base_grounded { path:"Pyramid/pyramid_phase_one_00013" }
      clear_land { id:2, offset:12 }
      image_stick { path:"Pyramid/pyramid_phase_one_00021" }
      empty_land {path:"Pyramid/Pyramid_00109"}
      ramps {path:"Pyramid/Pyramid_00110"}
      ditches_phase_1 { path:"Pyramid/pyramid_phase_one_00022" }
      ditches_phase_2 { path:"Pyramid/pyramid_phase_one_00031" }
      ditches_phase_3 { path:"Pyramid/pyramid_phase_one_00040" }
      ditches_phase_4 { path:"Pyramid/pyramid_phase_one_00049" }
      ground_phase_0 { path:"Pyramid/pyramid_phase_one_00013" }
      basement { path:"Pyramid/pyramid_phase_one_00058" }
      enter { path:"pharaoh_general/plazatiles_00064"}
    }
    build_menu_text : "Small Pyramid"
    building_size : 2
    info_title_id [198, 13]
    fire_proof :  true
    damage_proof : true
    meta { text_id:178, help_link:"message_true_pyramid" }
    init_tiles [8, 8]

    flags {
      is_monument: true
      non_deletable: true
    }

    enter_offset : [1, 8]
    stair_0_0_offset : [2, 8]
    stair_0_1_offset : [4, 8]
    stair_0_4_offset : [6, 8]
    stair_0_4_corner_offset : [6, 6]
    stair_0_5_offset : [6, 5]
    stair_0_6_offset : [6, 4]

    corner_type : BUILDING_SMALL_PYRAMID_CORNER
    wall_type : BUILDING_SMALL_PYRAMID_WALL
    cone_type : BUILDING_SMALL_PYRAMID_CONE
    filler_type : BUILDING_SMALL_PYRAMID
    part_count : 16
    block_total : 216
    // OG pyramid_ramp_table (8×8).
    ramps [
      { part: 13, ramp1_height: 1 }
      { part: 14, ramp1_height: 2, ramp1_linked_part: 15 }
      { part: 11, ramp1_height: 3 }
      { part: 9, ramp1_height: 4, ramp1_linked_part: 7 }
      { part: 6, ramp1_height: 5 }
      { part: 5, ramp1_height: 6 }
    ]
    pyramide_type : PYRAMID_STYLE_TRUE
  }

  building_small_pyramid_corner = building_small_pyramid
  building_small_pyramid_wall = building_small_pyramid
  building_small_pyramid_cone = building_small_pyramid

  // --- Mudbrick (brick-core) pyramids — PACK_MUDBRICK_PYRAMID + bricks + limestone polish ---
  building_small_mudbrick_pyramid {
    animations {
      _pack { pack:PACK_MUDBRICK_PYRAMID }
      preview { id:2, offset:7 }
      base { id:2, offset:7 }
      base_bricks { path:"mudbrick_pyramid/mudbrick_pyramid_00103" }
      corner_bricks { path:"mudbrick_pyramid/mudbrick_pyramid_00001" }
      wall_bricks { path:"mudbrick_pyramid/mudbrick_pyramid_00005" }
      // Polish casing (same corner/wall offset layout as bricks, pack index +53)
      base_polish { path:"mudbrick_pyramid/mudbrick_pyramid_00103" }
      corner_polish { path:"mudbrick_pyramid/mudbrick_pyramid_00054" }
      wall_polish { path:"mudbrick_pyramid/mudbrick_pyramid_00058" }
      base_grounded { path:"mudbrick_pyramid/pyramid_phase_one_00013" }
      clear_land { id:2, offset:12 }
      image_stick { path:"mudbrick_pyramid/pyramid_phase_one_00021" }
      empty_land {path:"mudbrick_pyramid/mudbrick_pyramid_00109"}
      ramps {path:"mudbrick_pyramid/mudbrick_pyramid_00110"}
      ditches_phase_1 { path:"mudbrick_pyramid/pyramid_phase_one_00022" }
      ditches_phase_2 { path:"mudbrick_pyramid/pyramid_phase_one_00031" }
      ditches_phase_3 { path:"mudbrick_pyramid/pyramid_phase_one_00040" }
      ditches_phase_4 { path:"mudbrick_pyramid/pyramid_phase_one_00049" }
      ground_phase_0 { path:"mudbrick_pyramid/pyramid_phase_one_00013" }
      basement { path:"mudbrick_pyramid/pyramid_phase_one_00058" }
      enter { path:"pharaoh_general/plazatiles_00064"}
    }
    build_menu_text : "Small Brick Pyramid"
    building_size : 2
    info_title_id [198, 3]
    fire_proof :  true
    damage_proof : true
    meta { text_id:178, help_link:"message_brick_core_pyramid" }
    init_tiles [8, 8]

    flags {
      is_monument: true
      non_deletable: true
    }

    enter_offset : [1, 8]
    stair_0_0_offset : [2, 8]
    stair_0_1_offset : [4, 8]
    stair_0_4_offset : [6, 8]
    stair_0_4_corner_offset : [6, 6]
    stair_0_5_offset : [6, 5]
    stair_0_6_offset : [6, 4]

    corner_type : BUILDING_SMALL_MUDBRICK_PYRAMID_CORNER
    wall_type : BUILDING_SMALL_MUDBRICK_PYRAMID_WALL
    cone_type : BUILDING_SMALL_MUDBRICK_PYRAMID_CONE
    filler_type : BUILDING_SMALL_MUDBRICK_PYRAMID
    part_count : 16
    block_total : 216
    // OG pyramid_ramp_table (8×8).
    ramps [
      { part: 13, ramp1_height: 1 }
      { part: 14, ramp1_height: 2, ramp1_linked_part: 15 }
      { part: 11, ramp1_height: 3 }
      { part: 9, ramp1_height: 4, ramp1_linked_part: 7 }
      { part: 6, ramp1_height: 5 }
      { part: 5, ramp1_height: 6 }
    ]
    pyramide_type : PYRAMID_STYLE_MUDBRICK
  }

  building_small_mudbrick_pyramid_corner = building_small_mudbrick_pyramid
  building_small_mudbrick_pyramid_wall = building_small_mudbrick_pyramid
  building_small_mudbrick_pyramid_cone = building_small_mudbrick_pyramid

  // Medium mudbrick — 12×12; stairs mirrored from true medium. Pack stairs start at
  // 112 (no 110/111), so those two map to 112/113.
  building_medium_mudbrick_pyramid {
    animations {
      _pack { pack:PACK_MUDBRICK_PYRAMID }
      preview { id:2, offset:7 }
      base { id:2, offset:7 }
      base_bricks { path:"mudbrick_pyramid/mudbrick_pyramid_00103" }
      corner_bricks { path:"mudbrick_pyramid/mudbrick_pyramid_00001" }
      wall_bricks { path:"mudbrick_pyramid/mudbrick_pyramid_00005" }
      base_polish { path:"mudbrick_pyramid/mudbrick_pyramid_00103" }
      corner_polish { path:"mudbrick_pyramid/mudbrick_pyramid_00054" }
      wall_polish { path:"mudbrick_pyramid/mudbrick_pyramid_00058" }
      base_grounded { path:"mudbrick_pyramid/pyramid_phase_one_00013" }
      clear_land { id:2, offset:12 }
      image_stick { path:"mudbrick_pyramid/pyramid_phase_one_00021" }
      empty_land {path:"mudbrick_pyramid/mudbrick_pyramid_00109"}
      ramps {path:"mudbrick_pyramid/mudbrick_pyramid_00110"}
      ditches_phase_1 { path:"mudbrick_pyramid/pyramid_phase_one_00022" }
      ditches_phase_2 { path:"mudbrick_pyramid/pyramid_phase_one_00031" }
      ditches_phase_3 { path:"mudbrick_pyramid/pyramid_phase_one_00040" }
      ditches_phase_4 { path:"mudbrick_pyramid/pyramid_phase_one_00049" }
      ground_phase_0 { path:"mudbrick_pyramid/pyramid_phase_one_00013" }
      basement { path:"mudbrick_pyramid/pyramid_phase_one_00058" }
      enter { path:"pharaoh_general/plazatiles_00064"}
    }
    build_menu_text : "Medium Brick Pyramid"
    building_size : 2
    info_title_id [198, 4]
    fire_proof :  true
    damage_proof : true
    meta { text_id:178, help_link:"message_brick_core_pyramid" }
    init_tiles [12, 12]

    flags {
      is_monument: true
      non_deletable: true
    }

    enter_offset : [2, 12]
    stairs [
      {
        phase : 7
        part : [2, 10]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00112" }
        offset : [-15, 25]
      }

      {
        phase : 8
        part : [4, 10]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00113" }
        offset : [-15, 25]
      }

      {
        phase : 9
        part : [6, 10]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00112" }
        offset : [-15, 25]
      }

      {
        phase : 10
        part : [8, 10]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00112" }
        offset : [15, -35]
      }

      {
        phase : 10
        part : [10, 10]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00122" }
        offset : [15, -40]
      }

      {
        phase : 11
        part : [10, 8]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00114" }
        offset : [25, -30]
      }

      {
        phase : 12
        part : [10, 6]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00115" }
        offset : [20, -30]
      }

      {
        phase : 13
        part : [10, 4]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00113" }
        offset : [0, -90]
      }

      {
        phase : 13
        part : [10, 2]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00124" }
        offset : [0, -95]
      }

      {
        phase : 16
        part : [4, 8]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00118" }
        offset : [-28, -155]
      }

      {
        phase : 17
        part : [6, 8]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00113" }
        offset : [-48, -158]
      }

      {
        phase : 18
        part : [8, 8]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00112" }
        offset : [-48, -158]
      }

      {
        phase : 19
        part : [8, 6]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00113" }
        offset : [0, -180]
      }

      {
        phase : 20
        part : [8, 4]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00124" }
        offset : [-0, -180]
      }

      {
        phase : 21
        part : [4, 6]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00119" }
        offset : [-20, -175]
      }

      {
        phase : 21
        part : [6, 6]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00112" }
        offset : [-40, -175]
      }

      {
        phase : 22
        part : [6, 4]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00113" }
        offset : [10, -200]
      }
    ]

    corner_type : BUILDING_MEDIUM_MUDBRICK_PYRAMID_CORNER
    wall_type : BUILDING_MEDIUM_MUDBRICK_PYRAMID_WALL
    cone_type : BUILDING_MEDIUM_MUDBRICK_PYRAMID_CONE
    filler_type : BUILDING_MEDIUM_MUDBRICK_PYRAMID
    part_count : 36
    block_total : 552
    // OG pyramid_ramp_table (12×12).
    ramps [
      { part: 31, ramp1_height: 1 }
      { part: 32, ramp1_height: 2 }
      { part: 33, ramp1_height: 3 }
      { part: 34, ramp1_height: 4, ramp1_linked_part: 35 }
      { part: 29, ramp1_height: 5 }
      { part: 27, ramp1_height: 6 }
      { part: 9, ramp1_height: 7, ramp1_linked_part: 7 }
      { part: 6, ramp1_height: 8 }
      { part: 5, ramp1_height: 9 }
      { part: 8, ramp1_height: 10 }
      { part: 10, ramp1_height: 11, ramp1_linked_part: 12 }
      { part: 13, ramp1_height: 12 }
    ]
    pyramide_type : PYRAMID_STYLE_MUDBRICK
  }

  building_medium_mudbrick_pyramid_corner = building_medium_mudbrick_pyramid
  building_medium_mudbrick_pyramid_wall = building_medium_mudbrick_pyramid
  building_medium_mudbrick_pyramid_cone = building_medium_mudbrick_pyramid

  // Large mudbrick — 16×16 (≠ true Large 20×20). Stairs = medium pattern shifted
  // to the south/east faces of the larger footprint (y=14 / x=14).
  building_large_mudbrick_pyramid {
    animations {
      _pack { pack:PACK_MUDBRICK_PYRAMID }
      preview { id:2, offset:7 }
      base { id:2, offset:7 }
      base_bricks { path:"mudbrick_pyramid/mudbrick_pyramid_00103" }
      corner_bricks { path:"mudbrick_pyramid/mudbrick_pyramid_00001" }
      wall_bricks { path:"mudbrick_pyramid/mudbrick_pyramid_00005" }
      base_polish { path:"mudbrick_pyramid/mudbrick_pyramid_00103" }
      corner_polish { path:"mudbrick_pyramid/mudbrick_pyramid_00054" }
      wall_polish { path:"mudbrick_pyramid/mudbrick_pyramid_00058" }
      base_grounded { path:"mudbrick_pyramid/pyramid_phase_one_00013" }
      clear_land { id:2, offset:12 }
      image_stick { path:"mudbrick_pyramid/pyramid_phase_one_00021" }
      empty_land {path:"mudbrick_pyramid/mudbrick_pyramid_00109"}
      ramps {path:"mudbrick_pyramid/mudbrick_pyramid_00110"}
      ditches_phase_1 { path:"mudbrick_pyramid/pyramid_phase_one_00022" }
      ditches_phase_2 { path:"mudbrick_pyramid/pyramid_phase_one_00031" }
      ditches_phase_3 { path:"mudbrick_pyramid/pyramid_phase_one_00040" }
      ditches_phase_4 { path:"mudbrick_pyramid/pyramid_phase_one_00049" }
      ground_phase_0 { path:"mudbrick_pyramid/pyramid_phase_one_00013" }
      basement { path:"mudbrick_pyramid/pyramid_phase_one_00058" }
      enter { path:"pharaoh_general/plazatiles_00064"}
    }
    build_menu_text : "Large Brick Pyramid"
    building_size : 2
    info_title_id [198, 5]
    fire_proof :  true
    damage_proof : true
    meta { text_id:178, help_link:"message_brick_core_pyramid" }
    init_tiles [16, 16]

    flags {
      is_monument: true
      non_deletable: true
    }

    enter_offset : [2, 16]
    stairs [
      {
        phase : 7
        part : [2, 14]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00112" }
        offset : [-15, 25]
      }

      {
        phase : 8
        part : [4, 14]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00113" }
        offset : [-15, 25]
      }

      {
        phase : 9
        part : [6, 14]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00112" }
        offset : [-15, 25]
      }

      {
        phase : 10
        part : [10, 14]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00112" }
        offset : [15, -35]
      }

      {
        phase : 10
        part : [14, 14]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00122" }
        offset : [15, -40]
      }

      {
        phase : 11
        part : [14, 12]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00114" }
        offset : [25, -30]
      }

      {
        phase : 12
        part : [14, 10]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00115" }
        offset : [20, -30]
      }

      {
        phase : 13
        part : [14, 6]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00113" }
        offset : [0, -90]
      }

      {
        phase : 13
        part : [14, 2]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00124" }
        offset : [0, -95]
      }

      {
        phase : 16
        part : [6, 12]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00118" }
        offset : [-28, -155]
      }

      {
        phase : 17
        part : [8, 12]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00113" }
        offset : [-48, -158]
      }

      {
        phase : 18
        part : [12, 12]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00112" }
        offset : [-48, -158]
      }

      {
        phase : 19
        part : [12, 10]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00113" }
        offset : [0, -180]
      }

      {
        phase : 20
        part : [12, 6]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00124" }
        offset : [0, -180]
      }

      {
        phase : 21
        part : [6, 10]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00119" }
        offset : [-20, -175]
      }

      {
        phase : 21
        part : [8, 10]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00112" }
        offset : [-40, -175]
      }

      {
        phase : 22
        part : [8, 6]
        tex { path:"mudbrick_pyramid/mudbrick_pyramid_00113" }
        offset : [10, -200]
      }
    ]

    corner_type : BUILDING_LARGE_MUDBRICK_PYRAMID_CORNER
    wall_type : BUILDING_LARGE_MUDBRICK_PYRAMID_WALL
    cone_type : BUILDING_LARGE_MUDBRICK_PYRAMID_CONE
    filler_type : BUILDING_LARGE_MUDBRICK_PYRAMID
    part_count : 64
    block_total : 1104
    // OG pyramid_ramp_table (16×16).
    ramps [
      { part: 57, ramp1_height: 1 }
      { part: 58, ramp1_height: 2 }
      { part: 59, ramp1_height: 3 }
      { part: 60, ramp1_height: 4 }
      { part: 61, ramp1_height: 5 }
      { part: 62, ramp1_height: 6 }
      { part: 29, ramp1_height: 7 }
      { part: 27, ramp1_height: 8 }
      { part: 25, ramp1_height: 9 }
      { part: 23, ramp1_height: 10, ramp1_linked_part: 21 }
      { part: 20, ramp1_height: 11 }
      { part: 19, ramp1_height: 12 }
      { part: 5, ramp1_height: 13, ramp1_linked_part: 4 }
      { part: 8, ramp1_height: 14 }
      { part: 10, ramp1_height: 15 }
      { part: 13, ramp1_height: 16 }
      { part: 14, ramp1_height: 17, ramp1_linked_part: 15 }
      { part: 11, ramp1_height: 18 }
    ]
    pyramide_type : PYRAMID_STYLE_MUDBRICK
  }

  building_large_mudbrick_pyramid_corner = building_large_mudbrick_pyramid
  building_large_mudbrick_pyramid_wall = building_large_mudbrick_pyramid
  building_large_mudbrick_pyramid_cone = building_large_mudbrick_pyramid

  // Mudbrick complex — on-land 20x20 + causeway annex (types 218–220). Reuses LARGE_MUDBRICK parts.
  building_mudbrick_pyramid_complex {
    animations {
      _pack { pack:PACK_MUDBRICK_PYRAMID }
      preview { id:2, offset:7 }
      base { id:2, offset:7 }
      base_bricks { path:"mudbrick_pyramid/mudbrick_pyramid_00103" }
      corner_bricks { path:"mudbrick_pyramid/mudbrick_pyramid_00001" }
      wall_bricks { path:"mudbrick_pyramid/mudbrick_pyramid_00005" }
      base_polish { path:"mudbrick_pyramid/mudbrick_pyramid_00103" }
      corner_polish { path:"mudbrick_pyramid/mudbrick_pyramid_00054" }
      wall_polish { path:"mudbrick_pyramid/mudbrick_pyramid_00058" }
      base_grounded { path:"mudbrick_pyramid/pyramid_phase_one_00013" }
      clear_land { id:2, offset:12 }
      image_stick { path:"mudbrick_pyramid/pyramid_phase_one_00021" }
      empty_land {path:"mudbrick_pyramid/mudbrick_pyramid_00109"}
      ramps {path:"mudbrick_pyramid/mudbrick_pyramid_00110"}
      ditches_phase_1 { path:"mudbrick_pyramid/pyramid_phase_one_00022" }
      ditches_phase_2 { path:"mudbrick_pyramid/pyramid_phase_one_00031" }
      ditches_phase_3 { path:"mudbrick_pyramid/pyramid_phase_one_00040" }
      ditches_phase_4 { path:"mudbrick_pyramid/pyramid_phase_one_00049" }
      ground_phase_0 { path:"mudbrick_pyramid/pyramid_phase_one_00013" }
      basement { path:"mudbrick_pyramid/pyramid_phase_one_00058" }
      enter { path:"pharaoh_general/plazatiles_00064"}
      // OG image_mausoleum_walkway_b = pack group 8 (58×48), not clear_land.
      complex_walkway { id:8, offset:0 }
    }
    build_menu_text : "Mudbrick Pyramid Complex"
    building_size : 2
    info_title_id [198, 6]
    fire_proof :  true
    damage_proof : true
    meta { text_id:178, help_link:"message_brick_core_pyramid" }
    init_tiles [20, 20]

    flags {
      is_monument: true
      non_deletable: true
    }

    enter_offset : [2, 20]
    stairs [
      { phase : 7, part : [4, 18], tex { path:"mudbrick_pyramid/mudbrick_pyramid_00112" }, offset : [-20, 20] }
      { phase : 8, part : [6, 18], tex { path:"mudbrick_pyramid/mudbrick_pyramid_00113" }, offset : [-25, 20] }
      { phase : 9, part : [8, 18], tex { path:"mudbrick_pyramid/mudbrick_pyramid_00112" }, offset : [-20, 20] }
      { phase : 10, part : [12, 18], tex { path:"mudbrick_pyramid/mudbrick_pyramid_00112" }, offset : [0, -40] }
      { phase : 11, part : [14, 18], tex { path:"mudbrick_pyramid/mudbrick_pyramid_00113" }, offset : [-5, -40] }
      { phase : 12, part : [16, 18], tex { path:"mudbrick_pyramid/mudbrick_pyramid_00112" }, offset : [-5, -45] }
      { phase : 13, part : [18, 14], tex { path:"mudbrick_pyramid/mudbrick_pyramid_00113" }, offset : [10, -100] }
      { phase : 14, part : [18, 12], tex { path:"mudbrick_pyramid/mudbrick_pyramid_00114" }, offset : [0, -100] }
      { phase : 15, part : [18, 10], tex { path:"mudbrick_pyramid/mudbrick_pyramid_00115" }, offset : [-5, -100] }
      { phase : 16, part : [18, 8], tex { path:"mudbrick_pyramid/mudbrick_pyramid_00113" }, offset : [0, -170] }
      { phase : 18, part : [18, 6], tex { path:"mudbrick_pyramid/mudbrick_pyramid_00114" }, offset : [0, -170] }
      { phase : 20, part : [18, 4], tex { path:"mudbrick_pyramid/mudbrick_pyramid_00124" }, offset : [0, -180] }
    ]

    corner_type : BUILDING_LARGE_MUDBRICK_PYRAMID_CORNER
    wall_type : BUILDING_LARGE_MUDBRICK_PYRAMID_WALL
    cone_type : BUILDING_LARGE_MUDBRICK_PYRAMID_CONE
    filler_type : BUILDING_MUDBRICK_PYRAMID_COMPLEX
    part_count : 100
    block_total : 1920
    // OG pyramid_ramp_table (20×20 complex).
    ramps [
      { part: 91, ramp1_height: 1 }
      { part: 92, ramp1_height: 2 }
      { part: 93, ramp1_height: 3 }
      { part: 94, ramp1_height: 4 }
      { part: 95, ramp1_height: 5 }
      { part: 96, ramp1_height: 6 }
      { part: 62, ramp1_height: 7, ramp1_linked_part: 63 }
      { part: 55, ramp1_height: 8 }
      { part: 53, ramp1_height: 9 }
      { part: 51, ramp1_height: 10 }
      { part: 49, ramp1_height: 11 }
      { part: 47, ramp1_height: 12 }
      { part: 20, ramp1_height: 13 }
      { part: 19, ramp1_height: 14 }
      { part: 18, ramp1_height: 15 }
      { part: 17, ramp1_height: 16, ramp1_linked_part: 16 }
      { part: 22, ramp1_height: 17 }
      { part: 24, ramp1_height: 18 }
      { part: 10, ramp1_height: 19, ramp1_linked_part: 12 }
      { part: 13, ramp1_height: 20 }
      { part: 14, ramp1_height: 21 }
      { part: 11, ramp1_height: 22 }
      { part: 9, ramp1_height: 23, ramp1_linked_part: 7 }
      { part: 6, ramp1_height: 24 }
    ]
    pyramide_type : PYRAMID_STYLE_MUDBRICK
  }

  // Grand mudbrick — same on-land 20x20; own TYPE for weight 44.
  building_grand_mudbrick_pyramid_complex {
    animations {
      _pack { pack:PACK_MUDBRICK_PYRAMID }
      preview { id:2, offset:7 }
      base { id:2, offset:7 }
      base_bricks { path:"mudbrick_pyramid/mudbrick_pyramid_00103" }
      corner_bricks { path:"mudbrick_pyramid/mudbrick_pyramid_00001" }
      wall_bricks { path:"mudbrick_pyramid/mudbrick_pyramid_00005" }
      base_polish { path:"mudbrick_pyramid/mudbrick_pyramid_00103" }
      corner_polish { path:"mudbrick_pyramid/mudbrick_pyramid_00054" }
      wall_polish { path:"mudbrick_pyramid/mudbrick_pyramid_00058" }
      base_grounded { path:"mudbrick_pyramid/pyramid_phase_one_00013" }
      clear_land { id:2, offset:12 }
      image_stick { path:"mudbrick_pyramid/pyramid_phase_one_00021" }
      empty_land {path:"mudbrick_pyramid/mudbrick_pyramid_00109"}
      ramps {path:"mudbrick_pyramid/mudbrick_pyramid_00110"}
      ditches_phase_1 { path:"mudbrick_pyramid/pyramid_phase_one_00022" }
      ditches_phase_2 { path:"mudbrick_pyramid/pyramid_phase_one_00031" }
      ditches_phase_3 { path:"mudbrick_pyramid/pyramid_phase_one_00040" }
      ditches_phase_4 { path:"mudbrick_pyramid/pyramid_phase_one_00049" }
      ground_phase_0 { path:"mudbrick_pyramid/pyramid_phase_one_00013" }
      basement { path:"mudbrick_pyramid/pyramid_phase_one_00058" }
      enter { path:"pharaoh_general/plazatiles_00064"}
      complex_walkway { id:8, offset:0 }
    }
    build_menu_text : "Grand Mudbrick Pyramid Complex"
    building_size : 2
    info_title_id [198, 7]
    fire_proof :  true
    damage_proof : true
    meta { text_id:178, help_link:"message_brick_core_pyramid" }
    init_tiles [20, 20]

    flags {
      is_monument: true
      non_deletable: true
    }

    enter_offset : [2, 20]
    stairs [
      { phase : 7, part : [4, 18], tex { path:"mudbrick_pyramid/mudbrick_pyramid_00112" }, offset : [-20, 20] }
      { phase : 10, part : [12, 18], tex { path:"mudbrick_pyramid/mudbrick_pyramid_00112" }, offset : [0, -40] }
      { phase : 12, part : [16, 18], tex { path:"mudbrick_pyramid/mudbrick_pyramid_00122" }, offset : [-5, -45] }
      { phase : 14, part : [18, 12], tex { path:"mudbrick_pyramid/mudbrick_pyramid_00114" }, offset : [0, -100] }
      { phase : 16, part : [18, 8], tex { path:"mudbrick_pyramid/mudbrick_pyramid_00113" }, offset : [0, -170] }
      { phase : 20, part : [18, 4], tex { path:"mudbrick_pyramid/mudbrick_pyramid_00124" }, offset : [0, -180] }
    ]

    corner_type : BUILDING_LARGE_MUDBRICK_PYRAMID_CORNER
    wall_type : BUILDING_LARGE_MUDBRICK_PYRAMID_WALL
    cone_type : BUILDING_LARGE_MUDBRICK_PYRAMID_CONE
    filler_type : BUILDING_GRAND_MUDBRICK_PYRAMID_COMPLEX
    part_count : 100
    block_total : 1920
    // OG size-4 schedule needs 24×24; remake grand is still 20×20 → complex table.
    ramps [
      { part: 91, ramp1_height: 1 }
      { part: 92, ramp1_height: 2 }
      { part: 93, ramp1_height: 3 }
      { part: 94, ramp1_height: 4 }
      { part: 95, ramp1_height: 5 }
      { part: 96, ramp1_height: 6 }
      { part: 62, ramp1_height: 7, ramp1_linked_part: 63 }
      { part: 55, ramp1_height: 8 }
      { part: 53, ramp1_height: 9 }
      { part: 51, ramp1_height: 10 }
      { part: 49, ramp1_height: 11 }
      { part: 47, ramp1_height: 12 }
      { part: 20, ramp1_height: 13 }
      { part: 19, ramp1_height: 14 }
      { part: 18, ramp1_height: 15 }
      { part: 17, ramp1_height: 16, ramp1_linked_part: 16 }
      { part: 22, ramp1_height: 17 }
      { part: 24, ramp1_height: 18 }
      { part: 10, ramp1_height: 19, ramp1_linked_part: 12 }
      { part: 13, ramp1_height: 20 }
      { part: 14, ramp1_height: 21 }
      { part: 11, ramp1_height: 22 }
      { part: 9, ramp1_height: 23, ramp1_linked_part: 7 }
      { part: 6, ramp1_height: 24 }
    ]
    pyramide_type : PYRAMID_STYLE_MUDBRICK
  }

  // OG complex annex 0xDA–0xDC = consecutive pack groups 9/10/11.
  // Pack comes from the parent complex `_pack` at place time; only group ids here.
  building_mortuary_temple {
    animations {
      _pack { pack:PACK_MUDBRICK_PYRAMID }
      base { id:9, offset:0 }
    }
    building_size : 2
    fire_proof : true
    damage_proof : true
    flags {
      is_monument: true
      non_deletable: true
    }
  }

  building_pyramid_causeway {
    animations {
      _pack { pack:PACK_MUDBRICK_PYRAMID }
      base { id:10, offset:0 }
    }
    building_size : 2
    fire_proof : true
    damage_proof : true
    flags {
      is_monument: true
      non_deletable: true
    }
  }

  building_valley_temple {
    animations {
      _pack { pack:PACK_MUDBRICK_PYRAMID }
      base { id:11, offset:0 }
    }
    building_size : 2
    fire_proof : true
    damage_proof : true
    flags {
      is_monument: true
      non_deletable: true
    }
  }

  building_medium_pyramid {
    animations {
      _pack { pack:PACK_PYRAMID }
      preview { id:2, offset:7 }
      base { id:2, offset:7 }
      base_bricks { path:"Pyramid/Pyramid_00103" }
      corner_bricks { path:"Pyramid/Pyramid_00001" }
      wall_bricks { path:"Pyramid/Pyramid_00005" }
      base_polish { path:"Pyramid/Pyramid_00103" }
      corner_polish { path:"Pyramid/Pyramid_00049" }
      wall_polish { path:"Pyramid/Pyramid_00053" }
      base_grounded { path:"Pyramid/pyramid_phase_one_00013" }
      clear_land { id:2, offset:12 }
      image_stick { path:"Pyramid/pyramid_phase_one_00021" }
      empty_land {path:"Pyramid/Pyramid_00109"}
      ramps {path:"Pyramid/Pyramid_00110"}
      ditches_phase_1 { path:"Pyramid/pyramid_phase_one_00022" }
      ditches_phase_2 { path:"Pyramid/pyramid_phase_one_00031" }
      ditches_phase_3 { path:"Pyramid/pyramid_phase_one_00040" }
      ditches_phase_4 { path:"Pyramid/pyramid_phase_one_00049" }
      ground_phase_0 { path:"Pyramid/pyramid_phase_one_00013" }
      basement { path:"Pyramid/pyramid_phase_one_00058" }
      enter { path:"pharaoh_general/plazatiles_00064"}
    }
    build_menu_text : "Medium Pyramid"
    building_size : 2
    info_title_id [198, 13]
    fire_proof :  true
    damage_proof : true
    meta { text_id:178, help_link:"message_true_pyramid" }
    init_tiles [12, 12]

    flags {
      is_monument: true
      non_deletable: true
    }

    enter_offset : [2, 12]
    stairs [
      {
        phase : 7
        part : [2, 10]
        tex { path:"Pyramid/Pyramid_00110" }
        offset : [-15, 25]
      }

      {
        phase : 8
        part : [4, 10]
        tex { path:"Pyramid/Pyramid_00111" }
        offset : [-15, 25]
      }

      {
        phase : 9
        part : [6, 10]
        tex { path:"Pyramid/Pyramid_00112" }
        offset : [-15, 25]
      }

      {
        phase : 10
        part : [8, 10]
        tex { path:"Pyramid/Pyramid_00110" }
        offset : [15, -35]
      }

      {
        phase : 10
        part : [10, 10]
        tex { path:"Pyramid/Pyramid_00122" }
        offset : [15, -40]
      }

      {
        phase : 11
        part : [10, 8]
        tex { path:"Pyramid/Pyramid_00114" }
        offset : [25, -30]
      }

      {
        phase : 12
        part : [10, 6]
        tex { path:"Pyramid/Pyramid_00115" }
        offset : [20, -30]
      }

      {
        phase : 13
        part : [10, 4]
        tex { path:"Pyramid/Pyramid_00113" }
        offset : [0, -90]
      }

      {
        phase : 13
        part : [10, 2]
        tex { path:"Pyramid/Pyramid_00124" }
        offset : [0, -95]
      }

      {
        phase : 16
        part : [4, 8]
        tex { path:"Pyramid/Pyramid_00118" }
        offset : [-28, -155]
      }

      {
        phase : 17
        part : [6, 8]
        tex { path:"Pyramid/Pyramid_00111" }
        offset : [-48, -158]
      }

      {
        phase : 18
        part : [8, 8]
        tex { path:"Pyramid/Pyramid_00112" }
        offset : [-48, -158]
      }

      {
        phase : 19
        part : [8, 6]
        tex { path:"Pyramid/Pyramid_00113" }
        offset : [0, -180]
      }

      {
        phase : 20
        part : [8, 4]
        tex { path:"Pyramid/Pyramid_00124" }
        offset : [-0, -180]
      }

      {
        phase : 21
        part : [4, 6]
        tex { path:"Pyramid/Pyramid_00119" }
        offset : [-20, -175]
      }

      {
        phase : 21
        part : [6, 6]
        tex { path:"Pyramid/Pyramid_00112" }
        offset : [-40, -175]
      }

      {
        phase : 22
        part : [6, 4]
        tex { path:"Pyramid/Pyramid_00113" }
        offset : [10, -200]
      }
    ]


    corner_type : BUILDING_MEDIUM_PYRAMID_CORNER
    wall_type : BUILDING_MEDIUM_PYRAMID_WALL
    cone_type : BUILDING_MEDIUM_PYRAMID_CONE
    filler_type : BUILDING_MEDIUM_PYRAMID
    part_count : 36
    block_total : 552
    // OG pyramid_ramp_table (12×12).
    ramps [
      { part: 31, ramp1_height: 1 }
      { part: 32, ramp1_height: 2 }
      { part: 33, ramp1_height: 3 }
      { part: 34, ramp1_height: 4, ramp1_linked_part: 35 }
      { part: 29, ramp1_height: 5 }
      { part: 27, ramp1_height: 6 }
      { part: 9, ramp1_height: 7, ramp1_linked_part: 7 }
      { part: 6, ramp1_height: 8 }
      { part: 5, ramp1_height: 9 }
      { part: 8, ramp1_height: 10 }
      { part: 10, ramp1_height: 11, ramp1_linked_part: 12 }
      { part: 13, ramp1_height: 12 }
    ]
    pyramide_type : PYRAMID_STYLE_TRUE
  }

  building_medium_pyramid_corner = building_medium_pyramid
  building_medium_pyramid_wall = building_medium_pyramid
  building_medium_pyramid_cone = building_medium_pyramid

  building_large_pyramid {
    animations {
      _pack { pack:PACK_PYRAMID }
      preview { pack:PACK_PYRAMID, id:2, offset:7 }
      base { id:2, offset:7 }
      base_bricks { path:"Pyramid/Pyramid_00103" }
      corner_bricks { path:"Pyramid/Pyramid_00001" }
      wall_bricks { path:"Pyramid/Pyramid_00005" }
      base_polish { path:"Pyramid/Pyramid_00103" }
      corner_polish { path:"Pyramid/Pyramid_00049" }
      wall_polish { path:"Pyramid/Pyramid_00053" }
      base_grounded { path:"Pyramid/pyramid_phase_one_00013" }
      clear_land { id:2, offset:12 }
      image_stick { path:"Pyramid/pyramid_phase_one_00021" }
      empty_land {path:"Pyramid/Pyramid_00109"}
      ramps {path:"Pyramid/Pyramid_00110"}
      ditches_phase_1 { path:"Pyramid/pyramid_phase_one_00022" }
      ditches_phase_2 { path:"Pyramid/pyramid_phase_one_00031" }
      ditches_phase_3 { path:"Pyramid/pyramid_phase_one_00040" }
      ditches_phase_4 { path:"Pyramid/pyramid_phase_one_00049" }
      ground_phase_0 { path:"Pyramid/pyramid_phase_one_00013" }
      basement { path:"Pyramid/pyramid_phase_one_00058" }
      enter { path:"pharaoh_general/plazatiles_00064"}
      stair_0_2 { path:"Pyramid/Pyramid_00112" }
      stair_0_4 { path:"Pyramid/Pyramid_00110" }
      stair_0_4_corner { path:"Pyramid/Pyramid_00122" }
      stair_0_5 { path:"Pyramid/Pyramid_00114" }
      stair_0_6 { path:"Pyramid/Pyramid_00115" }
    }
    build_menu_text : "Large Pyramid"
    building_size : 2
    info_title_id [198, 14]
    fire_proof :  true
    damage_proof : true
    meta { text_id:178, help_link:"message_true_pyramid" }
    init_tiles [20, 20]

    enter_offset : [2, 20]

    // Medium-style L-ramp: short approach on south from enter, SE corner, then
    // climb the east face (decreasing y) up to the tier-1 ledge. Sprites 00114+
    // are the ascending ramp pieces; offset.y rises ~+28 ? -110 (? one tier).
    stairs [
      {
        phase : 7
        part : [4, 18]
        tex { path:"Pyramid/Pyramid_00110" }
        offset : [-20, 20]
      }

      {
        phase : 8
        part : [6, 18]
        tex { path:"Pyramid/Pyramid_00111" }
        offset : [-25, 20]
      }

      {
        phase : 9
        part : [8, 18]
        tex { path:"Pyramid/Pyramid_00112" }
        offset : [-20, 20]
      }

      {
        phase : 10
        part : [12, 18]
        tex { path:"Pyramid/Pyramid_00110" }
        offset : [0, -40]
      }

      {
        phase : 11
        part : [14, 18]
        tex { path:"Pyramid/Pyramid_00111" }
        offset : [-5, -40]
      }

      {
        phase : 12
        part : [16, 18]
        tex { path:"Pyramid/Pyramid_00112" }
        offset : [-5, -45]
      }

      {
        phase : 13
        part : [18, 14]
        tex { path:"Pyramid/Pyramid_00113" }
        offset : [10, -100]
      }

      {
        phase : 14
        part : [18, 12]
        tex { path:"Pyramid/Pyramid_00114" }
        offset : [0, -100]
      }

      {
        phase : 15
        part : [18, 10]
        tex { path:"Pyramid/Pyramid_00115" }
        offset : [-5, -100]
      }

      {
        phase : 16
        part : [18, 8]
        tex { path:"Pyramid/Pyramid_00113" }
        offset : [0, -170]
      }

      {
        phase : 17
        part : [18, 6]
        tex { path:"Pyramid/Pyramid_00114" }
        offset : [0, -170]
      }

      {
        phase : 18
        part : [18, 4]
        tex { path:"Pyramid/Pyramid_00125" }
        offset : [-5, -170]
      }

      {
        phase : 19
        part : [12, 16]
        tex { path:"Pyramid/Pyramid_00110" }
        offset : [15, -200]
      }

      {
        phase : 20
        part : [14, 16]
        tex { path:"Pyramid/Pyramid_00111" }
        offset : [10, -200]
      }

      {
        phase : 20
        part : [16, 16]
        tex { path:"Pyramid/Pyramid_00123" }
        offset : [15, -205]
      }

      {
        phase : 21
        part : [16, 14]
        tex { path:"Pyramid/Pyramid_00115" }
        offset : [20, -200]
      }

      {
        phase : 22
        part : [14, 10]
        tex { path:"Pyramid/Pyramid_00113" }
        offset : [20, -210]
      }

      {
        phase : 23
        part : [14, 8]
        tex { path:"Pyramid/Pyramid_00114" }
        offset : [20, -210]
      }

      // --- Layer 2 (third tier): L2 south y=14 (begin+4, size 12) ? SE [14,14].
      // Offsets ~two tiers up (? -180..-270).
      {
        phase : 24
        part : [14, 6]
        tex { path:"Pyramid/Pyramid_00115" }
        offset : [15, -210]
      }

      {
        phase : 24
        part : [14, 4]
        tex { path:"Pyramid/Pyramid_00127" }
        offset : [10, -220]
      }

      {
        phase : 25
        part : [8, 14]
        tex { path:"Pyramid/Pyramid_00110" }
        offset : [0, -300]
      }

      {
        phase : 26
        part : [10, 14]
        tex { path:"Pyramid/Pyramid_00111" }
        offset : [0, -300]
      }

      {
        phase : 27
        part : [12, 14]
        tex { path:"Pyramid/Pyramid_00112" }
        offset : [0, -300]
      }

      {
        phase : 28
        part : [12, 10]
        tex { path:"Pyramid/Pyramid_00113" }
        offset : [20, -300]
      }

      {
        phase : 29
        part : [12, 8]
        tex { path:"Pyramid/Pyramid_00114" }
        offset : [15, -300]
      }

      {
        phase : 30
        part : [12, 6]
        tex { path:"Pyramid/Pyramid_00127" }
        offset : [15, -300]
      }

      {
        phase : 31
        part : [10, 12]
        tex { path:"Pyramid/Pyramid_00110" }
        offset : [0, -390]
      }

      {
        phase : 32
        part : [12, 12]
        tex { path:"Pyramid/Pyramid_00122" }
        offset : [0, -400]
      }

      {
        phase : 33
        part : [10, 12]
        tex { path:"Pyramid/Pyramid_00114" }
        offset : [0, -400]
      }
    ]

    flags {
        is_monument: true
        non_deletable: true
    }

    corner_type : BUILDING_LARGE_PYRAMID_CORNER
    wall_type : BUILDING_LARGE_PYRAMID_WALL
    cone_type : BUILDING_LARGE_PYRAMID_CONE
    filler_type : BUILDING_LARGE_PYRAMID
    part_count : 64
    block_total : 1104
    // OG pyramid_ramp_table (16×16).
    ramps [
      { part: 57, ramp1_height: 1 }
      { part: 58, ramp1_height: 2 }
      { part: 59, ramp1_height: 3 }
      { part: 60, ramp1_height: 4 }
      { part: 61, ramp1_height: 5 }
      { part: 62, ramp1_height: 6 }
      { part: 29, ramp1_height: 7 }
      { part: 27, ramp1_height: 8 }
      { part: 25, ramp1_height: 9 }
      { part: 23, ramp1_height: 10, ramp1_linked_part: 21 }
      { part: 20, ramp1_height: 11 }
      { part: 19, ramp1_height: 12 }
      { part: 5, ramp1_height: 13, ramp1_linked_part: 4 }
      { part: 8, ramp1_height: 14 }
      { part: 10, ramp1_height: 15 }
      { part: 13, ramp1_height: 16 }
      { part: 14, ramp1_height: 17, ramp1_linked_part: 15 }
      { part: 11, ramp1_height: 18 }
    ]
    pyramide_type : PYRAMID_STYLE_TRUE
  }


  building_large_pyramid_corner = building_large_pyramid
  building_large_pyramid_wall = building_large_pyramid
  building_large_pyramid_cone = building_large_pyramid

  // True pyramid complex = plain 20x20 (same as large; causeway/temples later).
  // Reuses LARGE_PYRAMID part types 344-346.
  building_pyramid_complex {
    animations {
      _pack { pack:PACK_PYRAMID }
      preview { pack:PACK_PYRAMID, id:2, offset:7 }
      base { id:2, offset:7 }
      base_bricks { path:"Pyramid/Pyramid_00103" }
      corner_bricks { path:"Pyramid/Pyramid_00001" }
      wall_bricks { path:"Pyramid/Pyramid_00005" }
      base_polish { path:"Pyramid/Pyramid_00103" }
      corner_polish { path:"Pyramid/Pyramid_00049" }
      wall_polish { path:"Pyramid/Pyramid_00053" }
      base_grounded { path:"Pyramid/pyramid_phase_one_00013" }
      clear_land { id:2, offset:12 }
      image_stick { path:"Pyramid/pyramid_phase_one_00021" }
      empty_land {path:"Pyramid/Pyramid_00109"}
      ramps {path:"Pyramid/Pyramid_00110"}
      ditches_phase_1 { path:"Pyramid/pyramid_phase_one_00022" }
      ditches_phase_2 { path:"Pyramid/pyramid_phase_one_00031" }
      ditches_phase_3 { path:"Pyramid/pyramid_phase_one_00040" }
      ditches_phase_4 { path:"Pyramid/pyramid_phase_one_00049" }
      ground_phase_0 { path:"Pyramid/pyramid_phase_one_00013" }
      basement { path:"Pyramid/pyramid_phase_one_00058" }
      enter { path:"pharaoh_general/plazatiles_00064"}
      // OG image_mausoleum_walkway_b = pack group 8 (same as mudbrick complex).
      complex_walkway { id:8, offset:0 }
      stair_0_2 { path:"Pyramid/Pyramid_00112" }
      stair_0_4 { path:"Pyramid/Pyramid_00110" }
      stair_0_4_corner { path:"Pyramid/Pyramid_00122" }
      stair_0_5 { path:"Pyramid/Pyramid_00114" }
      stair_0_6 { path:"Pyramid/Pyramid_00115" }
    }
    build_menu_text : "Pyramid Complex"
    building_size : 2
    info_title_id [198, 15]
    fire_proof :  true
    damage_proof : true
    meta { text_id:178, help_link:"message_true_pyramid" }
    init_tiles [20, 20]

    enter_offset : [2, 20]

    // Medium-style L-ramp: short approach on south from enter, SE corner, then
    // climb the east face (decreasing y) up to the tier-1 ledge. Sprites 00114+
    // are the ascending ramp pieces; offset.y rises ~+28 ? -110 (? one tier).
    stairs [
      {
        phase : 7
        part : [4, 18]
        tex { path:"Pyramid/Pyramid_00110" }
        offset : [-20, 20]
      }

      {
        phase : 8
        part : [6, 18]
        tex { path:"Pyramid/Pyramid_00111" }
        offset : [-25, 20]
      }

      {
        phase : 9
        part : [8, 18]
        tex { path:"Pyramid/Pyramid_00112" }
        offset : [-20, 20]
      }

      {
        phase : 10
        part : [12, 18]
        tex { path:"Pyramid/Pyramid_00110" }
        offset : [0, -40]
      }

      {
        phase : 11
        part : [14, 18]
        tex { path:"Pyramid/Pyramid_00111" }
        offset : [-5, -40]
      }

      {
        phase : 12
        part : [16, 18]
        tex { path:"Pyramid/Pyramid_00112" }
        offset : [-5, -45]
      }

      {
        phase : 13
        part : [18, 14]
        tex { path:"Pyramid/Pyramid_00113" }
        offset : [10, -100]
      }

      {
        phase : 14
        part : [18, 12]
        tex { path:"Pyramid/Pyramid_00114" }
        offset : [0, -100]
      }

      {
        phase : 15
        part : [18, 10]
        tex { path:"Pyramid/Pyramid_00115" }
        offset : [-5, -100]
      }

      {
        phase : 16
        part : [18, 8]
        tex { path:"Pyramid/Pyramid_00113" }
        offset : [0, -170]
      }

      {
        phase : 17
        part : [18, 6]
        tex { path:"Pyramid/Pyramid_00114" }
        offset : [0, -170]
      }

      {
        phase : 18
        part : [18, 4]
        tex { path:"Pyramid/Pyramid_00125" }
        offset : [-5, -170]
      }

      {
        phase : 19
        part : [12, 16]
        tex { path:"Pyramid/Pyramid_00110" }
        offset : [15, -200]
      }

      {
        phase : 20
        part : [14, 16]
        tex { path:"Pyramid/Pyramid_00111" }
        offset : [10, -200]
      }

      {
        phase : 20
        part : [16, 16]
        tex { path:"Pyramid/Pyramid_00123" }
        offset : [15, -205]
      }

      {
        phase : 21
        part : [16, 14]
        tex { path:"Pyramid/Pyramid_00115" }
        offset : [20, -200]
      }

      {
        phase : 22
        part : [14, 10]
        tex { path:"Pyramid/Pyramid_00113" }
        offset : [20, -210]
      }

      {
        phase : 23
        part : [14, 8]
        tex { path:"Pyramid/Pyramid_00114" }
        offset : [20, -210]
      }

      // --- Layer 2 (third tier): L2 south y=14 (begin+4, size 12) ? SE [14,14].
      // Offsets ~two tiers up (? -180..-270).
      {
        phase : 24
        part : [14, 6]
        tex { path:"Pyramid/Pyramid_00115" }
        offset : [15, -210]
      }

      {
        phase : 24
        part : [14, 4]
        tex { path:"Pyramid/Pyramid_00127" }
        offset : [10, -220]
      }

      {
        phase : 25
        part : [8, 14]
        tex { path:"Pyramid/Pyramid_00110" }
        offset : [0, -300]
      }

      {
        phase : 26
        part : [10, 14]
        tex { path:"Pyramid/Pyramid_00111" }
        offset : [0, -300]
      }

      {
        phase : 27
        part : [12, 14]
        tex { path:"Pyramid/Pyramid_00112" }
        offset : [0, -300]
      }

      {
        phase : 28
        part : [12, 10]
        tex { path:"Pyramid/Pyramid_00113" }
        offset : [20, -300]
      }

      {
        phase : 29
        part : [12, 8]
        tex { path:"Pyramid/Pyramid_00114" }
        offset : [15, -300]
      }

      {
        phase : 30
        part : [12, 6]
        tex { path:"Pyramid/Pyramid_00127" }
        offset : [15, -300]
      }

      {
        phase : 31
        part : [10, 12]
        tex { path:"Pyramid/Pyramid_00110" }
        offset : [0, -390]
      }

      {
        phase : 32
        part : [12, 12]
        tex { path:"Pyramid/Pyramid_00122" }
        offset : [0, -400]
      }

      {
        phase : 33
        part : [10, 12]
        tex { path:"Pyramid/Pyramid_00114" }
        offset : [0, -400]
      }
    ]

    flags {
      is_monument: true
      non_deletable: true
    }

    corner_type : BUILDING_LARGE_PYRAMID_CORNER
    wall_type : BUILDING_LARGE_PYRAMID_WALL
    cone_type : BUILDING_LARGE_PYRAMID_CONE
    filler_type : BUILDING_PYRAMID_COMPLEX
    part_count : 100
    block_total : 1920
    // OG pyramid_ramp_table (20×20 complex).
    ramps [
      { part: 91, ramp1_height: 1 }
      { part: 92, ramp1_height: 2 }
      { part: 93, ramp1_height: 3 }
      { part: 94, ramp1_height: 4 }
      { part: 95, ramp1_height: 5 }
      { part: 96, ramp1_height: 6 }
      { part: 62, ramp1_height: 7, ramp1_linked_part: 63 }
      { part: 55, ramp1_height: 8 }
      { part: 53, ramp1_height: 9 }
      { part: 51, ramp1_height: 10 }
      { part: 49, ramp1_height: 11 }
      { part: 47, ramp1_height: 12 }
      { part: 20, ramp1_height: 13 }
      { part: 19, ramp1_height: 14 }
      { part: 18, ramp1_height: 15 }
      { part: 17, ramp1_height: 16, ramp1_linked_part: 16 }
      { part: 22, ramp1_height: 17 }
      { part: 24, ramp1_height: 18 }
      { part: 10, ramp1_height: 19, ramp1_linked_part: 12 }
      { part: 13, ramp1_height: 20 }
      { part: 14, ramp1_height: 21 }
      { part: 11, ramp1_height: 22 }
      { part: 9, ramp1_height: 23, ramp1_linked_part: 7 }
      { part: 6, ramp1_height: 24 }
    ]
    pyramide_type : PYRAMID_STYLE_TRUE
  }



  // Grand = same on-land 20x20 until causeway/temples; own TYPE for rating weight.
  building_grand_pyramid_complex {
    animations {
      _pack { pack:PACK_PYRAMID }
      preview { pack:PACK_PYRAMID, id:2, offset:7 }
      base { id:2, offset:7 }
      base_bricks { path:"Pyramid/Pyramid_00103" }
      corner_bricks { path:"Pyramid/Pyramid_00001" }
      wall_bricks { path:"Pyramid/Pyramid_00005" }
      base_polish { path:"Pyramid/Pyramid_00103" }
      corner_polish { path:"Pyramid/Pyramid_00049" }
      wall_polish { path:"Pyramid/Pyramid_00053" }
      base_grounded { path:"Pyramid/pyramid_phase_one_00013" }
      clear_land { id:2, offset:12 }
      image_stick { path:"Pyramid/pyramid_phase_one_00021" }
      empty_land {path:"Pyramid/Pyramid_00109"}
      ramps {path:"Pyramid/Pyramid_00110"}
      ditches_phase_1 { path:"Pyramid/pyramid_phase_one_00022" }
      ditches_phase_2 { path:"Pyramid/pyramid_phase_one_00031" }
      ditches_phase_3 { path:"Pyramid/pyramid_phase_one_00040" }
      ditches_phase_4 { path:"Pyramid/pyramid_phase_one_00049" }
      ground_phase_0 { path:"Pyramid/pyramid_phase_one_00013" }
      basement { path:"Pyramid/pyramid_phase_one_00058" }
      enter { path:"pharaoh_general/plazatiles_00064"}
      complex_walkway { id:8, offset:0 }
      stair_0_2 { path:"Pyramid/Pyramid_00112" }
      stair_0_4 { path:"Pyramid/Pyramid_00110" }
      stair_0_4_corner { path:"Pyramid/Pyramid_00122" }
      stair_0_5 { path:"Pyramid/Pyramid_00114" }
      stair_0_6 { path:"Pyramid/Pyramid_00115" }
    }
    build_menu_text : "Grand Pyramid Complex"
    building_size : 2
    info_title_id [198, 16]
    fire_proof :  true
    damage_proof : true
    meta { text_id:178, help_link:"message_true_pyramid" }
    init_tiles [20, 20]

    enter_offset : [2, 20]

    // Medium-style L-ramp: short approach on south from enter, SE corner, then
    // climb the east face (decreasing y) up to the tier-1 ledge. Sprites 00114+
    // are the ascending ramp pieces; offset.y rises ~+28 ? -110 (? one tier).
    stairs [
      {
        phase : 7
        part : [4, 18]
        tex { path:"Pyramid/Pyramid_00110" }
        offset : [-20, 20]
      }

      {
        phase : 8
        part : [6, 18]
        tex { path:"Pyramid/Pyramid_00111" }
        offset : [-25, 20]
      }

      {
        phase : 9
        part : [8, 18]
        tex { path:"Pyramid/Pyramid_00112" }
        offset : [-20, 20]
      }

      {
        phase : 10
        part : [12, 18]
        tex { path:"Pyramid/Pyramid_00110" }
        offset : [0, -40]
      }

      {
        phase : 11
        part : [14, 18]
        tex { path:"Pyramid/Pyramid_00111" }
        offset : [-5, -40]
      }

      {
        phase : 12
        part : [16, 18]
        tex { path:"Pyramid/Pyramid_00112" }
        offset : [-5, -45]
      }

      {
        phase : 13
        part : [18, 14]
        tex { path:"Pyramid/Pyramid_00113" }
        offset : [10, -100]
      }

      {
        phase : 14
        part : [18, 12]
        tex { path:"Pyramid/Pyramid_00114" }
        offset : [0, -100]
      }

      {
        phase : 15
        part : [18, 10]
        tex { path:"Pyramid/Pyramid_00115" }
        offset : [-5, -100]
      }

      {
        phase : 16
        part : [18, 8]
        tex { path:"Pyramid/Pyramid_00113" }
        offset : [0, -170]
      }

      {
        phase : 17
        part : [18, 6]
        tex { path:"Pyramid/Pyramid_00114" }
        offset : [0, -170]
      }

      {
        phase : 18
        part : [18, 4]
        tex { path:"Pyramid/Pyramid_00125" }
        offset : [-5, -170]
      }

      {
        phase : 19
        part : [12, 16]
        tex { path:"Pyramid/Pyramid_00110" }
        offset : [15, -200]
      }

      {
        phase : 20
        part : [14, 16]
        tex { path:"Pyramid/Pyramid_00111" }
        offset : [10, -200]
      }

      {
        phase : 20
        part : [16, 16]
        tex { path:"Pyramid/Pyramid_00123" }
        offset : [15, -205]
      }

      {
        phase : 21
        part : [16, 14]
        tex { path:"Pyramid/Pyramid_00115" }
        offset : [20, -200]
      }

      {
        phase : 22
        part : [14, 10]
        tex { path:"Pyramid/Pyramid_00113" }
        offset : [20, -210]
      }

      {
        phase : 23
        part : [14, 8]
        tex { path:"Pyramid/Pyramid_00114" }
        offset : [20, -210]
      }

      // --- Layer 2 (third tier): L2 south y=14 (begin+4, size 12) ? SE [14,14].
      // Offsets ~two tiers up (? -180..-270).
      {
        phase : 24
        part : [14, 6]
        tex { path:"Pyramid/Pyramid_00115" }
        offset : [15, -210]
      }

      {
        phase : 24
        part : [14, 4]
        tex { path:"Pyramid/Pyramid_00127" }
        offset : [10, -220]
      }

      {
        phase : 25
        part : [8, 14]
        tex { path:"Pyramid/Pyramid_00110" }
        offset : [0, -300]
      }

      {
        phase : 26
        part : [10, 14]
        tex { path:"Pyramid/Pyramid_00111" }
        offset : [0, -300]
      }

      {
        phase : 27
        part : [12, 14]
        tex { path:"Pyramid/Pyramid_00112" }
        offset : [0, -300]
      }

      {
        phase : 28
        part : [12, 10]
        tex { path:"Pyramid/Pyramid_00113" }
        offset : [20, -300]
      }

      {
        phase : 29
        part : [12, 8]
        tex { path:"Pyramid/Pyramid_00114" }
        offset : [15, -300]
      }

      {
        phase : 30
        part : [12, 6]
        tex { path:"Pyramid/Pyramid_00127" }
        offset : [15, -300]
      }

      {
        phase : 31
        part : [10, 12]
        tex { path:"Pyramid/Pyramid_00110" }
        offset : [0, -390]
      }

      {
        phase : 32
        part : [12, 12]
        tex { path:"Pyramid/Pyramid_00122" }
        offset : [0, -400]
      }

      {
        phase : 33
        part : [10, 12]
        tex { path:"Pyramid/Pyramid_00114" }
        offset : [0, -400]
      }
    ]

    flags {
      is_monument: true
      non_deletable: true
    }

    corner_type : BUILDING_LARGE_PYRAMID_CORNER
    wall_type : BUILDING_LARGE_PYRAMID_WALL
    cone_type : BUILDING_LARGE_PYRAMID_CONE
    filler_type : BUILDING_GRAND_PYRAMID_COMPLEX
    part_count : 100
    block_total : 1920
    // OG size-4 schedule needs 24×24; remake grand is still 20×20 → complex table.
    ramps [
      { part: 91, ramp1_height: 1 }
      { part: 92, ramp1_height: 2 }
      { part: 93, ramp1_height: 3 }
      { part: 94, ramp1_height: 4 }
      { part: 95, ramp1_height: 5 }
      { part: 96, ramp1_height: 6 }
      { part: 62, ramp1_height: 7, ramp1_linked_part: 63 }
      { part: 55, ramp1_height: 8 }
      { part: 53, ramp1_height: 9 }
      { part: 51, ramp1_height: 10 }
      { part: 49, ramp1_height: 11 }
      { part: 47, ramp1_height: 12 }
      { part: 20, ramp1_height: 13 }
      { part: 19, ramp1_height: 14 }
      { part: 18, ramp1_height: 15 }
      { part: 17, ramp1_height: 16, ramp1_linked_part: 16 }
      { part: 22, ramp1_height: 17 }
      { part: 24, ramp1_height: 18 }
      { part: 10, ramp1_height: 19, ramp1_linked_part: 12 }
      { part: 13, ramp1_height: 20 }
      { part: 14, ramp1_height: 21 }
      { part: 11, ramp1_height: 22 }
      { part: 9, ramp1_height: 23, ramp1_linked_part: 7 }
      { part: 6, ramp1_height: 24 }
    ]
    pyramide_type : PYRAMID_STYLE_TRUE
  }



