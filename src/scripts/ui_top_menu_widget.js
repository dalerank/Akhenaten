log_info("akhenaten: ui top menu config started")

function menu_item(config) { return __extend({ type : "menu_item"}, config) }
function menu_header(config) { return __extend({ type : "menu_header"}, config) }

top_menu_widget = {
	offset : [10, 6],
	item_height : 20,
	background: { pack:PACK_GENERAL, id:121, offset:8 },
	sidebar_offset : 158,
	spacing : 16,
	offset_rotate_basic : 200,

	headers : {
		file 			: menu_header({text: {group:7, id:0}, tooltip:[68, 51] }),
		options			: menu_header({text: {group:2, id:0}, tooltip:[68, 52] }),
		help		   	: menu_header({text: {group:3, id:0}, tooltip:[68, 53] }),
		advisors  		: menu_header({text: {group:4, id:0} }),
		debug		   	: menu_header({text: "Debug" }),
		debug_render  	: menu_header({text: "Render" }),
	},

	file : {
		new_game     	: menu_item({text: {group:1, id:1} }),
		replay_map   	: menu_item({text: {group:1, id:2} }),
		load_game	    : menu_item({text: {group:1, id:3} }),
		save_game	    : menu_item({text: {group:1, id:4} }),
		delete_game	  	: menu_item({text: {group:1, id:6} }),
		exit_game	    : menu_item({text: {group:1, id:5} }),
	},

	options : {
		display_options	: menu_item({text: {group:2, id:1} }),
		sound_options  	: menu_item({text: {group:2, id:2} }),
		speed_options  	: menu_item({text: {group:2, id:3} }),
		difficulty_options: menu_item({ text: {group:2, id:6} }),
		autosave_options: menu_item({text: {group:19, id:51} }),
		hotkeys_options : menu_item({text: "Hotkeys options" }),
		enhanced_options: menu_item({text: "Enhanced options" }),
	},

	help : {
		help 			: menu_item({text: {group:3, id:1} }),
		mouse 			: menu_item({text: {group:3, id:2} }),
		warnings 		: menu_item({text: {group:3, id:5} }),
		about 			: menu_item({text: {group:3, id:7} }),
	},

	advisors : {
		advisor_labor 	 :  menu_item({text:{group: 4, id: ADVISOR_LABOR}, parameter: ADVISOR_LABOR}),
	    advisor_military :  menu_item({text:{group: 4, id: ADVISOR_MILITARY}, parameter: ADVISOR_MILITARY}),
	    advisor_imperial :  menu_item({text:{group: 4, id: ADVISOR_IMPERIAL}, parameter: ADVISOR_IMPERIAL}),
	    advisor_ratings  :  menu_item({text:{group: 4, id: ADVISOR_RATINGS}, parameter: ADVISOR_RATINGS}),
	    advisor_trade    :  menu_item({text:{group: 4, id: ADVISOR_TRADE}, parameter: ADVISOR_TRADE}),
	    advisor_population: menu_item({text:{group: 4, id: ADVISOR_POPULATION}, parameter: ADVISOR_POPULATION}),
	    advisor_health   :  menu_item({text:{group: 4, id: ADVISOR_HEALTH}, parameter: ADVISOR_HEALTH}),
	    advisor_education:  menu_item({text:{group: 4, id: ADVISOR_EDUCATION}, parameter: ADVISOR_EDUCATION}),
	    advisor_entertainment: menu_item({text:{group: 4, id: ADVISOR_ENTERTAINMENT}, parameter: ADVISOR_ENTERTAINMENT}),
	    advisor_religion :  menu_item({text:{group: 4, id: ADVISOR_RELIGION}, parameter: ADVISOR_RELIGION}),
	    advisor_financial:  menu_item({text:{group: 4, id: ADVISOR_FINANCIAL}, parameter: ADVISOR_FINANCIAL}),
	    advisor_chief    :  menu_item({text:{group: 4, id: ADVISOR_CHIEF}, parameter: ADVISOR_CHIEF}),
	},

	debug {
		pages 			: menu_item({text: "", parameter: e_debug_show_pages})
		floods 			: menu_item({text: "", parameter: e_debug_show_floods})
		tile_cache 		: menu_item({text: "", parameter: e_debug_show_tile_cache})
 		sound_channels  : menu_item({text: "", parameter: e_debug_show_sound_channels})
 		properties		: menu_item({text: "", parameter: e_debug_show_properties})
 		show_console    : menu_item({text: "", parameter: e_debug_show_console})
 		make_screenshot : menu_item({text: "", parameter: e_debug_make_screenshot})
 		make_full_screenshot : menu_item({text: "", parameter: e_debug_make_full_screenshot})
 		write_video     : menu_item({text: "", parameter: e_debug_write_video})
	}

	debug_render : {
	    buildings 		: menu_item({text:"xxx Buildings", parameter:e_debug_render_building})
	    tilesize 		: menu_item({text:"xxx Tile size", parameter:e_debug_render_tilesize})
	    roads 			: menu_item({text:"xxx Roads", parameter:e_debug_render_roads})
	    routing_dist 	: menu_item({text:"xxx Routing dist", parameter:e_debug_render_routing_dist})
	    routing_grid 	: menu_item({text:"xxx Routing grid", parameter:e_debug_render_routing_grid})
	    moisture 		: menu_item({text:"xxx Moisture", parameter:e_debug_render_moisture})
	    grass_level 	: menu_item({text:"xxx Grass level", parameter:e_debug_render_grass_level})
	    grass_soil_depletion: menu_item({text:"xxx Soil depl", parameter:e_debug_render_grass_soil_depletion})
	    grass_flood_order	: menu_item({text:"xxx Flood order", parameter:e_debug_render_grass_flood_order})
	    grass_flood_flags	: menu_item({text:"xxx Flood flags", parameter:e_debug_render_grass_flood_flags})
	    labor 			: menu_item({text:"xxx Labor", parameter:e_debug_render_labor})
	    sprite_frames 	: menu_item({text:"xxx Sprite frames", parameter:e_debug_render_sprite_frames})
	    terrain_bits 	: menu_item({text:"xxx Terrain bits", parameter:e_debug_render_terrain_bits})
	    image 			: menu_item({text:"xxx Image", parameter:e_debug_render_image})
	    image_alt 		: menu_item({text:"xxx Image alt", parameter:e_debug_render_image_alt})
	    marshland 		: menu_item({text:"xxx Marshland", parameter:e_debug_render_marshland})
	    terrain_type 	: menu_item({text:"xxx Terrain", parameter:e_debug_render_terrain_type})
	    tile_pos 		: menu_item({text:"xxx Tile coord", parameter:e_debug_render_tile_pos})
	    floodplain_shore: menu_item({text:"xxx Flood shore", parameter:e_debug_render_floodplain_shore})
	    tile_toph 		: menu_item({text:"xxx Tile toph ", parameter:e_debug_render_tile_toph})
	    monuments 		: menu_item({text:"xxx Monuments", parameter:e_debug_render_monuments})
	    figures 		: menu_item({text:"xxx Figures", parameter:e_debug_render_figures})
	    height 			: menu_item({text:"xxx Height", parameter:e_debug_render_height})
	    marshland_depl	: menu_item({text:"xxx Vegetation Growth", parameter:e_debug_render_vegetation_growth})
	    damage_fire 	: menu_item({text:"xxx Damage", parameter:e_debug_render_damage})
	    desirability 	: menu_item({text:"xxx Desirability", parameter:e_debug_render_desirability})
	    shoreline   	: menu_item({text:"xxx River Shore", parameter:e_debug_render_river_shore})
	    entertainment  	: menu_item({text:"xxx Entertainment", parameter:e_debug_render_overall_entertainment})
	    canals       	: menu_item({text:"xxx Canals", parameter:e_debug_render_canals})
	    overlay_add    	: menu_item({text:"xxx Overlay add", parameter:e_debug_render_overlay_add})
	    gardens      	: menu_item({text:"xxx Gardens", parameter:e_debug_render_gardens})
	    routing_noncitizen : menu_item({text:"xxx Routing noncitizen", parameter:e_debug_render_routing_noncitizen})
	    routing_amphibia: menu_item({text:"xxx Routing amphibia", parameter:e_debug_render_routing_amphibia})
	    routing_water   : menu_item({text:"xxx Routing water", parameter:e_debug_render_routing_water})
		invasion_point  : menu_item({text:"xxx Inv. points", parameter: e_debug_render_invasion_point})
		tile_random     : menu_item({text:"xxx Tile random", parameter: e_debug_render_tile_random})
		soldier_strength  : menu_item({text:"xxx Sld. strength", parameter: e_debug_render_soldier_strength})
	},

	ui : {
		background 		: dummy({size:[sw(0), 30], fill_width: true}),
		date            : link({pos:[0, 2], margin:{right: -110}, size:[117, 20], hbody:false, border:false, font_hover:FONT_NORMAL_YELLOW, tooltip:[68, 63] }),
		population   	: link({pos:[0, 2], margin:{right: -310}, size:[117, 20], hbody:false, border:false, font_hover:FONT_NORMAL_YELLOW, tooltip:[68, 62] }),
		funds        	: link({pos:[0, 2], margin:{right: -440}, size:[117, 20], hbody:false, border:false, font_hover:FONT_NORMAL_YELLOW, tooltip:[68, 61] }),
	}
}
