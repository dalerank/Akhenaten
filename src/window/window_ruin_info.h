#pragma once

#include "window/window_info.h"
#include "window/window_building_info.h"

struct object_info;

struct ruin_info_window : public common_info_window {
    virtual void init(object_info &c) override;
};

struct info_window_burning_ruin : public building_info_window_t<info_window_burning_ruin> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override;
};