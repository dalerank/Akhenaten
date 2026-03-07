#pragma once

#include "window_building_info.h"
#include "window/window_advisors.h"
#include "city/constants.h"
#include "core/xstring.h"

#include <memory>

// Dynamic window registered from JavaScript
struct js_building_info_window : public building_info_window {
    xstring window_name;

    virtual pcstr section() const override { return window_name.c_str(); }
    virtual void init(object_info &c) override;
};

struct mouse;

// Dynamic advisor window registered from JavaScript
struct js_advisor_window : public advisor_window {
    xstring window_name;

    js_advisor_window(pcstr name);
    virtual pcstr get_section() const override { return window_name.c_str(); }
    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void draw_foreground(UiFlags flags) override {}
};

// Global registry for dynamically created windows
class js_window_registry {
public:
    static js_window_registry& instance();

    void register_building_info_window(const xstring &name);
    void register_advisor_window(const xstring &name);
    advisor_window* get_advisor_window(e_advisor adv) const;
    void clear();

private:
    hvector<std::unique_ptr<js_building_info_window>, 32> windows;
    std::array<std::unique_ptr<js_advisor_window>, 16> advisor_windows;
};
