log_info("akhenaten: ui house window started")

info_window_house {
    help_id : "message_housing_and_desirability"
    ui {
        background : outer_panel({size [29, 23] }) // pos/size setup from code
        title      : text({pos[0, 16], text:"${house.level_name}", size[px(28), px(1)], font : FONT_LARGE_BLACK_ON_LIGHT, align:"center"})
        evolve_reason : text({pos[32, 40], size[px(27), -1], font : FONT_NORMAL_BLACK_ON_LIGHT, rich:true, wrap:px(27), scroll:false })
        food0_icon : resource_icon({pos[32, 95] })
        food0_text : text({pos[64, 100], font: FONT_NORMAL_BLACK_ON_LIGHT })
        food1_icon : resource_icon({pos[142, 95] })
        food1_text : text({pos[174, 100], font: FONT_NORMAL_BLACK_ON_LIGHT })
        food2_icon : resource_icon({pos[252, 95] })
        food2_text : text({pos[284, 100], font: FONT_NORMAL_BLACK_ON_LIGHT })
        food3_icon : resource_icon({pos[362, 95] })
        food3_text : text({pos[394, 100], font: FONT_NORMAL_BLACK_ON_LIGHT })
        good0_icon : resource_icon({pos[32, 120] })
        good0_text : text({pos[64, 124], font: FONT_NORMAL_BLACK_ON_LIGHT })
        good1_icon : resource_icon({pos[142, 120] })
        good1_text : text({pos[174, 124], font: FONT_NORMAL_BLACK_ON_LIGHT })
        good2_icon : resource_icon({pos[252, 120] })
        good2_text : text({pos[284, 124], font: FONT_NORMAL_BLACK_ON_LIGHT })
        good3_icon : resource_icon({pos[362, 120] })
        good3_text : text({pos[394, 124], font: FONT_NORMAL_BLACK_ON_LIGHT })

        tenants_panel: inner_panel({pos [16, 148], size[27, 10] })
        people_icon  : image({pos[34, 154], pack:PACK_GENERAL, id:134, offset:13, })
        people_text  : text({pos[64, 164], font: FONT_NORMAL_BLACK_ON_DARK, })
        tax_info     : text({pos[36, 194], font: FONT_NORMAL_BLACK_ON_DARK, })
        happiness_info  : text({pos[36, 214], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(27) })
        additional_info : text({pos[36, 234], font: FONT_NORMAL_BLACK_ON_DARK, multiline:true, wrap:px(27) })

        button_close : close_button({})
        button_help  : help_button({})
    }
}