#include "widget_top_menu_game.h"

#include "game/game.h"

#include "graphics/elements/menu.h"
#include "graphics/elements/ui.h"
#include "graphics/screenshot.h"
#include "graphics/window.h"
#include "graphics/graphics.h"
#include "city/constants.h"
#include "city/finance.h"
#include "city/population.h"
#include "core/profiler.h"
#include "core/core_utility.h"
#include "config/config.h"
#include "game/settings.h"
#include "game/cheats.h"
#include "game/orientation.h"
#include "game/state.h"
#include "game/undo.h"
#include "window/file_dialog.h"
#include "window/message_dialog.h"
#include "io/gamestate/boilerplate.h"
#include "building/construction/build_planner.h"
#include "scenario/scenario.h"
#include "game/system.h"
#include "graphics/screen.h"
#include "widget/widget_city.h"
#include "window/display_options.h"
#include "window/advisors.h"
#include "window/window_city.h"
#include "window/difficulty_options.h"
#include "window/config.h"
#include "window/game_menu.h"
#include "window/hotkey_config.h"
#include "window/main_menu.h"
#include "window/popup_dialog.h"
#include "window/autoconfig_window.h"
#include "window/speed_options.h"
#include "window/sound_options.h"
#include "widget/widget_sidebar.h"
#include "dev/debug.h"

#include "js/js_game.h"

static void button_rotate_left(int param1, int param2);
static void button_rotate_reset(int param1, int param2);
static void button_rotate_right(int param1, int param2);

struct top_menu_widget : autoconfig_window_t<top_menu_widget> {
    int offset_rotate;
    int offset_rotate_basic;

    xstring open_sub_menu;
    xstring focus_menu_id;
    xstring focus_sub_menu_id;

    vec2i offset;
    int item_height;
    int spacing;
    int sidebar_offset;
    image_desc background;

    ui::widget headers;

    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int draw_background(UiFlags flags) override { return 0; }
    virtual void draw_foreground(UiFlags flags) override;
    virtual void ui_draw_foreground(UiFlags flags) override {}
    virtual int get_tooltip_text() override { return 0; }
    virtual int ui_handle_mouse(const mouse *m) override;
    virtual void init() override;

    virtual void load(archive arch, pcstr section) override {
        autoconfig_window::load(arch, section);

        offset = arch.r_vec2i("offset");
        item_height = arch.r_int("item_height");
        arch.r_desc("background", background);
        spacing = arch.r_int("spacing");
        offset_rotate_basic = arch.r_int("offset_rotate_basic");
        sidebar_offset = arch.r_int("sidebar_offset");

        headers.load(arch, "headers");
        for (auto &header : headers.elements) {
            auto impl = header->dcast_menu_header();
            if (impl) {
                impl->load_items(arch, header->id.c_str());
            }
        }
    }

    void menu_item_update(pcstr header, int item, pcstr text);
    void update_month_year_max_width(uint8_t month, int year);
};

top_menu_widget g_top_menu;

int orientation_button_state = 0;
int orientation_button_pressed = 0;

static generic_button orientation_buttons_ph[] = {
    {12, 0, 36 - 24, 21, button_rotate_reset, button_none, 0, 0},
    {0, 0, 12, 21, button_rotate_left, button_none, 0, 0},
    {36 - 12, 0, 12, 21, button_rotate_right, button_none, 0, 0},
};

void top_menu_widget::init() {
    ui["date"].onrclick([] {
        window_message_dialog_show(MESSAGE_DIALOG_TOP_DATE, -1, window_city_draw_all);
    });

    ui["population"].onrclick([] {
        window_message_dialog_show(MESSAGE_DIALOG_TOP_POPULATION, -1, window_city_draw_all);
    });

    ui["funds"].onrclick([] {
        window_message_dialog_show(MESSAGE_DIALOG_TOP_FUNDS, -1, window_city_draw_all);
    });
}

void top_menu_widget::menu_item_update(pcstr header, int item, pcstr text) {
    auto menu = headers[header].dcast_menu_header();
    if (!menu) {
        return;
    }

    menu->item(item).text = text;
}

