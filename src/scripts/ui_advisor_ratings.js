log_info("akhenaten: ui advisor ratings started")

advisor_ratings_window = {
  ui : {
		background 		: outer_panel({size:[40, 27] }),
		background_image : image({pack:PACK_UNLOADED, id:2, pos :[60, 38]	}),
		rating_culture: button({pos:[80, 276], align:"xcenter", size:[120, 60], tooltip:[68, 104],
			ui : {
				value_culture : text({pos: [0, 22], size:[120, 20], align:"center", font : FONT_LARGE_BLACK_ON_LIGHT }),
				goal_culture  : text({pos: [0, 42], size:[120, 20], align:"center", font : FONT_NORMAL_BLACK_ON_LIGHT }),
			}
		}),
		
		base_culture  : text({pos: [110, 213], align:"center", font : FONT_LARGE_BLACK_ON_LIGHT }),

		rating_prosperity : button({pos:[200, 276], align:"xcenter", size:[120, 60], tooltip:[68, 105],
			ui : {
		 	  value_prosperity: text({pos: [0, 22], size:[120, 20], align:"center", font : FONT_LARGE_BLACK_ON_LIGHT }),
				goal_prosperity : text({pos: [0, 42], size:[120, 20], align:"center", font : FONT_NORMAL_BLACK_ON_LIGHT }),
			}
		}),
		base_prosperity : text({pos: [230, 213], align:"center", font : FONT_LARGE_BLACK_ON_LIGHT }),

		rating_monument: button({pos:[320, 276], align:"xcenter", size:[120, 60], tooltip:[68, 106],
			ui : {
				value_monument: text({pos: [0, 22], size:[120, 20], align:"center", font : FONT_LARGE_BLACK_ON_LIGHT }),
				goal_monument : text({pos: [0, 42], size:[120, 20], align:"center", font : FONT_NORMAL_BLACK_ON_LIGHT }),
			}
		}),
		
		base_monument : text({pos: [350, 213], align:"center", font : FONT_LARGE_BLACK_ON_LIGHT }),

		rating_kingdom: button({pos:[440, 276], align:"xcenter", size:[120, 60], tooltip:[68, 107],
			ui : {
				value_kingdom : text({pos: [0, 22], size:[120, 20], align:"center", font : FONT_LARGE_BLACK_ON_LIGHT }),
				goal_kingdom  : text({pos: [0, 42], size:[120, 20], align:"center", font : FONT_NORMAL_BLACK_ON_LIGHT }),
			}
		}),
		
		base_kingdom  : text({pos: [470, 213], align:"center", font : FONT_LARGE_BLACK_ON_LIGHT }),
		
		inner_panel 	: inner_panel({pos:[40, 340], size:[35, 5] }),
		advice_header : text({pos: [68, 344], font : FONT_NORMAL_WHITE_ON_DARK }),
		advice_text 	: text({pos: [68, 368], wrap:520, font : FONT_NORMAL_WHITE_ON_DARK, multiline:true }),
		advisor_icon 	: image({pack:PACK_GENERAL, id:128, offset:3, pos:[10, 10] }),
		header_label 	: label({font : FONT_LARGE_BLACK_ON_LIGHT, text: {group: 53, id: 0},	pos:[60, 17] }),
		population_label : label({pos :[300, 20], font : FONT_NORMAL_BLACK_ON_LIGHT}), 
	},
	column_offset   : {x: 30, y:-11}
}
