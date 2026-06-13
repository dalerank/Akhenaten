log_info("akhenaten: overlay scribal_school started")

[es=city_overlay]
overlay_scribal_school {
  id:OVERLAY_SCRIBAL_SCHOOL
  title: "#overlay_scribal_school"
  walkers:[FIGURE_TEACHER]
  buildings:[BUILDING_SCRIBAL_SCHOOL, BUILDING_ROADBLOCK]
  column_type: COLUMN_TYPE_WATER_ACCESS
  column_anim: {pack:PACK_GENERAL, id:103}
}

[es=(overlay_scribal_school, get_tooltip_for_building)]
function scribal_school_building_tooltip(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_tooltip = "#school_access_low"
        return
    }

    var school = house.school
    if (school <= 0) {
        city.overlay_tooltip = "#school_access_none"
    } else if (school >= 80) {
        city.overlay_tooltip = "#school_access_high"
    } else if (school >= 20) {
        city.overlay_tooltip = "#school_access_medium"
    } else {
        city.overlay_tooltip = "#school_access_low"
    }
}

[es=(overlay_scribal_school, get_column_height)]
function scribal_school_building_column_height(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_column_height = -1
        return
    }

    if (house.population <= 0) {
        city.overlay_column_height = -1
        return
    }

    if (house.school <= 0) {
        city.overlay_column_height = -1
        return
    }

    city.overlay_column_height = house.school / 10
}
