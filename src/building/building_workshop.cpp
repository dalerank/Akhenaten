#include "building_workshop.h"

#include "building/building.h"
#include "city/object_info.h"
#include "city/resource.h"
#include "core/calc.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/text.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"
#include "game/game.h"

void building_workshop_draw_raw_material_storage(painter &ctx, const building* b, vec2i pos, color color_mask) {
    int amount = ceil((float)b->stored_amount() / 100.0) - 1;
    int amount2 = 0;
    switch (b->type) {

    case BUILDING_CHARIOTS_WORKSHOP:
        //            ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_STOCK_WOOD_5) + amount, x + 65, y + 3,
        //            color_mask);
        break;

    case BUILDING_SENET_MASTER:
        //            ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_STOCK_CHARIOTS_2) + amount, x + 65, y +
        //            3, color_mask);
        break;
    }
}
