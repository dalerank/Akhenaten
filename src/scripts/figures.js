log_info("akhenaten: figures info started")

figure_fireman = {
	animations : {
		walk : { pos : [0, 0], anim_id: IMG_FIREMAN },
		death : { pos : [0, 0], anim_id: IMG_FIREMAN_DEATH },
    fight_fire : { pos : [0, 0], anim_id: IMG_FIREMAN_FIGHT_FIRE, max_frames: 36 }
  },
}

figure_water_carrier = {
	animations : {
		walk : { pos : [0, 0], anim_id: IMG_WATER_CARRIER },
		death : { pos : [0, 0], anim_id: IMG_WATER_CARRIER_DEATH },
  },
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

figure_architect = {
	animations : {
		walk : { pos : [0, 0], anim_id: IMG_ARCHITECT, max_frames:12 },
	}
}

figure_market_buyer = {
	animations : {
		walk : { pos : [0, 0], anim_id: ANIM_MARKET_BUYER_WALK, max_frames:12 },
	}
}

figure_delivery_boy = {
	animations : {
		walk : { pos : [0, 0], anim_id: ANIM_DELIVERY_BOY_WALK, max_frames:12 },
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

figure_sled = {
	animations : {
		walk : { pos : [0, 0], anim_id: IMG_BIGSLED_EMPTY, max_frames:1 },
	}
}

figure_tax_collector = {
	animations : {
		walk : { pos : [0, 0], anim_id: IMG_BIGSLED_EMPTY, max_frames:1 },
	},
	sound : {
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
