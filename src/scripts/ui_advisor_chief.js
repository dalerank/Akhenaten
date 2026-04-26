log_info("akhenaten: ui advisor chief started")

[es=advisor_window]
advisor_chief_window {
	advisor: ADVISOR_CHIEF
	allow_rmb_goback : true
	help_id: "message_chief_overseer"
	ui : baseui(advisor_window_base, {
		advisor_area             : dummy({ pos [(sw(0) - px(40)) / 2, (sh(0) - px(30)) / 2]
			ui : {
				background : dummy({ pos:[0, 0] })

				outer_panel : { type : "outer_panel", pos:[0, 0], size:[40, 27] }
				advisor_icon : { type : "image", pack:PACK_GENERAL, id:128, offset:11, pos:[10, 10] }
				header_label : { type : "label", font : FONT_LARGE_BLACK_ON_LIGHT, text:"#chief_overseer",	pos:[60, 17]}

				chief_report_list : scrollable_list({
					pos: [26, 66]
					size: [35, 21]
					view_items: 16
					buttons_size_y: 20
					buttons_margin_y: 8
					buttons_margin_x: 0
					text_padding_x: 0
					text_padding_y: 0
					draw_scrollbar_always: false
					draw_paneling: true
					onrender_item: advisor_chief_report_on_render_item
				})
			}
		})
	})
}

function advisor_chief_wrap_lines(text, maxChars) {
	var lines = []
	if (!text) {
		return lines
	}
	var t = String(text)
	while (t.length > 0) {
		if (maxChars <= 0 || t.length <= maxChars) {
			lines.push(t)
			break
		}
		var cut = maxChars
		var minWord = ((maxChars * 2 / 5) | 0)
		var sp = t.lastIndexOf(" ", cut)
		if (sp > minWord) {
			cut = sp
		}
		var chunk = t.substring(0, cut).trim()
		if (!chunk.length) {
			cut = Math.min(maxChars, Math.max(1, t.length))
			chunk = t.substring(0, cut).trim()
		}
		if (!chunk.length) {
			break
		}
		lines.push(chunk)
		var rest = t.substring(cut).trim()
		if (rest === t) {
			break
		}
		t = rest
	}
	return lines
}

function advisor_chief_report_body_max_chars() {
	var wrapPx = 31 * 16 - 2
	return Math.max(24, (wrapPx / 7) | 0)
}

function advisor_chief_push_wrapped_section_rows(bodyText, sectionTitle, font) {
	advisor_chief_window._chief_report_rows.push({
		title: sectionTitle
		body: ""
		font: font
		bullet: true
	})

	var lines = advisor_chief_wrap_lines(bodyText, advisor_chief_report_body_max_chars())
	var li
	for (li = 0; li < lines.length; li++) {
		advisor_chief_window._chief_report_rows.push({
			title: ""
			body: lines[li]
			font: font
			bullet: false
		})
	}
}

function advisor_chief_report_on_render_item(p) {
	var rows = advisor_chief_window._chief_report_rows

	var row = rows[p.user_data]

	var wrapPx = Math.max(120, p.sizex - 42)
	var maxChars = Math.max(24, (wrapPx / 7) | 0)

	if (row.title && row.title.length) {
		var img = get_image({ pack: PACK_GENERAL, id: 158 })
		ui.image(img, [p.x + 8, p.y + 4])
		ui.label(row.title, [p.x + 35, p.y + 3], FONT_NORMAL_WHITE_ON_DARK, UiFlags_None)
	}

	if (row.body && row.body.length) {
		ui.label(row.body, [p.x + 35, p.y + 3], row.font, UiFlags_None, wrapPx)
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
	advisor_chief_push_wrapped_section_rows(__loc(61, text_id), __loc("#chief_adv_sentiment"), font)
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

	advisor_chief_push_wrapped_section_rows(__loc(61, text_id), __loc("#chief_adv_migration"), font)
}

function advisor_chief_window_update_workers(window) {
	var lab = city.labor
	var pct_unemployment = lab.unemployment_percentage
	var needed_workers = lab.workers_needed
	var workers_unemployed = lab.workers_unemployed
	var text_id
	var text
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
		text = __loc(61, text_id) + " " + pct_unemployment + "(" + unemployed_num + ")"
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
		text = __loc(61, text_id) + " " + needed_workers
	} else {
		text = __loc(61, 84)
		font = FONT_NORMAL_BLACK_ON_DARK
	}
	advisor_chief_push_wrapped_section_rows(text, __loc("#chief_adv_workers"), font)
}

