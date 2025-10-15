log_info("akhenaten: ui send gift window started")

gift_to_kingdome_window {
	pos [(sw(0) - px(30))/2, (sh(0) - px(15))/2]
    ui {
    	background_image: background({pack:PACK_UNLOADED, id:11}),
        background      : outer_panel({ size[30, 15] })
        title           : header({ pos[0, 15], size[px(30), 20], text:"${52.69}", align:"center" })
        deben_icon      : resource_icon({pos[15, 15], resource:RESOURCE_GOLD})

        last_gift 		: text_center({ pos[0, 45], size[px(30), 20], text:"${52.50} ${city.months_since_gift} ${8.4}", })
        cant_send_gifts	: text_center({ pos[16, 85], size[px(28), 0], text:"${52.70}", font:FONT_NORMAL_WHITE_ON_DARK, multiline:true })

        panel           : inner_panel({pos[16, 70], size[28, 5]
        	ui {
		        lb_modest       : text({ text:"${52.63}", pos[16, 10], font:FONT_NORMAL_WHITE_ON_DARK })
		        link_modest 	: link({ pos[100, 5], size[250, 20], font: FONT_NORMAL_WHITE_ON_DARK, font_hover:FONT_NORMAL_YELLOW})

		    	lb_generous		: label({ text:"${52.64}", pos[16, 30], font: FONT_NORMAL_WHITE_ON_DARK})
		        link_generous 	: link({ pos[100, 25], size[250, 20], font: FONT_NORMAL_WHITE_ON_DARK, font_hover:FONT_NORMAL_YELLOW})

		    	lb_lavish		: label({ text:"${52.65}", pos[16, 50], font: FONT_NORMAL_WHITE_ON_DARK})
		        link_lavish 	: link({ pos[100, 45], size[250, 20], font: FONT_NORMAL_WHITE_ON_DARK, font_hover:FONT_NORMAL_YELLOW})
		    }
	    })

        send_gift 		: button({ margin{left:20, bottom:-40}, size[260, 20] })
        button_close    : button({ margin{right:-180, bottom:-40}, size[160, 20], text:"${13.4}"})
    }
}