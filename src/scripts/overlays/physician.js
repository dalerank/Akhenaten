log_info("akhenaten: overlay physician started")

[es=city_overlay]
overlay_physician {
  id:OVERLAY_PHYSICIAN
  title: "#overlay_physician"
  walkers:[FIGURE_PHYSICIAN]
  buildings:[BUILDING_PHYSICIAN, BUILDING_ROADBLOCK]
  column_type: COLUMN_TYPE_WATER_ACCESS
  column_anim: {pack:PACK_GENERAL, id:103}
}

[es=(overlay_physician, get_tooltip_for_building)]
function physician_building_tooltip(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_tooltip = "#physician_access_high"
        return
    }

    var physician = house.physician
    if (physician <= 0) {
        city.overlay_tooltip = "#physician_access_none"
    } else if (physician <= 33) {
        city.overlay_tooltip = "#physician_access_low"
    } else if (physician <= 66) {
        city.overlay_tooltip = "#physician_access_medium"
    } else {
        city.overlay_tooltip = "#physician_access_high"
    }
}

[es=(overlay_physician, get_column_height)]
function physician_building_column_height(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_column_height = -1
        return
    }

    if (house.population <= 0) {
        city.overlay_column_height = -1
        return
    }

    city.overlay_column_height = house.physician ? Math.floor(house.physician / 10) : 0
}
