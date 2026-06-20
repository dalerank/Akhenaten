log_info("akhenaten: building_water_supply started")

building_water_supply {
  animations {
    preview { pack:PACK_GENERAL, id:69 }
    base { pack:PACK_GENERAL, id:69, offset:0 }
    base_work { pos[42, 10], pack:PACK_GENERAL, id:69, offset:1, max_frames:1 }
    fancy { pack:PACK_GENERAL, id:69, offset:2 }
    fancy_work { pos[10, 0], pack:PACK_GENERAL, id:69, offset:3, max_frames:1 }
  }

  min_houses_coverage : 50
  labor_category : LABOR_CATEGORY_WATER_HEALTH,
  fire_proof : true
  meta { help_id:61, text_id:108 }
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
}

[es=(building_water_supply, on_place_checks)]
function building_water_supply_on_place_checks(ev) {
    var b = city.get_building(ev.bid)
    var has_groundwater = terrain.is(b.tile, TERRAIN_GROUNDWATER)
    city.warnings.show_if_not(has_groundwater, "#needs_groundwater")
}

[es=(building_water_supply, update_month)]
function building_water_supply_update_month(ev) {
    var building = city.get_building(ev.bid)
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