void top_menu_widget::update_month_year_max_width(uint8_t month, int year) {
    pcstr month_str = ui::str(25, month);
    bstring32 text;
    if (year >= 0) {
        int use_year_ad = locale_year_before_ad();
        if (use_year_ad) { text.printf("%s %d %s", month_str, year, ui::str(20, 1)); }
        else { text.printf("%s %s %d", month_str, year, ui::str(20, 1)); }
    } else {
        text.printf("%s %d %s", month_str, -year, ui::str(20, 0));
    }

    ui["date"] = text;
}

static void menu_debug_render_text(int opt, bool v) {
    auto& data = g_top_menu;
    struct option { pcstr on, off; };
    static option debug_text_rend[] = {
        {"Buildings ON", "Buildings OFF"},
        {"Tile Size ON", "Tile Size OFF"},
        {"Roads ON", "Roads OFF"},
        {"Routing Dist ON", "Routing Dist OFF"},
        {"Routing Grid ON", "Routing Grid OFF"},
        {"Moisture ON", "Moisture OFF"},
        {"Grass Level ON", "Grass Level OFF"},
        {"Soil Depl ON", "Soil Depl OFF"},
        {"Flood Order ON", "Flood Order OFF"},
        {"Flood Flags ON", "Flood Flags OFF"},
        {"Labor ON", "Labor OFF"},
        {"Sprite Frames ON", "Sprite Frames OFF"},
        {"Terrain Bits ON", "Terrain Bits OFF"},
        {"Image ON", "Image OFF"},
        {"Image Alt ON", "Image Alt OFF"},
        {"Marshland ON", "Marshland OFF"},
        {"Terrain ON", "Terrain OFF"},
        {"Tile Coord ON", "Tile Coord OFF"},
        {"Flood Shore ON", "Flood Shore OFF"},
        {"Tile TopH ON", "Tile TopH OFF"},
        {"Monuments ON", "Monuments OFF"},
        {"Figures ON", "Figures OFF"},
        {"Height ON", "Height OFF"},
        {"Marshland Depl ON", "Marshland Depl OFF"},
        {"Dmg Fire ON", "Dmg Fire OFF"},
        {"Desirability ON", "Desirability OFF"},
        {"River Shore ON", "River Shore OFF"},
    };
    const auto &current = debug_text_rend[opt];
    g_top_menu.menu_item_update("debug_render", opt, v ? current.on : current.off);
}

static void menu_debug_opt_text(int opt, bool v) {
    struct option { pcstr on, off; };
    static option debug_text_opt[] = {
        {"Pages ON", "Pages OFF"},
        {"Game Time ON", "Game Time OFF"},
        {"Build Planner ON", "Build Planner OFF"},
        {"Religion ON", "Religion OFF"},
        {"Tutorial ON", "Tutorial OFF"},
        {"Floods ON", "Floods OFF"},
        {"Camera ON", "Camera OFF"},
        {"Tile Cache ON", "Tile Cache OFF"},
        {"Migration ON", "Migration OFF"},
        {"Sentiment ON", "Sentiment OFF"},
        {"Sound Channels ON", "Sound Channels OFF"},
        {"Properties ON", "Properties OFF"},
        {"Show console", "Show console"},
        {"Screenshot", "Screenshot"},
        {"Full Screenshot", "Full Screenshot"},
        {"Write Video ON", "Write Video OFF"},
        {"Clouds ON", "Clouds OFF"},
    };
    const auto &current = debug_text_opt[opt];
    g_top_menu.menu_item_update("debug", opt, v ? current.on : current.off);
}

static void menu_debug_screenshot(int opt) {
    widget_top_menu_clear_state();
    window_go_back();
    graphics_save_screenshot(SCREENSHOT_DISPLAY);
}

static void menu_debug_full_screenshot(int opt) {
    widget_top_menu_clear_state();
    window_go_back();
    graphics_save_screenshot(SCREENSHOT_FULL_CITY);
}

