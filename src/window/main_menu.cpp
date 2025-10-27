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
#include "window/records.h"
#include "window/popup_dialog.h"
#include "window/player_selection.h"
#include "window/file_dialog.h"
#include "window/window_features.h"
#include "window/window_city.h"
#include "sound/sound.h"
#include "io/gamestate/boilerplate.h"
#include "resource/icons.h"

#ifdef GAME_PLATFORM_WIN
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "core/httplib.h"
#endif

main_menu_screen g_main_menu;

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

int main_menu_screen::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

    graphics_clear_screen();
    return 0;
}

void main_menu_screen::draw_foreground(UiFlags flags) {
    ui.begin_frame();
    ui.draw();
}

void main_menu_screen::init() {
    game.mt.detach_task([&] () {
        int current_commit = main_menu_get_total_commits("dalerank", "Akhenaten");

        if (current_commit <= 1) {
            return;
        }

        const xstring last_version_str = game_features::gameopt_last_game_version.to_string();
        const int last_version = std::atoi(last_version_str.c_str());

        if (last_version == current_commit) {
            return;
        }

        ui["update_panel"].enabled = true;
        ui["new_version"].enabled = true;
        ui["update_game"].enabled = true;
        ui["new_version"] = bstring32(current_commit);
        game_features::gameopt_last_game_version.set(current_commit);
    });

    ui["continue_game"].onclick([] {
        const xstring last_save = game_features::gameopt_last_save_filename.to_string();
        const xstring last_player = game_features::gameopt_last_player.to_string();
        g_settings.set_player_name((const uint8_t *)last_player.c_str());
        if (GamestateIO::load_savegame(last_save.c_str())) {
            window_city_show();
        }
    });

    ui["show_records"].onclick([] {
        window_records_show();
    });

    ui["show_config"].onclick([] {
        ui::window_features::show([] {});
    });

    ui["show_mods"].onclick([] {

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

void main_menu_handle_input(const mouse* m, const hotkeys* h) {
    ui::handle_mouse(m);

    if (h->escape_pressed) {
        popup_dialog::show_yesno("#popup_dialog_quit", [] {
            app_request_exit();
        });
    }
}

void main_menu_screen::show(bool restart_music) {
    if (restart_music) {
        g_sound.play_intro();
    }

    static window_type window = {
        WINDOW_MAIN_MENU,
        [] (int flags) { instance().draw_background(flags); },
        [] (int flags) { instance().draw_foreground(flags); },
        [] (auto m, auto h) { instance().ui_handle_mouse(m); },
    };

    instance().init();
    window_show(&window);
}

main_menu_screen &main_menu_screen::instance() {
    return g_main_menu;
}
