#pragma once

struct event_app_center_screen {
    int value;
};
struct event_app_toggle_fullscreen {
    int value;
};
struct event_app_screenshot {
    int value;
};
struct event_app_city_screenshot {
    int value;
};
struct event_request_exit {
    int value;
};
struct event_app_close_requested {
    int reserved = 0;
};
struct event_display_options_apply_resolution {
    int w;
    int h;
};
