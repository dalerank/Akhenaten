#include "window_features.h"

#include "core/string.h"
#include "core/log.h"
#include "city/city.h"
#include "game/settings.h"
#include "game/game.h"
#include "game/system.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/button.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/panel.h"
#include "graphics/view/view.h"
#include "graphics/elements/scrollbar.h"
#include "graphics/image_groups.h"
#include "graphics/screen.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "game/game_config.h"
#include "content/dir.h"
#include "io/gamefiles/lang.h"
#include "window/hotkey_config.h"
#include "window/plain_message_dialog.h"
#include "scenario/scenario.h"
#include "window/select_list.h"
#include "empire/empire_city.h"
#include "js/js_game.h"

#include <string.h>
#include <numeric>

ui::window_features g_features_window;

void ui::window_features::cancel_values() {
    for (auto &p : pages) {
        for (auto &feature : p.features) {
            feature.new_value = feature.original_value;
        }
    }
}

bool ui::window_features::config_change_basic(feature_t &alias, const xstring fname) {
    if (!alias.is_changed()) {
        return true;
    }

    auto feature = game_features::find(fname);
    assert(feature);
    if (feature) {
        feature->set(alias.new_value ? true : false);
    }
    alias.original_value = alias.new_value;
    return true;
}

bool ui::window_features::config_change_string_language(const game_language &lang) {
    game_features::gameopt_language = lang.lang;

    bool ok = lang_reload_localized_files()
                && lang_reload_localized_tables();

    if (!ok) {
        // Notify user that language dir is invalid and revert to previously selected
        game_features::gameopt_language = "";
        window_plain_message_dialog_show("#TR_INVALID_LANGUAGE_TITLE", "#TR_INVALID_LANGUAGE_MESSAGE", SOURCE_LOCATION);
        return false;
    }

    return true;
}

bool ui::window_features::apply_changed_configs() {
    for (auto &p : pages) {
        for (auto &feature : p.features) {
            if (!feature.is_changed()) {
                continue;
            }

            if (!feature.change_action) {
                logs::error("Change action is not available for index: %s", feature.text.c_str());
                continue;
            }

            if (!feature.change_action()) {
                return false;
            }
        }
    }

    return true;
}

void ui::window_features::button_reset_defaults() {
    for (auto &p : pages) {
        for (auto &feature: p.features) {
            feature.new_value = feature.original_value;
        }
    }
}

void ui::window_features::button_close(bool save) {
    if (!save) {
        cancel_values();
        window_go_back();
        return;
    }

    if (apply_changed_configs()) {
        window_go_back();
    }
}

void ui::window_features::button_page(bool next) {
    if (next) {
        page++;
        if (page >= pages.size())
            page = 0;

    } else {
        page--;
        if (page < 0) {
            page = (int)pages.size() - 1;
        }
    }
}

int ui::window_features::ui_handle_mouse(const mouse* m) {
    int result = autoconfig_window::ui_handle_mouse(m);

    //mouse_button |= !!generic_buttons_handle_mouse(m_dialog, {0, 0}, &language_button, 1, &data.language_focus_button);

    const hotkeys *h = hotkey_state();
    if (!result && (m->right.went_up || h->escape_pressed)) {
        if (close_callback) {
            close_callback();
        }
        window_go_back();
    }

    return 0;
}

void ui::window_features::archive_load(archive arch) {
    const bool need_reinit = _is_inited;
    autoconfig_window::archive_load(arch);

    if (need_reinit) {
        init(close_callback);
    }
}

//void ui::window_features::toggle_building(int id, int param2) {
//    e_building_type type = (e_building_type)BUILDING_NONE;
//
//    bool can_build = building_menu_is_building_enabled(type);
//    building_menu_toggle_building(type, !can_build);
//    building_menu_invalidate();
//}

void ui::window_features::toggle_resource(e_resource resource) {
    bool can_produce = !g_city.can_produce_resource(resource);
    g_city.set_produce_resource(resource, can_produce);

    if (resource == RESOURCE_FISH) {
        if (can_produce) {
            g_city.fishing_points.reset();
        } else {
            g_city.fishing_points.clear();
        }
    }
}

