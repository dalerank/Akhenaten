log_info("akhenaten: building_chariots_workshop started")

building_chariots_workshop = {
  animations : {
    preview : { pack:PACK_GENERAL, id:124 },
    base : { pack:PACK_GENERAL, id:124 },
    work : { pack:PACK_GENERAL, id:124 },
    timber : { pos:[51, 18], pack:PACK_GENERAL, id:206 },
    weapon : { pos:[46, 25], pack:PACK_GENERAL, id:207 },
  },
  input : {
    resource : RESOURCE_TIMBER
    resource_second : RESOURCE_WEAPONS
  }
  output : {
    resource : RESOURCE_CHARIOTS
  }
  production_rate : 20,
  production_rate_dcy : [100, 80, 70, 60, 50],
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
  building_size : 2,
  cost: [ 50, 100, 150, 300, 500 ]
  desirability : { value:[-6], step:[1], step_size:[1], range: [6] }
  laborers:[30], fire_risk:[4], damage_risk: [3]
  info_advisors [ADVISOR_LABOR, ADVISOR_MILITARY]
  flags {
    is_workshop: true
    is_industry: true
  }
}

[es=(building_chariots_workshop, update_animation)]
function building_chariots_workshop_on_update_animation(ev) {
    var b = city.get_building(ev.bid)
    if (!b.play_animation) {
        return
    }
    if (__building_industry_progress_pct(b.id) != 0) {
        return
    }
    if (b.stored_resource(RESOURCE_TIMBER) < 100 || b.stored_resource(RESOURCE_WEAPONS) < 100) {
        b.play_animation = false
    }
}
