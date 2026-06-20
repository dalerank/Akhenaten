log_info("akhenaten: building storage_yard started")

building_storage_yard {
    animations {
        preview { pos: [0, 0], pack: PACK_GENERAL, id: 82 }
        base { pos: [0, 0], pack: PACK_GENERAL, id: 82 }
        cover { pos: [-5, -42], pack: PACK_GENERAL, id: 82, offset: 17 }
        work { pos: [10, -10], pack: PACK_SPR_AMBIENT, id: 51, offset: 1, max_frames: 14, duration: 3 }
    }

    preview_view_offsets: [
        [0, 0],
        [-30, 15], [30, 15], [0, 30],
        [-60, 30], [60, 30], [-30, 45], [30, 45], [0, 60]
    ]
    preview_cover_offset: [-5, -45]
    preview_space: { pack: PACK_GENERAL, id: 83 }

    labor_category: LABOR_CATEGORY_INDUSTRY_COMMERCE
    meta: { help_id: 4, text_id: 99 }
    info_sound: "Wavs/warehouse1.wav"
    building_size: 3
    min_houses_coverage: 100
    cost: [14, 30, 50, 100, 150]
    desirability: { value: [-5], step: [2], step_size: [2], range: [3] }
    laborers: [6]
    fire_risk: [4]
    damage_risk: [1]
    flags {
        is_industry: true
    }
}

building_storage_room {
    animations {
    }

    building_size: 3
    fire_proof: true

    flags {
        is_industry: true
    }
}

function storage_yard_hut_corner(global_rotation, camera_orientation) {
    var rot = (2 * global_rotation + camera_orientation) % 8
    if (rot == 2) {
        return 4
    }
    if (rot == 4) {
        return 8
    }
    if (rot == 6) {
        return 5
    }
    return 0
}

[es=(building_storage_yard, ghost_preview)]
function building_storage_yard_ghost_preview(ev) {
    var pixel = ev.pixel
    var params = city.get_building_params_by_type(BUILDING_STORAGE_YARD)
    var corner = storage_yard_hut_corner(city.planner.global_rotation, __camera.orientation)
    var hut_id = params.first_img("base")
    var space_id = get_image(building_storage_yard.preview_space).tid
    var cover = building_storage_yard.animations.cover
    var cover_id = get_image({ pack: cover.pack, id: cover.id, offset: cover.offset }).tid
    var offsets = building_storage_yard.preview_view_offsets
    var cover_off = building_storage_yard.preview_cover_offset

    for (var i = 0; i < 9; i++) {
        var off = offsets[i]
        var tile_pixel = { x: pixel.x + off[0], y: pixel.y + off[1] }
        if (i == corner) {
            city.planner.draw_ghost(tile_pixel, hut_id)
            city.planner.draw_overlay_tile(
                { x: tile_pixel.x + cover_off[0], y: tile_pixel.y + cover_off[1] },
                cover_id,
                COLOR_MASK_GREEN
            )
        } else {
            city.planner.draw_ghost(tile_pixel, space_id)
        }
    }
}
