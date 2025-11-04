log_info("akhenaten: migration config started")

migration_defaults {
    max_immigration_amount_per_batch : 4
    max_emigration_amount_per_batch : 4
    max_newcomers_per_update : 12
    max_leftovers_per_update : 12
}

migration_sentiment_influence = [
    {s: 70, i:  100},
    {s: 60, i:  75},
    {s: 50, i:  50},
    {s: 40, i:  0},
    {s: 30, i: -10},
    {s: 20, i: -25},
    {s: 0,  i: -50},
]

migration {
    [property]
    population_cap { set: function(cap) { set_population_cap(cap) } }
}