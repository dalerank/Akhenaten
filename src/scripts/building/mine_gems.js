log_info("akhenaten: building_mine_gems started")

[es=building_mine]
building_mine_gems {
  type: BUILDING_GEMSTONE_MINE
  animations {
    preview { pack:PACK_GENERAL, id:188 },
    base { pack:PACK_GENERAL, id:188 },
    work { pos [54, 15], pack:PACK_SPR_AMBIENT, id:48, max_frames: 16, duration:2, internal_offset:true },
  }
  overlay_anims {
    gems {
      pos : [93, 0]
      pack:PACK_GENERAL
      id:203
      resource : RESOURCE_GEMS
      default_active : true
    }
  }

  output {
    resource : RESOURCE_GEMS
  }
  progress_max : 200,
  production_rate : 100,
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
    work_anim: true
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

[es=(building_mine_gems, update_production)]
function building_mine_gems_update_production(ev) {
    industry_mine_update_production_deplete(
        city.get_building(ev.bid),
        __map_get_gems,
        __map_gems_deplete
    )
}

[es=(building_mine_gems, produce_uptick_per_day)]
function building_mine_gems_produce_uptick_per_day(ev) {
    var b = city.get_building(ev.bid)
    if (b.num_workers <= 0) {
        b.produce_uptick = 0
        return
    }

    var production = Math.floor(b.num_workers / 3)
    b.produce_uptick = production < 1 ? 1 : production
}

[es=(building_mine_gems, draw_usable_paths)]
function building_mine_gems_draw_usable_paths(ev) {
    city.get_building(ev.bid).draw_usable_paths()
}
