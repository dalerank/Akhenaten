log_info("akhenaten: building mastaba started")

building_small_mastaba {
    animations {
      _pack { pack:PACK_MASTABA }
      preview { id:2, offset:7 }
      base { id:2, offset:7 }
      base_bricks { id:1, offset:0 }
      empty_land { path:"mastaba/mastaba_00109" }
      enter { id:114}
    }
    building_size : 2
    info_title_id[198, 18]
    fire_proof :  true
    damage_proof : true
    meta { help_id:4, text_id:120 }
    init_tiles [10, 4]
    
    config_north [
        { type: BUILDING_SMALL_MASTABA,      offset [-1, -1], base:true }, { type: BUILDING_SMALL_MASTABA,      offset [2, 0]},  
        { type: BUILDING_SMALL_MASTABA_WALL, offset [0, 2] },              { type: BUILDING_SMALL_MASTABA_WALL, offset[2, 2]},
        { type: BUILDING_SMALL_MASTABA_ENTRANCE, offset[2, 4] },           { type: BUILDING_SMALL_MASTABA_WALL, offset[0, 4] },
        { type: BUILDING_SMALL_MASTABA_WALL, offset [0, 6] },              { type: BUILDING_SMALL_MASTABA_WALL, offset[2, 6] },
        { type: BUILDING_SMALL_MASTABA_SIDE, offset [0, 8] },              { type: BUILDING_SMALL_MASTABA_SIDE, offset[2, 8] }
    ]
  }
  
  building_small_mastaba_part_side = building_small_mastaba
  building_small_mastaba_part_wall = building_small_mastaba
  building_small_mastaba_part_entrance = building_small_mastaba