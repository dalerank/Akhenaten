log_info("akhenaten: building cattle ranch started")

[es=(building_cattle_ranch, update_animation)]
function building_cattle_ranch_on_update_animation(ev) {
    var b = city.get_building(ev.bid)
    if (!b.play_animation) {
        return
    }
    if (b.stored_resource(RESOURCE_STRAW) < 100 || b.worker_percentage < 50) {
        b.play_animation = false
    }
}
