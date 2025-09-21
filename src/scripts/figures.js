log_info("akhenaten: figures info started")

figure_fireman = {
	animations : {
		walk : { pos : [0, 0], pack:PACK_SPR_MAIN, id:6, max_frames:12 }
		death : { pos : [0, 0], pack:PACK_SPR_MAIN, id:7, max_frames:8, loop:false }
    fight_fire : { pos : [0, 0], pack:PACK_SPR_MAIN, id:8, max_frames:36 }
  }

  sounds : {
  	fighting_fire : {sound:"fireman_e01.wav", group: 242, text:0}
 		going_to_fire : {sound:"fireman_e02.wav", group: 242, text:1}
 		fighting_fire_also : {sound:"fireman_e03.WAV", group: 242, text:2}
 		desease_can_start_at_any_moment : {sound:"fireman_g01.WAV", group: 242, text:3}
 		no_food_in_city : {sound:"fireman_g02.WAV", group: 242, text:4}
 		city_not_safety_workers_leaving : {sound:"fireman_g03.WAV", group: 242, text:5}
 		need_workers : {sound:"fireman_g04.WAV", group: 242, text:6}
 		hight_fire_level : {sound:"fireman_g05.WAV", group: 242, text:7}
 		gods_are_angry : {sound:"fireman_g06.WAV", group: 242, text:8}
 		need_more_workers : {sound:"fireman_g07.WAV", group: 242, text:9}
 		low_entertainment : {sound:"fireman_g08.WAV", group: 242, text:10}
 		gods_are_pleasures : {sound:"fireman_g09.WAV", group: 242, text:11}
 		city_is_amazing : {sound:"fireman_g10.wav", group: 242, text:12}
  }

	terrain_usage : TERRAIN_USAGE_ANIMAL
	max_roam_length : 640
	permission : epermission_maintenance
}

figure_water_carrier = {
	animations : {
		walk : { pos : [0, 0], pack:PACK_SPR_MAIN, id:59, max_frames:12 },
		death : { pos : [0, 0], pack:PACK_SPR_MAIN, id:60, max_frames:8, loop:false },
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
  },
  terrain_usage : TERRAIN_USAGE_ROADS,
  max_roam_length : 640,
}

figure_protestor = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:32, max_frames:12 },
		death : { pack:PACK_SPR_MAIN, id:33, max_frames:8, loop:false },
	},
	terrain_usage : TERRAIN_USAGE_ANY,
	max_amount : 25,
}

figure_robber = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:32, max_frames:12 },
		death : { pack:PACK_SPR_MAIN, id:33, max_frames:8, loop:false },
	},
	terrain_usage : TERRAIN_USAGE_ANY,
	max_amount : 25,
}

figure_festival_guy = {
	animations : {
		juggler_walk : { pack:PACK_SPR_MAIN, id:130, max_frames:12 }
		musician_walk : { pack:PACK_SPR_MAIN, id:191, max_frames:12 }
		dancer_walk : {pack:PACK_SPR_MAIN, id:128, max_frames:12}
		priest_ra_walk: { pack:PACK_SPR_MAIN, id:210, max_frames:12 }
		priest_osiris_walk : {pack:PACK_SPR_MAIN, id:197, max_frames:12}
		priest_ptah_walk: {pack:PACK_SPR_MAIN, id:187, max_frames:12}
		priest_seth_walk: {pack:PACK_SPR_MAIN, id:193, max_frames:12}
		priest_bast_walk: {pack:PACK_SPR_MAIN, id:208, max_frames:12}
	}

	terrain_usage : TERRAIN_USAGE_ANY
	max_amount : 25
	permission : epermission_entertainer
}

figure_tower_sentry = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:54, max_frames:12 },
		death : { pack:PACK_SPR_MAIN, id:55, max_frames:8, loop:false },
		fire : { pack:PACK_SPR_MAIN, id:56, max_frames:12 },
		attack : { pack:PACK_SPR_MAIN, id:197, max_frames:12 },
	},
	terrain_usage : TERRAIN_USAGE_ANY,
	max_amount : 25,
}

