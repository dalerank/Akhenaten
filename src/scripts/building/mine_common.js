log_info("akhenaten: building mine_common started")

function industry_mine_update_production_deplete(b, get_ore, deplete_ore) {
    var area = city.get_grid_area(b.tile, b.size, 0)
    var best_tile = null
    var best = 0
    for (var y = area.min_y; y <= area.max_y; y++) {
        for (var x = area.min_x; x <= area.max_x; x++) {
            var tile = { x: x, y: y }
            var amount = get_ore(tile)
            if (amount > best) {
                best = amount
                best_tile = tile
            }
        }
    }

    if (best <= 0) {
        return
    }

    var before = __building_industry_progress(b.id)
    __building_industry_update_production(b.id)
    var delta = __building_industry_progress(b.id) - before
    if (delta > 0) {
        deplete_ore(best_tile, delta)
    }
}
