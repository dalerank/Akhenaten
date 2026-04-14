log_info("akhenaten: ui advisor religion started")

function advisor_religion_advice_index() {
	var leastHappy = city.gods.least_happy()
	var demands = city.houses
	var reqRel = city.houses.requiring.religion
	if (leastHappy >= 0 && leastHappy < gods.length && city.gods.at(leastHappy).wrath_bolts > 4) {
		return 6 + leastHappy
	}
	if (demands.religion === 1) {
		return reqRel ? 1 : 0
	}
	if (demands.religion === 2) {
		return 2
	}
	if (demands.religion === 3) {
		return 3
	}
	if (!reqRel) {
		return 4
	}
	if (leastHappy >= 0 && leastHappy < gods.length) {
		return 6 + leastHappy
	}
	return 5
}

var advisor_religion_bolt_angel_images = null
function advisor_religion_get_bolt_angel_images() {
	if (!advisor_religion_bolt_angel_images) {
		advisor_religion_bolt_angel_images = {
			bolt: get_image({ pack: PACK_GENERAL, id: 129, offset: 34 }),
			angel: get_image({ pack: PACK_GENERAL, id: 129, offset: 33 })
		}
	}
	return advisor_religion_bolt_angel_images
}

function advisor_religion_gods_list_on_render_item(p) {
	if (!game.gods_enabled) {
		return
	}

	var row = p.user_data
	var g = gods[row]
	var gs = city.gods.at(g.type)
	var st = gs.status
	var font = (st === 0) ? FONT_NORMAL_WHITE_ON_DARK : FONT_NORMAL_YELLOW
	var lx = p.x
	var ly = p.y
	var dash = "-"

	ui.label(__loc(157, g.type), [lx + 2, ly], font)
	ui.label(__loc(187, st), [lx + 62, ly], font)
	ui.label(dash, [lx + 162, ly], font)
	ui.label(dash, [lx + 227, ly], font)
	ui.label(dash, [lx + 292, ly], font)
	ui.label(dash, [lx + 352, ly], font)
	ui.label(dash, [lx + 422, ly], font)
	ui.label(__loc(158, g.type), [lx + 2, ly + 20], FONT_NORMAL_BLACK_ON_DARK)

	if (st === 0) {
		if (p.hover) {
			ui.border({ x: p.x + 4, y: p.y - 4 }, { x: p.sizex - 8, y: p.sizey - 4 }, 0, COLOR_TOOLTIP_BORDER, UiFlags_None)
		}
		return
	}

	var bcount = dash
	if (scenario.building_allowed(g.complex_type)) {
		bcount = String(city.count_active_buildings(g.complex_type))
	}
	var activeTemples = city.count_active_buildings(g.temple_type)
	var totalTemples = city.count_total_buildings(g.temple_type)

	ui.label(bcount, [lx + 162, ly], font)
	ui.label(activeTemples + " (" + totalTemples + ")", [lx + 227, ly], font)
	ui.label(String(city.count_active_buildings(g.shrine_type)), [lx + 292, ly], font)
	ui.label(String(gs.months_since_festival), [lx + 352, ly], font)
	ui.label(__loc(59, 20 + ((gs.happiness / 10) | 0)), [lx + 422, ly], font)

	var imgs = advisor_religion_get_bolt_angel_images()
	var boltY = ly - 3
	var boltX = lx + 502
	var wrath = gs.wrath_bolts
	var i = 0
	for (i = 0; i < ((wrath / 20) | 0); i++) {
		ui.image(imgs.bolt, { x: boltX + i * 10, y: boltY })
	}
	var happy = gs.happy_angels
	var j = 0
	for (j = 0; j < ((happy / 20) | 0); j++) {
		ui.image(imgs.angel, { x: boltX + j * 10, y: boltY })
	}

	if (p.hover) {
		ui.border({ x: p.x + 4, y: p.y - 4 }, { x: p.sizex - 8, y: p.sizey - 4 }, 0, COLOR_TOOLTIP_BORDER, UiFlags_None)
	}
}