figure_priest = {
	animations : {
		osiris_walk : { pack:PACK_SPR_MAIN, id:197, max_frames:12}
		osiris_death : { pack:PACK_SPR_MAIN, id:198, loop:false }
		ra_walk : { pack:PACK_SPR_MAIN, id:210, max_frames:12 }
		ra_death : { pack:PACK_SPR_MAIN, id:211, loop:false }
		ptah_walk : {  pack:PACK_SPR_MAIN, id:187, max_frames:12 }
		ptah_death : { pack:PACK_SPR_MAIN, id:188, loop:false }
		seth_walk : { pack:PACK_SPR_MAIN, id:193, max_frames:12 }
		seth_death : {  pack:PACK_SPR_MAIN, id:194, loop:false }
		bast_walk : {  pack:PACK_SPR_MAIN, id:208, max_frames:12 }
		bast_death : { pack:PACK_SPR_MAIN, id:209, loop:false }
	}

	sounds : {
		osiris_god_love_festival : {sound:"priest_osiris_e01.wav", group:230, text: 0}
		osiris_city_low_mood : {sound:"priest_osiris_e02.wav", group:230, text: 1}
		osiris_low_entertainment : {sound:"priest_osiris_e03.wav", group:230, text: 2}
		osiris_disease_in_city : {sound:"priest_osiris_e04.wav", group:230, text: 3}
		osiris_city_low_health : {sound:"priest_osiris_g01.wav", group:230, text: 4}
		osiris_no_food_in_city : {sound:"priest_osiris_g02.wav", group:230, text: 5}
		osiris_city_not_safety : {sound:"priest_osiris_g03.wav", group:230, text: 6}
		osiris_need_workers : {sound:"priest_osiris_g04.wav", group:230, text: 7}
		osiris_gods_are_angry : {sound:"priest_osiris_g05.wav", group:230, text: 8}
		osiris_low_sentiment : {sound:"priest_osiris_g06.wav", group:230, text: 9}
		osiris_much_unemployments : {sound:"priest_osiris_g07.wav", group:230, text: 10}
		osiris_need_entertainment : {sound:"priest_osiris_g08.wav", group:230, text: 11}
		osiris_city_is_good : {sound:"priest_osiris_g09.wav", group:230, text: 12}
		osiris_city_is_amazing : {sound:"priest_osiris_g10.wav", group:230, text: 13}

		ra_god_love_festival : {sound:"priest_ra_e01.wav", group:231, text:0}
		ra_city_low_mood : {sound:"priest_ra_e02.wav", group:231, text:1}
		ra_low_entertainment : {sound:"priest_ra_e03.wav", group:231, text:2}
		ra_disease_in_city : {sound:"priest_ra_e04.wav", group:231, text:3}
		ra_city_low_health : {sound:"priest_ra_g01.wav", group:231, text:4}
		ra_no_food_in_city : {sound:"priest_ra_g02.wav", group:231, text:5}
		ra_city_not_safety : {sound:"priest_ra_g03.wav", group:231, text:6}
		ra_need_workers : {sound:"priest_ra_g04.wav", group:231, text:7}
		ra_gods_are_angry : {sound:"priest_ra_g05.wav", group:231, text:8}
		ra_low_sentiment : {sound:"priest_ra_g06.wav", group:231, text:9}
		ra_much_unemployments : {sound:"priest_ra_g07.wav", group:231, text:10}
		ra_need_entertainment : {sound:"priest_ra_g08.wav", group:231, text:11}
		ra_city_is_good : {sound:"priest_ra_g09.wav", group:231, text:12}
		ra_city_is_amazing : {sound:"priest_ra_g10.wav", group:231, text:13}

		ptah_god_love_festival : {sound:"priest_ptah_e01.wav", group:232, text:0}
		ptah_city_low_mood : {sound:"priest_ptah_e02.wav", group:232, text:1}
		ptah_low_entertainment : {sound:"priest_ptah_e03.wav", group:232, text:2}
		ptah_disease_in_city : {sound:"priest_ptah_e04.wav", group:232, text:3}
		ptah_city_low_health : {sound:"priest_ptah_g01.wav", group:232, text:4}
		ptah_no_food_in_city : {sound:"priest_ptah_g02.wav", group:232, text:5}
		ptah_city_not_safety : {sound:"priest_ptah_g03.wav", group:232, text:6}
		ptah_need_workers : {sound:"priest_ptah_g04.wav", group:232, text:7}
		ptah_gods_are_angry : {sound:"priest_ptah_g05.wav", group:232, text:8}
		ptah_low_sentiment : {sound:"priest_ptah_g06.wav", group:232, text:9}
		ptah_much_unemployments : {sound:"priest_ptah_g07.wav", group:232, text:10}
		ptah_need_entertainment : {sound:"priest_ptah_g08.wav", group:232, text:11}
		ptah_city_is_good : {sound:"priest_ptah_g09.wav", group:232, text:12},
		ptah_city_is_amazing : {sound:"priest_ptah_g10.wav", group:232, text:13}

		seth_god_love_festival : {sound:"priest_seth_e01.wav", group:233, text:0}
		seth_city_low_mood : {sound:"priest_seth_e02.wav", group:233, text:1}
		seth_low_entertainment : {sound:"priest_seth_e03.wav", group:233, text:2}
		seth_disease_in_city : {sound:"priest_seth_e04.wav", group:233, text:3}
		seth_city_low_health : {sound:"priest_seth_g01.wav", group:233, text:4}
		seth_no_food_in_city : {sound:"priest_seth_g02.wav", group:233, text:5}
		seth_city_not_safety : {sound:"priest_seth_g03.wav", group:233, text:6}
		seth_need_workers : {sound:"priest_seth_g04.wav", group:233, text:7}
		seth_gods_are_angry : {sound:"priest_seth_g05.wav", group:233, text:8}
		seth_low_sentiment : {sound:"priest_seth_g06.wav", group:233, text:9}
		seth_much_unemployments : {sound:"priest_seth_g07.wav", group:233, text:10}
		seth_need_entertainment : {sound:"priest_seth_g08.wav", group:233, text:11}
		seth_city_is_good : {sound:"priest_seth_g09.wav", group:233, text:12}
		seth_city_is_amazing : {sound:"priest_seth_g10.wav", group:233, text:13}

		bast_god_love_festival: {sound:"bast_e01.wav", groud:234, text:0}
		bast_city_low_mood: {sound:"bast_e02.wav", groud:234, text:1}
		bast_low_entertainment: {sound:"bast_e03.wav", groud:234, text:2}
		bast_disease_in_city: {sound:"bast_e04.wav", groud:234, text:3}
		bast_city_low_health: {sound:"bast_g01.wav", groud:234, text:4}
		bast_no_food_in_city: {sound:"bast_g02.wav", groud:234, text:5}
		bast_city_not_safety: {sound:"bast_g03.wav", groud:234, text:6}
		bast_need_workers: {sound:"bast_g04.wav", groud:234, text:7}
		bast_gods_are_angry: {sound:"bast_g05.wav", groud:234, text:8}
		bast_low_sentiment: {sound:"bast_g06.wav", groud:234, text:9}
		bast_much_unemployments: {sound:"bast_g07.wav", groud:234, text:10}
		bast_need_entertainment: {sound:"bast_g08.wav", groud:234, text:11}
		bast_city_is_good: {sound:"bast_g09.wav", groud:234, text:12}
		bast_city_is_amazing: {sound:"bast_g10.wav", groud:234, text:13}
	}

	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 384
	permission : epermission_priest
}

figure_ostrich = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:156, max_frames:12 },
		death : { pack:PACK_SPR_MAIN, id:157, max_frames:8, duration:3, loop:false },
		eating : { pack:PACK_SPR_MAIN, id:159, max_frames:7 },
		idle : { pack:PACK_SPR_MAIN, id:160, max_frames:8 },
	},
	terrain_usage : TERRAIN_USAGE_ANIMAL,
}

figure_hyena = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:161, max_frames:12 },
		attack : { pack:PACK_SPR_MAIN, id:163, max_frames:6 },
		death : { pack:PACK_SPR_MAIN, id:163, max_frames:8, duration:3, loop:false },
		idle : { pack:PACK_SPR_MAIN, id:164, max_frames:6 },
		eating : { pack:PACK_SPR_MAIN, id:165, max_frames:6 },
	},
	terrain_usage : TERRAIN_USAGE_ANIMAL,
}

