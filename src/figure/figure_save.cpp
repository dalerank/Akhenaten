#include "figure/figure_save.h"

#include "figure/figure.h"

static save_layout_registration<figure_save> g_figure_save_layout;

void figure_save::bind_current(figure& f, io_buffer* iob) {
    f.bind(iob);
}
