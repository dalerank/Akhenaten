log_info("akhenaten: ui advisor financial started")

advisor_financial_window = {
    row_text_x : 80,
    row_last_year_x : 290,
    row_this_year_x : 430,
    line_start_x : 280,
    line_size_x : 250,
    ui : {
        background   : outer_panel({size:[40, 27]}),
        advisor_icon : image({pack:PACK_GENERAL, id:128, offset:10, pos:[10, 10] }),
        title        : header({pos:[60, 17], text:[60, 0]}),

        inner_panel  : inner_panel({pos:[64, 48], size:[34, 5],
	        ui : {
	            treasury   : text({pos:[6, 10]}),
	            tax_header : text({text:[60, 1], pos:[70, 30], font:FONT_NORMAL_WHITE_ON_DARK}),
	            tax_value  : text({pos:[240, 30], text:"${city.tax_percentage}% ${60.4} ${8.0} ${city.estimated_tax_income}", font:FONT_NORMAL_WHITE_ON_DARK}),

	            tax_payers : text({pos:[10, 60], text:"${city.percentage_taxed_people}% ${60.5} ${60.22} ${city.estimated_tax_uncollected} Db", font:FONT_NORMAL_WHITE_ON_DARK}),
	            dec_tax    : arrowdown({pos:[170, 25], tiny:false}),
	            inc_tax    : arrowup({pos:[195, 25], tiny:false}),
	        }
	    }),

        // table headers
    	last_year       : text({text:[60, 6], pos:[270, 133], font:FONT_NORMAL_BLACK_ON_LIGHT}),
        this_year     : text({text:[60, 7], pos:[400, 133], font:FONT_NORMAL_BLACK_ON_LIGHT}),

        incomes_base  : text({pos:[10, 150]}),
        expenses_base  : text({pos:[10, 240]}),
    }
}