figure_antelope = {
	animations : {
		walk : { pack:PACK_SPR_AMBIENT, id:30, max_frames:12 },
		death : { pack:PACK_SPR_AMBIENT, id:31, max_frames:8, duration:3, loop:false },
		eating : { pack:PACK_SPR_AMBIENT, id:32, max_frames:7 },
		idle : { pack:PACK_SPR_AMBIENT, id:33, max_frames:8 },
		run : { pack:PACK_SPR_AMBIENT, id:34, max_frames:8 },
	},
	terrain_usage : TERRAIN_USAGE_ANIMAL,
}

figure_horses = {
	animations : {
		walk : { pack:PACK_SPR_AMBIENT, id:113, max_frames:12 }
	}

	terrain_usage : TERRAIN_USAGE_ANIMAL,
}

figure_birds = {
	animations : {
		flying : { pack:PACK_SPR_MAIN, id:114, max_frames:25, loop:true }
		eating : { pack:PACK_SPR_MAIN, id:115, max_frames:25 }
	}
	terrain_usage : TERRAIN_USAGE_ANIMAL
}

figure_crocodile = {
  animations : {
		walk : { pack:PACK_SPR_MAIN, id:23, max_frames:12 }
		death : { pack:PACK_SPR_MAIN, id:24, max_frames:8, duration:3, loop:false }
		attack : { pack:PACK_SPR_MAIN, id:25, max_frames:6 }
		swim : { pack:PACK_SPR_MAIN, id:26, max_frames:11 }
		idle : { pack:PACK_SPR_MAIN, id:23, max_frames:1, loop: false }
		swim_idle : { pack:PACK_SPR_MAIN, id:27, max_frames:11 }
		eating : { pack:PACK_SPR_MAIN, id:25, max_frames:6 }
	}
	terrain_usage : TERRAIN_USAGE_AMPHIBIA
	chase_speed_mult : 2
}

figure_hippo = {
  animations : {
		walk : { pack:PACK_SPR_AMBIENT, id:22, max_frames:12 }
		death : { pack:PACK_SPR_AMBIENT, id:23, max_frames:8, duration:3, loop:false }
		attack : { pack:PACK_SPR_AMBIENT, id:24, max_frames:7 }
		sweem : { pack:PACK_SPR_AMBIENT, id:25, max_frames:8 }
		sweem_attack : { pack:PACK_SPR_AMBIENT, id:26, max_frames:8 }
		sweem_idle : { pack:PACK_SPR_AMBIENT, id:27, max_frames:8 }
		eating : { pack:PACK_SPR_AMBIENT, id:28, max_frames:8 }
		dance : { pack:PACK_SPR_AMBIENT, id:29, max_frames:8 }
	}
	terrain_usage : TERRAIN_USAGE_AMPHIBIA
}

figure_immigrant = {
	animations : {
		walk : { pack: PACK_SPR_MAIN, id: 14, max_frames:12 },
		death : { pack: PACK_SPR_MAIN, id: 15, max_frames:8, loop:false },
		swim : { pack:PACK_SPR_MAIN, id:138, max_frames:4, duration:4 },
   	cart: { pack:PACK_SPR_MAIN, id:52, max_frames:1 },
	},
	sounds : {
		i_need_here: {sound:"immigrant_e01.wav", group: 202, text:0},
 		work_for_all : {sound:"immigrant_e02.wav", group: 202, text:1},
 		cheap_food : {sound:"immigrant_e03.wav", group: 202, text:2},
	},
	terrain_usage : TERRAIN_USAGE_ANIMAL,
}

figure_ostrich_hunter = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:45, max_frames:12 },
		death : { pack:PACK_SPR_MAIN, id:46, max_frames:8, loop:false },
		hunt : { pack:PACK_SPR_MAIN, id:47, max_frames:12 },
		figth : { pack:PACK_SPR_MAIN, id:48, max_frames:12 },
		//work_in_field : { pack:PACK_SPR_MAIN, id:49, max_frames:12, loop:false },
		pack : { pack:PACK_SPR_MAIN, id:50, max_frames:12, loop:false },
		unpack : { pack:PACK_SPR_MAIN, id:50, max_frames:12, loop:false, start_frame:11, reverse:true },
		move_pack : { pack:PACK_SPR_MAIN, id:51, max_frames:12 },
	},
	sounds : {
		hunting : {sound:"hunt_ostrich_e01.wav", group:209, text:0 },
    back : {sound:"hunt_ostrich_e02.wav", group:209, text:1 },
    city_is_good : {sound: "hunt_ostrich_e10.wav", phrase: "#hunter_ostrich_good_city"}
	},
	terrain_usage : TERRAIN_USAGE_ANIMAL,
	max_hunting_distance : 30,
}

figure_hunter_arrow = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:0, max_frames:12 },
		shadow : { pack:PACK_SPR_MAIN, id:1, max_frames:12 },
	},
  terrain_usage : TERRAIN_USAGE_ANY,
}

figure_antelope_hunter = {
	animations : {
		walk : { pack:PACK_SPR_AMBIENT, id:36, max_frames:12 },
		death : { pack:PACK_SPR_AMBIENT, id:37, max_frames:8, loop:false },
		hunt : { pack:PACK_SPR_AMBIENT, id:38, max_frames:12 },
		figth : { pack:PACK_SPR_AMBIENT, id:39, max_frames:12 },
		figth_apcked : { pack:PACK_SPR_AMBIENT, id:40, max_frames:12 },
		pack : { pack:PACK_SPR_AMBIENT, id:41, max_frames:18, loop:false },
		move_pack : { pack:PACK_SPR_AMBIENT, id:42, max_frames:12 },
	},
	sounds : {
		hunting : {sound:"hunt_ostrich_e01.wav", group:209, text:0 },
    back : {sound:"hunt_ostrich_e02.wav", group:209, text:1 },
    city_is_good : {sound: "hunt_ostrich_e10.wav", phrase: "#hunter_ostrich_good_city"}
	},
	terrain_usage : TERRAIN_USAGE_ANIMAL,
	max_hunting_distance : 30,
}

