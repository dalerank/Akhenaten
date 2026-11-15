log_info("akhenaten: building abu_simbel started")

building_abu_simbel {
    animations {
      // PACK_ABUSIMBEL group N = OG image group 811 + N.
      part10_side { pack:PACK_ABUSIMBEL, id:1 }
      part10_front { pack:PACK_ABUSIMBEL, id:2 }
      part7_side { pack:PACK_ABUSIMBEL, id:3 }
      part7_front { pack:PACK_ABUSIMBEL, id:4 }
      part8 { pack:PACK_ABUSIMBEL, id:5 }
      part9 { pack:PACK_ABUSIMBEL, id:6 }
      statue_view_1 { pack:PACK_ABUSIMBEL, id:7 }
      statue_view_0 { pack:PACK_ABUSIMBEL, id:8 }
      statue_view_3 { pack:PACK_ABUSIMBEL, id:9 }
      statue_view_2 { pack:PACK_ABUSIMBEL, id:10 }
      facade_view_0 { pack:PACK_ABUSIMBEL, id:11 }
      facade_view_3 { pack:PACK_ABUSIMBEL, id:12 }
      facade_view_1 { pack:PACK_ABUSIMBEL, id:13 }
      facade_view_2 { pack:PACK_ABUSIMBEL, id:14 }
      preview { pack:PACK_ABUSIMBEL, id:2 }
    }
    building_size : 3
    // OG abu_simbel_parts: offset from the clicked tile and what the record is. Part 0 is the main record.
    // Every kind but the entrance must stand on monument rock; statue blocks are 6x6, the rest 3x3.
    parts [
        { id: "main", dx: 1, dy: 7, kind: "cliff_north_end" }
        { id: "south_end", dx: 1, dy: -11, kind: "cliff_south_end" }
        { id: "back_1", dx: -5, dy: 4, kind: "cliff_back" }
        { id: "back_2", dx: -5, dy: 1, kind: "cliff_back" }
        { id: "back_3", dx: -5, dy: -2, kind: "cliff_back" }
        { id: "back_4", dx: -5, dy: -5, kind: "cliff_back" }
        { id: "back_5", dx: -5, dy: -8, kind: "cliff_back" }
        { id: "north_side", dx: -2, dy: 7, kind: "cliff_north" }
        { id: "south_side", dx: -2, dy: -11, kind: "cliff_south" }
        { id: "north_corner", dx: -5, dy: 7, kind: "cliff_north_corner" }
        { id: "south_corner", dx: -5, dy: -11, kind: "cliff_south_corner" }
        { id: "inner_facade", dx: -2, dy: -2, kind: "facade_inner" }
        { id: "door_facade", dx: 1, dy: -2, kind: "facade_door" }
        { id: "entrance", dx: 4, dy: -2, kind: "entrance" }
        { id: "north_statue", dx: -2, dy: 1, kind: "statue_north" }
        { id: "south_statue", dx: -2, dy: -8, kind: "statue_south" }
    ]
    // OG work spots, one per stage. A scaffold stage is carpenter work that raises scaffold N the first time it
    // comes up and lowers it the second (OG keeps the flags but never draws them); an art stage is stonemason
    // work that moves that part's art one stage on.
    stages [
        { stage: 0, hint: "scaffold 1 up", scaffold: 1, work: 200 }
        { stage: 1, hint: "scaffold 4 up", scaffold: 4, work: 200 }
        { stage: 2, hint: "scaffold 7 up", scaffold: 7, work: 250 }
        { stage: 3, hint: "scaffold 10 up", scaffold: 10, work: 300 }
        { stage: 4, hint: "scaffold 2 up", scaffold: 2, work: 170 }
        { stage: 5, hint: "scaffold 5 up", scaffold: 5, work: 200 }
        { stage: 6, hint: "scaffold 8 up", scaffold: 8, work: 250 }
        { stage: 7, hint: "scaffold 11 up", scaffold: 11, work: 300 }
        { stage: 8, hint: "scaffold 3 up", scaffold: 3, work: 300 }
        { stage: 9, hint: "scaffold 6 up", scaffold: 6, work: 300 }
        { stage: 10, hint: "scaffold 9 up", scaffold: 9, work: 350 }
        { stage: 11, hint: "scaffold 12 up", scaffold: 12, work: 400 }
        { stage: 12, hint: "north statue, carving 1", art: "north_statue", work: 1550 }
        { stage: 13, hint: "door facade, carving 1", art: "door_facade", work: 1000 }
        { stage: 14, hint: "inner facade, carving 1", art: "inner_facade", work: 950 }
        { stage: 15, hint: "south statue, carving 1", art: "south_statue", work: 1050 }
        { stage: 16, hint: "scaffold 10 down", scaffold: 10, work: 500 }
        { stage: 17, hint: "north statue, carving 2", art: "north_statue", work: 1050 }
        { stage: 18, hint: "scaffold 11 down", scaffold: 11, work: 500 }
        { stage: 19, hint: "door facade, carving 2", art: "door_facade", work: 1200 }
        { stage: 20, hint: "scaffold 8 down", scaffold: 8, work: 400 }
        { stage: 21, hint: "inner facade, carving 2", art: "inner_facade", work: 1100 }
        { stage: 22, hint: "scaffold 12 down", scaffold: 12, work: 500 }
        { stage: 23, hint: "south statue, carving 2", art: "south_statue", work: 1000 }
        { stage: 24, hint: "scaffold 7 down", scaffold: 7, work: 400 }
        { stage: 25, hint: "north statue, carving 3", art: "north_statue", work: 1000 }
        { stage: 26, hint: "door facade, carving 3", art: "door_facade", work: 900 }
        { stage: 27, hint: "scaffold 9 down", scaffold: 9, work: 300 }
        { stage: 28, hint: "south statue, carving 3", art: "south_statue", work: 1000 }
        { stage: 29, hint: "north statue, carving 4", art: "north_statue", work: 1200 }
        { stage: 30, hint: "inner facade, carving 3", art: "inner_facade", work: 900 }
        { stage: 31, hint: "south statue, carving 4", art: "south_statue", work: 400 }
        { stage: 32, hint: "scaffold 4 down", scaffold: 4, work: 300 }
        { stage: 33, hint: "north statue, carving 5", art: "north_statue", work: 500 }
        { stage: 34, hint: "scaffold 5 down", scaffold: 5, work: 300 }
        { stage: 35, hint: "door facade, carving 4", art: "door_facade", work: 800 }
        { stage: 36, hint: "scaffold 6 down", scaffold: 6, work: 300 }
        { stage: 37, hint: "south statue, carving 5", art: "south_statue", work: 900 }
        { stage: 38, hint: "scaffold 1 down", scaffold: 1, work: 300 }
        { stage: 39, hint: "north statue, carving 6", art: "north_statue", work: 900 }
        { stage: 40, hint: "scaffold 2 down", scaffold: 2, work: 200 }
        { stage: 41, hint: "inner facade, carving 4", art: "inner_facade", work: 500 }
        { stage: 42, hint: "door facade, carving 5", art: "door_facade", work: 500 }
        { stage: 43, hint: "entrance, carving 1", art: "entrance", work: 400 }
        { stage: 44, hint: "inner facade, carving 5", art: "inner_facade", work: 350 }
        { stage: 45, hint: "scaffold 3 down", scaffold: 3, work: 200 }
        { stage: 46, hint: "south statue, carving 6", art: "south_statue", work: 700 }
        { stage: 47, hint: "north statue, carving 7", art: "north_statue", work: 300 }
        { stage: 48, hint: "door facade, carving 6", art: "door_facade", work: 400 }
        { stage: 49, hint: "inner facade, carving 6", art: "inner_facade", work: 300 }
        { stage: 50, hint: "south statue, carving 7", art: "south_statue", work: 500 }
        { stage: 51, hint: "north statue, carving 8", art: "north_statue", work: 400 }
        { stage: 52, hint: "south statue, carving 8", art: "south_statue", work: 300 }
        { stage: 53, hint: "north statue, carving 9", art: "north_statue", work: 300 }
        { stage: 54, hint: "south statue, carving 9", art: "south_statue", work: 600 }
        { stage: 55, hint: "entrance, carving 2", art: "entrance", work: 400 }
    ]
    // OG abu_simbel_part_image, per part kind; a view is the camera rotation 0..3. The cliff kinds take image
    // family + "_" + (view + rotate) % 4; the others name the image per view, with an offset into it, and with
    // two_per_art_stage step two images per art stage the record has reached.
    part_art [
        { kind: "cliff_back", family: "facade_view", rotate: 0 }
        { kind: "cliff_north", family: "facade_view", rotate: 1 }
        { kind: "cliff_south", family: "facade_view", rotate: 3 }
        { kind: "cliff_north_corner", family: "statue_view", rotate: 0 }
        { kind: "cliff_south_corner", family: "statue_view", rotate: 3 }
        { kind: "cliff_north_end", family: "statue_view", rotate: 1 }
        { kind: "cliff_south_end", family: "statue_view", rotate: 2 }
        { kind: "facade_inner", views: [
            { image: "part7_front", two_per_art_stage: true },
            { image: "part7_side" },
            { image: "part7_side", offset: 1 },
            { image: "part7_front", offset: 1, two_per_art_stage: true } ] }
        { kind: "facade_door", views: [
            { image: "part8", two_per_art_stage: true },
            { image: "part8", offset: 15 },
            { image: "part8", offset: 14 },
            { image: "part8", offset: 1, two_per_art_stage: true } ] }
        { kind: "entrance", views: [
            { image: "part9", two_per_art_stage: true },
            { image: "part9", offset: 1, two_per_art_stage: true },
            { image: "part9", two_per_art_stage: true },
            { image: "part9", offset: 1, two_per_art_stage: true } ] }
        { kind: "statue_north", views: [
            { image: "part10_front", two_per_art_stage: true },
            { image: "part10_side" },
            { image: "part10_side", offset: 1 },
            { image: "part10_front", offset: 1, two_per_art_stage: true } ] }
        { kind: "statue_south", views: [
            { image: "part10_front", two_per_art_stage: true },
            { image: "part10_side" },
            { image: "part10_side", offset: 1 },
            { image: "part10_front", offset: 1, two_per_art_stage: true } ] }
    ]
    // OG abu_simbel_get_work_tile, from the main record.
    work_tile [6, -8]
    fire_proof : true
    damage_proof : true
    info_title_id [198, 37]
    meta { text_id: 178, help_link:"message_building_abu_simbel" }
    info_sound : "Wavs/rock3.wav"
    flags {
      no_map_edge_margin: true
        is_monument: true
        non_deletable: true
    }
}
