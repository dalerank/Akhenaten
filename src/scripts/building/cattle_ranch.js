log_info("akhenaten: building cattle ranch started")

[es=building_industry]
building_cattle_ranch {
  type: BUILDING_CATTLE_RANCH
  animations {
    preview { pack:PACK_GENERAL, id:105, },
    base { pack:PACK_GENERAL, id:105, offset:0 },
    work {  pack:PACK_GENERAL, id:105, offset:1, max_frames:12 },
    minimap { pack:PACK_GENERAL, id:149, offset:160 },
  }
  overlay_anims {
    straw {
      pos:[70, 40]
      pack:PACK_GENERAL
      id:206
      resource: RESOURCE_STRAW
      stack: true
      step: [5, -5]
      max_count: 8
      default_active: true
    }
  }
  min_houses_coverage : 100
  input {
    resource : RESOURCE_STRAW
  }
  output {
    resource : RESOURCE_MEAT
  }
  building_size : 3
  meta { text_id:117, help_link:"message_building_cattle_ranch" }
  info_sound : "Wavs/cowfarm_r.wav"
  sound_channel : SOUND_CHANNEL_CITY_COWFARM
  labor_category : LABOR_CATEGORY_FOOD_PRODUCTION
  cost [ 15, 20, 30, 50, 80 ]
  desirability { value:[-4], step:[1], step_size:[1], range: [4] }
  laborers[12]
  fire_risk[1]
  damage_risk[2]
  info_advisors [ADVISOR_LABOR]
  flags {
    is_food: true
    work_anim: true
    og_production_cycle: true
  }
}

[es=(building_cattle_ranch, update_animation)]
function building_cattle_ranch_on_update_animation(ev) {
    var b = city.get_building(ev.bid)
    if (!b.play_animation) {
        return
    }
    if (b.stored_resource(RESOURCE_STRAW) < 100 || b.worker_percentage < 50) {
        b.play_animation = false
    }
}

[es=(building_cattle_ranch, on_place_checks)]
function building_cattle_ranch_on_place_checks(ev) {
    var grain = city.resources.grain
    var straw = city.resources.straw
    if (grain.count_active_industry > 0 || straw.yards_stored > 0) {
        return
    }
    city.warnings.show("#building_needs_straw")
    if (grain.can_produce) {
        city.warnings.show("#build_grain_farm")
    } else if (straw.can_import) {
        city.warnings.show_if_not(straw.trade_status == TRADE_STATUS_IMPORT, "#overseer_of_commerce_to_import")
    } else if (straw.could_import) {
        city.warnings.show("#setup_trade_route_to_import")
    }
}
