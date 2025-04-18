log_info("akhenaten: ui advisor education started")

window advisor_education_window = {
	ui : {
		background   : outer_panel({size:[40, 16]}),
		advisor_icon : image({pack:PACK_GENERAL, id:128, offset:7, pos:[10, 10] }),
		title 	     : header({pos:[60, 17], text:[57, 0]}),
	  population   : text_center({pos:[20, 50], size:[200, 20],  font: FONT_NORMAL_BLACK_ON_LIGHT}),
	  school_age   : text_center({pos:[220, 50], size:[200, 20], font: FONT_NORMAL_BLACK_ON_LIGHT}),
	  academy_age  : text_center({pos:[420, 50], size:[200, 20], font: FONT_NORMAL_BLACK_ON_LIGHT}),

	  // table headers
    header1 	   : text({text:[57, 4], pos:[180, 86], font:FONT_SMALL_PLAIN}),
    header2 	   : text({text:[57, 5], pos:[290, 86], font:FONT_SMALL_PLAIN}),
    header3 	   : text({text:[57, 6], pos:[478, 86], font:FONT_SMALL_PLAIN}),

		inner_panel  : inner_panel({pos:[32, 108], size:[36, 4],
    	ui : {
    		school_total     : text({pos:[5, 5], size:[100, 20],  font: FONT_NORMAL_WHITE_ON_DARK}),
    		school_active    : text_center({pos:[100, 5], size:[150, 20],  font: FONT_NORMAL_WHITE_ON_DARK}),
    		school_care      : text_center({pos:[280, 5], size:[40, 20], font:FONT_NORMAL_WHITE_ON_DARK}),
    		school_covg      : text_center({pos:[440, 5], size:[60, 20], font:FONT_NORMAL_WHITE_ON_DARK}),

    		academies_total  : text({pos:[5, 23], size:[100, 20],  font: FONT_NORMAL_WHITE_ON_DARK}),
    		academies_active : text_center({pos:[100, 23], size:[150, 20],  font: FONT_NORMAL_WHITE_ON_DARK}),
    		academies_care   : text_center({pos:[280, 23], size:[40, 20], font:FONT_NORMAL_WHITE_ON_DARK}),
    		academies_covg   : text_center({pos:[440, 23], size:[60, 20], font:FONT_NORMAL_WHITE_ON_DARK}),

    		libraries_total  : text({pos:[5, 42], size:[100, 20],  font: FONT_NORMAL_WHITE_ON_DARK}),
    		libraries_active : text_center({pos:[100, 42], size:[150, 20],  font: FONT_NORMAL_WHITE_ON_DARK}),
    		libraries_care   : text_center({pos:[280, 42], size:[40, 20], font:FONT_NORMAL_WHITE_ON_DARK}),
    		libraries_covg   : text_center({pos:[440, 42], size:[60, 20], font:FONT_NORMAL_WHITE_ON_DARK}),
    	}
    }),

    education_advice : multiline({pos:[60, 180], wrap:px(32), font: FONT_NORMAL_BLACK_ON_LIGHT })
	}
}