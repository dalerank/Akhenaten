log_info("akhenaten: building_clay_pit started")

building_clay_pit {
  animations {
    preview { pack:PACK_GENERAL, id:40 }
    base { pack:PACK_GENERAL, id:40 }
    work { pos[18, -20], pack:PACK_GENERAL, id:40, offset:1, max_frames:23, duration:2 }
    flooded { pack:PACK_GENERAL, id:40 }
  }
  output {
    resource : RESOURCE_CLAY
  }
  progress_max : 200,
  building_size : 2,
  production_rate : 100,
  meta { help_id:92, text_id:121 }
  info_sound : "Wavs/clay.wav"
  sound_channel : SOUND_CHANNEL_CITY_CLAY_PIT
  needs {
    nearby_water : true
  }
  flags {
    is_extractor: true
    is_industry: true
  }
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE
  cost[ 8, 15, 30, 50, 100 ]
  desirability { value[-3], step[1], step_size[1], range[2] }
  laborers[8]
  fire_risk[0]
  damage_risk[1]
}

[es=(building_clay_pit, update_graphic)]
function building_clay_pit_on_update_graphic(ev) {
    var b = city.get_building(ev.bid)
    if (b.destroy_reason == e_destroy_flooded) {
        b.set_animation("flooded")
        return
    }
    var animkey = b.play_animation ? "work" : "none"
    b.set_animation(animkey)
}
