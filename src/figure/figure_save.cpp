#include "figure/figure_save.h"

#include "figure/figure.h"

static save_layout_registration<figure_save> g_figure_save_layout;

void figure_save::bind_current(figure& f, io_buffer* iob) {
    f.bind(iob);
}

figure_save::legacy_action_numbers figure_save::read(figure& f, io_buffer* iob, save_layout_tag<1>) {
    f.bind(iob);
    return {};
}

static void remap_range(short& action, int first, int last) {
    if (action >= first && action <= last) {
        action -= first;
    }
}

void figure_save::apply(figure& f, const legacy_action_numbers&) {
    switch (f.type) {
    case FIGURE_JUGGLER:
    case FIGURE_MUSICIAN:
    case FIGURE_DANCER:
    case FIGURE_SENET_PLAYER:
        if (f.action_state == 13) {
            f.action_state = 7;
        }
        remap_range(f.action_state, 90, 96);
        break;
    case FIGURE_FIREMAN:
        remap_range(f.action_state, 70, 77);
        break;
    case FIGURE_FISHING_BOAT:
        remap_range(f.action_state, 190, 198);
        break;
    case FIGURE_FERRY_BOAT:
        remap_range(f.action_state, 200, 204);
        break;
    case FIGURE_ARCHER:
    case FIGURE_INFANTRY:
    case FIGURE_FCHARIOTEER:
        remap_range(f.action_state, 80, 91);
        break;
    default:
        break;
    }
}
