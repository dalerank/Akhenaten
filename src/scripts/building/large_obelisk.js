log_info("akhenaten: building_large_obelisk started")

building_large_obelisk {
    animations {
      preview { pack:PACK_OBELISK_X5_A, id:1 }
      ladder { pack:PACK_OBELISK_EXTRA, id:1 }
    }
    building_size : 5

    // OG large obelisk (0xD0): 18 spots — stages 1-8 carpenter, 9-18 stonemason.
    // work_ticks from obelisk_large_work_spots (320/320/610/610/680/680/750/750,
    // 740/740/670/670/500/500/530/530/340/340).
    // Two columns, four rows. Carpenters raise bays left-then-right, bottom to top.
    // Stonemasons carve a→f from the tip down and strike bays in reverse.
    stages [
        {
            timber: 200
            work_ticks: 320
            obelisk_tx { pack:PACK_OBELISK_X5_A, id:1 }
            ladders [[86, 13]]
            carpenter_point [86, 13]
            carpenter_need: true
            stonemasons_need: false
        }
        {
            timber: 200
            work_ticks: 320
            obelisk_tx { pack:PACK_OBELISK_X5_A, id:1 }
            ladders [[86, 13], [158, 13]]
            carpenter_point [158, 13]
            carpenter_need: true
            stonemasons_need: false
        }
        {
            timber: 200
            work_ticks: 610
            obelisk_tx { pack:PACK_OBELISK_X5_A, id:1 }
            ladders [[86, 13], [158, 13], [86, -47]]
            carpenter_point [86, -47]
            carpenter_need: true
            stonemasons_need: false
        }
        {
            timber: 200
            work_ticks: 610
            obelisk_tx { pack:PACK_OBELISK_X5_A, id:1 }
            ladders [[86, 13], [158, 13], [86, -47], [158, -47]]
            carpenter_point [158, -47]
            carpenter_need: true
            stonemasons_need: false
        }
        {
            timber: 200
            work_ticks: 680
            obelisk_tx { pack:PACK_OBELISK_X5_A, id:1 }
            ladders [[86, 13], [158, 13], [86, -47], [158, -47], [86, -107]]
            carpenter_point [86, -107]
            carpenter_need: true
            stonemasons_need: false
        }
        {
            timber: 200
            work_ticks: 680
            obelisk_tx { pack:PACK_OBELISK_X5_A, id:1 }
            ladders [[86, 13], [158, 13], [86, -47], [158, -47], [86, -107], [158, -107]]
            carpenter_point [158, -107]
            carpenter_need: true
            stonemasons_need: false
        }
        {
            timber: 200
            work_ticks: 750
            obelisk_tx { pack:PACK_OBELISK_X5_A, id:1 }
            ladders [[86, 13], [158, 13], [86, -47], [158, -47], [86, -107], [158, -107], [86, -167]]
            carpenter_point [86, -167]
            carpenter_need: true
            stonemasons_need: false
        }
        {
            timber: 200
            work_ticks: 750
            obelisk_tx { pack:PACK_OBELISK_X5_A, id:1 }
            ladders [[86, 13], [158, 13], [86, -47], [158, -47], [86, -107], [158, -107], [86, -167], [158, -167]]
            carpenter_point [158, -167]
            carpenter_need: true
            stonemasons_need: false
        }
        {
            work_ticks: 740
            obelisk_tx { pack:PACK_OBELISK_X5_A, id:1 }
            ladders [[86, 13], [158, 13], [86, -47], [158, -47], [86, -107], [158, -107], [86, -167], [158, -167]]
            stonemasons_point [158, -167]
            carpenter_need: false
            stonemasons_need: true
        }
        {
            work_ticks: 740
            obelisk_tx { pack:PACK_OBELISK_X5_A, id:1 }
            ladders [[86, 13], [158, 13], [86, -47], [158, -47], [86, -107], [158, -107], [86, -167], [158, -167]]
            stonemasons_point [86, -167]
            carpenter_need: false
            stonemasons_need: true
        }
        {
            work_ticks: 670
            obelisk_tx { pack:PACK_OBELISK_X5_B, id:1 }
            ladders [[86, 13], [158, 13], [86, -47], [158, -47], [86, -107], [158, -107], [86, -167]]
            stonemasons_point [158, -167]
            carpenter_need: false
            stonemasons_need: true
        }
        {
            work_ticks: 670
            obelisk_tx { pack:PACK_OBELISK_X5_B, id:1 }
            ladders [[86, 13], [158, 13], [86, -47], [158, -47], [86, -107], [158, -107]]
            stonemasons_point [86, -167]
            carpenter_need: false
            stonemasons_need: true
        }
        {
            work_ticks: 500
            obelisk_tx { pack:PACK_OBELISK_X5_C, id:1 }
            ladders [[86, 13], [158, 13], [86, -47], [158, -47], [86, -107]]
            stonemasons_point [158, -107]
            carpenter_need: false
            stonemasons_need: true
        }
        {
            work_ticks: 500
            obelisk_tx { pack:PACK_OBELISK_X5_D, id:1 }
            ladders [[86, 13], [158, 13], [86, -47], [158, -47]]
            stonemasons_point [86, -107]
            carpenter_need: false
            stonemasons_need: true
        }
        {
            work_ticks: 530
            obelisk_tx { pack:PACK_OBELISK_X5_E, id:1 }
            ladders [[86, 13], [158, 13], [86, -47]]
            stonemasons_point [158, -47]
            carpenter_need: false
            stonemasons_need: true
        }
        {
            work_ticks: 530
            obelisk_tx { pack:PACK_OBELISK_X5_E, id:1 }
            ladders [[86, 13], [158, 13]]
            stonemasons_point [86, -47]
            carpenter_need: false
            stonemasons_need: true
        }
        {
            work_ticks: 340
            obelisk_tx { pack:PACK_OBELISK_X5_F, id:1 }
            ladders [[86, 13]]
            stonemasons_point [158, 13]
            carpenter_need: false
            stonemasons_need: true
        }
        {
            work_ticks: 340
            obelisk_tx { pack:PACK_OBELISK_X5_F, id:1 }
            ladders []
            stonemasons_point [122, 13]
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
