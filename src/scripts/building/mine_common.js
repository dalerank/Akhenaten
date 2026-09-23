log_info("akhenaten: building mine_common started")

function industry_mine_best_ore_tile(b, get_ore) {
    var area = city.get_grid_area(b.tile, b.size, 0)
    var best_tile = null
    var best = 0
    for (var y = area.miny; y <= area.maxy; y++) {
        for (var x = area.minx; x <= area.maxx; x++) {
            var tile = { x: x, y: y }
            var amount = get_ore(tile)
            if (amount > best) {
                best = amount
                best_tile = tile
            }
        }
    }

    if (best <= 0) {
        return null
    }

    return best_tile
}

function industry_mine_require_ore_for_uptick(b, get_ore) {
    if (!industry_mine_best_ore_tile(b, get_ore)) {
        b.produce_uptick = 0
    }
}

function industry_mine_deplete_production(b, get_ore, deplete_ore) {
    var delta = b.progress - b.progress_before
    if (delta <= 0) {
        return
    }

    var best_tile = industry_mine_best_ore_tile(b, get_ore)
    if (best_tile) {
        deplete_ore(best_tile, delta)
    }
}
