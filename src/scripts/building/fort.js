log_info("akhenaten: building fort started")

base_fort_ghost {
    main_view_offset [[-55, 20], [-55, -35], [-55, -35], [-60, -40]]
    ground_view_offset [[35, 65], [5, -70], [-200, -55], [-180, 46]]
    ground_check_offset [
        [3, -1], [4, -1], [4, 0], [3, 0],
        [-1, -4], [0, -4], [0, -3], [-1, -3],
        [-4, 0], [-3, 0], [-3, 1], [-4, 1],
        [0, 3], [1, 3], [1, 4], [0, 4]
    ]
}

building_fort_charioteers {
    animations {
        _pack {pack: PACK_GENERAL}
        base {id: 66}
        ground {id: 66, offset:1}
        picture {id: 66, offset:3, pos[93, -21]}
    }
    ghost : base_fort_ghost
    labor_category : LABOR_CATEGORY_MILITARY
    building_size : 3
    fire_proof : 1
    damage_proof : 1
    meta { text_id:89, help_link:"message_fort_and_company" }
    info_sound : "Wavs/f_chariot.wav"
    cost [ 500, 700, 900, 1300, 2000 ]
    desirability { value[-20], step[2], step_size[2], range[6] }
    flags {
        is_fort: true
        is_military: true
    }
}

building_fort_infantry {
    animations {
        _pack { pack: PACK_GENERAL }
        base { id: 66}
        ground { id: 66, offset:1}
        picture { id: 66, offset:4, pos:[93, -21]}
    }
    ghost : base_fort_ghost
    labor_category : LABOR_CATEGORY_MILITARY
    building_size : 3
    fire_proof : 1
    damage_proof : 1
    meta { text_id:89, help_link:"message_fort_and_company" }
    info_sound : "Wavs/f_infantry.wav"
    cost [ 200, 300, 500, 800, 1200 ]
    desirability { value[-20], step[2], step_size[2], range [6] }
    flags {
        is_fort: true
        is_military: true
    }
}

building_fort_archers = {
    animations : {
        base: {pack: PACK_GENERAL, id: 66},
        ground: {pack: PACK_GENERAL, id: 66, offset:1},
        picture: {pack: PACK_GENERAL, id: 66, offset:2, pos:[93, -21]},
    }
    ghost : base_fort_ghost
    labor_category : LABOR_CATEGORY_MILITARY
    building_size : 3
    fire_proof : 1
    damage_proof : 1
    meta : { text_id:89, help_link:"message_fort_and_company" }
    info_sound : "Wavs/F_ARCHER.WAV"
    cost : [ 200, 300, 500, 800, 1200 ]
    desirability : { value:[-20], step:[2], step_size:[2], range: [6] }
    flags {
        is_fort: true
        is_military: true
    }
}

building_fort_ground = {
    labor_category : LABOR_CATEGORY_MILITARY,
    building_size : 4,
    fire_proof : 1,
    damage_proof : 1,
    desirability : { value:[-20], step:[2], step_size:[2], range: [6] }
    fire_risk:[0], damage_risk: [0]
    flags {
        is_fort: true
        is_military: true
    }
}

function building_fort_vec(off) {
    if (!off) {
        return { x: 0, y: 0 }
    }
    if (off.length >= 2) {
        return { x: off[0], y: off[1] }
    }
    return { x: off.x | 0, y: off.y | 0 }
}

function building_fort_ghost_config(type) {
    var cfg = get_building_config_by_id(type)
    if (cfg && cfg.ghost && cfg.ghost.ground_check_offset) {
        return cfg.ghost
    }
    return base_fort_ghost
}

function building_fort_footprint_tiles(tile, size) {
    var orientation = Math.floor(__camera.orientation / 2)
    var num_tiles = size * size
    var tiles = []
    var blocked = false
    for (var i = 0; i < num_tiles; i++) {
        var offset = city_planner.tile_grid_offset(orientation, i)
        var check_tile = __map_tile_shift_offset(tile, offset)
        var tile_blocked = __city_planner_is_blocked_for_building(check_tile, 1, TERRAIN_ALL)
        tiles.push({ tile: check_tile, blocked: tile_blocked })
        if (tile_blocked) {
            blocked = true
        }
    }
    return { tiles: tiles, blocked: blocked }
}

function building_fort_draw_partially_blocked(tiles, fully_blocked) {
    for (var i = 0; i < tiles.length; i++) {
        var entry = tiles[i]
        var pixel = city_planner.tile_to_pixel(entry.tile)
        var color = (fully_blocked || entry.blocked) ? COLOR_MASK_RED_30 : COLOR_MASK_GREEN_30
        city_planner.draw_flat_tile(pixel, color)
    }
}

function building_fort_placement_check(ev) {
    var fully_blocked = (city.num_forts >= city.max_forts) || !!city.finance.is_out_of_money
    var blocked = fully_blocked
    var params = city.get_building_params_by_type(city_planner.build_type)
    var ground_params = city.get_building_params_by_type(BUILDING_FORT_GROUND)
    var ghost = building_fort_ghost_config(city_planner.build_type)
    var global_rotation = city_planner.global_rotation
    var ground_off = building_fort_vec(ghost.ground_check_offset[global_rotation * 4 + Math.floor(__camera.orientation / 2)])
    var tile_ground = { x: ev.end.x + ground_off.x, y: ev.end.y + ground_off.y }

    var fort_check = building_fort_footprint_tiles(ev.end, params.building_size)
    var ground_check = building_fort_footprint_tiles(tile_ground, ground_params.building_size)
    blocked = blocked || fort_check.blocked || ground_check.blocked

    var orientation_index = Math.floor(((2 * global_rotation + __camera.orientation) % 8) / 2)
    var main_off = building_fort_vec(ghost.main_view_offset[orientation_index])
    var ground_view_off = building_fort_vec(ghost.ground_view_offset[orientation_index])
    var pixel = ev.pixel
    return {
        blocked: blocked,
        fully_blocked: fully_blocked,
        orientation_index: orientation_index,
        fort_tiles: fort_check.tiles,
        ground_tiles: ground_check.tiles,
        main_pixel: { x: pixel.x + main_off.x, y: pixel.y + main_off.y },
        ground_pixel: { x: pixel.x + ground_view_off.x, y: pixel.y + ground_view_off.y },
        image_id: params.first_img("base"),
        ground_image_id: params.first_img("ground")
    }
}

[es=(building_fort_charioteers, ghost_preview), es=(building_fort_infantry, ghost_preview), es=(building_fort_archers, ghost_preview)]
function building_fort_ghost_preview(ev) {
    var check = building_fort_placement_check(ev)
    if (check.blocked) {
        building_fort_draw_partially_blocked(check.fort_tiles, check.fully_blocked)
        building_fort_draw_partially_blocked(check.ground_tiles, check.fully_blocked)
        return
    }

    if (check.orientation_index == 0 || check.orientation_index == 3) {
        city_planner.draw_ghost(check.main_pixel, check.image_id)
        city_planner.draw_ghost(check.ground_pixel, check.ground_image_id)
    } else {
        city_planner.draw_ghost(check.ground_pixel, check.ground_image_id)
        city_planner.draw_ghost(check.main_pixel, check.image_id)
    }
}

[es=(building_fort_charioteers, ghost_blocked), es=(building_fort_infantry, ghost_blocked), es=(building_fort_archers, ghost_blocked)]
function building_fort_ghost_blocked(ev) {
    building_fort_ghost_preview(ev)
}
