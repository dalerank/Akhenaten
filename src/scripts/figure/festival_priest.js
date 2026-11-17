log_info("akhenaten: figure festival_priest started")

// OG walkers.c figure_festival_priest_action, building_figure_helpers.c building_festival_spawn_celebrants,
// kingdom.h CELEBRANTS_PER_FESTIVAL_SIZE, building_data.c festival_group_rates / festival_type_lists.
figure_festival_priest {
	trips : 10
	celebrants_per_size : 10
	celebrant_groups : [
		{ rate : 15, buildings : [ BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY ] }
		{ rate : 20, buildings : [ BUILDING_HOUSE_COMMON_MANOR, BUILDING_HOUSE_SPACIOUS_MANOR, BUILDING_HOUSE_ELEGANT_MANOR,
		                           BUILDING_HOUSE_STATELY_MANOR, BUILDING_HOUSE_MODEST_ESTATE, BUILDING_HOUSE_PALATIAL_ESTATE ] }
		{ rate : 30, buildings : [ BUILDING_TEMPLE_OSIRIS, BUILDING_TEMPLE_RA, BUILDING_TEMPLE_PTAH, BUILDING_TEMPLE_SETH, BUILDING_TEMPLE_BAST,
		                           BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_TEMPLE_COMPLEX_RA, BUILDING_TEMPLE_COMPLEX_PTAH,
		                           BUILDING_TEMPLE_COMPLEX_SETH, BUILDING_TEMPLE_COMPLEX_BAST ] }
		// OG lists the pavilion twice: a pavilion sends two celebrants.
		{ rate : 35, buildings : [ BUILDING_BOOTH, BUILDING_BANDSTAND, BUILDING_PAVILLION, BUILDING_SENET_HOUSE, BUILDING_JUGGLER_SCHOOL,
		                           BUILDING_CONSERVATORY, BUILDING_PAVILLION ] }
	]
	// OG building_state.c building_count_update: a working bandstand also counts as a booth, a pavilion as both.
	active_counts_as : [
		{ building : BUILDING_BANDSTAND, counts : [ BUILDING_BOOTH, BUILDING_BANDSTAND ] }
		{ building : BUILDING_PAVILLION, counts : [ BUILDING_BOOTH, BUILDING_BANDSTAND, BUILDING_PAVILLION ] }
	]
	looks : [
		{ buildings : [ BUILDING_BANDSTAND, BUILDING_CONSERVATORY ], figure : FIGURE_MUSICIAN, anim : "musician_walk" }
		{ buildings : [ BUILDING_BOOTH, BUILDING_SENET_HOUSE, BUILDING_JUGGLER_SCHOOL ], figure : FIGURE_JUGGLER, anim : "juggler_walk" }
		{ buildings : [ BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL ], figure : FIGURE_DANCER, anim : "dancer_walk" }
		{ buildings : [ BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY ], figure : FIGURE_TEACHER, anim : "teacher_walk" }
		{ buildings : [ BUILDING_ZOO ], figure : FIGURE_ZOOKEEPER, anim : "zookeeper_walk" }
		{ buildings : [ BUILDING_TEMPLE_OSIRIS, BUILDING_TEMPLE_COMPLEX_OSIRIS ], figure : FIGURE_PRIEST, anim : "priest_osiris_walk" }
		{ buildings : [ BUILDING_TEMPLE_RA, BUILDING_TEMPLE_COMPLEX_RA ], figure : FIGURE_PRIEST, anim : "priest_ra_walk" }
		{ buildings : [ BUILDING_TEMPLE_PTAH, BUILDING_TEMPLE_COMPLEX_PTAH ], figure : FIGURE_PRIEST, anim : "priest_ptah_walk" }
		{ buildings : [ BUILDING_TEMPLE_SETH, BUILDING_TEMPLE_COMPLEX_SETH ], figure : FIGURE_PRIEST, anim : "priest_seth_walk" }
		{ buildings : [ BUILDING_TEMPLE_BAST, BUILDING_TEMPLE_COMPLEX_BAST ], figure : FIGURE_PRIEST, anim : "priest_bast_walk" }
	]
	default_look : { figure : FIGURE_NOBLES, anim : "patrician_walk" }

	overlay : OVERLAY_RELIGION
	animations {
		musician_walk { pack:PACK_SPR_MAIN, id:191, max_frames:12 }
		juggler_walk { pack:PACK_SPR_MAIN, id:130, max_frames:12 }
		dancer_walk { pack:PACK_SPR_MAIN, id:128, max_frames:12 }
		teacher_walk { pack:PACK_SPR_MAIN, id:57, max_frames:12 }
		zookeeper_walk { pack:PACK_EXPANSION_SPR, id:20, max_frames:12 }
		priest_osiris_walk { pack:PACK_SPR_MAIN, id:197, max_frames:12 }
		priest_ra_walk { pack:PACK_SPR_MAIN, id:210, max_frames:12 }
		priest_ptah_walk { pack:PACK_SPR_MAIN, id:187, max_frames:12 }
		priest_seth_walk { pack:PACK_SPR_MAIN, id:193, max_frames:12 }
		priest_bast_walk { pack:PACK_SPR_MAIN, id:208, max_frames:12 }
		patrician_walk { pack:PACK_SPR_MAIN, id:199, max_frames:12 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_FESTIVAL_PRIEST }
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
	terrain_usage : TERRAIN_USAGE_ROADS
	permission : epermission_entertainer
}

[es=(figure_festival_priest, setup_phrase)]
function figure_festival_priest_setup_phrase(ev) {
    var f = city.get_figure(ev.fid)
    if (!f || !f.valid) {
        return
    }

    var home = f.home
    if (!home || !home.valid) {
        figure_apply_phrase(f, "empty")
        return
    }

    switch (home.type) {
    case BUILDING_TEMPLE_OSIRIS:
    case BUILDING_TEMPLE_COMPLEX_OSIRIS:
        figure_apply_phrase(f, "osiris_god_love_festival")
        break
    case BUILDING_TEMPLE_RA:
    case BUILDING_TEMPLE_COMPLEX_RA:
        figure_apply_phrase(f, "ra_god_love_festival")
        break
    case BUILDING_TEMPLE_PTAH:
    case BUILDING_TEMPLE_COMPLEX_PTAH:
        figure_apply_phrase(f, "ptah_god_love_festival")
        break
    case BUILDING_TEMPLE_SETH:
    case BUILDING_TEMPLE_COMPLEX_SETH:
        figure_apply_phrase(f, "seth_god_love_festival")
        break
    case BUILDING_TEMPLE_BAST:
    case BUILDING_TEMPLE_COMPLEX_BAST:
        figure_apply_phrase(f, "bast_god_love_festival")
        break
    case BUILDING_JUGGLER_SCHOOL:
        figure_apply_phrase(f, "juggler_i_like_festivals")
        break
    case BUILDING_CONSERVATORY:
        figure_apply_phrase(f, "musician_i_like_festivals")
        break
    case BUILDING_DANCE_SCHOOL:
        figure_apply_phrase(f, "dancer_i_like_festivals")
        break
    default:
        figure_apply_phrase(f, "empty")
        break
    }
}
