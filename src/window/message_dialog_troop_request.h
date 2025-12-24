#pragma once

#include "message_dialog_new.h"

namespace ui {
    struct message_dialog_troop_request : public message_dialog_base {
        message_dialog_troop_request() : message_dialog_base("message_dialog_window_troop_request"), background_img(0) {}
        virtual int handle_mouse(const mouse *m) override;
        virtual void draw_foreground(UiFlags flags) override;
        virtual void draw_background_content() override;
        virtual void init_data(xstring text_id, int message_id, void (*background_callback)(void)) override;
        virtual void draw_city_message_text(const lang_message& msg) override;
        
        uint16_t background_img;
    };
}

