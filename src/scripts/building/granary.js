log_info("akhenaten: building_granary started")

// prototype for granary buildings

function Granary(building_id) {
    this.id = building_id
}

Granary.prototype = Object.create(Building.prototype)
Granary.prototype.constructor = Granary

Granary.prototype.total_stored = function() { return __granary_get_total_stored(this.id) }
Granary.prototype.amount = function(resource) { return __granary_get_amount(this.id, resource) }
Granary.prototype.free_space = function() { return __granary_get_freespace(this.id) }
Granary.prototype.is_accepting = function(resource) { return __granary_is_accepting(this.id, resource) }
Granary.prototype.is_empty_all = function() { return __granary_is_empty_all(this.id) }
Granary.prototype.resource_state = function(resource) { return __granary_resource_state(this.id, resource) }
Granary.prototype.resource_max_accept = function(resource) { return __granary_resource_max_accept(this.id, resource) }
Granary.prototype.resource_max_get = function(resource) { return __granary_resource_max_get(this.id, resource) }
Granary.prototype.toggle_empty_all = function() { __granary_toggle_empty_all(this.id) }
Granary.prototype.accept_none = function() { __granary_accept_none(this.id) }
Granary.prototype.cycle_resource_state = function(resource) { __granary_cycle_resource_state(this.id, resource) }
Granary.prototype.increase_decrease_resource_state = function(resource, increase) { __granary_increase_decrease_resource_state(this.id, resource, increase) }

city.get_granary = function(building_id) {
    if (!__building_is_granary(building_id)) {
        return null
    }
    return new Granary(building_id)
}

// prototype for granary buildings

building_granary {
    animations {
        preview { pack:PACK_GENERAL, id:99 },
        base { pack:PACK_GENERAL, id:99 },
        work { pack:PACK_SPR_AMBIENT, id:47, max_frames:23 },
        resources {pack:PACK_GENERAL, id:99, offset:2},
        minimap {pack:PACK_GENERAL, id:149, offset:160},
    }

    min_houses_coverage : 100
    labor_category : LABOR_CATEGORY_INFRASTRUCTURE
    meta { help_id: 3, text_id: 98 }
    info_sound : "Wavs/GRANARY1.wav"
    building_size : 4
    planner_update_rule {
        roads : true
    }

    flags {
        is_food: true
    }

    cost [ 50, 70, 100, 200, 300 ]
    laborers[20]
    fire_risk[0]
    damage_risk[5]
    desirability { value[-8], step[1], step_size[-2], range[4] }
    begin_spot_pos [110, -74]
    res_image_offsets [[0, 0], [16, 9], [35, 18], [51, 26], [-16, 7], [1, 16], [20, 26], [37, 35]]
    min_workers_percent_for_tasks : 50
    min_workers_percent_for_accepting :75
    min_workers_percent_for_getting : 100

    sound_channel : SOUND_CHANNEL_CITY_GRANARY
    overlay : OVERLAY_FOOD_STOCKS

    max_capacty_stored : 3200
    allow_food_types : 4
}

[es=(building_granary, on_place_checks)]
function building_granary_on_place_checks(ev) {
    var has_bazaar = city.count_active_buildings(BUILDING_BAZAAR) > 0
    city.warnings.show_if_not(has_bazaar, "#build_bazaars_to_distribute_food")
}
