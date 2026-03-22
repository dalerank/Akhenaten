#pragma once

#include "window_building_info.h"
#include "window/window_advisors.h"
#include "window/autoconfig_window.h"
#include "city/constants.h"
#include "core/xstring.h"

#include <memory>
#include <vector>

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

    js_advisor_window(xstring name) : advisor_window(name), window_name(name) {}
    virtual xstring get_section() const override { return window_name; }
    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void draw_foreground(UiFlags flags) override {}
};

// Standalone script window (e.g. dynasty menu) — section name from script, no C++ type
struct js_common_window : public autoconfig_window {
    xstring section_name;

    js_common_window(pcstr name) : autoconfig_window(name), section_name(name) {}
    virtual xstring get_section() const override { return section_name; }
    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void draw_foreground(UiFlags flags) override {}
};

// Global registry for dynamically created windows
class js_window_registry {
public:
    static js_window_registry& instance();

    advisor_window* get_advisor_window(e_advisor adv) const;
};
