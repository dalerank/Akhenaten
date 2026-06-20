log_info("akhenaten: building_scribal_school started")

building_scribal_school = {
  animations : {
    preview : { pack:PACK_GENERAL, id:42},
    base : { pack:PACK_GENERAL, id:42},
    work : { pos:[2, -25], pack:PACK_GENERAL, id:42, offset:1, max_frames:11, duration:4, can_reverse:true },
    papyrus : { pos:[61, 14], pack:PACK_GENERAL, id:207, offset:0},
  }
  input : {
    resource : RESOURCE_PAPYRUS
  }
  meta : { help_id: 68, text_id: 85 }
  info_sound : "Wavs/school_scribe.wav"
  min_houses_coverage : 50
  building_size : 2
  labor_category : LABOR_CATEGORY_EDUCATION
  cost : [ 30, 50, 70, 100, 150 ]
  desirability : { value:[4], step:[1], step_size:[-1], range:[4] }
  laborers:[10], fire_risk:[6], damage_risk: [2]
  max_service: 75
}

[es=(building_scribal_school, on_place_checks)]
function building_scribal_school_on_place_checks(ev) {
  var papyrus = city.resources.papyrus
  var has_supply = (papyrus.count_active_industry > 0) || (papyrus.yards_stored > 0)
  if (has_supply) {
    return
  }

  city.warnings.show("#needs_papyrus")
  city.warnings.show_if_not(papyrus.can_produce, "#build_papyrus_maker")
  city.warnings.show_if_not(papyrus.can_import, "#import_papyrus_overseer")
  city.warnings.show_if_not(papyrus.trade_status == TRADE_STATUS_IMPORT, "#import_papyrus_trade_route")
}

[es=(building_scribal_school, update_month)]
function building_scribal_school_update_month(ev) {
  var building = city.get_building(ev.bid)
  var stored = building.stored_resource(RESOURCE_PAPYRUS)
  if (stored <= 0) {
    return
  }

  var want_spent = Math.floor(building.num_workers * 50 / 100)
  var spent = Math.min(stored, want_spent)
  building.consume_resource(RESOURCE_PAPYRUS, spent)
}
