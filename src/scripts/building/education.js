log_info("akhenaten: building education started")

building_library {
  animations {
    preview { pos[0, 0], pack:PACK_GENERAL, id:43 }
    base { pos[0, 0], pack:PACK_GENERAL, id:43 }
    work { pos[48, -20], pack:PACK_GENERAL, id:43, offset:1, max_frames:12, duration:8 }
  }

  min_houses_coverage : 50
  meta { text_id: 87, help_link:"message_building_library" }
  labor_category : LABOR_CATEGORY_EDUCATION
  building_size : 3
  cost [ 90, 140, 200, 300, 400 ]
  desirability { value[8], step[2], step_size[-2], range[6] }
  laborers[20]
  fire_risk[6]
  damage_risk[1]
  max_service: 800
  flags {
    draw_normal_anim: true
  }
}

[es=(building_library, spawn_figure)]
function building_library_spawn_figure(ev) {
    var building = city.get_building(ev.bid)
    building.common_spawn_roamer(FIGURE_LIBRARIAN, building_library.min_houses_coverage, ACTION_125_ROAMER_ROAMING)
}

[es=(building_library, update_graphic)]
function building_library_update_graphic(ev) {
    var building = city.get_building(ev.bid)
    var animkey = building.play_animation ? "work" : "base"
    building.set_animation(animkey)
}
