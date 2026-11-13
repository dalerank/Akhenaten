log_info("akhenaten: ui advisor chief started")

// OG window/advisor_comments.c advisor_comment_rules.
advisor_comment_rules {
	sentiment_low : 50
	sentiment_fair : 100
	migration_max_armed_figures : 3
	migration_newcomers_strong : 5
	migration_percentage_strong : 80
	employment_balanced_unemployment : 5
	employment_balanced_workers_needed : 5
	unemployment_urgent : 17
	unemployment_serious : 10
	unemployment_important : 5
	labor_shortage_urgent : 20
	labor_shortage_serious : 10
	food_stocks_low_percent : 50
	food_supply_plenty_percent : 150
	food_supply_enough_percent : 110
	food_supply_barely_enough_percent : 95
	food_supply_slightly_short_percent : 85
	food_supply_short_percent : 70
	angry_god_mood : 40
	very_angry_god_mood : 20
	happy_god_mood : 60
	thefts_many : 10
	thefts_several : 5
	thefts_some : 2
	requests_counted : 5
	requests_some_max : 2
	requests_several_max : 4
}

// OG window/advisor/chief.c row thresholds.
chief_advisor_rules {
	sentiment_white_from : 30
	sentiment_green_from : 50
	sentiment_cause_below : 50
	migration_max_armed_figures : 3
	migration_newcomers_strong : 5
	migration_percentage_strong : 80
	unemployment_urgent : 18
	unemployment_serious : 11
	unemployment_important : 6
	unemployment_tolerable : 1
	workers_needed_urgent : 21
	workers_needed_serious : 11
	workers_needed_important : 6
	employment_balanced_below : 6
	food_stocks_low_percent : 50
	food_supply_plenty_percent : 150
	food_supply_enough_percent : 110
	food_supply_barely_enough_percent : 95
	food_supply_slightly_short_percent : 85
	food_supply_short_percent : 70
	health_white_from : 20
	health_green_from : 30
	angry_god_mood : 30
	very_angry_god_mood : 20
	happy_god_mood : 70
	thefts_many : 10
	thefts_several : 5
	thefts_some : 2
	requests_counted : 5
	requests_some_max : 2
	requests_several_max : 4
	flood_quality_step : 20
}

[es=advisor_window]
advisor_chief_window {
	advisor: ADVISOR_CHIEF
	allow_rmb_goback : true
	help_id: "message_chief_overseer"
	ui : baseui(advisor_window_base, {
		advisor_area             : dummy({ pos [(sw(0) - px(40)) / 2, (sh(0) - px(30)) / 2], size:[px(40), px(27)]
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

				click_hint    : text({ pos:[60, 406], text:{group:61, id:218}, font: FONT_NORMAL_BLACK_ON_LIGHT }),
				button_help   : help_button({}),
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

function advisor_chief_push_wrapped_section_rows(bodyText, sectionTitle, font, topic) {
	advisor_chief_window._chief_report_rows.push({
		title: sectionTitle
		body: ""
		font: font
		bullet: true
		topic: topic
	})
	advisor_chief_push_body_rows(bodyText, font, topic)
}

function advisor_chief_report_on_render_item(p) {
	var rows = advisor_chief_window._chief_report_rows

	var row = rows[p.user_data]

	var wrapPx = Math.max(120, p.sizex - 42)

	if (row.title && row.title.length) {
		var img = get_image({ pack: PACK_GENERAL, id: 158 })
		ui.image(img, [p.x + 8, p.y + 4])
		ui.label(row.title, [p.x + 35, p.y + 3], FONT_NORMAL_WHITE_ON_DARK, UiFlags_None)
	}

	if (row.body && row.body.length) {
		ui.label(row.body, [p.x + 35, p.y + 3], row.font, UiFlags_None, wrapPx)
	}

	if (p.hover) {
		ui.border({ x: p.x + 4, y: p.y }, { x: p.sizex - 8, y: p.sizey }, 0, COLOR_TOOLTIP_BORDER, UiFlags_None)
	}
}

function advisor_chief_push_body_rows(bodyText, font, topic) {
	var lines = advisor_chief_wrap_lines(bodyText, advisor_chief_report_body_max_chars())
	var li
	for (li = 0; li < lines.length; li++) {
		advisor_chief_window._chief_report_rows.push({
			title: ""
			body: lines[li]
			font: font
			bullet: false
			topic: topic
		})
	}
}

// OG chief.c fonts: red / white / green on the dark panel.
function advisor_chief_tone_font(tone) {
	if (tone === ADVISOR_TONE_RED) {
		return FONT_NORMAL_YELLOW
	}
	if (tone === ADVISOR_TONE_WHITE) {
		return FONT_NORMAL_WHITE_ON_DARK
	}
	return FONT_NORMAL_BLACK_ON_DARK
}

function advisor_chief_row_text(row) {
	var text = __loc(61, row.text)
	if (row.cause_text >= 0) {
		text += " " + __loc(61, row.cause_text)
	}
	if (row.number_kind === CHIEF_NUMBER_PERCENT) {
		text += " " + row.number + "%"
	} else if (row.number_kind !== CHIEF_NUMBER_NONE) {
		text += " " + row.number
	}
	if (row.suffix_group >= 0) {
		text += " " + __loc(row.suffix_group, row.suffix_text)
	}
	return text
}

function advisor_chief_window_push_topic(topic) {
	var row = __chief_advisor_row(topic)
	var font = advisor_chief_tone_font(row.tone)
	advisor_chief_push_wrapped_section_rows(advisor_chief_row_text(row), __loc(61, topic + 1), font, topic)
	if (row.second_text >= 0) {
		advisor_chief_push_body_rows(__loc(61, row.second_text), FONT_NORMAL_BLACK_ON_DARK, topic)
	}
}

function advisor_chief_window_push_nilometer() {
	if (scenario.hide_nilometer) {
		return
	}
	advisor_chief_window_push_topic(ADVISOR_COMMENT_NILOMETER)
	if (!!game_features.gameui_enhanced_nilometer && floods_ui_should_show()) {
		advisor_chief_push_body_rows(floods_ui_format_phase(), FONT_NORMAL_BLACK_ON_DARK, ADVISOR_COMMENT_NILOMETER)
		advisor_chief_push_body_rows(floods_ui_format_last_line(), FONT_NORMAL_BLACK_ON_DARK, ADVISOR_COMMENT_NILOMETER)
	}
}

function advisor_chief_window_fill_report_rows(window) {
	advisor_chief_window._chief_report_rows = []
	for (var topic = ADVISOR_COMMENT_SENTIMENT; topic < ADVISOR_COMMENT_NILOMETER; topic++) {
		advisor_chief_window_push_topic(topic)
	}
	advisor_chief_window_push_nilometer()

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
