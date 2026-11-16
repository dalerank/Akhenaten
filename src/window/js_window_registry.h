#pragma once

#include "window_building_info.h"
#include "window/window_figure_info.h"
#include "window/window_terrain_info.h"
#include "window/window_advisors.h"
#include "window/autoconfig_window.h"
#include "city/constants.h"
#include "core/xstring.h"

#include <memory>
#include <vector>

// Dynamic window registered from JavaScript
struct js_building_info_window : public building_info_window {
    xstring window_name;

    virtual xstring section() const override { return window_name; }
    virtual void init(object_info &c) override;
};

struct js_figure_info_window : public figure_info_window {
    xstring window_name;

    virtual xstring section() const override { return window_name; }
};

struct js_terrain_info_window : public terrain_info_window {
    xstring window_name;

    virtual xstring section() const override { return window_name; }
};

struct mouse;

// Dynamic advisor window registered from JavaScript
struct js_advisor_window : public advisor_window {
    xstring window_name;
    e_advisor advisor = ADVISOR_NONE;

    js_advisor_window(xstring name) : advisor_window(name), window_name(name) {}
    virtual xstring section() const override { return window_name; }
    virtual void archive_load(archive arch) override {
        advisor_window::archive_load(arch);
        advisor = arch.r_type<e_advisor>("advisor");
    }
    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void draw_foreground(UiFlags flags) override {}
};

// Standalone script window (e.g. dynasty menu) — section name from script, no C++ type
struct js_common_window : public autoconfig_window {
    xstring section_name;

    js_common_window(pcstr name) : autoconfig_window(name), section_name(name) {}
    virtual xstring section() const override { return section_name; }
    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void draw_foreground(UiFlags flags) override {}
};

struct js_common_modal_window : public js_common_window {
    js_common_modal_window(pcstr name) : js_common_window(name) {}
    virtual bool is_modal() const override { return true; }
};

// Global registry for dynamically created windows
class js_window_registry {
public:
    static js_window_registry& instance();

    advisor_window* get_advisor_window(e_advisor adv) const;
};
