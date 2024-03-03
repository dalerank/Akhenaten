log_info("akhenaten: figures info started")

figure_fireman = {
	animations : {
		walk : { pos : [0, 0], anim_id: IMG_FIREMAN },
		death : { pos : [0, 0], anim_id: IMG_FIREMAN_DEATH },
    fight_fire : { pos : [0, 0], anim_id: IMG_FIREMAN_FIGHT_FIRE, max_frames: 36 }
  },
  sounds : {
  	fighting_fire : {sound:"fireman_e01.wav", group: 242, text:0},
 		going_to_fire : {sound:"fireman_e02.wav", group: 242, text:1},
 		fighting_fire_also : {sound:"fireman_e03.WAV", group: 242, text:2},
 		desease_can_start_at_any_moment : {sound:"fireman_g01.WAV", group: 242, text:3},
 		no_food_in_city : {sound:"fireman_g02.WAV", group: 242, text:4},
 		city_not_safety_workers_leaving : {sound:"fireman_g03.WAV", group: 242, text:5},
 		need_workers : {sound:"fireman_g04.WAV", group: 242, text:6},
 		hight_fire_level : {sound:"fireman_g05.WAV", group: 242, text:7},
 		gods_are_angry : {sound:"fireman_g06.WAV", group: 242, text:8},
 		need_more_workers : {sound:"fireman_g07.WAV", group: 242, text:9},
 		low_entertainment : {sound:"fireman_g08.WAV", group: 242, text:10},
 		gods_are_pleasures : {sound:"fireman_g09.WAV", group: 242, text:11},
 		city_is_amazing : {sound:"fireman_g10.wav", group: 242, text:12},
  }
}

figure_water_carrier = {
	animations : {
		walk : { pos : [0, 0], anim_id: IMG_WATER_CARRIER },
		death : { pos : [0, 0], anim_id: IMG_WATER_CARRIER_DEATH },
  },
  sounds : {
  	desease_can_start_at_any_moment : {sound: "water_g01.wav", group:237, text:0},
    no_food_in_city : {sound: "water_g02.wav", group:237, text:1},
    city_have_no_army : {sound: "water_g03.wav", group:237, text:2},
    need_workers : {sound: "water_g04.wav", group:237, text:3},
    gods_are_angry : {sound: "water_g05.wav", group:237, text:4},
    city_is_bad : {sound: "water_g06.wav", group:237, text:5},
    much_unemployments : {sound: "water_g07.wav", group:237, text:6},
    low_entertainment : {sound: "water_g08.wav", group:237, text:7},
    city_is_good : {sound: "water_g09.wav", group:237, text:8},
    city_is_amazing : {sound: "water_g10.wav", group:237, text:9},
  }
}

figure_priest = {
	animations : {
		osiris_walk : { pos : [0, 0], anim_id: IMG_PRIEST_OSIRIS },
		osiris_death : { pos : [0, 0], anim_id: IMG_PRIEST_OSIRIS_DEATH },
		ra_walk : { pos : [0, 0], anim_id: IMG_PRIEST_RA },
		ra_death : { pos : [0, 0], anim_id: IMG_PRIEST_RA_DEATH },
		ptah_walk : { pos : [0, 0], anim_id: IMG_PRIEST_PTAH },
		ptah_death : { pos : [0, 0], anim_id: IMG_PRIEST_PTAH_DEATH },
		seth_walk : { pos : [0, 0], anim_id: IMG_PRIEST_SETH },
		seth_death : { pos : [0, 0], anim_id: IMG_PRIEST_SETH_DEATH },
		bast_walk : { pos : [0, 0], anim_id: IMG_PRIEST_BAST, max_frames:12 },
		bast_death : { pos : [0, 0], anim_id: IMG_PRIEST_BAST_DEATH },
  },
}

figure_ostrich = {
	animations : {
		idle : { pos : [0, 0], anim_id: ANIM_OSTRICH_IDLE, max_frames:8 },
		eating : { pos : [0, 0], anim_id: ANIM_OSTRICH_EATING, max_frames:7 },
		walk : { pos : [0, 0], anim_id: ANIM_OSTRICH_WALK, max_frames:12 },
		death : { pos : [0, 0], anim_id: ANIM_OSTRICH_DEATH, max_frames:8 },
	}
}

