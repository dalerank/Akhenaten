log_info("akhenaten: building health started")

building_apothecary {
    animations {
        preview { pos [0, 0], pack:PACK_GENERAL, id:68 }
        base { pos [0, 0], pack:PACK_GENERAL, id:68 }
        work { pos [25, -35], pack:PACK_GENERAL, id:68, offset:1, max_frames:11 }
    }
    labor_category : LABOR_CATEGORY_WATER_HEALTH
    overlay : OVERLAY_APOTHECARY
    sound_channel : SOUND_CHANNEL_CITY_APOTHECARY
    min_houses_coverage : 50
    max_serve_clients : 100
    meta { text_id:81, help_link:"message_building_apothecary" }
    info_sound : "Wavs/apothecary.wav"
    building_size : 1
    cost [ 6, 10, 15, 30, 50 ]
    desirability { value[1], step[1], step_size[-1], range[1] }
    laborers[5]
    fire_risk[4]
    damage_risk[2]
}

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
  building_size : 1
  meta { text_id:84, help_link:"message_building_dentist" }
  info_sound : "Wavs/dentist.wav"
  cost [ 10, 15, 30, 50, 80 ]
  desirability { value[2], step[1], step_size[-1], range[2] }
  laborers[5]
  fire_risk[4]
  damage_risk[2]
}

building_physician {
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
  info_sound : "Wavs/physician.wav"
  building_size : 2
  cost [ 10, 15, 30, 50, 100 ]
  desirability { value[2], step[1], step_size[-1], range[2] }
  laborers [8]
  fire_risk [3]
  damage_risk [3]
}

[es=(building_apothecary, spawn_figure)]
function building_apothecary_spawn_figure(ev) {
    var building = city.get_building(ev.bid)
    building.common_spawn_roamer(FIGURE_HERBALIST, building_apothecary.min_houses_coverage, ACTION_4_HERBALIST_ROAMING)
}

[es=(building_apothecary, update_graphic)]
function building_apothecary_update_graphic(ev) {
    var building = city.get_building(ev.bid)
    var animkey = building.play_animation ? "work" : "none"
    building.set_animation(animkey)
}


[es=(building_physician, spawn_figure)]
function building_physician_spawn_figure(ev) {
    var building = city.get_building(ev.bid)
    building.common_spawn_roamer(FIGURE_PHYSICIAN, building_physician.min_houses_coverage, ACTION_60_PHYSICIAN_CREATED)
}

[es=(building_physician, update_graphic)]
function building_physician_update_graphic(ev) {
    var building = city.get_building(ev.bid)
    var animkey = building.play_animation ? "work" : "none"
    building.set_animation(animkey)
}