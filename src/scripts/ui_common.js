log_info("akhenaten: ui common started")

ui {
    popup_message: __ui_popup_message

    sidebar {
        @offset_x { get: __ui_widget_sidebar_city_offset_x }
    }
}

imgui {
    tree_node_ex: __imgui_tree_node_ex
    tree_node_ex2: __imgui_tree_node_ex2
    tree_pop: __imgui_tree_pop
    begin_table: __imgui_begin_table
    end_table: __imgui_end_table
    table_flags_debug_props: __imgui_table_flags_debug_props
    property_input : __debug_props_show
    text: __imgui_text
    same_line: __imgui_same_line
    button: __imgui_button
    set_next_item_width: __imgui_set_next_item_width
    content_region_avail_x: __imgui_content_region_avail_x
    input_text: __imgui_input_text
}

ui.image = function(image, pos, flags) {
    if (!image || !pos) {
        return
    }

    if (image.tid === undefined) {
        return
    }

    if (flags) {
        __ui_draw_image_flags(image.tid, pos, flags)
    } else {
        __ui_draw_image(image.tid, pos)
    }
}

ui.image_scaled = function(image, pos, scale) {
    if (!image || !pos) {
        return
    }
    var tid = (typeof image === "number") ? image : image.tid
    if (tid === undefined || tid === null) {
        return
    }
    __ui_draw_image_scaled(tid, pos, scale)
}

ui.button_none = 0
ui.button_clicked = 1
ui.button_hovered = 2

ui.begin_widget = __ui_begin_widget
ui.end_widget = __ui_end_widget
ui.set_clip_rectangle = __ui_set_clip_rectangle
ui.reset_clip_rectangle = __ui_reset_clip_rectangle
ui.fill_rect = __ui_fill_rect
ui.border = __ui_border
ui.button_border = __ui_button_border
ui.panel = __ui_panel
ui.label_colored = __ui_label_colored
ui.set_tooltip = __ui_set_tooltip
ui.text_abs_colored = __ui_text_abs_colored
ui.draw_texture = __ui_draw_texture
ui.window_is = __ui_window_is
ui.resource_icon_flags = __ui_draw_resource_icon_flags
ui.set_window_pos = __ui_set_window_pos
ui.invalidate_minimap_preview = function(size) {
	if (size)
		__ui_invalidate_minimap_preview_size(size)
	else
		__ui_invalidate_minimap_preview()
}
ui.draw_minimap_preview = function(pos, size, generate_size) {
	if (generate_size)
		__ui_draw_minimap_preview_sized(pos, size, generate_size)
	else
		__ui_draw_minimap_preview(pos, size)
}

function show_window_by_id(window_id) {
	return function() {
		emit event_show_window{ id:window_id }
	}
}

ui.arw_button = function(pos, down, tiny, allow_repeat) {
    return __ui_draw_arw_button(pos, down, tiny, allow_repeat)
}

ui.button = __ui_draw_button

ui.label = function(text, pos, font) {
    if (!text || !pos) {
        return
    }

    __ui_draw_label(text, pos, font)
}

ui.label_ex = function(text, pos, font, flags, box_width) {
    if (!text || !pos) {
        return
    }

    __ui_draw_label_ex(text, pos, font, flags, box_width || 0)
}

ui.label_year = function(year, pos, font) {
    if (pos == null) {
        return
    }

    __ui_label_year(year, pos, font)
}

ui.resource_icon = function(pos, resource) {
    if (!pos) {
        return
    }

    __ui_draw_resource_icon(pos, resource)
}

ui.line = function(hline, pos, size) {
    if (!pos) {
        return
    }

    __ui_draw_line(hline, pos, size)
}

ui.window_city_show = __ui_window_city_show
ui.window_editor_map_show = __ui_window_editor_map_show
ui.window_message_dialog_show = __ui_window_message_dialog_show
ui.window_message_dialog = __ui_window_message_dialog
ui.sidebar_set_type = __ui_widget_sidebar_set_type
ui.scenario_mission_briefing_button_enabled = __ui_scenario_mission_briefing_button_enabled
ui.sidebar_overlay_link_text = __ui_sidebar_overlay_link_text
ui.show_yesno = __ui_dialog_show_yesno
ui.show_ok = __ui_dialog_show_ok

