log_info("akhenaten: ui advisor financial started")

function advisor_financial_window_inc_tax() { city.finance.tax_percentage = city.finance.tax_percentage + 1 }
function advisor_financial_window_dec_tax() { city.finance.tax_percentage = city.finance.tax_percentage - 1 }

[event=advisor_financial_window_draw]
function advisor_financial_window_update(window) {
    var ctreasury = city.finance.treasury
    var prefix = (ctreasury < 0) ? __loc(60, 3) : __loc(60, 2)
    
    window.treasury.text = prefix + " " + Math.abs(ctreasury)
    window.treasury.font = (ctreasury < 0) ? FONT_NORMAL_YELLOW : FONT_NORMAL_WHITE_ON_DARK

    window.tax_value.text = city.finance.tax_percentage + "% " + __loc(60, 4) + " " + __loc(8, 0) + " " + city.taxes.estimated_income
    window.tax_payers.text = city.taxes.percentage_taxed_people + "% " + __loc(60, 5) + " " + __loc(60, 22) + " " + city.taxes.estimated_uncollected + " Db"
}

[event=advisor_financial_window_draw]
function advisor_financial_window_update_incomes(window) {
    var last_year = city.finance.last_year
    var this_year = city.finance.this_year
    
    var line_y = 150
    var row_text_x = 80
    var row_last_year_x = 290
    var row_this_year_x = 430
    var line_start_x = 280
    var line_size_x = 250
    
    function draw_row(text, y, value_last_year, value_this_year) {
        ui.label(text, vec2i(row_text_x, y), FONT_NORMAL_BLACK_ON_LIGHT)
        ui.label(String(value_last_year), vec2i(row_last_year_x, y), FONT_NORMAL_BLACK_ON_LIGHT)
        ui.label(String(value_this_year), vec2i(row_this_year_x, y), FONT_NORMAL_BLACK_ON_LIGHT)
        return y + 15
    }
    
    // INCOMES rows
    line_y = draw_row(__loc(60, 8), line_y, last_year.income.taxes, this_year.income.taxes)
    line_y = draw_row(__loc(60, 9), line_y, last_year.income.exports, this_year.income.exports)
    line_y = draw_row(__loc(60, 20), line_y, last_year.income.donated, this_year.income.donated)
    line_y = draw_row(__loc(60, 24), line_y, last_year.income.gold_delivered, this_year.income.gold_delivered)
    
    ui.line(true, vec2i(line_start_x, line_y), line_size_x)
    line_y += 5

    line_y = draw_row(__loc(60, 10), line_y, last_year.income.total, this_year.income.total)
}

[event=advisor_financial_window_draw]
function advisor_financial_window_update_expenses(window) {
    var last_year = city.finance.last_year
    var this_year = city.finance.this_year

    var line_y = 240
    var row_text_x = 80
    var row_last_year_x = 290
    var row_this_year_x = 430
    var line_start_x = 280
    var line_size_x = 250

    function draw_row(text, y, value_last_year, value_this_year) {
        ui.label(text, vec2i(row_text_x, y), FONT_NORMAL_BLACK_ON_LIGHT)
        ui.label(String(value_last_year), vec2i(row_last_year_x, y), FONT_NORMAL_BLACK_ON_LIGHT)
        ui.label(String(value_this_year), vec2i(row_this_year_x, y), FONT_NORMAL_BLACK_ON_LIGHT)
        return y + 15
    }

    // EXPENSES rows
    line_y = draw_row(__loc(60, 11), line_y, last_year.expenses.imports, this_year.expenses.imports)
    line_y = draw_row(__loc(60, 12), line_y, last_year.expenses.wages, this_year.expenses.wages)
    line_y = draw_row(__loc(60, 13), line_y, last_year.expenses.construction, this_year.expenses.construction)
    line_y = draw_row(__loc(60, 14), line_y, last_year.expenses.interest, this_year.expenses.interest)
    line_y = draw_row(__loc(60, 16), line_y, last_year.expenses.stolen, this_year.expenses.stolen)
    line_y = draw_row(__loc(60, 21), line_y, last_year.expenses.tribute, this_year.expenses.tribute)
    line_y = draw_row(__loc(60, 22), line_y, last_year.expenses.festivals, this_year.expenses.festivals)
    line_y = draw_row(__loc(60, 23), line_y, last_year.expenses.kingdome, this_year.expenses.kingdome)
    line_y = draw_row(__loc(60, 24), line_y, last_year.expenses.disasters, this_year.expenses.disasters)

    ui.line(true, vec2i(line_start_x, line_y), line_size_x);
    line_y += 5

    line_y = draw_row(__loc(60, 17), line_y, last_year.expenses.total, this_year.expenses.total)
    line_y = draw_row(__loc(60, 18), line_y, last_year.net_in_out, this_year.net_in_out)
}

advisor_financial_window {
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