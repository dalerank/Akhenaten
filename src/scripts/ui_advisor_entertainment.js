log_info("akhenaten: ui advisor entertainment started")

function advisor_entertainment_advice_index() {
	var miss = city.houses.missing
	if (miss.entertainment > miss.more_entertainment) {
		return 3
	}
	if (!miss.more_entertainment) {
		return city.avg_coverage.average_entertainment ? 1 : 0
	}
	var vns = city.entertainment.venue_needing_shows
	if (vns) {
		return 3 + vns
	}
	return 2
}

function advisor_entertainment_coverage_text(coverage) {
	if (coverage === 0) {
		return __loc(57, 7)
	}
	if (coverage >= 100) {
		return __loc(57, 18)
	}
	return __loc(57, 8 + ((coverage / 10) | 0))
}

function advisor_entertainment_row_descriptor(row) {
	var ent = city.entertainment
	var cov = city.coverage
	switch (row) {
		case 0:
			return { rowType: 0, venue: BUILDING_BOOTH, shows: ent.booth_shows, coverage: cov.booth, coeff: 400 }
		case 1:
			return { rowType: 1, venue: BUILDING_BANDSTAND, shows: ent.bandstand_shows, coverage: cov.bandstand, coeff: 700 }
		case 2:
			return { rowType: 2, venue: BUILDING_PAVILLION, shows: ent.pavilion_shows, coverage: cov.pavilion, coeff: 1200 }
		case 3:
			return { rowType: 3, venue: BUILDING_SENET_HOUSE, shows: ent.senet_house_plays, coverage: cov.senet_house, coeff: 0 }
		case 4:
			return { rowType: 9, venue: BUILDING_ZOO, shows: 0, coverage: 0, coeff: 0 }
		default:
			return null
	}
}

function advisor_entertainment_venues_list_on_render_item(p) {
	var d = advisor_entertainment_row_descriptor(p.user_data)
	if (!d) {
		return
	}

	var enabled = scenario.building_allowed(d.venue)
	var font = enabled ? FONT_NORMAL_WHITE_ON_DARK : FONT_NORMAL_YELLOW
	var na = __loc(58, 51)

	if (!enabled) {
		ui.label(__loc(58, 47 + d.rowType), [p.x + 10, p.y], font)
		ui.label(na, [p.x + 180, p.y], font)
		ui.label(na, [p.x + 260, p.y], font)
		ui.label(na, [p.x + 310, p.y], font)
		ui.label(__loc(57, 7), [p.x + 460, p.y], font)
		return
	}

	var actCount = city.count_active_buildings(d.venue)
	ui.label(__loc(58, 47 + d.rowType), [p.x + 10, p.y], font)
	ui.label(String(actCount), [p.x + 180, p.y], font)
	ui.label(String(d.shows), [p.x + 260, p.y], font)
	ui.label((d.coeff * actCount) + " " + __loc(58, 5), [p.x + 310, p.y], font)
	ui.label(advisor_entertainment_coverage_text(d.coverage), [p.x + 460, p.y], font)
}

[es=advisor_window]
advisor_entertainment_window {
	advisor: ADVISOR_ENTERTAINMENT
	allow_rmb_goback : true
	help_id: "message_overseer_diversions"
	ui : baseui(advisor_window_base, {
		advisor_area             : dummy({ pos [(sw(0) - px(40)) / 2, (sh(0) - px(30)) / 2]
			ui : {
				background    : outer_panel({size:[40, 20] })
				title         : text({pos: [60, 12], text:[58, 0], font : FONT_LARGE_BLACK_ON_LIGHT })
				advisor_icon  : image({pack:PACK_GENERAL, id:128, offset:8, pos:[10, 10] }),

				working       : text({text:[58, 1], pos:[180, 42], font:FONT_NORMAL_BLACK_ON_LIGHT}),
				stages        : text({text:[58, 55], pos:[180, 56], font:FONT_NORMAL_BLACK_ON_LIGHT}),
				shows         : text({text:[58, 2], pos:[280, 56], font:FONT_NORMAL_BLACK_ON_LIGHT}),
				can_entertain : text({text:[58, 3], pos:[340, 56], font:FONT_NORMAL_BLACK_ON_LIGHT}),
				city_coverage : text({text:[58, 4], pos:[470, 56], font:FONT_NORMAL_BLACK_ON_LIGHT}),

				venues_list   : scrollable_list({
					pos: [32, 70]
					size: [36, 9]
					view_items: 5
					buttons_size_y: 25
					buttons_margin_x: 0
					buttons_margin_y: 10
					text_padding_x: 0
					text_padding_y: 0
					draw_scrollbar_always: false
					draw_paneling: true
					onrender_item: advisor_entertainment_venues_list_on_render_item
				}),

				advice        : multiline({ pos[30, 230], size:[px(37), 208], wrap:512, font:FONT_NORMAL_BLACK_ON_LIGHT }),
			}
		})
	})
}

[es=(advisor_entertainment_window, init)]
function advisor_entertainment_window_init(window) {
	var list = window.venues_list
	list.clear()
	var i
	for (i = 0; i < 5; i++) {
		list.add_item("venue", i)
	}

	window.advice.text = __loc(58, 7 + advisor_entertainment_advice_index())

	advisors_toolbar_refresh(window, ADVISOR_ENTERTAINMENT)
}