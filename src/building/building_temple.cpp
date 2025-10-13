#include "building_temple.h"

#include "building/building.h"
#include "city/object_info.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/view/view.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"
#include "game/game_config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"
#include "graphics/animation.h"
#include "game/game.h"
#include "widget/city/ornaments.h"
#include "window/window_building_info.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_temple_osiris);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_temple_ra);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_temple_ptah);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_temple_seth);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_temple_bast);

e_overlay building_temple::get_overlay() const {
    switch(type()) {
    case BUILDING_TEMPLE_OSIRIS: return OVERLAY_RELIGION_OSIRIS;
    case BUILDING_TEMPLE_RA: return OVERLAY_RELIGION_RA;
    case BUILDING_TEMPLE_PTAH: return OVERLAY_RELIGION_PTAH;
    case BUILDING_TEMPLE_SETH: return OVERLAY_RELIGION_SETH;
    case BUILDING_TEMPLE_BAST: return OVERLAY_RELIGION_BAST;

    default:
        assert(false);
    }

    return OVERLAY_NONE;
}

e_sound_channel_city building_temple::sound_channel() const {
    switch (type()) {
    case BUILDING_TEMPLE_OSIRIS: return SOUND_CHANNEL_CITY_TEMPLE_OSIRIS;
    case BUILDING_TEMPLE_RA: return SOUND_CHANNEL_CITY_TEMPLE_RA;
    case BUILDING_TEMPLE_PTAH: return SOUND_CHANNEL_CITY_TEMPLE_PTAH;
    case BUILDING_TEMPLE_SETH: return SOUND_CHANNEL_CITY_TEMPLE_SETH;
    case BUILDING_TEMPLE_BAST: return SOUND_CHANNEL_CITY_TEMPLE_BAST;

    default:
        assert(false);
    }

    return SOUND_CHANNEL_CITY_NONE;
}

void building_temple::spawn_figure() {
    if (is_main()) {
        common_spawn_roamer(FIGURE_PRIEST, 50, FIGURE_ACTION_125_ROAMING);
    }
}

bool building_temple::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    building_draw_normal_anim(ctx, point, &base, tile, anim("work"), color_mask);

    return true;
}
