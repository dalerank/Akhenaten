#pragma once

#include <cstdint>

#include "core/vec2i.h"

#include "graphics/elements/generic_button.h"
#include "graphics/elements/image_button.h"
#include "graphics/image_groups.h"

struct mouse;

enum UiFlags_ {
    UiFlags_None = 0,
    UiFlags_LabelCentered = 1 << 1,
    UiFlags_PanelOuter = 1 << 2,
};

namespace ui {

void begin_widget(vec2i offset);
void end_widget();
bool handle_mouse(const mouse *m);

}