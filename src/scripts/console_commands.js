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