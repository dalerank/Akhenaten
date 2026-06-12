log_info("akhenaten: overlay education started")

[es=city_overlay]
overlay_education {
  id:OVERLAY_EDUCATION
  title: "#overlay_education"
  walkers:[FIGURE_SCRIBER, FIGURE_LIBRARIAN, FIGURE_TEACHER]
  buildings:[BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY, BUILDING_ACADEMY, BUILDING_ROADBLOCK]
  column_type: COLUMN_TYPE_WATER_ACCESS
  column_anim: {pack:PACK_GENERAL, id:103}
}

[es=(overlay_education, get_tooltip_for_building)]
function education_building_tooltip(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        return
    }

    switch (house.education) {
    case 0:
        city.overlay_tooltip = "#education_access_none"
        break
    case 1:
        city.overlay_tooltip = "#education_access_school_or_library"
        break
    case 2:
        city.overlay_tooltip = "#education_access_school_and_library"
        break
    case 3:
        city.overlay_tooltip = "#education_access_academy_district"
        break
    }
}

[es=(overlay_education, get_column_height)]
function education_building_column_height(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_column_height = -1
        return
    }

    if (house.education <= 0) {
        city.overlay_column_height = -1
        return
    }

    city.overlay_column_height = house.education * 3 - 1
}
