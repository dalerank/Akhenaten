log_info("akhenaten: building_water_lift started")

building_water_lift {
  animations {
    _pack { pack:PACK_TERRAIN }
    preview { path: "pharaoh_terrain/transport_00029" }
    base { path: "pharaoh_terrain/transport_00029" }
    base_no_water { path: "pharaoh_terrain/transport_00033" }
    base_floodplain { path: "pharaoh_terrain/transport_00037" }
    work_n { pos [50, 15], path:"sprambient/shadne_00038", duration:8, max_frames:12, internal_offset:true }
    work_e { pos [54, 14], path:"sprambient/shadse_00051", duration:8, max_frames:12, internal_offset:true }
    work_s { pos [60, 15], path:"sprambient/shadsw_00064", duration:8, max_frames:12, internal_offset:true }
    work_w { pos [68, 20], path:"sprambient/shadnw_00077", duration:8, max_frames:12, internal_offset:true }
    minimap { pack:PACK_GENERAL, id:151 }
  }
  labor_category : LABOR_CATEGORY_INFRASTRUCTURE
  fire_proof : 1
  building_size : 2
  planner_update_rule {
    canals : true
    relative_orientation: true
  }
  needs {
    water_access : true
    shoreline : true
    floodplain_shoreline : true
  }
  meta { help_id: 59, text_id: 107 }
  info_sound : "Wavs/waterwheel.WAV"
  cost [ 6, 12, 25, 50, 100 ]
  desirability { value[-3], step[1], step_size[1], range[3] }
  laborers [8]
  fire_risk [0]
  damage_risk [3]
  irrigation_radius : 2
  canal_fill_water_level : 32
  base_irrigation_value : 32
}
