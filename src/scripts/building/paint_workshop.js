log_info("akhenaten: building_paint_workshop started")

[es=building_industry]
building_paint_workshop {
  type: BUILDING_PAINT_WORKSHOP
  animations {
    preview { pack:PACK_EXPANSION, id:27 }
    base { pack:PACK_EXPANSION, id:27 }
    work { pos [17, -14], pack:PACK_EXPANSION, id:27, offset:1, max_frames:10, duration:4 }
  }
  overlay_anims {
    henna {
      pos:[65, 3]
      pack:PACK_GENERAL
      id:207
      resource: RESOURCE_HENNA
      stack: true
      step: [5, -5]
      max_count: 8
      default_active: true
    }
  }
  input {
    resource : RESOURCE_HENNA
  }
  output {
    resource : RESOURCE_PAINT
  }
  progress_max : 400
  production_rate : 20
  production_rate_dcy : [100, 80, 70, 60, 50]
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE
  building_size : 2
  cost [ 20, 30, 50, 100, 150 ]
  desirability { value[-4], step[1], step_size[1], range[4] }
  laborers [12]
  fire_risk [3]
  damage_risk [1]
  meta { text_id: 313, help_link:"message_mission_paint_maker" }
  info_sound : "Wavs/farm2.wav"
  info_advisors [ADVISOR_LABOR]
  flags {
    is_workshop: true
    is_industry: true
    work_anim: true
  }
}

[es=(building_paint_workshop, on_place_checks)]
function building_paint_workshop_on_place_checks(ev) {
    var henna = city.resources.henna
    var has_supply = (henna.count_active_industry > 0) || (henna.yards_stored > 0)
    if (has_supply) {
        return
    }

    city.warnings.show("#building_needs_henna")
    city.warnings.show_if_not(henna.can_produce, "#build_henna_farm")
    city.warnings.show_if_not(henna.can_import, "#import_henna_trade_route")
    city.warnings.show_if_not(henna.trade_status == TRADE_STATUS_IMPORT, "#import_henna_overseer")
}

[es=(building_paint_workshop, update_animation)]
function building_paint_workshop_on_update_animation(ev) {
    var b = city.get_building(ev.bid)
    if (!b.play_animation) {
        return
    }
    if (__building_industry_progress_pct(b.id) != 0) {
        return
    }
    if (b.stored_resource(RESOURCE_HENNA) < 100) {
        b.play_animation = false
    }
}
