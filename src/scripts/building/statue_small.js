log_info("akhenaten: building_small_statue started")

building_small_statue = {
    variants : [
      {pack: PACK_GENERAL, id: 61, offset:0}
      {pack: PACK_GENERAL, id: 61, offset:4}
      {pack: PACK_EXPANSION, id: 37, offset:0}
      {pack: PACK_EXPANSION, id: 37, offset:4}
      {pack: PACK_TEMPLE_RA, id: 1, offset:27}
    ]
    meta : {
      help_id:79
      text_id:80
    }
    info_sound : "Wavs/statue1.wav"
    building_size : 1
    cost : [ 3, 5, 8, 13, 21 ]
    desirability : { value:[3], step:[1], step_size:[-1], range: [3] }
    flags {
      is_statue: true
      is_beautification: true
      allow_rotate: true
      no_road_access: true
    }
}

[es=(building_small_statue, setup_preview_graphics)]
function building_small_statue_setup_preview_graphics(ev) {
    var img = statue_get_image(building_small_statue.variants, city_planner.relative_orientation, city_planner.building_variant)
    __city_planner_set_tiles_building(img, building_small_statue.building_size)
}

[es=(building_small_statue, setup_building_variant)]
function building_small_statue_setup_building_variant(ev) {
    city_planner.custom_building_variant = Math.floor(Math.random() * building_small_statue.variants.length)
}

[es=(building_small_statue, next_building_variant)]
function building_small_statue_next_building_variant(ev) {
    statue_next_building_variant(ev, building_small_statue.variants)
}

[es=(building_small_statue, update_relative_orientation)]
function building_small_statue_update_relative_orientation(ev) {
    city_planner.relative_orientation = (city_planner.global_rotation + 1) % 4
}

[es=(building_small_statue, update_building_variant)]
function building_small_statue_update_building_variant(ev) {
    city_planner.building_variant = city_planner.custom_building_variant
}
