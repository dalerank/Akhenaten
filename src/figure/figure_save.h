#pragma once

#include "io/save_layout.h"

class figure;

struct figure_save {
    using object = figure;
    static constexpr const char* name = "figure";
    static constexpr uint16_t current = 2;

    struct legacy_action_numbers {};

    static uint16_t layout_of_file(int file_version) { return 1; }
    static void bind_current(figure& f, io_buffer* iob);
    static legacy_action_numbers read(figure& f, io_buffer* iob, save_layout_tag<1>);
    static void apply(figure& f, const legacy_action_numbers&);
};
