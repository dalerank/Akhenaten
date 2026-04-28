log_info("akhenaten: ui advisor ratings started")

function advisor_ratings_draw_column(basePos, value, openPlay, goal) {
	var enabled = !openPlay && goal
	var hasReached = !enabled || value >= goal
	var valueToDraw = ((value * 0.75) | 0)
	if (game_features.gameui_complete_ratings_columns) {
		if (hasReached && value < 25) {
			valueToDraw = 25
		}
	}
	var imgBase = get_image({ pack: PACK_GENERAL, id: 189, offset: 0 })
	var imgBody = get_image({ pack: PACK_GENERAL, id: 189, offset: 1 })
	var imgTop = get_image({ pack: PACK_GENERAL, id: 189, offset: 2 })
	var px = basePos.x
	var py = basePos.y
	var y = imgBase.height
	ui.image(imgBase, [px - 4, py + y])
	var i
	for (i = 0; i < 2 * valueToDraw; i++) {
		y = y - 1
		ui.image(imgBody, [px + 11, py + y])
	}
	if (hasReached) {
		ui.image(imgTop, [px - 6, py + y - 50])
	}
}

function advisor_ratings_draw_button_values(elm, value, goal) {
	var openPlay = scenario.is_open_play
	var enabled = !openPlay && goal

	ui.label_ex(String(value), [elm.pos.x, elm.pos.y + 22], FONT_LARGE_BLACK_ON_LIGHT, UiFlags_AlignCentered, elm.size.x)
	ui.label_ex(String(enabled ? goal : 0) + " " + __loc(53, 5), [elm.pos.x, elm.pos.y + 42], FONT_NORMAL_BLACK_ON_LIGHT, UiFlags_AlignCentered, elm.size.x)
}

function advisor_ratings_draw_rating_button(elm, value, goal) {
	advisor_ratings_draw_button_values(elm, value, goal)
	advisor_ratings_draw_column({x: elm.pos.x + 30, y: elm.pos.y - 63}, value, scenario.is_open_play, goal)
}

[es=(advisor_ratings_window, ondraw_culture_button)]
function advisor_ratings_ondraw_culture_button(window) {
	advisor_ratings_draw_rating_button(window.rating_culture, city.rating.culture, city.winning.culture.goal)
}

[es=(advisor_ratings_window, ondraw_prosperity_button)]
function advisor_ratings_ondraw_prosperity_button(window) {
	advisor_ratings_draw_rating_button(window.rating_prosperity, city.rating.prosperity, city.winning.prosperity.goal)
}

[es=(advisor_ratings_window, ondraw_monument_button)]
function advisor_ratings_ondraw_monument_button(window) {
	advisor_ratings_draw_rating_button(window.rating_monument, city.rating.monument, city.winning.monuments.goal)
}

[es=(advisor_ratings_window, ondraw_kingdom_button)]
function advisor_ratings_ondraw_kingdom_button(window) {
	advisor_ratings_draw_rating_button(window.rating_kingdom, city.rating.kingdom, city.winning.kingdom.goal)
}

function advisor_ratings_select_button(window, button) {
	window.rating_culture.selected = false
	window.rating_prosperity.selected = false
	window.rating_monument.selected = false
	window.rating_kingdom.selected = false
	button.selected = true
}

[es=(advisor_ratings_window, select_culture)]
function advisor_ratings_select_culture(window) {
	var expl = city.rating.get_culture_explanation()
	window.advice_header.text = __loc(53, 1)
	advisor_ratings_select_button(window, window.rating_culture)
	window.advice_text.text = (city.rating.culture <= 90) ? __loc(53, 9 + expl) : __loc(53, 50)
}

[es=(advisor_ratings_window, select_prosperity)]
function advisor_ratings_select_prosperity(window) {
	var expl = city.rating.get_prosperity_explanation()
	advisor_ratings_select_button(window, window.rating_prosperity)
	window.advice_header.text = __loc(53, 2)
	window.advice_text.text = (city.rating.prosperity <= 90) ? __loc(53, 16 + expl) : __loc(53, 51)
}

[es=(advisor_ratings_window, select_monument)]
function advisor_ratings_select_monument(window) {
	var expl = city.rating.get_monument_explanation()
	advisor_ratings_select_button(window, window.rating_monument)
	window.advice_header.text = __loc(53, 3)
	window.advice_text.text = (city.rating.monument <= 90) ? __loc(53, 41 + expl) : __loc(53, 52)
}

[es=(advisor_ratings_window, select_kingdom)]
function advisor_ratings_select_kingdom(window) {
	var expl = city.rating.get_kingdom_explanation()
	advisor_ratings_select_button(window, window.rating_kingdom)
	window.advice_header.text = __loc(53, 4)
	window.advice_text.text = (city.rating.kingdom <= 90) ? __loc(53, 27 + expl) : __loc(53, 53)
}

[es=advisor_window]
advisor_ratings_window {
    advisor: ADVISOR_RATINGS
    allow_rmb_goback : true
    help_id: "message_overseer_ratings"
    ui : baseui(advisor_window_base, {
		advisor_area             : dummy({ pos [(sw(0) - px(40)) / 2, (sh(0) - px(30)) / 2], size:[px(40), px(27)]
            ui : {
				background       : outer_panel({size:[40, 27]})
				background_image : image({pack:PACK_UNLOADED, id:2, pos:[60, 38]})

				rating_culture   : button({pos:[80, 276], align:"xcenter", size:[120, 60], tooltip:[68, 104], onclick_event: "select_culture", ondraw_event: "ondraw_culture_button"}),

				rating_prosperity: button({pos:[200, 276], align:"xcenter", size:[120, 60], tooltip:[68, 105], onclick_event: "select_prosperity", ondraw_event: "ondraw_prosperity_button"}),

				rating_monument  : button({pos:[320, 276], align:"xcenter", size:[120, 60], tooltip:[68, 106], onclick_event: "select_monument", ondraw_event: "ondraw_monument_button"}),

				rating_kingdom   : button({pos:[440, 276], align:"xcenter", size:[120, 60], tooltip:[68, 107], onclick_event: "select_kingdom", ondraw_event: "ondraw_kingdom_button"}),

				inner_panel      : inner_panel({pos:[40, 340], size:[35, 5]}),
				advice_header    : text({pos:[68, 344], font: FONT_NORMAL_WHITE_ON_DARK}),
				advice_text      : text({pos:[68, 368], wrap:520, font: FONT_NORMAL_WHITE_ON_DARK, multiline:true}),
				advisor_icon     : image({pack:PACK_GENERAL, id:128, offset:3, pos:[10, 10]}),
				header_label     : label({font: FONT_LARGE_BLACK_ON_LIGHT, text:{group:53, id:0}, pos:[60, 17]}),
				population_label : label({pos:[300, 20], font: FONT_NORMAL_BLACK_ON_LIGHT}),

				button_help   : help_button({})
			}
		})
	})
}

[es=(advisor_ratings_window, init)]
function advisor_ratings_window_init(window) {
	advisor_ratings_select_culture(window)

	var caption = __loc(53, 7)
	if (city.winning.population.enabled && !scenario.is_open_play) {
		caption = __loc(53, 6) + String(city.winning.population.goal)
	}
	window.population_label.text = caption

	window.rating_culture.text = __loc(53, 1)
	window.rating_prosperity.text = __loc(53, 2)
	window.rating_monument.text = __loc(53, 3)
	window.rating_kingdom.text = __loc(53, 4)

	advisors_toolbar_refresh(window, ADVISOR_RATINGS)
}
