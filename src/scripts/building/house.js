log_info("akhenaten: building_house.js loaded")

/* Constructor, prototype chain, __property_getter, food/inv/toString: native (js_register_house). */

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
House.property.magistrate = { }
House.property.num_gods = { }
House.property.dentist = { }
House.property.health = { }
House.property.mortuary = { }
House.property.physician = { }
House.property.worst_desirability_building_id = { }
House.property.fancy_bazaar_access = { }
House.property.no_space_to_expand = { }

House.property.population_room = { get: function() { return this.__population_room() } }
House.property.level = { get: function() { return this.__house_level() } }
House.property.model = { get: function() { return city.get_house_model(this.level) } }
House.property.is_vacant_lot = { get: function() { return this.__is_vacant_lot() } }
House.property.evolve_text = { get: function() { return this.__evolve_text() } }
House.property.worst_desirability_building_id = { get: function() { return this.__worst_desirability_building_id() } }
