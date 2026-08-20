log_info("akhenaten: building cattle ranch started")

building_cattle_ranch {
  animations {
    preview { pack:PACK_GENERAL, id:105, },
    base { pack:PACK_GENERAL, id:105, offset:0 },
    work {  pack:PACK_GENERAL, id:105, offset:1, max_frames:12 },
    minimap { pack:PACK_GENERAL, id:149, offset:160 },
  }
  min_houses_coverage : 100
  input {
    resource : RESOURCE_STRAW
  }
  output {
    resource : RESOURCE_MEAT
  }
  building_size : 3
  meta { text_id:117, help_link:"message_building_cattle_ranch" }
  info_sound : "Wavs/cowfarm_r.wav"
  labor_category : LABOR_CATEGORY_FOOD_PRODUCTION
  cost [ 15, 20, 30, 50, 80 ]
  desirability { value:[-4], step:[1], step_size:[1], range: [4] }
  laborers[12]
  fire_risk[1]
  damage_risk[2]
  info_advisors [ADVISOR_LABOR]
  flags {
    is_food: true
  }
}

[es=(building_cattle_ranch, update_animation)]
function building_cattle_ranch_on_update_animation(ev) {
    var b = city.get_building(ev.bid)
    if (!b.play_animation) {
        return
    }
    if (b.stored_resource(RESOURCE_STRAW) < 100 || b.worker_percentage < 50) {
        b.play_animation = false
    }
}
