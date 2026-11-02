log_info("akhenaten: building health started")

building_dentist {
  animations {
    preview { pack:PACK_GENERAL, id:67 }
    base { pack:PACK_GENERAL, id:67 }
    work { pack:PACK_GENERAL, id:67, offset:1, max_frames:12 }
  }

  overlay : OVERLAY_DENTIST
  labor_category : LABOR_CATEGORY_WATER_HEALTH
  min_houses_coverage : 50
  max_serve_clients : 1000
  spawn_delays : [3, 7, 15, 29, 44]
  building_size : 1
  meta { text_id:84, help_link:"message_building_dentist" }
  info_sound : "Wavs/DOCTOR.WAV"
  cost [ 10, 15, 30, 50, 80 ]
  desirability { value[2], step[1], step_size[-1], range[2] }
  laborers[5]
  fire_risk[4]
  damage_risk[2]
  flags {
    draw_normal_anim: true
    work_anim: true
  }
}

[es=(building_dentist, spawn_figure)]
function building_dentist_spawn_figure(ev) {
    city.get_building(ev.bid).spawn_service_walker(building_dentist, FIGURE_DENTIST, ACTION_125_ROAMER_ROAMING)
}
