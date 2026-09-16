log_info("akhenaten: building workshop started")

building_brewery {
  animations {
    preview { pack:PACK_GENERAL, id:116 },
    base { pack:PACK_GENERAL, id:116 },
    work { pack:PACK_GENERAL, id:116, max_frames: 12 }
    barley { pos:[28, -35], pack:PACK_GENERAL, id:208, max_frames: 12 }
  }
  input {
    resource : RESOURCE_BARLEY
  }
  output {
    resource : RESOURCE_BEER
  }

  overlay : OVERLAY_BREWERY
  water_amount_for_production : 50
  max_water_storage : 100
  progress_max : 400,
  production_rate : 50,
  production_rate_dcy : [100, 80, 70, 60, 50],
  meta { text_id:122, help_link:"message_building_brewery" }
  info_sound : "Wavs/brewery.wav"
  building_size : 2
  cost [ 15, 25, 50, 80, 120 ]
  desirability { value[-5], step[1], step_size[1], range[5] }
  laborers[12]
  fire_risk[4]
  damage_risk[2]
  info_advisors [ADVISOR_LABOR]
  flags {
    is_workshop: true
    is_industry: true
    work_anim: true
  }
}

[es=(building_brewery, on_place_checks)]
function building_brewery_on_place_checks(ev) {
    var barley = city.resources.barley
    var has_supply = (barley.count_active_industry > 0) || (barley.yards_stored > 0)
    if (!has_supply) {
        city.warnings.show("#needs_barley")
        if (barley.can_produce) {
            city.warnings.show("#build_barley_farm")
        } else if (barley.can_import) {
            city.warnings.show_if_not(barley.trade_status == TRADE_STATUS_IMPORT, "#overseer_of_commerce_to_import")
        } else if (barley.could_import) {
            city.warnings.show("#setup_trade_route_to_import")
        }
    }

    if (game_features.gameplay_brewery_requires_water) {
        var b = city.get_building(ev.bid)
        var size = b.params.building_size
        var has_water = terrain.exists_in_area(b.tile, size, TERRAIN_GROUNDWATER)
            || terrain.exists_in_area(b.tile, size, TERRAIN_FOUNTAIN_RANGE)
            || terrain.exists_in_radius(b.tile, size, 3, TERRAIN_WATER)
            || terrain.exists_in_radius(b.tile, size, 3, TERRAIN_FLOODPLAIN)
        city.warnings.show_if_not(has_water, "#needs_water_access")
    }
}

[es=(building_brewery, update_animation)]
function building_brewery_on_update_animation(ev) {
    var b = city.get_building(ev.bid)
    if (!b.play_animation) {
        return
    }

    if (b.stored_resource(RESOURCE_BARLEY) < 100) {
        b.play_animation = false
        return
    }

    if (game_features.gameplay_brewery_requires_water && b.stored_resource(RESOURCE_WATER) < 50) {
        b.play_animation = false
    }
}

building_jewels_workshop = {
  animations : {
    preview : { pos: [0, 0], pack:PACK_GENERAL, id:119 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:119 },
    work : { pos : [7, -10], pack:PACK_GENERAL, id:119, offset:1, max_frames:9 },
  },
  input : {
    resource: RESOURCE_GEMS
  }
  output : {
    resource : RESOURCE_LUXURY_GOODS
  }
  building_size : 2,
  meta : { text_id:125, help_link:"message_building_jeweler_and_luxury_goods" }
  info_sound : "Wavs/gem_r.wav"
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE
  cost: [ 18, 30, 50, 100, 200 ]
  desirability : { value:[-2], step:[1], step_size:[1], range: [2] }
  laborers:[12], fire_risk:[4], damage_risk: [0]
  material_reduction_per_nearby_workshop : 5
  info_advisors [ADVISOR_LABOR]
  flags {
    is_workshop: true
    is_industry: true
    work_anim: true
  }
}

[es=(building_jewels_workshop, on_place_checks)]
function building_jewels_workshop_on_place_checks(ev) {
    var gems = city.resources.gems
    var has_supply = (gems.count_active_industry > 0) || (gems.yards_stored > 0)
    if (has_supply) {
        return
    }

    city.warnings.show("#needs_gems")
    city.warnings.show_if_not(gems.can_produce, "#build_gem_mine")
    city.warnings.show_if_not(gems.can_import, "#setup_trade_route_to_import")
    city.warnings.show_if_not(gems.trade_status == TRADE_STATUS_IMPORT, "#overseer_of_commerce_to_import")
}
