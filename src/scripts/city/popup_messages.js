log_info("akhenaten: popup message categories started")

popup_message_categories = [
    {
        category: POPUP_MSG_FLOOD, hint: "nilometer flood predictions",
        messages: ["message_perfect_inundation", "message_excellent_inundation", "message_good_inundation",
                   "message_mediocre_inundation", "message_poor_inundation", "message_no_inundation",
                   "message_mediocre_inundation_seers", "message_poor_inundation_seers"]
    }
    {
        category: POPUP_MSG_POPULATION, hint: "population milestones",
        messages: ["message_population_milestone_100", "message_population_milestone_500",
                   "message_population_milestone_1000", "message_population_milestone_2000",
                   "message_population_milestone_3000", "message_population_milestone_5000",
                   "message_population_milestone_10000", "message_population_milestone_15000",
                   "message_population_milestone_20000", "message_population_milestone_25000"]
    }
    {
        category: POPUP_MSG_COMPLIANCE, hint: "a request can now be fulfilled",
        messages: ["message_compliance_now_possible", "message_storage_yards_ready_to_fulfill_request"]
    }
    {
        category: POPUP_MSG_KINGDOM, hint: "kingdom requests, set by the scenario events that post them",
        messages: []
    }
    {
        category: POPUP_MSG_FESTIVALS, hint: "festivals held",
        messages: ["message_common_festival", "message_lavish_festival", "message_grand_festival"]
    }
    {
        category: POPUP_MSG_MINOR_BLESSINGS, hint: "minor blessings from the gods",
        messages: ["message_small_blessing_from_osiris", "message_minor_blessing_from_ra",
                   "message_minor_blessing_from_ptah", "message_minor_blessing_from_seth",
                   "message_small_blessing_from_bast", "message_minor_blessing_trading_from_ra"]
    }
    {
        category: POPUP_MSG_PRICE, hint: "trade price changes",
        messages: ["message_price_increased", "message_price_decreased"]
    }
    {
        category: POPUP_MSG_TRADE_LEVEL, hint: "trade level changes",
        messages: ["message_increased_trading", "message_decreased_trading", "message_trade_stopped"]
    }
    {
        category: POPUP_MSG_WAGE, hint: "kingdom wage changes",
        messages: ["message_kingdome_raises_wages", "message_kingdome_lowers_wages"]
    }
    {
        category: POPUP_MSG_DISEASE, hint: "disease outbreaks",
        messages: ["message_disease", "message_disease_strikes"]
    }
    {
        category: POPUP_MSG_MALARIA, hint: "malaria outbreaks",
        messages: ["message_malaria"]
    }
    {
        category: POPUP_MSG_EMPLOYEES, hint: "employees needed",
        messages: ["message_employees_needed"]
    }
]
