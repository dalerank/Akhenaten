log_info("akhenaten: ui common started")

ui {
    popup_message: __ui_popup_message
}

ui.image = function(image, pos) {
    if (!image || !pos) {
        return
    }

    if (image.tid !== undefined) {
        __ui_draw_image(image.tid, pos)
    }
}

ui.button = function(config) {
    if (!config) {
        return
    }

    var flags = UiFlags_None
    flags |= (config.border === false ? UiFlags_NoBorder : 0)
    flags |= (config.body === false ? UiFlags_NoBody : 0)

    return __ui_draw_button(config.text, config.pos, config.size, config.font, flags)
}

ui.label = function(text, pos, font) {
    if (!text || !pos) {
        return
    }

    __ui_draw_label(text, pos, font)
}

ui.line = function(hline, pos, size) {
    if (!pos) {
        return
    }

    __ui_draw_line(hline, pos, size)
}

ui.window_city_show = __ui_window_city_show
ui.window_message_dialog_show = __ui_window_message_dialog_show

function ui_create_element_proxy(elementId) {
    return {
        id: elementId

        @text {
            get: function() { return __ui_element_get_enabled(this.id) }
            set: function(v) { __ui_element_set_text(this.id, v) }
        }

        @enabled {
            get: function() { return __ui_element_get_enabled(this.id) }
            set: function(v) { __ui_element_set_enabled(this.id, v) }
        }

        @font {
            get: function() { return __ui_element_get_font(this.id) }
            set: function(v) { __ui_element_set_font(this.id, v) }
        }

        @text_color { 
            get: function() { return __ui_element_get_text_color(this.id) }
            set: function(v) { __ui_element_set_text_color(this.id, v) }
        }

        @image { 
            set: function(v) { __ui_element_set_image(this.id, v) }
        }
    }
}

function px(i) { return i * 16 }
function sw(v) { return game.screen.w + v}
function sh(v) { return game.screen.h + v}
function mbutton(i) { return [sw(0) / 2 - 128, sh(0) / 2 - 100 + 40 * i] }

function baseui(base, ext) {
    var newui = {};

    for (var key in base.ui) { newui[key] = base.ui[key] }
    for (var key in ext) { newui[key] = ext[key]}

    return newui;
}

function extend(base, ext) {
		var newobj = {};

    for (var key in base) { newobj[key] = base[key] }
    for (var key in ext) { newobj[key] = ext[key]}

    return newobj;
}

function inner_panel(config) { return extend({type:"inner_panel"}, config) }
function outer_panel(config) { return extend({type:"outer_panel"}, config) }
function text(config) { return extend({type:"text"}, config) }
function border(config) { return extend({type:"border"}, config) }
function dummy(config) { return extend({type:"text"}, config) }
function text_center(config) { return extend({type:"text", align:"center"}, config) }
function label(config) { return extend({type:"label", font : FONT_NORMAL_WHITE_ON_DARK}, config) }
function header(config) { return extend({type:"label", font : FONT_LARGE_BLACK_ON_LIGHT}, config) }
function multiline(config) { return extend({type:"label", multiline:true, font : FONT_NORMAL_WHITE_ON_DARK}, config) }
function image(config) { return extend({type:"image"}, config) }
function image_button(config) { return extend({type:"image_button"}, config) }
function ok_button(config) { return extend({type:"image_button", size[39, 26], pack:PACK_GENERAL, id:96, offset:0 }, config) }
function cancel_button(config) { return extend({type:"image_button", size[39, 26], pack:PACK_GENERAL, id:96, offset:4 }, config) }
function button(config) { return extend({type:"generic_button", font : FONT_NORMAL_BLACK_ON_LIGHT}, config) }
function link(config) { return extend({type:"generic_button", hbody:false, border:false, font:FONT_NORMAL_BLACK_ON_LIGHT, font_hover:FONT_NORMAL_YELLOW,}, config) }
function arrowup(config) { return extend({type:"arrow_button", down:false}, config) }
function arrowdown(config) { return extend({type:"arrow_button", down:true}, config) }
function background(config) { return extend({type:"background", down:true}, config) }
function resource_icon(config) { return extend({ type : "resource_icon"}, config) }
function large_button(config) { return extend({ type : "large_button"}, config) }
function scrollable_list(config) { return extend({ type : "scrollable_list"}, config) }
function menu_item(config) { return extend({ type : "menu_item"}, config) }
function menu_header(config) { return extend({ type : "menu_header"}, config) }

function help_button(config) { var i = image_button({margin{left:14, bottom:-40}, size[27, 27], pack:PACK_GENERAL, id:134, onclick: window_show_help }); return extend(i, config) }
function close_button(config) { var i = image_button({margin{right:-40, bottom:-40}, size[27, 27], pack:PACK_GENERAL, id:134, offset:4, onclick: window_go_back }); return extend(i, config) }
function next_button(config) { var i = image_button({size[27, 27], pack:PACK_GENERAL, id:90 }); return extend(i, config) }
function advisor_button(config) { var i = image_button({pack:PACK_GENERAL, id:106, offset:12, tooltip[68, 41]}); return extend(i, config) }