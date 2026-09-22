log_info("akhenaten: building_tax_collector_up started")

building_tax_collector_up = {
  animations : {
    preview : { pos: [0, 0], pack:PACK_GENERAL, id:64 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:64 },
    work : { pos : [10, 10], pack:PACK_GENERAL, id:64, offset:1, max_frames:11 }
  },
  labor_category : LABOR_CATEGORY_GOVERNMENT,
  overlay : OVERLAY_TAX_INCOME
  sound_channel : SOUND_CHANNEL_CITY_TAX_COLLECTOR
  meta : { text_id:120, help_link:"message_building_tax_collector" }
  info_sound : "Wavs/taxfarm.wav"
  building_size : 2
  cost: [ 15, 24, 40, 80, 100 ]
  desirability : { value:[3], step:[1], step_size:[-1], range: [3] }
  laborers:[8], fire_risk:[4], damage_risk: [3]
  flags {
    is_tax_collector: true
    is_administration: true
    work_anim: true
  }
}

[es=(building_tax_collector_up, spawn_figure)]
function building_tax_collector_up_spawn_figure(ev) {
    var b = city.get_building(ev.bid)
    b.common_spawn_roamer(FIGURE_TAX_COLLECTOR, b.params.min_houses_coverage, ACTION_0_TAX_COLLECTOR_CREATED)
}

[es=(building_tax_collector_up, update_month)]
function building_tax_collector_up_update_month(ev) {
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
