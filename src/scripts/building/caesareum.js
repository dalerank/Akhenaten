log_info("akhenaten: building caesareum started")

building_caesareum {
    animations {
      // OG stage N draws pack caesareum(N+1); the 9 images are the parts, picked by camera view.
      s1 { pack:PACK_CAESAREUM_1, id:1 }
      s2 { pack:PACK_CAESAREUM_2, id:1 }
      s3 { pack:PACK_CAESAREUM_3, id:1 }
      s4 { pack:PACK_CAESAREUM_4, id:1 }
      s5 { pack:PACK_CAESAREUM_5, id:1 }
      s6 { pack:PACK_CAESAREUM_6, id:1 }
      s7 { pack:PACK_CAESAREUM_7, id:1 }
      s8 { pack:PACK_CAESAREUM_8, id:1 }
      s9 { pack:PACK_CAESAREUM_9, id:1 }
      s10 { pack:PACK_CAESAREUM_10, id:1 }
      s11 { pack:PACK_CAESAREUM_11, id:1 }
      s12 { pack:PACK_CAESAREUM_12, id:1 }
      s13 { pack:PACK_CAESAREUM_13, id:1 }
      s14 { pack:PACK_CAESAREUM_14, id:1 }
      s15 { pack:PACK_CAESAREUM_15, id:1 }
      s16 { pack:PACK_CAESAREUM_16, id:1 }
      s17 { pack:PACK_CAESAREUM_17, id:1 }
      s18 { pack:PACK_CAESAREUM_18, id:1 }
      s19 { pack:PACK_CAESAREUM_19, id:1 }
      s20 { pack:PACK_CAESAREUM_20, id:1 }
      preview { pack:PACK_CAESAREUM_1, id:1 }
    }
    building_size : 5
    // OG caesareum_work_spots; spots 3k..3k+2 are stored on part k.
    spots [
        { stage: 0, figure: FIGURE_STONEMASON, work: 700 }
        { stage: 1, figure: FIGURE_STONEMASON, work: 700 }
        { stage: 2, figure: FIGURE_CARPENTER, work: 400 }
        { stage: 2, figure: FIGURE_STONEMASON, work: 700 }
        { stage: 3, figure: FIGURE_CARPENTER, work: 400 }
        { stage: 3, figure: FIGURE_STONEMASON, work: 600 }
        { stage: 4, figure: FIGURE_CARPENTER, work: 400 }
        { stage: 4, figure: FIGURE_STONEMASON, work: 700 }
        { stage: 5, figure: FIGURE_CARPENTER, work: 300 }
        { stage: 5, figure: FIGURE_STONEMASON, work: 400 }
        { stage: 6, figure: FIGURE_CARPENTER, work: 300 }
        { stage: 6, figure: FIGURE_STONEMASON, work: 725 }
        { stage: 7, figure: FIGURE_STONEMASON, work: 560 }
        { stage: 8, figure: FIGURE_STONEMASON, work: 600 }
        { stage: 9, figure: FIGURE_STONEMASON, work: 600 }
        { stage: 9, figure: FIGURE_CARPENTER, work: 400 }
        { stage: 10, figure: FIGURE_STONEMASON, work: 400 }
        { stage: 10, figure: FIGURE_CARPENTER, work: 400 }
        { stage: 11, figure: FIGURE_STONEMASON, work: 700 }
        { stage: 11, figure: FIGURE_CARPENTER, work: 400 }
        { stage: 12, figure: FIGURE_STONEMASON, work: 525 }
        { stage: 13, figure: FIGURE_STONEMASON, work: 600 }
        { stage: 14, figure: FIGURE_STONEMASON, work: 500 }
        { stage: 15, figure: FIGURE_STONEMASON, work: 600 }
        { stage: 16, figure: FIGURE_STONEMASON, work: 500 }
        { stage: 17, figure: FIGURE_STONEMASON, work: 500 }
        { stage: 18, figure: FIGURE_STONEMASON, work: 550 }
    ]
    fire_proof : true
    damage_proof : true
    info_title_id [198, 30]
    meta { text_id: 178, help_link:"message_building_caesareum" }
    info_sound : "Wavs/rock3.wav"
    // OG Pharaoh_Model_*.txt row 227 is all zeros.
    cost [ 0, 0, 0, 0, 0 ]
    guild_worker_terrain: TERRAIN_USAGE_ANY
    flags {
        is_monument: true
        non_deletable: true
    }
}
