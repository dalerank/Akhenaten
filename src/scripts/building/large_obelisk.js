log_info("akhenaten: building_large_obelisk started")

building_large_obelisk {
    animations {
      preview { pack:PACK_OBELISK_X5_A, id:1 }
      ladder { pack:PACK_OBELISK_EXTRA, id:1 }
    }
    building_size : 5

    // Array order = construction phase. ladders/carpenter_point are pixel offsets
    // from the building draw origin (tune via --mixed).
    stages [
        {
            timber: 400
            obelisk_tx { pack:PACK_OBELISK_X5_A, id:1 }
            ladders: [[30, -56]]
            carpenter_point: [30, -56]
            carpenter_need: true
            stonemasons_need: false
        }
        {
            timber: 400
            obelisk_tx { pack:PACK_OBELISK_X5_B, id:1 }
            ladders: [[58, -36], [30, -56]]
            carpenter_point: [58, -36]
            carpenter_need: true
            stonemasons_need: false
        }
        {
            timber: 400
            obelisk_tx { pack:PACK_OBELISK_X5_C, id:1 }
            ladders: [[2, -36], [58, -36], [30, -56]]
            carpenter_point: [2, -36]
            carpenter_need: true
            stonemasons_need: false
        }
        {
            timber: 200
            obelisk_tx { pack:PACK_OBELISK_X5_D, id:1 }
            ladders: [[30, -16], [2, -36], [58, -36], [30, -56]]
            carpenter_point: [30, -16]
            carpenter_need: true
            stonemasons_need: false
        }
        {
            obelisk_tx { pack:PACK_OBELISK_X5_E, id:1 }
            ladders: [[30, -16], [2, -36], [58, -36], [30, -56]]
            stonemasons_point: [30, -16]
            carpenter_need: false
            stonemasons_need: true
        }
        {
            obelisk_tx { pack:PACK_OBELISK_X5_F, id:1 }
            ladders: []
            stonemasons_point: [30, -16]
            carpenter_need: false
            stonemasons_need: true
        }
    ]

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
        non_deletable: true
    }
}

[es=(building_large_obelisk, can_place)]
function building_large_obelisk_can_place(ev) {
    building_obelisk_can_place(ev)
}

[es=(building_large_obelisk, on_place_checks)]
function building_large_obelisk_on_place_checks(ev) {
    building_obelisk_on_place_checks(ev)
}
