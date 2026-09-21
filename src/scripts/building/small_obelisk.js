log_info("akhenaten: building_small_obelisk started")

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
    scaffold_offsets [[20, -40], [44, -24], [-4, -24]]
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
        non_deletable: true
    }
}

[es=(building_small_obelisk, can_place)]
function building_small_obelisk_can_place(ev) {
    building_obelisk_can_place(ev)
}

[es=(building_small_obelisk, on_place_checks)]
function building_small_obelisk_on_place_checks(ev) {
    building_obelisk_on_place_checks(ev)
}
