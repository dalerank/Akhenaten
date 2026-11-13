log_info("akhenaten: building royal_tomb started")

// OG royal tombs: the layout, chambers, work and art groups live in monument_royal_tomb_data.cpp
// (pack group = OG image group minus the pack base). OG model files give every tomb cost 0.

building_small_royal_tomb {
    animations {
      preview { pack:PACK_TOMB_THUTMOS_FINAL, id:11, offset:12 }
    }
    building_size : 1
    art_pack : PACK_TOMB_THUTMOS
    fire_proof : true
    damage_proof : true
    info_title_id [198, 33]
    meta { text_id: 178, help_link:"message_building_royal_burial_tomb" }
    info_sound : "Wavs/rock3.wav"
    cost [ 0, 0, 0, 0, 0 ]
    guild_worker_terrain: TERRAIN_USAGE_ANY
    flags {
        is_monument: true
        non_deletable: true
    }
}

building_medium_royal_tomb {
    animations {
      preview { pack:PACK_TOMB_TUTANKHAMUN_FINAL, id:11, offset:12 }
    }
    building_size : 1
    art_pack : PACK_TOMB_TUTANKHAMUN
    fire_proof : true
    damage_proof : true
    info_title_id [198, 34]
    meta { text_id: 178, help_link:"message_building_royal_burial_tomb" }
    info_sound : "Wavs/rock3.wav"
    cost [ 0, 0, 0, 0, 0 ]
    guild_worker_terrain: TERRAIN_USAGE_ANY
    flags {
        is_monument: true
        non_deletable: true
    }
}

building_large_royal_tomb {
    animations {
      preview { pack:PACK_TOMB_SETI_FINAL, id:21, offset:12 }
    }
    building_size : 1
    art_pack : PACK_TOMB_SETI
    fire_proof : true
    damage_proof : true
    info_title_id [198, 35]
    meta { text_id: 178, help_link:"message_building_royal_burial_tomb" }
    info_sound : "Wavs/rock3.wav"
    cost [ 0, 0, 0, 0, 0 ]
    guild_worker_terrain: TERRAIN_USAGE_ANY
    flags {
        is_monument: true
        non_deletable: true
    }
}

building_grand_royal_tomb {
    animations {
      preview { pack:PACK_TOMB_RAMSES_FINAL, id:25, offset:12 }
    }
    building_size : 1
    art_pack : PACK_TOMB_RAMSES
    fire_proof : true
    damage_proof : true
    info_title_id [198, 36]
    meta { text_id: 178, help_link:"message_building_royal_burial_tomb" }
    info_sound : "Wavs/rock3.wav"
    cost [ 0, 0, 0, 0, 0 ]
    guild_worker_terrain: TERRAIN_USAGE_ANY
    flags {
        is_monument: true
        non_deletable: true
    }
}
