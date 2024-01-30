#include "building_entertainment.h"

#include "building/building.h"
#include "city/object_info.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"
#include "widget/city/ornaments.h"

#include "js/js_game.h"

static void building_entertainment_school_draw_info(object_info& c, const char* type, int group_id) {
    c.help_id = 75;
    window_building_play_sound(&c, snd::get_building_info_sound(type));

    outer_panel_draw(c.offset, c.width_blocks, c.height_blocks);
    lang_text_draw_centered(group_id, 0, c.offset.x, c.offset.y + 10, 16 * c.width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    if (!c.has_road_access) {
        window_building_draw_description(c, 69, 25);
    } else if (building_get(c.building_id)->num_workers <= 0) {
        window_building_draw_description(c, group_id, 7);
    } else if (c.worker_percentage >= 100) {
        window_building_draw_description(c, group_id, 2);
    } else if (c.worker_percentage >= 75) {
        window_building_draw_description(c, group_id, 3);
    } else if (c.worker_percentage >= 50) {
        window_building_draw_description(c, group_id, 4);
    } else if (c.worker_percentage >= 25) {
        window_building_draw_description(c, group_id, 5);
    } else {
        window_building_draw_description(c, group_id, 6);
    }
    inner_panel_draw(c.offset.x + 16, c.offset.y + 136, c.width_blocks - 2, 4);
    window_building_draw_employment(&c, 142);
}

void building_juggler_school_draw_info(object_info& c) {
    building_entertainment_school_draw_info(c, "juggler_school", 77);
}

void building_conservatory_draw_info(object_info& c) {
    building_entertainment_school_draw_info(c, "conservatory", 75);
}

void building_dancer_school_draw_info(object_info& c) {
    building_entertainment_school_draw_info(c, "dancer_school", 76);
}

void building_bullfight_school_draw_info(object_info& c) {
    building_entertainment_school_draw_info(c, "bullfight_school", 78);
}

struct anim_t {
    vec2i pos;
    e_image_id base_id;
    e_image_id anim_id;
    int max_frames;

    void load(archive arch, pcstr section) {
        arch.r_section(section, [this] (archive arch) {
           pos.x = arch.r_int("pos_x");
           pos.y = arch.r_int("pos_y");
           base_id = (e_image_id)arch.r_int("base_id");
           anim_id = (e_image_id)arch.r_int("anim_id");
           max_frames = arch.r_int("max_frames");
        });
    }
};

struct building_booth_t {
    anim_t juggler;
} building_booth;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_booth_config);
void config_load_building_booth_config() {
    g_config_arch.r_section("building_booth", [] (archive arch) {
        building_booth.juggler.load(arch, "juggler_anim");
    });
}

struct building_bandstand_t {
    anim_t juggler;
    anim_t musician_sn;
    anim_t musician_we;
} building_bandstand;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_bandstand_config);
void config_load_building_bandstand_config() {
    g_config_arch.r_section("building_bandstand", [] (archive arch) {
        building_bandstand.juggler.load(arch, "juggler_anim");
        building_bandstand.musician_sn.load(arch, "musician_anim_sn");
        building_bandstand.musician_we.load(arch, "musician_anim_we");
    });
}

void building_entertainment_draw_shows_dancers(painter &ctx, building* b, vec2i pixel, color color_mask) {
    building* main = b->main();
    if (main->data.entertainment.days3_or_play) {
        building_draw_normal_anim(ctx, pixel + vec2i{64, 0}, b, b->tile, image_id_from_group(GROUP_DANCERS_SHOW) - 1, color_mask, image_id_from_group(GROUP_BUILDING_PAVILLION));
    }
}

void building_entertainment_draw_show_jugglers(painter &ctx, building* b, vec2i pixel, color color_mask) {
    const anim_t *config = nullptr;

    switch (b->type) {
    case BUILDING_BOOTH:
        config = &building_booth.juggler;
        break;
    case BUILDING_BANDSTAND:
        config = &building_bandstand.juggler;
        break;
    case BUILDING_PAVILLION:
        config = &building_booth.juggler;
        break;
    }
    if (!config) {
        return;
    }

    building* main = b->main();
    if (main->data.entertainment.days1) {
        building_draw_normal_anim(ctx, pixel + config->pos, b, b->tile,
                                  image_group(config->anim_id), color_mask,
                                  image_group(config->base_id),
                                  config->max_frames);
    }
}

void building_entertainment_draw_shows_musicians(painter &ctx, building* b, vec2i pixel, int direction, color color_mask) {
    building* main = b->main();
    if (main->data.entertainment.days2) {
        building* next_tile = b->next();
        switch (direction) {
        case 0:
            building_draw_normal_anim(ctx, pixel + building_bandstand.musician_sn.pos, b, b->tile, 
                                      image_group(building_bandstand.musician_sn.anim_id), color_mask,
                                      image_group(building_bandstand.musician_sn.base_id),
                                      building_bandstand.musician_sn.max_frames);
            break;

        case 1:
            building_draw_normal_anim(ctx, pixel + vec2i{48, 4}, b, b->tile,
                                      image_group(building_bandstand.musician_we.anim_id), color_mask,
                                      image_group(building_bandstand.musician_we.base_id),
                                      building_bandstand.musician_we.max_frames);
            break;
        }
    }
}