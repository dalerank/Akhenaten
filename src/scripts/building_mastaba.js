log_info("akhenaten: building mastaba started")

building_small_mastaba {
    animations {
      _pack { pack:PACK_MASTABA }
      preview { id:2, offset:7 }
      base { id:2, offset:7 }
      base_bricks { id:1, offset:0 }
      base_grounded { path:"mastaba/pyramid_phase_one_00013" }
      clear_land { id:2, offset:12 }
      image_stick { path:"mastaba/pyramid_phase_one_00021" }
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
        { type: BUILDING_SMALL_MASTABA,      offset[-1, -1], base:true }, { type: BUILDING_SMALL_MASTABA,      offset[2, 0] },  
        { type: BUILDING_SMALL_MASTABA_WALL, offset[0, 2] },              { type: BUILDING_SMALL_MASTABA_WALL, offset[2, 2] },
        { type: BUILDING_SMALL_MASTABA_ENTRANCE, offset[2, 4]},           { type: BUILDING_SMALL_MASTABA_WALL, offset[0, 4] },
        { type: BUILDING_SMALL_MASTABA_WALL, offset[0, 6] },              { type: BUILDING_SMALL_MASTABA_WALL, offset[2, 6] },
        { type: BUILDING_SMALL_MASTABA_SIDE, offset[0, 8] },              { type: BUILDING_SMALL_MASTABA_SIDE, offset[2, 8] }
    ]

    config_east [
        { type: BUILDING_SMALL_MASTABA,      offset[-2, 0]},     { type: BUILDING_SMALL_MASTABA,      offset[-1, -1], base:true },
        { type: BUILDING_SMALL_MASTABA_WALL, offset[0, 2] },     { type: BUILDING_SMALL_MASTABA_WALL, offset[-2, 2] },
        { type: BUILDING_SMALL_MASTABA_ENTRANCE, offset[0, 4] }, { type: BUILDING_SMALL_MASTABA_WALL, offset[-2, 4] },
        { type: BUILDING_SMALL_MASTABA_WALL, offset[0, 6] },     { type: BUILDING_SMALL_MASTABA_WALL, offset[-2, 6] },
        { type: BUILDING_SMALL_MASTABA_SIDE, offset[0, 8] },     { type: BUILDING_SMALL_MASTABA_SIDE, offset[-2, 8] }
    ]

    config_south [
        { type: BUILDING_SMALL_MASTABA,      offset[-2, -8] },    { type: BUILDING_SMALL_MASTABA,      offset[0, -8] },
        { type: BUILDING_SMALL_MASTABA_WALL, offset[0, -2] },     { type: BUILDING_SMALL_MASTABA_WALL, offset[-2, -2] },
        { type: BUILDING_SMALL_MASTABA_ENTRANCE, offset[0, -4] }, { type: BUILDING_SMALL_MASTABA_WALL, offset[-2, -4] },
        { type: BUILDING_SMALL_MASTABA_WALL, offset[0, -6] },     { type: BUILDING_SMALL_MASTABA_WALL, offset[-2, -6] },
        { type: BUILDING_SMALL_MASTABA_SIDE, offset[-2, 0] },     { type: BUILDING_SMALL_MASTABA,      offset[-1, -1], base:true }
    ]

    config_west [
        { type: BUILDING_SMALL_MASTABA,      offset[0, -8] },     { type: BUILDING_SMALL_MASTABA,      offset[2, -8] },
        { type: BUILDING_SMALL_MASTABA_WALL, offset[0, -6] },     { type: BUILDING_SMALL_MASTABA_WALL, offset[2, -6] },
        { type: BUILDING_SMALL_MASTABA_ENTRANCE, offset[2, -4] }, { type: BUILDING_SMALL_MASTABA_WALL, offset[0, -4] },
        { type: BUILDING_SMALL_MASTABA_WALL, offset[0, -2] },     { type: BUILDING_SMALL_MASTABA_WALL, offset[2, -2] },
        { type: BUILDING_SMALL_MASTABA_SIDE, offset[2, 0] },      { type: BUILDING_SMALL_MASTABA, offset[-1, -1], base:true }
    ]
  }
  
  building_small_mastaba_part_side = building_small_mastaba
  building_small_mastaba_part_wall = building_small_mastaba
  building_small_mastaba_part_entrance = building_small_mastaba

  building_medium_mastaba  {
    animations {    
      _pack { pack:PACK_MASTABA }
      preview { id:2, offset:7 }
      base { id:2, offset:7 }
      base_bricks { id:1, offset:0 }
      base_grounded { path:"mastaba/pyramid_phase_one_00013" }
      clear_land { id:2, offset:12 }
      image_stick { path:"mastaba/pyramid_phase_one_00021" }
      empty_land {path:"mastaba/mastaba_00109"}
      enter {id:114}
    }

    building_size : 2
    info_title_id [198, 19]
    fire_proof :  true
    damage_proof : true
    meta { help_id:4, text_id:120 }
    init_tiles [14, 6]

    config_north [
        { type: BUILDING_MEDIUM_MASTABA, offset[-1, -1], base:true }, { type: BUILDING_MEDIUM_MASTABA,      offset[2, 0] },  { type: BUILDING_MEDIUM_MASTABA_SIDE, offset[4, 0] },
        { type: BUILDING_MEDIUM_MASTABA_WALL, offset[0, 2] },         { type: BUILDING_MEDIUM_MASTABA_WALL, offset[2, 2] },  { type: BUILDING_MEDIUM_MASTABA_WALL, offset[4, 2] },
        { type: BUILDING_MEDIUM_MASTABA_WALL, offset[0, 4] },         { type: BUILDING_MEDIUM_MASTABA_WALL, offset[2, 4] },  { type: BUILDING_MEDIUM_MASTABA_WALL, offset[4, 4] },
        { type: BUILDING_MEDIUM_MASTABA_ENTRANCE, offset[4, 6] },     { type: BUILDING_MEDIUM_MASTABA_WALL, offset[0, 6] },  { type: BUILDING_MEDIUM_MASTABA_WALL, offset[2, 6] },
        { type: BUILDING_MEDIUM_MASTABA_WALL, offset[0, 8] },         { type: BUILDING_MEDIUM_MASTABA_WALL, offset[2, 8] },  { type: BUILDING_MEDIUM_MASTABA_WALL, offset[4, 8] },
        { type: BUILDING_MEDIUM_MASTABA_SIDE, offset[0, 10] },        { type: BUILDING_MEDIUM_MASTABA_SIDE, offset[2, 10] }, { type: BUILDING_MEDIUM_MASTABA_SIDE, offset[4, 10] },
        { type: BUILDING_MEDIUM_MASTABA_SIDE, offset[0, 12] },        { type: BUILDING_MEDIUM_MASTABA_SIDE, offset[2, 12] }, { type: BUILDING_MEDIUM_MASTABA_SIDE, offset[4, 12] }
    ]

    config_east [
        { type: BUILDING_MEDIUM_MASTABA,      offset[-2, 0]},     { type: BUILDING_MEDIUM_MASTABA,      offset[-4, 0] },  { type: BUILDING_MEDIUM_MASTABA,      offset[-1, -1], base:true }
        { type: BUILDING_MEDIUM_MASTABA_WALL, offset[0, 2] },     { type: BUILDING_MEDIUM_MASTABA_WALL, offset[-2, 2] },  { type: BUILDING_MEDIUM_MASTABA_WALL, offset[-4, 2] },
        { type: BUILDING_MEDIUM_MASTABA_WALL, offset[0, 4] },     { type: BUILDING_MEDIUM_MASTABA_WALL, offset[-2, 4] },  { type: BUILDING_MEDIUM_MASTABA_WALL, offset[-4, 4] },
        { type: BUILDING_MEDIUM_MASTABA_ENTRANCE, offset[0, 6] }, { type: BUILDING_MEDIUM_MASTABA_WALL, offset[-2, 6] },  { type: BUILDING_MEDIUM_MASTABA_WALL, offset[-4, 6] },
        { type: BUILDING_MEDIUM_MASTABA_WALL, offset[0, 8] },     { type: BUILDING_MEDIUM_MASTABA_WALL, offset[-2, 8] },  { type: BUILDING_MEDIUM_MASTABA_WALL, offset[-4, 8] },
        { type: BUILDING_MEDIUM_MASTABA_SIDE, offset[0, 10] },    { type: BUILDING_MEDIUM_MASTABA_SIDE, offset[-2, 10] }, { type: BUILDING_MEDIUM_MASTABA_SIDE, offset[-4, 10] },
        { type: BUILDING_MEDIUM_MASTABA_SIDE, offset[0, 12] },    { type: BUILDING_MEDIUM_MASTABA_SIDE, offset[-2, 12] }, { type: BUILDING_MEDIUM_MASTABA_SIDE, offset[-4, 12] }
    ]

    config_south [
        { type: BUILDING_MEDIUM_MASTABA,      offset[-4, -12] },   { type: BUILDING_MEDIUM_MASTABA_SIDE, offset[-2, -12] }, { type: BUILDING_MEDIUM_MASTABA_SIDE, offset[0, -12] },
        { type: BUILDING_MEDIUM_MASTABA_WALL, offset[0, -10] },    { type: BUILDING_MEDIUM_MASTABA_WALL, offset[-2, -10] }, { type: BUILDING_MEDIUM_MASTABA_WALL, offset[-4, -10] },
        { type: BUILDING_MEDIUM_MASTABA_WALL, offset[0, -8] },     { type: BUILDING_MEDIUM_MASTABA_WALL, offset[-2, -8] },  { type: BUILDING_MEDIUM_MASTABA_WALL, offset[-4, -8] },
        { type: BUILDING_MEDIUM_MASTABA_ENTRANCE, offset[0, -6] }, { type: BUILDING_MEDIUM_MASTABA_WALL, offset[-2, -6] },  { type: BUILDING_MEDIUM_MASTABA_WALL, offset[-4, -6] },
        { type: BUILDING_MEDIUM_MASTABA_WALL, offset[0, -4] },     { type: BUILDING_MEDIUM_MASTABA_WALL, offset[-2, -4] },  { type: BUILDING_MEDIUM_MASTABA_WALL, offset[-4, -4] },
        { type: BUILDING_MEDIUM_MASTABA_WALL, offset[0, -2] },     { type: BUILDING_MEDIUM_MASTABA_WALL, offset[-2, -2] },  { type: BUILDING_MEDIUM_MASTABA_WALL, offset[-4, -2] },
        { type: BUILDING_MEDIUM_MASTABA_SIDE, offset[-2, 0] },     { type: BUILDING_MEDIUM_MASTABA_SIDE, offset[-4, 0] },   { type: BUILDING_MEDIUM_MASTABA, offset[-1, -1], base:true }
    ]

    config_west [
        { type: BUILDING_MEDIUM_MASTABA,      offset[0, -12] },    { type: BUILDING_MEDIUM_MASTABA_SIDE, offset[2, -12] },  { type: BUILDING_MEDIUM_MASTABA_SIDE, offset[4, -12] },
        { type: BUILDING_MEDIUM_MASTABA_WALL, offset[0, -10] },    { type: BUILDING_MEDIUM_MASTABA_WALL, offset[2, -10] },  { type: BUILDING_MEDIUM_MASTABA_WALL, offset[4, -10] },
        { type: BUILDING_MEDIUM_MASTABA_WALL, offset[0, -8] },     { type: BUILDING_MEDIUM_MASTABA_WALL, offset[2, -8] },   { type: BUILDING_MEDIUM_MASTABA_WALL, offset[4, -8] },
        { type: BUILDING_MEDIUM_MASTABA_ENTRANCE, offset[4, -6] }, { type: BUILDING_MEDIUM_MASTABA_WALL, offset[2, -6] },   { type: BUILDING_MEDIUM_MASTABA_WALL, offset[0, -6] },
        { type: BUILDING_MEDIUM_MASTABA_WALL, offset[0, -4] },     { type: BUILDING_MEDIUM_MASTABA_WALL, offset[2, -4] },   { type: BUILDING_MEDIUM_MASTABA_WALL, offset[4, -4] },
        { type: BUILDING_MEDIUM_MASTABA_WALL, offset[0, -2] },     { type: BUILDING_MEDIUM_MASTABA_WALL, offset[2, -2] },   { type: BUILDING_MEDIUM_MASTABA_WALL, offset[4, -2] },
        { type: BUILDING_MEDIUM_MASTABA_SIDE, offset[2, 0] },      { type: BUILDING_MEDIUM_MASTABA_SIDE, offset[4, -2] },   { type: BUILDING_MEDIUM_MASTABA, offset[-1, -1], base:true }
    ]
  }
  
  building_medium_mastaba_part_side = building_medium_mastaba
  building_medium_mastaba_part_wall = building_medium_mastaba
  building_medium_mastaba_part_entrance = building_medium_mastaba