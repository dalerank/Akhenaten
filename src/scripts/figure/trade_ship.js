log_info("akhenaten: figure trade_ship started")

figure_trade_ship {
	animations {
		walk { pack:PACK_SPR_MAIN, id:123, max_frames:4, duration:4 }
		death { pack:PACK_SPR_MAIN, id:124, max_frames:8 }
		idle { pack:PACK_SPR_MAIN, id:125, max_frames:1, offset:0 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_TRADE_SHIP }
	}

	sounds {
		barge_have_no_place_for_dock { sound:"barge_e01.wav", text: "#barge_have_no_place_for_dock" }
		barge_docked_wait_for_dockpushers { sound:"barge_e02.wav", text: "#barge_docked_wait_for_dockpushers" }
		barge_city_not_trades { sound:"barge_e03.wav", text: "#barge_city_not_trades" }
		barge_i_like_to_trage { sound:"barge_e04.wav", text: "#barge_i_like_to_trage" }
		barge_amazing_trades { sound:"barge_e05.wav", text: "#barge_amazing_trades" }
	}

	category: figure_category_citizen
	max_damage : 250
	terrain_usage : TERRAIN_USAGE_ANY
	max_capacity : 1200
}

function figure_trade_ship_phrase_key(f) {
	var trade = f.trade
	var state = f.action_state

	// ACTION_115_TRADE_SHIP_LEAVING
	if (state == 115) {
		return (trade && trade.has_traded) ? "barge_amazing_trades" : "barge_city_not_trades"
	}

	// ACTION_112_TRADE_SHIP_MOORED
	if (state == 112) {
		var trading = trade ? trade.is_trading : 0
		if (trading == 1) { // TRADE_SHIP_BUYING
			return "barge_docked_wait_for_dockpushers"
		}
		if (trading == 2) { // TRADE_SHIP_SELLING
			return "barge_have_no_place_for_dock"
		}
		return "barge_city_not_trades"
	}

	return "barge_i_like_to_trage"
}

[es=(figure_trade_ship, setup_phrase)]
function figure_trade_ship_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_trade_ship_phrase_key(f))
}
