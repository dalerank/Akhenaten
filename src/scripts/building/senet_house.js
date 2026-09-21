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

[es=(building_senet_house, on_place_checks)]
function building_senet_house_on_place_checks(ev) {
  var has_senet_master = city.count_active_buildings(BUILDING_BULLFIGHT_SCHOOL) > 0
  var beer = city.resources.beer
  var is_import_beer = beer.trade_status == TRADE_STATUS_IMPORT

  city.warnings.show_if_not(has_senet_master, "#build_senet_master")
  city.warnings.show_if_not(beer.yards_stored > 0, "#need_beer")
  city.warnings.show_if_not(beer.count_active_industry > 0, "#need_brewery")
  city.warnings.show_if_not(beer.can_produce, "#build_brewery")
  city.warnings.show_if_not(beer.can_import, "#import_beer_overseer")
  city.warnings.show_if_not(is_import_beer, "#import_beer_trade_route")
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

  if (building.common_spawn_roamer(FIGURE_SENET_PLAYER, 100, ACTION_4_ENTERTAINER_ROAMING)) {
    return
  }

  if (building.stored_resource(RESOURCE_BEER) <= 0) {
    return
  }

  if (!building.common_spawn_figure_trigger(100, BUILDING_SLOT_DRUNKARD)) {
    return
  }

  var beer = building.stored_resource(RESOURCE_BEER)
  var spent = beer < 20 ? beer : 20
  building.consume_resource(RESOURCE_BEER, spent)
  __building_create_roaming_figure(ev.bid, FIGURE_DRUNKARD, 14, BUILDING_SLOT_DRUNKARD)
}
