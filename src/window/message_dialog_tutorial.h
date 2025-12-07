 #pragma once

#include "message_dialog_new.h"

namespace ui {
    struct message_dialog_tutorial : public message_dialog_base {
        message_dialog_tutorial() : message_dialog_base("message_dialog_window_tutorial") {}
        virtual int handle_mouse(const mouse *m) override;
        virtual void draw_foreground(UiFlags flags) override;
        virtual void draw_city_message_text(const lang_message& msg) override;
    };
}

