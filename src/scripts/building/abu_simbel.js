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
      scaffold_a { pack:PACK_ABUSIMBEL, id:15 }
      scaffold_b { pack:PACK_ABUSIMBEL, id:16 }
      preview { pack:PACK_ABUSIMBEL, id:2 }
    }
    building_size : 3
    // OG part kinds; the row index is the OG kind number. A kind is 3x3 tiles, a statue block 6x6; every kind but
    // the entrance stands on monument rock. A view is the camera rotation 0..3: the cliff kinds take image
    // family + "_" + (view + rotate) % 4, the others name the image per view, with an offset into it, and with
    // two_per_art_stage step two images per art stage the record has reached.
    part_kinds [
        { kind: 0, name: "cliff_back", hint: "cliff behind the facade", size: 3, on_rock: true, family: "facade_view", rotate: 0 }
        { kind: 1, name: "cliff_north", hint: "north cliff side", size: 3, on_rock: true, family: "facade_view", rotate: 1 }
        { kind: 2, name: "cliff_south", hint: "south cliff side", size: 3, on_rock: true, family: "facade_view", rotate: 3 }
        { kind: 3, name: "cliff_north_corner", hint: "north back corner", size: 3, on_rock: true, family: "statue_view", rotate: 0 }
        { kind: 4, name: "cliff_south_corner", hint: "south back corner", size: 3, on_rock: true, family: "statue_view", rotate: 3 }
        { kind: 5, name: "cliff_north_end", hint: "north front end", size: 3, on_rock: true, family: "statue_view", rotate: 1 }
        { kind: 6, name: "cliff_south_end", hint: "south front end", size: 3, on_rock: true, family: "statue_view", rotate: 2 }
        { kind: 7, name: "facade_inner", hint: "facade between the statues", size: 3, on_rock: true, views: [
            { image: "part7_front", two_per_art_stage: true },
            { image: "part7_side" },
            { image: "part7_side", offset: 1 },
            { image: "part7_front", offset: 1, two_per_art_stage: true } ] }
        { kind: 8, name: "facade_door", hint: "facade with the door", size: 3, on_rock: true, views: [
            { image: "part8", two_per_art_stage: true },
            { image: "part8", offset: 15 },
            { image: "part8", offset: 14 },
            { image: "part8", offset: 1, two_per_art_stage: true } ] }
        { kind: 9, name: "entrance", hint: "entrance on open ground", size: 3, on_rock: false, views: [
            { image: "part9", two_per_art_stage: true },
            { image: "part9", offset: 1, two_per_art_stage: true },
            { image: "part9", two_per_art_stage: true },
            { image: "part9", offset: 1, two_per_art_stage: true } ] }
        { kind: 10, name: "statue_north", hint: "north statue block", size: 6, on_rock: true, views: [
            { image: "part10_front", two_per_art_stage: true },
            { image: "part10_side" },
            { image: "part10_side", offset: 1 },
            { image: "part10_front", offset: 1, two_per_art_stage: true } ] }
        { kind: 11, name: "statue_south", hint: "south statue block", size: 6, on_rock: true, views: [
            { image: "part10_front", two_per_art_stage: true },
            { image: "part10_side" },
            { image: "part10_side", offset: 1 },
            { image: "part10_front", offset: 1, two_per_art_stage: true } ] }
    ]
    // OG abu_simbel_parts: offset from the clicked tile and the part kind. Part 0 is the main record.
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
    // OG built parts (abu_simbel_data.c): 4 tiers of 3, screen offset from the main record in camera views 0 and 3;
    // the image steps by one in view 3.
    scaffolds [
        { scaffold: 1, name: "tier1_left", image: "scaffold_a", view0: [243, -99], view3: [-411, -247] }
        { scaffold: 2, name: "tier1_middle", image: "scaffold_a", view0: [401, -178], view3: [-253, -171] }
        { scaffold: 3, name: "tier1_right", image: "scaffold_a", view0: [540, -244], view3: [-114, -101] }
        { scaffold: 4, name: "tier2_left", image: "scaffold_a", view0: [243, -159], view3: [-411, -307] }
        { scaffold: 5, name: "tier2_middle", image: "scaffold_a", view0: [401, -238], view3: [-253, -231] }
        { scaffold: 6, name: "tier2_right", image: "scaffold_a", view0: [540, -304], view3: [-114, -161] }
        { scaffold: 7, name: "tier3_left", image: "scaffold_b", view0: [228, -269], view3: [-396, -417] }
        { scaffold: 8, name: "tier3_middle", image: "scaffold_b", view0: [386, -348], view3: [-238, -341] }
        { scaffold: 9, name: "tier3_right", image: "scaffold_b", view0: [525, -414], view3: [-99, -271] }
        { scaffold: 10, name: "tier4_left", image: "scaffold_b", view0: [208, -384], view3: [-376, -532] }
        { scaffold: 11, name: "tier4_middle", image: "scaffold_b", view0: [366, -463], view3: [-218, -456] }
        { scaffold: 12, name: "tier4_right", image: "scaffold_b", view0: [505, -529], view3: [-79, -386] }
    ]
    // OG work spots, one per stage. A scaffold stage is carpenter work that raises the scaffold the first time it
    // comes up and lowers it the second; an art stage is stonemason work that moves that part's art one stage on.
    stages [
        { stage: 0, hint: "raise the tier 1 left scaffold", scaffold: "tier1_left", work: 200 }
        { stage: 1, hint: "raise the tier 2 left scaffold", scaffold: "tier2_left", work: 200 }
        { stage: 2, hint: "raise the tier 3 left scaffold", scaffold: "tier3_left", work: 250 }
        { stage: 3, hint: "raise the tier 4 left scaffold", scaffold: "tier4_left", work: 300 }
        { stage: 4, hint: "raise the tier 1 middle scaffold", scaffold: "tier1_middle", work: 170 }
        { stage: 5, hint: "raise the tier 2 middle scaffold", scaffold: "tier2_middle", work: 200 }
        { stage: 6, hint: "raise the tier 3 middle scaffold", scaffold: "tier3_middle", work: 250 }
        { stage: 7, hint: "raise the tier 4 middle scaffold", scaffold: "tier4_middle", work: 300 }
        { stage: 8, hint: "raise the tier 1 right scaffold", scaffold: "tier1_right", work: 300 }
        { stage: 9, hint: "raise the tier 2 right scaffold", scaffold: "tier2_right", work: 300 }
        { stage: 10, hint: "raise the tier 3 right scaffold", scaffold: "tier3_right", work: 350 }
        { stage: 11, hint: "raise the tier 4 right scaffold", scaffold: "tier4_right", work: 400 }
        { stage: 12, hint: "north statue, carving 1", art: "north_statue", work: 1550 }
        { stage: 13, hint: "door facade, carving 1", art: "door_facade", work: 1000 }
        { stage: 14, hint: "inner facade, carving 1", art: "inner_facade", work: 950 }
        { stage: 15, hint: "south statue, carving 1", art: "south_statue", work: 1050 }
        { stage: 16, hint: "lower the tier 4 left scaffold", scaffold: "tier4_left", work: 500 }
        { stage: 17, hint: "north statue, carving 2", art: "north_statue", work: 1050 }
        { stage: 18, hint: "lower the tier 4 middle scaffold", scaffold: "tier4_middle", work: 500 }
        { stage: 19, hint: "door facade, carving 2", art: "door_facade", work: 1200 }
        { stage: 20, hint: "lower the tier 3 middle scaffold", scaffold: "tier3_middle", work: 400 }
        { stage: 21, hint: "inner facade, carving 2", art: "inner_facade", work: 1100 }
        { stage: 22, hint: "lower the tier 4 right scaffold", scaffold: "tier4_right", work: 500 }
        { stage: 23, hint: "south statue, carving 2", art: "south_statue", work: 1000 }
        { stage: 24, hint: "lower the tier 3 left scaffold", scaffold: "tier3_left", work: 400 }
        { stage: 25, hint: "north statue, carving 3", art: "north_statue", work: 1000 }
        { stage: 26, hint: "door facade, carving 3", art: "door_facade", work: 900 }
        { stage: 27, hint: "lower the tier 3 right scaffold", scaffold: "tier3_right", work: 300 }
        { stage: 28, hint: "south statue, carving 3", art: "south_statue", work: 1000 }
        { stage: 29, hint: "north statue, carving 4", art: "north_statue", work: 1200 }
        { stage: 30, hint: "inner facade, carving 3", art: "inner_facade", work: 900 }
        { stage: 31, hint: "south statue, carving 4", art: "south_statue", work: 400 }
        { stage: 32, hint: "lower the tier 2 left scaffold", scaffold: "tier2_left", work: 300 }
        { stage: 33, hint: "north statue, carving 5", art: "north_statue", work: 500 }
        { stage: 34, hint: "lower the tier 2 middle scaffold", scaffold: "tier2_middle", work: 300 }
        { stage: 35, hint: "door facade, carving 4", art: "door_facade", work: 800 }
        { stage: 36, hint: "lower the tier 2 right scaffold", scaffold: "tier2_right", work: 300 }
        { stage: 37, hint: "south statue, carving 5", art: "south_statue", work: 900 }
        { stage: 38, hint: "lower the tier 1 left scaffold", scaffold: "tier1_left", work: 300 }
        { stage: 39, hint: "north statue, carving 6", art: "north_statue", work: 900 }
        { stage: 40, hint: "lower the tier 1 middle scaffold", scaffold: "tier1_middle", work: 200 }
        { stage: 41, hint: "inner facade, carving 4", art: "inner_facade", work: 500 }
        { stage: 42, hint: "door facade, carving 5", art: "door_facade", work: 500 }
        { stage: 43, hint: "entrance, carving 1", art: "entrance", work: 400 }
        { stage: 44, hint: "inner facade, carving 5", art: "inner_facade", work: 350 }
        { stage: 45, hint: "lower the tier 1 right scaffold", scaffold: "tier1_right", work: 200 }
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
