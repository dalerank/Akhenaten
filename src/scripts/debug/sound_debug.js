log_info("akhenaten: sound_debug")

[es=event_draw_debug_properties]
function sound_debug_draw_properties(ev) {
    if (!imgui.tree_node_ex("Sound")) {
        return
    }

    imgui.begin_table("Sound", 2, imgui.table_flags_debug_props())

    var count = __sound_channel_count()
    for (var i = 0; i < count; i++) {
        var ch = SoundChannel(i)
        if (!ch.playing) {
            continue
        }

        imgui.property_input("Channel" + i, "L:" + ch.left_pan + " R:" + ch.right_pan + " " + ch.filename())
    }

    imgui.end_table()
    imgui.tree_pop()
}
