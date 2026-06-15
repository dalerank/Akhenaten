log_info("akhenaten: building_papyrus_maker started")

building_papyrus_maker = {
  animations : {
    preview : { pos: [0, 0], pack:PACK_GENERAL, id:44 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:44 },
    work : { pos : [7, -10], pack:PACK_GENERAL, id:44, offset:1, max_frames:10, duration:4 },
    reeds : { pos : [35, 4], pack:PACK_GENERAL, id:206 },
  },
  input : {
    resource : RESOURCE_REEDS
  }
  output : {
    resource : RESOURCE_PAPYRUS
  }
  production_rate : 50,
  production_rate_dcy : [100, 80, 70, 60, 50],
  building_size : 2,
  meta : { help_id:1, text_id:190 }
  info_sound : "Wavs/paper.wav"
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
  cost: [ 20, 30, 50, 100, 200 ]
  desirability : { value:[-4], step:[1], step_size:[1], range: [4] }
  laborers:[12], fire_risk:[4], damage_risk: [2]
  info_advisors [ADVISOR_LABOR]
  flags {
    is_workshop: true
    is_industry: true
  }
}

[es=(building_papyrus_maker, on_place_checks)]
function building_papyrus_maker_on_place_checks(ev) {
    var reeds = city.resources.reeds
    var has_supply = (reeds.count_active_industry > 0) || (reeds.yards_stored > 0)
    if (has_supply) {
        return
    }

    city.warnings.show("#building_needs_reeds")
    city.warnings.show_if_not(reeds.can_produce, "#build_reed_gatherer")
    city.warnings.show_if_not(reeds.can_import, "#setup_trade_route_to_import")
    city.warnings.show_if_not(reeds.trade_status == TRADE_STATUS_IMPORT, "#overseer_of_commerce_to_import")
}