figure_antelopr_hunter_arrow = {
	animations : {
		walk : { pack:PACK_SPR_AMBIENT, id:43, max_frames:12 },
		shadow : { pack:PACK_SPR_AMBIENT, id:44, max_frames:12 },
	},
  terrain_usage : TERRAIN_USAGE_ANY,
}

figure_arrow = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:0, max_frames:12 },
		shadow : { pack:PACK_SPR_MAIN, id:1, max_frames:12 },
	},
  terrain_usage : TERRAIN_USAGE_ANY,
}

figure_spear = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:198, max_frames:12 },
	},
  terrain_usage : TERRAIN_USAGE_ANY,
}

figure_javelin = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:198, max_frames:4 },
	},
  terrain_usage : TERRAIN_USAGE_ANY,
}

figure_bolt = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:198, max_frames:12 },
	},
  terrain_usage : TERRAIN_USAGE_ANY,
}

figure_standard_bearer = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:45, max_frames:12 },
		pole : { pack:PACK_GENERAL, id:54, offset:0, max_frames:21 },
		flag_infantry : { pack:PACK_GENERAL, id:126, offset:0, max_frames:9, duration:6 },
		flag_archers  : { pack:PACK_GENERAL, id:126, offset:10, max_frames:9, duration:6 },
		flag_chariots : { pack:PACK_GENERAL, id:126, offset:20, max_frames:9, duration:6 }, 
		sign : { pack:PACK_GENERAL, id:3 },
	},
	terrain_usage : TERRAIN_USAGE_ANY,
}

figure_native_trader = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:45, max_frames:12 },
		cart: { pack:PACK_SPR_MAIN, id:52, max_frames:1 },
	},
}

figure_magistrate = {
	animations : {
		walk : { pack: PACK_SPR_MAIN, id: 212, max_frames:12 },
		death : { pack: PACK_SPR_MAIN, id: 213, max_frames:8, loop:false },
	},
	sounds : {
    i_hope_we_are_ready : {sound: "magistrate_e02.wav", group:210, text:0 },
    no_criminals_in_city : {sound: "magistrate_e03.wav", group:210, text:0 },
    all_good_in_city : {sound: "magistrate_e04.wav", group:210, text:0 },
    streets_still_arent_safety : {sound: "magistrate_e05.wav", group:210, text:0 },
    disease_in_city : {sound: "magistrate_g01.wav", group:210, text:0 },
    no_food_in_city : {sound: "magistrate_g02.wav", group:210, text:0 },
    city_not_safety : {sound: "magistrate_g03.wav", group:210, text:0 },
    need_workers : {sound: "magistrate_g04.wav", group:210, text:0 },
    gods_are_angry : {sound: "magistrate_g05.wav", group:210, text:0 },
    city_bad_reputation : {sound: "magistrate_g06.wav", group:210, text:0 },
    much_unemployments : {sound: "magistrate_g07.wav", group:210, text:0 },
    no_entertainment_need : {sound: "magistrate_g08.wav", group:210, text:0 },
    city_not_bad : {sound: "magistrate_g09.wav", group:210, text:0 },
    city_is_amazing : {sound: "magistrate_g10.wav", group:210, text:0 },
	},
	info_help_id:182,
  info_text_id:210,
	terrain_usage : TERRAIN_USAGE_ROADS,
	max_roam_length : 800,
}

figure_lumberjack = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:73, max_frames:12 },
		death: { pack:PACK_SPR_MAIN, id:74, max_frames:8, loop:false  },
		work : { pack:PACK_SPR_MAIN, id:75, max_frames:12 },
		back : { pack:PACK_SPR_MAIN, id:76, max_frames:12 },
	},
	sounds : {
		hunting : {sound:"woodcutter_e01.wav", group:209, text:0 },
    back : {sound:"woodcutter_e02.wav", group:209, text:1 },
	},
	terrain_usage : TERRAIN_USAGE_ANY,
}

figure_flotsam = {
	animations : {
		walk : {pack:PACK_SPR_AMBIENT, id:0, max_frames: 12}
	},
	terrain_usage : TERRAIN_USAGE_ANY,
}

figure_scriber = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:199, max_frames:12 },
		death : { pack:PACK_SPR_MAIN, id:200, max_frames:8, loop:false },
	},
	terrain_usage : TERRAIN_USAGE_ROADS,
	max_roam_length : 384,
}

figure_dentist = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:182, max_frames:12 }
		death : { pack:PACK_SPR_MAIN, id:183, max_frames:8, loop:false }
	}

	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 384
	permission : epermission_medicine
}

figure_embalmer = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:184, max_frames:12 }
		death : { pack:PACK_SPR_MAIN, id:185, max_frames:8, loop:false }
	}
	
	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 384
	permission : epermission_medicine
}

figure_worker = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:116, max_frames:12 },
		death : { pack:PACK_SPR_MAIN, id:117, max_frames:8, loop:false },
		work : { pack:PACK_SPR_MAIN, id:118, max_frames:12 },
	},
	sounds : {
		going_to_workplace : {sound:"worker_e02.wav", group:212, text:0},
    farm_is_flooded : {sound:"worker_e03.wav", group:212, text:1},
    desease_can_start_at_any_moment : {sound:"worker_g01.wav", group:212, text:2},
    no_food_in_city : {sound:"worker_g02.wav", group:212, text:3},
    enemies_in_city : {sound:"worker_g03.wav", group:212, text:4},
    need_workers : {sound:"worker_g04.wav", group:212, text:5},
    gods_are_angry : {sound:"worker_g05.wav", group:212, text:6},
    city_is_bad : {sound:"worker_g06.wav", group:212, text:7},
    much_unemployments : {sound:"worker_g07.wav", group:212, text:8},
    low_entertainment : {sound:"worker_g08.wav", group:212, text:9},
    city_is_good : {sound:"worker_g09.wav", group:212, text:10},
    city_is_amazing : {sound:"worker_g10.wav", group:212, text:11},
	}
}

