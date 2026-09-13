log_info("akhenaten: building_weaver started")

[es=building_industry]
building_weaver = {
  type: BUILDING_WEAVER_WORKSHOP
  animations : {
    preview : { pos: [0, 0], pack:PACK_GENERAL, id:122 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:122 },
    work : { pos : [19, -39], pack:PACK_GENERAL, id:122, offset:1, max_frames:12, duration:4 },
  },
  overlay_anims {
    flax {
      pos : [45, 3]
      pack:PACK_GENERAL
      id:206
      resource: RESOURCE_FLAX
      stack: false
      max_count: 2
      default_active: true
    }
  }
  input : {
    resource : RESOURCE_FLAX
  }
  output : {
    resource : RESOURCE_LINEN
  }
  building_size : 2,
  meta : { text_id:123, help_link:"message_building_weaver" }
  info_sound : "Wavs/flaxfarm.wav"
  sound_channel : SOUND_CHANNEL_CITY_NONE
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE
  cost: [ 16, 30, 50, 100, 150 ]
  desirability : { value:[-3], step:[1], step_size:[1], range: [3] }
  laborers:[12], fire_risk:[4], damage_risk: [3]
  info_advisors [ADVISOR_LABOR]
  flags {
    is_workshop: true
    is_industry: true
    work_anim: true
  }
}

[es=(building_weaver, on_place_checks)]
function building_weaver_on_place_checks(ev) {
    var flax = city.resources.flax
    var has_supply = (flax.count_active_industry > 0) || (flax.yards_stored > 0)
    if (has_supply) {
        return
    }

    city.warnings.show("#building_needs_flax")
    city.warnings.show_if_not(flax.can_produce, "#build_flax_farm")
    city.warnings.show_if_not(flax.can_import, "#setup_trade_route_to_import")
    city.warnings.show_if_not(flax.trade_status == TRADE_STATUS_IMPORT, "#overseer_of_commerce_to_import")
}

[es=(building_weaver, update_animation)]
function building_weaver_on_update_animation(ev) {
    var b = city.get_building(ev.bid)
    if (!b.play_animation) {
        return
    }
    if (__building_industry_progress_pct(b.id) != 0) {
        return
    }
    if (b.stored_resource(RESOURCE_FLAX) < 100) {
        b.play_animation = false
    }
}
