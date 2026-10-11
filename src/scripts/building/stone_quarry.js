log_info("akhenaten: building_stone_quarry started")

[es=building_industry]
building_stone_quarry {
  type: BUILDING_STONE_QUARRY
  animations {
    preview { pack:PACK_GENERAL, id:187 },
    base { pack:PACK_GENERAL, id:187 },
    work { pos : [84, 15], pack:PACK_SPR_AMBIENT, id:49, max_frames: 6, duration:3, internal_offset:true }
    work_2 { pos : [44, 20], pack:PACK_SPR_AMBIENT, id:49, offset:7, max_frames: 6, duration:3, internal_offset:true }
  }
  output {
    resource : RESOURCE_STONE
  }
  progress_max : 200,
  production_rate : 100,
  building_size : 2,
  meta { text_id:118, help_link:"message_building_stone_quarries" }
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
  needs {
    rock : true
  }

  flags {
    is_extractor: true
    is_industry: true
    work_anim: true
  }

  cost [ 15, 30, 50, 80, 150 ]
  desirability { value[-6], step[1], step_size[1], range[6] }
  laborers[12]
  fire_risk[0]
  damage_risk[2]
}

[es=(building_stone_quarry, update_production)]
function building_stone_quarry_update_production(ev) {
    industry_mine_deplete_production(
        city.get_building(ev.bid),
        __map_get_stone,
        __map_stone_deplete
    )
}

[es=(building_stone_quarry, produce_uptick_per_day)]
function building_stone_quarry_produce_uptick_per_day(ev) {
    industry_quarry_produce_uptick(city.get_building(ev.bid), __map_get_stone)
}

[es=(building_stone_quarry, update_day)]
function building_stone_quarry_update_day(ev) {
    var b = city.get_building(ev.bid)
    var animkey = b.worker_percentage > 50 ? "work_2" : "none"
    b.set_slot_animation(0, animkey)
}
