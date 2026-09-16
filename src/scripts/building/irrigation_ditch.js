log_info("akhenaten: building_irrigation_ditch started")

function building_irrigation_ditch_has_water_source_nearby(tile) {
    if (terrain.count_adjacent(tile, TERRAIN_WATER) > 0) {
        return true
    }

    var offsets = [
        { x: 0, y: 1 },
        { x: 1, y: 0 },
        { x: 0, y: -1 },
        { x: -1, y: 0 }
    ]
    for (var i = 0; i < offsets.length; i++) {
        var adj = { x: tile.x + offsets[i].x, y: tile.y + offsets[i].y }
        if (terrain.is(adj, TERRAIN_BUILDING)) {
            var bid = __building_at(adj.x, adj.y)
            if (bid && __building_type(bid) == BUILDING_WATER_LIFT) {
                return true
            }
        }
        if (terrain.is(adj, TERRAIN_CANAL)) {
            return true
        }
    }
    return false
}

function building_irrigation_ditch_is_road_tile_for_canal(tile, gate_orientation) {
    var is_road = terrain.is(tile, TERRAIN_ROAD)
    if (terrain.is(tile, TERRAIN_BUILDING)) {
        var b = city.get_building_at(tile.x, tile.y)
        if (b.type == BUILDING_MUD_GATEHOUSE) {
            if (b.orientation == gate_orientation) {
                is_road = true
            }
        } else if (b.type == BUILDING_GRANARY) {
            if (__map_routing_citizen_is_road(tile)) {
                is_road = true
            }
        }
    }
    return is_road
}

function building_irrigation_ditch_is_straight_road_for_canal(tile) {
    var road_x = building_irrigation_ditch_is_road_tile_for_canal({ x: tile.x + 1, y: tile.y }, 2)
        || building_irrigation_ditch_is_road_tile_for_canal({ x: tile.x - 1, y: tile.y }, 2)
    var road_y = building_irrigation_ditch_is_road_tile_for_canal({ x: tile.x, y: tile.y - 1 }, 1)
        || building_irrigation_ditch_is_road_tile_for_canal({ x: tile.x, y: tile.y + 1 }, 1)
    if (road_x && !road_y) {
        return true
    }
    if (road_y && !road_x) {
        return true
    }
    return false
}

[es=(building_irrigation_ditch, can_place)]
function building_irrigation_ditch_can_place(ev) {
    if (!building_irrigation_ditch_has_water_source_nearby(ev.start)) {
        city_planner.set_warning("#irrigation_ditch_needs_water_source")
        city_planner.finalize_check_result = CAN_NOT_PLACE
        return
    }
    city_planner.finalize_check_result = ev.state
}

[es=(building_irrigation_ditch, can_construction_start)]
function building_irrigation_ditch_can_construction_start(ev) {
    var start = ev.start
    if (!__map_routing_calculate_distances_for_building(ROUTED_BUILDING_CANALS, start)) {
        city_planner.preview_allow_result = 0
        return
    }

    var valid = terrain.is(start, TERRAIN_ROAD)
        || terrain.is(start, TERRAIN_CANAL)
        || terrain.is(start, TERRAIN_FLOODPLAIN)
        || (!terrain.is(start, TERRAIN_NOT_CLEAR) && !terrain.is(start, TERRAIN_WATER))
    if (!valid) {
        city_planner.preview_allow_result = 0
        return
    }

    city_planner.preview_allow_result = building_irrigation_ditch_has_water_source_nearby(start)
}

[es=(building_irrigation_ditch, ghost_allow_tile)]
function building_irrigation_ditch_ghost_allow_tile(ev) {
    if (!ev.in_progress) {
        city_planner.preview_allow_result = building_irrigation_ditch_has_water_source_nearby(ev.tile)
        return
    }
    city_planner.preview_allow_result = !__map_has_figure_at(ev.tile)
}

[es=(building_irrigation_ditch, construction_update)]
function building_irrigation_ditch_construction_update(ev) {
    __game_undo_restore_map(0)
    city_planner.construction_update_items = 0

    var start = { x: ev.start_x, y: ev.start_y }
    var end = { x: ev.end_x, y: ev.end_y }
    if (!__map_routing_calculate_distances_for_building(ROUTED_BUILDING_CANALS, start)) {
        return
    }

    var items = __place_routed_building(start, end, ROUTED_BUILDING_CANALS)
    if (items > 0) {
        var pmin = { x: Math.min(start.x, end.x) - 2, y: Math.min(start.y, end.y) - 2 }
        var pmax = { x: Math.max(start.x, end.x) + 2, y: Math.max(start.y, end.y) + 2 }
        terrain.update_canal_tiles_region(pmin, pmax)
    }
    city_planner.construction_update_items = items
}

[es=(building_irrigation_ditch, construction_place)]
function building_irrigation_ditch_construction_place(ev) {
    __game_undo_restore_map(0)

    var start = { x: ev.start_x, y: ev.start_y }
    var end = { x: ev.end_x, y: ev.end_y }
    var items = 0
    if (__map_routing_calculate_distances_for_building(ROUTED_BUILDING_CANALS, start)) {
        items = __place_routed_building(start, end, ROUTED_BUILDING_CANALS)
    }

    terrain.update_canal_tiles(0)
    city_planner.should_update_land_routing = true
    city_planner.construction_update_items = items
}

[es=(building_irrigation_ditch, ghost_preview)]
function building_irrigation_ditch_ghost_preview(ev) {
    var blocked = false
    if (!terrain.can_place_initial_road_or_canal(ev.end, 1)) {
        blocked = true
    }

    if (ev.in_progress) {
        if (!city_planner.total_cost) {
            blocked = true
        }
    } else {
        if (!building_irrigation_ditch_has_water_source_nearby(ev.start)) {
            blocked = true
            city_planner.set_warning("#irrigation_ditch_needs_water_source")
        }

        if (terrain.is(ev.end, TERRAIN_ROAD)) {
            if (!building_irrigation_ditch_is_straight_road_for_canal(ev.end)) {
                blocked = true
            }
            if (terrain.is_plaza_or_earthquake(ev.end)) {
                blocked = true
            }
        } else if (terrain.is(ev.end, TERRAIN_NOT_CLEAR) && !terrain.is(ev.end, TERRAIN_FLOODPLAIN)) {
            blocked = true
        }
    }

    if (city.finance.is_out_of_money) {
        blocked = true
    }

    if (blocked) {
        city_planner.draw_blocked(ev.pixel)
    } else {
        city_planner.draw_ghost(ev.pixel, terrain.canal_ghost_image(ev.end))
    }
}
