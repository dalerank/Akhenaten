log_info("akhenaten: overlay city_defenses started")

[es=city_overlay]
overlay_city_defenses {
  id:OVERLAY_CITY_DEFENSES
  title: "#overlay_city_defenses"
  walkers:[FIGURE_TOWER_SENTRY, FIGURE_CONSTABLE]
  buildings:[BUILDING_ROADBLOCK]
  column_type: COLUMN_TYPE_POSITIVE
  column_anim: {pack:PACK_GENERAL, id:103}
}

var city_defenses_types = [
    BUILDING_MUD_WALL,
    BUILDING_BRICK_WALL,
    BUILDING_WALL,
    BUILDING_MUD_TOWER,
    BUILDING_BRICK_TOWER,
    BUILDING_TOWER,
    BUILDING_MUD_GATEHOUSE,
    BUILDING_BRICK_GATEHOUSE,
    BUILDING_GATEHOUSE,
    BUILDING_MUD_GATEHOUSE_UP,
    BUILDING_BRICK_GATEHOUSE_UP,
    BUILDING_DECORATIVE_GATEHOUSE,
    BUILDING_TOWER_GATEHOUSE
]

function city_defenses_is_type(type) {
    for (var i = 0; i < city_defenses_types.length; i++) {
        if (city_defenses_types[i] == type) {
            return true
        }
    }
    return false
}

[es=(overlay_city_defenses, get_column_height)]
function city_defenses_building_column_height(ev) {
    city.overlay_column_height = -1
}

[es=(overlay_city_defenses, show_building)]
function city_defenses_show_building(ev) {
    var building = city.get_building(ev.bid)
    if (!building || !building.valid) {
        city.overlay_show_building = 0
        return
    }

    // Roadblocks stay visible for navigation; they are not defense structures.
    if (building.type == BUILDING_ROADBLOCK || city_defenses_is_type(building.type)) {
        city.overlay_show_building = 1
        return
    }

    city.overlay_show_building = 0
}

[es=(overlay_city_defenses, get_tooltip_for_building)]
function city_defenses_building_tooltip(ev) {
    var building = city.get_building(ev.bid)
    if (!building || !building.valid) {
        return
    }

    if (city_defenses_is_type(building.type)) {
        city.overlay_tooltip = "#overlay_city_defenses_structure"
    }
}
