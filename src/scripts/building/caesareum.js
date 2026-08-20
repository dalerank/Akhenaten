log_info("akhenaten: building caesareum started")

building_caesareum {
    animations {
      // PACK_CAESAREUM_1..4 — progressive art (ids provisional until CZ0 dump).
      sa { pack:PACK_CAESAREUM_1, id:1 }
      sb { pack:PACK_CAESAREUM_2, id:1 }
      sc { pack:PACK_CAESAREUM_3, id:1 }
      sd { pack:PACK_CAESAREUM_4, id:1 }
      preview { pack:PACK_CAESAREUM_1, id:1 }
    }
    // Heaven 15×15 clear land.
    building_size : 15
    init_tiles [15, 15]
    art_stages : 4
    // Heaven totals: marble 152, granite 8; timber stub (W=Y). Defaults also in C++ base_params.
    marble_loads [ 48, 52, 52 ]
    timber_loads [ 100, 100 ]
    granite_loads [ 8 ]
    fire_proof : true
    damage_proof : true
    info_title_id [198, 30]
    meta { text_id: 178, help_link:"message_building_caesareum" }
    info_sound : "Wavs/rock3.wav"
    cost [ 5000, 6500, 8000, 11000, 16000 ]
    flags {
        is_monument: true
    }
}