figure_physician = {
	animations : {
		walk : { pos : [0, 0], pack:PACK_SPR_MAIN, id:71, max_frames:12 }
		death : { pos : [0, 0], pack:PACK_SPR_MAIN, id:72, max_frames:8, loop:false }
	}

	sounds : {
		desease_can_start_at_any_moment : {sound:"doctor_e01.wav", group: 239, text:1}
    city_has_low_health : {sound:"doctor_g01.wav", group: 239, text:1}
    no_food_in_city : {sound:"doctor_g02.wav", group: 239, text:2}
    city_have_no_army : {sound:"doctor_g03.wav", group: 239, text:3}
    need_workers : {sound:"doctor_g04.wav", group: 239, text:4}
    gods_are_angry : {sound:"doctor_g05.wav", group: 239, text:5}
    gods_are_pleasures : {sound:"doctor_g06.wav", group: 239, text:6}
    no_job_in_city : {sound:"doctor_g07.wav", group: 239, text:7}
    low_entertainment : {sound:"doctor_g08.wav", group: 239, text:8}
    all_good_in_city : {sound:"doctor_g09.wav", group: 239, text:9}
    city_very_healthy : {sound:"doctor_g10.wav", group: 239, text:10}
	}

	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 384
	permission : epermission_medicine
}

figure_architector = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:4, max_frames:12 }
		death : { pack:PACK_SPR_MAIN, id:5, max_frames:8, loop:false }
    work_ground : { pack:PACK_SPR_AMBIENT, id:49, max_frames:6 }
    work_stand : { pack:PACK_SPR_AMBIENT, id:50, max_frames:6 }
	}

	sounds : {
		extreme_damage_level: {sound:"engineer_e01.wav", group: 243, text:0}
    i_am_works: {sound:"engineer_e02.wav", group: 243, text:1}
    high_damage_level: {sound:"engineer_g01.wav", group: 243, text:2}
    no_food_in_city: {sound:"engineer_g02.wav", group: 243, text:3}
    city_not_safety: {sound:"engineer_g03.wav", group: 243, text:4}
    need_more_workers: {sound:"engineer_g04.wav", group: 243, text:5}
    gods_are_angry: {sound:"engineer_g05.wav", group: 243, text:6}
    city_has_bad_reputation: {sound:"engineer_g06.wav", group: 243, text:7}
    city_is_good: {sound:"engineer_g07.wav", group: 243, text:7}
    low_entertainment: {sound:"engineer_g08.wav", group: 243, text:8}
    city_is_bad: {sound:"engineer_g09.wav", group: 243, text:9}
    city_is_amazing: {sound:"engineer_g10.wav", group: 243, text:10}
	}

	terrain_usage : TERRAIN_USAGE_ROADS
	max_service_buildings : 100
	max_roam_length : 640
	permission : epermission_maintenance
}

figure_market_buyer = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:16, max_frames:12 },
		death : { pack:PACK_SPR_MAIN, id:17, max_frames:8, loop:false },
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
	},
	terrain_usage : TERRAIN_USAGE_ROADS,
}

figure_delivery_boy = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:9, max_frames:12 },
		death : { pack:PACK_SPR_MAIN, id:10, max_frames:8, loop:false },
	},
	sounds : {
		those_baskets_too_heavy : {sound: "marketboy_e01.wav", group:221, text: 0},
    i_works_all_day : {sound: "marketboy_e02.wav", group:221, text: 1},
    upon_ill_be_market_owner : {sound: "marketboy_e03.wav", group:221, text: 2},
	},
	terrain_usage : TERRAIN_USAGE_ROADS,
}

figure_carpenter = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:145, max_frames:12 },
		death : { pack:PACK_SPR_MAIN, id:146, max_frames:8, loop:false },
		work_ground : { pack:PACK_SPR_MAIN, id:147, max_frames:7 },
		work_wall : { pack:PACK_SPR_MAIN, id:148, max_frames:7 },
		climbing : { pack:PACK_SPR_MAIN, id:149, max_frames:3 },
	},

	terrain_usage : TERRAIN_USAGE_ROADS,
}

figure_stonemason = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:150, max_frames:12 }
		death : { pack:PACK_SPR_MAIN, id:151, max_frames:8, loop:false }
		work_ground : { pack:PACK_SPR_MAIN, id:152, max_frames:7 }
		work_wall : { pack:PACK_SPR_MAIN, id:153, max_frames:7 }
		climbing : { pack:PACK_SPR_MAIN, id:154, max_frames:3 }
	}

	terrain_usage : TERRAIN_USAGE_ROADS,
}

figure_cartpusher = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:43, max_frames:12 },
		death : { pack:PACK_SPR_MAIN, id:44, max_frames:8, loop:false },
		swim : { pack:PACK_SPR_MAIN, id:138, max_frames:4, duration:4 },
	},
	sounds  : {
	  have_no_place_for_goods : { sound:"cartpusher_e01.wav", group:222, text:0},
    i_have_time_for_rest : { sound:"cartpusher_e02.wav", group:222, text:1},
    road_too_long : { sound:"cartpusher_e03.wav", group:222, text:2},
    i_have_no_destination : { sound:"cartpusher_e01.wav", group:223, text:0},
    back_to_home : { sound:"cartpusher_e02.wav", group:223, text:1},
    delivering_items : { sound:"cartpusher_e03.wav", group:223, text:2},
	},
	terrain_usage : TERRAIN_USAGE_ROADS,
}

figure_docker = {
	animations : {
		walk : { pos : [0, 0], pack:PACK_SPR_MAIN, id:43, max_frames:12 },
		death : { pos : [0, 0], pack:PACK_SPR_MAIN, id:44, max_frames:8, loop:false },
	},
	terrain_usage : TERRAIN_USAGE_ROADS,
}

figure_bricklayer = {
	animations : {
		walk : {pack:PACK_SPR_MAIN, id:109, max_frames:12 },
		death : {pack:PACK_SPR_MAIN, id:110, max_frames:8, loop:false },
		work : {pack:PACK_SPR_MAIN, id:111, max_frames:12, duration:4 },
		idle : {pack:PACK_SPR_MAIN, id:112, max_frames:8, duration:2 },
	},
	sounds : {
		time_to_put_bricks : {sound:"brick_e01.wav", group:222, text: 0},
 		with_my_bricks_monuments_will_be_fine : {sound:"brick_e02.wav", group:222, text: 1},
	},
	terrain_usage : TERRAIN_USAGE_ROADS,
}

