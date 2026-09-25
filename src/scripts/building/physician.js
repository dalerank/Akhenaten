log_info("akhenaten: building_physician started")

[es=building]
building_physician {
  type: BUILDING_PHYSICIAN
  animations {
    _pack { pack:PACK_GENERAL }
    preview { id:70 }
    base { id:70 }
    work { pos [60, -60], id:70, offset:1, max_frames:11 }
  }

  min_houses_coverage : 50
  max_serve_clients : 1000
  overlay: OVERLAY_PHYSICIAN
  labor_category : LABOR_CATEGORY_WATER_HEALTH,
  sound_channel : SOUND_CHANNEL_CITY_PHYSICIAN
  meta { text_id: 83, help_link:"message_building_physician" }
  info_sound : "Wavs/DOCTOR.WAV"
  building_size : 2
  cost [ 10, 15, 30, 50, 100 ]
  desirability { value[2], step[1], step_size[-1], range[2] }
  laborers [8]
  fire_risk [3]
  damage_risk [3]
  flags {
    draw_normal_anim: true
  }
}

[es=(building_physician, spawn_figure)]
function building_physician_spawn_figure(ev) {
    var building = city.get_building(ev.bid)
    building.common_spawn_roamer(FIGURE_PHYSICIAN, building_physician.min_houses_coverage, ACTION_60_PHYSICIAN_CREATED)
}

[es=(building_physician, update_month)]
function building_physician_update_month(ev) {
    city.get_building(ev.bid).residents_served_this_month = 0
}

[es=(building_physician, update_graphic)]
function building_physician_update_graphic(ev) {
    var building = city.get_building(ev.bid)
    var animkey = building.play_animation ? "work" : "none"
    building.set_animation(animkey)
}
