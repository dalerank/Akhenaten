log_info("akhenaten: building_mine_gold started")

[es=building_mine]
building_mine_gold {
  type: BUILDING_GOLD_MINE
  animations {
    _pack { pack:PACK_GENERAL }
    preview { id:185 }
    base { id:185 }
    work { pos [54, 15], pack:PACK_SPR_AMBIENT, internal_offset:true, id:48, max_frames: 16, duration:2 }
  }
  output {
    resource : RESOURCE_GOLD
  }
  building_size : 2
  meta { text_id:162, help_link:"message_building_gold_copper_mine" }
  info_sound : "Wavs/gold.wav"
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE
  needs {
    rock : true
    ore : true
  }
  flags {
    is_extractor: true
    is_industry: true
    keeps_visitor_paths: true
    draw_normal_anim: true
    work_anim: true
  }
  cost [ 50, 100, 150, 250, 400 ]
  desirability { value[-16], step[2], step_size[3], range[6] }
  laborers [12]
  fire_risk [0]
  damage_risk [2]
  progress_max : 200
  production_rate : 100
}

[es=(building_mine_gold, on_before_collapse)]
function building_mine_gold_on_before_collapse(ev) {
    if (!game_features.gameplay_change_random_mine_or_pit_collapses_take_money) {
        return
    }
    emit event_finance_request { type: efinance_request_disasters, deben: 250 }
}

[es=(building_mine_gold, update_production)]
function building_mine_gold_update_production(ev) {
    industry_mine_update_production_deplete(
        city.get_building(ev.bid),
        __map_get_golden,
        __map_golden_deplete
    )
}

[es=(building_mine_gold, produce_uptick_per_day)]
function building_mine_gold_produce_uptick_per_day(ev) {
    var b = city.get_building(ev.bid)
    if (b.num_workers <= 0) {
        b.produce_uptick = 0
        return
    }

    var divider = 10
    if (game_features.gameplay_change_goldmine_twice_production) {
        divider = Math.floor(divider / 2)
        if (divider < 1) {
            divider = 1
        }
    }

    var production = Math.floor(b.num_workers / divider)
    b.produce_uptick = production < 1 ? 1 : production
}

[es=(building_mine_gold, draw_usable_paths)]
function building_mine_gold_draw_usable_paths(ev) {
    city.get_building(ev.bid).draw_usable_paths()
}
