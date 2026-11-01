log_info("akhenaten: figure bubbles started")

// OG FIG_BUBBLES (28): 22-tick one-shot sinking VFX (SPR_AMBIENT 11).
figure_bubbles = {
	animations : {
		walk : { pack:PACK_SPR_AMBIENT, id:11, max_frames:22, duration:1 },
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_BUBBLES }
	}

	category: figure_category_inactive
	max_damage : 0
	terrain_usage : TERRAIN_USAGE_ANY
}