figure_immigrant = {
	animations : {
		swim : { pos : [0, 0], anim_id: ANIM_FERRY_BOAT, max_frames:4, duration:4 },
	},
	sounds : {
		i_need_here: {sound:"immigrant_e01.wav", group: 202, text:0},
 		work_for_all : {sound:"immigrant_e02.wav", group: 202, text:1},
 		cheap_food : {sound:"immigrant_e03.wav", group: 202, text:2},
	}
}

figure_worker = {
	animations : {
		work : { pos : [0, 0], anim_id: IMG_WORKER_AKNH_WORK, max_frames:12 },
	}
}

figure_physician = {
	animations : {
		walk : { pos : [0, 0], anim_id: ANIM_DOCTOR_WALK, max_frames:12 },
		death : { pos : [0, 0], anim_id: ANIM_DOCTOR_DEATH, max_frames:8 },
	},
	sounds : {
		desease_can_start_at_any_moment : {sound:"doctor_e01.wav", group: 239, text:1},
    city_has_low_health : {sound:"doctor_g01.wav", group: 239, text:1},
    no_food_in_city : {sound:"doctor_g02.wav", group: 239, text:2},
    city_have_no_army : {sound:"doctor_g03.wav", group: 239, text:3},
    need_workers : {sound:"doctor_g04.wav", group: 239, text:4},
    gods_are_angry : {sound:"doctor_g05.wav", group: 239, text:5},
    gods_are_pleasures : {sound:"doctor_g06.wav", group: 239, text:6},
    no_job_in_city : {sound:"doctor_g07.wav", group: 239, text:7},
    low_entertainment : {sound:"doctor_g08.wav", group: 239, text:8},
    all_good_in_city : {sound:"doctor_g09.wav", group: 239, text:9},
    city_very_healthy : {sound:"doctor_g10.wav", group: 239, text:10},
	}
}

figure_architect = {
	animations : {
		walk : { pos : [0, 0], anim_id: ANIM_ARCHITECT_WALK, max_frames:12 },
		death : { pos : [0, 0], anim_id: ANIM_ARCHITECT_DEATH, max_frames:8 },
	},
	sounds : {
		extreme_damage_level: {sound:"engineer_e01.wav", group: 243, text:0},
    i_am_works: {sound:"engineer_e02.wav", group: 243, text:1},
    high_damage_level: {sound:"engineer_g01.wav", group: 243, text:2},
    no_food_in_city: {sound:"engineer_g02.wav", group: 243, text:3},
    city_not_safety: {sound:"engineer_g03.wav", group: 243, text:4},
    need_more_workers: {sound:"engineer_g04.wav", group: 243, text:5},
    gods_are_angry: {sound:"engineer_g05.wav", group: 243, text:6},
    city_has_bad_reputation: {sound:"engineer_g06.wav", group: 243, text:7},
    city_is_good: {sound:"engineer_g07.wav", group: 243, text:7},
    low_entertainment: {sound:"engineer_g08.wav", group: 243, text:8},
    city_is_bad: {sound:"engineer_g09.wav", group: 243, text:9},
    city_is_amazing: {sound:"engineer_g10.wav", group: 243, text:10},
	}
}

figure_market_buyer = {
	animations : {
		walk : { pos : [0, 0], anim_id: ANIM_MARKET_BUYER_WALK, max_frames:12 },
	},
	sounds : {
		goto_store : {sound:"mkt_buyer_e01.wav", group:244, text:0 },
    back_to_market : {sound:"mkt_buyer_e02.wav", group:244, text:0 },
    city_has_low_health : {sound:"mkt_buyer_g01.wav", group:244, text:0 },
    no_food_in_city : {sound:"mkt_buyer_g02.wav", group:244, text:0 },
    city_have_no_army : {sound:"mkt_buyer_g03.wav", group:244, text:0 },
    much_unemployments : {sound:"mkt_buyer_g04.wav", group:244, text:0 },
    gods_are_angry : {sound:"mkt_buyer_g05.wav", group:244, text:0 },
    city_is_bad_reputation : {sound:"mkt_buyer_g06.wav", group:244, text:0 },
    too_much_unemployments : {sound:"mkt_buyer_g07.wav", group:244, text:0 },
    low_entertainment : {sound:"mkt_buyer_g08.wav", group:244, text:0 },
    city_is_good : {sound:"mkt_buyer_g09.wav", group:244, text:0 },
    city_is_amazing : {sound:"mkt_buyer_g10.wav", group:244, text:0 },
	}
}

