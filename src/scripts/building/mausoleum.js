log_info("akhenaten: building mausoleum started")

building_mausoleum {
    animations {
      // MVP: extras packs have 2 groups only; stage .sg3 follow-up after pack build.
      // Keys: s{a|b|c}{1|2}_v{0|1|2} — stage × camera × art skin.
      // sb* reuse sa* groups until stage packs exist (avoids "group 3 not found").
      sa1_v0 { pack:PACK_LIB_MAUSOLEUM_0, id:1 }
      sa2_v0 { pack:PACK_LIB_MAUSOLEUM_0, id:2 }
      sb1_v0 { pack:PACK_LIB_MAUSOLEUM_0, id:1 }
      sb2_v0 { pack:PACK_LIB_MAUSOLEUM_0, id:2 }
      sc1_v0 { pack:PACK_LIB_MAUS_CARRYOVER, id:1 }
      sc2_v0 { pack:PACK_LIB_MAUS_CARRYOVER, id:2 }

      sa1_v1 { pack:PACK_LIB_MAUSOLEUM_1, id:1 }
      sa2_v1 { pack:PACK_LIB_MAUSOLEUM_1, id:2 }
      sb1_v1 { pack:PACK_LIB_MAUSOLEUM_1, id:1 }
      sb2_v1 { pack:PACK_LIB_MAUSOLEUM_1, id:2 }
      sc1_v1 { pack:PACK_LIB_MAUS_CARRYOVER, id:1 }
      sc2_v1 { pack:PACK_LIB_MAUS_CARRYOVER, id:2 }

      sa1_v2 { pack:PACK_LIB_MAUSOLEUM_2, id:1 }
      sa2_v2 { pack:PACK_LIB_MAUSOLEUM_2, id:2 }
      sb1_v2 { pack:PACK_LIB_MAUSOLEUM_2, id:1 }
      sb2_v2 { pack:PACK_LIB_MAUSOLEUM_2, id:2 }
      sc1_v2 { pack:PACK_LIB_MAUS_CARRYOVER, id:1 }
      sc2_v2 { pack:PACK_LIB_MAUS_CARRYOVER, id:2 }

      // Short aliases / ghost fallback (skin 0)
      sa1 { pack:PACK_LIB_MAUSOLEUM_0, id:1 }
      preview { pack:PACK_LIB_MAUS_CARRYOVER, id:1 }
    }
    // Heaven 8×22 clear land (swap on odd rotation).
    building_size : 22
    init_tiles [8, 22]
    art_stages : 3
    // Place 240 (gate); finish ~220 → 110+110. Timber provisional (ramp).
    sandstone_loads [ 110, 110 ]
    timber_loads [ 100 ]
    placement_resources [
        { resource: RESOURCE_SANDSTONE, count: 240 }
    ]
    fire_proof : true
    damage_proof : true
    info_title_id [198, 25]
    meta { text_id: 178, help_link:"message_building_mausoleum" }
    info_sound : "Wavs/rock3.wav"
    cost [ 3500, 4500, 6000, 8500, 12000 ]
    flags {
        is_monument: true
        allow_rotate: true
    }
}

// M1.4: 3 art skins (MAUSOLEUM_0/1/2). Ctrl+R cycles; titles gr198:25/26/27.
[es=(building_mausoleum, setup_building_variant)]
function building_mausoleum_setup_building_variant(ev) {
    city_planner.custom_building_variant = 0
}

[es=(building_mausoleum, next_building_variant)]
function building_mausoleum_next_building_variant(ev) {
    if (ev.variant < 0) {
        city_planner.custom_building_variant = 0
        return
    }
    city_planner.custom_building_variant = (ev.variant + 1) % 3
}

[es=(building_mausoleum, update_building_variant)]
function building_mausoleum_update_building_variant(ev) {
    var v = city_planner.custom_building_variant | 0
    if (v < 0) {
        v = 0
    }
    city_planner.building_variant = v % 3
}
