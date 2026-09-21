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

    stages {
        stage_1 {
            timber: 200
            ladders: [{x: 20, y: -40}]
            carpenter_point: {x: 20, y: -20}
            carpenter_need: true
            stonemasons_need: false
        }
        stage_2 {
            timber: 200
            ladders: [{x: 44, y: -24}, {x: 20, y: -40}]
            carpenter_point: {x: 44, y: -24}
            carpenter_need: true
            stonemasons_need: false
        }
        stage_3 {
            timber: 200
            ladders: [{x: -4, y: -24}, {x: 44, y: -24}, {x: 20, y: -40}]
            carpenter_point: {x: -4, y: -24}
            carpenter_need: true
            stonemasons_need: false
        }
        stage_4 {
            ladders: [{x: -4, y: -24}, {x: 44, y: -24}, {x: 20, y: -40}]
            stonemasons_point: {x: -4, y: -24}
            carpenter_need: false
            stonemasons_need: true
        }
        stage_5 {
            ladders: [{x: -4, y: -24}, {x: 44, y: -24}]
            stonemasons_point: {x: -4, y: -24}
            carpenter_need: false
            stonemasons_need: true
        }
        stage_6 {
            ladders: [{x: -4, y: -24}]
            stonemasons_point: {x: -4, y: -24}
            carpenter_need: false
            stonemasons_need: true
        }
        stage_7 {
            ladders: []
            stonemasons_point: {x: -4, y: -24}
            carpenter_need: false
            stonemasons_need: true
        }
    }

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
