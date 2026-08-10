log_info("akhenaten: mission 4 started")

// Trade + pharaoh request chains verified vs mission1.pak scenario 4 (2026-07-25 dump).

mission4 {
	map_file : "data/maps/m_004_mennefer.map"
	start_message : "message_trade_on_the_water"
	selection_title : "Mennefer"
	env {
		has_animals : true
		marshland_grow : default_marshland_grow
	    tree_grow : default_tree_grow
	}
	player_rank : 1
	initial_funds [7500, 5000, 3750, 2500, 2000]
	rescue_loans [7500, 5000, 3750, 2500, 2000]
	house_tax_multipliers [300, 200, 150, 100, 75]

	buildings  [
					BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
					BUILDING_ROADBLOCK, BUILDING_LOW_BRIDGE, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION, BUILDING_VILLAGE_PALACE,
					BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION,
					BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN,
					BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY,
					BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH, BUILDING_TEMPLE_BAST, BUILDING_SHRINE_BAST, BUILDING_FESTIVAL_SQUARE,
					BUILDING_CLAY_PIT, BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
					BUILDING_CHICKPEAS_FARM, BUILDING_BARLEY_FARM, BUILDING_WORK_CAMP,
					BUILDING_MUD_WALL,

					BUILDING_MUD_GATEHOUSE, BUILDING_TOWER_GATEHOUSE, BUILDING_MUD_TOWER,
				]

	sounds {
		briefing : "Voice/Mission/204_mission.mp3"
		victory : "Voice/Mission/204_victory.mp3"
	}

	// Win ratings match mission1.pak; housing_level goal 10 from pak (count goal 0 ignored).
	win_criteria {
		population    {enabled : true, goal : 1500 }
		culture       {enabled : true, goal : 15 }
		prosperity    {enabled : true, goal : 20 }
		monuments     {enabled : true, goal : 9 }
		kingdom       {enabled : true, goal : 40 }
		housing_level {enabled : true, goal : 10 }
	}

	// Map points from mission1.pak scenario 4.
	entry_point [34, 35]
	exit_point [110, 99]
	river_entry_point [70, 2]
	river_exit_point [137, 69]

	// Empire cities from mission1.pak scenario 4 (empire id=1) — full map objects, not pak patch.
	map_background : {pack:PACK_EMPIRE, id:1}
	hide_pak_cities : true
	cities [
		{
			name : "Men-nefer"
			idx : 0
			pos : [541, 491]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_CHICKPEAS, RESOURCE_CLAY, RESOURCE_BARLEY, RESOURCE_REEDS ]
			buys [ RESOURCE_LETTUCE, RESOURCE_BRICKS, RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LUXURY_GOODS ]
		}

		{
			name : "Perwadjyt"
			idx : 3
			pos : [489, 350]
			route : 1
			is_open : false
			cost_to_open : 300
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_FIGS, RESOURCE_CLAY, RESOURCE_BRICKS, RESOURCE_POTTERY, RESOURCE_REEDS ]
			route_limits [
				{ resource: RESOURCE_FIGS, limit: 4000 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_BRICKS, limit: 4000 }
				{ resource: RESOURCE_POTTERY, limit: 4000 }
				{ resource: RESOURCE_REEDS, limit: 4000 }
			]
		}

		{
			name : "Nekhen"
			idx : 22
			pos : [803, 1009]
			route : 4
			is_open : false
			cost_to_open : 550
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_BEER ]
			buys [ RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 1500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
			]
		}

		{
			name : "Nubt"
			idx : 2
			pos : [800, 933]
			route : 3
			is_open : false
			cost_to_open : 450
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Thinis"
			idx : 4
			pos : [687, 871]
			route : 2
			is_open : false
			cost_to_open : 550
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
	]

	// Trade route polylines from mission1.pak empire_map_routes (scenario 4).
	// type: 1=land, 2=sea. Route 3 (Nubt) is empty in pak.
	hide_pak_routes : true
	empire_routes [
		{
			route : 1
			type : 1
			points [
				[508, 382], [520, 399], [530, 416], [534, 441],
				[540, 466], [551, 486], [555, 506], [555, 506]
			]
		}
		{
			route : 2
			type : 1
			points [
				[421, 880], [418, 942], [489, 927], [480, 886], [456, 883], [430, 883]
			]
		}
		{
			route : 4
			type : 1
			points [
				[821, 1024], [812, 996], [808, 982], [810, 973], [804, 958],
				[788, 946], [773, 940], [760, 926], [754, 922], [744, 919],
				[735, 910], [708, 892], [679, 864], [651, 846], [632, 828],
				[608, 815], [590, 798], [580, 781], [567, 739], [562, 722],
				[565, 702], [565, 683], [567, 671], [575, 646], [583, 618],
				[588, 608], [588, 598], [586, 585], [584, 565], [581, 546],
				[576, 525], [560, 511], [560, 511]
			]
		}
	]

	// Region labels from mission1.pak empire_map_objects (scenario 4 dump).
	hide_pak_objects : true
	empire_texts [
		{ name : "#crete", pos : [83, 159] }
		{ name : "#cyprus", pos : [594, 107] }
		{ name : "#eastern_africa", pos : [1019, 1560] }
		{ name : "#eastern_desert", pos : [702, 773] }
		{ name : "#greece", pos : [1, 67] }
		{ name : "#libya", pos : [17, 425] }
		{ name : "#lower_egypt", pos : [429, 476] }
		{ name : "#delta", pos : [518, 362] }
		{ name : "#fayuum", pos : [462, 606] }
		{ name : "#nubia", pos : [806, 1445] }
		{ name : "#palestine", pos : [833, 182] }
		{ name : "#sinai", pos : [787, 478] }
		{ name : "#syria", pos : [1003, 46] }
		{ name : "#upper_egypt", pos : [696, 993] }
		{ name : "#western_desert", pos : [230, 774] }
		{ name : "#lebanon", pos : [877, 109] }
		{ name : "#canaan", pos : [850, 271] }
	]

	vars {
		spacious_apartment_needed : 1
		papyrus_stored : 100
		bricks_stored_needed : 100
		victory_last_action_delay : 3

		spacious_apartment_built : false
		papyrus_made_handled : false
		bricks_bought_handled : false
		pharaoh_requested_beer : false
		pharaoh_requested_papyrus : false
		pharaoh_requested_barley : false
		pharaoh_requested_pottery : false
		last_action_time : 0
		start_message_shown : false
	}

	goal_tooltip: function() {
		if (!mission.spacious_apartment_built) {
			return "#mission4_goal_spacious_apartment"
		}

		if (!mission.papyrus_made_handled) {
			if (city.count_total_buildings(BUILDING_REED_GATHERER) < 1) {
				return "#mission4_goal_reed_gatherer"
			}
			if (city.count_total_buildings(BUILDING_PAPYRUS_WORKSHOP) < 1) {
				return "#mission4_goal_papyrus_maker"
			}
			if (city.count_total_buildings(BUILDING_SCRIBAL_SCHOOL) < 1) {
				return "#mission4_goal_scribal_school"
			}
			return "#mission4_goal_store_papyrus"
		}

		if (!mission.bricks_bought_handled) {
			return "#mission4_goal_import_bricks"
		}

		if (city.count_total_buildings(BUILDING_BRICKLAYERS_GUILD) < 1
			|| city.count_total_buildings(BUILDING_SMALL_MASTABA) < 1) {
			return "#mission4_goal_build_mastaba"
		}

		return "#mission4_goal_export_papyrus"
	}
}

