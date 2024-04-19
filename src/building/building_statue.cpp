#include "building_statue.h"

#include "building/building.h"
#include "building/rotation.h"
#include "city/object_info.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "sound/sound_building.h"
#include "core/svector.h"
#include "grid/terrain.h"
#include "grid/building_tiles.h"

#include "js/js_game.h"

namespace model {
    struct small_statue_t {
        std::vector<image_desc> var;
    };
    small_statue_t small_statue;

    struct medium_statue_t {
        std::vector<image_desc> var;
    };
    medium_statue_t medium_statue;

    struct big_statue_t {
        std::vector<image_desc> var;
    };
    big_statue_t big_statue;

    template<typename T>
    void config_load_statue(pcstr key, T& model) {
        model.var.clear();
        g_config_arch.r_section(key, [&model] (archive model_arch) {
            model_arch.r_array("variants", [&model] (archive arch) {
                int pack = arch.r_int("pack");
                int id = arch.r_int("id");
                int offset = arch.r_int("offset");
                model.var.push_back({pack, id, offset});
            });
        });
    }
}

ANK_REGISTER_CONFIG_ITERATOR(config_load_statue_models);
void config_load_statue_models() {
    model::config_load_statue(building_small_statue::CLSID, model::small_statue);
    model::config_load_statue(building_medium_statue::CLSID, model::medium_statue);
    model::config_load_statue(building_large_statue::CLSID, model::big_statue);
}

void building_statue::on_create(int o) {
    int orientation = (4 + building_rotation_global_rotation() + city_view_orientation() / 2) % 4;
    data.monuments.variant = building_rotation_get_building_variant();
    data.monuments.statue_offset = rand() % 4;
}

void building_statue::on_place(int orientation, int variant) {
    int orientation_rel = city_view_relative_orientation(orientation);
    int image_id = get_image(type(), orientation_rel, variant);
    map_building_tiles_add(id(), tile(), size(), image_id, TERRAIN_BUILDING);
}

void building_statue::window_info_background(object_info &c) {
    c.help_id = 79;
    window_building_play_sound(&c, snd::get_building_info_sound("statue"));
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(80, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    window_building_draw_description_at(c, 16 * c.bgsize.y - 158, 80, 1);
}

int building_statue_get_variant_size(int type) {
    switch (type) {
    case BUILDING_SMALL_STATUE: return model::small_statue.var.size(); break;
    case BUILDING_MEDIUM_STATUE: return model::medium_statue.var.size(); break;
    case BUILDING_LARGE_STATUE: return model::big_statue.var.size(); break;
    }

    return 0;
}

int building_statue_random_variant(int type, int variant) {
    int size = building_statue_get_variant_size(type);
    return rand() % size;
}

int building_statue_next_variant(int type, int variant) {
    if (variant < 0) {
        return 0;
    }

    int size = building_statue_get_variant_size(type);
    if (!size) {
        return variant;
    }

    variant = (variant + 1) % size;
    return variant;
}

int building_statue::get_image(int type, int orientation, int variant) {
    int image_id = 0;

    int size = building_statue_get_variant_size(type);

    if (!size) {
        return 0;
    }
    //
    while (orientation < 0) { orientation += 4; }
    //
    while (orientation > 3) { orientation -= 4; }

    while (variant < 0) { variant += 4; }

    while (variant > (size - 1)) { variant -= size; }

    switch (type) {
    case BUILDING_SMALL_STATUE:
        variant %= size;
        return image_group(model::small_statue.var[variant]);

    case BUILDING_MEDIUM_STATUE:
        variant %= size;
        return image_group(model::medium_statue.var[variant]);

    case BUILDING_LARGE_STATUE:
        variant %= size;
        return image_group(model::big_statue.var[variant]);
    }

    return image_id;
}

int building_statue::get_image_from_value(int type, int combined, int variant, int map_orientation) {
    int orientation = combined % 4 - (map_orientation / 2);
    return get_image(type, orientation - 1, variant);
}
