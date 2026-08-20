log_info("akhenaten: building alexandria_library started")

building_alexandria_library {
    animations {
      // PACK_LIB_MAIN_1..5 = LibMaina1..a5 (orientation a MVP).
      sa { pack:PACK_LIB_MAIN_1, id:1 }
      sb { pack:PACK_LIB_MAIN_2, id:1 }
      sc { pack:PACK_LIB_MAIN_3, id:1 }
      sd { pack:PACK_LIB_MAIN_4, id:1 }
      se { pack:PACK_LIB_MAIN_5, id:1 }
      preview { pack:PACK_LIB_MAIN_5, id:1 }
    }
    // Heaven 13×14 clear land; orientation swaps W↔H.
    building_size : 13
    init_tiles [13, 14]
    art_stages : 5
    // Heaven marble 112, wood ~3200; copper provisional (AL0.2).
    marble_loads [ 28, 28, 28, 28 ]
    timber_loads [ 400, 1400, 1400 ]
    copper_loads [ 24 ]
    fire_proof : true
    damage_proof : true
    info_title_id [198, 29]
    meta { text_id: 178, help_link:"message_building_alexandria_library" }
    info_sound : "Wavs/rock3.wav"
    cost [ 5000, 6500, 8000, 11000, 16000 ]
    flags {
        is_monument: true
        allow_rotate: true
    }
}
