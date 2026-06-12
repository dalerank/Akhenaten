log_info("akhenaten: overlay senet house started")

[es=city_overlay]
overlay_senet_house {
  id:OVERLAY_SENET_HOUSE
  title: "#overlay_senet_house"
  walkers:[FIGURE_SENET_PLAYER]
  buildings:[BUILDING_BULLFIGHT_SCHOOL, BUILDING_SENET_HOUSE, BUILDING_ROADBLOCK]
  column_type: COLUMN_TYPE_WATER_ACCESS
  column_anim: {pack:PACK_GENERAL, id:103}
}

[es=(overlay_senet_house, get_tooltip_for_building)]
function senet_house_building_tooltip(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_tooltip = "#senet_access_low"
        return
    }

    var senet = house.senet_player
    if (senet <= 0) {
        city.overlay_tooltip = "#senet_access_none"
    } else if (senet >= 80) {
        city.overlay_tooltip = "#senet_access_high"
    } else if (senet >= 20) {
        city.overlay_tooltip = "#senet_access_medium"
    } else {
        city.overlay_tooltip = "#senet_access_low"
    }
}

[es=(overlay_senet_house, get_column_height)]
function senet_house_building_column_height(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_column_height = -1
        return
    }

    if (house.population <= 0) {
        city.overlay_column_height = -1
        return
    }

    city.overlay_column_height = house.senet_player / 10
}
