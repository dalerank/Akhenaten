log_info("akhenaten: building_bullfight_school started")

[es=building_entertainment]
building_bullfight_school = {
  type: BUILDING_BULLFIGHT_SCHOOL
  animations : {
    preview : { pack:PACK_CUSTOM, id:0 },
    base : { pack:PACK_CUSTOM, id:0 },
  }
  overlay_anims {
    straw {
      pos : [65, 3]
      pack:PACK_GENERAL
      id:206
      resource : RESOURCE_STRAW
      stack : true
      step : [5, -5]
      max_count : 8
      default_active : true
    }
  }
  meta : { text_id:78, help_link:"message_building_trading_centers" }
  info_sound : "Wavs/bullfight_school.wav"
  building_size : 2
  cost: [ 50, 80, 100, 150, 200 ]
  desirability : { value:[-3], step:[1], step_size:[1], range: [3] }
  laborers:[15], fire_risk:[4], damage_risk: [3]
  flags {
    is_entertainment: true
  }
}
