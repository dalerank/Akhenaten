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
  cost : [ 30, 50, 70, 100, 150 ]
  desirability : { value:[4], step:[1], step_size:[-1], range:[4] }
  laborers:[10], fire_risk:[6], damage_risk: [2]
  max_service: 75
  // OG Pharaoh_Model_*.txt: papyrus per teacher (Scribal School) and its % with a Ptah complex oracle (Large Temple to Ptah row)
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
    var p = building_scribal_school
    var cost = dcy_get(p.walker_cost)
    if (__city_temple_complex_has_upgrade(BUILDING_TEMPLE_COMPLEX_PTAH, 2 /* etc_upgrade_oracle */)) {
        cost = Math.floor(cost * dcy_get(p.ptah_oracle_walker_cost_pct) / 100)
    }
    return cost
}

function building_scribal_school_spawn_delay(pct_workers) {
    var d = building_scribal_school.spawn_delays
    if (pct_workers >= 100) return d[0]
    if (pct_workers >= 75) return d[1]
    if (pct_workers >= 50) return d[2]
    if (pct_workers >= 25) return d[3]
    return d[4]
}

// OG spawn_stock_walker: the day counter keeps running (uint8 wrap) while papyrus is short;
// papyrus is paid only when the teacher leaves.
[es=(building_scribal_school, spawn_figure)]
function building_scribal_school_spawn_figure(ev) {
    var building = city.get_building(ev.bid)
    building.check_labor_problem()
    if (building.has_figure(BUILDING_SLOT_SERVICE) || !building.has_road_access) {
        return
    }

    building.common_spawn_labor_seeker(building_scribal_school.min_houses_coverage)

    var pct_workers = building.worker_percentage
    if (pct_workers <= 0) {
        return
    }

    building.figure_spawn_delay = (building.figure_spawn_delay + 1) & 0xff
    if (building.figure_spawn_delay <= building_scribal_school_spawn_delay(pct_workers)) {
        return
    }

    var cost = building_scribal_school_walker_cost()
    if (cost > building.stored_resource(RESOURCE_PAPYRUS)) {
        return
    }

    building.consume_resource(RESOURCE_PAPYRUS, cost)
    building.figure_spawn_delay = 0
    building.create_roaming_figure(FIGURE_TEACHER, ACTION_125_ROAMER_ROAMING, BUILDING_SLOT_SERVICE)
}

[es=(building_scribal_school, add_resource)]
function building_scribal_school_add_resource(ev) {
    if (ev.resource != RESOURCE_PAPYRUS) {
        return
    }
    var building = city.get_building(ev.bid)
    building.store_resource(ev.resource, ev.amount)
}
