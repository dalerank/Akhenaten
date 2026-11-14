log_info("akhenaten: building_water_supply started")

[es=building]
building_water_supply {
  type: BUILDING_WATER_SUPPLY
  animations {
    preview { pack:PACK_GENERAL, id:69 }
    base { pack:PACK_GENERAL, id:69, offset:0 }
    base_work { pos[42, 10], pack:PACK_GENERAL, id:69, offset:1, max_frames:1 }
    fancy { pack:PACK_GENERAL, id:69, offset:2 }
    fancy_work { pos[10, 0], pack:PACK_GENERAL, id:69, offset:3, max_frames:1 }
  }

  min_houses_coverage : 50
  overlay : OVERLAY_WATER
  labor_category : LABOR_CATEGORY_WATER_HEALTH,
  fire_proof : true
  meta { text_id:108, help_link:"message_building_water_supply" }
  info_sound : "Wavs/WELL.WAV"
  building_size : 2
  needs {
    groundwater : true
  }
  cost [ 10, 20, 40, 80, 140 ]
  desirability { value[4], step[1], step_size[-1], range[4] }
  laborers[5]
  fire_risk[0]
  damage_risk[0]
  flags {
    keeps_visitor_paths: true
    draw_normal_anim: true
  }
}

// OG spawn_water_supply: days between carriers by the share of workers (100/75/50/25/1%), the share halved below
// low_desirability on the building tile.
var building_water_supply_rules = {
    spawn_delays : [1, 3, 7, 15, 29]
    low_desirability : 30
}

[es=(building_water_supply, spawn_figure)]
function building_water_supply_spawn_figure(ev) {
    var building = city.get_building(ev.bid)
    building.has_water_access = terrain.exists_in_area(building.tile, building.size, TERRAIN_GROUNDWATER)
    if (!building.has_water_access) {
        building.show_on_problem_overlay = 2
        return
    }
    var rules = building_water_supply_rules
    var low = __desirability_at_tile(building.tile.x, building.tile.y) < rules.low_desirability
    building.spawn_service_walker({ min_houses_coverage: building_water_supply.min_houses_coverage, spawn_delays: rules.spawn_delays,
                                    workers_halved: low }, FIGURE_WATER_CARRIER, ACTION_72_WATER_CARRIER_ROAMING)
}

[es=(building_water_supply, update_month)]
function building_water_supply_update_month(ev) {
    var building = city.get_building(ev.bid)
    // OG water_supply_update_image: only a staffed building on groundwater changes its image.
    if (building.num_workers <= 0 || !building.has_water_access) {
        return
    }
    var avg_desirability = __desirability_get_avg(building.tile, 4)
    var is_fancy = avg_desirability > 30
    building.set_fancy(is_fancy)
    var animkey = is_fancy ? "fancy" : "base"
    var params = building.params
    __map_building_tiles_add(building.id, building.tile, params.building_size, building.first_img(animkey), TERRAIN_BUILDING)
}

[es=(building_water_supply, update_graphic)]
function building_water_supply_update_graphic(ev) {
    var building = city.get_building(ev.bid)
    var animkey = building.is_fancy ? "fancy_work" : "base_work"
    building.set_animation(animkey)
}

[es=(building_water_supply, draw_usable_paths)]
function building_water_supply_draw_usable_paths(ev) {
    city.get_building(ev.bid).draw_usable_paths()
}
