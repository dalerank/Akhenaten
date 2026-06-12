log_info("akhenaten: overlay dentist started")

[es=city_overlay]
overlay_dentist {
  id:OVERLAY_DENTIST
  title: "#overlay_dentist"
  walkers:[FIGURE_DENTIST]
  buildings:[BUILDING_DENTIST, BUILDING_ROADBLOCK]
  column_type: COLUMN_TYPE_POSITIVE
  column_anim: {pack:PACK_GENERAL, id:103}
}

[es=(overlay_dentist, get_tooltip_for_building)]
function dentist_building_tooltip(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_tooltip = "#dentist_access_low"
        return
    }

    var dentist = house.dentist
    if (dentist <= 0) {
        city.overlay_tooltip = "#dentist_access_none"
    } else if (dentist >= 80) {
        city.overlay_tooltip = "#dentist_access_high"
    } else if (dentist >= 20) {
        city.overlay_tooltip = "#dentist_access_medium"
    } else {
        city.overlay_tooltip = "#dentist_access_low"
    }
}

[es=(overlay_dentist, get_column_height)]
function dentist_building_column_height(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_column_height = -1
        return
    }

    if (house.dentist <= 0) {
        city.overlay_column_height = -1
        return
    }

    city.overlay_column_height = house.dentist / 10
}