function mission4_fire_request(tag, resource, amount, months, ok_tag, fail_tag, late_tag, ok_amt, fail_amt, late_amt) {
	var request = city.create_good_request({ tag_id: tag, resource: resource, amount: amount, months_initial: months })
	var ok_ev = city.create_chain_event({ tag_id: ok_tag, type: EVENT_TYPE_REPUTATION_INCREASE, amount: ok_amt })
	city.create_chain_event({ tag_id: fail_tag, type: EVENT_TYPE_REPUTATION_DECREASE, amount: fail_amt })
	request.set_completed_action_tag(ok_tag)
	request.set_refusal_action_tag(fail_tag)
	if (late_tag) {
		city.create_chain_event({ tag_id: late_tag, type: EVENT_TYPE_REPUTATION_DECREASE, amount: late_amt })
		request.set_too_late_action_tag(late_tag)
	}
	request.execute()
	return ok_ev
}

[es=event_mission_start, mission=mission4]
function mission4_on_start(ev) {
	mission_show_start_message(mission, "message_trade_on_the_water")
	city.set_empire_available(-1)
	empire.set_id(1)
	empire.set_expanded(false)

	if (mission.papyrus_made_handled) {
		city.set_advisor_available(ADVISOR_TRADE, 1)
		city.use_building(BUILDING_DOCK, true)
		city.set_empire_available(1)
	}

	if (mission.spacious_apartment_built) {
		city.use_building(BUILDING_REED_GATHERER, true)
		city.use_building(BUILDING_PAPYRUS_WORKSHOP, true)
		city.use_building(BUILDING_SCRIBAL_SCHOOL, true)
		city.set_advisor_available(ADVISOR_EDUCATION, 1)
	}

	if (mission.bricks_bought_handled) {
		city.use_building(BUILDING_BRICKLAYERS_GUILD, true)
		city.use_building(BUILDING_SMALL_MASTABA, true)
		city.set_advisor_available(ADVISOR_MONUMENTS, 1)
	}

	city.set_advisor_available(ADVISOR_LABOR, 1)
	city.set_advisor_available(ADVISOR_IMPERIAL, 1)
	city.set_advisor_available(ADVISOR_RATINGS, 1)
	city.set_advisor_available(ADVISOR_POPULATION, 1)
	city.set_advisor_available(ADVISOR_HEALTH, 1)
	city.set_advisor_available(ADVISOR_ENTERTAINMENT, 1)
	city.set_advisor_available(ADVISOR_RELIGION, 1)
	city.set_advisor_available(ADVISOR_FINANCIAL, 1)
	city.set_advisor_available(ADVISOR_CHIEF, 1)
}

