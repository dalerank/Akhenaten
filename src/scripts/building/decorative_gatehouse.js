log_info("akhenaten: building_decorative_gatehouse started")

var building_decorative_gatehouse_composite_tiles = [
    { part: "wall_left", ix: 0, iy: 0 },
    { part: "wall_left", ix: 1, iy: 0 },
    { part: "gate", ix: 0, iy: 0 },
    { part: "wall_right", ix: 0, iy: 0 },
    { part: "wall_right", ix: 1, iy: 0 },
    { part: "wall_left", ix: 0, iy: 1 },
    { part: "wall_left", ix: 1, iy: 1 },
    { part: "gate", ix: 0, iy: 1 },
    { part: "wall_right", ix: 0, iy: 1 },
    { part: "wall_right", ix: 1, iy: 1 }
]

var building_decorative_gatehouse_anim_keys = [
    "wall_left_0_0",
    "wall_left_1_0",
    "gate_0_0",
    "wall_right_0_0",
    "wall_right_1_0",
    "wall_left_0_1",
    "wall_left_1_1",
    "gate_0_1",
    "wall_right_0_1",
    "wall_right_1_1"
]

function building_decorative_gatehouse_composite_world_tile(anchor, layout_orientation, desc) {
    if (layout_orientation == 0) {
        if (desc.part == "wall_left") {
            return { x: anchor.x + desc.ix, y: anchor.y + desc.iy }
        }
        if (desc.part == "gate") {
            return { x: anchor.x + 2, y: anchor.y + desc.iy }
        }
        return { x: anchor.x + 3 + desc.ix, y: anchor.y + desc.iy }
    }

    if (desc.part == "wall_left") {
        return { x: anchor.x + desc.ix, y: anchor.y + desc.iy }
    }
    if (desc.part == "gate") {
        return { x: anchor.x + desc.iy, y: anchor.y + 2 }
    }
    return { x: anchor.x + desc.ix, y: anchor.y + 3 + desc.iy }
}

function building_decorative_gatehouse_footprint_anchor(end, layout_orientation) {
    var width = layout_orientation == 0 ? 5 : 2
    var height = layout_orientation == 0 ? 2 : 5
    var anchor = { x: end.x, y: end.y }
    var ori = __camera.orientation
    if (ori == 2) {
        anchor.x = anchor.x - width + 1
    } else if (ori == 4) {
        anchor.x = anchor.x - width + 1
        anchor.y = anchor.y - height + 1
    } else if (ori == 6) {
        anchor.y = anchor.y - height + 1
    }
    return anchor
}

function building_decorative_gatehouse_ghost_preview(ev) {
    var params = city.get_building_params_by_type(BUILDING_DECORATIVE_GATEHOUSE)
    var gate_orientation = __map_orientation_for_gatehouse(ev.end)
    var layout_orientation = gate_orientation == 1 ? 1 : 0
    var anchor = building_decorative_gatehouse_footprint_anchor(ev.end, layout_orientation)
    var blocked_tiles = []
    var blocked = gate_orientation == 0
    var end_view = building_gatehouse_tile_to_view(ev.end)

    for (var i = 0; i < building_decorative_gatehouse_composite_tiles.length; i++) {
        var world_tile = building_decorative_gatehouse_composite_world_tile(
            anchor, layout_orientation, building_decorative_gatehouse_composite_tiles[i])
        var tile_blocked = __city_planner_is_blocked_for_building(world_tile, 1, TERRAIN_ALL)
        blocked_tiles.push({ tile: world_tile, blocked: tile_blocked })
        blocked = blocked || tile_blocked
    }

    if (blocked) {
        building_gatehouse_draw_partially_blocked(blocked_tiles, false)
        return
    }

    for (var i = 0; i < building_decorative_gatehouse_composite_tiles.length; i++) {
        var world_tile = building_decorative_gatehouse_composite_world_tile(
            anchor, layout_orientation, building_decorative_gatehouse_composite_tiles[i])
        var world_view = building_gatehouse_tile_to_view(world_tile)
        var tile_pixel = {
            x: ev.pixel.x + world_view.x - end_view.x,
            y: ev.pixel.y + world_view.y - end_view.y
        }
        city_planner.draw_ghost(tile_pixel, params.first_img(building_decorative_gatehouse_anim_keys[i]))
    }
}

[es=(building_decorative_gatehouse, setup_preview_graphics)]
function building_decorative_gatehouse_setup_preview_graphics(ev) {
    city_planner.init_tiles(5, 2)
}

[es=(building_decorative_gatehouse, ghost_preview)]
function building_decorative_gatehouse_ghost_preview_es(ev) {
    building_decorative_gatehouse_ghost_preview(ev)
}

[es=(building_decorative_gatehouse, ghost_blocked)]
function building_decorative_gatehouse_ghost_blocked_es(ev) {
    building_decorative_gatehouse_ghost_preview(ev)
}

[es=(building_decorative_gatehouse, can_place)]
function building_decorative_gatehouse_can_place(ev) {
    if (__map_orientation_for_gatehouse(ev.end) == 0) {
        city_planner.finalize_check_result = CAN_NOT_PLACE
        return
    }
    city_planner.finalize_check_result = ev.state
}

[es=(building_decorative_gatehouse, on_place_checks)]
function building_decorative_gatehouse_on_place_checks(ev) {
    building_gatehouse_on_place_checks(ev, 5)
}