figure_storageyard_cart = {
	animations : {
		walk : { pack: PACK_SPR_MAIN, id:43, max_frames:12 },
		death : { pack: PACK_SPR_MAIN, id:44, max_frames:8, loop:false },
		swim : { pack:PACK_SPR_MAIN, id:138, max_frames:4, duration:4 },
	},
	terrain_usage : TERRAIN_USAGE_ROADS,
}

figure_governor = {
	animations : {
		walk : { pack: PACK_SPR_MAIN, id:189, max_frames:12 },
		death : { pack: PACK_SPR_MAIN, id:190, max_frames:8, loop:false },
	},
	terrain_usage : TERRAIN_USAGE_ROADS,
}

figure_trade_ship = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:123, max_frames:4, duration:4 }
		death : { pack:PACK_SPR_MAIN, id:124, max_frames:8 }
		idle : { pack:PACK_SPR_MAIN, id:125, max_frames:1, offset:0 }
	}
	sounds : {
		looking_for_unload : {sound:"barge_e01.wav", group: 224, text:0}
		waiting_for_cargo : {sound:"barge_e02.wav", group: 224, text:1}
		no_trade : {sound:"barge_e03.wav", group: 224, text:2}
		good_trade : {sound:"barge_e04.wav", group: 224, text:3}
		beatiful_journey : {sound:"barge_e05.wav", group: 224, text:4}
	}
	terrain_usage : TERRAIN_USAGE_ANY
	max_capacity : 1200
}

figure_shipwreck = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:226, max_frames:12 }
	},
	terrain_usage : TERRAIN_USAGE_ANY,
}

figure_emigrant = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:2, max_frames:12 },
		death : { pack: PACK_SPR_MAIN, id:3, max_frames:8, loop:false },
		cart : { pack:PACK_SPR_MAIN, id:52, max_frames:1 },
	},
	sounds : {
		no_job_in_city : {sound:"emigrant_e01.wav", group: 203, text:0},
    no_food_in_city : {sound:"emigrant_e02.wav", group: 203, text:1},
    tax_too_high : {sound:"emigrant_e03.wav", group: 203, text:2},
    salary_too_low : {sound:"emigrant_e04.wav", group: 203, text:3},
    no_house_for_me : {sound:"emigrant_e05.wav", group: 203, text:4},
	},
	terrain_usage : TERRAIN_USAGE_ANIMAL,
}

figure_sled = {
	animations : {
		empty : { pack:PACK_SPR_MAIN, id:166, max_frames:1 },
		stone : { pack:PACK_SPR_MAIN, id:167, max_frames:1 },
		sandstone : { pack:PACK_SPR_MAIN, id:168, max_frames:1 },
		granite : { pack:PACK_SPR_MAIN, id:169, max_frames:1 },
		limestone : { pack:PACK_SPR_MAIN, id:170, max_frames:1 },
		clay : { pack:PACK_SPR_MAIN, id:171, max_frames:1 },
		bricks : { pack:PACK_SPR_MAIN, id:172, max_frames:1 },
	},
	terrain_usage: TERRAIN_USAGE_ANY,
}

figure_sled_puller = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:121, max_frames:12 },
	},
	terrain_usage: TERRAIN_USAGE_ANY,
}

figure_trade_caravan = {
	animations : {
		walk : { pack:PACK_SPR_AMBIENT, id:20, max_frames:12 }
		death : { pack:PACK_SPR_AMBIENT, id:21, max_frames:8, loop:false }
	}
	wait_ticks_after_create : 10
	terrain_usage : TERRAIN_USAGE_PREFER_ROADS
	max_capacity : 800
}

figure_caravan_donkey = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:52, max_frames:12 },
		death : { pack:PACK_SPR_MAIN, id:53, max_frames:8, loop:false },
	},
	terrain_usage : TERRAIN_USAGE_PREFER_ROADS,
}

figure_homeless = {
	animations : {
		walk : { pack: PACK_SPR_MAIN, id: 12, max_frames:12 },
		death : { pack: PACK_SPR_MAIN, id: 13, max_frames:8, loop:false },
	},
	terrain_usage : TERRAIN_USAGE_PREFER_ROADS,
}

figure_drunkard = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:203, max_frames:12 }
		back : { pack:PACK_SPR_MAIN, id:203, max_frames:12 }
		womit : { pack:PACK_SPR_MAIN, id:204, max_frames:12, duration:4 }
		death : { pack:PACK_SPR_MAIN, id:205, max_frames:8, loop:false }
	}

	walk_delay : 50
  womit_delay : 50
	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 384
}

figure_teacher = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:201, max_frames:12 }
		death : { pack:PACK_SPR_MAIN, id:202, max_frames:8, loop:false }
	}

	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 384
	permission : epermission_education
}

figure_librarian = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:57, max_frames:12 }
		death : { pack:PACK_SPR_MAIN, id:58, max_frames:8, loop:false }
	}

	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 384
	permission : epermission_education
}

figure_constable = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:20, max_frames:12 },
		death : { pack:PACK_SPR_MAIN, id:21, max_frames:8, loop:false },
		attack : { pack:PACK_SPR_MAIN, id:21, max_frames:8, loop:false },
	},
	terrain_usage : TERRAIN_USAGE_ROADS,
	max_roam_length : 640,
}

figure_herbalist = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:180, max_frames:12 }
		death : { pack:PACK_SPR_MAIN, id:181, max_frames:8, loop:false }
	}

	sounds : {
		no_threat_malaria_here : {sound:"apothecary_e02.wav", group: 241, text:1}
    have_malaria_risk_here : {sound:"apothecary_e03.wav", group: 241, text:2}
	}

	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 384
	permission : epermission_medicine
}

