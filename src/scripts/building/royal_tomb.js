log_info("akhenaten: building royal_tomb started")

// PACK_TOMB_THUTMOS (TombThut.sg3) — verified group starts (system@0 + content@201):
//   id1..6 hallwaysbmp | id7..8 room1 | id9..10 room2
//   id11..14 thutmose×40 (16+4+16+4) — chamber cutaway progress (map bulk)
//   id15..16 tombground | id17 Entrance(All)×4 | id18..19 tombcliff | id20..21 hallways2
// thutmose id11: 8 progress × 2 camera (even/odd). sa..sh = stages 1..8; si reuses last.
// TombThutFin id11: only offset 12/14 are real finished frames (earlier are 7×7 stubs).
building_small_royal_tomb {
    animations {
      sa { pack:PACK_TOMB_THUTMOS, id:11, offset:0 }
      sb { pack:PACK_TOMB_THUTMOS, id:11, offset:2 }
      sc { pack:PACK_TOMB_THUTMOS, id:11, offset:4 }
      sd { pack:PACK_TOMB_THUTMOS, id:11, offset:6 }
      se { pack:PACK_TOMB_THUTMOS, id:11, offset:8 }
      sf { pack:PACK_TOMB_THUTMOS, id:11, offset:10 }
      sg { pack:PACK_TOMB_THUTMOS, id:11, offset:12 }
      sh { pack:PACK_TOMB_THUTMOS, id:11, offset:14 }
      si { pack:PACK_TOMB_THUTMOS, id:11, offset:14 }
      preview { pack:PACK_TOMB_THUTMOS_FINAL, id:11, offset:12 }
      finish { pack:PACK_TOMB_THUTMOS_FINAL, id:11, offset:12 }
      entrance { pack:PACK_TOMB_THUTMOS, id:17 }
      ground { pack:PACK_TOMB_THUTMOS, id:15 }
      cliff { pack:PACK_TOMB_THUTMOS, id:18 }
    }
    building_size : 11
    init_tiles [11, 20]
    entrance_size [1, 1]
    art_stages : 9
    max_masons : 1
    max_artisans : 2
    // Help 478: 400 lamps before work. Later phase loads burn from stock (≤700).
    // Clay/paint from Stairway (phase≥1): 1 guild-load (=100) — provisional vs My Palace totals.
    lamp_loads [ 400, 0, 0, 0, 0, 0, 0, 0, 0 ]
    clay_loads [ 0, 100, 100, 100, 100, 100, 100, 100, 100 ]
    paint_loads [ 0, 100, 100, 100, 100, 100, 100, 100, 100 ]
    fire_proof : true
    damage_proof : true
    info_title_id [198, 33]
    meta { text_id: 178, help_link:"message_building_royal_burial_tomb" }
    info_sound : "Wavs/rock3.wav"
    cost [ 2500, 3500, 4500, 6000, 8500 ]
    flags {
        is_monument: true
        allow_rotate: true
    }
}

// PACK_TOMB_TUTANKHAMUN (TombTut.sg3) — verified:
//   id1..6 hallways | id7..10 room3 | id11..16 tutankamen (16+4)×3
//   id11 298×180/150 — main bulk progress (8×2 camera); id17..18 ground; id19 Entrance
// TombTutFin id11: real finish at offset 12/14 only.
building_medium_royal_tomb {
    animations {
      sa { pack:PACK_TOMB_TUTANKHAMUN, id:11, offset:0 }
      sb { pack:PACK_TOMB_TUTANKHAMUN, id:11, offset:2 }
      sc { pack:PACK_TOMB_TUTANKHAMUN, id:11, offset:4 }
      sd { pack:PACK_TOMB_TUTANKHAMUN, id:11, offset:6 }
      se { pack:PACK_TOMB_TUTANKHAMUN, id:11, offset:8 }
      sf { pack:PACK_TOMB_TUTANKHAMUN, id:11, offset:10 }
      sg { pack:PACK_TOMB_TUTANKHAMUN, id:11, offset:12 }
      sh { pack:PACK_TOMB_TUTANKHAMUN, id:11, offset:14 }
      preview { pack:PACK_TOMB_TUTANKHAMUN_FINAL, id:11, offset:12 }
      finish { pack:PACK_TOMB_TUTANKHAMUN_FINAL, id:11, offset:12 }
      entrance { pack:PACK_TOMB_TUTANKHAMUN, id:19 }
      ground { pack:PACK_TOMB_TUTANKHAMUN, id:17 }
      cliff { pack:PACK_TOMB_TUTANKHAMUN, id:20 }
    }
    building_size : 14
    init_tiles [14, 16]
    entrance_size [1, 1]
    art_stages : 8
    max_masons : 1
    max_artisans : 2
    lamp_loads [ 400, 0, 0, 0, 0, 0, 0, 0 ]
    clay_loads [ 0, 100, 100, 100, 100, 100, 100, 100 ]
    paint_loads [ 0, 100, 100, 100, 100, 100, 100, 100 ]
    fire_proof : true
    damage_proof : true
    info_title_id [198, 34]
    meta { text_id: 178, help_link:"message_building_royal_burial_tomb" }
    info_sound : "Wavs/rock3.wav"
    cost [ 3500, 4500, 6000, 8500, 11000 ]
    flags {
        is_monument: true
        allow_rotate: true
    }
}

