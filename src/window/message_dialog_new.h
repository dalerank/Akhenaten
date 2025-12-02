#pragma once

#include "autoconfig_window.h"
#include "core/xstring.h"
#include "core/bstring.h"
#include "graphics/elements/rich_text.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/image_button.h"
#include "io/gamefiles/lang.h"
#include "city/constants.h"
#include "scenario/scenario.h"
#include "game/gods.h"
#include "core/vec2i.h"

struct text_tag_substitution {
    xstring tag;
    xstring content;
};

namespace ui {
    // Base class with common functionality
    struct message_dialog_base : public autoconfig_window {
        message_dialog_base(pcstr config_name);
        
        virtual int handle_mouse(const mouse *m) override = 0;
        virtual int get_tooltip_text() override { return 0; }
        virtual void draw_foreground(UiFlags flags) override = 0;
        virtual int draw_background(UiFlags flags) override;
        virtual void ui_draw_foreground(UiFlags flags) override {}
        virtual int ui_handle_mouse(const mouse *m) override;
        virtual void init() override;

        void show(xstring text_id, int message_id, void (*background_callback)(void));
        void show_city_message(xstring text_id, int message_id, int year, int month, int param1, int param2, int message_advisor, bool use_popup);
        void setup_help_id(xstring helpid);

        struct history_item {
            int text_id;
            int scroll_position;
        };
        
        static const int MAX_HISTORY = 200;
        history_item history[MAX_HISTORY];
        int num_history;

        uint16_t text_id;
        int message_id;
        bool is_eventmsg;
        pcstr title_text;
        bstring1024 body_text;
        bstring256 phrase_text;
        pcstr body_template;
        pcstr phrase_template;

        void (*background_callback)();
        bool show_video;
        bool background;
        uint16_t background_img;
        e_god god;

        vec2i pos;
        int x_text;
        int y_text;
        int text_height_blocks;
        int text_width_blocks;
        int focus_button_id;
        xstring help_id;
        rich_text_t rich_text;

        struct player_message {
            int year;
            int month;
            int param1;
            int param2;
            int message_advisor;
            bool use_popup;
        } player_msg;

        void init_data(xstring text_id, int message_id, void (*background_callback)(void));
        void set_city_message(int year, int month, int param1, int param2, int message_advisor, bool use_popup);
        void eventmsg_template_combine(pcstr template_ptr, pstr out_ptr, bool phrase_modifier);
        void cleanup();
        
        virtual void draw_background_normal();
        virtual void draw_background_image();
        virtual void draw_background_video();
        virtual void draw_foreground_normal();
        virtual void draw_foreground_image();
        virtual void draw_foreground_video();
        
        void draw_title(const lang_message& msg);
        void draw_subtitle(const lang_message& msg);
        virtual void draw_content(const lang_message& msg);
        virtual void draw_city_message_text(const lang_message& msg);
        
        virtual bool handle_input_normal(const mouse* m_dialog, const lang_message& msg);
        bool handle_input_video(const mouse* m_dialog, const lang_message& msg);
        bool handle_input_godmsg(const mouse* m_dialog, const lang_message& msg);
        
        void button_back();
        void button_close();
        void button_help();
        void button_advisor(int advisor);
        void button_go_to_problem();
        
        int resource_image(int resource);
        int is_problem_message(const lang_message& msg);
        int get_message_image_id(const lang_message& msg);
        image_button* get_advisor_button();
        
        virtual pcstr get_section() const override;
    protected:
        xstring config_name;
    };

    // Derived classes for each message type
    struct message_dialog_general : public message_dialog_base {
        message_dialog_general() : message_dialog_base("message_dialog_window_general") {}
        virtual int handle_mouse(const mouse *m) override;
        virtual void draw_foreground(UiFlags flags) override;
    };

    struct message_dialog_disaster : public message_dialog_base {
        message_dialog_disaster() : message_dialog_base("message_dialog_window_disaster") {}
        virtual int handle_mouse(const mouse *m) override;
        virtual void draw_foreground(UiFlags flags) override;
        virtual void draw_city_message_text(const lang_message& msg) override;
    };

    struct message_dialog_imperial : public message_dialog_base {
        message_dialog_imperial() : message_dialog_base("message_dialog_window_imperial") {}
        virtual int handle_mouse(const mouse *m) override;
        virtual void draw_foreground(UiFlags flags) override;
        virtual void draw_city_message_text(const lang_message& msg) override;
    };

    struct message_dialog_emigration : public message_dialog_base {
        message_dialog_emigration() : message_dialog_base("message_dialog_window_emigration") {}
        virtual int handle_mouse(const mouse *m) override;
        virtual void draw_foreground(UiFlags flags) override;
        virtual void draw_city_message_text(const lang_message& msg) override;
    };

    struct message_dialog_tutorial : public message_dialog_base {
        message_dialog_tutorial() : message_dialog_base("message_dialog_window_tutorial") {}
        virtual int handle_mouse(const mouse *m) override;
        virtual void draw_foreground(UiFlags flags) override;
        virtual void draw_city_message_text(const lang_message& msg) override;
    };

    struct message_dialog_trade_change : public message_dialog_base {
        message_dialog_trade_change() : message_dialog_base("message_dialog_window_trade_change") {}
        virtual int handle_mouse(const mouse *m) override;
        virtual void draw_foreground(UiFlags flags) override;
        virtual void draw_city_message_text(const lang_message& msg) override;
    };

    struct message_dialog_price_change : public message_dialog_base {
        message_dialog_price_change() : message_dialog_base("message_dialog_window_price_change") {}
        virtual int handle_mouse(const mouse *m) override;
        virtual void draw_foreground(UiFlags flags) override;
        virtual void draw_city_message_text(const lang_message& msg) override;
    };

    struct message_dialog_invasion : public message_dialog_base {
        message_dialog_invasion() : message_dialog_base("message_dialog_window_invasion") {}
        virtual int handle_mouse(const mouse *m) override;
        virtual void draw_foreground(UiFlags flags) override;
        virtual void draw_city_message_text(const lang_message& msg) override;
    };
}

void window_message_dialog_show(xstring text_id, int message_id, void (*background_callback)(void));
void window_message_dialog_show_city_message(xstring text_id, int message_id, int year, int month, int param1, int param2, int message_advisor, bool use_popup);
void window_message_setup_help_id(xstring helpid);
void window_show_help();
void text_fill_in_tags(pcstr src, pstr dst, text_tag_substitution* tag_templates, int num_tags);

