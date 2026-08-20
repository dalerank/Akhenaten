log_info("akhenaten: building_mine_copper started")

building_mine_copper {
  animations {
    preview { pack:PACK_GENERAL, id:196 },
    base { pack:PACK_GENERAL, id:196 },
    work { pos : [54, 15], pack:PACK_SPR_AMBIENT, id:48, max_frames: 16, duration:2, internal_offset:true }
  },
  output {
    resource : RESOURCE_COPPER
  }
  progress_max : 200,
  production_rate : 100,
  meta { text_id:193, help_link:"message_building_gold_copper_mine" }
  info_sound : "Wavs/gold.wav"
  building_size : 2,
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE,
  needs {
    rock : true
    ore : true
  }
  flags {
    is_extractor: true
    is_industry: true
    keeps_visitor_paths: true
  }
  cost [ 50, 75, 100, 150, 300 ]
  desirability { value[-12], step[2], step_size[2], range[6] }
  laborers[10]
  fire_risk[0]
  damage_risk[2]
}

[es=(building_mine_copper, on_before_collapse)]
function building_mine_copper_on_before_collapse(ev) {
    if (!game_features.gameplay_change_random_mine_or_pit_collapses_take_money) {
        return
    }
    emit event_finance_request { type: efinance_request_disasters, deben: 250 }
}

[es=(building_mine_copper, draw_usable_paths)]
function building_mine_copper_draw_usable_paths(ev) {
    city.get_building(ev.bid).draw_usable_paths()
}
