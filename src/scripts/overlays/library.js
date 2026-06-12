log_info("akhenaten: overlay library started")

[es=city_overlay]
overlay_library {
  id:OVERLAY_LIBRARY
  title: "#overlay_library"
  walkers:[FIGURE_LIBRARIAN]
  buildings:[BUILDING_LIBRARY, BUILDING_ROADBLOCK]
  column_type: COLUMN_TYPE_WATER_ACCESS
  column_anim: {pack:PACK_GENERAL, id:103}
}

[es=(overlay_library, get_tooltip_for_building)]
function library_building_tooltip(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_tooltip = "#library_access_low"
        return
    }

    var library = house.library
    if (library <= 0) {
        city.overlay_tooltip = "#library_access_none"
    } else if (library >= 80) {
        city.overlay_tooltip = "#library_access_high"
    } else if (library >= 20) {
        city.overlay_tooltip = "#library_access_medium"
    } else {
        city.overlay_tooltip = "#library_access_low"
    }
}

[es=(overlay_library, get_column_height)]
function library_building_column_height(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_column_height = -1
        return
    }

    if (house.library <= 0) {
        city.overlay_column_height = -1
        return
    }

    city.overlay_column_height = house.library / 10
}
