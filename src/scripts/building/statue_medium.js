log_info("akhenaten: building_medium_statue started")

building_medium_statue = {
    variants : [
      {pack: PACK_GENERAL, id: 8, offset:1},
      {pack: PACK_GENERAL, id: 8, offset:5},
      {pack: PACK_EXPANSION, id: 36, offset:1},
      {pack: PACK_EXPANSION, id: 36, offset:5},
    ]
    meta : {
      help_id:79
      text_id:80
    }
    info_sound : "Wavs/statue1.wav"
    building_size : 2
    cost : [ 12, 18, 24, 30, 50 ]
    desirability : { value:[10], step:[1], step_size:[-2], range: [4] }
    flags {
      is_statue: true
      is_beautification: true
      allow_rotate: true
    }
}

[es=(building_medium_statue, setup_preview_graphics)]
function building_medium_statue_setup_preview_graphics(ev) {
    var img = statue_get_image(building_medium_statue.variants, city_planner.relative_orientation, city_planner.building_variant)
    __city_planner_set_tiles_building(img, building_medium_statue.building_size)
}

[es=(building_medium_statue, setup_building_variant)]
function building_medium_statue_setup_building_variant(ev) {
    city_planner.custom_building_variant = Math.floor(Math.random() * building_medium_statue.variants.length)
}

[es=(building_medium_statue, next_building_variant)]
function building_medium_statue_next_building_variant(ev) {
    statue_next_building_variant(ev, building_medium_statue.variants)
}

[es=(building_medium_statue, update_relative_orientation)]
function building_medium_statue_update_relative_orientation(ev) {
    city_planner.relative_orientation = (city_planner.global_rotation + 1) % 4
}

[es=(building_medium_statue, update_building_variant)]
function building_medium_statue_update_building_variant(ev) {
    city_planner.building_variant = city_planner.custom_building_variant
}
