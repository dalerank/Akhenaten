log_info("akhenaten: overlay apothecary started")

[es=city_overlay]
overlay_apothecary {
  id:OVERLAY_APOTHECARY
  title: "#overlay_apothecary"
  walkers:[FIGURE_HERBALIST]
  buildings:[BUILDING_APOTHECARY, BUILDING_ROADBLOCK],
  column_type: COLUMN_TYPE_POSITIVE
  column_anim: {pack:PACK_GENERAL, id:103}
}

[es=(overlay_apothecary, get_tooltip_for_building)]
function apothecary_building_tooltip(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_tooltip = __loc("#apothecary_access_medium")
        return
    }

    var apothecary = house.apothecary
    if (apothecary <= 0) {
        city.overlay_tooltip = __loc("#apothecary_access_none")
    } else if (apothecary >= 80) {
        city.overlay_tooltip = __loc("#apothecary_access_high")
    } else if (apothecary < 20) {
        city.overlay_tooltip = __loc("#apothecary_access_low")
    } else {
        city.overlay_tooltip = __loc("#apothecary_access_medium")
    }
}

[es=(overlay_apothecary, get_column_height)]
function apothecary_building_column_height(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_column_height = -1
        return
    }

    if (house.population <= 0) {
        city.overlay_column_height = -1
        return
    }

    city.overlay_column_height = house.apothecary / 10
}