// PACK_TOMB_SETI (TombSeti.sg3) — verified:
//   id1..6 hallways | id7..10 room1 | id11..16 room2 | id17..18 room4/5
//   id19..22 seti (298×150 + 358×210 bulk) | id23..24 ground | id25 Entrance | id26..27 cliff
// Main map bulk = id21 (358×210, 8×2 camera). Fin real finish @offset 12/14.
building_large_royal_tomb {
    animations {
      sa { pack:PACK_TOMB_SETI, id:21, offset:0 }
      sb { pack:PACK_TOMB_SETI, id:21, offset:2 }
      sc { pack:PACK_TOMB_SETI, id:21, offset:4 }
      sd { pack:PACK_TOMB_SETI, id:21, offset:6 }
      se { pack:PACK_TOMB_SETI, id:21, offset:8 }
      sf { pack:PACK_TOMB_SETI, id:21, offset:10 }
      sg { pack:PACK_TOMB_SETI, id:21, offset:12 }
      sh { pack:PACK_TOMB_SETI, id:21, offset:14 }
      preview { pack:PACK_TOMB_SETI_FINAL, id:21, offset:12 }
      finish { pack:PACK_TOMB_SETI_FINAL, id:21, offset:12 }
      entrance { pack:PACK_TOMB_SETI, id:25 }
      ground { pack:PACK_TOMB_SETI, id:23 }
      cliff { pack:PACK_TOMB_SETI, id:26 }
    }
    building_size : 17
    init_tiles [17, 33]
    entrance_size [1, 1]
    art_stages : 8
    max_masons : 1
    max_artisans : 2
    lamp_loads [ 400, 0, 0, 0, 0, 0, 0, 0 ]
    clay_loads [ 0, 100, 100, 100, 100, 100, 100, 100 ]
    paint_loads [ 0, 100, 100, 100, 100, 100, 100, 100 ]
    fire_proof : true
    damage_proof : true
    info_title_id [198, 35]
    meta { text_id: 178, help_link:"message_building_royal_burial_tomb" }
    info_sound : "Wavs/rock3.wav"
    cost [ 5000, 6500, 8500, 11000, 15000 ]
    flags {
        is_monument: true
        allow_rotate: true
    }
}

// PACK_TOMB_RAMSES (TombRam.sg3) — verified:
//   id1..6 hallways | rooms … | id23..28 ramses | id29..30 ground | id31 Entrance | id32..33 cliff
// Main map bulk = id25 (358×210, 8×2 camera). Fin real finish @offset 12/14.
building_grand_royal_tomb {
    animations {
      sa { pack:PACK_TOMB_RAMSES, id:25, offset:0 }
      sb { pack:PACK_TOMB_RAMSES, id:25, offset:2 }
      sc { pack:PACK_TOMB_RAMSES, id:25, offset:4 }
      sd { pack:PACK_TOMB_RAMSES, id:25, offset:6 }
      se { pack:PACK_TOMB_RAMSES, id:25, offset:8 }
      sf { pack:PACK_TOMB_RAMSES, id:25, offset:10 }
      sg { pack:PACK_TOMB_RAMSES, id:25, offset:12 }
      sh { pack:PACK_TOMB_RAMSES, id:25, offset:14 }
      preview { pack:PACK_TOMB_RAMSES_FINAL, id:25, offset:12 }
      finish { pack:PACK_TOMB_RAMSES_FINAL, id:25, offset:12 }
      entrance { pack:PACK_TOMB_RAMSES, id:31 }
      ground { pack:PACK_TOMB_RAMSES, id:29 }
      cliff { pack:PACK_TOMB_RAMSES, id:32 }
    }
    building_size : 23
    init_tiles [23, 29]
    entrance_size [1, 1]
    art_stages : 8
    max_masons : 1
    max_artisans : 2
    lamp_loads [ 400, 0, 0, 0, 0, 0, 0, 0 ]
    clay_loads [ 0, 100, 100, 100, 100, 100, 100, 100 ]
    paint_loads [ 0, 100, 100, 100, 100, 100, 100, 100 ]
    fire_proof : true
    damage_proof : true
    info_title_id [198, 36]
    meta { text_id: 178, help_link:"message_building_royal_burial_tomb" }
    info_sound : "Wavs/rock3.wav"
    cost [ 8000, 10000, 13000, 17000, 22000 ]
    flags {
        is_monument: true
        allow_rotate: true
    }
}
