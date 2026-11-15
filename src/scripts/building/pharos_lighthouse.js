log_info("akhenaten: building pharos_lighthouse started")

building_pharos_lighthouse {
    animations {
      s1 { pack:PACK_LTHOUSE_1, id:1 }
      s2 { pack:PACK_LTHOUSE_2, id:1 }
      s3 { pack:PACK_LTHOUSE_3, id:1 }
      s4 { pack:PACK_LTHOUSE_4, id:1 }
      s5 { pack:PACK_LTHOUSE_5, id:1 }
      s6 { pack:PACK_LTHOUSE_6, id:1 }
      s7 { pack:PACK_LTHOUSE_7, id:1 }
      s8 { pack:PACK_LTHOUSE_8, id:1 }
      s9 { pack:PACK_LTHOUSE_9, id:1 }
      s10 { pack:PACK_LTHOUSE_10, id:1 }
      preview { pack:PACK_LTHOUSE_1, id:1 }
    }
    building_size : 6
    stages [
        { stage: 0, hint: "laying the foundation", stonemason: 400, text: 133 }
        { stage: 1, hint: "foundation and parquet floor", stonemason: 400, text: 134 }
        { stage: 2, hint: "first tier", stonemason: 410, carpenter: 300, text: 135 }
        { stage: 3, hint: "first tier", stonemason: 600, carpenter: 350, text: 135 }
        { stage: 4, hint: "second octagonal tier", stonemason: 355, carpenter: 600, text: 136 }
        { stage: 5, hint: "cupola", stonemason: 500, carpenter: 500, text: 137 }
        { stage: 6, hint: "cupola", stonemason: 500, carpenter: 500, text: 137 }
        { stage: 7, hint: "removing the scaffolding", stonemason: 500, carpenter: 500, text: 138 }
        { stage: 8, hint: "last scaffolding, finishing", stonemason: 400, text: 139 }
    ]
    fire_proof : true
    damage_proof : true
    info_title_id [198, 28]
    meta { text_id: 178, help_link:"message_building_pharos_lighthouse" }
    info_sound : "Wavs/rock3.wav"
    cost [ 0, 0, 0, 0, 0 ]
    guild_worker_terrain: TERRAIN_USAGE_ANY
    flags {
      no_map_edge_margin: true
        is_monument: true
        non_deletable: true
    }
}
