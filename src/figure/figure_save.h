#pragma once

#include "io/save_layout.h"

class figure;

struct figure_save {
    using object = figure;
    static constexpr const char* name = "figure";
    static constexpr uint16_t current = 2;
    static constexpr uint16_t oldest = 2;

    static void bind_current(figure& f, io_buffer* iob);
};
