log_info("akhenaten: building_granite_quarry started")

building_granite_quarry {
  animations {
    preview { pack:PACK_GENERAL, id:38 },
    base { pack:PACK_GENERAL, id:38 },
    work { pos : [54, 15], pack:PACK_SPR_AMBIENT, id:49, max_frames: 16, duration:2 }
  }
  output {
    resource : RESOURCE_GRANITE
  }
  progress_max : 200,
  production_rate : 100,
  building_size : 2,
  meta { text_id:162, help_link:"message_building_stone_quarries" }
  info_sound : "Wavs/marble.wav"
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
  needs {
    rock : true
  }
  flags {
    is_extractor: true
    is_industry: true
    draw_normal_anim: true
    work_anim: true
  }
  cost [ 20, 40, 80, 150, 200 ]
  desirability { value[-6], step[1], step_size[1], range[6] }
  laborers[12]
  fire_risk[0]
  damage_risk[1]
}

[es=(building_granite_quarry, update_production)]
function building_granite_quarry_update_production(ev) {
    industry_mine_deplete_production(
        city.get_building(ev.bid),
        __map_get_granite,
        __map_granite_deplete
    )
}

[es=(building_granite_quarry, produce_uptick_per_day)]
function building_granite_quarry_produce_uptick_per_day(ev) {
    industry_quarry_produce_uptick(city.get_building(ev.bid), __map_get_granite)
}
