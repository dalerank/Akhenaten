log_info("akhenaten: building_mine_copper started")

[es=building_industry]
building_mine_copper {
  type: BUILDING_COPPER_MINE
  animations {
    preview { pack:PACK_GENERAL, id:196 },
    base { pack:PACK_GENERAL, id:196 },
    work { pos : [54, 15], pack:PACK_SPR_AMBIENT, id:48, max_frames: 16, duration:2, internal_offset:true }
  },
  overlay_anims {
    copper {
      pos : [93, 0]
      pack:PACK_GENERAL
      id:203
      resource : RESOURCE_COPPER
      default_active : true
    }
  }
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
    work_anim: true
  }
  cost [ 50, 75, 100, 150, 300 ]
  desirability { value[-12], step[2], step_size[2], range[6] }
  laborers[10]
  fire_risk[0]
  damage_risk[2]
}

[es=(building_mine_copper, is_need_flag)]
function building_mine_copper_is_need_flag(ev) {
    if (ev.flag == PLANNER_RULE_ORE) {
        city_planner.need_flag_result = !game_features.gameplay_copper_mine_can_build_near_mountains && ev.result
    }
}

[es=(building_mine_copper, on_before_collapse)]
function building_mine_copper_on_before_collapse(ev) {
    if (!game_features.gameplay_change_random_mine_or_pit_collapses_take_money) {
        return
    }
    emit event_finance_request { type: efinance_request_disasters, deben: 250 }
}

[es=(building_mine_copper, update_production)]
function building_mine_copper_update_production(ev) {
    industry_mine_deplete_production(
        city.get_building(ev.bid),
        __map_get_copper,
        __map_copper_deplete
    )
}

[es=(building_mine_copper, produce_uptick_per_day)]
function building_mine_copper_produce_uptick_per_day(ev) {
    var b = city.get_building(ev.bid)
    if (b.num_workers <= 0) {
        b.produce_uptick = 0
        return
    }

    var production = Math.floor(b.num_workers / 2)
    b.produce_uptick = production < 1 ? 1 : production
    industry_mine_require_ore_for_uptick(b, __map_get_copper)
}

[es=(building_mine_copper, draw_usable_paths)]
function building_mine_copper_draw_usable_paths(ev) {
    city.get_building(ev.bid).draw_usable_paths()
}
