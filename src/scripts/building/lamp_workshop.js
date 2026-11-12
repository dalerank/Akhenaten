log_info("akhenaten: building_lamp_workshop started")

[es=building_industry]
building_lamp_workshop {
  type: BUILDING_LAMP_WORKSHOP
  animations {
    preview { pack:PACK_EXPANSION, id:26 }
    base { pack:PACK_EXPANSION, id:26 }
    work { pos [10, -11], pack:PACK_EXPANSION, id:26, offset:1, max_frames:9, duration:6, can_reverse:true }
  }
  // OG draw_workshop_raw_material_storage: one pile per input, the bigger one from 200 in stock.
  overlay_anims {
    pottery {
      pos:[50, 20]
      pack:PACK_EXPANSION
      id:28
      resource: RESOURCE_POTTERY
      stack: false
      max_count: 1
      default_active: true
    }
    oil {
      pos:[15, 8]
      pack:PACK_EXPANSION
      id:29
      resource: RESOURCE_OIL
      stack: false
      max_count: 1
      default_active: true
    }
  }
  input {
    resource : RESOURCE_OIL
    resource_second : RESOURCE_POTTERY
  }
  output {
    resource : RESOURCE_LAMPS
  }
  min_houses_coverage : 50
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE
  building_size : 2
  cost [ 20, 80, 100, 120, 150 ]
  desirability { value[-4], step[1], step_size[1], range[4] }
  laborers [12]
  fire_risk [4, 15, 20, 24, 30]
  damage_risk [0]
  meta { text_id: 314, help_link:"message_building_lamp_maker" }
  info_sound : "Wavs/lampmaker_r.wav"
  sound_channel : SOUND_CHANNEL_CITY_LAMP_WORKSHOP
  info_advisors [ADVISOR_LABOR]
  flags {
    is_workshop: true
    is_industry: true
    work_anim: true
    og_production_cycle: true
  }
}

function building_lamp_workshop_imported(res) {
    return res.trade_status == TRADE_STATUS_IMPORT || res.trade_status == TRADE_STATUS_IMPORT_AS_NEEDED
}

function building_lamp_workshop_hint_import(res, no_route, not_imported) {
    if (!res.can_import) {
        city.warnings.show(no_route)
    } else if (!building_lamp_workshop_imported(res)) {
        city.warnings.show(not_imported)
    }
}

function building_lamp_workshop_hint_pottery(no_route, not_imported) {
    var pottery = city.resources.pottery
    if (pottery.can_produce) {
        city.warnings.show("#build_potter")
        return
    }
    building_lamp_workshop_hint_import(pottery, no_route, not_imported)
}

// construction_warning_check_lamps. With both inputs missing OG swaps the oil hints:
// no trade route shows the overseer text and a route without import shows the trade route text.
[es=(building_lamp_workshop, on_place_checks)]
function building_lamp_workshop_on_place_checks(ev) {
    if (game.editor_is_active()) {
        return
    }
    var oil = city.resources.oil
    var pottery = city.resources.pottery
    var oil_active = oil.count_active_industry
    var pottery_active = pottery.count_active_industry
    if (oil_active > 0 && pottery_active > 0) {
        return
    }
    if (city.resources.lamps.yards_stored > 0) {
        return
    }
    var oil_stock = oil.yards_stored
    var pottery_stock = pottery.yards_stored
    if (oil_stock > 0 && pottery_stock > 0) {
        return
    }
    if (oil_active <= 0 && oil_stock <= 0) {
        if (pottery_active <= 0 && pottery_stock <= 0) {
            city.warnings.show("#building_needs_oil_and_pottery")
            building_lamp_workshop_hint_import(oil, "#import_oil_overseer", "#import_oil_trade_route")
            building_lamp_workshop_hint_pottery("#import_pottery_overseer", "#import_pottery_trade_route")
            return
        }
        city.warnings.show("#building_needs_oil")
        building_lamp_workshop_hint_import(oil, "#setup_trade_route_to_import", "#overseer_of_commerce_to_import")
        return
    }
    if (pottery_active > 0 || pottery_stock > 0) {
        return
    }
    city.warnings.show("#building_needs_pottery")
    building_lamp_workshop_hint_pottery("#setup_trade_route_to_import", "#overseer_of_commerce_to_import")
}

// OG building_animation_offset: the lamp maker animates while staffed with any oil and any pottery in stock.
[es=(building_lamp_workshop, update_animation)]
function building_lamp_workshop_on_update_animation(ev) {
    var b = city.get_building(ev.bid)
    if (!b.play_animation) {
        return
    }
    if (b.stored_resource(RESOURCE_OIL) <= 0 || b.stored_resource(RESOURCE_POTTERY) <= 0) {
        b.play_animation = false
    }
}
