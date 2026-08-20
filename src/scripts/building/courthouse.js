log_info("akhenaten: building_courthouse started")

building_courthouse {
  animations {
    preview { pack:PACK_GENERAL, id:62, }
    base { pack:PACK_GENERAL, id:62, }
    work { pos[80, -80], pack:PACK_GENERAL, id:62, offset:1, max_frames:11 }
  }

  labor_category : LABOR_CATEGORY_INFRASTRUCTURE
  overlay : OVERLAY_COUTHOUSE
  min_houses_coverage : 50
  building_size : 3
  meta { text_id:176, help_link:"message_building_courthouse" }
  info_sound : "Wavs/forum.WAV"
  cost [ 30, 50, 100, 200, 400 ]
  desirability { value[8], step[2], step_size[-2], range[3] }
  crime { value[-5], step[1], step_size[-1], range[4] }
  laborers[10]
  fire_risk[0]
  damage_risk[1]

  flags {
    is_administration: true
  }
}

[es=(building_courthouse, spawn_figure)]
function building_courthouse_spawn_figure(ev) {
    var building = city.get_building(ev.bid)
    building.common_spawn_roamer(FIGURE_MAGISTRATE, building_courthouse.min_houses_coverage, ACTION_125_ROAMER_ROAMING)
}

[es=(building_courthouse, update_graphic)]
function building_courthouse_update_graphic(ev) {
    var building = city.get_building(ev.bid)
    var animkey = building.play_animation ? "work" : "none"
    building.set_animation(animkey)
}
