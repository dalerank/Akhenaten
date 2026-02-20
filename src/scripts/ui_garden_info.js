log_info("akhenaten: ui garden info started")

terrain_info_garden {
    open_sounds       : [ "Wavs/park1.wav" ]
    ui : baseui(terrain_info_window, {
        title   : text({pos: [0, 16], size: [px(29), 13], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        describe: text({pos: [32, 66], wrap: px(26), font : FONT_NORMAL_BLACK_ON_LIGHT, multiline: true})
    })
}

[es=terrain_info_garden_init]
function terrain_info_garden_on_init(window) {
    window.title.text = __loc(building_garden.meta.text_id, 0)
    window.describe.text = __loc(building_garden.meta.text_id, 1)
}