static void menu_debug_change_opt(menu_item &item) {
    int opt = item.parameter;
    switch (opt) {
    case e_debug_show_console: game_cheat_console(true); break;
    case e_debug_make_screenshot: menu_debug_screenshot(0); break;
    case e_debug_make_full_screenshot: menu_debug_full_screenshot(0); break;
    case e_debug_show_properties: 
        game.debug_properties = !game.debug_properties;
        g_debug_show_opts[opt] = game.debug_properties;
        widget_top_menu_clear_state();
        window_go_back();
        menu_debug_opt_text(e_debug_show_properties, game.debug_properties );
        break;

    case e_debug_write_video: 
        game.set_write_video(!game.get_write_video());
        menu_debug_opt_text(e_debug_write_video, game.get_write_video());
        g_debug_show_opts[opt] = game.get_write_video();
        break;

    default:
        g_debug_show_opts[opt] = !g_debug_show_opts[opt];
        menu_debug_opt_text(opt, g_debug_show_opts[opt]);
    }
}

static void menu_debug_render_change_opt(menu_item &item) {
    int opt = item.parameter;
    g_debug_render = (opt == g_debug_render) ? 0 : opt;
    auto& data = g_top_menu;
    auto *render = data.headers["debug_render"].dcast_menu_header();
    for (int i = 0; i < render->impl.items.size(); ++i) {
        menu_debug_render_text(i, g_debug_render == render->impl.items[i].parameter);
    }
}

static void button_rotate_reset(int param1, int param2) {
    game_orientation_rotate_north();
}

static void button_rotate_left(int param1, int param2) {
    game_orientation_rotate_left();
}

static void button_rotate_right(int param1, int param2) {
    game_orientation_rotate_right();
}

void widget_top_menu_draw_elements() {
    auto& data = g_top_menu;
    auto &headers = data.headers;
    vec2i offset = data.offset;
    e_font hightlight_font = config_get(CONFIG_UI_HIGHLIGHT_TOP_MENU_HOVER) ? FONT_NORMAL_YELLOW : FONT_NORMAL_BLACK_ON_LIGHT;
    for (auto &it : headers.elements) {
        ui::emenu_header *header = it->dcast_menu_header();

        if (!header) {
            continue;
        }

        const bool is_hovered = (it->id == data.focus_menu_id);

        header->impl.x_start = offset.x;
        header->font(is_hovered ? hightlight_font : FONT_NORMAL_BLACK_ON_LIGHT);
        header->pos = vec2i{offset.x, data.offset.y};
        header->draw(UiFlags_None);

        if (is_hovered) {
            ui::set_tooltip(header->tooltip());
        }

        offset.x += header->text_width();
        header->impl.x_end = offset.x;
        offset.x += data.spacing;
    }
}

static xstring top_menu_bar_get_selected_header(const mouse* m) {
    auto& data = g_top_menu;
    auto &headers = g_top_menu.headers;
    for (auto &it : headers.elements) {
        ui::emenu_header *header = it->dcast_menu_header();

        if (!header) {
            continue;
        }

        if (header->impl.x_start <= m->x && header->impl.x_end > m->x && data.offset.y <= m->y && data.offset.y + 12 > m->y) {
            return header->id;
        }
    }
    return {};
}

static xstring top_menu_bar_handle_mouse(const mouse* m) {
    g_top_menu.focus_menu_id = top_menu_bar_get_selected_header(m);
    return top_menu_bar_get_selected_header(m);
}

static void top_menu_calculate_menu_dimensions(menu_header& menu) {
    auto& data = g_top_menu;
    int max_width = 0;
    int height_pixels = data.item_height;
    for (const auto &item: menu.items) {
        if (item.hidden) {
            continue;
        }

        int width_pixels = lang_text_get_width(item.text.c_str(), FONT_NORMAL_BLACK_ON_LIGHT);
        max_width = std::max(max_width, width_pixels);

        height_pixels += data.item_height;
    }
    int blocks = (max_width + 8) / 16 + 1; // 1 block padding
    menu.calculated_width_blocks = blocks < 10 ? 10 : blocks;
    menu.calculated_height_blocks = height_pixels / 16;
}

