log_info("akhenaten: overlay mortuary started")

[es=city_overlay]
overlay_mortuary {
  id:OVERLAY_MORTUARY
  title: "#overlay_mortuary"
  walkers:[FIGURE_EMBALMER]
  buildings:[BUILDING_MORTUARY, BUILDING_ROADBLOCK]
  column_type: COLUMN_TYPE_POSITIVE
  column_anim: {pack:PACK_GENERAL, id:103}
}

[es=(overlay_mortuary, get_tooltip_for_building)]
function mortuary_building_tooltip(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_tooltip = "#mortuary_access_low"
        return
    }

    var mortuary = house.mortuary
    if (mortuary <= 0) {
        city.overlay_tooltip = "#mortuary_access_none"
    } else if (mortuary >= 80) {
        city.overlay_tooltip = "#mortuary_access_high"
    } else if (mortuary >= 20) {
        city.overlay_tooltip = "#mortuary_access_medium"
    } else {
        city.overlay_tooltip = "#mortuary_access_low"
    }
}

[es=(overlay_mortuary, get_column_height)]
function mortuary_building_column_height(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_column_height = -1
        return
    }

    if (house.mortuary <= 0) {
        city.overlay_column_height = -1
        return
    }

    city.overlay_column_height = house.mortuary / 10
}
