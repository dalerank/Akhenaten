log_info("akhenaten: building education started")

[es=building]
building_library {
  type: BUILDING_LIBRARY
  animations {
    preview { pos[0, 0], pack:PACK_GENERAL, id:43 }
    base { pos[0, 0], pack:PACK_GENERAL, id:43 }
    work { pos[48, -20], pack:PACK_GENERAL, id:43, offset:1, max_frames:12, duration:8 }
  }

  overlay : OVERLAY_LIBRARY
  min_houses_coverage : 50
  meta { text_id: 87, help_link:"message_building_library" }
  labor_category : LABOR_CATEGORY_EDUCATION
  building_size : 3
  cost [ 90, 140, 200, 300, 400 ]
  desirability { value[8], step[2], step_size[-2], range[6] }
  laborers[30]
  fire_risk[6]
  damage_risk[1]
  max_service: 800
  input { resource : RESOURCE_PAPYRUS }
  max_storage_amount : 500
  // OG Pharaoh_Model_*.txt: papyrus per walker and its % with a Ptah complex oracle (Large Temple to Ptah row)
  walker_cost : [5, 10, 20, 40, 60]
  ptah_oracle_walker_cost_pct : [12, 60, 60, 70, 90]
  spawn_delays : [5, 10, 25, 50, 100]
  flags {
    draw_normal_anim: true
  }
}

function education_walker_cost(params) {
    var cost = dcy_get(params.walker_cost)
    var complex = city.get_temple_complex()
    if (complex && complex.type == BUILDING_TEMPLE_COMPLEX_PTAH && complex.has_upgrade(TEMPLE_COMPLEX_UPGRADE_ORACLE)) {
        cost = Math.floor(cost * dcy_get(params.ptah_oracle_walker_cost_pct) / 100)
    }
    return cost
}

function education_spawn_delay(params, pct_workers) {
    var d = params.spawn_delays
    if (pct_workers >= 100) return d[0]
    if (pct_workers >= 75) return d[1]
    if (pct_workers >= 50) return d[2]
    if (pct_workers >= 25) return d[3]
    return d[4]
}

// OG spawn_stock_walker: the day counter keeps running (uint8 wrap) while papyrus is short;
// papyrus is paid only when the walker leaves.
function education_spawn_stock_walker(building, params, figure_type) {
    building.check_labor_problem()
    if (building.has_figure(BUILDING_SLOT_SERVICE) || !building.has_road_access) {
        return
    }

    building.common_spawn_labor_seeker(params.min_houses_coverage)

    var pct_workers = building.worker_percentage
    if (pct_workers <= 0) {
        return
    }

    building.figure_spawn_delay = (building.figure_spawn_delay + 1) & 0xff
    if (building.figure_spawn_delay <= education_spawn_delay(params, pct_workers)) {
        return
    }

    var cost = education_walker_cost(params)
    if (cost > building.stored_resource(RESOURCE_PAPYRUS)) {
        return
    }

    building.consume_resource(RESOURCE_PAPYRUS, cost)
    building.figure_spawn_delay = 0
    building.create_roaming_figure(figure_type, ACTION_125_ROAMER_ROAMING, BUILDING_SLOT_SERVICE)
}

function building_library_walker_cost() {
    return education_walker_cost(building_library)
}

[es=(building_library, spawn_figure)]
function building_library_spawn_figure(ev) {
    education_spawn_stock_walker(city.get_building(ev.bid), building_library, FIGURE_LIBRARIAN)
}

[es=(building_library, add_resource)]
function building_library_add_resource(ev) {
    if (ev.resource != RESOURCE_PAPYRUS) {
        return
    }
    var building = city.get_building(ev.bid)
    building.store_resource(ev.resource, ev.amount)
}

[es=(building_library, update_graphic)]
function building_library_update_graphic(ev) {
    var building = city.get_building(ev.bid)
    var animkey = building.play_animation ? "work" : "base"
    building.set_animation(animkey)
}
