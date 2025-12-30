log_info("akhenaten: ui advisor military started")

advisor_military_window {
    ui {
        background   : outer_panel({size[40, 27]})

        title        : text({pos[60, 12], text{group:51, id:0}, font : FONT_LARGE_BLACK_ON_LIGHT })
        advisor_icon : image({pack:PACK_GENERAL, id:128, offset:1, pos[10, 10] })

        h1           : text({text{group:51, id:1}, pos[374, 43], font:FONT_SMALL_PLAIN})
        h2           : text({text{group:51, id:2}, pos[374, 58], font:FONT_SMALL_PLAIN})
        h3           : text({text{group:51, id:3}, pos[454, 43], font:FONT_SMALL_PLAIN})
        h4           : text({text{group:51, id:4}, pos[454, 58], font:FONT_SMALL_PLAIN})
        h5           : text({text{group:51, id:5}, pos[534, 43], font:FONT_SMALL_PLAIN})
        h6           : text({text{group:51, id:6}, pos[534, 58], font:FONT_SMALL_PLAIN})
        h7           : text({text{group:138, id:36}, pos[274, 58], font:FONT_SMALL_PLAIN})
        
        inner_panel  : inner_panel({pos[32, 70], size[36, 17]})
        forts_area   : text({
            margin{left:60, bottom:-100}
            ui {
                imgb1       : image({group:PACK_GENERAL, id:158, pos[0, 10]})
                enemy_text  : text({pos[30, 10], font:FONT_NORMAL_BLACK_ON_LIGHT})

                imgb2       : image({group:PACK_GENERAL, id:158, pos[0, 30]})
                distant_text: text({pos[30, 30], font:FONT_NORMAL_BLACK_ON_LIGHT})

                forts_text  : text({pos[80, 48], font:FONT_NORMAL_BLACK_ON_LIGHT})
            }
        })

        no_legions   : text({text{group:51, id:16}, pos[64, 200], wrap:496, font:FONT_NORMAL_BLACK_ON_DARK, multiline:true})
    }
}

function get_figure_type_str(figure_type) {
    if (figure_type == FIGURE_INFANTRY)  return __loc(138, 34)
    if (figure_type == FIGURE_FCHARIOTEER) return __loc(138, 33)
    if (figure_type == FIGURE_ARCHER) return __loc(138, 35)
    return ""
}

[event=advisor_military_window_draw]
function advisor_military_window_draw_battalions(window) {     
    if (city.num_forts > 0) {
        for (var i = 0; i < city.num_forts; i++) {
            var form = city.get_battalion(i)
            
            ui.button({ text:"", pos[40, 77 + 44 * i], size[px(35), 40], font:FONT_NORMAL_BLACK_ON_DARK, border:false, body:false })

            var battalion_image = get_image(PACK_GENERAL, 127, form.batalion_id)
            ui.image(battalion_image, {x:44, y:82 + 44 * i})
            ui.label(__loc(138, form.batalion_id), vec2i(84, 83 + 44 * i), FONT_NORMAL_WHITE_ON_DARK)
 
            ui.label("" + form.num_figures + " " + get_figure_type_str(form.figure_type), vec2i(84, 100 + 44 * i), FONT_NORMAL_BLACK_ON_DARK);
            // ui.label(ui::str(138, 37 + form->morale / 5), vec2i{224, 91 + 44 * i}, FONT_NORMAL_BLACK_ON_DARK, UiFlags_AlignCentered, 150);
// 
            // image_desc image{ PACK_GENERAL, 222 };
            // ui.button("", vec2i{ 384, 83 + 44 * i }, vec2i{ 30, 30 }, fonts_vec{ FONT_NORMAL_BLACK_ON_DARK });
            // ui.image(image + 0, vec2i{ 387, 86 + 44 * i });
// 
            // ui.button("", vec2i{ 464, 83 + 44 * i }, vec2i{ 30, 30 });
            // ui.image(image + (form->is_at_fort ? 2 : 1), vec2i{ 467, 86 + 44 * i });
// 
            // ui.button("", vec2i{ 544, 83 + 44 * i }, vec2i{ 30, 30 });
            // ui.image(image + (form->empire_service ? 3 : 4), vec2i{ 547, 86 + 44 * i });
        }
    }
}