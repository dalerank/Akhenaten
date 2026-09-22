log_info("akhenaten: building_village_palace started")

building_village_palace {
  animations {
    preview { pack:PACK_GENERAL, id:47 },
    base { pack:PACK_GENERAL, id:47 },
    work { pos : [24, -20], pack:PACK_GENERAL, id:47, offset:1, max_frames:5, duration:5, can_reverse:true }
    // Optional flat-view sprite (Shift+F). Drawn once on main's draw-tile.
    // Multi-part complexes: parts are skipped when flat is set (provide a full-complex sprite).
    // Single multi-tile buildings (palace): one draw-tile → full footprint sprite is fine.
    // If omitted, city keeps isometric foot.
    // flat { pack:PACK_GENERAL, id:47 }
  }

  labor_category : LABOR_CATEGORY_GOVERNMENT
  planner_update_rule {
    unique_building : true
  }
  meta { text_id:105, help_link:"message_building_palace" }
  info_sound : "Wavs/palace.wav"
  building_size : 4
  needs {
    groundwater : true
  }
  flags {
    is_palace: true
    is_administration: true
    keeps_visitor_paths: true
    work_anim: true
  }
  cost [ 100, 200, 300, 400, 500 ]
  desirability { value:[8], step:[2], step_size:[-2], range: [6] }
  laborers[20]
  fire_risk[4]
  damage_risk [1]
  add_resource_finance [
    { building: BUILDING_GOLD_MINE, request: efinance_request_gold_delivered }
    { building: BUILDING_TAX_COLLECTOR, request: efinance_request_tax_collected }
    { building: BUILDING_TAX_COLLECTOR_UPGRADED, request: efinance_request_tax_collected }
  ]
}

[es=(building_village_palace, update_animation)]
function building_village_palace_on_update_animation(ev) {
    var b = city.get_building(ev.bid)
    b.play_animation = b.worker_percentage > 50
}

[es=(building_village_palace, draw_tooltip)]
function building_village_palace_draw_tooltip(ev) {
    building_palace_show_tooltip(ev)
}

[es=(building_village_palace, draw_usable_paths)]
function building_village_palace_draw_usable_paths(ev) {
    city.get_building(ev.bid).draw_usable_paths()
}
