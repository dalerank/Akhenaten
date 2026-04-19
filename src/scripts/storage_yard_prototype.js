log_info("akhenaten: storage_yard_prototype.js loaded")

function StorageYard(building_id) {
    this.id = building_id
    this.storage_id = __storage_yard_storage_id(building_id)
}

StorageYard.prototype = Object.create(Building.prototype)
StorageYard.prototype.constructor = StorageYard

StorageYard.prototype.is_empty_all = function() { return __storage_yard_is_empty_all(this.storage_id) }
StorageYard.prototype.resource_state = function(resource_type) { return __storage_yard_resource_state(this.storage_id, resource_type) }
StorageYard.prototype.resource_max_accept = function(resource_type) { return __storage_yard_resource_max_accept(this.storage_id, resource_type) }
StorageYard.prototype.resource_max_get = function(resource_type) { return __storage_yard_resource_max_get(this.storage_id, resource_type) }
StorageYard.prototype.toggle_empty_all = function() { __storage_yard_toggle_empty_all(this.storage_id) }
StorageYard.prototype.accept_none = function() { __storage_yard_accept_none(this.storage_id) }
StorageYard.prototype.cycle_resource_state = function(resource_type, backwards) { __storage_yard_cycle_resource_state(this.storage_id, resource_type, backwards) }
StorageYard.prototype.increase_decrease_resource_state = function(resource_type, increase) { __storage_yard_increase_decrease_resource_state(this.storage_id, resource_type, increase) }