void ui::window_features::init(std::function<void()> cb) {
    autoconfig_window::init();

    page = 0;
    close_callback = cb;

    auto gfeatures = game_features::all();

    pages.clear();

    int page_index = 0;

    pages.emplace_back();
    pages.back().title = "#TR_CONFIG_HEADER_GAMEPLAY_CHANGES";
    for (int i = 0; i < gfeatures.size(); ++i) {
        auto *feature = game_features::all()[i];
        if (feature->type() != setting_bool) {
           continue;
        }

        if (page_index != 0 && (page_index % FEATURES_PER_PAGE) == 0) {
            pages.emplace_back();
            pages.back().title = "#TR_CONFIG_HEADER_GAMEPLAY_CHANGES";
        }

        auto &pageref = pages.back();
        auto &alias = pageref.features.emplace_back();
        
        alias.get_value = [feature] () -> int { return feature->to_bool(); };
        const bool value = alias.get_value();
        alias.original_value = value;
        alias.new_value = value;
        alias.change_action = [&,name = feature->name] () -> bool { return config_change_basic(alias, name); };
        alias.toggle_action = [&] (int p1, int p2) { alias.new_value = (alias.new_value > 0) ? false : true;  };
        alias.text = feature->text;

        page_index++;
    }

    {
        auto &pageref = pages.emplace_back();
        pages.back().title = "#TR_CONFIG_HEADER_SCENARIO_CHANGES";
        {
            auto &alias = pageref.features.emplace_back();
            alias.get_value = [] () -> bool { return g_scenario.env.has_animals; };
            alias.change_action = [&] () -> bool { return g_scenario.env.has_animals = alias.new_value; };
            alias.toggle_action = [&] (int p1, int p2) { alias.new_value = (alias.new_value > 0) ? false : true;  };
            alias.text = "#TR_CONFIG_ANIMALS";
        }

        {
            auto &alias = pageref.features.emplace_back();
            alias.get_value = [] () -> bool { return g_scenario.env.flotsam_enabled; };
            alias.change_action = [&] () -> bool { return g_scenario.env.flotsam_enabled = alias.new_value; };
            alias.toggle_action = [&] (int p1, int p2) { alias.new_value = (alias.new_value > 0) ? false : true;  };
            alias.text = "#TR_CONFIG_FLOTSAM";
        }
    }

    {
        auto &pageref = pages.emplace_back();
        pageref.title = "#TR_CONFIG_HEADER_GODS_CHANGES";
        for (int i = 0; i < 5; i++) {
            auto &alias = pageref.features.emplace_back();

            alias.get_value = [i] () -> int { return g_city.religion.is_god_known((e_god)i); };
            alias.original_value = g_city.religion.is_god_known((e_god)i);
            alias.new_value = g_city.religion.is_god_known((e_god)i);
            alias.toggle_action = [&] (int p1, int p2) { alias.new_value = (alias.new_value > 0) ? false : true;  };

            bstring64 text; text.printf("God disabled %s", e_god_tokens.name((e_god)i));
            alias.text = text;
            alias.change_action = [alias, god = e_god(i)] () -> bool {
                bool known = !alias.new_value;
                const auto new_status = known ? GOD_STATUS_KNOWN : GOD_STATUS_UNKNOWN;
                events::emit(event_religion_god_status_update{ god, new_status });
                g_city.religion.set_god_known(god, new_status);
                return true;
            };
        }
    }

    {
        auto &pageref = pages.emplace_back();
        pages.back().title = "#TR_CONFIG_HEADER_RESOURCES";
        const resource_list city_resources = g_city.resource.available();
        for (int i = 1; i < resource_list::all.size(); ++i) {
            if (i != 0 && (i % FEATURES_PER_PAGE) == 0) {
                pages.emplace_back();
                pages.back().title = "#TR_CONFIG_HEADER_RESOURCES";
            }

            auto &pageref = pages.back();
            auto &feature = pageref.features.emplace_back();

            const resource_value r = resource_list::all.at(i);
            const bool allow = city_resources[r.type] > 0;

            feature.get_value = [r] () -> bool { return  g_city.resource.available()[r.type] > 0; };
            const bool value = feature.get_value();
            feature.original_value = value;
            feature.new_value = value;
            feature.change_action = [this, r] () -> bool { this->toggle_resource(r.type); return true; };
            feature.toggle_action = [&feature] (int p1, int p2) { 
                feature.new_value = (feature.new_value > 0) ? false : true;
            };

            bstring64 text; text.printf("City allow %s", ui::resource_name(r.type));
            feature.text = text;
        }
    }

    {
        auto &pageref = pages.emplace_back();
        pages.back().title = "#TR_CONFIG_HEADER_LANGUAGES";

        auto& game_languages = get_available_languages();
        for (int i = 0; i < game_languages.size(); i++) {
            const auto &config = game_languages[i];
            if (i != 0 && (i % FEATURES_PER_PAGE) == 0) {
                pages.emplace_back();
                pages.back().title = "#TR_CONFIG_HEADER_LANGUAGES";
            }

            auto &pageref = pages.back();
            auto &feature = pageref.features.emplace_back();

            feature.get_value = [lang = config, this] () -> bool { 
                const xstring curlang = game_features::gameopt_language.to_string();
                return (curlang == lang.lang || (curlang.empty() && lang.lang == "en"));
            };
            const bool value = feature.get_value();
            feature.original_value = value;
            feature.new_value = value;
            feature.volatile_value = true;
            feature.change_action = [] () -> bool { return false; };
            feature.toggle_action = [lpack = config, this, &feature] (int p1, int p2) {
                this->config_change_string_language(lpack);
            };
            feature.text = config.caption;
        }
    }  

    ui["btn_defaults"].onclick([this] { button_reset_defaults(); });
    ui["btn_hotkeys"].onclick([this] { window_hotkey_config_show([] {}); });
    ui["btn_close"].onclick([this] { button_close(false); });
    ui["btn_save"].onclick([this] { button_close(true); });
    ui["btn_next"].onclick([this] { button_page(true); });
    ui["btn_prev"].onclick([this] { button_page(false); });
}

