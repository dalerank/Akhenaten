log_info("akhenaten: building_wood_cutter started")

building_wood_cutter {
  animations {
    preview { pos : [0, 0], pack:PACK_GENERAL, id:65 }
    base { pos : [0, 0], pack:PACK_GENERAL, id:65 }
    work { pos : [30, -17], pack:PACK_GENERAL, id:65, offset:1, max_frames:12, duration:4 }
  }
  overlay_anims {
    wood {
      pos : [65, 3]
      pack:PACK_GENERAL
      id:202
      resource : RESOURCE_TIMBER
      default_active : true
    }
  }
  output {
    resource : RESOURCE_TIMBER
  }
  flags {
    is_harvester: true
    is_industry: true
    work_anim: true
  }
  building_size : 2
  meta { text_id:120, help_link:"message_building_woodcutter_and_reed_gatherer" }
  info_sound : "Wavs/lumber.wav"
  sound_channel : SOUND_CHANNEL_CITY_NONE
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE
  min_houses_coverage : 100
  max_storage_amount : 200
  max_gatherers : 1
  cost [ 10, 20, 40, 80, 140 ]
  desirability { value[-4], step[1], step_size[1], range[3] }
  laborers[8], fire_risk[4], damage_risk[3]
}

[es=(building_wood_cutter, update_animation)]
function building_wood_cutter_on_update_animation(ev) {
    var b = city.get_building(ev.bid)
    if (!b.play_animation) {
        return
    }
    if (b.stored_resource(RESOURCE_TIMBER) >= building_wood_cutter.max_storage_amount) {
        b.play_animation = false
    }
}