figure_dancer = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:128, max_frames:12 }
		death : { pospack:PACK_SPR_MAIN, id:129, max_frames:8, loop:false }
	}

	sounds : {
		i_like_festivals : {sound:"dancer_e01.wav", group:228, text:0}
    desease_can_start_at_any_moment : {sound:"dancer_g01.wav", group:228, text:1}
    no_food_in_city : {sound:"dancer_g02.wav", group:228, text:2}
    city_not_safety_workers_leaving : {sound:"dancer_g03.wav", group:228, text:3}
    need_workers : {sound:"dancer_g04.wav", group:228, text:4}
    gods_are_angry : {sound:"dancer_g05.wav", group:228, text:5}
    city_is_bad : {sound:"dancer_g06.wav", group:228, text:6}
    much_unemployments : {sound:"dancer_g07.wav", group:228, text:7}
    salary_too_low : {sound:"dancer_g08.wav", group:228, text:8}
    city_is_good : {sound:"dancer_g09.wav", group:228, text:9}
    city_is_amazing : {sound:"dancer_g10.wav", group:228, text:10}
	}

	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 512
	permission : epermission_entertainer  // roadblock option
}

figure_musician = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:191, max_frames:12 },
		death : { pack:PACK_SPR_MAIN, id:192, max_frames:8, loop:false },
	}

	sounds : {
		i_like_festivals : { sound:"musician_e01.wav", group:229, text:0 }
 		city_heath_too_low : { sound:"musician_g01.wav", group:229, text:0 }
 		no_food_in_city : { sound:"musician_g02.wav", group:229, text:0 }
 		city_not_safety_workers_leaving : { sound:"musician_g03.wav", group:229, text:0 }
 		need_workers : { sound:"musician_g04.wav", group:229, text:0 }
 		gods_are_angry : { sound:"musician_g05.wav", group:229, text:0 }
 		city_is_bad_reputation : { sound:"musician_g06.wav", group:229, text:0 }
 		much_unemployments : { sound:"musician_g07.wav", group:229, text:0 }
 		no_entertainment_need : { sound:"musician_g08.wav", group:229, text:0 }
 		city_not_bad : { sound:"musician_g09.wav", group:229, text:0 }
 		city_is_good : { sound:"musician_g10.wav", group:229, text:0 }
	}

	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 512
	permission: epermission_entertainer
}

figure_soldier_infantry = {
	animations : {
		walk : { pos : [0, 0], pack:PACK_SPR_MAIN, id:64, max_frames:12 },
		death : { pos : [0, 0], pack:PACK_SPR_MAIN, id:65, max_frames:8, loop:false },
		attack : { pos : [0, 0], pack:PACK_SPR_MAIN, id:66, max_frames:12 },
	},
	terrain_usage : TERRAIN_USAGE_ANY,
}

figure_fishing_point = {
	animations : {
		point : { pack:PACK_SPR_AMBIENT, id:8, max_frames:22, duration:4 },
		bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames: 22, duration:4},
	},
	terrain_usage : TERRAIN_USAGE_ANY,
}

figure_fishing_spot = {
	animations : {
		point : { pack:PACK_SPR_AMBIENT, id:8, max_frames:22, duration:4 },
		bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames: 22, duration:4},
	},
	terrain_usage : TERRAIN_USAGE_ANY,
}

figure_fishing_boat = {
	animations : {
		walk : {pack:PACK_SPR_MAIN, id:134, max_frames:4, duration:3 },
		swim : {pack:PACK_SPR_MAIN, id:134, max_frames:4, duration:3 },
		death : {pack:PACK_SPR_MAIN, id:135, max_frames:8, loop:false },
		work : {pack:PACK_SPR_MAIN, id:135, max_frames:6, duration:5 },
		idle : {pack:PACK_SPR_MAIN, id:136, offset:3, max_frames:1 },
	},
	terrain_usage : TERRAIN_USAGE_ANY,
}

figure_ferry_boat = {
	animations : {
		walk : {pack:PACK_SPR_MAIN, id:137, max_frames:4, duration:3 },
		swim : {pack:PACK_SPR_MAIN, id:137, max_frames:4, duration:3 },
		death : {pack:PACK_SPR_MAIN, id:138, max_frames:8, loop:false },
		idle : {pack:PACK_SPR_MAIN, id:139, offset:3, max_frames:1 },
	},
	terrain_usage : TERRAIN_USAGE_ANY,
}

figure_warship = {
	animations : {
		walk : {pack:PACK_SPR_MAIN, id:141, max_frames:4, duration:10 },
		swim : {pack:PACK_SPR_MAIN, id:141, max_frames:4, duration:10 },
		death : {pack:PACK_SPR_MAIN, id:142, max_frames:8, loop:false },
		attack : {pack:PACK_SPR_MAIN, id:143, max_frames:6, duration:5 },
		idle : {pack:PACK_SPR_MAIN, id:143, offset:3, max_frames:1 },
	},
	orders : {
		goto_wharf : { id: 1, text: 9 },
		engage_nearby : { id: 2, text: 11 },
		hold_position : { id: 3, text: 13 },
		seek_and_destroy : { id: 4, text: 15 },
		repair : { id: 5, text: 17 },
	},
	info_help_id: 84,
  info_text_id: 184,
	terrain_usage : TERRAIN_USAGE_ANY,
}

figure_transport_ship = {
	animations : {
		walk : {pack:PACK_SPR_MAIN, id:34, max_frames:4, duration:10 },
		swim : {pack:PACK_SPR_MAIN, id:34, max_frames:4, duration:10 },
		death : {pack:PACK_SPR_MAIN, id:35, max_frames:8, loop:false },
		idle : {pack:PACK_SPR_MAIN, id:35, offset:8, max_frames:1 },
	},
	terrain_usage : TERRAIN_USAGE_ANY,
}

figure_soldier_archer = {
	animations : {
		walk : {pack:PACK_SPR_MAIN, id:61, max_frames:12 },
		death : {pack:PACK_SPR_MAIN, id:62, max_frames:8, loop:false },
		attack : {pack:PACK_SPR_MAIN, id:63, max_frames:12 },
	},
	terrain_usage : TERRAIN_USAGE_ANY,
}

figure_soldier_charioteer = {
	animations : {
		walk : {pack:PACK_SPR_MAIN, id:67, max_frames:12 },
		death : {pack:PACK_SPR_MAIN, id:68, max_frames:8, loop:false },
		attack : {pack:PACK_SPR_MAIN, id:69, max_frames:12 },
	},
	terrain_usage : TERRAIN_USAGE_ANY,
}

