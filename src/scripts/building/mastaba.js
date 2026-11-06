log_info("akhenaten: building mastaba started")

building_small_mastaba {
    animations {
      _pack { pack:PACK_MASTABA }
      preview { id:2, offset:7 }
      base { id:2, offset:7 }
      base_bricks { id:1, offset:0 }
      base_grounded { path:"mastaba/pyramid_phase_one_00013" }
      clear_land { id:2, offset:12 }
      image_stick { path:"pharaoh_general/plazatiles_00064" }
      empty_land { path:"mastaba/mastaba_00109" }
      enter { id:114 }
    }
    building_size : 2
    part_count : 10
    brick_layers : 6
    entry_part : 8
    // OG mastaba_entry.entry_points size 0
    entry_points [
      {part:8, height:1}, {part:8, height:2}, {part:8, height:3},
      {part:8, height:4}, {part:8, height:5}, {part:8, height:6}
    ]
    // OG part_pair_table for this size
    part_pairs [
      {first:1, second:2}, {first:3, second:4}, {first:0, second:5}, {first:6, second:7}, {first:8, second:9}
    ]

    info_title_id[198, 18]
    fire_proof :  true
    damage_proof : true
    meta { text_id:178, help_link:"message_building_mastaba" }
    info_sound : "Wavs/rock3.wav"
    init_tiles [10, 4]

    // RESOURCE_NONE count = architects (ARCHITECTS). Phase 8 = finished.
    // Brick phases: blocks = OG block quota; BRICKS = blocks*100; workers drive guild spawn.
    // CLAY quotas are remake-only (gameplay_change_mastaba_clay_delivery); OG hauled bricks only.
    construction {
        phases [
            { id: 0, resources: [ { resource: RESOURCE_NONE, count: 1 } ] }
            { id: 1, resources: [ { resource: RESOURCE_NONE, count: 1 } ] }
            { id: 2, blocks: 9,  resources: [ { resource: RESOURCE_NONE, count: 1 }, { resource: RESOURCE_BRICKS, count: 900 } ],  workers: [ { type: FIGURE_BRICKLAYER, count: 1 }, { type: FIGURE_LABORER, count: 1 } ] }
            { id: 3, blocks: 9,  resources: [ { resource: RESOURCE_NONE, count: 1 }, { resource: RESOURCE_CLAY, count: 2000 }, { resource: RESOURCE_BRICKS, count: 900 } ],  workers: [ { type: FIGURE_BRICKLAYER, count: 1 }, { type: FIGURE_LABORER, count: 1 } ] }
            { id: 4, blocks: 9,  resources: [ { resource: RESOURCE_NONE, count: 1 }, { resource: RESOURCE_CLAY, count: 1600 }, { resource: RESOURCE_BRICKS, count: 900 } ],  workers: [ { type: FIGURE_BRICKLAYER, count: 1 }, { type: FIGURE_LABORER, count: 1 } ] }
            { id: 5, blocks: 9,  resources: [ { resource: RESOURCE_NONE, count: 1 }, { resource: RESOURCE_CLAY, count: 1200 }, { resource: RESOURCE_BRICKS, count: 900 } ],  workers: [ { type: FIGURE_BRICKLAYER, count: 1 }, { type: FIGURE_LABORER, count: 1 } ] }
            { id: 6, blocks: 9,  resources: [ { resource: RESOURCE_NONE, count: 1 }, { resource: RESOURCE_CLAY, count: 800 },  { resource: RESOURCE_BRICKS, count: 900 } ],  workers: [ { type: FIGURE_BRICKLAYER, count: 1 }, { type: FIGURE_LABORER, count: 1 } ] }
            { id: 7, blocks: 10, resources: [ { resource: RESOURCE_NONE, count: 1 }, { resource: RESOURCE_CLAY, count: 400 },  { resource: RESOURCE_BRICKS, count: 1000 } ], workers: [ { type: FIGURE_BRICKLAYER, count: 1 }, { type: FIGURE_LABORER, count: 1 } ] }
            { id: 8, resources: [ { resource: RESOURCE_NONE, count: 0 } ] }
        ]
    }

    flags {
        is_monument: true
        non_deletable: true
        allow_rotate: true
    }

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

  // Parts are 2×2 blocks on the init_tiles grid — without building_size they stay
  // size 0, claim no map tiles, and only the main-type pieces render (thin strip).
  building_small_mastaba_part_side { building_size: 2, show_in_debug: false }
  building_small_mastaba_part_wall { building_size: 2, show_in_debug: false }
  building_small_mastaba_part_entrance { building_size: 2, show_in_debug: false }

  building_medium_mastaba  {
    animations {
      _pack { pack:PACK_MASTABA }
      preview { id:2, offset:7 }
      base { id:2, offset:7 }
      base_bricks { id:1, offset:0 }
      base_grounded { path:"mastaba/pyramid_phase_one_00013" }
      clear_land { id:2, offset:12 }
      image_stick { path:"pharaoh_general/plazatiles_00064" }
      empty_land {path:"mastaba/mastaba_00109"}
      enter {id:114}
    }

    building_size : 2
    part_count : 21
    brick_layers : 6
    entry_part : 19
    // OG mastaba_entry.entry_points size 1
    entry_points [
      {part:19, height:1}, {part:19, height:2}, {part:19, height:3},
      {part:19, height:4}, {part:19, height:5}, {part:19, height:6}
    ]
    // OG part_pair_table for this size
    part_pairs [
      {first:11, second:12}, {first:13, second:10}, {first:1, second:2}, {first:3, second:4}, {first:15, second:14}, {first:0, second:5},
      {first:6, second:7}, {first:8, second:9}, {first:17, second:16}, {first:19, second:20}
    ]

    info_title_id [198, 19]
    fire_proof :  true
    damage_proof : true
    meta { text_id:178, help_link:"message_building_mastaba" }
    info_sound : "Wavs/rock3.wav"
    init_tiles [14, 6]

    // Brick phases sum to OG medium block total 121.
    construction {
        phases [
            { id: 0, resources: [ { resource: RESOURCE_NONE, count: 1 } ] }
            { id: 1, resources: [ { resource: RESOURCE_NONE, count: 1 } ] }
            { id: 2, blocks: 20, resources: [ { resource: RESOURCE_NONE, count: 1 }, { resource: RESOURCE_BRICKS, count: 2000 } ], workers: [ { type: FIGURE_BRICKLAYER, count: 1 }, { type: FIGURE_LABORER, count: 1 } ] }
            { id: 3, blocks: 20, resources: [ { resource: RESOURCE_NONE, count: 1 }, { resource: RESOURCE_CLAY, count: 4000 }, { resource: RESOURCE_BRICKS, count: 2000 } ], workers: [ { type: FIGURE_BRICKLAYER, count: 1 }, { type: FIGURE_LABORER, count: 1 } ] }
            { id: 4, blocks: 20, resources: [ { resource: RESOURCE_NONE, count: 1 }, { resource: RESOURCE_CLAY, count: 3200 }, { resource: RESOURCE_BRICKS, count: 2000 } ], workers: [ { type: FIGURE_BRICKLAYER, count: 1 }, { type: FIGURE_LABORER, count: 1 } ] }
            { id: 5, blocks: 20, resources: [ { resource: RESOURCE_NONE, count: 1 }, { resource: RESOURCE_CLAY, count: 2400 }, { resource: RESOURCE_BRICKS, count: 2000 } ], workers: [ { type: FIGURE_BRICKLAYER, count: 1 }, { type: FIGURE_LABORER, count: 1 } ] }
            { id: 6, blocks: 20, resources: [ { resource: RESOURCE_NONE, count: 1 }, { resource: RESOURCE_CLAY, count: 1600 }, { resource: RESOURCE_BRICKS, count: 2000 } ], workers: [ { type: FIGURE_BRICKLAYER, count: 1 }, { type: FIGURE_LABORER, count: 1 } ] }
            { id: 7, blocks: 21, resources: [ { resource: RESOURCE_NONE, count: 1 }, { resource: RESOURCE_CLAY, count: 800 },  { resource: RESOURCE_BRICKS, count: 2100 } ], workers: [ { type: FIGURE_BRICKLAYER, count: 1 }, { type: FIGURE_LABORER, count: 1 } ] }
            { id: 8, resources: [ { resource: RESOURCE_NONE, count: 0 } ] }
        ]
    }

    flags {
        is_monument: true
        non_deletable: true
        allow_rotate: true
    }

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
        { type: BUILDING_MEDIUM_MASTABA_SIDE, offset[2, 0] },      { type: BUILDING_MEDIUM_MASTABA_SIDE, offset[4, 0] },   { type: BUILDING_MEDIUM_MASTABA, offset[-1, -1], base:true }
    ]
  }

  building_medium_mastaba_part_side { building_size: 2, show_in_debug: false }
  building_medium_mastaba_part_wall { building_size: 2, show_in_debug: false }
  building_medium_mastaba_part_entrance { building_size: 2, show_in_debug: false }

  building_large_mastaba {
    animations {
      _pack { pack:PACK_MASTABA }
      preview { id:2, offset:7 }
      base { id:2, offset:7 }
      base_bricks { id:1, offset:0 }
      base_grounded { path:"mastaba/pyramid_phase_one_00013" }
      clear_land { id:2, offset:12 }
      image_stick { path:"pharaoh_general/plazatiles_00064" }
      empty_land { path:"mastaba/mastaba_00109" }
      enter { id:114 }
    }

    building_size : 2
    part_count : 36
    brick_layers : 12
    entry_part : 33
    // OG mastaba_entry.entry_points size 2
    entry_points [
      {part:33, height:1}, {part:33, height:2}, {part:33, height:3}, {part:33, height:4},
      {part:33, height:5}, {part:33, height:6}, {part:18, height:7}, {part:18, height:8},
      {part:18, height:9}, {part:18, height:10}, {part:18, height:11}, {part:18, height:12}
    ]
    // OG part_pair_table for this size
    part_pairs [
      {first:21, second:22}, {first:23, second:24}, {first:25, second:10}, {first:11, second:12}, {first:26, second:13}, {first:1, second:2},
      {first:27, second:14}, {first:3, second:4}, {first:28, second:15}, {first:0, second:5}, {first:29, second:16}, {first:6, second:7},
      {first:30, second:17}, {first:8, second:9}, {first:31, second:18}, {first:19, second:20}, {first:32, second:33}, {first:34, second:35},
    ]

    info_title_id [198, 20]
    fire_proof :  true
    damage_proof : true
    meta { text_id:178, help_link:"message_building_mastaba" }
    info_sound : "Wavs/rock3.wav"
    init_tiles [18, 8]

    // Brick phases sum to OG large block total 373.
    construction {
        phases [
            { id: 0, resources: [ { resource: RESOURCE_NONE, count: 1 } ] }
            { id: 1, resources: [ { resource: RESOURCE_NONE, count: 1 } ] }
            { id: 2, blocks: 62, resources: [ { resource: RESOURCE_NONE, count: 1 }, { resource: RESOURCE_BRICKS, count: 6200 } ], workers: [ { type: FIGURE_BRICKLAYER, count: 1 }, { type: FIGURE_LABORER, count: 1 } ] }
            { id: 3, blocks: 62, resources: [ { resource: RESOURCE_NONE, count: 1 }, { resource: RESOURCE_CLAY, count: 6800 }, { resource: RESOURCE_BRICKS, count: 6200 } ], workers: [ { type: FIGURE_BRICKLAYER, count: 1 }, { type: FIGURE_LABORER, count: 1 } ] }
            { id: 4, blocks: 62, resources: [ { resource: RESOURCE_NONE, count: 1 }, { resource: RESOURCE_CLAY, count: 5600 }, { resource: RESOURCE_BRICKS, count: 6200 } ], workers: [ { type: FIGURE_BRICKLAYER, count: 1 }, { type: FIGURE_LABORER, count: 1 } ] }
            { id: 5, blocks: 62, resources: [ { resource: RESOURCE_NONE, count: 1 }, { resource: RESOURCE_CLAY, count: 4000 }, { resource: RESOURCE_BRICKS, count: 6200 } ], workers: [ { type: FIGURE_BRICKLAYER, count: 1 }, { type: FIGURE_LABORER, count: 1 } ] }
            { id: 6, blocks: 62, resources: [ { resource: RESOURCE_NONE, count: 1 }, { resource: RESOURCE_CLAY, count: 2800 }, { resource: RESOURCE_BRICKS, count: 6200 } ], workers: [ { type: FIGURE_BRICKLAYER, count: 1 }, { type: FIGURE_LABORER, count: 1 } ] }
            { id: 7, blocks: 63, resources: [ { resource: RESOURCE_NONE, count: 1 }, { resource: RESOURCE_CLAY, count: 1400 }, { resource: RESOURCE_BRICKS, count: 6300 } ], workers: [ { type: FIGURE_BRICKLAYER, count: 1 }, { type: FIGURE_LABORER, count: 1 } ] }
            { id: 8, resources: [ { resource: RESOURCE_NONE, count: 0 } ] }
        ]
    }

    flags {
        is_monument: true
        non_deletable: true
        allow_rotate: true
    }

    // 4×9 parts on 8×18 footprint (mirror medium pattern scaled).
    config_north [
        { type: BUILDING_LARGE_MASTABA, offset[-1, -1], base:true }, { type: BUILDING_LARGE_MASTABA, offset[2, 0] }, { type: BUILDING_LARGE_MASTABA, offset[4, 0] }, { type: BUILDING_LARGE_MASTABA_SIDE, offset[6, 0] },
        { type: BUILDING_LARGE_MASTABA_WALL, offset[0, 2] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[2, 2] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[4, 2] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[6, 2] },
        { type: BUILDING_LARGE_MASTABA_WALL, offset[0, 4] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[2, 4] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[4, 4] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[6, 4] },
        { type: BUILDING_LARGE_MASTABA_WALL, offset[0, 6] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[2, 6] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[4, 6] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[6, 6] },
        { type: BUILDING_LARGE_MASTABA_ENTRANCE, offset[6, 8] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[0, 8] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[2, 8] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[4, 8] },
        { type: BUILDING_LARGE_MASTABA_WALL, offset[0, 10] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[2, 10] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[4, 10] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[6, 10] },
        { type: BUILDING_LARGE_MASTABA_SIDE, offset[0, 12] }, { type: BUILDING_LARGE_MASTABA_SIDE, offset[2, 12] }, { type: BUILDING_LARGE_MASTABA_SIDE, offset[4, 12] }, { type: BUILDING_LARGE_MASTABA_SIDE, offset[6, 12] },
        { type: BUILDING_LARGE_MASTABA_SIDE, offset[0, 14] }, { type: BUILDING_LARGE_MASTABA_SIDE, offset[2, 14] }, { type: BUILDING_LARGE_MASTABA_SIDE, offset[4, 14] }, { type: BUILDING_LARGE_MASTABA_SIDE, offset[6, 14] },
        { type: BUILDING_LARGE_MASTABA_SIDE, offset[0, 16] }, { type: BUILDING_LARGE_MASTABA_SIDE, offset[2, 16] }, { type: BUILDING_LARGE_MASTABA_SIDE, offset[4, 16] }, { type: BUILDING_LARGE_MASTABA_SIDE, offset[6, 16] }
    ]

    config_east [
        { type: BUILDING_LARGE_MASTABA, offset[-2, 0] }, { type: BUILDING_LARGE_MASTABA, offset[-4, 0] }, { type: BUILDING_LARGE_MASTABA, offset[-6, 0] }, { type: BUILDING_LARGE_MASTABA, offset[-1, -1], base:true },
        { type: BUILDING_LARGE_MASTABA_WALL, offset[0, 2] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-2, 2] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-4, 2] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-6, 2] },
        { type: BUILDING_LARGE_MASTABA_WALL, offset[0, 4] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-2, 4] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-4, 4] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-6, 4] },
        { type: BUILDING_LARGE_MASTABA_WALL, offset[0, 6] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-2, 6] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-4, 6] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-6, 6] },
        { type: BUILDING_LARGE_MASTABA_ENTRANCE, offset[0, 8] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-2, 8] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-4, 8] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-6, 8] },
        { type: BUILDING_LARGE_MASTABA_WALL, offset[0, 10] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-2, 10] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-4, 10] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-6, 10] },
        { type: BUILDING_LARGE_MASTABA_SIDE, offset[0, 12] }, { type: BUILDING_LARGE_MASTABA_SIDE, offset[-2, 12] }, { type: BUILDING_LARGE_MASTABA_SIDE, offset[-4, 12] }, { type: BUILDING_LARGE_MASTABA_SIDE, offset[-6, 12] },
        { type: BUILDING_LARGE_MASTABA_SIDE, offset[0, 14] }, { type: BUILDING_LARGE_MASTABA_SIDE, offset[-2, 14] }, { type: BUILDING_LARGE_MASTABA_SIDE, offset[-4, 14] }, { type: BUILDING_LARGE_MASTABA_SIDE, offset[-6, 14] },
        { type: BUILDING_LARGE_MASTABA_SIDE, offset[0, 16] }, { type: BUILDING_LARGE_MASTABA_SIDE, offset[-2, 16] }, { type: BUILDING_LARGE_MASTABA_SIDE, offset[-4, 16] }, { type: BUILDING_LARGE_MASTABA_SIDE, offset[-6, 16] }
    ]

    config_south [
        { type: BUILDING_LARGE_MASTABA, offset[-6, -16] }, { type: BUILDING_LARGE_MASTABA_SIDE, offset[-4, -16] }, { type: BUILDING_LARGE_MASTABA_SIDE, offset[-2, -16] }, { type: BUILDING_LARGE_MASTABA_SIDE, offset[0, -16] },
        { type: BUILDING_LARGE_MASTABA_WALL, offset[0, -14] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-2, -14] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-4, -14] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-6, -14] },
        { type: BUILDING_LARGE_MASTABA_WALL, offset[0, -12] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-2, -12] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-4, -12] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-6, -12] },
        { type: BUILDING_LARGE_MASTABA_WALL, offset[0, -10] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-2, -10] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-4, -10] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-6, -10] },
        { type: BUILDING_LARGE_MASTABA_ENTRANCE, offset[0, -8] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-2, -8] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-4, -8] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-6, -8] },
        { type: BUILDING_LARGE_MASTABA_WALL, offset[0, -6] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-2, -6] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-4, -6] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-6, -6] },
        { type: BUILDING_LARGE_MASTABA_WALL, offset[0, -4] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-2, -4] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-4, -4] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-6, -4] },
        { type: BUILDING_LARGE_MASTABA_WALL, offset[0, -2] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-2, -2] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-4, -2] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[-6, -2] },
        { type: BUILDING_LARGE_MASTABA_SIDE, offset[-2, 0] }, { type: BUILDING_LARGE_MASTABA_SIDE, offset[-4, 0] }, { type: BUILDING_LARGE_MASTABA_SIDE, offset[-6, 0] }, { type: BUILDING_LARGE_MASTABA, offset[-1, -1], base:true }
    ]

    config_west [
        { type: BUILDING_LARGE_MASTABA, offset[0, -16] }, { type: BUILDING_LARGE_MASTABA_SIDE, offset[2, -16] }, { type: BUILDING_LARGE_MASTABA_SIDE, offset[4, -16] }, { type: BUILDING_LARGE_MASTABA_SIDE, offset[6, -16] },
        { type: BUILDING_LARGE_MASTABA_WALL, offset[0, -14] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[2, -14] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[4, -14] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[6, -14] },
        { type: BUILDING_LARGE_MASTABA_WALL, offset[0, -12] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[2, -12] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[4, -12] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[6, -12] },
        { type: BUILDING_LARGE_MASTABA_WALL, offset[0, -10] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[2, -10] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[4, -10] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[6, -10] },
        { type: BUILDING_LARGE_MASTABA_ENTRANCE, offset[6, -8] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[4, -8] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[2, -8] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[0, -8] },
        { type: BUILDING_LARGE_MASTABA_WALL, offset[0, -6] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[2, -6] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[4, -6] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[6, -6] },
        { type: BUILDING_LARGE_MASTABA_WALL, offset[0, -4] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[2, -4] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[4, -4] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[6, -4] },
        { type: BUILDING_LARGE_MASTABA_WALL, offset[0, -2] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[2, -2] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[4, -2] }, { type: BUILDING_LARGE_MASTABA_WALL, offset[6, -2] },
        { type: BUILDING_LARGE_MASTABA_SIDE, offset[2, 0] }, { type: BUILDING_LARGE_MASTABA_SIDE, offset[4, 0] }, { type: BUILDING_LARGE_MASTABA_SIDE, offset[6, 0] }, { type: BUILDING_LARGE_MASTABA, offset[-1, -1], base:true }
    ]
  }

  building_large_mastaba_part_side { building_size: 2, show_in_debug: false }
  building_large_mastaba_part_wall { building_size: 2, show_in_debug: false }
  building_large_mastaba_part_entrance { building_size: 2, show_in_debug: false }

