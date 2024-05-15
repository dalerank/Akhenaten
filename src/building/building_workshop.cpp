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

void building_flax_workshop_draw_info(object_info& c) {
    e_resource input_resource = RESOURCE_FLAX;
    e_resource output_resource = RESOURCE_LINEN;
    building_workshop_draw_background(c, 97, "flax_workshop", 123, output_resource, input_resource);
}

void building_luxury_workshop_draw_info(object_info& c) {
    e_resource input_resource = RESOURCE_GEMS;
    e_resource output_resource = RESOURCE_LUXURY_GOODS;

    building_workshop_draw_background(c, 99, "luxury_workshop", 125, output_resource, input_resource);
}

void building_workshop_draw_raw_material_storage(painter &ctx, const building* b, vec2i pos, color color_mask) {
    int amount = ceil((float)b->stored_amount() / 100.0) - 1;
    int amount2 = 0;
    switch (b->type) {
        case BUILDING_HUNTING_LODGE:
        if (amount >= 0) {
            ImageDraw::img_generic(ctx, image_group(IMG_RESOURCE_GAMEMEAT) + amount, pos + vec2i{61, 14}, color_mask);
        }
        break;

    case BUILDING_WEAPONSMITH:
        amount = std::min<int>(2, ceil((float)b->stored_amount() / 100.0) - 1);
        if (amount >= 0) {
            ImageDraw::img_generic(ctx, image_id_from_group(GROUP_RESOURCE_STOCK_COPPER_2) + amount, pos + vec2i{61, 14}, color_mask);
        }
        break;

    case BUILDING_BREWERY_WORKSHOP:
        amount = std::min<int>(2, ceil((float)b->stored_amount() / 100.0) - 1);
        if (amount >= 0) {
            ImageDraw::img_generic(ctx, image_id_from_group(GROUP_RESOURCE_STOCK_BARLEY_2) + amount, pos + vec2i{65, 3}, color_mask);
        }
        break;

    case BUILDING_PAPYRUS_WORKSHOP:
        amount = std::min<int>(2, ceil((float)b->stored_amount() / 100.0) - 1);
        if (amount >= 0) {
            ImageDraw::img_generic(ctx, image_id_from_group(GROUP_RESOURCE_STOCK_REEDS_5) + amount, pos + vec2i{35, 4}, color_mask);
        }
        break;

    case BUILDING_WOOD_CUTTERS:
        if (amount >= 0) {
            ImageDraw::img_generic(ctx, image_id_from_group(GROUP_RESOURCE_STOCK_WOOD_5) + amount, pos + vec2i{65, 3}, color_mask);
        }
        break;

    case BUILDING_WEAVER_WORKSHOP:
        //            ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_STOCK_FLAX_2) + amount, x + 65, y + 3,
        //            color_mask);
        break;

    case BUILDING_JEWELS_WORKSHOP:
        //            ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_STOCK_GEMS_2) + amount, x + 65, y + 3,
        //            color_mask);
        break;

    case BUILDING_SHIPWRIGHT:
        //            ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_STOCK_WOOD_5) + amount, x + 65, y + 3,
        //            color_mask);
        break;

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
