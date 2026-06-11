log_info("akhenaten: overlay entertainment started")

[es=city_overlay]
overlay_entertainment {
  id:OVERLAY_ENTERTAINMENT
  title: "#overlay_entertainment"
  walkers:[FIGURE_JUGGLER, FIGURE_MUSICIAN, FIGURE_DANCER, FIGURE_SENET_PLAYER, FIGURE_CHARIOR_RACER]
  buildings:[ BUILDING_JUGGLER_SCHOOL, BUILDING_BOOTH, BUILDING_CONSERVATORY,
              BUILDING_BANDSTAND, BUILDING_DANCE_SCHOOL, BUILDING_PAVILLION,
              BUILDING_BULLFIGHT_SCHOOL, BUILDING_SENET_HOUSE,
              BUILDING_ROADBLOCK ]
  column_type: COLUMN_TYPE_WATER_ACCESS
  column_anim: {pack:PACK_GENERAL, id:103}
}

function entertainment_tooltip_tier(entertainment) {
    if (entertainment <= 0) {
        return 0
    }
    if (entertainment < 10) {
        return 1
    }
    if (entertainment < 20) {
        return 2
    }
    if (entertainment < 30) {
        return 3
    }
    if (entertainment < 40) {
        return 4
    }
    if (entertainment < 50) {
        return 5
    }
    if (entertainment < 60) {
        return 6
    }
    if (entertainment < 70) {
        return 7
    }
    if (entertainment < 80) {
        return 8
    }
    if (entertainment < 90) {
        return 9
    }
    return 10
}

var entertainment_tooltip_keys = [
    "#entertainment_access_none",
    "#entertainment_access_barely",
    "#entertainment_access_very_limited",
    "#entertainment_access_limited",
    "#entertainment_access_some",
    "#entertainment_access_several",
    "#entertainment_access_reasonable",
    "#entertainment_access_good",
    "#entertainment_access_very_good",
    "#entertainment_access_excellent",
    "#entertainment_access_max"
]

[es=(overlay_entertainment, get_tooltip_for_building)]
function entertainment_building_tooltip(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_tooltip = "#entertainment_access_max"
        return
    }

    city.overlay_tooltip = entertainment_tooltip_keys[entertainment_tooltip_tier(house.entertainment)]
}

[es=(overlay_entertainment, get_column_height)]
function entertainment_building_column_height(ev) {
    var house = city.get_house(ev.bid)
    if (!house) {
        city.overlay_column_height = -1
        return
    }

    if (house.population <= 0) {
        city.overlay_column_height = -1
        return
    }

    city.overlay_column_height = house.entertainment / 10
}