function building_mastaba_preview_footprint(init_tiles) {
  var orient = Math.floor(__camera.orientation / 2)
  if (orient == 0 || orient == 2) {
    return { x: init_tiles[1], y: init_tiles[0] }
  }
  return { x: init_tiles[0], y: init_tiles[1] }
}

function building_mastaba_setup_preview_graphics(ev) {
  var cfg = get_building_config_by_id(city_planner.build_type)
  var footprint = building_mastaba_preview_footprint(cfg.init_tiles)
  city_planner.init_tiles(footprint.x, footprint.y)
}

function building_mastaba_preview_image_id(image_id, tile, start, size) {
  if (tile.x == start.x && tile.y == start.y) {
    return image_id
  }
  if (tile.x == start.x && tile.y == start.y + size.y - 1) {
    return image_id - 2
  }
  if (tile.x == start.x + size.x - 1 && tile.y == start.y + size.y - 1) {
    return image_id - 4
  }
  if (tile.x == start.x + size.x - 1 && tile.y == start.y) {
    return image_id - 6
  }
  if (tile.x == start.x) {
    return image_id - 1
  }
  if (tile.x == start.x + size.x - 1) {
    return image_id - 5
  }
  if (tile.y == start.y) {
    return image_id - 7
  }
  if (tile.y == start.y + size.y - 1) {
    return image_id - 3
  }
  return image_id + 5 + ((tile.x + tile.y) % 7)
}

