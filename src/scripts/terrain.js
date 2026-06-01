log_info("akhenaten: terrain.js started")

terrain = {
    is: function(tile, mask) {
        return __map_terrain_is(tile, mask)
    }

    add: function(tile, mask) {
        __map_terrain_add(tile, mask)
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

    can_place_road_under_canal: function(tile) {
        return __map_can_place_road_under_canal(tile)
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
}
