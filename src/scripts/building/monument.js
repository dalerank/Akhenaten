log_info("akhenaten: building monument prototype started")

/* Constructor, prototype chain, methods: native (js_register_monument). */

Monument.property.variant = { }

// Walks the multipart chain (same coverage as map_grid_get_tiles(main, 0)).
Monument.prototype.foreach_tile = function(fn) {
    var part = city.get_building(this.id)
    var guard = 0
    while (part && guard < 128) {
        guard++
        var origin = part.tile
        var size = part.size
        for (var dx = 0; dx < size; dx++) {
            for (var dy = 0; dy < size; dy++) {
                fn({ x: origin.x + dx, y: origin.y + dy })
            }
        }
        if (!part.next_part_building_id) {
            break
        }
        part = city.get_building(part.next_part_building_id)
    }
}

// Dev cheat: set incomplete tiles to 200, then place OG engine blocks.
// max_count <= 0 = all remaining tiles/blocks for this monument.
Monument.prototype.boost_incomplete_tiles = function(max_count) {
    if (this.phase() === -1) {
        return 0
    }
    var limit = max_count || 0
    var bumped = 0
    var done = false
    var self = this
    this.foreach_tile(function(tile) {
        if (done || (limit > 0 && bumped >= limit)) {
            done = true
            return
        }
        var incomplete = self.tile_progress(tile) < 200
        if (limit > 0 && !incomplete) {
            return
        }
        if (incomplete) {
            bumped++
        }
        self.set_tile_progress(tile, 200)
    })

    var left = limit > 0 ? (limit - bumped) : 0
    if (limit <= 0 || left > 0) {
        bumped += this.boost_engine_blocks(limit > 0 ? left : 0)
    }
    return bumped
}

Monument.prototype.weight_btype = function() {
    return monument_weight_btype(this.id)
}
