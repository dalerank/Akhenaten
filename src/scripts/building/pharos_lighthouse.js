log_info("akhenaten: building pharos_lighthouse started")

building_pharos_lighthouse {
    animations {
      // PACK_LTHOUSE_1..9 = LtHouse1..9 progressive stages; LtHouse10 = beacon (PL4).
      sa { pack:PACK_LTHOUSE_1, id:1 }
      sb { pack:PACK_LTHOUSE_2, id:1 }
      sc { pack:PACK_LTHOUSE_3, id:1 }
      sd { pack:PACK_LTHOUSE_4, id:1 }
      se { pack:PACK_LTHOUSE_5, id:1 }
      sf { pack:PACK_LTHOUSE_6, id:1 }
      sg { pack:PACK_LTHOUSE_7, id:1 }
      sh { pack:PACK_LTHOUSE_8, id:1 }
      si { pack:PACK_LTHOUSE_9, id:1 }
      preview { pack:PACK_LTHOUSE_9, id:1 }
    }
    // Heaven 6×6 rocky ground (Pharos Island).
    building_size : 6
    init_tiles [6, 6]
    art_stages : 9
    // Heaven marble ~108; timber provisional (scaffold).
    marble_loads [ 22, 22, 22, 21, 21 ]
    timber_loads [ 100, 200, 200 ]
    fire_proof : true
    damage_proof : true
    info_title_id [198, 28]
    meta { text_id: 178, help_link:"message_building_pharos_lighthouse" }
    info_sound : "Wavs/rock3.wav"
    cost [ 5000, 6500, 8000, 11000, 16000 ]
    flags {
        is_monument: true
        non_deletable: true
    }
}
