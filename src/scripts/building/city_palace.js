log_info("akhenaten: building_city_palace started")

building_city_palace {
  animations {
    preview { pack:PACK_GENERAL, id:18 },
    base { pack:PACK_GENERAL, id:18 },
    work { pos : [-1, -1], pack:PACK_GENERAL, id:18, offset:1, max_frames:12 }
  }

  labor_category : LABOR_CATEGORY_GOVERNMENT

  planner_update_rule {
    unique_building : true
  }

  meta { text_id:105, help_link:"message_building_palace" }
  info_sound : "Wavs/palace.wav"
  building_size : 6

  needs {
    groundwater : true
  }

  flags {
    is_palace: true
    is_administration: true
    keeps_visitor_paths: true
    work_anim: true
  }

  cost [ 300, 400, 500, 800, 1000 ]
  add_resource_finance [
    { building: BUILDING_GOLD_MINE, request: efinance_request_gold_delivered }
    { building: BUILDING_TAX_COLLECTOR, request: efinance_request_tax_collected }
    { building: BUILDING_TAX_COLLECTOR_UPGRADED, request: efinance_request_tax_collected }
  ]
}

[es=(building_city_palace, update_animation)]
function building_city_palace_on_update_animation(ev) {
    var b = city.get_building(ev.bid)
    b.play_animation = b.worker_percentage > 50
}

[es=(building_city_palace, draw_tooltip)]
function building_city_palace_draw_tooltip(ev) {
    building_palace_show_tooltip(ev)
}

[es=(building_city_palace, draw_usable_paths)]
function building_city_palace_draw_usable_paths(ev) {
    city.get_building(ev.bid).draw_usable_paths()
}
