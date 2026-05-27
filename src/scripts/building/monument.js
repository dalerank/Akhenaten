log_info("akhenaten: building monument prototype started")

function Monument(building_id) {
    this.id = building_id
}

Monument.prototype = Object.create(Building.prototype)
Monument.prototype.constructor = Monument

Monument.prototype.need_workers = function() {
    return __monument_need_workers(this.id)
}

Monument.prototype.phase = function() {
    return __monument_phase_code(this.id)
}

Monument.prototype.phases_total = function() {
    return __monument_phases_total(this.id)
}

Monument.prototype.material_pct_min = function() {
    return __monument_material_pct_min(this.id)
}
