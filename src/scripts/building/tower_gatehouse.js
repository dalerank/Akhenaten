log_info("akhenaten: building_tower_gatehouse started")

function building_tower_gatehouse_ghost_preview(ev) {
    var params = city.get_building_params_by_type(BUILDING_TOWER_GATEHOUSE)
    var orientation = __map_adjust_building_determine_orientation(
        ev.end, params.building_size, 1, 1, BUILDING_MUD_GATEHOUSE)
    var fully_blocked = orientation < 0
    var restricted = TERRAIN_ALL - TERRAIN_WALL
    var blocked_tiles = []
    var size = params.building_size
    var blocked = fully_blocked
    var city_orientation = Math.floor(__camera.orientation / 2)

    for (var i = 0; i < size * size; i++) {
        var offset = city_planner.tile_grid_offset(city_orientation, i)
        var check_tile = __map_tile_shift_offset(ev.end, offset)
        var tile_blocked = __city_planner_is_blocked_for_building(check_tile, 1, restricted)
        blocked_tiles.push({ tile: check_tile, blocked: tile_blocked })
        blocked = blocked || tile_blocked
    }

    if (blocked) {
        building_gatehouse_draw_partially_blocked(blocked_tiles, fully_blocked)
        return
    }

    var image_id = params.first_img("base")
    image_id += (orientation == 0 || orientation == 2) ? 1 : 0
    city_planner.update_tiles_building(image_id)
    city_planner.draw_tile_graphics_array(ev.start, ev.end, ev.pixel)
}

[es=(building_tower_gatehouse, ghost_preview)]
function building_tower_gatehouse_ghost_preview_es(ev) {
    building_tower_gatehouse_ghost_preview(ev)
}

[es=(building_tower_gatehouse, ghost_blocked)]
function building_tower_gatehouse_ghost_blocked_es(ev) {
    building_tower_gatehouse_ghost_preview(ev)
}

[es=(building_tower_gatehouse, can_place)]
function building_tower_gatehouse_can_place(ev) {
    var params = city.get_building_params_by_type(BUILDING_TOWER_GATEHOUSE)
    var orientation = __map_adjust_building_determine_orientation(
        ev.start, params.building_size, 1, 1, BUILDING_MUD_GATEHOUSE)
    city_planner.finalize_check_result = orientation < 0 ? CAN_NOT_PLACE : ev.state
}
