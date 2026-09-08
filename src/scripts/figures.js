log_info("akhenaten: figures info started")

import figure.prototype
import figure.figure_params
import figure.phrase
import figure.festival_guy
import figure.ostrich_hunter
import figure.antelope_hunter
import figure.birds_hunter
import figure.architector
import figure.bricklayer
import figure.carpenter
import figure.caravan_donkey
import figure.trade_caravan
import figure.cartpusher
import figure.constable
import figure.dancer
import figure.musician
import figure.juggler
import figure.senet_player
import figure.delivery_boy
import figure.dentist
import figure.docker
import figure.drunkard
import figure.embalmer
import figure.emigrant
import figure.enemy_chariot
import figure.enemy_archer
import figure.enemy_fast_sword
import figure.enemy_spearman
import figure.enemy_transport
import figure.enemy_warship
import figure.ferry_boat
import figure.fishing_boat
import figure.fireman
import figure.flotsam
import figure.frog
import figure.funeral_walker
import figure.governor
import figure.herbalist
import figure.homeless
import figure.immigrant
import figure.labor_seeker
import figure.librarian
import figure.lumberjack
import figure.magistrate
import figure.market_buyer
import figure.market_trader
import figure.mummy
import figure.noble
import figure.pharaoh
import figure.physician
import figure.plagued_citizen
import figure.priest
import figure.protestor
import figure.reed_gatherer
import figure.rioter
import figure.robber
import figure.scriber
import figure.academy_scriber
import figure.slave
import figure.soldier
import figure.stonemason
import figure.storageyard_cart
import figure.tax_collector
import figure.teacher
import figure.tomb_artisan
import figure.tomb_robber
import figure.tower_sentry
import figure.trade_ship
import figure.transport_ship
import figure.warship
import figure.water_carrier
import figure.worker
import figure.zookeeper

figure_festival_guy {
  overlay : OVERLAY_RELIGION
	animations {
		juggler_walk { pack:PACK_SPR_MAIN, id:130, max_frames:12 }
		musician_walk { pack:PACK_SPR_MAIN, id:191, max_frames:12 }
		dancer_walk {pack:PACK_SPR_MAIN, id:128, max_frames:12}
		priest_ra_walk { pack:PACK_SPR_MAIN, id:210, max_frames:12 }
		priest_osiris_walk {pack:PACK_SPR_MAIN, id:197, max_frames:12}
		priest_ptah_walk {pack:PACK_SPR_MAIN, id:187, max_frames:12}
		priest_seth_walk {pack:PACK_SPR_MAIN, id:193, max_frames:12}
		priest_bast_walk {pack:PACK_SPR_MAIN, id:208, max_frames:12}
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_FESTIVAL_GUY }
	}

	sounds {
		osiris_god_love_festival { sound:"priest_osiris_e01.wav", group:230, text:0 }
		ra_god_love_festival { sound:"priest_ra_e01.wav", group:231, text:0 }
		ptah_god_love_festival { sound:"priest_ptah_e01.wav", group:232, text:0 }
		seth_god_love_festival { sound:"priest_seth_e01.wav", group:233, text:0 }
		bast_god_love_festival { sound:"priest_bast_e01.wav", group:234, text:0 }
		juggler_i_like_festivals { sound:"juggler_e01.wav" }
		musician_i_like_festivals { sound:"musician_e01.wav" }
		dancer_i_like_festivals { sound:"dancer_e01.wav" }
	}

	category: figure_category_citizen
	max_damage: 10
	terrain_usage : TERRAIN_USAGE_ANY
	max_amount : 25
	permission : epermission_entertainer
}

figure_ostrich {
	animations {
		_pack { pack:PACK_SPR_MAIN }
		walk { id:156, max_frames:12 }
		death { id:157, max_frames:8, duration:3, loop:false }
		eating { id:159, max_frames:7 }
		idle { id:160, max_frames:7 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_OSTRICH }
	}

	category: figure_category_animal
	max_damage: 100
	corpse_time_delay: 300
	terrain_usage : TERRAIN_USAGE_ANIMAL
	scared_ticks: 128
}

figure_hyena {
	animations {
		_pack { pack:PACK_SPR_MAIN }
		walk { id:161, max_frames:12 }
		attack { id:162, max_frames:6 }
		death { id:163, max_frames:8, duration:3, loop:false }
		idle { id:164, max_frames:6 }
		eating { id:165, max_frames:6 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_HYENA }
	}

	category: figure_category_animal
	max_damage: 100
	attack_value: 6
	terrain_usage : TERRAIN_USAGE_ANIMAL
	max_hungry : 30
	max_hunting_distance : 12
	chase_speed_mult : 2
}

