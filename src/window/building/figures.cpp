#include "figures.h"
#include <graphics/view/lookup.h>

#include "building/building.h"
#include "empire/empire_city.h"
#include "figure/figure.h"
#include "figure/formation.h"
#include "figure/figure_phrase.h"
#include "empire/trader_handler.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "graphics/view/view.h"
#include "graphics/window.h"
#include "game/game_config.h"
#include "scenario/scenario.h"
#include "widget/widget_city.h"
#include "dev/debug.h"
#include "game/game.h"

int inventory_to_resource_id(int value) {
    switch (value) {
    case 0:
        return RESOURCE_GRAIN;
    case 1:
        return RESOURCE_MEAT;
    case 2:
        return RESOURCE_LETTUCE;
    case 3:
        return RESOURCE_FIGS;
    case INVENTORY_GOOD4:
        return RESOURCE_BEER;
    case INVENTORY_GOOD3:
        return RESOURCE_MEAT;
    case INVENTORY_GOOD2:
        return RESOURCE_LUXURY_GOODS;
    case INVENTORY_GOOD1:
        return RESOURCE_POTTERY;
    default:
        return RESOURCE_NONE;
    }
}