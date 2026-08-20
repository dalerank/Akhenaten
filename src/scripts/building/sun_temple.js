log_info("akhenaten: building sun_temple started")

building_sun_temple {
    animations {
      // Body packs: id 1/2 = map orientations (I4). Stages sa→sd = construction.
      sa1 { pack:PACK_SUN_TEMPLE_1, id:1 }
      sa2 { pack:PACK_SUN_TEMPLE_1, id:2 }
      sb1 { pack:PACK_SUN_TEMPLE_2, id:1 }
      sb2 { pack:PACK_SUN_TEMPLE_2, id:2 }
      sc1 { pack:PACK_SUN_TEMPLE_3, id:1 }
      sc2 { pack:PACK_SUN_TEMPLE_3, id:2 }
      sd1 { pack:PACK_SUN_TEMPLE_3, id:1 }
      sd2 { pack:PACK_SUN_TEMPLE_3, id:2 }
      preview { pack:PACK_SUN_TEMPLE_1, id:1 }

      hall1 { pack:PACK_SUN_TEMPLE_EXTRA, id:1 }
      hall2 { pack:PACK_SUN_TEMPLE_EXTRA, id:2 }
      wall_a { pack:PACK_SUN_TEMPLE_EXTRA, id:3 }
      wall_b { pack:PACK_SUN_TEMPLE_EXTRA, id:4 }
      wall_c { pack:PACK_SUN_TEMPLE_EXTRA, id:5 }
      wall_d { pack:PACK_SUN_TEMPLE_EXTRA, id:6 }
      wall_e { pack:PACK_SUN_TEMPLE_EXTRA, id:7 }
      wall_f { pack:PACK_SUN_TEMPLE_EXTRA, id:8 }
      path1 { pack:PACK_SUN_TEMPLE_EXTRA, id:9 }
      path2 { pack:PACK_SUN_TEMPLE_EXTRA, id:10 }
      path_b { pack:PACK_SUN_TEMPLE_EXTRA, id:11 }
      path_c { pack:PACK_SUN_TEMPLE_EXTRA, id:12 }
      complex { pack:PACK_SUN_TEMPLE_EXTRA, id:13 }
      stake { pack:PACK_SUN_TEMPLE_EXTRA, id:14 }
      ornament { pack:PACK_SUN_TEMPLE_EXTRA, id:15 }
    }
    building_size : 10

    init_tiles [10, 15]
    path_size [8, 2]
    hall_size [3, 3]

    part_path_offset [[1, 10], [-2, 1], [1, -2], [10, 1]]
    part_hall_offset [[4, 12], [-5, 4], [4, -5], [12, 4]]

    plaza_overlays [
      // V0–V1 stakes (rot0 footprint edges relative to body)
      { key: "stake", offset: [0, 0], min_phase: 0, max_phase: 1 }
      { key: "stake", offset: [9, 0], min_phase: 0, max_phase: 1 }
      { key: "stake", offset: [0, 14], min_phase: 0, max_phase: 1 }
      { key: "stake", offset: [9, 14], min_phase: 0, max_phase: 1 }
      { key: "stake", offset: [4, 0], min_phase: 0, max_phase: 1 }
      { key: "stake", offset: [4, 14], min_phase: 0, max_phase: 1 }
      { key: "stake", offset: [0, 7], min_phase: 0, max_phase: 1 }
      { key: "stake", offset: [9, 7], min_phase: 0, max_phase: 1 }
      // V4 plaza / courtyard walls around body + path corridor
      { key: "wall_a", offset: [-1, 2], min_phase: 4 }
      { key: "wall_b", offset: [10, 2], min_phase: 4 }
      { key: "wall_c", offset: [-1, 7], min_phase: 4 }
      { key: "wall_d", offset: [10, 7], min_phase: 4 }
      { key: "wall_e", offset: [2, -1], min_phase: 4 }
      { key: "wall_f", offset: [7, -1], min_phase: 4 }
      // Extra path strips flanking the main path part
      { key: "path_b", offset: [0, 10], min_phase: 4 }
      { key: "path_c", offset: [8, 10], min_phase: 4 }
      // Larger complex / gatehouse near hall
      { key: "complex", offset: [3, 11], min_phase: 4 }
      // V5 finished ornaments at courtyard corners
      { key: "ornament", offset: [-1, -1], min_phase: 5 }
      { key: "ornament", offset: [10, -1], min_phase: 5 }
      { key: "ornament", offset: [-1, 14], min_phase: 5 }
      { key: "ornament", offset: [10, 14], min_phase: 5 }
    ]
    art_stages : 4
    // Heaven chart: wood = Y for carpenters (no fixed monument load published).
    // Remake keeps a phase-2 delivery gate; provisional 100 until .pak dump.
    timber_loads [ 100 ]
    sandstone_loads [ 160 ]
    build_sandstone : 160
    placement_resources [
        { resource: RESOURCE_SANDSTONE, count: 220 }
    ]
    fire_proof : true
    damage_proof : true
    info_title_id [198, 24]
    meta { text_id: 178, help_link:"message_building_sun_temple" }
    info_sound : "Wavs/rock3.wav"
    cost [ 4000, 5000, 6500, 9000, 13000 ]
    flags {
        is_monument: true
    }
}
