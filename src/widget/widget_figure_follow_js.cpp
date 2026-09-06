#include "widget_figure_follow.h"

#include "js/js_game.h"

bool __figure_follow_start(int figure_id) {
    return g_figure_follow.start(figure_id);
}
ANK_FUNCTION_1(__figure_follow_start)

void __figure_follow_stop() {
    g_figure_follow.stop();
}
ANK_FUNCTION(__figure_follow_stop)

bool __figure_follow_enabled() {
    return g_figure_follow.enabled();
}
ANK_FUNCTION(__figure_follow_enabled)

int __figure_follow_texture_id() {
    return g_figure_follow.texture_id();
}
ANK_FUNCTION(__figure_follow_texture_id)

int __figure_follow_figure_id() {
    return g_figure_follow.figure_id();
}
ANK_FUNCTION(__figure_follow_figure_id)

void __figure_follow_capture_if_due() {
    g_figure_follow.capture_if_due();
}
ANK_FUNCTION(__figure_follow_capture_if_due)