void top_menu_menu_draw(const xstring header, const xstring focus_item_id) {
    auto& menu = g_top_menu;
    auto &impl = ((ui::emenu_header *)&menu.headers[header])->impl;

    if (impl.calculated_width_blocks == 0 || impl.calculated_height_blocks == 0) {
        top_menu_calculate_menu_dimensions(impl);
    }

    unbordered_panel_draw(impl.x_start, TOP_MENU_HEIGHT, impl.calculated_width_blocks, impl.calculated_height_blocks);
    int y_offset = TOP_MENU_HEIGHT + menu.offset.y * 2;
    for (const auto &item: impl.items) {
        if (item.hidden) {
            continue;
        }
        // Set color/font on the menu item mouse hover
        lang_text_draw(item.text.c_str(), vec2i{impl.x_start + 8, y_offset}, item.id == focus_item_id ? FONT_NORMAL_YELLOW : FONT_NORMAL_BLACK_ON_LIGHT);
        y_offset += menu.item_height;
    }
}

static xstring top_menu_get_subitem(const mouse* m, menu_header &menu) {
    auto& data = g_top_menu;
    int y_offset = TOP_MENU_HEIGHT + data.offset.y * 2;

    for (const auto &item: menu.items) {
        if (item.hidden) {
            continue;
        }

        if (menu.x_start <= m->x && menu.x_start + 16 * menu.calculated_width_blocks > m->x && y_offset - 2 <= m->y && y_offset + 19 > m->y) {
            return item.id;
        }

        y_offset += data.item_height;
    }

    return {};
}

xstring top_menu_menu_handle_mouse(const mouse* m, menu_header* menu, xstring& focus_item_id) {
    if (!menu) {
        return "";
    }

    xstring item_id = top_menu_get_subitem(m, *menu);
    focus_item_id = item_id;

    if (!item_id) {
        return "";
    }

    if (m->left.went_up) {
        auto it = std::find_if(menu->items.begin(), menu->items.end(), [&item_id] (auto &it) { return it.id == item_id; });
        if (it != menu->items.end()) {
            if (it->left_click_handler) {
                it->left_click_handler(it->parameter);
            } else if (menu->_onclick) {
                menu->_onclick(*it);
            }
        }
    }

    return item_id;
}

void top_menu_header_update_text(pcstr header, pcstr text) {
    auto& menu = g_top_menu;
    auto &impl = ((ui::emenu_header *)&menu.headers[header])->impl;

    menu.headers[header].text(text);
    if (impl.calculated_width_blocks == 0) {
        return;
    }

    int item_width = lang_text_get_width(impl.text, FONT_NORMAL_BLACK_ON_LIGHT);
    int blocks = (item_width + 8) / 16 + 1;
    if (blocks > impl.calculated_width_blocks) {
        impl.calculated_width_blocks = blocks;
    }
}

std::pair<bstring64, bstring64> split_string(pcstr input) {
    std::pair<bstring64, bstring64> result;
    pcstr pos = strstr(input, "/");
    if (pos) {
        result.first.ncat(input, (pos - input));
        result.second.cat(pos + 1);
    }

    return result;
}

void top_menu_item_update_text(pcstr path, pcstr text) {
    auto &menu = g_top_menu;

    auto pair = split_string(path);
    auto header = menu.headers[pair.first].dcast_menu_header();
    auto &item = header->item(pair.second);
    item.text = text;
}

void widget_top_menu_clear_state() {
    auto& data = g_top_menu;

    data.open_sub_menu = "";
    data.focus_menu_id = "";
    data.focus_sub_menu_id = "";
}

static void set_text_for_autosave() {
    top_menu_item_update_text("options/autosave_options", ui::str(19, g_settings.monthly_autosave ? 51 : 52));
}

static void set_text_for_tooltips() {
    top_menu_item_update_text("help/mouse", ui::str(3, g_settings.tooltips + 2));
}

static void set_text_for_warnings(void) {
    top_menu_item_update_text("help/warnings", ui::str(3, g_settings.warnings ? 6 : 5));
}

