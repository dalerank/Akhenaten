log_info("akhenaten: building mausoleum started")

building_mausoleum {
    animations {
      // Keys stay flat (first_img): m{skin}_{stage}{a-d}{view}. View bit → offset 0/1.
      // stages: 1 = building, 2 = low done + carpenter, 3 = full / finished.

      // --- skin 0 / stage 1 ---
      m0_1a1 { pack:PACK_MAUS0_1A, id:1 }
      m0_1a2 { pack:PACK_MAUS0_1A, id:1, offset:1 }
      m0_1b1 { pack:PACK_MAUS0_1B, id:1 }
      m0_1b2 { pack:PACK_MAUS0_1B, id:1, offset:1 }
      m0_1c1 { pack:PACK_MAUS0_1C, id:1 }
      m0_1c2 { pack:PACK_MAUS0_1C, id:1, offset:1 }
      m0_1d1 { pack:PACK_MAUS0_1D, id:1 }
      m0_1d2 { pack:PACK_MAUS0_1D, id:1, offset:1 }
      // --- skin 0 / stage 2 ---
      m0_2a1 { pack:PACK_MAUS0_2A, id:1 }
      m0_2a2 { pack:PACK_MAUS0_2A, id:1, offset:1 }
      m0_2b1 { pack:PACK_MAUS0_2B, id:1 }
      m0_2b2 { pack:PACK_MAUS0_2B, id:1, offset:1 }
      m0_2c1 { pack:PACK_MAUS0_2C, id:1 }
      m0_2c2 { pack:PACK_MAUS0_2C, id:1, offset:1 }
      m0_2d1 { pack:PACK_MAUS0_2D, id:1 }
      m0_2d2 { pack:PACK_MAUS0_2D, id:1, offset:1 }
      // --- skin 0 / stage 3 ---
      m0_3a1 { pack:PACK_MAUS0_3A, id:1 }
      m0_3a2 { pack:PACK_MAUS0_3A, id:1, offset:1 }
      m0_3b1 { pack:PACK_MAUS0_3B, id:1 }
      m0_3b2 { pack:PACK_MAUS0_3B, id:1, offset:1 }
      m0_3c1 { pack:PACK_MAUS0_3C, id:1 }
      m0_3c2 { pack:PACK_MAUS0_3C, id:1, offset:1 }
      m0_3d1 { pack:PACK_MAUS0_3D, id:1 }
      m0_3d2 { pack:PACK_MAUS0_3D, id:1, offset:1 }

      // --- skin 1 / stage 1 ---
      m1_1a1 { pack:PACK_MAUS1_1A, id:1 }
      m1_1a2 { pack:PACK_MAUS1_1A, id:1, offset:1 }
      m1_1b1 { pack:PACK_MAUS1_1B, id:1 }
      m1_1b2 { pack:PACK_MAUS1_1B, id:1, offset:1 }
      m1_1c1 { pack:PACK_MAUS1_1C, id:1 }
      m1_1c2 { pack:PACK_MAUS1_1C, id:1, offset:1 }
      m1_1d1 { pack:PACK_MAUS1_1D, id:1 }
      m1_1d2 { pack:PACK_MAUS1_1D, id:1, offset:1 }
      // --- skin 1 / stage 2 ---
      m1_2a1 { pack:PACK_MAUS1_2A, id:1 }
      m1_2a2 { pack:PACK_MAUS1_2A, id:1, offset:1 }
      m1_2b1 { pack:PACK_MAUS1_2B, id:1 }
      m1_2b2 { pack:PACK_MAUS1_2B, id:1, offset:1 }
      m1_2c1 { pack:PACK_MAUS1_2C, id:1 }
      m1_2c2 { pack:PACK_MAUS1_2C, id:1, offset:1 }
      m1_2d1 { pack:PACK_MAUS1_2D, id:1 }
      m1_2d2 { pack:PACK_MAUS1_2D, id:1, offset:1 }
      // --- skin 1 / stage 3 ---
      m1_3a1 { pack:PACK_MAUS1_3A, id:1 }
      m1_3a2 { pack:PACK_MAUS1_3A, id:1, offset:1 }
      m1_3b1 { pack:PACK_MAUS1_3B, id:1 }
      m1_3b2 { pack:PACK_MAUS1_3B, id:1, offset:1 }
      m1_3c1 { pack:PACK_MAUS1_3C, id:1 }
      m1_3c2 { pack:PACK_MAUS1_3C, id:1, offset:1 }
      m1_3d1 { pack:PACK_MAUS1_3D, id:1 }
      m1_3d2 { pack:PACK_MAUS1_3D, id:1, offset:1 }

      // --- skin 2 / stage 1 ---
      m2_1a1 { pack:PACK_MAUS2_1A, id:1 }
      m2_1a2 { pack:PACK_MAUS2_1A, id:1, offset:1 }
      m2_1b1 { pack:PACK_MAUS2_1B, id:1 }
      m2_1b2 { pack:PACK_MAUS2_1B, id:1, offset:1 }
      m2_1c1 { pack:PACK_MAUS2_1C, id:1 }
      m2_1c2 { pack:PACK_MAUS2_1C, id:1, offset:1 }
      m2_1d1 { pack:PACK_MAUS2_1D, id:1 }
      m2_1d2 { pack:PACK_MAUS2_1D, id:1, offset:1 }
      // --- skin 2 / stage 2 ---
      m2_2a1 { pack:PACK_MAUS2_2A, id:1 }
      m2_2a2 { pack:PACK_MAUS2_2A, id:1, offset:1 }
      m2_2b1 { pack:PACK_MAUS2_2B, id:1 }
      m2_2b2 { pack:PACK_MAUS2_2B, id:1, offset:1 }
      m2_2c1 { pack:PACK_MAUS2_2C, id:1 }
      m2_2c2 { pack:PACK_MAUS2_2C, id:1, offset:1 }
      m2_2d1 { pack:PACK_MAUS2_2D, id:1 }
      m2_2d2 { pack:PACK_MAUS2_2D, id:1, offset:1 }
      // --- skin 2 / stage 3 ---
      m2_3a1 { pack:PACK_MAUS2_3A, id:1 }
      m2_3a2 { pack:PACK_MAUS2_3A, id:1, offset:1 }
      m2_3b1 { pack:PACK_MAUS2_3B, id:1 }
      m2_3b2 { pack:PACK_MAUS2_3B, id:1, offset:1 }
      m2_3c1 { pack:PACK_MAUS2_3C, id:1 }
      m2_3c2 { pack:PACK_MAUS2_3C, id:1, offset:1 }
      m2_3d1 { pack:PACK_MAUS2_3D, id:1 }
      m2_3d2 { pack:PACK_MAUS2_3D, id:1, offset:1 }

      preview { pack:PACK_MAUS0_3A, id:1 }

      // --- fence / plaza (mausoleum*_extra, skin 0; offsets = OG ground 0..15) ---
      g0 { pack:PACK_LIB_MAUSOLEUM_0, id:1 }
      g1 { pack:PACK_LIB_MAUSOLEUM_0, id:1, offset:1 }
      g2 { pack:PACK_LIB_MAUSOLEUM_0, id:1, offset:2 }
      g3 { pack:PACK_LIB_MAUSOLEUM_0, id:1, offset:3 }
      g4 { pack:PACK_LIB_MAUSOLEUM_0, id:1, offset:4 }
      g5 { pack:PACK_LIB_MAUSOLEUM_0, id:1, offset:5 }
      g6 { pack:PACK_LIB_MAUSOLEUM_0, id:1, offset:6 }
      g7 { pack:PACK_LIB_MAUSOLEUM_0, id:1, offset:7 }
      g8 { pack:PACK_LIB_MAUSOLEUM_0, id:1, offset:8 }
      g9 { pack:PACK_LIB_MAUSOLEUM_0, id:1, offset:9 }
      g10 { pack:PACK_LIB_MAUSOLEUM_0, id:1, offset:10 }
      g11 { pack:PACK_LIB_MAUSOLEUM_0, id:1, offset:11 }
      g12 { pack:PACK_LIB_MAUSOLEUM_0, id:1, offset:12 }
      g13 { pack:PACK_LIB_MAUSOLEUM_0, id:1, offset:13 }
      g14 { pack:PACK_LIB_MAUSOLEUM_0, id:1, offset:14 }
      g15 { pack:PACK_LIB_MAUSOLEUM_0, id:1, offset:15 }
      walkway { pack:PACK_PYRAMID, id:8 }
      walkway_alex { pack:PACK_LIB_MAUS_CARRYOVER, id:5 }
      leveled { pack:PACK_TERRAIN, id:10 }
    }
    building_size : 22
    leveled : "leveled"
    unbuilt : "walkway"
    placement_resources [
        { resource: RESOURCE_SANDSTONE, count: 240 }
    ]
    // Glyph → part kind. Unknown map glyphs (e.g. #) are skipped. pair_dy emits the
    // cell below as the next chained part (approach outer/inner for laborer_tick).
    fence_tokens [
      { token: ".", kind: 4 }
      { token: "W", kind: 4, walkway: true }
      { token: "5", kind: 5 }
      { token: "6", kind: 6 }
      { token: "7", kind: 7 }
      { token: "w", kind: 7, walkway: true }
      { token: "8", kind: 8 }
      { token: "9", kind: 9 }
      { token: "a", kind: 10, pair_dy: 1 }
      { token: "A", kind: 11 }
      { token: "b", kind: 12, pair_dy: 1 }
      { token: "B", kind: 13 }
    ]
    // mausoleum_part_descs[116] → blocks[4] + fence_map[8×22] + fence_links.
    //
    // x: 0                   5                   10                  15                  20
    // y0: W . 8 8 5 5 8 8 5 5 8 8 5 5 8 8 5 5 6 7 6 w
    // y1: . . . . 5 5 . . 5 5 . . 5 5 . . 5 5 . a a a
    // y2: . . # # # # # # # # # # # # # # # # . A A A
    // y3: . . # # # # # # # # # # # # # # # # 5 5 5 5
    // y4: . . # # # # # # # # # # # # # # # # 5 5 5 5
    // y5: . . # # # # # # # # # # # # # # # # . b b b
    // y6: . . . . 5 5 . . 5 5 . . 5 5 . . 5 5 . B B B
    // y7: W . 9 9 5 5 9 9 5 5 9 9 5 5 9 9 5 5 6 7 6 w
    //
    blocks [
      { hint: "#0 sandstone block 0", offset: [2, 2], size: 4, kind: 0 }
      { hint: "#1 sandstone block 1", offset: [6, 2], size: 4, kind: 1 }
      { hint: "#2 sandstone block 2", offset: [10, 2], size: 4, kind: 2 }
      { hint: "#3 sandstone block 3", offset: [14, 2], size: 4, kind: 3 }
    ]
    fence_map [
      "W . 8 8 5 5 8 8 5 5 8 8 5 5 8 8 5 5 6 7 6 w"
      ". . . . 5 5 . . 5 5 . . 5 5 . . 5 5 . a a a"
      ". . # # # # # # # # # # # # # # # # . A A A"
      ". . # # # # # # # # # # # # # # # # 5 5 5 5"
      ". . # # # # # # # # # # # # # # # # 5 5 5 5"
      ". . # # # # # # # # # # # # # # # # . b b b"
      ". . . . 5 5 . . 5 5 . . 5 5 . . 5 5 . B B B"
      "W . 9 9 5 5 9 9 5 5 9 9 5 5 9 9 5 5 6 7 6 w"
    ]
    fence_links [
      { offset: [2, 1], block: 0, pair: 0 }
      { offset: [2, 6], block: 0, pair: 2 }
      { offset: [6, 1], block: 1, pair: 0 }
      { offset: [6, 6], block: 1, pair: 2 }
      { offset: [10, 1], block: 2, pair: 0 }
      { offset: [10, 6], block: 2, pair: 2 }
      { offset: [14, 1], block: 3, pair: 0 }
      { offset: [14, 6], block: 3, pair: 2 }
      { offset: [5, 1], block: 0, pair: 1 }
      { offset: [5, 6], block: 0, pair: 3 }
      { offset: [9, 1], block: 1, pair: 1 }
      { offset: [9, 6], block: 1, pair: 3 }
      { offset: [13, 1], block: 2, pair: 1 }
      { offset: [13, 6], block: 2, pair: 3 }
      { offset: [17, 1], block: 3, pair: 1 }
      { offset: [17, 6], block: 3, pair: 3 }
    ]
    // --- END GENERATED ---
    fire_proof : true
    damage_proof : true
    info_title_id [198, 25]
    meta { text_id: 178, help_link:"message_building_mausoleum" }
    info_sound : "Wavs/rock3.wav"
    cost [ 3500, 4500, 6000, 8500, 12000 ]
    guild_worker_terrain: TERRAIN_USAGE_ANY
    flags {
        is_monument: true
        non_deletable: true
    }
}

// M1.4: 3 art skins (MAUSOLEUM_0/1/2). Ctrl+R cycles; titles gr198:25/26/27.
[es=(building_mausoleum, setup_building_variant)]
function building_mausoleum_setup_building_variant(ev) {
    city_planner.custom_building_variant = 0
}

[es=(building_mausoleum, next_building_variant)]
function building_mausoleum_next_building_variant(ev) {
    if (ev.variant < 0) {
        city_planner.custom_building_variant = 0
        return
    }
    city_planner.custom_building_variant = (ev.variant + 1) % 3
}

[es=(building_mausoleum, update_building_variant)]
function building_mausoleum_update_building_variant(ev) {
    var v = city_planner.custom_building_variant | 0
    if (v < 0) {
        v = 0
    }
    city_planner.building_variant = v % 3
}
