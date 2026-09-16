log_info("akhenaten: terrain.js started")

terrain = {
    is: function(tile, mask) {
        return __map_terrain_is(tile, mask)
    }

    is_plaza_or_earthquake: function(tile) {
        return __map_property_is_plaza_or_earthquake(tile)
    }

    add: function(tile, mask) {
        __map_terrain_add(tile, mask)
    }

    remove: function(tile, mask) {
        __map_terrain_remove(tile, mask)
    }

    wall_building_type: function(tile) {
        return __map_wall_building_type(tile)
    }

    wall_material: function(tile) {
        return __map_wall_material(tile)
    }

    has_adjacent_x: function(tile, type) {
        return __map_terrain_has_adjacent_x_with_type(tile, type)
    }

    has_adjacent_y: function(tile, type) {
        return __map_terrain_has_adjacent_y_with_type(tile, type)
    }

    has_adjacent: function(tile, type) {
        return __map_terrain_has_adjacent_with_type(tile, type)
    }

    count_adjacent: function(tile, type) {
        return __map_terrain_count_directly_adjacent_with_type(tile, type)
    }

    exists_in_area: function(tile, size, type) {
        return __map_terrain_exists_in_area(tile, size, type)
    }

    exists_in_radius: function(tile, size, radius, type) {
        return __map_terrain_exists_in_radius(tile, size, radius, type)
    }

    can_place_road_under_canal: function(tile) {
        return __map_can_place_road_under_canal(tile)
    }

    can_place_canal_on_road: function(tile) {
        return __map_can_place_canal_on_road(tile)
    }

    set_water: function(tile) {
        __map_tiles_set_water(tile)
    }

    set_canal: function(tile) {
        return __map_tiles_set_canal(tile)
    }

    update_canal_tiles: function(include_construction) {
        __map_canal_update_all_tiles(include_construction)
    }

    update_canal_tiles_region: function(pmin, pmax) {
        __map_tiles_update_region_canals(pmin, pmax)
    }

    can_place_initial_road_or_canal: function(tile, is_canal) {
        return __map_can_place_initial_road_or_canal(tile, is_canal)
    }

    canal_ghost_image: function(tile) {
        return __map_canal_ghost_image(tile)
    }

    canal_with_road_image: function(tile) {
        return __map_get_canal_with_road_image(tile)
    }

    dirt_road_image_base: function() {
        return __terrain_dirt_road_image_base()
    }

    canal_image_begin: function() {
        return __terrain_canal_image_begin()
    }

    basin_id: function(tile) {
        return __map_basin_id_at(tile)
    }

    basin_sealed: function(tile) {
        return __map_basin_is_sealed_at(tile)
    }

    // First sealed basin among 8 neighbors (corner crest only touches interior diagonally).
    basin_adjacent_id: function(tile) {
        return __map_basin_adjacent_id(tile)
    }
}
