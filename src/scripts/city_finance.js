log_info("akhenaten: city finance started")

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

    @treasury { get: __city_finance_get_treasury }
    @tax_percentage { set: __city_finance_set_tax_percentage }
}