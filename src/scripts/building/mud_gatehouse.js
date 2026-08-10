log_info("akhenaten: building_mud_gatehouse started")

[es=(building_mud_gatehouse, ghost_preview)]
function building_mud_gatehouse_ghost_preview(ev) {
    building_gatehouse_ghost_preview(ev)
}

[es=(building_mud_gatehouse, ghost_blocked)]
function building_mud_gatehouse_ghost_blocked(ev) {
    building_gatehouse_ghost_blocked(ev)
}

[es=(building_mud_gatehouse, on_place_checks)]
function building_mud_gatehouse_on_place_checks(ev) {
    building_gatehouse_on_place_checks(ev)
}
