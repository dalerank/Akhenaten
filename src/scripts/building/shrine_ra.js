log_info("akhenaten: building_shrine_ra started")

[es=building]
building_shrine_ra {
    type: BUILDING_SHRINE_RA
    animations : {
      preview : {pack:PACK_GENERAL, id:74, },
      base : {pack:PACK_GENERAL, id:74, offset:0 },
    },
    labor_category : LABOR_CATEGORY_RELIGION,
    overlay : OVERLAY_RELIGION_RA,
    meta : { text_id: 161, help_link:"message_building_shrine_and_temple" }
    info_sound : "Wavs/SHR_RA.wav"
    building_size : 1
    cost: [ 20, 30, 50, 80, 120 ]
    laborers:[0], fire_risk:[0], damage_risk: [2]
    desirability : { value:[4], step:[1], step_size:[-1], range: [4] }

    flags {
      is_shrine: true
      is_religion: true
      no_road_access: true
    }
}

[es=(building_shrine_ra, on_place_checks)]
function building_shrine_ra_on_place_checks(ev) {
    var b = city.get_building(ev.bid)
    var has_road = __map_road_within_radius(b.tile, b.size, 2)
    city.warnings.show_if_not(has_road, "#shrines_near_road_required")
}
