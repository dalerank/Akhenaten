log_info("akhenaten: overlay bandstand started")

[es=city_overlay]
overlay_bandstand {
  id:OVERLAY_BANDSTAND
  title: "#overlay_bandstand"
  walkers:[FIGURE_MUSICIAN, FIGURE_JUGGLER]
  buildings:[BUILDING_CONSERVATORY, BUILDING_BANDSTAND, BUILDING_ROADBLOCK]
  column_type: COLUMN_TYPE_POSITIVE
  column_anim: {pack:PACK_GENERAL, id:103}
}

function bandstand_musician_value(house) {
    return Math.max(house.bandstand_musician, house.pavillion_musician)
}

[es=(overlay_bandstand, show_figure)]
function bandstand_show_figure(ev) {
    var fig = city.get_figure(ev.fid)
    if (!fig.valid) {
        city.overlay_show_figure = 0
        return
    }

    if (fig.type == FIGURE_MUSICIAN || fig.type == FIGURE_JUGGLER) {
        var dest = fig.destination
        city.overlay_show_figure = (dest && dest.valid && dest.type == BUILDING_BANDSTAND) ? 1 : 0
        return
    }

    city.overlay_show_figure = 0
}

[es=(overlay_bandstand, get_tooltip_for_building)]
function bandstand_building_tooltip(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        return
    }

    var musician = bandstand_musician_value(house)
    if (musician <= 20) {
        city.overlay_tooltip = "#bandstand_none"
    } else if (musician <= 40) {
        city.overlay_tooltip = "#bandstand_low"
    } else if (musician <= 80) {
        city.overlay_tooltip = "#bandstand_medium"
    } else {
        city.overlay_tooltip = "#bandstand_high"
    }
}

[es=(overlay_bandstand, get_column_height)]
function bandstand_building_column_height(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_column_height = -1
        return
    }

    if (house.population <= 0) {
        city.overlay_column_height = -1
        return
    }

    city.overlay_column_height = bandstand_musician_value(house) / 10
}
