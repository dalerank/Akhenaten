log_info("akhenaten: overlay courthouse started")

[es=city_overlay]
overlay_courthouse {
  id:OVERLAY_COUTHOUSE
  title: "#overlay_magistrate"
  walkers:[FIGURE_MAGISTRATE]
  buildings:[BUILDING_COURTHOUSE, BUILDING_ROADBLOCK]
  column_type: COLUMN_TYPE_WATER_ACCESS
  column_anim: {pack:PACK_GENERAL, id:103}
}

[es=(overlay_courthouse, get_tooltip_for_building)]
function courthouse_building_tooltip(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_tooltip = "#magistrate_access_high"
        return
    }

    var magistrate = house.magistrate
    if (magistrate <= 0) {
        city.overlay_tooltip = "#magistrate_access_none"
    } else if (magistrate <= 33) {
        city.overlay_tooltip = "#magistrate_access_low"
    } else if (magistrate <= 66) {
        city.overlay_tooltip = "#magistrate_access_medium"
    } else {
        city.overlay_tooltip = "#magistrate_access_high"
    }
}

[es=(overlay_courthouse, get_column_height)]
function courthouse_building_column_height(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_column_height = -1
        return
    }

    if (house.population <= 0) {
        city.overlay_column_height = -1
        return
    }

    if (house.magistrate <= 0) {
        city.overlay_column_height = 0
        return
    }

    city.overlay_column_height = house.magistrate / 10
}
