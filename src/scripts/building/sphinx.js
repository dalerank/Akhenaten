log_info("akhenaten: building sphinx started")

building_sphinx {
    animations {
      s1a1 { pack:PACK_SPHINX_1_A, id:1 }
      s1a2 { pack:PACK_SPHINX_1_A, id:2 }
      s1b1 { pack:PACK_SPHINX_1_B, id:1 }
      s1b2 { pack:PACK_SPHINX_1_B, id:2 }
      s1c1 { pack:PACK_SPHINX_1_C, id:1 }
      s1c2 { pack:PACK_SPHINX_1_C, id:2 }
      s2a1 { pack:PACK_SPHINX_2_A, id:1 }
      s2a2 { pack:PACK_SPHINX_2_A, id:2 }
      s2b1 { pack:PACK_SPHINX_2_B, id:1 }
      s2b2 { pack:PACK_SPHINX_2_B, id:2 }
      s2c1 { pack:PACK_SPHINX_2_C, id:1 }
      s2c2 { pack:PACK_SPHINX_2_C, id:2 }
      s3a1 { pack:PACK_SPHINX_3_A, id:1 }
      s3a2 { pack:PACK_SPHINX_3_A, id:2 }
      s3b1 { pack:PACK_SPHINX_3_B, id:1 }
      s3b2 { pack:PACK_SPHINX_3_B, id:2 }
      s3c1 { pack:PACK_SPHINX_3_C, id:1 }
      s3c2 { pack:PACK_SPHINX_3_C, id:2 }
      s4a1 { pack:PACK_SPHINX_4_A, id:1 }
      s4a2 { pack:PACK_SPHINX_4_A, id:2 }
      s4b1 { pack:PACK_SPHINX_4_B, id:1 }
      s4b2 { pack:PACK_SPHINX_4_B, id:2 }
      s4c1 { pack:PACK_SPHINX_4_C, id:1 }
      s4c2 { pack:PACK_SPHINX_4_C, id:2 }
      s5a1 { pack:PACK_SPHINX_5_A, id:1 }
      s5a2 { pack:PACK_SPHINX_5_A, id:2 }
      s5b1 { pack:PACK_SPHINX_5_B, id:1 }
      s5b2 { pack:PACK_SPHINX_5_B, id:2 }
      s5c1 { pack:PACK_SPHINX_5_C, id:1 }
      s5c2 { pack:PACK_SPHINX_5_C, id:2 }
      s6a1 { pack:PACK_SPHINX_6_A, id:1 }
      s6a2 { pack:PACK_SPHINX_6_A, id:2 }
      s6b1 { pack:PACK_SPHINX_6_B, id:1 }
      s6b2 { pack:PACK_SPHINX_6_B, id:2 }
      s6c1 { pack:PACK_SPHINX_6_C, id:1 }
      s6c2 { pack:PACK_SPHINX_6_C, id:2 }
      preview { pack:PACK_SPHINX_1_A, id:1 }
    }
    building_size : 6
    init_tiles [6, 18]
    // Placement rotation 0..3: chain a→b→c along axis (temporary; tune via --mixed)
    part_b_offset [[0, 6], [-6, 0], [0, -6], [6, 0]]
    part_c_offset [[0, 12], [-12, 0], [0, -12], [12, 0]]
    fire_proof : true
    damage_proof : true
    info_title_id [198, 21]
    meta { help_id: 362, text_id: 178 }
    info_sound : "Wavs/rock3.wav"
    cost [ 2500, 3500, 4500, 6500, 10000 ]
    flags {
        is_monument: true
    }
}
