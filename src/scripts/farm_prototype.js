log_info("akhenaten: farm_prototype.js loaded")

function Farm(building_id) {
    this.id = building_id
}

Farm.prototype = Object.create(Building.prototype)
Farm.prototype.constructor = Farm

Farm.prototype.__property_getter = function(property) {
    return __farm_get_property(this.id, property)
}

Farm.property.flood_imminent = { }
Farm.property.progress = { }
Farm.property.is_floodplain = { }

Farm.prototype.set_worker = function(action, coords) {
    __farm_set_worker(this.id, action, coords)
}