static void set_text_for_debug_city() {
    auto& data = g_top_menu;
    auto *debug = data.headers["debug"].dcast_menu_header();
    for (int i = 0; i < debug->impl.items.size(); ++i) {
        menu_debug_opt_text(i, g_debug_show_opts[i]);
    }
}

static void set_text_for_debug_render() {
    auto& data = g_top_menu;
    auto *render = data.headers["debug_render"].dcast_menu_header();
    for (int i = 0; i < render->impl.items.size(); ++i) {
        menu_debug_render_text(i, g_debug_render == render->impl.items[i].parameter);
    }
}

static void menu_file_delete_game(int param) {
    widget_top_menu_clear_state();
    window_city_show();
    window_file_dialog_show(FILE_TYPE_SAVED_GAME, FILE_DIALOG_DELETE);
}

static void menu_file_exit_city(int param) {
    widget_top_menu_clear_state();
    window_yesno_dialog_show("#popup_dialog_quit", [] (bool accepted) {
        if (accepted) {
            widget_top_menu_clear_state();
            window_main_menu_show(true);
        } else {
            window_city_show();
        }
    });
}

static void menu_file_load_game(int param) {
    widget_top_menu_clear_state();
    Planner.reset();
    window_city_show();
    window_file_dialog_show(FILE_TYPE_SAVED_GAME, FILE_DIALOG_LOAD);
}

static void menu_file_save_game(int param) {
    widget_top_menu_clear_state();
    window_city_show();
    window_file_dialog_show(FILE_TYPE_SAVED_GAME, FILE_DIALOG_SAVE);
}

static void menu_file_new_game(int param) {
    widget_top_menu_clear_state();
    window_yesno_dialog_show("#popup_dialog_quit", [] (bool confirmed) {
        if (!confirmed) {
            window_city_show();
            return;
        }

        Planner.reset();
        game_undo_disable();
        game_state_reset_overlay();
        window_game_menu_show();
    });
}

static void menu_file_replay_map(int param) {
    widget_top_menu_clear_state();
    window_popup_dialog_show_confirmation("#replay_mission", [] (bool confirmed) {
        if (!confirmed) {
            window_city_show();
            return;
        }

        Planner.reset();
        if (scenario_is_custom()) {
            GamestateIO::load_savegame("autosave_replay.sav");
            window_city_show();
        } else {
            int scenario_id = scenario_campaign_scenario_id();
            widget_top_menu_clear_state();
            GamestateIO::load_mission(scenario_id, true);
        }
    });
}

static void top_menu_file_handle(menu_item &item) {
    if (item.id == "new_game") { menu_file_new_game(0); }
    else if (item.id == "replay_map") { menu_file_replay_map(0); }
    else if (item.id == "load_game") { menu_file_load_game(0); }
    else if (item.id == "save_game") { menu_file_save_game(0); }
    else if (item.id == "delete_game") { menu_file_delete_game(0); }
    else if (item.id == "exit_game") { menu_file_exit_city(0); }
}

static void menu_options_sound(int param) {
    widget_top_menu_clear_state();
    window_sound_options_show(window_city_show);
}

static void menu_options_speed(int param) {
    widget_top_menu_clear_state();
    window_speed_options_show(window_city_show);
}

static void menu_options_difficulty(int param) {
    widget_top_menu_clear_state();
    window_difficulty_options_show(window_city_show);
}

static void menu_options_autosave(int param) {
    g_settings.toggle_monthly_autosave();
    set_text_for_autosave();
}

static void menu_options_change_enh(int param) {
    window_config_show([] {});
}

static void menu_options_hotkeys(int param) {
    window_hotkey_config_show([] {});
}

static void top_menu_options_handle(menu_item &item) {
    if (item.id == "display_options") { 
        widget_top_menu_clear_state();
        ui::display_options_window::show(window_city_show); 
    }
    else if (item.id == "sound_options") { menu_options_sound(0); }
    else if (item.id == "speed_options") { menu_options_speed(0); }
    else if (item.id == "difficulty_options") { menu_options_difficulty(0); }
    else if (item.id == "autosave_options") { menu_options_autosave(0); }
    else if (item.id == "hotkeys_options") { menu_options_hotkeys(0); }
    else if (item.id == "enhanced_options") { menu_options_change_enh(0); }
}

