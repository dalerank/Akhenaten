#include "widget_top_menu_game.h"

#include "game/game.h"

#include "graphics/elements/menu.h"
#include "graphics/elements/ui.h"
#include "graphics/screenshot.h"
#include "graphics/window.h"
#include "graphics/graphics.h"
#include "city/constants.h"
#include "city/city.h"
#include "core/profiler.h"
#include "core/core_utility.h"
#include "config/config.h"
#include "game/settings.h"
#include "game/orientation.h"
#include "game/cheats.h"
#include "game/state.h"
#include "game/undo.h"
#include "window/file_dialog.h"
#include "window/message_dialog.h"
#include "io/gamestate/boilerplate.h"
#include "building/construction/build_planner.h"
#include "game/system.h"
#include "window/display_options.h"
#include "window/advisors.h"
#include "window/window_city.h"
#include "window/difficulty_options.h"
#include "window/config.h"
#include "window/game_menu.h"
#include "window/hotkey_config.h"
#include "window/main_menu.h"
#include "window/popup_dialog.h"
#include "window/speed_options.h"
#include "window/sound_options.h"
#include "widget/widget_sidebar.h"
#include "dev/debug.h"

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

    struct {
        int population = 0;
    } states;

    ui::widget headers;

    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int draw_background(UiFlags flags) override { return 0; }
    virtual void draw_foreground(UiFlags flags) override;
    virtual void ui_draw_foreground(UiFlags flags) override {}
    virtual int get_tooltip_text() override { return 0; }
    virtual int ui_handle_mouse(const mouse *m) override;
    virtual void init() override;
    virtual void on_mission_start() override;
    void draw_background_impl();
    void draw_elements_impl();
    void draw_rotate_buttons();
    xstring get_selected_header(const mouse *m);
    xstring bar_handle_mouse(const mouse *m);
    bool handle_input_submenu(const mouse *m, const hotkeys *h);
    void sub_menu_draw_foreground(int flags);
    void sub_menu_draw_background(int flags);
    void sub_menu_draw_text(const xstring header, const xstring focus_item_id);
    void sub_menu_init();
    void advisors_handle(menu_item &item);
    void help_handle(menu_item &item);
    void options_handle(menu_item &item);
    void file_handle(menu_item &item);
    void set_text_for_debug_render();
    void set_text_for_debug_city();
    void set_text_for_autosave();
    void set_text_for_tooltips();
    void set_text_for_warnings();
    void item_update_text(pcstr path, pcstr text);
    void header_update_text(pcstr header, pcstr text);
    xstring menu_handle_mouse(const mouse *m, menu_header *menu, xstring &focus_item_id);
    xstring get_subitem(const mouse *m, menu_header &menu);
    void calculate_menu_dimensions(menu_header &menu);
    void debug_render_change_opt(menu_item &item);
    void debug_change_opt(menu_item &item);
    void debug_opt_text(int opt, bool v);
    void debug_render_text(int opt, bool v);

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
    void update_date(event_advance_day);
    void update_finance(event_finance_changed ev);
};

top_menu_widget g_top_menu;

int orientation_button_state = 0;
int orientation_button_pressed = 0;

static generic_button orientation_buttons_ph[] = {
    {12, 0, 36 - 24, 21, button_rotate_reset, button_none, 0, 0},
    {0, 0, 12, 21, button_rotate_left, button_none, 0, 0},
    {36 - 12, 0, 12, 21, button_rotate_right, button_none, 0, 0},
};

void top_menu_widget::on_mission_start() {
    init();
}

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

    g_city_events.subscribe([this] (event_population_changed ev) { states.population = ev.value; });
    g_city_events.subscribe([this] (event_advance_day ev) { update_date(ev); });
    g_city_events.subscribe([this] (event_finance_changed ev) { update_finance(ev); });
}

void top_menu_widget::menu_item_update(pcstr header, int item, pcstr text) {
    auto menu = headers[header].dcast_menu_header();
    if (!menu) {
        return;
    }

    menu->item(item).text = text;
}