function advisor_chief_window_update_housing(window) {
	var cap = city.open_housing_capacity()
	var text
	var font
	if (cap <= 0) {
		text = __loc("#TR_ADVISOR_HOUSING_NO_ROOM")
		font = FONT_NORMAL_YELLOW
	} else {
		text = __loc("#TR_ADVISOR_HOUSING_ROOM") + " " + String(cap)
		font = FONT_NORMAL_BLACK_ON_DARK
	}
	advisor_chief_push_wrapped_section_rows(text, __loc("#TR_HEADER_HOUSING"), font)
}

/** Group 61 ids 39–42 are not education in this fork; texts use Overseer of Learning strings (group 57). */
function advisor_chief_window_update_education(window) {
	var edu = city.houses.education
	var tid57
	var font
	if (edu === 1) {
		tid57 = 19
		font = FONT_NORMAL_YELLOW
	} else if (edu === 2) {
		tid57 = 21
		font = FONT_NORMAL_YELLOW
	} else if (edu === 3) {
		tid57 = 23
		font = FONT_NORMAL_YELLOW
	} else {
		tid57 = 25
		font = FONT_NORMAL_BLACK_ON_DARK
	}
	advisor_chief_push_wrapped_section_rows(__loc(57, tid57), __loc(14, 5), font)
}

/** Group 61 ids 43–45 are not entertainment here; uses Overseer of Diversions strings (group 58). */
function advisor_chief_window_update_entertainment(window) {
	var ent = city.houses.entertainment
	var tid58
	var font
	if (ent === 1) {
		tid58 = 10
		font = FONT_NORMAL_YELLOW
	} else if (ent === 2) {
		tid58 = 11
		font = FONT_NORMAL_YELLOW
	} else {
		tid58 = (city.avg_coverage.average_entertainment === 0) ? 7 : 8
		font = FONT_NORMAL_BLACK_ON_DARK
	}
	advisor_chief_push_wrapped_section_rows(__loc(58, tid58), __loc(14, 3), font)
}

function advisor_chief_window_update_foodstocks(window) {
	var text
	var font
	if (scenario.kingdom_supplies_grain()) {
		text = __loc(61, 26)
		font = FONT_NORMAL_BLACK_ON_DARK
	} else {
		var months = __city_resource_food_supply_months()
		if (months > 0) {
			text = __loc(61, 98) + " " + months
			font = FONT_NORMAL_BLACK_ON_DARK
		} else {
			text = __loc(61, 95)
			font = FONT_NORMAL_YELLOW
		}
	}
	advisor_chief_push_wrapped_section_rows(text, __loc("#chief_adv_foodstocks"), font)
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
	advisor_chief_push_wrapped_section_rows(__loc(61, text_id), __loc("#chief_adv_foodconsumption"), font)
}

function advisor_chief_window_update_health(window) {
	var health_rate = city.health_rating
	var font = (health_rate >= 40) ? FONT_NORMAL_BLACK_ON_DARK : FONT_NORMAL_YELLOW
	advisor_chief_push_wrapped_section_rows(__loc(61, 103 + ((health_rate / 10) | 0)), __loc("#chief_adv_health"), font)
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
	advisor_chief_push_wrapped_section_rows(__loc(61, text_id), __loc("#chief_adv_religion"), font)
}

function advisor_chief_window_update_finance(window) {
	var treasury = city.finance.treasury
	var balance_last_year = city.finance.last_year.balance
	var text
	var font
	if (treasury > balance_last_year) {
		text = __loc(61, 152) + " " + (treasury - balance_last_year)
		font = FONT_NORMAL_BLACK_ON_DARK
	} else if (treasury < balance_last_year) {
		text = __loc(61, 154) + " " + (balance_last_year - treasury)
		font = FONT_NORMAL_YELLOW
	} else if (city.taxes.percentage_taxed_people < 75) {
		text = __loc(61, 151)
		font = FONT_NORMAL_BLACK_ON_DARK
	} else {
		text = __loc(61, 153)
		font = FONT_NORMAL_BLACK_ON_DARK
	}
	advisor_chief_push_wrapped_section_rows(text, __loc("#chief_adv_finance"), font)
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
	advisor_chief_push_wrapped_section_rows(text, __loc("#chief_adv_crime"), font)
}

