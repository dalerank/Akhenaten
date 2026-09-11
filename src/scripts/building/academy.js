log_info("akhenaten: building_academy started")

[es=building]
building_academy {
  type: BUILDING_ACADEMY
  show_in_debug: false
  animations {
    _pack { pack:PACK_GENERAL }
    preview { id:44 }
    base { id:44 }
    work { pos [36, -4], id:44, offset:1, max_frames:18 }
  }

  overlay : OVERLAY_EDUCATION
  labor_category : LABOR_CATEGORY_EDUCATION
  sound_channel : SOUND_CHANNEL_CITY_NONE
  building_size : 2
  min_houses_coverage : 50
  cost [ 200, 250, 300, 400, 500 ]
  desirability { value[-3], step[1], step_size[1], range[3] }
  laborers [20]
  fire_risk [4]
  damage_risk [1]
  max_service: 100
  flags {
    draw_normal_anim: true
    work_anim: true
  }
}

[es=(building_academy, spawn_figure)]
function building_academy_spawn_figure(ev) {
    var building = city.get_building(ev.bid)
    building.common_spawn_roamer(FIGURE_ACADEMY_SCRIBER, building_academy.min_houses_coverage, ACTION_125_ROAMER_ROAMING)
}
