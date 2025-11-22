log_info("akhenaten: migration config started")

migration_defaults {
    max_immigration_amount_per_batch : 4
    max_emigration_amount_per_batch : 4
    max_newcomers_per_update : 12
    max_leftovers_per_update : 12
}

migration_sentiment_influence = [
    {s: 70, i:  100}
    {s: 60, i:  75}
    {s: 50, i:  50}
    {s: 40, i:  0}
    {s: 30, i: -10}
    {s: 20, i: -25}
    {s: 0,  i: -50}
]

migration_unemployment_percentage = [
    {u: 100, p: -240}
    {u: 90, p: -220}
    {u: 80, p: -200}
    {u: 70, p: -180}
    {u: 60, p: -160}
    {u: 50, p: -140}
    {u: 40, p: -120}
    {u: 30, p: -100}
    {u: 25, p: -80}
    {u: 20, p: -40}
    {u: 15, p: -20}
    {u: 10, p: -10}
    {u: 0,  p: 0}
]

migration {
    set_population_cap: __migration_set_population_cap
}