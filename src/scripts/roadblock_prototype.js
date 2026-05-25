log_info("akhenaten: roadblock_prototype.js loaded")

function Roadblock(building_id) {
    this.id = building_id
}

Roadblock.prototype = Object.create(Building.prototype)
Roadblock.prototype.constructor = Roadblock

Roadblock.prototype.get_permission = function(permission) {
    return __roadblock_get_permission(this.id, permission)
}

Roadblock.prototype.toggle_permission = function(permission) {
    __roadblock_toggle_permission(this.id, permission)
}
