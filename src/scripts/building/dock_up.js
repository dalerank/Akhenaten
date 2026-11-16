log_info("akhenaten: building_dock_up started")

// OG BUILD_DOCK2 / BUILDING_DOCK_UP: same gameplay as building_dock, Cleopatra sprites.
building_dock_up {
  animations : {
    preview : { pack:PACK_TERRAIN, id:27 },
    base : { pack:PACK_TERRAIN, id:27 },
    wait_n : { pos:[132, -7], pack:PACK_SPR_AMBIENT, id:55, offset:3, max_frames:25, duration:8 },
    wait_w : { pos:[115, 25], pack:PACK_SPR_AMBIENT, id:55, offset:0, max_frames:25, duration:8 },
    wait_s : { pos:[60, 20], pack:PACK_SPR_AMBIENT, id:55, offset:1, max_frames:25, duration:4 },
    wait_e : { pos:[49, -4], pack:PACK_SPR_AMBIENT, id:55, offset:2, max_frames:25, duration:4 },
    work_n : { pos:[152, -13], pack:PACK_SPR_AMBIENT, id:56, offset:3, max_frames:20, duration:8 },
    work_w : { pos:[123, 16], pack:PACK_SPR_AMBIENT, id:56, offset:0, max_frames:20, duration:8 },
    work_s : { pos:[65, 14], pack:PACK_SPR_AMBIENT, id:56, offset:1, max_frames:20, duration:4 },
    work_e : { pos:[38, -12], pack:PACK_SPR_AMBIENT, id:56, offset:2, max_frames:20, duration:4 },
    minimap { pack:PACK_GENERAL, id:149, offset:160 }
  }
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE
  planner_update_rule : {
    relative_orientation: true
  }
  min_houses_coverage : 50
  building_size : 3
  meta : { text_id:101, help_link:"message_building_dock" }
  info_sound : "Wavs/DOCK1.WAV"
  sound_channel : SOUND_CHANNEL_CITY_DOCK
  needs : {
    water_access : true
    shoreline : true
  }
  cost: [ 20, 40, 70, 100, 150 ]
  desirability : { value:[-12], step:[2], step_size:[2], range: [6] }
  laborers:[12], fire_risk:[4], damage_risk: [1]
  flags {
    no_map_edge_margin: true
    is_industry: true
  }
}

[es=(building_dock_up, update_animation)]
function building_dock_up_on_update_animation(ev) {
    building_dock_on_update_animation(ev)
}

[es=(building_dock_up, update_graphic)]
function building_dock_up_on_update_graphic(ev) {
    building_dock_on_update_graphic(ev)
}

[es=(building_dock_up, highlight_waypoints)]
function building_dock_up_highlight_waypoints(ev) {
    building_dock_highlight_waypoints(ev)
}
