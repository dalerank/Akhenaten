log_info("akhenaten: console_commands started");

[console_command=hello]
function console_command_hello(args) {
	log_info("Hello, " + ((args && args[0]) || "World") + "!");
}

[console_command=add_pottery]
function console_command_add_pottery(args) {
	var amount = parseInt((args && args[0]) || "100", 10)
	if (amount <= 0) {
		amount = 100
	}
	__cheat_add_resource(RESOURCE_POTTERY, amount)
}

[console_command=add_chickpeas]
function console_command_add_chickpeas(args) {
	var amount = parseInt((args && args[0]) || "100", 10)
	if (amount <= 0) amount = 100
	__cheat_add_resource(RESOURCE_CHICKPEAS, amount)
}

[console_command=add_gamemeat]
function console_command_add_gamemeat(args) {
	var amount = parseInt((args && args[0]) || "100", 10)
	if (amount <= 0) amount = 100
	__cheat_add_resource(RESOURCE_GAMEMEAT, amount)
}

[console_command=collapse_no]
function console_command_collapse_no(args) {
	for (var i = 1; i <= MAX_BUILDINGS; i++) {
		var building = city.get_building(i)
		building.add_collapse_damage(-building.collapse_risk)
	}
}

[console_command=damage_no]
function console_command_damage_no(args) {
	for (var i = 1; i <= MAX_BUILDINGS; i++) {
		var building = city.get_building(i)
		building.add_structure_damage(-building.structure_damage)
	}
}

[console_command=collapse_random_buildings]
function console_command_collapse_random_buildings(args) {
	var count = parseInt((args && args[0]) || "0", 10)
	if (count <= 0) {
		count = 10
	}

	for (var i = 0; i < count; i++) {
		var building = city.get_random_building()
		building.add_collapse_damage(2000)
	}
}

[console_command=test_request_pottery]
function console_command_request_status(args) {
	var amount = parseInt((args && args[0]) || "0", 10)
	if (amount <= 0) {
		amount = 0
	}

	city.create_good_request({ tag_id: 1, resource: RESOURCE_POTTERY, amount: amount, months_initial: 12 })
}

[console_command=migration_status]
function console_command_migration_status(args) {
	log_info("immigration_duration: " + __city_get_migration_property("immigration_duration"))
	log_info("emigration_duration: " + __city_get_migration_property("emigration_duration"))
	log_info("immigration_queue_size: " + __city_get_migration_property("immigration_queue_size"))
	log_info("emigration_queue_size: " + __city_get_migration_property("emigration_queue_size"))
	log_info("percentage: " + __city_get_migration_property("percentage")
			+ " (sentiment " + __city_get_migration_property("percentage_by_sentiment")
			+ " + unemployment " + __city_get_migration_property("percentage_by_unemployments") + ")")
	log_info("population_cap: " + __city_get_migration_property("population_cap"))
	log_info("migration_cap (pop hit): " + __city_get_migration_property("migration_cap"))
	log_info("invading_cap (war): " + __city_get_migration_property("invading_cap"))
	log_info("no_immigration_cause: " + __city_get_migration_property("no_immigration_cause"))
	log_info("sentiment: " + __city_get_sentiment_property("value")
			+ ", low_mood_cause: " + __city_get_sentiment_property("low_mood_cause"))
	log_info("no_room_for_immigrants: " + __city_migration_no_room_for_immigrants())
}

/** off/on or 0/1 sets explicitly; no or other arg toggles current */
function console_tri_state_on_off(args, current) {
	var v = args && args[0]
	if (v === "0" || v === "off") {
		return false
	}
	if (v === "1" || v === "on") {
		return true
	}
	return !current
}