log_info("akhenaten: ui overlay menu started")

overlay_menu {
	menus [
		{
			title[14, 0] //"None"
			ids[OVERLAY_NONE]		
		}

		{
			title[14, 2] //"Water"
			ids[OVERLAY_WATER]
		}

		{
			title[14, 1] //"Risks"
			ids[ 
			    OVERLAY_FIRE,
				OVERLAY_DAMAGE,
				OVERLAY_CRIME,
				OVERLAY_CRIMINAL,
				OVERLAY_NATIVE,
				OVERLAY_PROBLEMS,
				OVERLAY_LABOR,
				OVERLAY_ROUTING
	        ]
	    }

	    {
	    	title[14, 3] //"Entertainment"
	    	ids[
	    		OVERLAY_ENTERTAINMENT,
				OVERLAY_BOOTH,
				OVERLAY_BANDSTAND,
				OVERLAY_PAVILION,
				OVERLAY_SENET_HOUSE,
	    	]
	    }

	    {
	    	title[14, 5] //"Education"
	    	ids[
	    		OVERLAY_EDUCATION,
			    OVERLAY_SCRIBAL_SCHOOL,
			    OVERLAY_LIBRARY,
			    OVERLAY_ACADEMY,
	    	]
	    }

	    {
	    	title[14, 6] //"Health"
	    	ids[
	    	    OVERLAY_HEALTH,
				OVERLAY_APOTHECARY,
				OVERLAY_PHYSICIAN,
				OVERLAY_DENTIST,
				OVERLAY_MORTUARY,
				// OVERLAY_DISEASE
				// OVERLAY_INFECTED_HOUSING
				// OVERLAY_MALARIA
	    	]
	    }

	    {
	    	title[14, 7] //"Administration"
	    	ids[
	    		OVERLAY_TAX_INCOME,
			    OVERLAY_BAZAAR_ACCESS,
			    OVERLAY_DESIRABILITY,
			    OVERLAY_FERTILITY,
			    OVERLAY_COUTHOUSE,
			    OVERLAY_FOOD_STOCKS,
			    OVERLAY_LABOR_ACCESS,
			    // OVERLAY_LABOR
			    // OVERLAY_ADMINISTRATION_PROBLEMS
			    // OVERLAY_WATER_CROSSINGS
			    // OVERLAY_EMPTY_HOUSING
			    // OVERLAY_MAGISTRATE
	    	]
	    }

	    {
	    	title[14, 4] //"Religion"
	    	ids[
	    		OVERLAY_RELIGION,
			    OVERLAY_RELIGION_OSIRIS,
			    OVERLAY_RELIGION_RA,
			    OVERLAY_RELIGION_PTAH,
			    OVERLAY_RELIGION_SETH,
			    OVERLAY_RELIGION_BAST,
	    	]
	    }

	    {
	    	title: "Food"
	    	ids[
	    		// OVERLAY_GRAIN
	    		// OVERLAY_CHICKPEAS
				// OVERLAY_POMEGRANATES
				// OVERLAY_FIGS
				// OVERLAY_MEAT
				// OVERLAY_GAME
				// OVERLAY_POTTERY
				// OVERLAY_JEWELRY
				// OVERLAY_LINEN
				// OVERLAY_BEER
	    	]
	    }

	    {
	    	title: "Other"
	    	ids[
				// OVERLAY_IRRIGATION
				// OVERLAY_CITY_DEFENSES
				// OVERLAY_HIDE_CLIFFS
	    	]
	    }
	]
}

overlay_menu_widget {
	pos [-85, 20]
	ui {
		category_item : dummy({pos[0, 24], size[160, 20]})
		submenu_image : image({pos[-17, 6], pack:PACK_GENERAL, id:158, enabled:false})
		submenu_item  : dummy({pos[-185, 24], size[160, 20]}) 
	}
}