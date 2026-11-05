log_info("akhenaten: building mortuary started")

function Mortuary(building_id) {
    this.id = building_id
}

Mortuary.prototype = Object.create(Building.prototype)
Mortuary.prototype.constructor = Mortuary

Mortuary.property.residents_served_this_month = { }
Mortuary.property.residents_served_this_year = { }
Mortuary.property.total_residents_served = { }
Mortuary.property.months_active = { }

city.get_mortuary = function(building_id) {
    var b = city.get_building(building_id)
    if (!b.valid || b.type != BUILDING_MORTUARY) {
        return null
    }
    return new Mortuary(building_id)
}

building_mortuary {
  animations {
    preview { pack:PACK_GENERAL, id:175 },
    base { pack:PACK_GENERAL, id:175 },
    work { pos[35, -20], pack:PACK_GENERAL, id:175, offset:1, max_frames:12, duration:4 },
  }
  overlay_anims {
    linen {
      pos : [45, 3]
      pack:PACK_GENERAL
      id:206
      resource : RESOURCE_LINEN
      stack : true
      step : [5, -5]
      max_count : 8
      default_active : true
    }
  }

  input : {
    resource : RESOURCE_LINEN
  }
  max_serve_clients : 1000
  // OG Pharaoh_Model_*.txt: linen per embalmer and its % with a Seth complex altar (Large Temple to Seth row)
  walker_cost : [5, 10, 20, 40, 60]
  seth_altar_walker_cost_pct : [12, 60, 60, 70, 90]
  spawn_delays : [3, 7, 15, 29, 44]
  linen_required_for_animation : 100
  monthly_linen_consumption : 20
  min_houses_coverage : 50
  building_size : 2
  labor_category : LABOR_CATEGORY_WATER_HEALTH
  meta { text_id:82, help_link:"message_building_mortuary" }
  info_sound : "Wavs/EMBALM.WAV"
  cost [ 20, 80, 100, 120, 150 ]
  desirability { value[-3], step[2], step_size[1], range[2] }
  laborers[8]
  fire_risk [ 4, 17, 20, 24, 30 ]
  damage_risk [0]
  flags {
    work_anim: true
  }
}

function building_mortuary_walker_cost() {
    var params = building_mortuary
    var cost = dcy_get(params.walker_cost)
    var complex = city.get_temple_complex(BUILDING_TEMPLE_COMPLEX_SETH)
    if (complex && complex.has_upgrade(TEMPLE_COMPLEX_UPGRADE_ALTAR)) {
        cost = Math.floor(cost * dcy_get(params.seth_altar_walker_cost_pct) / 100)
    }
    return cost
}

[es=(building_mortuary, spawn_figure)]
function building_mortuary_spawn_figure(ev) {
    if (game_features.gameplay_change_mortuary_mothballed_linen && __city_resource_is_mothballed(RESOURCE_LINEN)) {
        return
    }

    building_spawn_stock_walker(city.get_building(ev.bid), building_mortuary, FIGURE_EMBALMER, RESOURCE_LINEN, building_mortuary_walker_cost())
}

[es=(building_mortuary, on_place_checks)]
function building_mortuary_on_place_checks(ev) {
    var linen = city.resources.linen
    var has_supply = (linen.count_active_industry > 0) || (linen.yards_stored > 0)
    if (has_supply) {
        return
    }

    city.warnings.show("#building_needs_linen")
    city.warnings.show_if_not(!linen.can_produce, "#build_weaver_or_import_linen")
    city.warnings.show_if_not(linen.can_import, "#setup_trade_route_to_import")
    city.warnings.show_if_not(linen.trade_status == TRADE_STATUS_IMPORT, "#overseer_of_commerce_to_import")
}

[es=(building_mortuary, update_animation)]
function building_mortuary_update_animation(ev) {
    var b = city.get_building(ev.bid)
    if (!b.play_animation) {
        return
    }

    if (__city_resource_is_mothballed(RESOURCE_LINEN)) {
        b.play_animation = false
        return
    }

    if (b.stored_resource(RESOURCE_LINEN) < building_mortuary.linen_required_for_animation) {
        b.play_animation = false
    }
}
