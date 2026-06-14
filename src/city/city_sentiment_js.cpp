#include "city_sentiment.h"

#include "city/city.h"
#include "js/js_game.h"
#include "js/js_global_object.h"

ANK_GLOBAL_OBJECT(g_city.sentiment, __city_sentiment,
    value,
    previous_value,
    message_delay,
    include_huts,
    unemployment_pct,
    wages,
    low_mood_cause,
    protesters,
    criminals,
    can_create_mugger,
    can_create_protestor,
    last_mugger_message,
    contribution_taxes,
    contribution_wages,
    contribution_employment,
    contribution_penalty_huts,
    contribution_monuments,
    contribution_religion_coverage);