function px(i) { return i * 16 }
function sw(v) { return screen.width + v}
function sh(v) { return screen.height + v}
function mbutton(i) { return [sw(0) / 2 - 128, sh(0) / 2 - 100 + 40 * i] }

function baseui(base, ext) {
    var newui = {};

    for (var key in base.ui) { newui[key] = base.ui[key] }
    for (var key in ext) { newui[key] = ext[key]}

    return newui;
}

function ui_extend(base, ext) {
    var newobj = {};

    for (var key in base) {
        var bdesc = Object.getOwnPropertyDescriptor(base, key);
        if (bdesc && (bdesc.get || bdesc.set)) {
            Object.defineProperty(newobj, key, bdesc);
        } else {
            newobj[key] = base[key];
        }
    }

    if (ext == null) return newobj;

    var keys = Object.keys(ext);
    for (var i = 0; i < keys.length; i++) {
        var k = keys[i];
        var desc = Object.getOwnPropertyDescriptor(ext, k);
        if (desc && (desc.get || desc.set)) {
            Object.defineProperty(newobj, k, desc);
        } else {
            newobj[k] = desc ? desc.value : ext[k];
        }
    }

    return newobj;
}

function inner_panel(config) { return ui_extend({type:"inner_panel"}, config) }
function outer_panel(config) { return ui_extend({type:"outer_panel"}, config) }
function text(config) { return ui_extend({type:"text"}, config) }
function border(config) { return ui_extend({type:"border"}, config) }
function dummy(config) { return ui_extend({type:"text"}, config) }
function text_center(config) { return ui_extend({type:"text", align:"center"}, config) }
function label(config) { return ui_extend({type:"label", font : FONT_NORMAL_WHITE_ON_DARK}, config) }
function header(config) { return ui_extend({type:"label", font : FONT_LARGE_BLACK_ON_LIGHT}, config) }
function multiline(config) { return ui_extend({type:"label", multiline:true, font : FONT_NORMAL_WHITE_ON_DARK}, config) }
function image(config) { return ui_extend({type:"image"}, config) }
function image_queue(config) { return ui_extend({type:"image_queue"}, config) }
function image_button(config) { return ui_extend({type:"image_button"}, config) }
function ok_button(config) { return ui_extend({type:"image_button", size[39, 26], pack:PACK_GENERAL, id:96, offset:0 }, config) }
function cancel_button(config) { return ui_extend({type:"image_button", size[39, 26], pack:PACK_GENERAL, id:96, offset:4 }, config) }
function button(config) { return ui_extend({type:"generic_button", font : FONT_NORMAL_BLACK_ON_LIGHT}, config) }
function checkbox(config) { return ui_extend({type:"checkbox", size:[23, 23], font : FONT_NORMAL_BLACK_ON_LIGHT}, config) }
function link(config) { return ui_extend({type:"generic_button", hbody:false, border:false, font:FONT_NORMAL_BLACK_ON_LIGHT, font_hover:FONT_NORMAL_YELLOW,}, config) }
function arrowup(config) { return ui_extend({type:"arrow_button", down:false}, config) }
function arrowdown(config) { return ui_extend({type:"arrow_button", down:true}, config) }
function background(config) { return ui_extend({type:"background", down:true}, config) }
function resource_icon(config) { return ui_extend({ type : "resource_icon"}, config) }
function large_button(config) { return ui_extend({ type : "large_button"}, config) }
function scrollable_list(config) { return ui_extend({ type : "scrollable_list"}, config) }
function scrollbar(config) { return ui_extend({ type : "scrollbar"}, config) }
function input(config) { return ui_extend({ type : "input", font : FONT_NORMAL_WHITE_ON_DARK }, config) }
function menu_item(config) { return ui_extend({ type : "menu_item"}, config) }
function menu_header(config) { return ui_extend({ type : "menu_header"}, config) }

function help_button(config) { var i = image_button({margin{left:14, bottom:-40}, size[27, 27], pack:PACK_GENERAL, id:134, onclick_event: "help" }); return ui_extend(i, config) }
function close_button(config) { var i = image_button({margin{right:-40, bottom:-40}, size[27, 27], pack:PACK_GENERAL, id:134, offset:4, onclick_event: "go_back" }); return ui_extend(i, config) }
function next_button(config) { var i = image_button({size[27, 27], pack:PACK_GENERAL, id:90 }); return ui_extend(i, config) }
function advisor_button(config) { var i = image_button({pack:PACK_GENERAL, id:106, offset:12, tooltip[68, 41]}); return ui_extend(i, config) }


