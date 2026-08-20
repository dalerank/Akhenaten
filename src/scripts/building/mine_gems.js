log_info("akhenaten: building_mine_gems started")

building_mine_gems {
  animations {
    preview { pack:PACK_GENERAL, id:188 },
    base { pack:PACK_GENERAL, id:188 },
    work { pos [54, 15], pack:PACK_SPR_AMBIENT, id:48, max_frames: 16, duration:2, internal_offset:true },
    gems { pos : [93, 0], pack:PACK_GENERAL, id:203 }
  }

  output {
    resource : RESOURCE_GEMS
  }
  progress_max : 200,
  production_rate : 100,
  production_divider : 3,
  building_size : 2,
  meta { text_id:163, help_link:"message_building_gemstone_mine" }
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
  needs {
    rock : true
  }
  flags {
    is_extractor: true
    is_industry: true
    keeps_visitor_paths: true
  }
  cost [ 50, 75, 100, 150, 300 ]
  desirability { value[-12], step[2], step_size[2], range[6] }
  laborers[8]
  fire_risk[0]
  damage_risk[2]
}

[es=(building_mine_gems, on_before_collapse)]
function building_mine_gems_on_before_collapse(ev) {
    if (!game_features.gameplay_change_random_mine_or_pit_collapses_take_money) {
        return
    }
    emit event_finance_request { type: efinance_request_disasters, deben: 250 }
}

[es=(building_mine_gems, draw_usable_paths)]
function building_mine_gems_draw_usable_paths(ev) {
    city.get_building(ev.bid).draw_usable_paths()
}