function building_mastaba_ghost_preview(ev) {
  var params = city.get_building_params_by_type(city_planner.build_type)
  var cfg = get_building_config_by_id(city_planner.build_type)
  var size = building_mastaba_preview_footprint(cfg.init_tiles)
  var image_id = params.first_img("base")
  var pixel = ev.pixel
  var end = ev.end

  for (var i = 0; i < size.x; i++) {
    for (var j = 0; j < size.y; j++) {
      var p = { x: pixel.x + 30 * i - 30 * j, y: pixel.y + 15 * i + 15 * j }
      var tile = { x: end.x + i, y: end.y + j }
      city_planner.draw_ghost(p, building_mastaba_preview_image_id(image_id, tile, end, size))
    }
  }
}


[es=(building_small_mastaba, setup_preview_graphics), es=(building_medium_mastaba, setup_preview_graphics), es=(building_large_mastaba, setup_preview_graphics)]
function building_mastaba_setup_preview_graphics_es(ev) {
  building_mastaba_setup_preview_graphics(ev)
}

[es=(building_small_mastaba, ghost_preview), es=(building_medium_mastaba, ghost_preview), es=(building_large_mastaba, ghost_preview)]
function building_mastaba_ghost_preview_es(ev) {
  building_mastaba_ghost_preview(ev)
}

[es=(building_small_mastaba, on_place_checks), es=(building_medium_mastaba, on_place_checks), es=(building_large_mastaba, on_place_checks)]
function building_mastaba_on_place_checks_es(ev) {
  var b = city.get_building(ev.bid)
  var size = b.params.building_size
  var has_groundwater = terrain.exists_in_area(b.tile, size, TERRAIN_GROUNDWATER)
  city.warnings.show_if_not(has_groundwater, "#needs_groundwater")
}

[es=(building_small_mastaba, complete_construction), es=(building_medium_mastaba, complete_construction), es=(building_large_mastaba, complete_construction)]
function building_mastaba_complete_construction(ev) {
  var b = city.get_building(ev.bid)
  __city_message_post_with_popup_delay(MESSAGE_CAT_MONUMENTS, true, "message_history_mastaba", b.type, __map_grid_offset(b.tile), true, "message_building_mastaba")
}