void top_menu_widget::update_date(event_advance_day ev) {
    pcstr month_str = ui::str(25, ev.month);
    bstring32 text;
    if (ev.year >= 0) {
        int use_year_ad = locale_year_before_ad();
        if (use_year_ad) { text.printf("%s %d %s", month_str, ev.year, ui::str(20, 1)); }
        else { text.printf("%s %s %d", month_str, ev.year, ui::str(20, 1)); }
    } else {
        text.printf("%s %d %s", month_str, -ev.year, ui::str(20, 0));
    }

    ui["date"] = text;
}

void top_menu_widget::update_finance(event_finance_changed ev) {
    color treasure_color = ev.value < 0 ? COLOR_FONT_RED : COLOR_WHITE;
    e_font treasure_font = (ev.value >= 0 ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_BLUE);
    ui["funds"].font(treasure_font);
    ui["funds"].text_color(treasure_color);
    ui["funds"].text_var("%s %d", ui::str(6, 0), ev.value);
}

void top_menu_widget::debug_render_text(int opt, bool v) {
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
        {"Entertainment ON", "Entertainment OFF"},
        {"Canals ON", "Canals OFF"},
    };
    const auto &current = debug_text_rend[opt];
    menu_item_update("debug_render", opt, v ? current.on : current.off);
}

void top_menu_widget::debug_opt_text(int opt, bool v) {
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
    menu_item_update("debug", opt, v ? current.on : current.off);
}

void top_menu_widget::debug_change_opt(menu_item &item) {
    int opt = item.parameter;
    switch (opt) {
    case e_debug_show_console: 
        game_cheat_console(true); 
        break;

    case e_debug_make_screenshot: 
        widget_top_menu_clear_state();
        window_go_back();
        graphics_save_screenshot(SCREENSHOT_DISPLAY);
        break;

    case e_debug_make_full_screenshot: 
        widget_top_menu_clear_state();
        window_go_back();
        graphics_save_screenshot(SCREENSHOT_FULL_CITY);
        break;

    case e_debug_show_properties: 
        game.debug_properties = !game.debug_properties;
        g_debug_show_opts[opt] = game.debug_properties;
        widget_top_menu_clear_state();
        window_go_back();
        debug_opt_text(e_debug_show_properties, game.debug_properties );
        break;

    case e_debug_write_video: 
        game.set_write_video(!game.get_write_video());
        debug_opt_text(e_debug_write_video, game.get_write_video());
        g_debug_show_opts[opt] = game.get_write_video();
        break;

    default:
        g_debug_show_opts[opt] = !g_debug_show_opts[opt];
        debug_opt_text(opt, g_debug_show_opts[opt]);
    }
}

