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
    spots [
        { stage: 0, figure: FIGURE_STONEMASON, work: 400 }
        { stage: 1, figure: FIGURE_STONEMASON, work: 400 }
        { stage: 2, figure: FIGURE_STONEMASON, work: 410 }
        { stage: 2, figure: FIGURE_CARPENTER, work: 300 }
        { stage: 3, figure: FIGURE_STONEMASON, work: 600 }
        { stage: 3, figure: FIGURE_CARPENTER, work: 350 }
        { stage: 4, figure: FIGURE_STONEMASON, work: 355 }
        { stage: 4, figure: FIGURE_CARPENTER, work: 600 }
        { stage: 5, figure: FIGURE_STONEMASON, work: 500 }
        { stage: 5, figure: FIGURE_CARPENTER, work: 500 }
        { stage: 6, figure: FIGURE_STONEMASON, work: 500 }
        { stage: 6, figure: FIGURE_CARPENTER, work: 500 }
        { stage: 7, figure: FIGURE_STONEMASON, work: 500 }
        { stage: 7, figure: FIGURE_CARPENTER, work: 500 }
        { stage: 8, figure: FIGURE_STONEMASON, work: 400 }
    ]
    stage_texts [133, 134, 135, 135, 136, 137, 137, 138, 139]
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
