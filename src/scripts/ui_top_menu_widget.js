log_info("akhenaten: ui top menu config started")

function menu_item(config) { return __extend({ type : "menu_item"}, config) }
function menu_header(config) { return __extend({ type : "menu_header"}, config) }

window top_menu_widget = {
	offset : [10, 6],
	item_height : 20,
	background: { pack:PACK_GENERAL, id:121, offset:8 },
	sidebar_offset : 158,
	spacing : 32,
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

	debug : {
		pages 			: menu_item({text: "", parameter: 0}),
		game_time 		: menu_item({text: "", parameter: 1}),
		build_planner   : menu_item({text: "", parameter: 2}),
		religion 		: menu_item({text: "", parameter: 3}),
		tutorial 		: menu_item({text: "", parameter: 4}),
		floods 			: menu_item({text: "", parameter: 5}),
		camera 			: menu_item({text: "", parameter: 6}),
		tile_cache 		: menu_item({text: "", parameter: 7}),
		migration 		: menu_item({text: "", parameter: 8}),
 		sentiment 		: menu_item({text: "", parameter: 9}),
 		sound_channels  : menu_item({text: "", parameter: 10}),
 		properties		: menu_item({text: "", parameter: 11}),
 		show_console    : menu_item({text: "", parameter: 12}),
 		make_screenshot : menu_item({text: "", parameter: 13}),
 		make_full_screenshot : menu_item({text: "", parameter: 14}),
 		write_video     : menu_item({text: "", parameter: 15}),
		clouds          : menu_item({text: "", parameter: 16}),
	},

	debug_render : {
	    building 		: menu_item({text:"", parameter:1}),
	    tilesize 		: menu_item({text:"", parameter:2}),
	    roads 			: menu_item({text:"", parameter:3}),
	    routing_dist 	: menu_item({text:"", parameter:4}),
	    routing_grid 	: menu_item({text:"", parameter:5}),
	    moisture 		: menu_item({text:"", parameter:6}),
	    grass_level 	: menu_item({text:"", parameter:7}),
	    grass_soil_depletion: menu_item({text:"", parameter:8}),
	    grass_flood_order	: menu_item({text:"", parameter:9}),
	    grass_flood_flags	: menu_item({text:"", parameter:10}),
	    labor 			: menu_item({text:"", parameter:11}),
	    sprite_frames 	: menu_item({text:"", parameter:12}),
	    terrain_bits 	: menu_item({text:"", parameter:13}),
	    image 			: menu_item({text:"", parameter:14}),
	    image_alt 		: menu_item({text:"", parameter:15}),
	    marshland 		: menu_item({text:"", parameter:16}),
	    terrain_type 	: menu_item({text:"", parameter:17}),
	    tile_pos 		: menu_item({text:"", parameter:20}),
	    floodplain_shore: menu_item({text:"", parameter:21}),
	    tile_toph 		: menu_item({text:"", parameter:22}),
	    monuments 		: menu_item({text:"", parameter:23}),
	    figures 		: menu_item({text:"", parameter:24}),
	    height 			: menu_item({text:"", parameter:25}),
	    marshland_depl	: menu_item({text:"", parameter:26}),
	    damage_fire 	: menu_item({text:"", parameter:27}),
	    desirability 	: menu_item({text:"", parameter:28}),
	    shoreline   	: menu_item({text:"", parameter:29}),
	},

	ui : {
		background 		: dummy({size:[sw(0), 30]}),
		date          	: link({pos:[0, 2], margin:{right: -150}, size:[117, 20], hbody:false, border:false, font_hover:FONT_NORMAL_YELLOW, tooltip:[68, 63] }),
		population   	: link({pos:[0, 2], margin:{right: -320}, size:[117, 20], hbody:false, border:false, font_hover:FONT_NORMAL_YELLOW, tooltip:[68, 62] }),
		funds        	: link({pos:[0, 2], margin:{right: -450}, size:[117, 20], hbody:false, border:false, font_hover:FONT_NORMAL_YELLOW, tooltip:[68, 62] }),
	}
}
