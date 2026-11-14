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
    // OG abu_simbel_parts: offset from the clicked tile, size, kind. Part 0 is the main record.
    // Kinds 0-6 cliff faces, 7/8 the facade beside the door, 9 the entrance on open ground,
    // 10/11 the two statue blocks; every kind but 9 must stand on monument rock.
    parts [
        { dx: 1, dy: 7, size: 3, kind: 5 }
        { dx: 1, dy: -11, size: 3, kind: 6 }
        { dx: -5, dy: 4, size: 3, kind: 0 }
        { dx: -5, dy: 1, size: 3, kind: 0 }
        { dx: -5, dy: -2, size: 3, kind: 0 }
        { dx: -5, dy: -5, size: 3, kind: 0 }
        { dx: -5, dy: -8, size: 3, kind: 0 }
        { dx: -2, dy: 7, size: 3, kind: 1 }
        { dx: -2, dy: -11, size: 3, kind: 2 }
        { dx: -5, dy: 7, size: 3, kind: 3 }
        { dx: -5, dy: -11, size: 3, kind: 4 }
        { dx: -2, dy: -2, size: 3, kind: 7 }
        { dx: 1, dy: -2, size: 3, kind: 8 }
        { dx: 4, dy: -2, size: 3, kind: 9 }
        { dx: -2, dy: 1, size: 6, kind: 10 }
        { dx: -2, dy: -8, size: 6, kind: 11 }
    ]
    // OG work spots (one per stage) with the stage table entry applied when it is done:
    // built_part toggles a scaffold flag (OG never draws them), part/part_stage moves a part's art.
    stages [
        { figure: FIGURE_CARPENTER, work: 200, built_part: 1, raise: true }
        { figure: FIGURE_CARPENTER, work: 200, built_part: 4, raise: true }
        { figure: FIGURE_CARPENTER, work: 250, built_part: 7, raise: true }
        { figure: FIGURE_CARPENTER, work: 300, built_part: 10, raise: true }
        { figure: FIGURE_CARPENTER, work: 170, built_part: 2, raise: true }
        { figure: FIGURE_CARPENTER, work: 200, built_part: 5, raise: true }
        { figure: FIGURE_CARPENTER, work: 250, built_part: 8, raise: true }
        { figure: FIGURE_CARPENTER, work: 300, built_part: 11, raise: true }
        { figure: FIGURE_CARPENTER, work: 300, built_part: 3, raise: true }
        { figure: FIGURE_CARPENTER, work: 300, built_part: 6, raise: true }
        { figure: FIGURE_CARPENTER, work: 350, built_part: 9, raise: true }
        { figure: FIGURE_CARPENTER, work: 400, built_part: 12, raise: true }
        { figure: FIGURE_STONEMASON, work: 1550, part: 14, part_stage: 1 }
        { figure: FIGURE_STONEMASON, work: 1000, part: 12, part_stage: 1 }
        { figure: FIGURE_STONEMASON, work: 950, part: 11, part_stage: 1 }
        { figure: FIGURE_STONEMASON, work: 1050, part: 15, part_stage: 1 }
        { figure: FIGURE_CARPENTER, work: 500, built_part: 10 }
        { figure: FIGURE_STONEMASON, work: 1050, part: 14, part_stage: 2 }
        { figure: FIGURE_CARPENTER, work: 500, built_part: 11 }
        { figure: FIGURE_STONEMASON, work: 1200, part: 12, part_stage: 2 }
        { figure: FIGURE_CARPENTER, work: 400, built_part: 8 }
        { figure: FIGURE_STONEMASON, work: 1100, part: 11, part_stage: 2 }
        { figure: FIGURE_CARPENTER, work: 500, built_part: 12 }
        { figure: FIGURE_STONEMASON, work: 1000, part: 15, part_stage: 2 }
        { figure: FIGURE_CARPENTER, work: 400, built_part: 7 }
        { figure: FIGURE_STONEMASON, work: 1000, part: 14, part_stage: 3 }
        { figure: FIGURE_STONEMASON, work: 900, part: 12, part_stage: 3 }
        { figure: FIGURE_CARPENTER, work: 300, built_part: 9 }
        { figure: FIGURE_STONEMASON, work: 1000, part: 15, part_stage: 3 }
        { figure: FIGURE_STONEMASON, work: 1200, part: 14, part_stage: 4 }
        { figure: FIGURE_STONEMASON, work: 900, part: 11, part_stage: 3 }
        { figure: FIGURE_STONEMASON, work: 400, part: 15, part_stage: 4 }
        { figure: FIGURE_CARPENTER, work: 300, built_part: 4 }
        { figure: FIGURE_STONEMASON, work: 500, part: 14, part_stage: 5 }
        { figure: FIGURE_CARPENTER, work: 300, built_part: 5 }
        { figure: FIGURE_STONEMASON, work: 800, part: 12, part_stage: 4 }
        { figure: FIGURE_CARPENTER, work: 300, built_part: 6 }
        { figure: FIGURE_STONEMASON, work: 900, part: 15, part_stage: 5 }
        { figure: FIGURE_CARPENTER, work: 300, built_part: 1 }
        { figure: FIGURE_STONEMASON, work: 900, part: 14, part_stage: 6 }
        { figure: FIGURE_CARPENTER, work: 200, built_part: 2 }
        { figure: FIGURE_STONEMASON, work: 500, part: 11, part_stage: 4 }
        { figure: FIGURE_STONEMASON, work: 500, part: 12, part_stage: 5 }
        { figure: FIGURE_STONEMASON, work: 400, part: 13, part_stage: 1 }
        { figure: FIGURE_STONEMASON, work: 350, part: 11, part_stage: 5 }
        { figure: FIGURE_CARPENTER, work: 200, built_part: 3 }
        { figure: FIGURE_STONEMASON, work: 700, part: 15, part_stage: 6 }
        { figure: FIGURE_STONEMASON, work: 300, part: 14, part_stage: 7 }
        { figure: FIGURE_STONEMASON, work: 400, part: 12, part_stage: 6 }
        { figure: FIGURE_STONEMASON, work: 300, part: 11, part_stage: 6 }
        { figure: FIGURE_STONEMASON, work: 500, part: 15, part_stage: 7 }
        { figure: FIGURE_STONEMASON, work: 400, part: 14, part_stage: 8 }
        { figure: FIGURE_STONEMASON, work: 300, part: 15, part_stage: 8 }
        { figure: FIGURE_STONEMASON, work: 300, part: 14, part_stage: 9 }
        { figure: FIGURE_STONEMASON, work: 600, part: 15, part_stage: 9 }
        { figure: FIGURE_STONEMASON, work: 400, part: 13, part_stage: 2 }
    ]
    // OG abu_simbel_part_image: per part kind and camera view, the image group, an offset into it and whether
    // it steps two images per art stage of the record (front/back views 0 and 3 vs. the side views 1 and 2).
    part_art [
        { kind: 0, view: 0, image: "facade_view_0" }
        { kind: 0, view: 1, image: "facade_view_1" }
        { kind: 0, view: 2, image: "facade_view_2" }
        { kind: 0, view: 3, image: "facade_view_3" }
        { kind: 1, view: 0, image: "facade_view_1" }
        { kind: 1, view: 1, image: "facade_view_2" }
        { kind: 1, view: 2, image: "facade_view_3" }
        { kind: 1, view: 3, image: "facade_view_0" }
        { kind: 2, view: 0, image: "facade_view_3" }
        { kind: 2, view: 1, image: "facade_view_0" }
        { kind: 2, view: 2, image: "facade_view_1" }
        { kind: 2, view: 3, image: "facade_view_2" }
        { kind: 3, view: 0, image: "statue_view_0" }
        { kind: 3, view: 1, image: "statue_view_1" }
        { kind: 3, view: 2, image: "statue_view_2" }
        { kind: 3, view: 3, image: "statue_view_3" }
        { kind: 4, view: 0, image: "statue_view_3" }
        { kind: 4, view: 1, image: "statue_view_0" }
        { kind: 4, view: 2, image: "statue_view_1" }
        { kind: 4, view: 3, image: "statue_view_2" }
        { kind: 5, view: 0, image: "statue_view_1" }
        { kind: 5, view: 1, image: "statue_view_2" }
        { kind: 5, view: 2, image: "statue_view_3" }
        { kind: 5, view: 3, image: "statue_view_0" }
        { kind: 6, view: 0, image: "statue_view_2" }
        { kind: 6, view: 1, image: "statue_view_3" }
        { kind: 6, view: 2, image: "statue_view_0" }
        { kind: 6, view: 3, image: "statue_view_1" }
        { kind: 7, view: 0, image: "part7_front", staged: true }
        { kind: 7, view: 1, image: "part7_side" }
        { kind: 7, view: 2, image: "part7_side", offset: 1 }
        { kind: 7, view: 3, image: "part7_front", offset: 1, staged: true }
        { kind: 8, view: 0, image: "part8", staged: true }
        { kind: 8, view: 1, image: "part8", offset: 15 }
        { kind: 8, view: 2, image: "part8", offset: 14 }
        { kind: 8, view: 3, image: "part8", offset: 1, staged: true }
        { kind: 9, view: 0, image: "part9", staged: true }
        { kind: 9, view: 1, image: "part9", offset: 1, staged: true }
        { kind: 9, view: 2, image: "part9", staged: true }
        { kind: 9, view: 3, image: "part9", offset: 1, staged: true }
        { kind: 10, view: 0, image: "part10_front", staged: true }
        { kind: 10, view: 1, image: "part10_side" }
        { kind: 10, view: 2, image: "part10_side", offset: 1 }
        { kind: 10, view: 3, image: "part10_front", offset: 1, staged: true }
        { kind: 11, view: 0, image: "part10_front", staged: true }
        { kind: 11, view: 1, image: "part10_side" }
        { kind: 11, view: 2, image: "part10_side", offset: 1 }
        { kind: 11, view: 3, image: "part10_front", offset: 1, staged: true }
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
