log_info("akhenaten: building_large_obelisk started")

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

    stages {
        stage_1 {
            timber: 400
            ladders: [{x: 30, y: -56}]
            carpenter_point: {x: 30, y: -56}
            carpenter_need: true
            stonemasons_need: false
        }
        stage_2 {
            timber: 400
            ladders: [{x: 58, y: -36}, {x: 30, y: -56}]
            carpenter_point: {x: 58, y: -36}
            carpenter_need: true
            stonemasons_need: false
        }
        stage_3 {
            timber: 400
            ladders: [{x: 2, y: -36}, {x: 58, y: -36}, {x: 30, y: -56}]
            carpenter_point: {x: 2, y: -36}
            carpenter_need: true
            stonemasons_need: false
        }
        stage_4 {
            timber: 200
            ladders: [{x: 30, y: -16}, {x: 2, y: -36}, {x: 58, y: -36}, {x: 30, y: -56}]
            carpenter_point: {x: 30, y: -16}
            carpenter_need: true
            stonemasons_need: false
        }
        stage_5 {
            ladders: [{x: 30, y: -16}, {x: 2, y: -36}, {x: 58, y: -36}, {x: 30, y: -56}]
            stonemasons_point: {x: 30, y: -16}
            carpenter_need: false
            stonemasons_need: true
        }
        stage_6 {
            ladders: []
            stonemasons_point: {x: 30, y: -16}
            carpenter_need: false
            stonemasons_need: true
        }
    }

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
