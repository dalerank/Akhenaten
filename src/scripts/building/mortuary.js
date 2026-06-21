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
    linen { pos : [45, 3], pack:PACK_GENERAL, id:206 },
  }

  input : {
    resource : RESOURCE_LINEN
  }
  max_serve_clients : 1000
  linen_required_for_spawn : 20
  linen_required_for_animation : 100
  monthly_linen_consumption : 20
  min_houses_coverage : 50
  building_size : 2
  labor_category : LABOR_CATEGORY_WATER_HEALTH
  meta { help_id:66, text_id:82 }
  info_sound : "Wavs/mortuary.wav"
  cost [ 20, 30, 50, 100, 200 ]
  desirability { value[-3], step[2], step_size[1], range[2] }
  laborers[8]
  fire_risk[4]
  damage_risk[2]
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
