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

[console_command=addpapyrus]
function console_command_addpapyrus(args) {
	var amount = parseInt((args && args[0]) || "100", 10)
	if (amount <= 0) {
		amount = 100
	}
	__cheat_add_resource(RESOURCE_PAPYRUS, amount)
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

[console_command=fire_no]
function console_command_fire_no(args) {
	for (var i = 1; i <= MAX_BUILDINGS; i++) {
		var building = city.get_building(i)
		building.add_fire_damage(-building.fire_risk)
	}
}

[console_command=fire_start]
function console_command_fire_start(args) {
	var count = parseInt((args && args[0]) || "1", 10)
	if (count <= 0) {
		count = 1
	}

	for (var i = 0; i < count; i++) {
		var building = city.get_random_building()
		building.destroy_by_fire()
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

[console_command=show_mission_won]
function console_command_show_mission_won(args) {
    emit event_show_window { id: "window_mission_won" }
}

[console_command=show_victory_dialog]
function console_command_show_victory_dialog(args) {
    city.victory.state = 1
    emit event_show_window { id: "window_victory_dialog" }
}

[console_command=victory]
function console_command_victory(args) {
    city.victory.force_win = true
}

[console_command=defeat]
function console_command_defeat(args) {
    city.victory.force_lost = true
}

[console_command=show_labor_priority]
function console_command_show_labor_priority(args) {
    var category = parseInt((args && args[0]) || "0", 10)
    if (category < 0 || category >= LABOR_CATEGORY_SIZE) {
        category = 0
    }
    show_labor_priority_window(category)
}

[console_command=addmoney]
function console_command_addmoney(args) {
    var money = parseInt((args && args[0]) || "100", 10)
    if (money <= 0) {
        money = 100
    }
    emit event_finance_donation{ amount: money }
    city.warnings.show("Added money")
}

[console_command=crashme]
function console_command_crashme(args) {
    __debug_crash()
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