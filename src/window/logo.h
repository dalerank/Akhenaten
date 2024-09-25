#pragma once

enum { 
    MESSAGE_NONE = 0,
    MESSAGE_MISSING_PATCH = 1,
    MESSAGE_MISSING_FONTS = 2 
};

void window_logo_show(int show_patch_message);
