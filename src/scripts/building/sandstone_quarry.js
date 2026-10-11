log_info("akhenaten: building_sandstone_quarry started")

[es=building_industry]
building_sandstone_quarry {
  type: BUILDING_SANDSTONE_QUARRY
  animations {
    preview { pack:PACK_GENERAL, id:197 },
    base { pack:PACK_GENERAL, id:197 },
    work { pos : [54, 15], pack:PACK_SPR_AMBIENT, id:49, max_frames: 16, duration:2 }
  }
  output {
    resource : RESOURCE_SANDSTONE
  }
  progress_max : 200,
  production_rate : 100,
  building_size : 2,
  meta { text_id:162, help_link:"message_building_stone_quarries" }
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
  cost [ 15, 30, 50, 80, 150 ]
  desirability { value[-6], step[1], step_size[1], range[6] }
  laborers[12]
  fire_risk[0]
  damage_risk[1]
}

[es=(building_sandstone_quarry, update_production)]
function building_sandstone_quarry_update_production(ev) {
    industry_mine_deplete_production(
        city.get_building(ev.bid),
        __map_get_sandstone,
        __map_sandstone_deplete
    )
}

[es=(building_sandstone_quarry, produce_uptick_per_day)]
function building_sandstone_quarry_produce_uptick_per_day(ev) {
    industry_quarry_produce_uptick(city.get_building(ev.bid), __map_get_sandstone)
}
