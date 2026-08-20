log_info("akhenaten: building bridge started")

building_low_bridge {
  animations {
    _pack { pack:PACK_TERRAIN }
    preview { id:63 }
    base { id:63 }
  }
  building_size : 1
  max_length : 8
  min_length : 2
  flags {
    is_water_crossing: true
    is_infrastructure: true
  }
  fire_proof : true
  damage_proof : true
  meta { text_id: 70, help_link:"message_game_concept_water_crossings" }
  cost [8, 32, 40, 48, 60]
  laborers[0]
  fire_risk[0]
  damage_risk[0]
}

// Texture packs for bridge_type grid.
// index = numeric type on the tile; type = optional text alias.
// parts[]: part = e_bridge_part (BRIDGE_PART_*), tip = label, img / pos = draw.
bridge_styles = [
  {
    index: 0,
    type: "low",
    pack: PACK_TERRAIN,
    id: 63,
    parts: [
      { part: BRIDGE_PART_RAMP_DIR_0, tip: "ramp DIR_0", img: 3, pos: [15, -10] }
      { part: BRIDGE_PART_RAMP_DIR_2, tip: "ramp DIR_2", img: 0, pos: [-1, -18] }
      { part: BRIDGE_PART_RAMP_DIR_4, tip: "ramp DIR_4", img: 5, pos: [15, -8] }
      { part: BRIDGE_PART_RAMP_DIR_6, tip: "ramp DIR_6", img: 2, pos: [3, -18] }
      { part: BRIDGE_PART_MID_NE_SW, tip: "mid NE-SW", img: 4, pos: [10, -10] }
      { part: BRIDGE_PART_MID_NW_SE, tip: "mid NW-SE", img: 1, pos: [0, -18] }
    ]
  }
]

building_ship_bridge {
  animations {
    _pack { pack:PACK_TERRAIN }
    preview { id:63 }
    base { id:63 }
  }
  building_size : 1
  max_length : 40
  min_length : 5
  flags {
    is_water_crossing: true
    is_infrastructure: true
  }
  fire_proof : true
  damage_proof : true
  cost [8, 32, 40, 48, 60]
}
