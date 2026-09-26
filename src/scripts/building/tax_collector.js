log_info("akhenaten: building_tax_collector started")

[es=building]
building_tax_collector {
  type: BUILDING_TAX_COLLECTOR
  animations {
    preview { pos: [0, 0], pack:PACK_GENERAL, id:63 }
    base { pos: [0, 0], pack:PACK_GENERAL, id:63 }
    work { pos: [60, -45], pack:PACK_GENERAL, id:63, offset:1, max_frames:11 }
  }
  labor_category : LABOR_CATEGORY_GOVERNMENT
  overlay : OVERLAY_TAX_INCOME
  sound_channel : SOUND_CHANNEL_CITY_TAX_COLLECTOR
  meta { text_id:106, help_link:"message_building_tax_collector" }
  info_sound : "Wavs/taxfarm.wav"
  building_size : 2
  min_houses_coverage : 50
  cost [ 15, 20, 40, 70, 100 ]
  desirability { value:[3], step:[1], step_size:[-1], range: [3] }
  laborers:[6], fire_risk:[4], damage_risk: [3]
  flags {
    is_tax_collector: true
    is_administration: true
    work_anim: true
  }
}

[es=(building_tax_collector, spawn_figure)]
function building_tax_collector_spawn_figure(ev) {
    var b = city.get_building(ev.bid)
    b.common_spawn_roamer(FIGURE_TAX_COLLECTOR, b.params.min_houses_coverage, ACTION_0_TAX_COLLECTOR_CREATED)
}

[es=(building_tax_collector, update_month)]
function building_tax_collector_update_month(ev) {
    if (!game_features.gameplay_change_new_tax_collection_system) {
        return
    }

    var b = city.get_building(ev.bid)
    if (b.has_figure(BUILDING_SLOT_CARTPUSHER)) {
        return
    }

    if (!b.has_road_access || b.deben_storage <= 100) {
        return
    }

    var may_send = Math.floor(b.deben_storage / 100) * 100
    if (may_send > 400) {
        may_send = 400
    }

    var fid = b.create_cartpusher(RESOURCE_GOLD, may_send, ACTION_20_CARTPUSHER_INITIAL, BUILDING_SLOT_CARTPUSHER)
    b.deben_storage -= may_send
    var f = city.get_figure(fid)
    if (f) {
        f.sender_building_id = b.id
    }
}
