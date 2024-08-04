#include "figures.h"
#include <graphics/view/lookup.h>

#include "building/building.h"
#include "empire/empire_city.h"
#include "figure/figure.h"
#include "figure/formation.h"
#include "figure/figure_phrase.h"
#include "figure/trader.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "graphics/view/view.h"
#include "graphics/window.h"
#include "config/config.h"
#include "scenario/scenario.h"
#include "widget/widget_city.h"
#include "dev/debug.h"
#include "game/game.h"

static void window_info_select_figure(int index, int param2);

static const int FIGURE_TYPE_TO_BIG_FIGURE_IMAGE[] = {
     8,  13, 13, 9,  4,  13, 8,  16, 7,  4, 18, 42, 26, 41, 8,  1,  33, 10, 11, 25, 8,  25, 15, 15, 15,
     60, 12, 14, 5,  52, 52, 2,  3,  6,  6, 13, 8,  8,  17, 12, 58, 21, 50, 8,  8,  8,  28, 30, 23, 8,
     8,  8,  34, 39, 33, 43, 27, 48, 63, 8, 8,  8,  8,  8,  53, 8,  38, 62, 54, 55, 56, 8,  8
};

int big_people_image(e_figure_type type) {
    int result = 0;
    int index = type;
    result = image_id_from_group(GROUP_PORTRAITS) + type;
    return result;
}

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

int name_group_id() { // TODO
    return 254;
}

void figure::draw_enemy(object_info* c) {
    painter ctx = game.painter();
    int image_id = FIGURE_TYPE_TO_BIG_FIGURE_IMAGE[type];
    int enemy_type = formation_get(formation_id)->enemy_type;
    switch (type) {
    case FIGURE_ENEMY43_SPEAR:
        switch (enemy_type) {
        case ENEMY_5_PERGAMUM:
            image_id = 44;
            break;
        case ENEMY_6_SELEUCID:
            image_id = 46;
            break;
        case ENEMY_7_ETRUSCAN:
            image_id = 32;
            break;
        case ENEMY_8_GREEK:
            image_id = 36;
            break;
        }
        break;
    case FIGURE_ENEMY44_SWORD:
        switch (enemy_type) {
        case ENEMY_5_PERGAMUM:
            image_id = 45;
            break;
        case ENEMY_6_SELEUCID:
            image_id = 47;
            break;
        case ENEMY_9_EGYPTIAN:
            image_id = 29;
            break;
        }
        break;
    case FIGURE_ENEMY45_SWORD:
        switch (enemy_type) {
        case ENEMY_7_ETRUSCAN:
            image_id = 31;
            break;
        case ENEMY_8_GREEK:
            image_id = 37;
            break;
        case ENEMY_10_CARTHAGINIAN:
            image_id = 22;
            break;
        }
        break;
    case FIGURE_ENEMY49_FAST_SWORD:
        switch (enemy_type) {
        case ENEMY_0_BARBARIAN:
            image_id = 21;
            break;
        case ENEMY_1_NUMIDIAN:
            image_id = 20;
            break;
        case ENEMY_4_GOTH:
            image_id = 35;
            break;
        }
        break;
    case FIGURE_ENEMY50_SWORD:
        switch (enemy_type) {
        case ENEMY_2_GAUL:
            image_id = 40;
            break;
        case ENEMY_3_CELT:
            image_id = 24;
            break;
        }
        break;
    case FIGURE_ENEMY51_SPEAR:
        switch (enemy_type) {
        case ENEMY_1_NUMIDIAN:
            image_id = 20;
            break;
        }
        break;
    }
    ImageDraw::img_generic(ctx, image_id_from_group(GROUP_PORTRAITS) + image_id - 1, c->offset + vec2i{28, 112});

    lang_text_draw(name_group_id(), name, c->offset.x + 90, c->offset.y + 108, FONT_LARGE_BLACK_ON_DARK);
    lang_text_draw(37, scenario_property_enemy() + 20, c->offset.x + 92, c->offset.y + 149, FONT_NORMAL_BLACK_ON_DARK);
}

void figure::draw_animal(object_info* c) {
    painter ctx = game.painter();
    ImageDraw::img_generic(ctx, big_people_image(type), c->offset + vec2i{28, 112});
    lang_text_draw(64, type, c->offset.x + 92, c->offset.y + 139, FONT_NORMAL_BLACK_ON_DARK);
}

void figure::draw_normal_figure(object_info* c) {
    painter ctx = game.painter();
    int image_id = big_people_image(type);
    if (action_state == FIGURE_ACTION_74_FIREMAN_GOING_TO_FIRE || action_state == FIGURE_ACTION_75_FIREMAN_AT_FIRE) {
        image_id = image_id_from_group(GROUP_PORTRAITS) + 18;
    }

    ImageDraw::img_generic(ctx, image_id, c->offset + vec2i{28, 112});

    lang_text_draw(name_group_id(), name, c->offset.x + 90, c->offset.y + 108, FONT_LARGE_BLACK_ON_DARK);
    lang_text_draw(64, type, c->offset.x + 92, c->offset.y + 139, FONT_NORMAL_BLACK_ON_DARK);

    if (c->figure.phrase_group > 0 && c->figure.phrase_id >= 0) {
        lang_text_draw_multiline(c->figure.phrase_group, c->figure.phrase_id, c->offset + vec2i{90, 160}, 16 * (c->bgsize.x - 8), FONT_NORMAL_BLACK_ON_DARK);
    }
}