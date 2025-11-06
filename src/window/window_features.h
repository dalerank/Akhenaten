#pragma once

#include "platform/renderer.h"
#include "autoconfig_window.h"

struct lang_pack;
namespace game_features {
    struct game_feature;
}

namespace ui {
    struct window_features : public autoconfig_window_t<window_features> {
        enum {
            FEATURES_PER_PAGE = 14,
            MAX_LANGUAGE_DIRS = 20,
            CONFIG_STRING_VALUE_MAX = 64,
        };

        int focus_button;
        int language_focus_button;
        int bottom_focus_button;
        int page_focus_button;
        int page;
        std::function<void()> close_callback;

        struct feature_t {
            int original_value;
            int new_value;
            xstring text;
            bool volatile_value = false;
            std::function<void(int, int)> toggle_action;
            std::function<int()> change_action;
            std::function<int()> get_value;

            bool is_changed() const { return new_value != original_value; }
        };

        struct features_page_t {
            xstring title;
            svector<feature_t, 14> features;
        };

        svector<features_page_t, 16> pages;

        virtual int handle_mouse(const mouse *m) override { return 0; }
        virtual int get_tooltip_text() override { return 0; }
        virtual void draw_foreground(UiFlags flags) override {}
        virtual void ui_draw_foreground(UiFlags flags) override;
        virtual int ui_handle_mouse(const mouse *m) override;
        virtual void archive_load(archive arch) override;
        virtual void init() override {}

        void button_reset_defaults();
        void button_close(bool save);
        void button_page(bool next);
        bool apply_changed_configs();
        void cancel_values();
        void toggle_resource(e_resource resource);
        int config_change_basic(feature_t &alias, const xstring feature);
        int config_change_string_language(const game_language &lang);
        void init(std::function<void()> callback);

        static void show(std::function<void()> callback);
    };
}