[es=advisor_window]
advisor_religion_window = {
	advisor: ADVISOR_RELIGION
	needs_sync : true
	ui : {
		background : outer_panel({size:[40, 27] }),
		title : text({pos: [60, 12], text: {group:59, id:0}, font : FONT_LARGE_BLACK_ON_LIGHT }),
		advisor_icon : image({pack:PACK_GENERAL, id:128, offset:9, pos:[10, 10] }),
		nogods_text : text({pos: [60, 256], text: {group:59, id:43}, wrap:520, font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true }),

		temple_header: { type : "text", pos: [180, 32], text: {group:59, id:5}, font : FONT_NORMAL_BLACK_ON_LIGHT },
		complex_header: { type : "text", pos: [170, 46], text: {group:59, id:2}, font : FONT_NORMAL_BLACK_ON_LIGHT },
		tempe_header: { type : "text", pos: [250, 46], text: {group:59, id:1}, font : FONT_NORMAL_BLACK_ON_LIGHT },
		shrine_header: { type : "text", pos: [320, 46], text: {group:28, id:150}, font : FONT_NORMAL_BLACK_ON_LIGHT },
		months_header: { type : "text", pos: [390, 18], text: {group:59, id:6}, font : FONT_NORMAL_BLACK_ON_LIGHT },
		since_header: { type : "text", pos: [400, 32], text: {group:59, id:8}, font : FONT_NORMAL_BLACK_ON_LIGHT },
		fest_header: { type : "text", pos: [390, 46], text: {group:59, id:7}, font : FONT_NORMAL_BLACK_ON_LIGHT },
		mood_header: { type : "text", pos: [460, 46], text: {group:59, id:3}, font : FONT_NORMAL_BLACK_ON_LIGHT },

		inner_panel : { type : "inner_panel", pos:[32, 60], size:[36, 13] },

		gods_list : scrollable_list({
			pos: [38, 66]
			size: [35, 13]
			view_items: 5
			buttons_size_y: 40
			buttons_margin_x: 0
			buttons_margin_y: 0
			text_padding_x: 0
			text_padding_y: 0
			draw_scrollbar_always: false
			draw_paneling: false
			onrender_item: advisor_religion_gods_list_on_render_item
		})

		advice_text : { type : "text", pos: [60, 273], wrap:512, font : FONT_NORMAL_BLACK_ON_LIGHT, multiline:true },
		fest_inner_panel : { type : "inner_panel", pos:[48, 252 + 68], size:[34, 6] },
		fest_icon : { type : "image", pack:PACK_UNLOADED, id:21, offset:15, pos:[460, 255 + 68] },
		fest_months_last : { type : "label", pos:[112, 328], font:FONT_NORMAL_WHITE_ON_DARK},
		planed_festival : { type : "text", pos: [102, 284 + 68], font : FONT_NORMAL_BLACK_ON_DARK, align:"center" },
		hold_festival_btn : { type:"generic_button", pos:[102, 278 + 68], size:[300, 24], onclick: advisor_religion_window_hold_festival },
		festival_advice : { type : "text", pos: [56, 305 + 68], wrap:400, font : FONT_NORMAL_WHITE_ON_DARK, multiline:true },
	}
}

function advisor_religion_window_hold_festival() {
	if (city.count_total_buildings(BUILDING_FESTIVAL_SQUARE) === 0) {
		ui.show_ok("#popup_dialog_no_festival_square")
		return
	}

	if (!city.festival.is_planned) {
		hold_festival_window.show(false, function() {
			advisor_religion_window.needs_sync = true
		})
	}
}

[es=(advisor_religion_window, init)]
function advisor_religion_window_init(window) {
	if (!game.gods_enabled) {
		window.nogods_text.enabled = true
		window.gods_list.clear()
		return
	}

	window.nogods_text.enabled = false
	var list = window.gods_list
	list.clear()
	for (var gi = 0; gi < gods.length; gi++) {
		list.add_item("god", gi)
	}
	__city_religion_calculate_least_happy_god()

	advisor_religion_window.needs_sync = true
}

[es=(advisor_religion_window, draw_background)]
function advisor_religion_window_draw_background(window) {
	if (!advisor_religion_window.needs_sync) {
		return
	}

	var fest = city.festival
	var m = fest.months_since_festival
	window.fest_months_last.text = String(m) + " " + __loc(8, 5) + " " + __loc(58, 15)

	var festivalTextIffs = [0, 10, 20, 31]
	if (city.festival.is_planned) {
		var size = __city_festival_selected_size()
		var monthsLeft = __city_festival_months_till_next()
		var plannedMonth = (__game_simtime_month() + monthsLeft) % 12
		var baseIdx = (size >= 0 && size < festivalTextIffs.length) ? festivalTextIffs[size] : festivalTextIffs[festivalTextIffs.length - 1]

		window.hold_festival_btn.enabled = false
		window.planed_festival.text = __loc(58, 34) + " " + __loc(160, plannedMonth)
		window.festival_advice.text = __loc(295, baseIdx + monthsLeft - 1)
	} else {
		window.hold_festival_btn.enabled = true
		window.hold_festival_btn.text = __loc(58, 16)
		window.festival_advice.text = __loc(58, 18 + city.festival.get_advice())
	}

	window.advice_text.text = __loc(59, 9 + advisor_religion_advice_index())
	advisor_religion_window.needs_sync = false
}
