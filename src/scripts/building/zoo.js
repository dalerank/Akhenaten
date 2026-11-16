log_info("akhenaten: building_zoo started")

building_zoo {
  animations {
    // Dump: base frame 358×218 → isometric_size (360/60)=6. Ref: tmp/zoo_sprite/base_frame.png
    // Work frames = pack offsets 1+ (animals/water); count not in single export — verify in-game.
    preview : { pack:PACK_EXPANSION, id:6 },
    base : { pack:PACK_EXPANSION, id:6 },
    work : { pack:PACK_EXPANSION, id:6, offset:1, max_frames:19, can_reverse:true, duration:3 },
  }
  overlay_anims {
    // Stack icons near courtyard pots (SE of main building / by water cage)
    gamemeat {
      pos:[90, 70]
      pack:PACK_GENERAL
      id:205
      resource: RESOURCE_GAMEMEAT
      stack: true
      step: [5, -5]
      max_count: 8
      default_active: true
    }
    straw {
      pos:[100, 78]
      pack:PACK_GENERAL
      id:206
      resource: RESOURCE_STRAW
      stack: true
      step: [5, -5]
      max_count: 8
      default_active: true
    }
  }
  input : {
    resource : RESOURCE_GAMEMEAT
    resource_second : RESOURCE_STRAW
  }
  meta : { text_id:308, help_link:"message_building_zoo" }
  building_size : 6
  labor_category : LABOR_CATEGORY_ENTERTAINMENT
  cost : [ 500, 1500, 2000, 2200, 2600 ]
  // Pharaoh_Model_*.txt row 226: des -6/1/2/3, fire and damage 5 (7 on impossible).
  desirability : { value:[-6], step:[1], step_size:[2], range: [3] }
  laborers:[30], fire_risk:[5, 5, 5, 5, 7], damage_risk: [5, 5, 5, 5, 7]
  min_houses_coverage : 51
  sound_channel : SOUND_CHANNEL_CITY_ZOO
  flags {
    is_entertainment: true
  }
}

function building_zoo_trade_is_import(res) {
  return res.trade_status == TRADE_STATUS_IMPORT || res.trade_status == TRADE_STATUS_IMPORT_AS_NEEDED
}

function building_zoo_hint_import(res, no_route, not_imported) {
  if (!res.can_import) {
    city.warnings.show(no_route)
  } else if (!building_zoo_trade_is_import(res)) {
    city.warnings.show(not_imported)
  }
}

function building_zoo_hint_straw() {
  var grain = city.resources.grain
  var straw = city.resources.straw
  if (grain.can_produce) {
    city.warnings.show("#build_grain_farm")
    return
  }
  building_zoo_hint_import(straw, "#import_straw_trade_route", "#import_straw_overseer")
}

[es=(building_zoo, on_place_checks)]
function building_zoo_on_place_checks(ev) {
  if (game.editor_is_active()) {
    return
  }
  // construction_warning_check_zoo. Game meat in the yards, or any hunting lodge, ends the check.
  var meat = city.resources.gamemeat
  if (meat.yards_stored > 0) {
    return
  }
  city.warnings.show("#building_needs_game_meat")
  if (meat.count_total_industry > 0) {
    return
  }
  if (meat.can_produce || meat.could_import) {
    if (!meat.could_import) {
      city.warnings.show("#build_hunting_lodge")
    } else if (!meat.can_import) {
      city.warnings.show("#game_meat_import_trade_route")
    } else if (!building_zoo_trade_is_import(city.resources.meat)) {
      // The import test is meat, not game meat.
      city.warnings.show("#build_hunting_lodge_or_import")
    }
  }
  var grain = city.resources.grain
  var straw = city.resources.straw
  if (grain.count_active_industry > 0 || straw.yards_stored > 0) {
    return
  }
  city.warnings.show("#building_needs_straw")
  building_zoo_hint_straw()
}

// OG spawn_zoo: delays 7/15/30/50/80, walker_cost of game meat AND straw (model row 226).
function building_zoo_feed_cost() {
  return dcy_get([20, 20, 20, 40, 60])
}

[es=(building_zoo, spawn_figure)]
function building_zoo_spawn_figure(ev) {
  var building = city.get_building(ev.bid)
  if (!building) {
    return
  }

  building.check_labor_problem()
  if (building.has_figure(BUILDING_SLOT_SERVICE) || !building.has_road_access) {
    return
  }

  building.common_spawn_labor_seeker(building_zoo.min_houses_coverage)
  if (building.worker_percentage <= 0) {
    return
  }

  var delays = [7, 15, 30, 50, 80]
  building.figure_spawn_delay = (building.figure_spawn_delay + 1) & 0xff
  if (building.figure_spawn_delay <= building.spawn_delay_by_workers(delays)) {
    return
  }

  var cost = building_zoo_feed_cost()
  if (building.stored_resource(RESOURCE_GAMEMEAT) < cost || building.stored_resource(RESOURCE_STRAW) < cost) {
    return
  }

  building.consume_resource(RESOURCE_GAMEMEAT, cost)
  building.consume_resource(RESOURCE_STRAW, cost)
  building.figure_spawn_delay = 0
  building.create_roaming_figure(FIGURE_ZOOKEEPER, ACTION_4_ENTERTAINER_ROAMING, BUILDING_SLOT_SERVICE)
}

[es=(building_zoo, update_day)]
function building_zoo_update_day(ev) {
  var zoo = city.get_entertainment_building(ev.bid)
  if (!zoo) {
    return
  }
  zoo.num_shows = 0
  if (zoo.juggler_visited > 0) {
    zoo.juggler_visited = zoo.juggler_visited - 1
    zoo.num_shows = zoo.num_shows + 1
  }
}

[es=(building_zoo, update_graphic)]
function building_zoo_update_graphic(ev) {
  var zoo = city.get_entertainment_building(ev.bid)
  var building = city.get_building(ev.bid)
  if (!zoo || !building) {
    return
  }
  // OG animation_offset: workers and both input stocks, otherwise the cages stay still.
  var fed = building.stored_resource(RESOURCE_GAMEMEAT) > 0 && building.stored_resource(RESOURCE_STRAW) > 0
  var animkey = (building.play_animation && fed) ? "work" : "none"
  zoo.set_animation(animkey)
}
