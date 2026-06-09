log_info("akhenaten: migration_debug")

[es=event_draw_debug_properties]
function migration_debug_draw_properties(ev) {
    if (!imgui.tree_node_ex("Migration")) {
        return
    }

    imgui.begin_table("Migration", 2, imgui.table_flags_debug_props())
    imgui.property_input("invading_cap", __city_migration, "invading_cap")
    imgui.property_input("migration_cap", __city_migration, "migration_cap")
    imgui.property_input("percentage_by_sentiment", __city_migration, "percentage_by_sentiment")
    imgui.property_input("percentage_by_unemployments", __city_migration, "percentage_by_unemployments")
    imgui.property_input("emigration_message_shown", __city_migration, "emigration_message_shown")
    imgui.property_input("newcomers", __city_migration, "newcomers")
    imgui.property_input("percentage", __city_migration, "percentage")
    imgui.property_input("no_immigration_cause", __city_migration, "no_immigration_cause")
    imgui.property_input("refused_immigrants_today", __city_migration, "refused_immigrants_today")
    imgui.property_input("emigrated_today", __city_migration, "emigrated_today")
    imgui.property_input("immigrated_today", __city_migration, "immigrated_today")
    imgui.property_input("emigration_queue_size", __city_migration, "emigration_queue_size")
    imgui.property_input("immigration_queue_size", __city_migration, "immigration_queue_size")
    imgui.property_input("immigration_duration", __city_migration, "immigration_duration")
    imgui.property_input("emigration_amount_per_batch", __city_migration, "emigration_amount_per_batch")
    imgui.property_input("emigration_duration", __city_migration, "emigration_duration")
    imgui.property_input("immigration_amount_per_batch", __city_migration, "immigration_amount_per_batch")
    imgui.property_input("nobles_leave_city_this_year", __city_migration, "nobles_leave_city_this_year")
    imgui.end_table()
    imgui.tree_pop()
}