figure_juggler = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:130, max_frames:12 }
		death : { pack:PACK_SPR_MAIN, id:131, max_frames:8, loop:false }
	}

	sounds : {
		i_like_festivals : {sound:"juggler_e01.wav", group: 230, text:0 }
    disease_in_city : {sound:"juggler_g01.wav", group: 230, text:0 }
    city_low_sentiment : {sound:"juggler_g02.wav", group: 230, text:0 }
    city_not_safety_workers_leaving : {sound:"juggler_g03.wav", group: 230, text:0 }
    salary_too_low : {sound:"juggler_g04.wav", group: 230, text:0 }
    gods_are_angry : {sound:"juggler_g05.wav", group: 230, text:0 }
    city_verylow_sentiment : {sound:"juggler_g06.wav", group: 230, text:0 }
    much_unemployments : {sound:"juggler_g07.wav", group: 230, text:0 }
    low_entertainment : {sound:"juggler_g08.wav", group: 230, text:0 }
    city_is_good : {sound:"juggler_g09.wav", group: 230, text:0 }
    city_is_amazing : {sound:"juggler_g10.wav", group: 230, text:0 }
	}

	max_roam_length: 640
	permission : epermission_entertainer  // roadblock option
}

figure_senet_player = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:132, max_frames:12 }
		death : { pack:PACK_SPR_MAIN, id:133, max_frames:8, loop:false }
	}

	sounds : {
		i_like_festivals : {sound:"juggler_e01.wav", group: 230, text:0 }
    disease_in_city : {sound:"juggler_g01.wav", group: 230, text:0 }
    city_low_sentiment : {sound:"juggler_g02.wav", group: 230, text:0 }
    city_not_safety_workers_leaving : {sound:"juggler_g03.wav", group: 230, text:0 }
    salary_too_low : {sound:"juggler_g04.wav", group: 230, text:0 }
    gods_are_angry : {sound:"juggler_g05.wav", group: 230, text:0 }
    city_verylow_sentiment : {sound:"juggler_g06.wav", group: 230, text:0 }
    much_unemployments : {sound:"juggler_g07.wav", group: 230, text:0 }
    low_entertainment : {sound:"juggler_g08.wav", group: 230, text:0 }
    city_is_good : {sound:"juggler_g09.wav", group: 230, text:0 }
    city_is_amazing : {sound:"juggler_g10.wav", group: 230, text:0 }
	}

	max_roam_length: 640
	permission : epermission_entertainer  // for roadblocks
}

figure_market_trader = {
	animations : {
		walk : { pos : [0, 0], pack:PACK_SPR_MAIN, id:18, max_frames:12 }
		death : { pos : [0, 0], pack:PACK_SPR_MAIN, id:19, max_frames:8, loop:false }
	}

	sounds : {
		goods_are_finished : {sound:"mkt_seller_e01.wav", group:245, text:0}
 	  we_are_selling_goods : {sound:"mkt_seller_e02.wav", group:245, text:0}
	}

	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 384
	permission : epermission_market
}

figure_labor_seeker = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:206, max_frames:12 },
		death : { pack:PACK_SPR_MAIN, id:207, max_frames:8, loop:false },
	},
	sounds : {
		no_jobs : { sound:"Labor_e01.wav", group:213, text:0},
    need_workers : { sound:"Labor_e02.WAV", group:213, text:1},
    disease_in_city : { sound:"Labor_g01.WAV", group:213, text:2},
    i_looking_for_the_workers : { sound:"Labor_g02.WAV", group:213, text:3},
    city_not_safety_workers_leaving : { sound:"Labor_g03.WAV", group:213, text:4},
    need_more_workers : { sound:"Labor_g04.WAV", group:213, text:5},
    gods_are_angry : { sound:"Labor_g05.WAV", group:213, text:6},
    no_food_in_city : { sound:"Labor_g06.WAV", group:213, text:7},
    much_unemployments : { sound:"Labor_g07.WAV", group:213, text:8},
    no_some_workers : { sound:"Labor_g08.WAV", group:213, text:9},
    i_want_to_leave_city : { sound:"Labor_g09.WAV", group:213, text:10},
    city_is_amazing : { sound:"Labor_g10.WAV", group:213, text:11},
	},
	terrain_usage : TERRAIN_USAGE_ROADS,
	max_roam_length : 384,
}

figure_reed_gatherer = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:37, max_frames:12 },
		death : { pack:PACK_SPR_MAIN, id:38, max_frames:8, loop:false },
		work : { pack:PACK_SPR_MAIN, id:39, max_frames:15 },
		back : { pack:PACK_SPR_MAIN, id:40, max_frames:12 },
	},
	terrain_usage : TERRAIN_USAGE_ANY,
	max_amount : 25,
}

figure_explosion = {
	animations : {
		poof : { pack:PACK_SPR_AMBIENT, id:12, max_frames:12 },
	},
	terrain_usage : TERRAIN_USAGE_ANY,
}

figure_tax_collector = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:41, max_frames:12 }
		death : { pack:PACK_SPR_MAIN, id:42, max_frames:8, loop:false }
	}

	sounds : {
		need_more_tax_collectors: {sound: "taxman_e01.wav", group: 245, text:0}
    high_taxes: {sound: "taxman_e02.wav", group: 245, text:1}
    much_pooh_houses: {sound: "taxman_e03.wav", group: 245, text:2}
    desease_can_start_at_any_moment: {sound: "taxman_g01.wav", group: 245, text:3}
    no_food_in_city: {sound: "taxman_g02.wav", group: 245, text:4}
    city_have_no_army: {sound: "taxman_g03.wav", group: 245, text:5}
    need_workers: {sound: "taxman_g04.wav", group: 245, text:6}
    gods_are_angry: {sound: "taxman_g05.wav", group: 245, text:7}
    city_is_bad: {sound: "taxman_g06.wav", group: 245, text:8}
    much_unemployments: {sound: "taxman_g07.wav", group: 245, text:9}
    low_entertainment: {sound: "taxman_g08.wav", group: 245, text:10}
    city_is_good: {sound: "taxman_g09.wav", group: 245, text:11}
    city_is_amazing: {sound: "taxman_g10.wav", group: 245, text:12}
	}

	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 512
	permission : epermission_tax_collector
}
