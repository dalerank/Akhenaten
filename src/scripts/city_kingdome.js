log_info("akhenaten: city kingdome started")

gift_type {
    MODEST : 0
    GENEROUS : 1
    LAVISH : 2
    ROYAL : 3
    KINGDOM : 4
    KINGDOM_ROYAL : 5
    KINGDOM_LAVISH : 6
    KINGDOM_GENEROUS : 7
    KINGDOM_MODEST : 8
    COUNT : 9
}

city.kingdome = extend(__city_kingdome, {
    // salary_rank
    // player_rank
    // kingdom_change
    // kingdom_salary_penalty
    // kingdom_milestone_penalty
    // kingdom_ignored_request_penalty
    // donate_amount

    selected_size : gift_type.MODEST

    gift_rules [
        {
            id : gift_type.MODEST
            rate : 8
            minimum : 20
        }
        {
            id : gift_type.GENEROUS
            rate : 4
            minimum : 50
        }
        {
            id : gift_type.LAVISH
            rate : 2
            minimum : 100
        }
    ]

    gifts [
        { id: 0, cost: 0 }
        { id: 0, cost: 0 }
        { id: 0, cost: 0 }
    ]
})

city.kingdome.can_send_gift = function(size) {
    return city.kingdome.gift_cost(size) <= city.kingdome.personal_savings
}

city.kingdome.gift_item_id = function(size) {
    return city.kingdome.gifts[size].id
}

city.kingdome.gift_cost = function(size) {
    return city.kingdome.gifts[size].cost
}

city.kingdome.set_donation_amount = function(amount) {
    var cap = city.kingdome.personal_savings
    city.kingdome.donate_amount = Math.max(0, Math.min(amount, cap))
}

city.kingdome.change_donation_amount = function(delta) {
    city.kingdome.set_donation_amount(city.kingdome.donate_amount + delta)
}

city.kingdome.recompute_gift_costs = function(savings) {
    var sr = Math.floor(Number(savings))
    if (sr < 0) {
        sr = 0
    }

    function cost_for(size) {
        var rules = city.kingdome.gift_rules
        for (var i = 0; i < rules.length; i++) {
            var r = rules[i]
            if (r.id === size) {
                return Math.floor(sr / r.rate + r.minimum)
            }
        }
        return 100
    }

    city.kingdome.gifts[0].cost = cost_for(gift_type.MODEST)
    city.kingdome.gifts[1].cost = cost_for(gift_type.GENEROUS)
    city.kingdome.gifts[2].cost = cost_for(gift_type.LAVISH)
}

city.kingdome.update_gifts = function() {
    city.kingdome.recompute_gift_costs(city.kingdome.personal_savings)
}

city.kingdome.reset_gifts = function() {
    for (var i = 0; i < 3; i++) {
        city.kingdome.gifts[i].id = 0
        city.kingdome.gifts[i].cost = 0
    }
}

function kingdome_apply_rating_delta(delta) {
    var cap = city.kingdome.rating_cap
    var r = Math.clamp(city.kingdome.rating + delta, 0, cap)
    city.kingdome.rating = r
}

city.kingdome.send_gift = function(gift_size) {
    if (gift_size < 0 || gift_size > 2) {
        return
    }
    var cost = city.kingdome.gifts[gift_size].cost
    if (cost > city.kingdome.personal_savings) {
        return
    }

    var o = city.kingdome.gift_overdose_penalty
    var first = kingdome_relation.gift_relation_change_first
    var second = kingdome_relation.gift_relation_change_second
    var third = kingdome_relation.gift_relation_change_third
    var last = kingdome_relation.gift_relation_change_last

    if (o <= 0) {
        city.kingdome.gift_overdose_penalty = 1
        kingdome_apply_rating_delta(first[gift_size])
    } else if (o === 1) {
        city.kingdome.gift_overdose_penalty = 2
        kingdome_apply_rating_delta(second[gift_size])
    } else if (o === 2) {
        city.kingdome.gift_overdose_penalty = 3
        kingdome_apply_rating_delta(third[gift_size])
    } else if (o === 3) {
        city.kingdome.gift_overdose_penalty = 4
        kingdome_apply_rating_delta(last[gift_size])
    }

    city.kingdome.months_since_gift = 0
    var nid = city.kingdome.gifts[gift_size].id + 1
    if (nid >= 4) {
        nid = 0
    }
    city.kingdome.gifts[gift_size].id = nid
    city.kingdome.personal_savings -= cost
}

city.kingdome.donate_savings_to_city = function() {
    var a = city.kingdome.donate_amount
    emit event_finance_donation{ amount: a }
    city.kingdome.personal_savings -= a
    __city_finance_calculate_totals()
}

[es=event_kingdome_update_gifts]
function kingdome_relation_on_update_gifts(ev) {
    city.kingdome.recompute_gift_costs(ev.personal_savings)
}

[es=event_mission_start]
function kingdome_relation_on_mission_start_gifts(ev) {
    city.kingdome.reset_gifts()
    city.kingdome.recompute_gift_costs(city.kingdome.personal_savings)
}

[es=event_send_gift_to_kingdome]
function kingdome_relation_on_send_gift_to_kingdome(ev) {
    city.kingdome.send_gift(ev.gift_size)
}
