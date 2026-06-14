log_info("akhenaten: sentiment_debug")

[es=event_draw_debug_properties]
function sentiment_debug_draw_properties(ev) {
    if (!imgui.tree_node_ex("Sentiment")) {
        return
    }

    imgui.begin_table("Sentiment", 2, imgui.table_flags_debug_props())
    imgui.property_input("value:", __city_sentiment, "value")
    imgui.property_input("previous_value:", __city_sentiment, "previous_value")
    imgui.property_input("message_delay:", __city_sentiment, "message_delay")
    imgui.property_input("include_tents:", __city_sentiment, "include_huts")
    imgui.property_input("unemployment_pct:", __city_sentiment, "unemployment_pct")
    imgui.property_input("wages:", __city_sentiment, "wages")
    imgui.property_input("low_mood_cause:", __city_sentiment, "low_mood_cause")
    imgui.property_input("protesters:", __city_sentiment, "protesters")
    imgui.property_input("criminals:", __city_sentiment, "criminals")
    imgui.property_input("can_create_mugger:", __city_sentiment, "can_create_mugger")
    imgui.property_input("can_create_protestor:", __city_sentiment, "can_create_protestor")
    imgui.property_input("last_mugger_message:", __city_sentiment, "last_mugger_message")
    imgui.property_input("contribution_taxes:", __city_sentiment, "contribution_taxes")
    imgui.property_input("contribution_wages:", __city_sentiment, "contribution_wages")
    imgui.property_input("contribution_employment:", __city_sentiment, "contribution_employment")
    imgui.property_input("penalty_huts:", __city_sentiment, "contribution_penalty_huts")
    imgui.property_input("monuments:", __city_sentiment, "contribution_monuments")
    imgui.property_input("religion_coverage:", __city_sentiment, "contribution_religion_coverage")
    imgui.end_table()
    imgui.tree_pop()
}