figure_delivery_boy = {
	animations : {
		walk : { pos : [0, 0], anim_id: ANIM_DELIVERY_BOY_WALK, max_frames:12 },
		death : { pos : [0, 0], anim_id: ANIM_DELIVERY_BOY_DEATH, max_frames:8 },
	},
	sounds : {
		those_baskets_too_heavy : {sound: "marketboy_e01.wav", group:221, text: 0},
    i_works_all_day : {sound: "marketboy_e02.wav", group:221, text: 1},
    upon_ill_be_market_owner : {sound: "marketboy_e03.wav", group:221, text: 2},
	}
}

figure_cartpusher = {
	animations : {
		walk : { pos : [0, 0], anim_id: ANIM_CARTPUSHER_WALK, max_frames:12 },
	}
}

figure_storageyard_cart = {
	animations : {
		walk : { pos : [0, 0], anim_id: ANIM_CARTPUSHER_WALK, max_frames:12 },
	}
}

figure_trade_ship = {
	animations : {
		walk : { pos : [0, 0], anim_id: ANIM_TRADER_SHIP_WALK, max_frames:3 },
		idle : { pos : [0, 0], anim_id: ANIM_TRADER_SHIP_IDLE, max_frames:1 },
	}
}

figure_emigrant = {
	animations : {
		walk : { pos : [0, 0], anim_id: ANIM_EMIGRANT_WALK, max_frames:12 },
		death : { pos : [0, 0], anim_id: ANIM_EMIGRANT_DEATH, max_frames:8 },
	},
	sounds : {
		no_job_in_city : {sound:"emigrant_e01.wav", group: 203, text:0},
    no_food_in_city : {sound:"emigrant_e02.wav", group: 203, text:1},
    tax_too_high : {sound:"emigrant_e03.wav", group: 203, text:2},
    salary_too_low : {sound:"emigrant_e04.wav", group: 203, text:3},
    no_house_for_me : {sound:"emigrant_e05.wav", group: 203, text:4},
	}
}

figure_sled = {
	animations : {
		walk : { pos : [0, 0], anim_id: IMG_BIGSLED_EMPTY, max_frames:1 },
	}
}

figure_herbalist = {
	animations : {
		walk : { pos : [0, 0], anim_id: ANIM_HERBALIST_WALK, max_frames:12 },
		death : { pos : [0, 0], anim_id: ANIM_HERBALIST_DEATH, max_frames:8 },
	},
	sounds : {
		no_threat_malaria_here : {sound:"apothecary_e02.wav", group: 241, text:1},
    have_malaria_risk_here : {sound:"apothecary_e03.wav", group: 241, text:2},
	}
}

figure_dancer = {
	animations : {
		walk : { pos : [0, 0], anim_id: ANIM_DANCER_WALK, max_frames:12 },
		death : { pos : [0, 0], anim_id: ANIM_DANCER_DEATH, max_frames:8 },
	},
	sounds : {
		i_like_festivals : {sound:"dancer_e01.wav", group:228, text:0},
    desease_can_start_at_any_moment : {sound:"dancer_g01.wav", group:228, text:1},
    no_food_in_city : {sound:"dancer_g02.wav", group:228, text:2},
    city_not_safety_workers_leaving : {sound:"dancer_g03.wav", group:228, text:3},
    need_workers : {sound:"dancer_g04.wav", group:228, text:4},
    gods_are_angry : {sound:"dancer_g05.wav", group:228, text:5},
    city_is_bad : {sound:"dancer_g06.wav", group:228, text:6},
    much_unemployments : {sound:"dancer_g07.wav", group:228, text:7},
    salary_too_low : {sound:"dancer_g08.wav", group:228, text:8},
    city_is_good : {sound:"dancer_g09.wav", group:228, text:9},
    city_is_amazing : {sound:"dancer_g10.wav", group:228, text:10},
	}
}

