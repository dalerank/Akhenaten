log_info("akhenaten: building_senet_house started")

[es=building_entertainment]
building_senet_house = {
  type: BUILDING_SENET_HOUSE
  animations : {
    preview : { pack:PACK_GENERAL, id:17 },
    base : { pack:PACK_GENERAL, id:17 },
    work : { pos:[30, -35], pack:PACK_GENERAL, id:17, offset:1, max_frames:18, duration:5 },
  }
  overlay_anims {
    beer {
      pos : [65, 3]
      pack:PACK_GENERAL
      id:198
      resource : RESOURCE_BEER
      stack : true
      step : [5, -5]
      max_count : 8
      default_active : true
    }
  }
  input : {
    resource : RESOURCE_BEER
  }
  meta : { text_id:73, help_link:"message_building_senet_house" }
  building_size : 4
  labor_category : LABOR_CATEGORY_ENTERTAINMENT
  sound_channel : SOUND_CHANNEL_CITY_SENET_HOUSE
  cost : [ 300, 400, 500, 700, 1000 ]
  desirability : { value:[-6], step:[1], step_size:[2], range: [3] }
  crime : { value:[5], step:[1], step_size:[1], range: [3] }
  laborers:[25], fire_risk:[1], damage_risk: [1]
  flags {
    is_entertainment: true
    work_anim: true
  }
}

// OG senet-house beer per walker trip (Heaven entertainment notes).
function building_senet_house_beer_per_trip() {
  var amounts = [5, 10, 20, 40, 60]
  var i = game.difficulty
  if (i < 0) {
    i = 0
  }
  if (i >= amounts.length) {
    i = amounts.length - 1
  }
  return amounts[i]
}

[es=(building_senet_house, add_resource)]
function building_senet_house_add_resource(ev) {
  if (ev.resource != RESOURCE_BEER) {
    return
  }
  var building = city.get_building(ev.bid)
  building.store_resource(ev.resource, ev.amount)
}

[es=(building_senet_house, spawn_figure)]
function building_senet_house_spawn_figure(ev) {
  var building = city.get_building(ev.bid)
  var need = building_senet_house_beer_per_trip()
  var beer = building.stored_resource(RESOURCE_BEER)

  // OG: beer funds each senet-player trip (amount by difficulty).
  if (beer >= need) {
    if (building.common_spawn_figure_trigger(100, BUILDING_SLOT_SERVICE)) {
      building.consume_resource(RESOURCE_BEER, need)
      // Roamers do not hit update_shows(); mark plays active like zoo feed consume.
      var ent = city.get_entertainment_building(ev.bid)
      if (ent) {
        ent.juggler_visited = 32
      }
      building.create_roaming_figure(FIGURE_SENET_PLAYER, ACTION_4_ENTERTAINER_ROAMING, BUILDING_SLOT_SERVICE)
      return
    }
  }

  // Remake flavor drunkard: no extra beer drain (OG has no drunkard figure).
  if (beer <= 0) {
    return
  }

  if (!building.common_spawn_figure_trigger(100, BUILDING_SLOT_DRUNKARD)) {
    return
  }

  __building_create_roaming_figure(ev.bid, FIGURE_DRUNKARD, 14, BUILDING_SLOT_DRUNKARD)
}
