log_info("akhenaten: building_large_statue started")

building_large_statue = {
    variants : [
      {pack: PACK_GENERAL, id: 7, offset:1},
      {pack: PACK_GENERAL, id: 7, offset:5},
      {pack: PACK_EXPANSION, id: 35, offset:1},
      {pack: PACK_EXPANSION, id: 35, offset:5},
    ]
    meta : {
      help_id:79
      text_id:80
    }
    info_sound : "Wavs/statue1.wav"
    building_size : 3
    cost : [ 30, 45, 60, 90, 150 ]
    desirability : { value:[14], step:[2], step_size:[-2], range: [5] }
    flags {
      is_statue: true
      is_beautification: true
      allow_rotate: true
      no_road_access: true
    }
}

[es=(building_large_statue, setup_preview_graphics)]
function building_large_statue_setup_preview_graphics(ev) {
    var img = statue_get_image(building_large_statue.variants, city_planner.relative_orientation, city_planner.building_variant)
    __city_planner_set_tiles_building(img, building_large_statue.building_size)
}

[es=(building_large_statue, setup_building_variant)]
function building_large_statue_setup_building_variant(ev) {
    city_planner.custom_building_variant = Math.floor(Math.random() * building_large_statue.variants.length)
}

[es=(building_large_statue, next_building_variant)]
function building_large_statue_next_building_variant(ev) {
    statue_next_building_variant(ev, building_large_statue.variants)
}

[es=(building_large_statue, update_relative_orientation)]
function building_large_statue_update_relative_orientation(ev) {
    city_planner.relative_orientation = (city_planner.global_rotation + 1) % 4
}

[es=(building_large_statue, update_building_variant)]
function building_large_statue_update_building_variant(ev) {
    city_planner.building_variant = city_planner.custom_building_variant
}
