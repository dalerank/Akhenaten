log_info("akhenaten: overlay academy started")

[es=city_overlay]
overlay_academy {
  id:OVERLAY_ACADEMY
  title: "#overlay_academy"
  walkers:[FIGURE_LIBRARIAN]
  buildings:[BUILDING_LIBRARY, BUILDING_ROADBLOCK]
  column_type: COLUMN_TYPE_WATER_ACCESS
  column_anim: {pack:PACK_GENERAL, id:103}
}

[es=(overlay_academy, get_tooltip_for_building)]
function academy_building_tooltip(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_tooltip = "#academy_access_low"
        return
    }

    var academy = house.academy
    if (academy <= 0) {
        city.overlay_tooltip = "#academy_access_none"
    } else if (academy >= 80) {
        city.overlay_tooltip = "#academy_access_high"
    } else if (academy >= 20) {
        city.overlay_tooltip = "#academy_access_medium"
    } else {
        city.overlay_tooltip = "#academy_access_low"
    }
}

[es=(overlay_academy, get_column_height)]
function academy_building_column_height(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_column_height = -1
        return
    }

    if (house.academy <= 0) {
        city.overlay_column_height = -1
        return
    }

    city.overlay_column_height = house.academy / 10
}