figure_musician = {
	animations : {
		walk : { pos : [0, 0], anim_id: ANIM_MUSICIAN_WALK, max_frames:12 },
		death : { pos : [0, 0], anim_id: ANIM_MUSICIAN_DEATH, max_frames:8 },
	},
	sounds : {
		i_like_festivals : { sound:"musician_e01.wav", group:229, text:0 },
 		city_heath_too_low : { sound:"musician_g01.wav", group:229, text:0 },
 		no_food_in_city : { sound:"musician_g02.wav", group:229, text:0 },
 		city_not_safety_workers_leaving : { sound:"musician_g03.wav", group:229, text:0 },
 		need_workers : { sound:"musician_g04.wav", group:229, text:0 },
 		gods_are_angry : { sound:"musician_g05.wav", group:229, text:0 },
 		city_is_bad_reputation : { sound:"musician_g06.wav", group:229, text:0 },
 		much_unemployments : { sound:"musician_g07.wav", group:229, text:0 },
 		no_entertainment_need : { sound:"musician_g08.wav", group:229, text:0 },
 		city_not_bad : { sound:"musician_g09.wav", group:229, text:0 },
 		city_is_good : { sound:"musician_g10.wav", group:229, text:0 },
	}
}

figure_juggler = {
	animations : {
		walk : { pos : [0, 0], anim_id: ANIM_JUGGLER_WALK, max_frames:12 },
		death : { pos : [0, 0], anim_id: ANIM_JUGGLER_DEATH, max_frames:8 },
	},
	sounds : {
		i_like_festivals : {sound:"juggler_e01.wav", group: 230, text:0 },
    disease_in_city : {sound:"juggler_g01.wav", group: 230, text:0 },
    city_low_sentiment : {sound:"juggler_g02.wav", group: 230, text:0 },
    city_not_safety_workers_leaving : {sound:"juggler_g03.wav", group: 230, text:0 },
    salary_too_low : {sound:"juggler_g04.wav", group: 230, text:0 },
    gods_are_angry : {sound:"juggler_g05.wav", group: 230, text:0 },
    city_verylow_sentiment : {sound:"juggler_g06.wav", group: 230, text:0 },
    much_unemployments : {sound:"juggler_g07.wav", group: 230, text:0 },
    low_entertainment : {sound:"juggler_g08.wav", group: 230, text:0 },
    city_is_good : {sound:"juggler_g09.wav", group: 230, text:0 },
    city_is_amazing : {sound:"juggler_g10.wav", group: 230, text:0 },
	}
}

figure_market_trader = {
	animations : {
		walk : { pos : [0, 0], anim_id: ANIM_HERBALIST_WALK, max_frames:12 },
		death : { pos : [0, 0], anim_id: ANIM_HERBALIST_DEATH, max_frames:8 },
	},
	sounds : {
		goods_are_finished : {sound:"mkt_seller_e01.wav", group:245, text:0},
 	  we_are_selling_goods : {sound:"mkt_seller_e02.wav", group:245, text:0},
	}
}

figure_tax_collector = {
	animations : {
		walk : { pos : [0, 0], anim_id: IMG_BIGSLED_EMPTY, max_frames:1 },
	},
	sounds : {
		need_more_tax_collectors: {sound: "taxman_e01.wav", group: 245, text:0},
    high_taxes: {sound: "taxman_e02.wav", group: 245, text:1},
    much_pooh_houses: {sound: "taxman_e03.wav", group: 245, text:2},
    desease_can_start_at_any_moment: {sound: "taxman_g01.wav", group: 245, text:3},
    no_food_in_city: {sound: "taxman_g02.wav", group: 245, text:4},
    city_have_no_army: {sound: "taxman_g03.wav", group: 245, text:5},
    need_workers: {sound: "taxman_g04.wav", group: 245, text:6},
    gods_are_angry: {sound: "taxman_g05.wav", group: 245, text:7},
    city_is_bad: {sound: "taxman_g06.wav", group: 245, text:8},
    much_unemployments: {sound: "taxman_g07.wav", group: 245, text:9},
    low_entertainment: {sound: "taxman_g08.wav", group: 245, text:10},
    city_is_good: {sound: "taxman_g09.wav", group: 245, text:11},
    city_is_amazing: {sound: "taxman_g10.wav", group: 245, text:12},
	}
}
