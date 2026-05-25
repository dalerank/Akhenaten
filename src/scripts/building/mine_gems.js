log_info("akhenaten: building_mine_gems started")

[es=(building_mine_gems, on_before_collapse)]
function building_mine_gems_on_before_collapse(ev) {
    if (!game_features.gameplay_change_random_mine_or_pit_collapses_take_money) {
        return
    }
    emit event_finance_request { type: efinance_request_disasters, deben: 250 }
}
