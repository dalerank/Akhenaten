log_info("akhenaten: entertainment_prototype.js loaded")

function EntertainmentBuilding(building_id) {
    this.id = building_id
}

EntertainmentBuilding.prototype = Object.create(Building.prototype)
EntertainmentBuilding.prototype.constructor = EntertainmentBuilding

EntertainmentBuilding.prototype.__property_getter = function(property) {
    return __entertainment_building_get_property(this.id, property)
}

EntertainmentBuilding.property.num_shows = { }
EntertainmentBuilding.property.juggler_visited = { }
EntertainmentBuilding.property.musician_visited = { }
EntertainmentBuilding.property.dancer_visited = { }
EntertainmentBuilding.property.play_index = { }