function advisor_chief_window_update_military(window) {
	var fig = city.figures
	var text_id
	var font
	if (fig.kingdome_soldiers) {
		text_id = 170
		font = FONT_NORMAL_YELLOW
	} else if (fig.enemies) {
		text_id = 170
		font = FONT_NORMAL_YELLOW
	} else if (__scenario_invasion_exists_upcoming()) {
		text_id = 170
		font = FONT_NORMAL_YELLOW
	} else if (__distant_battle_kingdome_army_is_traveling()) {
		text_id = 170
		font = FONT_NORMAL_BLACK_ON_DARK
	} else if (__distant_battle_months_until_battle() > 0) {
		text_id = 170
		font = FONT_NORMAL_YELLOW
	} else if (fig.soldiers > 0) {
		text_id = 177
		font = FONT_NORMAL_BLACK_ON_DARK
	} else {
		text_id = 171
		font = FONT_NORMAL_BLACK_ON_DARK
	}
	advisor_chief_push_wrapped_section_rows(__loc(61, text_id), __loc("#chief_adv_military"), font)
}

function advisor_chief_window_update_kingdom(window) {
	var requests = __scenario_requests_active_count()
	var text_id
	var font
	if (requests === 0) {
		text_id = 187
		font = FONT_NORMAL_BLACK_ON_DARK
	} else if (requests === 1) {
		text_id = 186
		font = FONT_NORMAL_WHITE_ON_DARK
	} else if (requests === 2) {
		text_id = 185
		font = FONT_NORMAL_YELLOW
	} else {
		text_id = 184
		font = FONT_NORMAL_YELLOW
	}
	advisor_chief_push_wrapped_section_rows(__loc(61, text_id), __loc("#chief_adv_kingdom"), font)
}

function advisor_chief_window_update_nilometr(window) {
	var flood_quality = __city_floods_expected_quality()
	var text_id
	var font
	if (flood_quality === 100) {
		text_id = 197
		font = FONT_NORMAL_BLACK_ON_DARK
	} else if (flood_quality > 75) {
		text_id = 196
		font = FONT_NORMAL_BLACK_ON_DARK
	} else if (flood_quality > 50) {
		text_id = 195
		font = FONT_NORMAL_BLACK_ON_DARK
	} else if (flood_quality > 25) {
		text_id = 194
		font = FONT_NORMAL_BLACK_ON_DARK
	} else if (flood_quality > 0) {
		text_id = 193
		font = FONT_NORMAL_BLACK_ON_DARK
	} else {
		text_id = 192 + flood_quality
		font = FONT_NORMAL_YELLOW
	}

	var text = __loc(61, text_id)
	if (flood_quality > 0) {
		text += " " + __loc(61, 204 + __city_floods_expected_month())
	}
	advisor_chief_push_wrapped_section_rows(text, __loc("#chief_adv_nilometr"), font)
}

function advisor_chief_window_fill_report_rows(window) {
	advisor_chief_window._chief_report_rows = []
	advisor_chief_window_update_sentiment(window)
	advisor_chief_window_update_migration(window)
	advisor_chief_window_update_workers(window)
	advisor_chief_window_update_housing(window)
	advisor_chief_window_update_education(window)
	advisor_chief_window_update_entertainment(window)
	advisor_chief_window_update_foodstocks(window)
	advisor_chief_window_update_foodconsumption(window)
	advisor_chief_window_update_health(window)
	advisor_chief_window_update_religion(window)
	advisor_chief_window_update_finance(window)
	advisor_chief_window_update_crime(window)
	advisor_chief_window_update_military(window)
	advisor_chief_window_update_kingdom(window)
	advisor_chief_window_update_nilometr(window)

	window.chief_report_list.clear()
	for (var i = 0; i < advisor_chief_window._chief_report_rows.length; i++) {
		window.chief_report_list.add_item("", i)
	}
}

[es=(advisor_chief_window, init)]
function advisor_chief_window_on_init(window) {
	advisor_chief_window_fill_report_rows(window)
	advisors_toolbar_refresh(window, ADVISOR_CHIEF)
}