figure_asp {
	animations {
		walk { pack:PACK_EXPANSION_SPR, id:0, max_frames:12 }
		attack { pack:PACK_EXPANSION_SPR, id:1, max_frames:12 }
		idle { pack:PACK_EXPANSION_SPR, id:2, max_frames:12 }
		death { pack:PACK_EXPANSION_SPR, id:3, max_frames:6, loop:false }
		eating { pack:PACK_EXPANSION_SPR, id:4, max_frames:12 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_ASP }
	}

	category: figure_category_animal
	max_damage: 60
	attack_value: 4
	terrain_usage: TERRAIN_USAGE_ANIMAL
	max_hungry: 30
	max_hunting_distance: 10
	chase_speed_mult: 2
}

figure_lion {
	animations {
		walk { pack:PACK_EXPANSION_SPR, id:5, max_frames:11 }
		attack { pack:PACK_EXPANSION_SPR, id:6, max_frames:11 }
		idle { pack:PACK_EXPANSION_SPR, id:7, max_frames:6 }
		eating { pack:PACK_EXPANSION_SPR, id:8, max_frames:10 }
		death { pack:PACK_EXPANSION_SPR, id:9, max_frames:4 } // sit/rest frames (not corpse)
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_LION }
	}

	category: figure_category_animal
	max_damage: 150
	attack_value: 8
	terrain_usage: TERRAIN_USAGE_ANIMAL
	max_hungry: 30
	max_hunting_distance: 12
	chase_speed_mult: 2
}

figure_scorpion {
	animations {
		walk { pack:PACK_EXPANSION_SPR, id:10, max_frames:12 }
		attack { pack:PACK_EXPANSION_SPR, id:11, max_frames:6 }
		idle { pack:PACK_EXPANSION_SPR, id:12, max_frames:6 }
		eating { pack:PACK_EXPANSION_SPR, id:14, max_frames:6 }
		death { pack:PACK_EXPANSION_SPR, id:13, max_frames:6, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_SCORPION }
	}

	category: figure_category_animal
	max_damage: 80
	attack_value: 5
	terrain_usage: TERRAIN_USAGE_ANIMAL
	max_hungry: 30
	max_hunting_distance: 10
	chase_speed_mult: 2
}

figure_antelope {
	animations {
		_pack { pack:PACK_SPR_AMBIENT }
		walk { id:30, max_frames: 12 }
		death { id:31, max_frames:8, duration:3, loop:false }
		eating { id:33, max_frames:7 }
		idle { id:33, max_frames:8 }
		run { id:34, max_frames:8 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_ANTELOPE }
	}

	category: figure_category_animal
	max_damage: 100
	terrain_usage : TERRAIN_USAGE_ANIMAL
	scared_ticks: 128
	corpse_time_delay: 300
}

figure_horses = {
	animations : {
		walk : { pack:PACK_SPR_AMBIENT, id:113, max_frames:12 }
	}

	category: figure_category_citizen
	max_damage: 10
	terrain_usage : TERRAIN_USAGE_ANIMAL,
}

figure_ballista {
	animations {
		flying { pack:PACK_SPR_MAIN, id:114, max_frames:25, loop:true }
		eating { pack:PACK_SPR_MAIN, id:115, max_frames:25 }
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_BIRDS }
	}

	category: figure_category_inactive
	max_damage: 100
	terrain_usage : TERRAIN_USAGE_ANIMAL
}

figure_birds = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:114, max_frames:25, loop:true }
		idle : { pack:PACK_SPR_MAIN, id:114, max_frames:1, loop:false }
		eating : { pack:PACK_SPR_MAIN, id:115, max_frames:25 }
		death : { pack:PACK_SPR_MAIN, id:115, max_frames:25, loop:false }
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_BIRDS }
	}

	category: figure_category_animal
	max_damage: 100
	corpse_time_delay: 300
	terrain_usage : TERRAIN_USAGE_ANIMAL
	scared_ticks: 128
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
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_CROCODILE }
	}

	category: figure_category_hostile
	max_damage: 200
	attack_value: 7
	terrain_usage : TERRAIN_USAGE_AMPHIBIA
	max_hungry : 25
	max_hunting_distance : 10
	chase_speed_mult : 2
}

