log_info("akhenaten: building_chariots_workshop started")

[es=building_industry]
building_chariots_workshop = {
  type: BUILDING_CHARIOTS_WORKSHOP
  animations : {
    preview : { pack:PACK_GENERAL, id:120 },
    base : { pack:PACK_GENERAL, id:120 },
    work : { pos:[81, -31], pack:PACK_GENERAL, id:120, offset:1, max_frames:11, duration:5 },
  },
  overlay_anims {
    timber {
      pos:[166, -23]
      pack:PACK_GENERAL
      id:202
      resource: RESOURCE_TIMBER
      stack: false
      max_count: 4
      default_active: true
    }

    weapons {
      pos:[136, -8]
      pack:PACK_GENERAL
      id:201
      resource: RESOURCE_WEAPONS
      stack: false
      max_count: 4
      default_active: true
    }
  }
  input : {
    resource : RESOURCE_TIMBER
    resource_second : RESOURCE_WEAPONS
  }
  output : {
    resource : RESOURCE_CHARIOTS
  }
  production_rate : 20,
  production_rate_dcy : [100, 80, 70, 60, 50],
  labor_category : LABOR_CATEGORY_MILITARY,
  meta { text_id:185, help_link:"message_building_weapongsmith_and_chariot_maker" }
  info_sound : "Wavs/chariot.wav"
  sound_channel : SOUND_CHANNEL_CITY_CHARIOTS_WORKSHOP
  building_size : 4,
  cost: [ 50, 200, 250, 300, 375 ]
  desirability : { value:[-6], step:[1], step_size:[1], range: [6] }
  laborers:[30], fire_risk:[4, 15, 20, 24, 30], damage_risk: [0]
  info_advisors [ADVISOR_MILITARY, ADVISOR_TRADE]
  flags {
    is_workshop: true
    is_industry: true
    work_anim: true
  }
}

[es=(building_chariots_workshop, update_animation)]
function building_chariots_workshop_on_update_animation(ev) {
    var b = city.get_building(ev.bid)

    var needs_weapons = !!game_features.gameplay_chariots_workshop_needs_weapons
    b.set_second_material(needs_weapons ? building_chariots_workshop.input.resource_second : RESOURCE_NONE)

    if (!b.play_animation) {
        return
    }
    if (__building_industry_progress_pct(b.id) != 0) {
        return
    }
    if (b.stored_resource(RESOURCE_TIMBER) < 100 || (needs_weapons && b.stored_resource(RESOURCE_WEAPONS) < 100)) {
        b.play_animation = false
    }
}
