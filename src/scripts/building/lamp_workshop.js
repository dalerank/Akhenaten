log_info("akhenaten: building_lamp_workshop started")

[es=building_industry]
building_lamp_workshop {
  type: BUILDING_LAMP_WORKSHOP
  animations {
    preview { pack:PACK_EXPANSION, id:26 }
    base { pack:PACK_EXPANSION, id:26 }
    work { pos [10, -14], pack:PACK_EXPANSION, id:26, offset:1, max_frames:10, duration:4 }
  }
  overlay_anims {
    oil {
      pos:[46, 25]
      pack:PACK_GENERAL
      id:208
      resource: RESOURCE_OIL
      stack: true
      step: [5, -5]
      max_count: 8
      default_active: true
    }
    pottery {
      pos:[51, 18]
      pack:PACK_GENERAL
      id:207
      resource: RESOURCE_POTTERY
      stack: true
      step: [5, -5]
      max_count: 8
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
  progress_max : 400
  production_rate : 20
  production_rate_dcy : [100, 80, 70, 60, 50]
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE
  building_size : 2
  cost [ 20, 30, 50, 100, 150 ]
  desirability { value[-4], step[1], step_size[1], range[4] }
  laborers [12]
  fire_risk [4]
  damage_risk [3]
  meta { text_id: 314, help_link:"message_building_lamp_maker" }
  info_sound : "Wavs/pottery.wav"
  info_advisors [ADVISOR_LABOR]
  flags {
    is_workshop: true
    is_industry: true
    work_anim: true
  }
}

[es=(building_lamp_workshop, on_place_checks)]
function building_lamp_workshop_on_place_checks(ev) {
    var oil = city.resources.oil
    var pottery = city.resources.pottery
    var has_oil = (oil.yards_stored > 0) || (oil.count_active_industry > 0)
    var has_pottery = (pottery.yards_stored > 0) || (pottery.count_active_industry > 0)
    if (has_oil && has_pottery) {
        return
    }

    city.warnings.show("#building_needs_oil_and_pottery")
    if (!has_pottery) {
        city.warnings.show_if_not(pottery.can_produce, "#build_potter")
        city.warnings.show_if_not(pottery.can_import, "#import_pottery_trade_route")
        city.warnings.show_if_not(pottery.trade_status == TRADE_STATUS_IMPORT, "#import_pottery_overseer")
    }
    if (!has_oil) {
        city.warnings.show_if_not(oil.can_import, "#import_oil_trade_route")
        city.warnings.show_if_not(oil.trade_status == TRADE_STATUS_IMPORT, "#import_oil_overseer")
    }
}

[es=(building_lamp_workshop, update_animation)]
function building_lamp_workshop_on_update_animation(ev) {
    var b = city.get_building(ev.bid)
    if (!b.play_animation) {
        return
    }
    if (__building_industry_progress_pct(b.id) != 0) {
        return
    }
    if (b.stored_resource(RESOURCE_OIL) < 100 || b.stored_resource(RESOURCE_POTTERY) < 100) {
        b.play_animation = false
    }
}
