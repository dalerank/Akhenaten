log_info("akhenaten: building_small_obelisk started")

building_small_obelisk {
    animations {
      preview { pack:PACK_OBELISK_X3_A, id:1 }
      ladder { pack:PACK_OBELISK_EXTRA, id:1 }
    }
    building_size : 3

    // Array order = construction phase. ladders/carpenter_point are pixel offsets
    // from the building draw origin (tune via --mixed).
    stages [
        {
            timber: 200
            obelisk_tx { pack:PACK_OBELISK_X3_A, id:1 }
            ladders [[30, 10]]
            carpenter_point [30, 40]
            carpenter_need: true
            stonemasons_need: false
        }
        {
            timber: 200
            obelisk_tx { pack:PACK_OBELISK_X3_A, id:1 }
            ladders [[30, 10], [85, 10]]
            carpenter_point [120, -20]
            carpenter_need: true
            stonemasons_need: false
        }
        {
            timber: 200
            obelisk_tx { pack:PACK_OBELISK_X3_A, id:1 }
            ladders [[30, 10], [85, 10], [30, -50]]
            carpenter_point [160, 40]
            carpenter_need: true
            stonemasons_need: false
        }
        {
            obelisk_tx { pack:PACK_OBELISK_X3_A, id:1 }
            ladders [[30, 10], [85, 10], [30, -50], [85, -50]]
            stonemasons_point [70, -84]
            carpenter_need: false
            stonemasons_need: true
        }
        {
            obelisk_tx { pack:PACK_OBELISK_X3_A, id:1 }
            ladders [[30, 10], [85, 10], [30, -50], [85, -50]]
            stonemasons_point [120, -84]
            carpenter_need: false
            stonemasons_need: true
        }
        {
            obelisk_tx { pack:PACK_OBELISK_X3_B, id:1 }
            ladders [[30, 10], [85, 10]]
            stonemasons_point [70, -24]
            carpenter_need: false
            stonemasons_need: true
        }
        {
            obelisk_tx { pack:PACK_OBELISK_X3_B, id:1 }
            ladders [[30, 10], [85, 10]]
            stonemasons_point [120, -24]
            carpenter_need: false
            stonemasons_need: true
        }
        {
            obelisk_tx { pack:PACK_OBELISK_X3_B, id:1 }
            ladders [[30, 10]]
            stonemasons_point [120, 0]
            carpenter_need: false
            stonemasons_need: true
        }
        {
            obelisk_tx { pack:PACK_OBELISK_X3_C, id:1 }
            ladders []
            stonemasons_point [70, 0]
            carpenter_need: false
            stonemasons_need: true
        }
        {
            obelisk_tx { pack:PACK_OBELISK_X3_D, id:1 }
            ladders []
            stonemasons_point [70, 0]
            carpenter_need: false
            stonemasons_need: true
        }
    ]

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
