log_info("akhenaten: building_garden started")

function building_garden_place_impl(ev, place) {
    __game_undo_restore_map(1)

    var min_x = Math.min(ev.start_x, ev.end_x)
    var max_x = Math.max(ev.start_x, ev.end_x)
    var min_y = Math.min(ev.start_y, ev.end_y)
    var max_y = Math.max(ev.start_y, ev.end_y)

    var items_placed = 0
    for (var y = min_y; y <= max_y; y++) {
        for (var x = min_x; x <= max_x; x++) {
            var tile = { x: x, y: y }
            if (!__map_grid_is_inside(tile)) {
                continue
            }
            if (terrain.is(tile, TERRAIN_NOT_CLEAR)) {
                continue
            }
            if (terrain.exists_in_radius(tile, 1, 1, TERRAIN_FLOODPLAIN)) {
                continue
            }
            if (__city_animals_breeding_ground_at(tile, 1)) {
                __map_property_clear_constructing_and_deleted()
                city.warnings.show("#cannot_build_over_animal_breeding_grounds")
                continue
            }

            items_placed++
            var flags = TERRAIN_GARDEN
            if (!place) {
                flags |= TERRAIN_PLANER_FUTURE
            }
            terrain.add(tile, flags)
        }
    }

    __map_tiles_gardens_update_all()
    return items_placed
}

[es=(building_garden, construction_update)]
function building_garden_construction_update(ev) {
    city_planner.construction_update_items = building_garden_place_impl(ev, false)
}

[es=(building_garden, construction_place)]
function building_garden_construction_place(ev) {
    city_planner.should_update_land_routing = true
    city_planner.construction_update_items = building_garden_place_impl(ev, true)
}
