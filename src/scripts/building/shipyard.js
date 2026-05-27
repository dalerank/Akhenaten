log_info("akhenaten: building shipyard started")

function Shipyard(building_id) {
    this.id = building_id
}

Shipyard.prototype = Object.create(Building.prototype)
Shipyard.prototype.constructor = Shipyard

Shipyard.prototype.__property_getter = function(property) {
    return __shipyard_get_property(this.id, property)
}

Shipyard.property.progress = { }
Shipyard.property.reparing = { }
Shipyard.property.process_type = { }

city.get_shipyard = function(building_id) {
    var b = city.get_building(building_id)
    if (!b.valid || b.type != BUILDING_SHIPWRIGHT) {
        return null
    }
    return new Shipyard(building_id)
}
