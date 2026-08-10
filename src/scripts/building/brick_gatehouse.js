log_info("akhenaten: building_brick_gatehouse started")

[es=(building_brick_gatehouse, ghost_preview)]
function building_brick_gatehouse_ghost_preview(ev) {
    building_gatehouse_ghost_preview(ev)
}

[es=(building_brick_gatehouse, ghost_blocked)]
function building_brick_gatehouse_ghost_blocked(ev) {
    building_gatehouse_ghost_blocked(ev)
}

[es=(building_brick_gatehouse, on_place_checks)]
function building_brick_gatehouse_on_place_checks(ev) {
    building_gatehouse_on_place_checks(ev)
}
