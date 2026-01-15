log_info("akhenaten: ui advisor financial started")

function advisor_financial_window_inc_tax() { city.finance.tax_percentage = city.finance.tax_percentage + 1 }
function advisor_financial_window_dec_tax() { city.finance.tax_percentage = city.finance.tax_percentage - 1 }

[event=advisor_financial_window_draw]
function advisor_financial_window_update(window) {
    var treasury = city.finance.treasury;
    var prefix = (treasury < 0) ? __loc(60, 3) : __loc(60, 2);
    
    window.treasury.text = prefix + " " + Math.abs(treasury);
    window.treasury.font = (treasury < 0) ? FONT_NORMAL_YELLOW : FONT_NORMAL_WHITE_ON_DARK;

    window.tax_value.text = city.finance.tax_percentage + "% " + __loc(60, 4) + " " + __loc(8, 0) + " " + city.taxes.estimated_income;
    window.tax_payers.text = city.taxes.percentage_taxed_people + "% " + __loc(60, 5) + " " + __loc(60, 22) + " " + city.taxes.estimated_uncollected + " Db";
}

advisor_financial_window {
    row_text_x : 80
    row_last_year_x : 290
    row_this_year_x : 430
    line_start_x : 280
    line_size_x : 250

    rows {
    	imports:"${60.11}"
    }

    ui {
        background   : outer_panel({size[40, 27]})
        advisor_icon : image({pack:PACK_GENERAL, id:128, offset:10, pos[10, 10] })
        title        : header({pos[60, 17], text[60, 0]})

        inner_panel  : inner_panel({pos{x:64, y:48}, size[34, 5]
	        ui {
	            treasury   : text({pos[6, 10]})

	            tax_header : text({text[60, 1], pos[70, 30], font:FONT_NORMAL_WHITE_ON_DARK})
	            tax_value  : text({pos[240, 30], font:FONT_NORMAL_WHITE_ON_DARK})

	            tax_payers : text({pos[10, 60], font:FONT_NORMAL_WHITE_ON_DARK})
	            
                dec_tax    : arrowdown({margin{left:170, top:25}, tiny:false, onclick:advisor_financial_window_dec_tax})
	            inc_tax    : arrowup({margin{left:195, top:25}, tiny:false, onclick:advisor_financial_window_inc_tax})
	        }
	    })

        // table headers
    	last_year       : text({text[60, 6], pos[270, 133], font:FONT_NORMAL_BLACK_ON_LIGHT})
        this_year     : text({text[60, 7], pos[400, 133], font:FONT_NORMAL_BLACK_ON_LIGHT})

        incomes_base  : text({pos[10, 150]})
        expenses_base  : text({pos[10, 240]})
    }
}