log_info("akhenaten: overlay booth started")

[es=city_overlay]
overlay_booth {
  id:OVERLAY_BOOTH
  title: "#overlay_booth"
  walkers:[FIGURE_JUGGLER]
  buildings:[BUILDING_JUGGLER_SCHOOL, BUILDING_BOOTH, BUILDING_ROADBLOCK]
  column_type: COLUMN_TYPE_POSITIVE
  column_anim: {pack:PACK_GENERAL, id:103}
}

function booth_juggler_value(house) {
    return Math.max(house.booth_juggler, house.bandstand_juggler)
}

[es=(overlay_booth, get_tooltip_for_building)]
function booth_building_tooltip(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_tooltip = "#booth_access_low"
        return
    }

    var juggler = booth_juggler_value(house)
    if (juggler <= 0) {
        city.overlay_tooltip = "#booth_access_none"
    } else if (juggler >= 80) {
        city.overlay_tooltip = "#booth_access_high"
    } else if (juggler >= 20) {
        city.overlay_tooltip = "#booth_access_medium"
    } else {
        city.overlay_tooltip = "#booth_access_low"
    }
}

[es=(overlay_booth, get_column_height)]
function booth_building_column_height(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_column_height = -1
        return
    }

    var juggler = booth_juggler_value(house)
    if (juggler <= 0) {
        city.overlay_column_height = -1
        return
    }

    city.overlay_column_height = juggler / 10
}
