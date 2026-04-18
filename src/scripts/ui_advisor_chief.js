log_info("akhenaten: ui advisor chief started")

advisor_chief_window = {
	ui : {
		background : dummy({ pos:[0, 0] }),

		outer_panel : { type : "outer_panel", pos:[0, 0], size:[40, 27] },
		advisor_icon : { type : "image", pack:PACK_GENERAL, id:128, offset:11, pos:[10, 10] },
		header_label : { type : "label", font : FONT_LARGE_BLACK_ON_LIGHT, text:"#chief_overseer",	pos:[60, 17]},
		inner_panel : { type : "inner_panel", pos:[17, 60], size:[38, 17] },

		// sentiment
		sentiment_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 67] },
		sentiment_label : { type : "label", pos:[44, 66], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_sentiment"},
		sentiment_info : { type : "label", pos:[185, 66], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// migration
		migration_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 87] },
		migration_label : { type : "label", pos:[44, 86], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_migration"},
		migration_info : { type : "label", pos:[185, 86], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// workers
		workers_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 107] },
		workers_label : { type : "label", pos:[44, 106], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_workers"},
		workers_info : { type : "label", pos:[185, 106], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// food stocks
		foodstocks_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 127] },
		foodstocks_label : { type : "label", pos:[44, 126], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_foodstocks"},
		foodstocks_info : { type : "label", pos:[185, 126], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// food consumption
		foodconsumption_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 147] },
		foodconsumption_label : { type : "label", pos:[44, 146], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_foodconsumption"},
		foodconsumption_info : { type : "label", pos:[185, 146], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// health
		health_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 167] },
		health_label : { type : "label", pos:[44, 166], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_health"},
		health_info : { type : "label", pos:[185, 166], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// religion
		religion_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 187] },
		religion_label : { type : "label", pos:[44, 186], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_religion"},
		religion_info : { type : "label", pos:[185, 186], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// finance
		finance_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 207] },
		finance_label : { type : "label", pos:[44, 206], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_finance"},
		finance_info : { type : "label", pos:[185, 206], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// crime
		crime_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 227] },
		crime_label : { type : "label", pos:[44, 226], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_crime"},
		crime_info : { type : "label", pos:[185, 226], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// military
		military_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 247] },
		military_label : { type : "label", pos:[44, 246], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_military"},
		military_info : { type : "label", pos:[185, 246], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// kingdom
		kingdom_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 267] },
		kingdom_label : { type : "label", pos:[44, 266], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_kingdom"},
		kingdom_info : { type : "label", pos:[185, 266], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// nilometr
		nilometr_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 287] },
		nilometr_label : { type : "label", pos:[44, 286], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_nilometr"},
		nilometr_info : { type : "label", pos:[185, 286], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},
		nilometr_info2 : { type : "label", pos:[185, 306], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},
	}
}

function advisor_chief_window_update_sentiment(window) {
	var sentiment = city.sentiment.value
	var text_id
	var font
	if (sentiment <= 0) {
		text_id = 20
		font = FONT_NORMAL_YELLOW
	} else if (sentiment >= 100) {
		text_id = 31
		font = FONT_NORMAL_BLACK_ON_DARK
	} else {
		text_id = 32 + ((sentiment / 10) | 0)
		font = FONT_NORMAL_BLACK_ON_DARK
	}
	window.sentiment_info.text = __loc(61, text_id)
	window.sentiment_info.font = font
}

function advisor_chief_window_update_migration(window) {
	var invaders = __city_figures_total_invading_enemies()

	var newcomers = city.migration.newcomers
	var pct = city.migration.percentage
	var cause = city.migration.no_immigration_cause

	var text_id
	var font
	if (invaders > 3) {
		text_id = 43
		font = FONT_NORMAL_BLACK_ON_DARK
	} else if (newcomers >= 5) {
		text_id = 44
		font = FONT_NORMAL_BLACK_ON_DARK
	} else if (__city_migration_no_room_for_immigrants()) {
		text_id = 45
		font = FONT_NORMAL_YELLOW
	} else if (pct >= 80) {
		text_id = 44
		font = FONT_NORMAL_BLACK_ON_DARK
	} else {
		text_id = 43
		font = FONT_NORMAL_BLACK_ON_DARK
		switch (cause) {
			case NO_IMMIGRATION_LOW_WAGES: text_id = 46; break
			case NO_IMMIGRATION_NO_JOBS: text_id = 47; break
			case NO_IMMIGRATION_NO_FOOD: text_id = 48; break
			case NO_IMMIGRATION_HIGH_TAXES: text_id = 49; break
			case NO_IMMIGRATION_MANY_TENTS: text_id = 50; break
			case NO_IMMIGRATION_LOW_MOOD: text_id = 51; break
			default: text_id = 59; break
		}
	}

	window.migration_info.text = __loc(61, text_id)
	window.migration_info.font = font
}

function advisor_chief_window_update_workers(window) {
	var lab = city.labor
	var pct_unemployment = lab.unemployment_percentage
	var needed_workers = lab.workers_needed
	var workers_unemployed = lab.workers_unemployed
	var text_id
	var font
	if (pct_unemployment > 0) {
		if (pct_unemployment > 10) {
			text_id = 76
			font = FONT_NORMAL_YELLOW
		} else if (pct_unemployment > 5) {
			text_id = 77
			font = FONT_NORMAL_YELLOW
		} else if (pct_unemployment > 2) {
			text_id = 78
			font = FONT_NORMAL_YELLOW
		} else {
			text_id = 79
			font = FONT_NORMAL_BLACK_ON_DARK
		}
		var unemployed_num = workers_unemployed - needed_workers
		window.workers_info.text = __loc(61, text_id) + " " + pct_unemployment + "(" + unemployed_num + ")"
	} else if (needed_workers > 0) {
		if (needed_workers > 75) {
			text_id = 80
			font = FONT_NORMAL_YELLOW
		} else if (needed_workers > 50) {
			text_id = 81
			font = FONT_NORMAL_YELLOW
		} else if (needed_workers > 25) {
			text_id = 82
			font = FONT_NORMAL_YELLOW
		} else {
			text_id = 83
			font = FONT_NORMAL_BLACK_ON_DARK
		}
		window.workers_info.text = __loc(61, text_id) + " " + needed_workers
	} else {
		text_id = 84
		font = FONT_NORMAL_BLACK_ON_DARK
		window.workers_info.text = __loc(61, text_id)
	}
	window.workers_info.font = font
}

