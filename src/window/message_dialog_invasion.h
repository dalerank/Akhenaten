#pragma once

#include "message_dialog_new.h"

namespace ui {
    struct message_dialog_invasion : public message_dialog_base {
        message_dialog_invasion() : message_dialog_base("message_dialog_window_invasion") {}
        virtual int handle_mouse(const mouse *m) override;
        virtual void draw_foreground(UiFlags flags) override;
        virtual void draw_city_message_text(const lang_message& msg) override;
        virtual void init() override;
        
        void button_go_to_problem();
    };
}

