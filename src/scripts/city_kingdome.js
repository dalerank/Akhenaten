log_info("akhenaten: city kingdome started")

city.kingdome = extend(__city_kingdome, {
    // salary_rank
    // player_rank
    // kingdom_change
    // kingdom_salary_penalty
    // kingdom_milestone_penalty
    // kingdom_ignored_request_penalty
    // donate_amount
    set_donation_amount: function(amount) {
        var cap = city.kingdome.personal_savings
        city.kingdome.donate_amount = Math.max(0, Math.min(amount, cap))
    },
    change_donation_amount: function(delta) {
        city.kingdome.set_donation_amount(city.kingdome.donate_amount + delta)
    },
    donate_savings_to_city: function() {
        var a = city.kingdome.donate_amount
        emit event_finance_donation{ amount: a }
        city.kingdome.personal_savings -= a
        __city_finance_calculate_totals()
    },
})
