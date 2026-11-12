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
      pos:[45, 25]
      pack:PACK_EXPANSION
      id:30
      resource: RESOURCE_HENNA
      stack: false
      max_count: 1
      default_active: true
    }
  }
  input {
    resource : RESOURCE_HENNA
  }
  output {
    resource : RESOURCE_PAINT
  }
  min_houses_coverage : 50
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE
  building_size : 2
  cost [ 20, 80, 100, 120, 150 ]
  desirability { value[-4], step[1], step_size[1], range[4] }
  laborers [12]
  fire_risk [3]
  damage_risk [1]
  meta { text_id: 313, help_link:"message_mission_paint_maker" }
  info_sound : "Wavs/paintmaker_r.wav"
  sound_channel : SOUND_CHANNEL_CITY_PAINT_WORKSHOP
  info_advisors [ADVISOR_LABOR]
  flags {
    is_workshop: true
    is_industry: true
    work_anim: true
    og_production_cycle: true
  }
}

[es=(building_paint_workshop, on_place_checks)]
function building_paint_workshop_on_place_checks(ev) {
    var henna = city.resources.henna
    var paint = city.resources.paint
    var has_supply = (henna.count_active_industry > 0) || (paint.yards_stored > 0) || (henna.yards_stored > 0)
    if (has_supply) {
        return
    }

    city.warnings.show("#building_needs_henna")
    if (henna.can_produce) {
        city.warnings.show("#build_henna_farm")
    } else if (!henna.can_import) {
        city.warnings.show("#import_henna_trade_route")
    } else if (henna.trade_status != TRADE_STATUS_IMPORT && henna.trade_status != TRADE_STATUS_IMPORT_AS_NEEDED) {
        city.warnings.show("#import_henna_overseer")
    }
}

[es=(building_paint_workshop, update_animation)]
function building_paint_workshop_on_update_animation(ev) {
    var b = city.get_building(ev.bid)
    if (b.play_animation && b.stored_resource(RESOURCE_HENNA) <= 0) {
        b.play_animation = false
    }
}
