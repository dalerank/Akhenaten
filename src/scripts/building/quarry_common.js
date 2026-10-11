log_info("akhenaten: building quarry_common started")

function industry_quarry_produce_uptick(b, get_deposit) {
    if (b.num_workers <= 0) {
        b.produce_uptick = 0
        return
    }

    var production = Math.floor(b.num_workers / 2)
    b.produce_uptick = production < 1 ? 1 : production
    industry_mine_require_ore_for_uptick(b, get_deposit)
}
