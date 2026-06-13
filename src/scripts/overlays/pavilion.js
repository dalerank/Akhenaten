log_info("akhenaten: overlay pavilion started")

[es=city_overlay]
overlay_pavilion {
  id:OVERLAY_PAVILION
  title: "#overlay_pavilion"
  walkers:[]
  buildings:[BUILDING_CONSERVATORY, BUILDING_DANCE_SCHOOL, BUILDING_PAVILLION, BUILDING_ROADBLOCK]
  column_type: COLUMN_TYPE_WATER_ACCESS
  column_anim: {pack:PACK_GENERAL, id:103}
}

[es=(overlay_pavilion, show_figure)]
function pavilion_show_figure(ev) {
    var fig = city.get_figure(ev.fid)
    if (!fig.valid) {
        city.overlay_show_figure = 0
        return
    }

    if (fig.type == FIGURE_DANCER) {
        city.overlay_show_figure = 1
        return
    }

    if (fig.type == FIGURE_MUSICIAN) {
        var dest = fig.destination
        city.overlay_show_figure = (dest && dest.valid && dest.type == BUILDING_PAVILLION) ? 1 : 0
        return
    }

    city.overlay_show_figure = 0
}

[es=(overlay_pavilion, get_tooltip_for_building)]
function pavilion_building_tooltip(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_tooltip = "#pavilion_access_low"
        return
    }

    var dancer = house.pavillion_dancer
    if (dancer <= 0) {
        city.overlay_tooltip = "#pavilion_access_none"
    } else if (dancer >= 80) {
        city.overlay_tooltip = "#pavilion_access_high"
    } else if (dancer >= 20) {
        city.overlay_tooltip = "#pavilion_access_medium"
    } else {
        city.overlay_tooltip = "#pavilion_access_low"
    }
}

[es=(overlay_pavilion, get_column_height)]
function pavilion_building_column_height(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_column_height = -1
        return
    }

    if (house.population <= 0) {
        city.overlay_column_height = -1
        return
    }

    city.overlay_column_height = house.pavillion_dancer / 10
}
