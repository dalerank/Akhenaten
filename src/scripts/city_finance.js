log_info("akhenaten: city finance started")

function city_finance_clamp_tax_percentage(v) {
    if (v < 0) return 0
    if (v > 25) return 25
    return v | 0
}

function city_finance_apply_tax_percentage(value) {
    __city_finance.tax_percentage = city_finance_clamp_tax_percentage(value)
    __city_finance_update_estimate_taxes()
    __city_finance_calculate_totals()
}

[es=event_finance_change_tax]
function city_finance_on_change_tax(ev) {
    city_finance_apply_tax_percentage(__city_finance.tax_percentage + ev.value)
}

function make_finance_year(current) {
    return {
        __property_getter: function(property) { return __city_finance_overview(property, current) }
        income: make_finance_income(current)
        expenses: make_finance_expenses(current)
        @net_in_out { }
        @balance { }
    }
}

function make_finance_income(current) {
    return {
        __property_getter: function(property) { return __city_finance_income(property, current) }
        @taxes { }
        @exports { }
        @donated { }
        @gold_delivered { }
        @total { }
    }
}

function make_finance_expenses(current) {
    return {
        __property_getter: function(property) { return __city_finance_expenses(property, current) }
        @imports { }
        @wages { }
        @construction { }
        @interest { }
        @mayour_salary { }
        @stolen { }
        @tribute { }
        @festivals { }
        @kingdome { }
        @disasters { }
        @total { }
    }
}

city.finance = extend(__city_finance, {
    @tax_percentage { set: city_finance_apply_tax_percentage }
    @is_out_of_money { get: __city_finance_is_out_of_money }

    @has_made_money {
        get: function() {
            var treasury_this_year = city.finance.last_year.expenses.construction + city.finance.treasury
            return treasury_this_year > city.rating.prosperity_treasury_last_year
        }
    }

    this_year : make_finance_year(true)
    last_year : make_finance_year(false)
})