void top_menu_widget::debug_render_change_opt(menu_item &item) {
    int opt = item.parameter;
    g_debug_render = (opt == g_debug_render) ? 0 : opt;
    auto *render = headers["debug_render"].dcast_menu_header();
    for (int i = 0; i < render->impl.items.size(); ++i) {
        debug_render_text(i, g_debug_render == render->impl.items[i].parameter);
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

void top_menu_widget::draw_elements_impl() {
    vec2i cur_offset = offset;
    e_font hightlight_font = config_get(CONFIG_UI_HIGHLIGHT_TOP_MENU_HOVER) ? FONT_NORMAL_YELLOW : FONT_NORMAL_BLACK_ON_LIGHT;
    for (auto &it : headers.elements) {
        ui::emenu_header *header = it->dcast_menu_header();

        if (!header) {
            continue;
        }

        const bool is_hovered = (it->id == focus_menu_id);

        header->impl.x_start = cur_offset.x;
        header->font(is_hovered ? hightlight_font : FONT_NORMAL_BLACK_ON_LIGHT);
        header->pos = vec2i{cur_offset.x, offset.y};
        header->draw(UiFlags_None);

        if (is_hovered) {
            ui::set_tooltip(header->tooltip());
        }

        cur_offset.x += header->text_width();
        header->impl.x_end = cur_offset.x;
        cur_offset.x += spacing;
    }
}

xstring top_menu_widget::get_selected_header(const mouse* m) {
    for (auto &it : headers.elements) {
        ui::emenu_header *header = it->dcast_menu_header();

        if (!header) {
            continue;
        }

        if (header->impl.x_start <= m->x && header->impl.x_end > m->x && offset.y <= m->y && offset.y + 12 > m->y) {
            return header->id;
        }
    }
    return {};
}

xstring top_menu_widget::bar_handle_mouse(const mouse* m) {
    focus_menu_id = get_selected_header(m);
    return get_selected_header(m);
}

void top_menu_widget::calculate_menu_dimensions(menu_header& menu) {
    int max_width = 0;
    int height_pixels = item_height;
    for (const auto &item: menu.items) {
        if (item.hidden) {
            continue;
        }

        int width_pixels = lang_text_get_width(item.text.c_str(), FONT_NORMAL_BLACK_ON_LIGHT);
        max_width = std::max(max_width, width_pixels);

        height_pixels += item_height;
    }
    int blocks = (max_width + 8) / 16 + 1; // 1 block padding
    menu.calculated_width_blocks = blocks < 10 ? 10 : blocks;
    menu.calculated_height_blocks = height_pixels / 16;
}

void top_menu_widget::sub_menu_draw_text(const xstring header, const xstring focus_item_id) {
    auto &impl = ((ui::emenu_header *)&headers[header])->impl;

    if (impl.calculated_width_blocks == 0 || impl.calculated_height_blocks == 0) {
        calculate_menu_dimensions(impl);
    }

    unbordered_panel_draw(impl.x_start, TOP_MENU_HEIGHT, impl.calculated_width_blocks, impl.calculated_height_blocks);
    int y_offset = TOP_MENU_HEIGHT + offset.y * 2;
    for (const auto &item: impl.items) {
        if (item.hidden) {
            continue;
        }
        // Set color/font on the menu item mouse hover
        lang_text_draw(item.text.c_str(), vec2i{impl.x_start + 8, y_offset}, item.id == focus_item_id ? FONT_NORMAL_YELLOW : FONT_NORMAL_BLACK_ON_LIGHT);
        y_offset += item_height;
    }
}

xstring top_menu_widget::get_subitem(const mouse* m, menu_header &menu) {
    int y_offset = TOP_MENU_HEIGHT + offset.y * 2;

    for (const auto &item: menu.items) {
        if (item.hidden) {
            continue;
        }

        if (menu.x_start <= m->x && menu.x_start + 16 * menu.calculated_width_blocks > m->x && y_offset - 2 <= m->y && y_offset + 19 > m->y) {
            return item.id;
        }

        y_offset += item_height;
    }

    return {};
}

xstring top_menu_widget::menu_handle_mouse(const mouse* m, menu_header* menu, xstring& focus_item_id) {
    if (!menu) {
        return "";
    }

    xstring item_id = get_subitem(m, *menu);
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

void top_menu_widget::header_update_text(pcstr header, pcstr text) {
    auto &impl = ((ui::emenu_header *)&headers[header])->impl;

    headers[header].text(text);
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

void top_menu_widget::item_update_text(pcstr path, pcstr text) {
    auto pair = split_string(path);
    auto header = headers[pair.first].dcast_menu_header();
    auto &item = header->item(pair.second);
    item.text = text;
}

void widget_top_menu_clear_state() {
    auto& data = g_top_menu;

    data.open_sub_menu = "";
    data.focus_menu_id = "";
    data.focus_sub_menu_id = "";
}

void top_menu_widget::set_text_for_autosave() {
    item_update_text("options/autosave_options", ui::str(19, g_settings.monthly_autosave ? 51 : 52));
}

void top_menu_widget::set_text_for_tooltips() {
    item_update_text("help/mouse", ui::str(3, g_settings.tooltips + 2));
}

void top_menu_widget::set_text_for_warnings() {
    item_update_text("help/warnings", ui::str(3, g_settings.warnings ? 6 : 5));
}

void top_menu_widget::set_text_for_debug_city() {
    auto *debug = headers["debug"].dcast_menu_header();
    for (int i = 0; i < debug->impl.items.size(); ++i) {
        debug_opt_text(i, g_debug_show_opts[i]);
    }
}

void top_menu_widget::set_text_for_debug_render() {
    auto *render = headers["debug_render"].dcast_menu_header();
    for (int i = 0; i < render->impl.items.size(); ++i) {
        debug_render_text(i, g_debug_render == render->impl.items[i].parameter);
    }
}

void top_menu_widget::file_handle(menu_item &item) {
    if (item.id == "new_game") { 
        widget_top_menu_clear_state();
        popup_dialog::show_yesno("#popup_dialog_quit", [] (bool confirmed) {
            if (!confirmed) {
                window_city_show();
                return;
            }

            g_city_planner.reset();
            game_undo_disable();
            game_state_reset_overlay();
            window_game_menu_show();
        });
    }
    else if (item.id == "replay_map") { 
        widget_top_menu_clear_state();
        popup_dialog::show_yesno("#replay_mission", [] (bool confirmed) {
            if (!confirmed) {
                window_city_show();
                return;
            }

            g_city_planner.reset();
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
    else if (item.id == "load_game") { 
        widget_top_menu_clear_state();
        g_city_planner.reset();
        window_city_show();
        window_file_dialog_show(FILE_TYPE_SAVED_GAME, FILE_DIALOG_LOAD);
    }
    else if (item.id == "save_game") { 
        widget_top_menu_clear_state();
        window_city_show();
        window_file_dialog_show(FILE_TYPE_SAVED_GAME, FILE_DIALOG_SAVE);
    }
    else if (item.id == "delete_game") { 
        widget_top_menu_clear_state();
        window_city_show();
        window_file_dialog_show(FILE_TYPE_SAVED_GAME, FILE_DIALOG_DELETE);
    }
    else if (item.id == "exit_game") { 
        widget_top_menu_clear_state();
        popup_dialog::show_yesno("#popup_dialog_quit", [] (bool accepted) {
            if (accepted) {
                widget_top_menu_clear_state();
                window_main_menu_show(true);
            } else {
                window_city_show();
            }
        });
    }
}

void top_menu_widget::options_handle(menu_item &item) {
    if (item.id == "display_options") { 
        widget_top_menu_clear_state();
        ui::display_options_window::show(window_city_show); 
    }
    else if (item.id == "sound_options") { 
        widget_top_menu_clear_state();
        window_sound_options_show(window_city_show);
    }
    else if (item.id == "speed_options") { 
        widget_top_menu_clear_state();
        window_speed_options_show(window_city_show);
    }
    else if (item.id == "difficulty_options") { 
        widget_top_menu_clear_state();
        window_difficulty_options_show(window_city_show);
    }
    else if (item.id == "autosave_options") {
        g_settings.toggle_monthly_autosave();
        set_text_for_autosave();
    }
    else if (item.id == "hotkeys_options") { 
        window_hotkey_config_show([] {});
    }
    else if (item.id == "enhanced_options") { 
        window_config_show([] {});
    }
}

void top_menu_widget::help_handle(menu_item &item) {
    if (item.id == "help") { 
        widget_top_menu_clear_state();
        window_go_back();
        window_message_dialog_show(MESSAGE_DIALOG_HELP, -1, window_city_draw_all);
    }
    else if (item.id == "mouse") { 
        g_settings.toggle_tooltips();
        set_text_for_tooltips();
    }
    else if (item.id == "warnings") { 
        g_settings.toggle_warnings();
        set_text_for_warnings();
    }
    else if (item.id == "about") { 
        widget_top_menu_clear_state();
        window_go_back();
        window_message_dialog_show(MESSAGE_DIALOG_ABOUT, -1, window_city_draw_all);
    }
}

void top_menu_widget::advisors_handle(menu_item &item) {
    widget_top_menu_clear_state();
    window_go_back();
    window_advisors_show_advisor((e_advisor)item.parameter);
}

void top_menu_widget::sub_menu_init() {
    auto *options = headers["options"].dcast_menu_header();
    if (options) {
        options->item(0).hidden = system_is_fullscreen_only();
        options->onclick([this] (auto &h) { options_handle(h); });
    }

    auto *file = headers["file"].dcast_menu_header();
    if (file) {
        file->item("new_game").hidden = config_get(CONFIG_UI_HIDE_NEW_GAME_TOP_MENU);
        file->onclick([this] (auto &h) { file_handle(h); });
    }

    auto *help = headers["help"].dcast_menu_header();
    if (help) {
        help->onclick([this] (auto &h) { help_handle(h); });
    }

    auto *advisors = headers["advisors"].dcast_menu_header();
    if (advisors) {
        advisors->onclick([this] (auto &h) { advisors_handle(h); });
    }

    auto *debug = headers["debug"].dcast_menu_header();
    if (debug) {
        debug->onclick([this] (auto &h) { debug_change_opt(h); });
    }

    auto *render = headers["debug_render"].dcast_menu_header();
    if (render) {
        render->onclick([this] (auto &h) { debug_render_change_opt(h); });
    }

    g_debug_show_opts[e_debug_show_properties] = game.debug_properties;

    set_text_for_autosave();
    set_text_for_tooltips();
    set_text_for_warnings();
    set_text_for_debug_city();
    set_text_for_debug_render();
}

void top_menu_widget::sub_menu_draw_background(int flags) {
    window_city_draw_panels();
    window_city_draw();
    widget_sidebar_city_draw_foreground();
}

void top_menu_widget::sub_menu_draw_foreground(int) {
    if (!open_sub_menu) {
        return;
    }

    sub_menu_draw_text(open_sub_menu, focus_sub_menu_id);
}

void widget_sub_menu_show() {
    static window_type window = {
        WINDOW_TOP_MENU,
        [] (int flags) { g_top_menu.sub_menu_draw_background(flags); },
        [] (int flags) { g_top_menu.sub_menu_draw_foreground(flags); },
        widget_top_menu_handle_input
    };
    g_top_menu.sub_menu_init();
    window_show(&window);
}

void top_menu_widget::draw_background_impl() {
    painter ctx = game.painter();

    int img_id = image_group(background);
    const image_t *img = image_get(img_id);
    const int block_width = img->width;
    assert(block_width > 0);

    for (int x = -(screen_width() - widget_sidebar_city_offset_x()); x < screen_width(); x += (block_width - sidebar_offset)) {
       ImageDraw::img_generic(ctx, img_id, x, 0);
    }

    ImageDraw::img_generic(ctx, img_id, widget_sidebar_city_offset_x() - block_width + sidebar_offset, 0);
}

void top_menu_widget::draw_rotate_buttons() {
    // Orientation icon
    painter ctx = game.painter();
    if (orientation_button_pressed) {
        ImageDraw::img_generic(ctx, image_id_from_group(GROUP_SIDEBAR_BUTTONS) + 72 + orientation_button_state + 3, offset_rotate, 0);
        orientation_button_pressed--;
    } else {
        ImageDraw::img_generic(ctx, image_id_from_group(GROUP_SIDEBAR_BUTTONS) + 72 + orientation_button_state, offset_rotate, 0);
    }
}

void top_menu_widget::draw_foreground(UiFlags flags) {
    OZZY_PROFILER_SECTION("Render/Frame/Window/City/Topmenu");

    draw_background_impl();
    draw_elements_impl();
    draw_rotate_buttons();

    int s_width = screen_width();

    offset_rotate = s_width - offset_rotate_basic;

    ui["population"].text_var("%s %d", ui::str(6, 1), states.population);

    ui.begin_widget({ 0, 0 });
    ui.draw();
    ui.end_widget();
}

void widget_top_menu_draw() {
    g_top_menu.draw_foreground(0);
}

bool top_menu_widget::handle_input_submenu(const mouse* m, const hotkeys* h) {
    if (m->right.went_up || h->escape_pressed) {
        widget_top_menu_clear_state();
        window_go_back();
        return true;
    }

    xstring menu_id = bar_handle_mouse(m);
    if (!!menu_id && menu_id != open_sub_menu) {
        open_sub_menu = menu_id;
    }

    auto *header = headers[open_sub_menu].dcast_menu_header();
    if (!menu_handle_mouse(m, header ? &header->impl : nullptr, focus_sub_menu_id)) {
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

    xstring menu_id = bar_handle_mouse(m);
    if (!!menu_id && m->left.went_up) {
        open_sub_menu = menu_id;
        widget_sub_menu_show();
        return 0;
    }

    return 0;
}

void widget_top_menu_handle_input(const mouse* m, const hotkeys* h) {
    int result = 0;
    if (!widget_city_has_input()) {
        int button_id = 0;
        int handled = false;

        handled = generic_buttons_handle_mouse(m, { g_top_menu.offset_rotate, 0}, orientation_buttons_ph, 3, &button_id);
        if (button_id) {
            orientation_button_state = button_id;
            if (handled)
                orientation_button_pressed = 5;
        } else {
            orientation_button_state = 0;
        }

        if (button_id) { result = handled; }
        else if (!!g_top_menu.open_sub_menu) { g_top_menu.handle_input_submenu(m, h); }
        else { g_top_menu.ui_handle_mouse(m); }
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