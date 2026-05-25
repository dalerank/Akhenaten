log_info("akhenaten: dock_prototype.js loaded")

function Dock(building_id) {
    this.id = building_id
}

Dock.prototype = Object.create(Building.prototype)
Dock.prototype.constructor = Dock

Dock.prototype.is_trade_accepted = function(resource) { return __dock_is_trade_accepted(this.id, resource) }
Dock.prototype.toggle_good_accepted = function(resource) { __dock_toggle_good_accepted(this.id, resource) }
Dock.prototype.unaccept_all_goods = function() { __dock_unaccept_all_goods(this.id) }
Dock.prototype.has_trade_ship = function() { return __dock_has_trade_ship(this.id) }
