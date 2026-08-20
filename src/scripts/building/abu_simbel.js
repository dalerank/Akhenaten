log_info("akhenaten: building abu_simbel started")

building_abu_simbel {
    animations {
      // PACK_ABUSIMBEL (AbuSimbel.sg3) — verified group starts (system@0 + content@201):
      //   id1 @201 backing×4 | id2 @205 2statue×20 | id3 @203 (alt backing)
      //   id4 @225 midcut_back×14 | id5 @239 midcut_front×14 | id6 @253 stairs×6
      //   id7..14 @259..266 cliffs×8 (one group each) | id15 @267 scaffold×2 | id16 @269 scaffold×2
      // Composite parts: cliffs 3×3, statues 6×6, midcut 3×3. Footprint 9×21 (Heaven/OG).
      backing { pack:PACK_ABUSIMBEL, id:1 }
      sa1 { pack:PACK_ABUSIMBEL, id:2, offset:0 }
      sa2 { pack:PACK_ABUSIMBEL, id:2, offset:1 }
      sb1 { pack:PACK_ABUSIMBEL, id:2, offset:2 }
      sb2 { pack:PACK_ABUSIMBEL, id:2, offset:3 }
      sc1 { pack:PACK_ABUSIMBEL, id:2, offset:4 }
      sc2 { pack:PACK_ABUSIMBEL, id:2, offset:5 }
      sd1 { pack:PACK_ABUSIMBEL, id:2, offset:6 }
      sd2 { pack:PACK_ABUSIMBEL, id:2, offset:7 }
      se1 { pack:PACK_ABUSIMBEL, id:2, offset:8 }
      se2 { pack:PACK_ABUSIMBEL, id:2, offset:9 }
      sf1 { pack:PACK_ABUSIMBEL, id:2, offset:10 }
      sf2 { pack:PACK_ABUSIMBEL, id:2, offset:11 }
      sg1 { pack:PACK_ABUSIMBEL, id:2, offset:12 }
      sg2 { pack:PACK_ABUSIMBEL, id:2, offset:13 }
      sh1 { pack:PACK_ABUSIMBEL, id:2, offset:14 }
      sh2 { pack:PACK_ABUSIMBEL, id:2, offset:15 }
      si1 { pack:PACK_ABUSIMBEL, id:2, offset:16 }
      si2 { pack:PACK_ABUSIMBEL, id:2, offset:17 }
      sj1 { pack:PACK_ABUSIMBEL, id:2, offset:18 }
      sj2 { pack:PACK_ABUSIMBEL, id:2, offset:19 }
      preview { pack:PACK_ABUSIMBEL, id:2, offset:18 }
      finish1 { pack:PACK_ABUSIMBEL, id:2, offset:18 }
      finish2 { pack:PACK_ABUSIMBEL, id:2, offset:19 }

      midcut_back { pack:PACK_ABUSIMBEL, id:4 }
      midcut_front { pack:PACK_ABUSIMBEL, id:5 }
      stairs { pack:PACK_ABUSIMBEL, id:6 }
      // cliffs 00001..00008 → pack id7..14
      // L_FAR uses jagged peak (iso-back = screen-outer). R uses 00006/00004 pair.
      cliff_l_far { pack:PACK_ABUSIMBEL, id:7 }    // abu-cliffs_00001 jagged peak
      cliff_l_near { pack:PACK_ABUSIMBEL, id:13 }  // abu-cliffs_00007 shelf→statue
      cliff_r_far { pack:PACK_ABUSIMBEL, id:12 }   // abu-cliffs_00006 corner strata
      cliff_r_near { pack:PACK_ABUSIMBEL, id:10 }  // abu-cliffs_00004 sloping edge
      // unused: id8=00002, id9=00003, id11=00005, id14=00008
      scaffold_a { pack:PACK_ABUSIMBEL, id:15 }
      scaffold_b { pack:PACK_ABUSIMBEL, id:15, offset:1 }
      scaffold_c { pack:PACK_ABUSIMBEL, id:16 }
      scaffold_d { pack:PACK_ABUSIMBEL, id:16, offset:1 }
    }
    // Main part is NW cliff 3×3; full composite AABB is init_tiles.
    building_size : 3
    init_tiles [9, 21]
    art_stages : 10
    timber_loads [ 400, 400, 400, 200, 200, 0, 0, 0, 0, 0 ]
    fire_proof : true
    damage_proof : true
    info_title_id [198, 37]
    meta { text_id: 178, help_link:"message_building_abu_simbel" }
    info_sound : "Wavs/rock3.wav"
    cost [ 5000, 6500, 8000, 11000, 16000 ]
    flags {
        is_monument: true
        non_deletable: true
        allow_rotate: true
    }
}
