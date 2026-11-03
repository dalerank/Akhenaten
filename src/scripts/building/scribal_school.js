log_info("akhenaten: building_scribal_school started")

[es=building]
building_scribal_school {
  type: BUILDING_SCRIBAL_SCHOOL
  animations : {
    preview : { pack:PACK_GENERAL, id:42},
    base : { pack:PACK_GENERAL, id:42},
    work : { pos:[2, -25], pack:PACK_GENERAL, id:42, offset:1, max_frames:11, duration:4, can_reverse:true },
  }
  overlay_anims {
    papyrus {
      pos : [61, 14]
      pack:PACK_GENERAL
      id:207
      resource : RESOURCE_PAPYRUS
      stack : true
      step : [5, -5]
      max_count : 8
      default_active : true
    }
  }
  input : {
    resource : RESOURCE_PAPYRUS
  }
  meta : { text_id: 85, help_link:"message_building_scribal_school" }
  info_sound : "Wavs/school_scribe.wav"
  overlay : OVERLAY_SCRIBAL_SCHOOL
  min_houses_coverage : 50
  building_size : 2
  labor_category : LABOR_CATEGORY_EDUCATION
  cost : [ 30, 120, 150, 180, 225 ]
  desirability : { value:[4], step:[1], step_size:[-1], range:[4] }
  laborers:[10]
  fire_risk : [ 6, 25, 30, 36, 45 ]
  damage_risk : [0]
  // OG advisor education: active schools * 300 / school_age
  max_service: 300
  // OG Pharaoh_Model_*.txt: papyrus per walker and its % with a Ptah complex oracle (Large Temple to Ptah row)
  walker_cost : [2, 5, 10, 20, 40]
  ptah_oracle_walker_cost_pct : [12, 60, 60, 70, 90]
  spawn_delays : [5, 10, 25, 50, 100]
  flags {
    work_anim: true
  }
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

function building_scribal_school_walker_cost() {
    return education_walker_cost(building_scribal_school)
}

[es=(building_scribal_school, spawn_figure)]
function building_scribal_school_spawn_figure(ev) {
    education_spawn_stock_walker(city.get_building(ev.bid), building_scribal_school, FIGURE_TEACHER)
}

[es=(building_scribal_school, add_resource)]
function building_scribal_school_add_resource(ev) {
    if (ev.resource != RESOURCE_PAPYRUS) {
        return
    }
    var building = city.get_building(ev.bid)
    building.store_resource(ev.resource, ev.amount)
}
