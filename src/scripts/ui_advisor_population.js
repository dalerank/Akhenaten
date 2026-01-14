log_info("akhenaten: ui advisor population started")

advisor_population_graph_census = {
	y_axis_offset  : [-56, 0]
	y_axis_label_w : 60 
	y_axis_height  : 200

    x_axis_offset  : [-20, 210]
    x_axis_width   : 170
}

advisor_population_graph_history = {
    y_axis_offset  : [-56, 0]
	y_axis_label_w : 60 
	y_axis_height  : 200

    x_axis_offset  : [-20, 215]
    x_axis_width   : 170
}

advisor_population_society_history {
    y_axis_offset  [-56, 0]
	y_axis_label_w : 60 
	y_axis_height  : 200

    x_axis_offset  [-20, 215]
    x_axis_width   : 170
}

advisor_population_window = {
	graph_bar_1 : { pack:PACK_GENERAL, id:157 }
	graph_bar_2 : { pack:PACK_GENERAL, id:157, offset:1 }
	graph_bar_3 : { pack:PACK_GENERAL, id:157, offset:2 }
	graph_bar_4 : { pack:PACK_GENERAL, id:157, offset:3 }

    ui : {
        background   : outer_panel({size:[40, 27] })
        advisor_icon : image({pack:PACK_GENERAL, id:128, offset:5, pos:[10, 10] })
        title        : label({font : FONT_LARGE_BLACK_ON_LIGHT, pos:[60, 17]})
        bgimage      : image({pack : PACK_UNLOADED, id:21, offset:14, pos:[56, 60]})
        population   : label({font : FONT_NORMAL_BLACK_ON_DARK, text:"${TR_ADVISOR_TOTAL_POPULATION} ${city.population}", pos:[450, 25]})
        housing      : text_center({font : FONT_NORMAL_BLACK_ON_DARK, pos:[545, 315]})

        housing_button : button({pos:[540, 260], size:[64, 50], tooltip:[68, 106]
            ui : {
                tx   : image({pos: [3, 18], pack: PACK_GENERAL, id: 29, isometric:true })
            }
        }),

        top_text     : text({pos:[503, 44], font:FONT_NORMAL_BLACK_ON_DARK})
        next_graph   : button({pos:[503, 61], size:[104, 55]
            ui : {
                next_graph_tx : image({pos:[5, 0]}),
            }
        }),

        bot_text     : text({pos:[503, 144], font:FONT_NORMAL_BLACK_ON_DARK}),
        prev_graph   : button({pos:[503, 161], size:[104, 55], 
            ui : {
                prev_graph_tx : image({pos:[5, 0]}),
            }
        }),

        big_text     : label({font : FONT_NORMAL_BLACK_ON_DARK, pos:[60, 44]}),
        big_graph_tx : label({pos:[65, 62]}),

        inner_panel  : inner_panel({pos:[48, 336], size:[34, 5],
            ui : {
	            img1     : image({pack: PACK_GENERAL, id: 158, pos:[8, 8]}),
	            text1    : text({pos:[35, 8], font:FONT_NORMAL_WHITE_ON_DARK}),
	            img2     : image({pack: PACK_GENERAL, id: 158, pos:[8, 26]}),
	            text2    : text({pos:[35, 26], font:FONT_NORMAL_WHITE_ON_DARK}),
	            img3     : image({pack: PACK_GENERAL, id: 158, pos:[8, 44]}),
	            text3    : text({pos:[35, 44], font:FONT_NORMAL_WHITE_ON_DARK, multiline:true, wrap:px(32)}),
	            img4     : image({pack: PACK_GENERAL, id: 158, pos:[8, 62]}),
	            text4    : text({pos:[35, 62], font:FONT_NORMAL_WHITE_ON_DARK}),
	        }
        }),
    }
}