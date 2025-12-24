#pragma once

#include "graphics/animation.h"
#include "message_dialog_new.h"

namespace ui {

    struct message_dialog_god : public message_dialog_base {
        message_dialog_god() : message_dialog_base("message_dialog_window_god"), god(GOD_UNKNOWN) {}
        virtual int handle_mouse(const mouse *m) override;
        virtual void draw_foreground(UiFlags flags) override;
        virtual void draw_city_message_text(const lang_message& msg) override;
        virtual void init_data(xstring text_id, int message_id, void (*background_callback)(void)) override;
        virtual void archive_load(archive arch) override;
        
        e_god god;
        uint16_t background_img;
        animations_t god_images;
    };
}

