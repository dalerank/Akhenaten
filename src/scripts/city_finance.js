log_info("akhenaten: city finance started")

// Native CPTR-backed fields (see city_finance_js.cpp ANK_GLOBAL_OBJECT): treasury, wages,
// wages_kingdome, tax_percentage, estimated_wages, wages_so_far, cheated_money,
// tribute_not_paid_last_year, wage_rate_paid_this_year, wage_rate_paid_last_year — also as __city_finance.*

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

[event=event_finance_change_tax]
function city_finance_on_change_tax(ev) {
    city_finance_apply_tax_percentage(__city_finance.tax_percentage + ev.value)
}

city.finance = {
    __property_getter: __city_get_finance_property

    this_year {
        __property_getter: function(property) { return __city_finance_overview(property, true) }

        income {
            __property_getter: function(property) { return __city_finance_income(property, true) }
            @taxes { }
            @exports { }
            @donated { }
            @gold_delivered { }
            @total { }
        }

        expenses {
            __property_getter: function(property) { return __city_finance_expenses(property, true) }
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

        @net_in_out { }
        @balance { }
    }

    last_year {
        __property_getter: function(property) { return __city_finance_overview(property, false) }

        income {
            __property_getter: function(property) { return __city_finance_income(property, false) }

            @taxes { }
            @exports { }
            @donated { }
            @gold_delivered { }
            @total { }
        }

        expenses {
            __property_getter: function(property) { return __city_finance_expenses(property, false) }
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

        @net_in_out { }
        @balance { }
    }

    @treasury { get: function() { return __city_finance.treasury } }
    @tax_percentage { set: city_finance_apply_tax_percentage }
    @is_out_of_money { get: __city_finance_is_out_of_money }
    @has_made_money {
        get: function() {
            var treasury_this_year = city.finance.last_year.expenses.construction + city.finance.treasury
            return treasury_this_year > city.rating.prosperity_treasury_last_year
        }
    }
}