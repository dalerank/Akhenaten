log_info("akhenaten: building_recruiter started")

building_recruiter {
  animations {
    preview { pos: [0, 0], pack:PACK_GENERAL, id:166 }
    base { pos: [0, 0], pack:PACK_GENERAL, id:166 }
    work { pos: [10, 10], pack:PACK_GENERAL, id:166, offset:1, max_frames:11 }
  }
  labor_category : LABOR_CATEGORY_MILITARY
  min_houses_coverage : 100
  meta { text_id:136, help_link:"message_building_recruiter_academy" }
  info_sound : "Wavs/BARRACK.WAV"
  building_size : 3
  planner_update_rule {
    unique_building : true
  }
  cost [ 30, 50, 100, 200, 300 ]
  desirability { value:[-6], step:[1], step_size:[1], range: [3] }
  laborers [10]
  fire_risk [4]
  damage_risk [1]
  flags {
    is_military: true
  }
}

[es=(building_recruiter, on_place_checks)]
function building_recruiter_on_place_checks(ev) {
    city.warnings.show_if_not(city.resources.weapons.yards_stored > 0, "#soldiers_need_supplies_of_weapons")
}

[es=(building_recruiter, add_resource)]
function building_recruiter_add_resource(ev) {
    if (ev.resource != RESOURCE_WEAPONS) {
        return
    }
    var building = city.get_building(ev.bid)
    building.store_resource(ev.resource, ev.amount)
}
