log_info("akhenaten: figure market_trader started")

figure_market_trader {
	overlay : OVERLAY_BAZAAR_ACCESS
	animations {
		walk { pack:PACK_SPR_MAIN, id:18, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:19, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_MARKET_TRADER }
	}

	sounds {
		goods_are_finished { sound:"mkt_seller_e01.wav", text: "#goods_are_finished" }
		we_are_selling_goods { sound:"mkt_seller_e02.wav", text: "#we_are_selling_goods" }
	}

	category: figure_category_citizen
	max_damage : 10
	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 384
	permission : epermission_market
	record_path : true
}

[es=(figure_market_trader, setup_phrase)]
function figure_market_trader_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	// ACTION_126_MARKET_TRADER_RETURNING / ACTION_126_ROAMER_RETURNING
	var key = (f.action_state == 126) ? "goods_are_finished" : "we_are_selling_goods"
	figure_apply_phrase(f, key)
}
