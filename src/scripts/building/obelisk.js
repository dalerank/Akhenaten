log_info("akhenaten: building obelisk started")

building_small_obelisk {
    animations {
      sa { pack:PACK_OBELISK_X3_A, id:1 }
      sb { pack:PACK_OBELISK_X3_B, id:1 }
      sc { pack:PACK_OBELISK_X3_C, id:1 }
      sd { pack:PACK_OBELISK_X3_D, id:1 }
      preview { pack:PACK_OBELISK_X3_A, id:1 }
      ladder { pack:PACK_OBELISK_EXTRA, id:1 }
    }
    building_size : 3
    art_stages : 4
    // Timber per phase 0..; remaining art_stages are masons-only. Tune vs original .pak.
    timber_loads [ 200, 200, 200 ]
    placement_resources [
        { resource: RESOURCE_GRANITE, count: 100 }
    ]
    fire_proof : true
    damage_proof : true
    info_title_id [198, 22]
    meta { text_id: 178, help_link:"message_building_obelisk" }
    info_sound : "Wavs/rock3.wav"
    cost [ 1500, 2000, 2500, 3500, 5000 ]
    flags {
        is_monument: true
    }
}

building_large_obelisk {
    animations {
      sa { pack:PACK_OBELISK_X5_A, id:1 }
      sb { pack:PACK_OBELISK_X5_B, id:1 }
      sc { pack:PACK_OBELISK_X5_C, id:1 }
      sd { pack:PACK_OBELISK_X5_D, id:1 }
      se { pack:PACK_OBELISK_X5_E, id:1 }
      sf { pack:PACK_OBELISK_X5_F, id:1 }
      preview { pack:PACK_OBELISK_X5_A, id:1 }
      ladder { pack:PACK_OBELISK_EXTRA, id:1 }
    }
    building_size : 5
    art_stages : 6
    // Timber per phase 0..; remaining art_stages are masons-only. Tune vs original .pak.
    timber_loads [ 400, 400, 400, 200 ]
    placement_resources [
        { resource: RESOURCE_GRANITE, count: 200 }
    ]
    fire_proof : true
    damage_proof : true
    info_title_id [198, 23]
    meta { text_id: 178, help_link:"message_building_obelisk" }
    info_sound : "Wavs/rock3.wav"
    cost [ 3000, 4000, 5000, 7000, 10000 ]
    flags {
        is_monument: true
    }
}
