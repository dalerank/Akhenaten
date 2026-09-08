log_info("akhenaten: figure trade_caravan started")

figure_trade_caravan {
	animations {
		walk { pack:PACK_SPR_AMBIENT, id:20, max_frames:12 }
		death { pack:PACK_SPR_AMBIENT, id:21, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_TRADE_CARAVAN }
	}

	sounds {
		trader_city_not_trades { sound:"caravan_e01.wav", text: "#trader_city_not_trades" }
		trader_buy_for_less_sell_for_more { sound:"caravan_e02.wav", text: "#trader_buy_for_less_sell_for_more" }
		trader_its_my_life { sound:"caravan_e03.wav", text: "#trader_its_my_life" }
		trader_i_ll_be_a_hero { sound:"caravan_e04.wav", text: "#trader_i_ll_be_a_hero" }
		trader_you_talk_a_fine_bargain { sound:"caravan_e05.wav", text: "#trader_you_talk_a_fine_bargain" }
	}

	category : figure_category_citizen
	max_damage : 20
	wait_ticks_after_create : 10
	terrain_usage : TERRAIN_USAGE_PREFER_ROADS
	max_capacity : 800
	min_capacity : 100
	capacity_random : 701
}

[es=(figure_trade_caravan, setup_phrase)]
function figure_trade_caravan_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	var trade = f.trade
	var state = f.action_state
	var key = "trader_its_my_life"

	if (state == ACTION_3_TRADE_CARAVAN_LEAVING) {
		key = (trade && trade.has_traded) ? "trader_you_talk_a_fine_bargain" : "trader_city_not_trades"
	} else if (state == ACTION_2_TRADE_CARAVAN_TRADING) {
		if (trade && trade.can_buy_at_destination) {
			key = "trader_buy_for_less_sell_for_more"
		} else if (trade && trade.can_sell_at_destination) {
			key = "trader_you_talk_a_fine_bargain"
		} else {
			key = "trader_its_my_life"
		}
	} else if (state == ACTION_1_TRADE_CARAVAN_ARRIVING) {
		key = "trader_i_ll_be_a_hero"
	}

	figure_apply_phrase(f, key)
}
