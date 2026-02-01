#pragma once

#include "window_building_info.h"
#include "core/xstring.h"

#include <memory>

// Dynamic window registered from JavaScript
struct js_building_info_window : public building_info_window {
    xstring window_name;
    xstring init_event_name;

    virtual pcstr section() const override { return window_name.c_str(); }
    virtual void init(object_info &c) override;
};

// Global registry for dynamically created windows
class js_window_registry {
public:
    static js_window_registry& instance();

    void register_building_info_window(const xstring &name, const xstring &event_name);
    void clear();

private:
    hvector<std::unique_ptr<js_building_info_window>, 32> windows;
};

// Wrapper functions for use from js_game.cpp
void js_window_registry_clear();
void js_register_building_info_window(const xstring &name, const xstring &event_name);