[event=event_advance_day, mission=mission4]
function mission4_handle_spacious_apartment() {
    if (mission.spacious_apartment_built) {
        return
    }

    var spacious_apartment_count = city.count_total_buildings(BUILDING_HOUSE_SPACIOUS_APARTMENT);
    if (spacious_apartment_count < mission.spacious_apartment_needed) {
        return
    }

    mission.spacious_apartment_built = true
    mission.last_action_time = game.absolute_day

    city.set_advisor_available(ADVISOR_EDUCATION, 1)

	city.use_building(BUILDING_REED_GATHERER, true)
	city.use_building(BUILDING_PAPYRUS_WORKSHOP, true)
	city.use_building(BUILDING_SCRIBAL_SCHOOL, true)

    ui.popup_message("message_tutorial_education")
}

[event=event_update_victory_state, mission=mission4]
function mission4_handle_victory_state(ev) {
	city.victory.set_reason("spacious_apartment_built", mission.spacious_apartment_built)
	city.victory.set_reason("papyrus_made", mission.papyrus_made_handled)
	city.victory.set_reason("bricks_bought", mission.bricks_bought_handled)

	var some_days_after_last_action = (game.absolute_day - mission.last_action_time) > mission.victory_last_action_delay
	city.victory.set_reason("some_days_after_last_action", some_days_after_last_action)
}

[event=event_warehouse_filled, mission=mission4]
function mission4_handle_papyrus(ev) {
    if (mission.papyrus_made_handled) {
        return
    }

	var papyrus_amount = city.yards_stored(RESOURCE_PAPYRUS)
    if (papyrus_amount < mission.papyrus_stored) {
        return
    }

    mission.papyrus_made_handled = true
	mission.last_action_time = game.absolute_day

	city.set_advisor_available(ADVISOR_TRADE, 1)
	city.set_empire_available(1)
    city.use_building(BUILDING_DOCK, true)

	ui.popup_message("message_tutorial_trade_with_other_cities")
}