// H6b: default help/close ES for helper buttons (override per window when needed).
[es=(advisor_chief_window, help), es=(advisor_education_window, help), es=(advisor_entertainment_window, help), es=(advisor_financial_window, help), es=(advisor_health_window, help), es=(advisor_housing_window, help), es=(advisor_imperial_window, help), es=(advisor_labors_window, help), es=(advisor_military_window, help), es=(advisor_monuments_window, help), es=(advisor_population_window, help), es=(advisor_ratings_window, help), es=(advisor_religion_window, help), es=(advisor_trade_window, help), es=(artisans_guild_info_window, help), es=(batalion_info_window, help), es=(bazaar_info_window, help), es=(bazaar_orders_window, help), es=(bricklayers_guild_info_window, help), es=(brickworks_info_window, help), es=(building_info_window, help), es=(carpenters_guild_info_window, help), es=(dock_orders_window, help), es=(festival_square_info_window, help), es=(figure_enemy_info_window, help), es=(figure_info_window, help), es=(figure_market_buyer_window, help), es=(figure_trader_info_window, help), es=(figure_transport_ship_info_window, help), es=(figure_warship_info_window, help), es=(granary_orders_window, help), es=(health_info_window, help), es=(industry_office_info_window, help), es=(info_window_abu_simbel, help), es=(info_window_alexandria_library, help), es=(info_window_architect_post, help), es=(info_window_bandstand, help), es=(info_window_booth, help), es=(info_window_bullfight, help), es=(info_window_burning_ruin, help), es=(info_window_caesareum, help), es=(info_window_courthouse, help), es=(info_window_dock, help), es=(info_window_education, help), es=(info_window_entertainment, help), es=(info_window_farm, help), es=(info_window_ferry, help), es=(info_window_fishing_wharf, help), es=(info_window_food_mill, help), es=(info_window_fort, help), es=(info_window_gatehouse, help), es=(info_window_granary, help), es=(info_window_house, help), es=(info_window_hunting_lodge, help), es=(info_window_lamp_workshop, help), es=(info_window_mansion, help), es=(info_window_mausoleum, help), es=(info_window_milacademy, help), es=(info_window_mission_post, help), es=(info_window_mortuary, help), es=(info_window_native_crops, help), es=(info_window_native_hut, help), es=(info_window_native_meeting, help), es=(info_window_obelisk, help), es=(info_window_oracle, help), es=(info_window_palace, help), es=(info_window_pavilion, help), es=(info_window_pharos_lighthouse, help), es=(info_window_police_station, help), es=(info_window_pyramid, help), es=(info_window_recruiter, help), es=(info_window_roadblock, help), es=(info_window_senet_house, help), es=(info_window_shrine, help), es=(info_window_sphinx, help), es=(info_window_statue, help), es=(info_window_storageyard, help), es=(info_window_sun_temple, help), es=(info_window_temple, help), es=(info_window_temple_complex, help), es=(info_window_tower, help), es=(info_window_triumphal_arch, help), es=(info_window_vacant_lot, help), es=(info_window_water_lift, help), es=(info_window_water_supply, help), es=(info_window_work_camp, help), es=(info_window_zoo, help), es=(infrastructure_common_info_window, help), es=(message_dialog_window_disaster, help), es=(message_dialog_window_emigration, help), es=(message_dialog_window_general, help), es=(message_dialog_window_god, help), es=(message_dialog_window_image, help), es=(message_dialog_window_imperial, help), es=(message_dialog_window_invasion, help), es=(message_dialog_window_price_change, help), es=(message_dialog_window_trade_change, help), es=(message_dialog_window_troop_request, help), es=(message_dialog_window_tutorial, help), es=(mortuary_info_window, help), es=(raw_material_info_window, help), es=(roadblock_orders_window, help), es=(scribal_school_info_window, help), es=(shipyard_info_window, help), es=(stonemason_guild_info_window, help), es=(storage_yard_orders_window, help), es=(taxcollector_info_window, help), es=(terrain_info_window, help), es=(warshipwharf_info_window, help), es=(well_info_window, help), es=(workshop_info_window, help)]
function ui_help_button_on_help(window) {
    window_show_help()
}