void ui::window_features::ui_draw_foreground(UiFlags flags) {
    ui["title"] = pages[page].title;

    auto btn = [&] (int i) -> ui::element& { bstring32 id; id.printf("bfeature%d", i); return ui[id]; };
    auto lb = [&] (int i) -> ui::element& { bstring32 id; id.printf("tfeature%d", i); return ui[id]; };
    for (int i = 0; i < FEATURES_PER_PAGE; ++i) {
        auto &b = btn(i); b.enabled = false;
        auto &l = lb(i); l.enabled = false;
    }

    for (int i = 0; i < pages[page].features.size(); ++i) {
        auto &feature = pages[page].features[i];
        
        auto &b = btn(i);
        if (feature.volatile_value) {
            b = feature.get_value() ? "x" : "";
        } else {
            b = feature.new_value ? "x" : "";
        }
        b.enabled = true;

        b.onclick(feature.toggle_action);

        auto &l = lb(i);
        l = feature.text;
        l.enabled = true;
    }

    ui.begin_widget(pos);

    ui.draw();

    ui.end_widget();
}

void ui::window_features::show(std::function<void()> close_callback) {
    static window_type window = {
        WINDOW_CONFIG,
        [] (int flags) { g_features_window.draw_background(flags); },
        [] (int flags) { g_features_window.ui_draw_foreground(flags); },
        [] (auto m, auto h) { g_features_window.ui_handle_mouse(m); }
    };

    g_features_window.init(close_callback);
    window_show(&window);
}

void window_features_show() { ui::window_features::show([] {}); }
ANK_FUNCTION(window_features_show)