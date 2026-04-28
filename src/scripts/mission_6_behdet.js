log_info("akhenaten: mission 6 behdet started")

mission6 { // Behdet
	start_message : "message_soldiers_and_forts"
	player_rank : 1
	next_mission : 8
	initial_funds [7500, 5000, 3750, 2500, 2000]
	rescue_loans [7500, 5000, 3750, 2500, 2000]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
	    has_animals : true
	    marshland_grow : default_marshland_grow
	    tree_grow : default_tree_grow
	}

	buildings [
					BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
					BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION, BUILDING_VILLAGE_PALACE,
					BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION,
					BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN,
					BUILDING_WORK_CAMP, BUILDING_CHICKPEAS_FARM, BUILDING_BARLEY_FARM,
					BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY,
					BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
					BUILDING_RECRUITER, BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_WEAPONSMITH,
					BUILDING_SCRIBAL_SCHOOL,
					BUILDING_CLAY_PIT, BUILDING_REED_GATHERER, BUILDING_GOLD_MINE,
					BUILDING_POTTERY_WORKSHOP, BUILDING_WEAVER_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_BRICKS_WORKSHOP,
					BUILDING_SHIPWRIGHT, BUILDING_FISHING_WHARF, BUILDING_FERRY, BUILDING_DOCK,
					BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF,
					BUILDING_BRICKLAYERS_GUILD,
					BUILDING_SMALL_MASTABA, BUILDING_MEDIUM_MASTABA,
					BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
					BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
				]

	win_criteria {
		population {enabled : true, goal : 2500 }
		culture    {enabled : true, goal : 15 }
		prosperity {enabled : true, goal : 20 }
		monuments  {enabled : true, goal : 11 }
		kingdom    {enabled : true, goal : 45 }
	}

	cities [
		{
			name : "Byblos"
			is_sea_trade : true
			max_traders : 1
			trade_limits : default_trade_limits
		}

		{
			name: "Perwadjyt"
			is_sea_trade : true
			max_traders : 1
			trade_limits : default_trade_limits
		}

		{
			name: "Men-nefer"
			is_sea_trade : true
			max_traders : 1
			trade_limits : default_trade_limits
		}
	]

	choice_background {pack:PACK_UNLOADED, id:12}
	choice_image1 {pack:PACK_UNLOADED, id:13}
	choice_image1_pos [192, 144]
	choice_title [144, 19]

	choice [
		{
			name : "Abydos"
			id : 6
			image {pack:PACK_UNLOADED, id:20}
			tooltip [144, 20]
			pos [620, 420]
		}

		{
			name : "Behdet"
			id : 7
			image {pack:PACK_UNLOADED, id:20}
			tooltip [144, 21]
			pos [640, 480]
		}
	]

	vars {
		pharaoh_pottery_requested : false
		pharaoh_fish_requested : false
		pharaoh_beer_requested : false
		pharaoh_beer_late_requested : false
		pharaoh_bricks_gift_sent : false
	}
}

[es=event_advance_month, mission=mission6]
function mission6_pharaoh_request_pottery(ev) {
	if (mission.pharaoh_pottery_requested) {
		return
	}

	if (ev.years_since_start < 1) {
		return
	}
	if (ev.years_since_start == 1 && ev.month < 7) {
		return
	}

	mission.pharaoh_pottery_requested = true
	var request = city.create_good_request({ tag_id: 1, resource: RESOURCE_POTTERY, amount: 14, months_initial: 9 })
	city.create_chain_event({ tag_id: 101, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 6 })
	city.create_chain_event({ tag_id: 102, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 6 })
	request.set_completed_action_tag(101)
	request.set_refusal_action_tag(102)
	request.execute()
}

[es=event_advance_month, mission=mission6]
function mission6_pharaoh_request_beer(ev) {
	if (mission.pharaoh_beer_requested) {
		return
	}

	if (ev.years_since_start < 2) {
		return
	}

	mission.pharaoh_beer_requested = true
	var request = city.create_good_request({ tag_id: 2, resource: RESOURCE_BEER, amount: 11, months_initial: 12 })
	city.create_chain_event({ tag_id: 201, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 12 })
	city.create_chain_event({ tag_id: 202, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 3 })
	request.set_completed_action_tag(201)
	request.set_refusal_action_tag(202)
	request.execute()
}

[es=event_advance_month, mission=mission6]
function mission6_pharaoh_request_fish(ev) {
	if (mission.pharaoh_fish_requested) {
		return
	}

	if (ev.years_since_start < 3) {
		return
	}
	if (ev.years_since_start == 3 && ev.month < 3) {
		return
	}

	mission.pharaoh_fish_requested = true
	var request = city.create_good_request({ tag_id: 4, resource: RESOURCE_FISH, amount: 13, months_initial: 12 })
	city.create_chain_event({ tag_id: 401, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 7 })
	city.create_chain_event({ tag_id: 402, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 10 })
	request.set_completed_action_tag(401)
	request.set_refusal_action_tag(402)
	request.execute()
}

[es=event_advance_month, mission=mission6]
function mission6_pharaoh_request_beer_late(ev) {
	if (mission.pharaoh_beer_late_requested) {
		return
	}

	if (ev.years_since_start < 17) {
		return
	}

	mission.pharaoh_beer_late_requested = true
	var request = city.create_good_request({ tag_id: 5, resource: RESOURCE_BEER, amount: 21, months_initial: 16 })
	city.create_chain_event({ tag_id: 501, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 12 })
	city.create_chain_event({ tag_id: 502, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 7 })
	request.set_completed_action_tag(501)
	request.set_refusal_action_tag(502)
	request.execute()
}

[es=event_advance_month, mission=mission6]
function mission6_pharaoh_bricks_gift(ev) {
	if (mission.pharaoh_bricks_gift_sent) {
		return
	}

	if (ev.years_since_start < 1) {
		return
	}

	mission.pharaoh_bricks_gift_sent = true
	var gift = city.create_pharaoh_gift({ tag_id: 3, resource: RESOURCE_BRICKS, amount: 28 })
	gift.execute()
}