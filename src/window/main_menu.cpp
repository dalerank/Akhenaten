#include "main_menu.h"

#include "editor/editor.h"
#include "core/log.h"
#include "platform/platform.h"
#include "graphics/elements/ui.h"
#include "graphics/graphics.h"
#include "graphics/window.h"
#include "graphics/screen.h"
#include "graphics/image.h"
#include "game/game.h"
#include "game/settings.h"
#include "game/game_config.h"
#include "core/app.h"
#include "js/js_game.h"
#include "window/records.h"
#include "window/popup_dialog.h"
#include "window/player_selection.h"
#include "window/file_dialog.h"
#include "window/config.h"
#include "window/window_city.h"
#include "sound/music.h"
#include "io/gamestate/boilerplate.h"
#include "resource/icons.h"

#ifdef GAME_PLATFORM_WIN
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "core/httplib.h"
#endif

//autoconfig_window_t<window_warnings>
ui::widget g_main_menu_data;

ANK_REGISTER_CONFIG_ITERATOR(config_load_main_menu);
void config_load_main_menu() {
    g_config_arch.r_section("main_menu_window", [] (archive arch) {
        g_main_menu_data.load(arch);
    });
}

int main_menu_get_total_commits(pcstr owner, pcstr repo) {
#ifdef GAME_PLATFORM_WIN
    bstring256 req;
    req.printf("https://api.github.com/repos/%s/%s/commits?per_page=1", owner, repo);
    httplib::Url url(req.c_str());
    httplib::SSLClient sslClient(url.host);

    auto res = sslClient.Get(req.c_str());

    if (res && res->status == 200) {
        std::smatch match;
        std::regex link_regex(R"(<([^>]+)>; rel="last")");
        std::string link_header = res->get_header_value("Link");

        if (std::regex_search(link_header, match, link_regex)) {
            std::string last_page_url = match[1].str();
            std::regex page_regex(R"(&page=(\d+))");
            if (std::regex_search(last_page_url, match, page_regex)) {
                return std::stoi(match[1].str());
            }
        }
        return 1; // If no pagination, assume one page exists
    } else {
        std::cerr << "Error: Unable to fetch commits (status code " << (res ? res->status : 0) << ")" << std::endl;
        return -1;
    }
#else
    return -1;
#endif // GAME_PLATFORM_WIN
}

void main_menu_download_latest_version() {
#ifdef GAME_PLATFORM_WIN
    game.mt.detach_task([] () {
        ShellExecuteA(0, "Open", "update_binary_windows.cmd", 0, 0, SW_SHOW);
    });
#endif // GAME_PLATFORM_WIN
}

static void main_menu_draw_background(int) {
    graphics_clear_screen();

    auto &ui = g_main_menu_data;
    ui["continue_game"].onclick([] {
        const xstring last_save = g_ankh_config.get(CONFIG_STRING_LAST_SAVE);
        const xstring last_player = g_ankh_config.get(CONFIG_STRING_LAST_PLAYER);
        g_settings.set_player_name((const uint8_t *)last_player.c_str());
        if (GamestateIO::load_savegame(last_save.c_str())) {
            window_city_show();
        }
    });

    ui["select_player"].onclick([] {
        window_player_selection_show(); 
    });

    ui["show_records"].onclick([] {
        window_records_show();
    });

    ui["show_config"].onclick([] {
        window_config_show([] {
        
        });
    });

    ui["quit_game"].onclick([] { 
        popup_dialog::show_yesno("#popup_dialog_quit", [] {
            app_request_exit(); 
        });
    });

    ui["discord"].onclick([] {
        platform.open_url("https://discord.gg/HS4njmBvpb", "");
    });

    ui["patreon"].onclick([] {
        platform.open_url("https://www.patreon.com/imspinner", "");
    });

    ui["update_game"].onclick([] {
        main_menu_download_latest_version();
    });
}

void main_menu_draw_foreground(int) {
    auto &ui = g_main_menu_data;

    ui.begin_frame();
    ui.draw();
}

void main_menu_init() {
    auto &ui = g_main_menu_data;
    game.mt.detach_task([&] () {
        int current_commit = main_menu_get_total_commits("dalerank", "Akhenaten");

        if (current_commit <= 1) {
            return;
        }

        ui["update_panel"].enabled = true;
        ui["new_version"].enabled = true;
        ui["update_game"].enabled = true;
        ui["new_version"] = bstring32(current_commit);
    });
}

void main_menu_handle_input(const mouse* m, const hotkeys* h) {
    ui::handle_mouse(m);

    if (h->escape_pressed) {
        popup_dialog::show_yesno("#popup_dialog_quit", [] {
            app_request_exit();
        });
    }

    if (h->load_file) {
        window_file_dialog_show(FILE_TYPE_SAVED_GAME, FILE_DIALOG_LOAD);
    }
}

void window_main_menu_show(bool restart_music) {
    if (restart_music) {
        sound_music_play_intro();
    }

    static window_type window = {
        WINDOW_MAIN_MENU,
        main_menu_draw_background,
        main_menu_draw_foreground,
        main_menu_handle_input
    };

    main_menu_init();
    window_show(&window);
}
