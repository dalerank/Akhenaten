#pragma once

#include "graphics/elements/ui.h"

#include <array>

enum e_instr {
    INSTR_STORAGE_YARD = 0,
    INSTR_GRANARY = 1,
    INSTR_DOCK = 2,
    INSTR_OTHERS = 3,
    INSTR_MARKET = 4,
};

struct object_info;
struct storage_t;


std::pair<bstring64, e_font> window_building_get_order_instruction(int instr_kind, const storage_t &storage, e_resource resource);
std::pair<bstring64, e_font> window_dock_get_order_instruction(int instr_kind, e_resource resource, int dock_order);