function advisor_chief_window_update_foodstocks(window) {
	if (scenario.kingdom_supplies_grain()) {
		window.foodstocks_info.text = __loc(61, 26)
		window.foodstocks_info.font = FONT_NORMAL_BLACK_ON_DARK
	} else {
		var months = __city_resource_food_supply_months()
		if (months > 0) {
			window.foodstocks_info.text = __loc(61, 98) + " " + months
			window.foodstocks_info.font = FONT_NORMAL_BLACK_ON_DARK
		} else {
			window.foodstocks_info.text = __loc(61, 95)
			window.foodstocks_info.font = FONT_NORMAL_YELLOW
		}
	}
}

function advisor_chief_window_update_foodconsumption(window) {
	var text_id
	var font
	if (scenario.kingdom_supplies_grain()) {
		text_id = 26
		font = FONT_NORMAL_BLACK_ON_DARK
	} else {
		var pct = city.resources.food_percentage_produced
		if (pct > 150) {
			text_id = 13
			font = FONT_NORMAL_BLACK_ON_DARK
		} else if (pct > 105) {
			text_id = 14
			font = FONT_NORMAL_BLACK_ON_DARK
		} else if (pct > 95) {
			text_id = 15
			font = FONT_NORMAL_BLACK_ON_DARK
		} else if (pct > 75) {
			text_id = 16
			font = FONT_NORMAL_YELLOW
		} else if (pct > 30) {
			text_id = 17
			font = FONT_NORMAL_YELLOW
		} else {
			text_id = 18
			font = FONT_NORMAL_YELLOW
		}
	}
	window.foodconsumption_info.text = __loc(61, text_id)
	window.foodconsumption_info.font = font
}

function advisor_chief_window_update_health(window) {
	var health_rate = city.health_rating
	window.health_info.text = __loc(61, 103 + ((health_rate / 10) | 0))
	window.health_info.font = (health_rate >= 40) ? FONT_NORMAL_BLACK_ON_DARK : FONT_NORMAL_YELLOW
}

function advisor_chief_window_update_religion(window) {
	var r = city.houses.religion
	var text_id
	var font
	if (r === 1) {
		text_id = 46
		font = FONT_NORMAL_YELLOW
	} else if (r === 2) {
		text_id = 47
		font = FONT_NORMAL_YELLOW
	} else if (r === 3) {
		text_id = 48
		font = FONT_NORMAL_YELLOW
	} else {
		text_id = 49
		font = FONT_NORMAL_BLACK_ON_DARK
	}
	window.religion_info.text = __loc(61, text_id)
	window.religion_info.font = font
}

function advisor_chief_window_update_finance(window) {
	var treasury = city.finance.treasury
	var balance_last_year = city.finance.last_year.balance
	if (treasury > balance_last_year) {
		window.finance_info.text = __loc(61, 152) + " " + (treasury - balance_last_year)
		window.finance_info.font = FONT_NORMAL_BLACK_ON_DARK
	} else if (treasury < balance_last_year) {
		window.finance_info.text = __loc(61, 154) + " " + (balance_last_year - treasury)
		window.finance_info.font = FONT_NORMAL_YELLOW
	} else if (city.taxes.percentage_taxed_people < 75) {
		window.finance_info.text = __loc(61, 151)
		window.finance_info.font = FONT_NORMAL_BLACK_ON_DARK
	} else {
		window.finance_info.text = __loc(61, 153)
		window.finance_info.font = FONT_NORMAL_BLACK_ON_DARK
	}
}

function advisor_chief_window_update_crime(window) {
	var criminals = city.sentiment.criminals
	var stolen = city.finance.this_year.expenses.stolen
	var text
	var font
	if (criminals > 10) {
		text = __loc(61, 159) + " " + stolen + " " + __loc(61, 164)
		font = FONT_NORMAL_YELLOW
	} else if (criminals > 7) {
		text = __loc(61, 160) + " " + stolen + " " + __loc(61, 164)
		font = FONT_NORMAL_YELLOW
	} else if (criminals > 5) {
		text = __loc(61, 161) + " " + stolen + " " + __loc(61, 164)
		font = FONT_NORMAL_YELLOW
	} else if (criminals > 2) {
		text = __loc(61, 162) + " " + stolen + " " + __loc(61, 164)
		font = FONT_NORMAL_BLACK_ON_DARK
	} else {
		text = __loc(61, 163)
		font = FONT_NORMAL_BLACK_ON_DARK
	}
	window.crime_info.text = text
	window.crime_info.font = font
}

[es=(advisor_chief_window, ui_draw_foreground)]
function advisor_chief_window_ui_draw_foreground(window) {
	advisor_chief_window_update_sentiment(window)
	advisor_chief_window_update_migration(window)
	advisor_chief_window_update_workers(window)
	advisor_chief_window_update_foodstocks(window)
	advisor_chief_window_update_foodconsumption(window)
	advisor_chief_window_update_health(window)
	advisor_chief_window_update_religion(window)
	advisor_chief_window_update_finance(window)
	advisor_chief_window_update_crime(window)
}