figure_hippo = {
  animations : {
		walk : { pack:PACK_SPR_AMBIENT, id:22, max_frames:12 }
		idle : { pack:PACK_SPR_AMBIENT, id:22, max_frames:1 }
		death : { pack:PACK_SPR_AMBIENT, id:23, max_frames:8, duration:3, loop:false }
		attack : { pack:PACK_SPR_AMBIENT, id:24, max_frames:7 }
		swim : { pack:PACK_SPR_AMBIENT, id:25, max_frames:8 }
		swim_attack : { pack:PACK_SPR_AMBIENT, id:26, max_frames:8 }
		swim_idle : { pack:PACK_SPR_AMBIENT, id:27, max_frames:8 }
		eating : { pack:PACK_SPR_AMBIENT, id:28, max_frames:8 }
		dance : { pack:PACK_SPR_AMBIENT, id:29, max_frames:8 }
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_HIPPO }
	}

	category: figure_category_animal
	max_damage: 250
	attack_value: 12
	terrain_usage : TERRAIN_USAGE_AMPHIBIA
}

figure_hunter_arrow {
	animations {
		walk { pack:PACK_SPR_MAIN, id:0, max_frames:12 }
		shadow { pack:PACK_SPR_MAIN, id:1, max_frames:12 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_HUNTER_ARROW }
	}

	category: figure_category_inactive
    max_damage : 100
    missile_attack_value : 6
    terrain_usage : TERRAIN_USAGE_ANY
}

figure_antelope_hunter_javelin = {
	animations : {
		walk : { pack:PACK_SPR_AMBIENT, id:44, max_frames:12 }
		shadow : { pack:PACK_SPR_AMBIENT, id:43, max_frames:12 }
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_HUNTER_ARROW }
	}

	category: figure_category_inactive
	max_damage : 100
	missile_attack_value : 6
	terrain_usage : TERRAIN_USAGE_ANY,
}

figure_arrow = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:0, max_frames:12 }
		shadow : { pack:PACK_SPR_MAIN, id:1, max_frames:12 }
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_ARROW }
	}

	category: figure_category_inactive
    max_damage : 100
    missile_attack_value : 6
    terrain_usage : TERRAIN_USAGE_ANY
}

figure_spear = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:198, max_frames:12 }
	}

	category: figure_category_inactive
  max_damage : 100
  missile_attack_value : 20
  terrain_usage : TERRAIN_USAGE_ANY,
  big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_SPEAR }
}

figure_javelin = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:198, max_frames:4 }
	}

	category: figure_category_hostile
  max_damage : 70
  attack_value : 5
  missile_attack_value : 5
  missile_delay : 70
  terrain_usage : TERRAIN_USAGE_ANY
  big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_JAVELIN }
}

figure_bolt = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:198, max_frames:12 }
	}

	category: figure_category_inactive
  max_damage : 100
  missile_attack_value : 100
  terrain_usage : TERRAIN_USAGE_ANY,
  big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_BOLT }
}

figure_standard_bearer {
	animations {
		walk { pack:PACK_SPR_MAIN, id:45, max_frames:12 }
		pole { pack:PACK_GENERAL, id:54, offset:0, max_frames:21 }
		flag_infantry { pack:PACK_GENERAL, id:126, offset:0, max_frames:9, duration:6 }
		flag_archers  { pack:PACK_GENERAL, id:126, offset:10, max_frames:9, duration:6 }
		flag_chariots { pack:PACK_GENERAL, id:126, offset:20, max_frames:9, duration:6 }
		sign { pack:PACK_GENERAL, id:3 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_STANDARD_BEARER }
	}

    is_soldier : true
	category: figure_category_armed
    max_damage : 80
	terrain_usage : TERRAIN_USAGE_ANY
}

figure_native = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:45, max_frames:12 }
		cart: { pack:PACK_SPR_MAIN, id:52, max_frames:1 }
	}

	category: figure_category_native
	max_damage: 10
}

figure_native_trader = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:45, max_frames:12 }
		cart: { pack:PACK_SPR_MAIN, id:52, max_frames:1 }
	}

	category: figure_category_native
	max_damage: 10
}

figure_cart {
	stone: { pack:PACK_SPR_MAIN, id:102  }
	granite: { pack:PACK_SPR_MAIN, id:103 }
	sandstone: { pack:PACK_SPR_MAIN, id:101 }
	limestone: { pack:PACK_SPR_MAIN, id:104 }
	bricks: { pack:PACK_SPR_MAIN, id:89 }
	empty: { pack:PACK_SPR_MAIN, id:77 }
}

