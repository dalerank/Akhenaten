#include "building_plaza.h"

#include "building/building.h"
#include "building/count.h"
#include "city/object_info.h"
#include "city/labor.h"
#include "city/warnings.h"
#include "grid/road_access.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/view/view.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"
#include "game/game.h"
#include "building_shrine.h"

buildings::model_t<building_shrine_osiris> shrine_osiris_m;
buildings::model_t<building_shrine_ra>   shrine_ra_m;
buildings::model_t<building_shrine_ptah> shrine_ptah_m;
buildings::model_t<building_shrine_seth> shrine_seth_m;
buildings::model_t<building_shrine_bast> shrine_bast_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_shrines);
void config_load_building_shrines() {
    shrine_osiris_m.load();
    shrine_ra_m.load();
    shrine_ptah_m.load();
    shrine_seth_m.load();
    shrine_bast_m.load();
}

void building_shrine_draw_info(object_info& c, int image_offset) {
    building *b = building_get(c.building_id);
    const auto &params = b->dcast()->params();

    c.help_id = params.meta.help_id;
    int group_id = params.meta.text_id;

    painter ctx = game.painter();

    window_building_play_sound(&c, b->get_sound());
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(161, group_id, c.offset.x, c.offset.y + 12, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);

    if (c.has_road_access) {
        ImageDraw::img_generic(ctx, image_offset + image_id_from_group(PACK_UNLOADED, 21), c.offset.x + 190, c.offset.y + 16 * c.bgsize.y - 148);
    } else {
        window_building_draw_description_at(c, 16 * c.bgsize.y - 128, 69, 25);
    }
}

void building_shrine::on_place_checks() {
    if (!map_has_road_access(tile(), 2)) {
        building_construction_warning_show(WARNING_ROAD_ACCESS_NEEDED);
    }
}

e_overlay building_shrine::get_overlay() const {
    switch (type()) {
    case BUILDING_SHRINE_OSIRIS: return OVERLAY_RELIGION_OSIRIS;
    case BUILDING_SHRINE_RA:   return OVERLAY_RELIGION_RA;
    case BUILDING_SHRINE_PTAH: return OVERLAY_RELIGION_PTAH;
    case BUILDING_SHRINE_SETH: return OVERLAY_RELIGION_SETH;
    case BUILDING_SHRINE_BAST: return OVERLAY_RELIGION_BAST;
    }

    return OVERLAY_NONE;
}

void building_shrine::window_info_background(object_info &ctx) {
    switch (base.type) {
    case BUILDING_SHRINE_OSIRIS:
        building_shrine_draw_info(ctx, 21);
        break;
    case BUILDING_SHRINE_RA:
        building_shrine_draw_info(ctx, 22);
        break;
    case BUILDING_SHRINE_PTAH:
        building_shrine_draw_info(ctx, 23);
        break;
    case BUILDING_SHRINE_SETH:
        building_shrine_draw_info(ctx, 24);
        break;
    case BUILDING_SHRINE_BAST:
        building_shrine_draw_info(ctx, 25);
        break;
    }
}
