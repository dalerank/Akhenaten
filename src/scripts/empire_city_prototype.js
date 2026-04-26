log_info("akhenaten: empire_city_prototype started")

EmpireCity.property.empire_object = { get: function() { return new EmpireCityObject(this.id) } }
EmpireCity.property.is_sieged = { get: function() { return this.months_under_siege > 0 } }