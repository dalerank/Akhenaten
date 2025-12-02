#pragma once

#include "message_dialog_new.h"

namespace ui {
    struct message_dialog_imperial : public message_dialog_base {
        message_dialog_imperial() : message_dialog_base("message_dialog_window_imperial") {}
        virtual int handle_mouse(const mouse *m) override;
        virtual void draw_foreground(UiFlags flags) override;
        virtual void draw_city_message_text(const lang_message& msg) override;
        virtual void draw_background_image() override;
        virtual void draw_background_video() override;
    };
}

