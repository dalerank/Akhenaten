log_info("akhenaten: ui advisor chief started")

advisor_chief_window = {
	ui : {
		outer_panel : { type : "outer_panel", pos:[0, 0], size:[40, 27] },
		advisor_icon : { type : "image", pack:PACK_GENERAL, id:128, offset:11, pos:[10, 10] },
		header_label : { type : "label", font : FONT_LARGE_BLACK_ON_LIGHT, text:"#chief_overseer",	pos:[60, 17]},
		inner_panel : { type : "inner_panel", pos:[17, 60], size:[38, 17] },

		// sentiment
		sentiment_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 67] },
		sentiment_label : { type : "label", pos:[44, 66], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_sentiment"},
		sentiment_info : { type : "label", pos:[185, 66], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// migration
		migration_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 87] },
		migration_label : { type : "label", pos:[44, 86], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_migration"},
		migration_info : { type : "label", pos:[185, 86], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// workers
		workers_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 107] },
		workers_label : { type : "label", pos:[44, 106], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_workers"},
		workers_info : { type : "label", pos:[185, 106], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// food stocks
		foodstocks_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 127] },
		foodstocks_label : { type : "label", pos:[44, 126], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_foodstocks"},
		foodstocks_info : { type : "label", pos:[185, 126], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// food consumption
		foodconsumption_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 147] },
		foodconsumption_label : { type : "label", pos:[44, 146], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_foodconsumption"},
		foodconsumption_info : { type : "label", pos:[185, 146], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// health
		health_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 167] },
		health_label : { type : "label", pos:[44, 166], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_health"},
		health_info : { type : "label", pos:[185, 166], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// religion
		religion_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 187] },
		religion_label : { type : "label", pos:[44, 186], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_religion"},
		religion_info : { type : "label", pos:[185, 186], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// finance
		finance_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 207] },
		finance_label : { type : "label", pos:[44, 206], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_finance"},
		finance_info : { type : "label", pos:[185, 206], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// crime
		crime_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 227] },
		crime_label : { type : "label", pos:[44, 226], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_crime"},
		crime_info : { type : "label", pos:[185, 226], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// military
		military_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 247] },
		military_label : { type : "label", pos:[44, 246], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_military"},
		military_info : { type : "label", pos:[185, 246], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// kingdom
		kingdom_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 267] },
		kingdom_label : { type : "label", pos:[44, 266], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_kingdom"},
		kingdom_info : { type : "label", pos:[185, 266], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},

		// nilometr
		nilometr_icon : { type : "image", pack:PACK_GENERAL, id:158, pos:[26, 287] },
		nilometr_label : { type : "label", pos:[44, 286], font:FONT_NORMAL_WHITE_ON_DARK, text:"#chief_adv_nilometr"},
		nilometr_info : { type : "label", pos:[185, 286], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},
		nilometr_info2 : { type : "label", pos:[185, 306], font:FONT_NORMAL_BLACK_ON_LIGHT, wrap:400},
	}
}