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