// Locust swarm — Cleopatra SprMain2 bmp "locust":
// groups 30–34 = 6-frame cloud strips (non-8-dir). Runtime picks variant 0–4.
// Walk JS id=30 is timing only; main_image_update remaps to g30+variant.
// Must override main_image_update (no dir+8*frame) — see figure_locust.cpp.
// big_image: Cleopatra Unloaded pack 25 slot FIGURE_LOCUST (107).
// Tunables: swarm_days matches building_curse_farms(big); happiness Major Plague TEMP.
figure_locust {
	animations {
		walk { pack:PACK_EXPANSION_SPR, id:30, max_frames:6 }
		idle { pack:PACK_EXPANSION_SPR, id:30, max_frames:6 }
		death { pack:PACK_EXPANSION_SPR, id:30, max_frames:6, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_LOCUST }
	}

	category: figure_category_inactive
	max_damage: 1
	attack_value: 0
	terrain_usage: TERRAIN_USAGE_ANY
	max_roam_length: 320

	default_swarm: 8
	max_amount: 16
	swarm_days: 48
	happiness_hit: -10
	float_height: 20
}

figure_shipwreck = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:226, max_frames:12 }
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_SHIPWRECK }
	}

	category: figure_category_inactive
	max_damage: 10
	terrain_usage : TERRAIN_USAGE_ANY,
}

figure_sled {
	animations {
		empty { pack:PACK_SPR_MAIN, id:166, max_frames:1 }
		stone { pack:PACK_SPR_MAIN, id:167, max_frames:1 }
		sandstone { pack:PACK_SPR_MAIN, id:168, max_frames:1 }
		granite { pack:PACK_SPR_MAIN, id:169, max_frames:1 }
		limestone { pack:PACK_SPR_MAIN, id:170, max_frames:1 }
		clay { pack:PACK_SPR_MAIN, id:171, max_frames:1 }
		bricks { pack:PACK_SPR_MAIN, id:172, max_frames:1 }
		marble { pack:PACK_SPR_MAIN, id:170, max_frames:1 }
		copper { pack:PACK_SPR_MAIN, id:167, max_frames:1 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_SLED }
	}

	category: figure_category_citizen
	max_damage: 10
	terrain_usage: TERRAIN_USAGE_ANY,
}

figure_sled_puller = {
	animations : {
		walk : { pack:PACK_SPR_MAIN, id:121, max_frames:12 }
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_SLED_PULLER }
	}

	category: figure_category_citizen
	max_damage: 10
	terrain_usage: TERRAIN_USAGE_ANY,
}

figure_drunkard {
	animations {
		_pack { pack:PACK_SPR_MAIN }
		walk { id:203, max_frames:12 }
		back { id:203, max_frames:12 }
		womit { id:204, max_frames:12, duration:4 }
		death { id:205, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_DRUNKARD }
	}

	sounds {
		drunkard_need_drink {sound:"drunkard_e01.wav"}
		drunkard_going_to_tavern {sound:"drunkard_e02.wav"}
		drunkard_time_for_beer {sound:"drunkard_e03.wav"}
		drunkard_feeling_dizzy {sound:"drunkard_e04.wav"}
		drunkard_oh_my_stomach {sound:"drunkard_e05.wav"}
		drunkard_going_home {sound:"drunkard_e06.wav"}
	}

	category: figure_category_citizen
	max_damage: 10
	walk_delay : 50
    womit_delay : 50
	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 384
}

figure_fishing_point {
	animations {
		point { pack:PACK_SPR_AMBIENT, id:8, max_frames:22, duration:4 }
		bubbles { pack:PACK_SPR_AMBIENT, id:11, max_frames: 22, duration:4}
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_FISHING_POINT }
	}

	category: figure_category_inactive
	max_damage: 100
	terrain_usage : TERRAIN_USAGE_ANY,
	render_on_flat_tiles : true
}

figure_fishing_spot = {
	animations : {
		point : { pack:PACK_SPR_AMBIENT, id:8, max_frames:22, duration:4 }
		bubbles : { pack:PACK_SPR_AMBIENT, id:11, max_frames: 22, duration:4}
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_FISHING_SPOT }
	}

	terrain_usage : TERRAIN_USAGE_ANY,
}

figure_explosion = {
	animations : {
		poof : { pack:PACK_SPR_AMBIENT, id:12, max_frames:12 },
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_EXPLOSION }
	}

	category: figure_category_inactive
	max_damage : 0
	terrain_usage : TERRAIN_USAGE_ANY,
}

figure_map_flag = {
	animations : {
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_MAP_FLAG }
	}

	category: figure_category_inactive
	max_damage : 0
	terrain_usage : TERRAIN_USAGE_ANY,
}
