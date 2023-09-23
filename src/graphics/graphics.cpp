#include "graphics/graphics.h"

#include "core/profiler.h"
#include "platform/renderer.h"

void graphics_clear_screen() {
    OZZY_PROFILER_SECTION("Render/Frame/Clear Screen");
    graphics_renderer()->clear_screen();
}