static void menu_help_help(int param) {
    widget_top_menu_clear_state();
    window_go_back();
    window_message_dialog_show(MESSAGE_DIALOG_HELP, -1, window_city_draw_all);
}

static void menu_help_mouse_help(int param) {
    g_settings.toggle_tooltips();
    set_text_for_tooltips();
}
static void menu_help_warnings(int param) {
    g_settings.toggle_warnings();
    set_text_for_warnings();
}

static void menu_help_about(int param) {
    widget_top_menu_clear_state();
    window_go_back();
    window_message_dialog_show(MESSAGE_DIALOG_ABOUT, -1, window_city_draw_all);
}

static void top_menu_help_handle(menu_item &item) {
    if (item.id == "help") { menu_help_help(0); }
    else if (item.id == "mouse") { menu_help_mouse_help(0); }
    else if (item.id == "warnings") { menu_help_warnings(0); }
    else if (item.id == "about") { menu_help_about(0); }
}

static void top_menu_advisors_handle(menu_item &item) {
    widget_top_menu_clear_state();
    window_go_back();
    window_advisors_show_advisor((e_advisor)item.parameter);
}

static void widget_top_menu_init() {
    auto& data = g_top_menu;
    auto *options = data.headers["options"].dcast_menu_header();
    if (options) {
        options->item(0).hidden = system_is_fullscreen_only();
        options->onclick(top_menu_options_handle);
    }

    auto *file = data.headers["file"].dcast_menu_header();
    if (file) {
        file->item("new_game").hidden = config_get(CONFIG_UI_HIDE_NEW_GAME_TOP_MENU);
        file->onclick(top_menu_file_handle);
    }

    auto *help = data.headers["help"].dcast_menu_header();
    if (help) {
        help->onclick(top_menu_help_handle);
    }

    auto *advisors = data.headers["advisors"].dcast_menu_header();
    if (advisors) {
        advisors->onclick(top_menu_advisors_handle);
    }

    auto *debug = data.headers["debug"].dcast_menu_header();
    if (debug) {
        debug->onclick(menu_debug_change_opt);
    }

    auto *render = data.headers["debug_render"].dcast_menu_header();
    if (render) {
        render->onclick(menu_debug_render_change_opt);
    }

    g_debug_show_opts[e_debug_show_properties] = game.debug_properties;

    set_text_for_autosave();
    set_text_for_tooltips();
    set_text_for_warnings();
    set_text_for_debug_city();
    set_text_for_debug_render();
}

static void widget_sub_menu_draw_background(int) {
    window_city_draw_panels();
    window_city_draw();
    widget_sidebar_city_draw_foreground();
}

static void widget_sub_menu_draw_foreground(int) {
    auto& data = g_top_menu;
    if (!data.open_sub_menu) {
        return;
    }

    top_menu_menu_draw(data.open_sub_menu, data.focus_sub_menu_id);
}

void widget_sub_menu_show() {
    static window_type window = {
        WINDOW_TOP_MENU,
        widget_sub_menu_draw_background,
        widget_sub_menu_draw_foreground,
        widget_top_menu_handle_input
    };
    widget_top_menu_init();
    window_show(&window);
}

void wdiget_top_menu_draw_background() {
    painter ctx = game.painter();

    int img_id = image_group(g_top_menu.background);
    const image_t *img = image_get(img_id);
    const int block_width = img->width;
    assert(block_width > 0);

    for (int x = -(screen_width() - widget_sidebar_city_offset_x()); x < screen_width(); x += (block_width - g_top_menu.sidebar_offset)) {
       ImageDraw::img_generic(ctx, img_id, x, 0);
    }

    ImageDraw::img_generic(ctx, img_id, widget_sidebar_city_offset_x() - block_width + g_top_menu.sidebar_offset, 0);
}

