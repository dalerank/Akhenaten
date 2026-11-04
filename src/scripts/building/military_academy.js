log_info("akhenaten: building_military_academy started")

[es=building]
building_military_academy {
  type: BUILDING_MILITARY_ACADEMY
  animations {
    preview { pos: [0, 0], pack:PACK_GENERAL, id:173 }
    base { pos: [0, 0], pack:PACK_GENERAL, id:173 }
    work { pos: [33, -38], pack:PACK_GENERAL, id:173, offset:1, max_frames:12 }
  }
  labor_category : LABOR_CATEGORY_MILITARY
  meta { text_id: 135, help_link:"message_building_recruiter_academy" }
  info_sound : "Wavs/BARRACK.WAV"
  building_size : 4
  // OG generate_labor_seeker when houses_covered < 101.
  min_houses_coverage : 100
  planner_update_rule {
    unique_building : true
  }
  cost [ 240, 300, 500, 1000, 1500 ]
  desirability { value:[8], step:[2], step_size:[-2], range: [6] }
  laborers[25]
  fire_risk[4]
  damage_risk[1]
  flags {
    is_military: true
    work_anim: true
  }
}

[es=building]
building_military_academy_2 {
  type: BUILDING_MILITARY_ACADEMY_2
  animations {
    preview { pos: [0, 0], pack:PACK_GENERAL, id:173 }
    base { pos: [0, 0], pack:PACK_GENERAL, id:173 }
    work { pos: [33, -38], pack:PACK_GENERAL, id:173, offset:1, max_frames:12 }
  }
  labor_category : LABOR_CATEGORY_MILITARY
  meta { text_id: 135, help_link:"message_building_recruiter_academy" }
  info_sound : "Wavs/BARRACK.WAV"
  building_size : 4
  min_houses_coverage : 100
  cost [ 300, 500, 1000, 1500, 2000 ]
  desirability { value:[8], step:[2], step_size:[-2], range: [6] }
  laborers[30]
  fire_risk[4]
  damage_risk[1]
  flags {
    is_military: true
    work_anim: true
  }
}

[es=building]
building_military_academy_3 {
  type: BUILDING_MILITARY_ACADEMY_3
  animations {
    preview { pos: [0, 0], pack:PACK_GENERAL, id:173 }
    base { pos: [0, 0], pack:PACK_GENERAL, id:173 }
    work { pos: [33, -38], pack:PACK_GENERAL, id:173, offset:1, max_frames:12 }
  }
  labor_category : LABOR_CATEGORY_MILITARY
  meta { text_id: 135, help_link:"message_building_recruiter_academy" }
  info_sound : "Wavs/BARRACK.WAV"
  building_size : 4
  min_houses_coverage : 100
  cost [ 300, 500, 1000, 1500, 2000 ]
  desirability { value:[8], step:[2], step_size:[-2], range: [6] }
  laborers[30]
  fire_risk[4]
  damage_risk[1]
  flags {
    is_military: true
    work_anim: true
  }
}

[es=(building_military_academy, spawn_figure)]
function building_military_academy_spawn_figure(ev) {
    var b = city.get_building(ev.bid)
    if (!b.has_road_access) {
        return
    }
    b.common_spawn_labor_seeker(b.params.min_houses_coverage)
}

[es=(building_military_academy_2, spawn_figure)]
function building_military_academy_2_spawn_figure(ev) {
    var b = city.get_building(ev.bid)
    if (!b.has_road_access) {
        return
    }
    b.common_spawn_labor_seeker(b.params.min_houses_coverage)
}

[es=(building_military_academy_3, spawn_figure)]
function building_military_academy_3_spawn_figure(ev) {
    var b = city.get_building(ev.bid)
    if (!b.has_road_access) {
        return
    }
    b.common_spawn_labor_seeker(b.params.min_houses_coverage)
}
