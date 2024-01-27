#pragma once

#include <cstdint>

#include "core/vec2i.h"

#include "graphics/elements/generic_button.h"
#include "graphics/elements/image_button.h"
#include "graphics/image_groups.h"

struct mouse;

enum UiFlags_ {
    UiFlags_LabelCentered = 1 << 1,
    UiFlags_PanelOuter = 1 << 2,
};

namespace ui {

void begin_window(vec2i offset);
bool handle_mouse(const mouse *m);

}