[es=(artisans_guild_info_window, go_back), es=(batalion_info_window, go_back), es=(bazaar_info_window, go_back), es=(bazaar_orders_window, go_back), es=(bricklayers_guild_info_window, go_back), es=(brickworks_info_window, go_back), es=(building_info_window, go_back), es=(carpenters_guild_info_window, go_back), es=(dock_orders_window, go_back), es=(festival_square_info_window, go_back), es=(figure_enemy_info_window, go_back), es=(figure_info_window, go_back), es=(figure_market_buyer_window, go_back), es=(figure_trader_info_window, go_back), es=(figure_transport_ship_info_window, go_back), es=(figure_warship_info_window, go_back), es=(granary_orders_window, go_back), es=(health_info_window, go_back), es=(industry_office_info_window, go_back), es=(info_window_abu_simbel, go_back), es=(info_window_alexandria_library, go_back), es=(info_window_architect_post, go_back), es=(info_window_bandstand, go_back), es=(info_window_booth, go_back), es=(info_window_bullfight, go_back), es=(info_window_burning_ruin, go_back), es=(info_window_caesareum, go_back), es=(info_window_courthouse, go_back), es=(info_window_dock, go_back), es=(info_window_education, go_back), es=(info_window_entertainment, go_back), es=(info_window_farm, go_back), es=(info_window_ferry, go_back), es=(info_window_fishing_wharf, go_back), es=(info_window_food_mill, go_back), es=(info_window_fort, go_back), es=(info_window_gatehouse, go_back), es=(info_window_granary, go_back), es=(info_window_house, go_back), es=(info_window_hunting_lodge, go_back), es=(info_window_lamp_workshop, go_back), es=(info_window_mansion, go_back), es=(info_window_mausoleum, go_back), es=(info_window_milacademy, go_back), es=(info_window_mission_post, go_back), es=(info_window_mortuary, go_back), es=(info_window_native_crops, go_back), es=(info_window_native_hut, go_back), es=(info_window_native_meeting, go_back), es=(info_window_obelisk, go_back), es=(info_window_oracle, go_back), es=(info_window_palace, go_back), es=(info_window_pavilion, go_back), es=(info_window_pharos_lighthouse, go_back), es=(info_window_police_station, go_back), es=(info_window_pyramid, go_back), es=(info_window_recruiter, go_back), es=(info_window_roadblock, go_back), es=(info_window_senet_house, go_back), es=(info_window_shrine, go_back), es=(info_window_sphinx, go_back), es=(info_window_statue, go_back), es=(info_window_storageyard, go_back), es=(info_window_sun_temple, go_back), es=(info_window_temple, go_back), es=(info_window_temple_complex, go_back), es=(info_window_tower, go_back), es=(info_window_triumphal_arch, go_back), es=(info_window_vacant_lot, go_back), es=(info_window_water_lift, go_back), es=(info_window_water_supply, go_back), es=(info_window_work_camp, go_back), es=(info_window_zoo, go_back), es=(infrastructure_common_info_window, go_back), es=(message_dialog_window_disaster, go_back), es=(message_dialog_window_emigration, go_back), es=(message_dialog_window_general, go_back), es=(message_dialog_window_god, go_back), es=(message_dialog_window_image, go_back), es=(message_dialog_window_imperial, go_back), es=(message_dialog_window_invasion, go_back), es=(message_dialog_window_price_change, go_back), es=(message_dialog_window_trade_change, go_back), es=(message_dialog_window_troop_request, go_back), es=(message_dialog_window_tutorial, go_back), es=(message_list_window, go_back), es=(mortuary_info_window, go_back), es=(raw_material_info_window, go_back), es=(roadblock_orders_window, go_back), es=(scribal_school_info_window, go_back), es=(shipyard_info_window, go_back), es=(stonemason_guild_info_window, go_back), es=(storage_yard_orders_window, go_back), es=(taxcollector_info_window, go_back), es=(terrain_info_window, go_back), es=(trade_resource_settings_window, go_back), es=(warshipwharf_info_window, go_back), es=(well_info_window, go_back), es=(workshop_info_window, go_back)]
function ui_close_button_on_go_back(window) {
    window_go_back()
}
