log_info("akhenaten: building_weaponsmith started")

building_weaponsmith = {
  animations : {
    preview : { pos : [0, 0], pack:PACK_GENERAL, id:123, },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:123, offset:0 },
    work : { pos : [57, -16], pack:PACK_GENERAL, id:123, offset:1, max_frames:20, duration:5, can_reverse:true },
    copper : { pos : [93, 0], pack:PACK_GENERAL, id:203 },
  }

  input : {
    resource : RESOURCE_COPPER
  }
  output : {
    resource : RESOURCE_WEAPONS
  }
  labor_category : LABOR_CATEGORY_MILITARY
  meta : { help_id: 98, text_id: 124 }
  info_sound : "Wavs/weapon.wav"
  building_size: 2
  cost: [ 24, 40, 80, 120, 150 ]
  desirability : { value:[-3], step:[1], step_size:[1], range: [3] }
  laborers:[12], fire_risk:[4], damage_risk: [2]
  info_advisors [ADVISOR_LABOR, ADVISOR_MILITARY]
  flags {
    is_workshop: true
    is_industry: true
  }
}

[es=(building_weaponsmith, on_place_checks)]
function building_weaponsmith_on_place_checks(ev) {
    var copper = city.resources.copper
    var has_supply = (copper.count_active_industry > 0) || (copper.yards_stored >= 100)
    if (has_supply) {
        return
    }

    city.warnings.show("#building_needs_copper_ore")
    city.warnings.show_if_not(copper.can_produce, "#build_copper_mine")
    city.warnings.show_if_not(copper.can_import, "#setup_trade_route_to_import")
    city.warnings.show_if_not(copper.trade_status == TRADE_STATUS_IMPORT, "#overseer_of_commerce_to_import")
}