[event=event_warehouse_filled, mission=mission4]
function mission4_handle_bricks(ev) {
    if (mission.bricks_bought_handled) {
        return
    }

    var bricks_amount = city.yards_stored(RESOURCE_BRICKS)
    if (bricks_amount < mission.bricks_stored_needed) {
        return
    }

    mission.bricks_bought_handled = true
	mission.last_action_time = game.absolute_day

	city.use_building(BUILDING_BRICKLAYERS_GUILD, true)
	city.use_building(BUILDING_SMALL_MASTABA, true)

	city.set_advisor_available(ADVISOR_MONUMENTS, 1)
	ui.popup_message("message_tutorial_monuments")
}

// pak request chains (scenario 4 dump 2026-07-25).
// beer y6m8 / 9 / 12mo — once; ok→+5→GIFT bricks 20; refuse/late→−6
[es=event_advance_month, mission=mission4]
function mission4_pharaoh_request_beer(ev) {
	if (mission.pharaoh_requested_beer) {
		return
	}
	if (ev.years_since_start < 6 || (ev.years_since_start == 6 && ev.month < 8)) {
		return
	}
	mission.pharaoh_requested_beer = true
	var ok_ev = mission4_fire_request(10, RESOURCE_BEER, 9, 12, 110, 111, 112, 5, 6, 6)
	city.create_chain_event({
		tag_id: 113,
		type: EVENT_TYPE_GIFT_FROM_PHARAOH,
		resource: RESOURCE_BRICKS,
		amount: 20
	})
	ok_ev.set_completed_action_tag(113)
}

// papyrus y8m10 / 8 / 9mo — ok→DEMAND_INCREASE→+5; refuse/late→DEMAND_DECREASE→−4
// (demand ± currently message-only in engine, same as Behdet stubs)
[es=event_advance_month, mission=mission4]
function mission4_pharaoh_request_papyrus(ev) {
	if (mission.pharaoh_requested_papyrus) {
		return
	}
	if (ev.years_since_start < 8 || (ev.years_since_start == 8 && ev.month < 10)) {
		return
	}
	mission.pharaoh_requested_papyrus = true
	var request = city.create_good_request({ tag_id: 20, resource: RESOURCE_PAPYRUS, amount: 8, months_initial: 9 })
	var ok_demand = city.create_chain_event({
		tag_id: 201,
		type: EVENT_TYPE_DEMAND_INCREASE,
		resource: RESOURCE_PAPYRUS,
		amount: 8
	})
	city.create_chain_event({ tag_id: 202, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 5 })
	ok_demand.set_completed_action_tag(202)

	var fail_demand = city.create_chain_event({
		tag_id: 203,
		type: EVENT_TYPE_DEMAND_DECREASE,
		resource: RESOURCE_PAPYRUS,
		amount: 8
	})
	city.create_chain_event({ tag_id: 204, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 4 })
	fail_demand.set_completed_action_tag(204)

	request.set_completed_action_tag(201)
	request.set_refusal_action_tag(203)
	request.set_too_late_action_tag(203)
	request.execute()
}

// barley y10m5 / 10 / 18mo — ok→+9; refuse/late→−6
[es=event_advance_month, mission=mission4]
function mission4_pharaoh_request_barley(ev) {
	if (mission.pharaoh_requested_barley) {
		return
	}
	if (ev.years_since_start < 10 || (ev.years_since_start == 10 && ev.month < 5)) {
		return
	}
	mission.pharaoh_requested_barley = true
	mission4_fire_request(12, RESOURCE_BARLEY, 10, 18, 301, 302, 303, 9, 6, 6)
}

// pottery y15m4 / 8 / 12mo — ok→+9; refuse/late→−6
[es=event_advance_month, mission=mission4]
function mission4_pharaoh_request_pottery(ev) {
	if (mission.pharaoh_requested_pottery) {
		return
	}
	if (ev.years_since_start < 15 || (ev.years_since_start == 15 && ev.month < 4)) {
		return
	}
	mission.pharaoh_requested_pottery = true
	mission4_fire_request(13, RESOURCE_POTTERY, 8, 12, 401, 402, 403, 9, 6, 6)
}
