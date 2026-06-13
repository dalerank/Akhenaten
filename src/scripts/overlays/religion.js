log_info("akhenaten: overlay religion started")

[es=city_overlay]
overlay_religion {
  id:OVERLAY_RELIGION
  title: "#overlay_menu_religion"
  walkers:[FIGURE_PRIEST]
  buildings:[ BUILDING_FESTIVAL_SQUARE,
              BUILDING_TEMPLE_RA, BUILDING_TEMPLE_COMPLEX_RA, BUILDING_SHRINE_RA,
              BUILDING_TEMPLE_OSIRIS, BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_SHRINE_OSIRIS,
              BUILDING_ROADBLOCK ]
  column_type: COLUMN_TYPE_WATER_ACCESS
  column_anim: {pack:PACK_GENERAL, id:103}
}

[es=city_overlay]
overlay_religion_osiris {
  id:OVERLAY_RELIGION_OSIRIS
  title: "#overlay_osiris"
  walkers:[FIGURE_PRIEST]
  buildings:[BUILDING_TEMPLE_OSIRIS, BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_ROADBLOCK]
  tooltip_base:0
  tooltips:[]
  column_type: COLUMN_TYPE_WATER_ACCESS
  column_anim: {pack:PACK_GENERAL, id:103}
}

[es=city_overlay]
overlay_religion_ra {
  id:OVERLAY_RELIGION_RA
  title: "#overlay_ra"
  walkers:[FIGURE_PRIEST]
  buildings:[BUILDING_TEMPLE_RA, BUILDING_TEMPLE_COMPLEX_RA, BUILDING_SHRINE_RA, BUILDING_ROADBLOCK]
  tooltip_base:0
  tooltips:[]
  column_type: COLUMN_TYPE_WATER_ACCESS
  column_anim: {pack:PACK_GENERAL, id:103}
}

[es=city_overlay]
overlay_religion_seth {
  id:OVERLAY_RELIGION_SETH
  title: "#overlay_seth"
  walkers:[FIGURE_PRIEST]
  buildings:[BUILDING_TEMPLE_SETH, BUILDING_TEMPLE_COMPLEX_SETH, BUILDING_SHRINE_SETH, BUILDING_ROADBLOCK]
  column_type: COLUMN_TYPE_WATER_ACCESS
  column_anim: {pack:PACK_GENERAL, id:103}
}

[es=city_overlay]
overlay_religion_ptah {
  id:OVERLAY_RELIGION_PTAH
  title: "#overlay_ptah"
  walkers:[FIGURE_PRIEST]
  buildings:[BUILDING_TEMPLE_PTAH, BUILDING_TEMPLE_COMPLEX_PTAH, BUILDING_SHRINE_PTAH, BUILDING_ROADBLOCK]
  column_type: COLUMN_TYPE_WATER_ACCESS
  column_anim: {pack:PACK_GENERAL, id:103}
}

[es=city_overlay]
overlay_religion_bast {
  id:OVERLAY_RELIGION_BAST
  title: "#overlay_bast"
  walkers:[FIGURE_PRIEST]
  buildings:[BUILDING_TEMPLE_BAST, BUILDING_TEMPLE_COMPLEX_BAST, BUILDING_SHRINE_BAST, BUILDING_ROADBLOCK]
  column_type: COLUMN_TYPE_WATER_ACCESS
  column_anim: {pack:PACK_GENERAL, id:103}
}

function religion_tooltip_for_house(house) {
    if (!house) {
        return __loc("#religion_access_shrine_and_all")
    }

    var numGods = house.num_gods
    var tooltip = ""
    if (numGods <= 0) {
        tooltip = __loc("#religion_access_none")
    } else if (numGods == 1) {
        tooltip = __loc("#religion_access_one")
    } else if (numGods == 2) {
        tooltip = __loc("#religion_access_two")
    } else if (numGods == 3) {
        tooltip = __loc("#religion_access_three")
    } else if (numGods == 4) {
        tooltip = __loc("#religion_access_four")
    } else if (numGods == 5) {
        tooltip = __loc("#religion_access_all")
    } else {
        tooltip = __loc("#religion_access_shrine_and_all")
    }

    if (numGods < 5) {
        var extras = []
        if (house.temple_osiris) extras.push(__loc(59, 11 + GOD_OSIRIS))
        if (house.temple_ra) extras.push(__loc(59, 11 + GOD_RA))
        if (house.temple_ptah) extras.push(__loc(59, 11 + GOD_PTAH))
        if (house.temple_seth) extras.push(__loc(59, 11 + GOD_SETH))
        if (house.temple_bast) extras.push(__loc(59, 11 + GOD_BAST))
        if (extras.length > 0) {
            tooltip = tooltip + ":\n" + extras.join(", ")
        }
    }

    return tooltip
}

[es=(overlay_religion, get_tooltip_for_building)]
function religion_building_tooltip(ev) {
    city.overlay_tooltip = religion_tooltip_for_house(city.get_house(ev.bid))
}

[es=(overlay_religion, get_column_height)]
function religion_building_column_height(ev) {
    var house = city.get_house(ev.bid)
    if (!house || house.population <= 0 || !house.num_gods) {
        city.overlay_column_height = -1
        return
    }

    city.overlay_column_height = Math.floor(house.num_gods * 17 / 10)
}

[es=(overlay_religion_osiris, get_column_height)]
function religion_osiris_column_height(ev) {
    var house = city.get_house(ev.bid)
    if (!house || house.population <= 0) {
        city.overlay_column_height = -1
        return
    }

    city.overlay_column_height = Math.floor(house.temple_osiris / 10)
}

[es=(overlay_religion_ra, get_column_height)]
function religion_ra_column_height(ev) {
    var house = city.get_house(ev.bid)
    if (!house || house.population <= 0) {
        city.overlay_column_height = -1
        return
    }

    city.overlay_column_height = Math.floor(house.temple_ra / 10)
}

[es=(overlay_religion_ptah, get_column_height)]
function religion_ptah_column_height(ev) {
    var house = city.get_house(ev.bid)
    if (!house || house.population <= 0) {
        city.overlay_column_height = -1
        return
    }

    city.overlay_column_height = Math.floor(house.temple_ptah / 10)
}

[es=(overlay_religion_seth, get_column_height)]
function religion_seth_column_height(ev) {
    var house = city.get_house(ev.bid)
    if (!house || house.population <= 0) {
        city.overlay_column_height = -1
        return
    }

    city.overlay_column_height = Math.floor(house.temple_seth / 10)
}

[es=(overlay_religion_bast, get_column_height)]
function religion_bast_column_height(ev) {
    var house = city.get_house(ev.bid)
    if (!house || house.population <= 0) {
        city.overlay_column_height = -1
        return
    }

    city.overlay_column_height = Math.floor(house.temple_bast / 10)
}
