log_info("akhenaten: building_house.js loaded")

/* Constructor, prototype chain, __property_getter, get/set food+inv, toString: native (js_register_house). */

House.property.population = { }
House.property.tax_coverage = { }
House.property.tax_income_or_storage = { }
House.property.house_happiness = { }
House.property.current_desirability = { }
House.property.has_water_access = { }
House.property.has_well_access = { }
House.property.water_supply = { }
House.property.entertainment = { }
House.property.bazaar_access = { }
House.property.education = { }
House.property.school = { }
House.property.library = { }
House.property.academy = { }
House.property.magistrate = { }
House.property.num_gods = { }
House.property.temple_osiris = { }
House.property.temple_ra = { }
House.property.temple_ptah = { }
House.property.temple_seth = { }
House.property.temple_bast = { }
House.property.dentist = { }
House.property.apothecary = { }
House.property.health = { }
House.property.mortuary = { }
House.property.physician = { }
House.property.booth_juggler = { }
House.property.senet_player = { }
House.property.zookeeper = { }
House.property.frog_infest_days = { }
House.property.bandstand_juggler = { }
House.property.bandstand_musician = { }
House.property.pavillion_musician = { }
House.property.pavillion_dancer = { }
House.property.criminal_active = { }
House.property.worst_desirability_building_id = { }
House.property.fancy_bazaar_access = { }
House.property.no_space_to_expand = { }
House.property.evolve_text = { }
House.property.unreachable_ticks = { }
House.property.days_without_food = { }

House.property.population_room = { get: function() { return this.__population_room() } }
House.property.level = { get: function() { return this.__house_level() } }
House.property.model = { get: function() { return city.get_house_model(this.level) } }
House.property.is_vacant_lot = { get: function() { return this.__is_vacant_lot() } }
House.property.num_foods = { }
House.property.hsize = { }

var food_consumption_difficulty_reductions = [40, 35, 30, 25, 15]

function difficulty_adjust_food_consumption(pct) {
    var reduced = (pct * (100 - food_consumption_difficulty_reductions[game.difficulty]) / 100) | 0
    return ((reduced / 5) | 0) * 5
}

House.prototype.consume_food_weekly = function() {
    if (!this.hsize) {
        return
    }

    var model = this.model
    var food_types = model.food_types
    var adjusted_pct = difficulty_adjust_food_consumption(model.food_consumption_percentage)
    var amount_per_type = (adjusted_pct * this.population / 100) | 0
    if (food_types > 1) {
        amount_per_type = (amount_per_type / food_types) | 0
    }

    if (amount_per_type > 0) {
        amount_per_type = (amount_per_type / 2) | 0
        if (amount_per_type < 1) {
            amount_per_type = 1
        }
    }

    this.num_foods = 0
    if (scenario.kingdom_supplies_grain) {
        this.set_food(0, amount_per_type)
        city.resources.note_consumed(RESOURCE_GRAIN, amount_per_type)
        this.num_foods = 1
        return
    }

    if (food_types <= 0) {
        return
    }

    house_consume_food_pass(this, food_types, amount_per_type, amount_per_type * food_types)
}

function house_consume_food_pass(house, food_types, amount_per_type, want_consumed) {
    var slot_mask = 0
    var pass = 0
    while (pass < 2) {
        for (var t = 0; t < 4; t++) {
            var slot_bit = 1 << t
            var counted = (slot_mask & slot_bit) != 0
            if (house.num_foods >= food_types && !counted) {
                continue
            }

            var stored = house.get_food(t)
            var exist_amount = Math.min(stored, amount_per_type)
            if (exist_amount <= 0) {
                continue
            }

            want_consumed -= exist_amount
            house.set_food(t, stored - exist_amount)
            city.resources.note_consumed(city.allowed_foods(t), exist_amount)
            if (!counted) {
                slot_mask |= slot_bit
                house.num_foods = house.num_foods + 1
            }
        }

        pass++
        if (want_consumed <= 0) {
            break
        }
    }
}

House.prototype.consume_goods_weekly = function() {
    if (!this.hsize) {
        return
    }

    var model = this.model
    house_consume_good(this, 0, model.pottery, RESOURCE_POTTERY)
    house_consume_good(this, 1, model.jewelry, RESOURCE_LUXURY_GOODS)
    house_consume_good(this, 2, model.linen, RESOURCE_LINEN)
    house_consume_good(this, 3, model.beer, RESOURCE_BEER)
}

function house_consume_good(house, inv, amount, resource) {
    if (amount <= 0) {
        return
    }
    var stored = house.inv(inv)
    var spent = Math.min(amount, stored)
    if (spent <= 0) {
        return
    }
    house.set_inv(inv, stored - spent)
    city.resources.note_consumed(resource, spent)
}

function house_es_consume_food_weekly(ev) {
    var house = city.get_house(ev.bid)
    if (house) {
        house.consume_food_weekly()
    }
}

function house_es_consume_goods_weekly(ev) {
    var house = city.get_house(ev.bid)
    if (house) {
        house.consume_goods_weekly()
    }
}
