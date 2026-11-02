#pragma once

#include "figure/figure.h"
#include "figure/figure_impl.h"

// Flag numbers are the original editor's (figure_create_editor_flags / figure_editor_flag_action).
enum {
    MAP_FLAG_EARTHQUAKE = 1,
    MAP_FLAG_ENTRY = 2,
    MAP_FLAG_EXIT = 3,
    MAP_FLAG_RIVER_ENTRY = 0x0C,
    MAP_FLAG_RIVER_EXIT = 0x0D,
    MAP_FLAG_FISHING_MIN = 0x0E,
    MAP_FLAG_FISHING_MAX = 0x16,
    MAP_FLAG_PREDATOR_HERD_MIN = 0x16,
    MAP_FLAG_PREDATOR_HERD_MAX = 0x1A,
    MAP_FLAG_PREY_HERD_MIN = 0x1A,
    MAP_FLAG_PREY_HERD_MAX = 0x1E,
    MAP_FLAG_DISEMBARK_MIN = 0x1E,
    MAP_FLAG_DISEMBARK_MAX = 0x21,
    MAP_FLAG_INVASION_MIN = 0x32,
    MAP_FLAG_INVASION_LAND_MAX = 0x3A,
    MAP_FLAG_INVASION_MAX = 0x42,

    MAP_FLAG_FRAMES = 8,
};

int map_flag_number(int flag);

class figure_map_flag : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_MAP_FLAG, figure_map_flag)
    figure_map_flag(figure *f) : figure_impl(f) {}

    virtual void figure_action() override;
    virtual void update_animation() override {}
};

void figure_create_editor_flags(void);