void widget_top_menu_draw_rotate_buttons() {
    // Orientation icon
    auto &data = g_top_menu;
    painter ctx = game.painter();
    if (orientation_button_pressed) {
        ImageDraw::img_generic(ctx, image_id_from_group(GROUP_SIDEBAR_BUTTONS) + 72 + orientation_button_state + 3, data.offset_rotate, 0);
        orientation_button_pressed--;
    } else {
        ImageDraw::img_generic(ctx, image_id_from_group(GROUP_SIDEBAR_BUTTONS) + 72 + orientation_button_state, data.offset_rotate, 0);
    }
}

void top_menu_widget::draw_foreground(UiFlags flags) {
    OZZY_PROFILER_SECTION("Render/Frame/Window/City/Topmenu");

    wdiget_top_menu_draw_background();
    widget_top_menu_draw_elements();
    widget_top_menu_draw_rotate_buttons();

    color treasure_color = city_finance_treasury() < 0 ? COLOR_FONT_RED : COLOR_WHITE;

    e_font treasure_font = (city_finance_treasury() >= 0 ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_BLUE);
    int s_width = screen_width();

    offset_rotate = s_width - offset_rotate_basic;

    update_month_year_max_width(game.simtime.month, game.simtime.year);

    ui["funds"].font(treasure_font);
    ui["funds"].text_color(treasure_color);
    ui["funds"].text_var("%s %d", ui::str(6, 0), city_finance_treasury());

    ui["population"].text_var("%s %d", ui::str(6, 1), city_population());

    ui.begin_widget({ 0, 0 });
    ui.draw();
    ui.end_widget();
}

void widget_top_menu_draw() {
    g_top_menu.draw_foreground(0);
}

static bool widget_top_menu_handle_input_submenu(const mouse* m, const hotkeys* h) {
    auto& data = g_top_menu;
    if (m->right.went_up || h->escape_pressed) {
        widget_top_menu_clear_state();
        window_go_back();
        return true;
    }

    xstring menu_id = top_menu_bar_handle_mouse(m);
    if (!!menu_id && menu_id != data.open_sub_menu) {
        data.open_sub_menu = menu_id;
    }

    auto *header = data.headers[data.open_sub_menu].dcast_menu_header();
    if (!top_menu_menu_handle_mouse(m, header ? &header->impl : nullptr, data.focus_sub_menu_id)) {
        if (m->left.went_up) {
            widget_top_menu_clear_state();
            window_go_back();
            return true;
        }
    }
    return false;
}

int top_menu_widget::ui_handle_mouse(const mouse *m) {
    autoconfig_window::ui_handle_mouse(m);

    auto &data = g_top_menu;
    xstring menu_id = top_menu_bar_handle_mouse(m);
    if (!!menu_id && m->left.went_up) {
        data.open_sub_menu = menu_id;
        widget_sub_menu_show();
        return 0;
    }

    return 0;
}

void widget_top_menu_handle_input(const mouse* m, const hotkeys* h) {
    auto& data = g_top_menu;
    int result = 0;
    if (!widget_city_has_input()) {
        int button_id = 0;
        int handled = false;

        handled = generic_buttons_handle_mouse(m, {data.offset_rotate, 0}, orientation_buttons_ph, 3, &button_id);
        if (button_id) {
            orientation_button_state = button_id;
            if (handled)
                orientation_button_pressed = 5;
        } else {
            orientation_button_state = 0;
        }

        if (button_id)
            result = handled;
        else if (!!data.open_sub_menu)
            widget_top_menu_handle_input_submenu(m, h);
        else
            g_top_menu.ui_handle_mouse(m);
    }
}

int widget_top_menu_get_tooltip_text(tooltip_context* c) {
    auto& data = g_top_menu;
    //if (data.focus_menu_id)
    //    return 50 + data.focus_menu_id;
    //
    //int button_id = get_info_id(c->mpos);
    //if (button_id) {
    //    button_id += 1;
    //}
    //
    //if (button_id) {
    //    return 59 + button_id;
    //}

    return 0;
}