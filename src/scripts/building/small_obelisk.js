log_info("akhenaten: building_small_obelisk started")

building_small_obelisk {
    animations {
      preview { pack:PACK_OBELISK_X3_A, id:1 }
      ladder { pack:PACK_OBELISK_EXTRA, id:1 }
    }
    building_size : 3

    // OG small obelisk (0xCF): 10 spots — stages 1-4 carpenter, 5-10 stonemason.
    // work_ticks from obelisk_small_work_spots (320/320/600/600, 580/580/520/520/340/340).
    // ladders/carpenter_point/stonemasons_point are pixel offsets from the draw origin.
    stages [
        {
            timber: 200
            work_ticks: 320
            obelisk_tx { pack:PACK_OBELISK_X3_A, id:1 }
            ladders [[30, 10]]
            carpenter_point [30, 40]
            carpenter_need: true
            stonemasons_need: false
        }
        {
            timber: 200
            work_ticks: 320
            obelisk_tx { pack:PACK_OBELISK_X3_A, id:1 }
            ladders [[30, 10], [85, 10]]
            carpenter_point [120, -20]
            carpenter_need: true
            stonemasons_need: false
        }
        {
            timber: 200
            work_ticks: 600
            obelisk_tx { pack:PACK_OBELISK_X3_A, id:1 }
            ladders [[30, 10], [85, 10], [30, -50]]
            carpenter_point [160, 40]
            carpenter_need: true
            stonemasons_need: false
        }
        {
            timber: 200
            work_ticks: 600
            obelisk_tx { pack:PACK_OBELISK_X3_A, id:1 }
            ladders [[30, 10], [85, 10], [30, -50], [85, -50]]
            carpenter_point [70, -84]
            carpenter_need: true
            stonemasons_need: false
        }
        {
            work_ticks: 580
            obelisk_tx { pack:PACK_OBELISK_X3_A, id:1 }
            ladders [[30, 10], [85, 10], [30, -50], [85, -50]]
            stonemasons_point [70, -84]
            carpenter_need: false
            stonemasons_need: true
        }
        {
            work_ticks: 580
            obelisk_tx { pack:PACK_OBELISK_X3_A, id:1 }
            ladders [[30, 10], [85, 10], [30, -50], [85, -50]]
            stonemasons_point [120, -84]
            carpenter_need: false
            stonemasons_need: true
        }
        {
            work_ticks: 520
            obelisk_tx { pack:PACK_OBELISK_X3_B, id:1 }
            ladders [[30, 10], [85, 10]]
            stonemasons_point [70, -24]
            carpenter_need: false
            stonemasons_need: true
        }
        {
            work_ticks: 520
            obelisk_tx { pack:PACK_OBELISK_X3_B, id:1 }
            ladders [[30, 10], [85, 10]]
            stonemasons_point [120, -24]
            carpenter_need: false
            stonemasons_need: true
        }
        {
            work_ticks: 340
            obelisk_tx { pack:PACK_OBELISK_X3_C, id:1 }
            ladders [[30, 10]]
            stonemasons_point [120, 0]
            carpenter_need: false
            stonemasons_need: true
        }
        {
            work_ticks: 340
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
