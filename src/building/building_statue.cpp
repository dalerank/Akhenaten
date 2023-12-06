#include "building_statue.h"

#include "building/building.h"
#include "city/object_info.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/boilerplate.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "sound/sound_building.h"
#include "core/svector.h"

#include "js/js_game.h"

void building_statue_draw_info(object_info &c) {
    c.help_id = 79;
    window_building_play_sound(&c, snd::get_building_info_sound("statue"));
    outer_panel_draw(c.offset, c.width_blocks, c.height_blocks);
    lang_text_draw_centered(80, 0, c.offset.x, c.offset.y + 10, 16 * c.width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    window_building_draw_description_at(c, 16 * c.height_blocks - 158, 80, 1);
}

svector<image_desc, 10> small_statues_img;
svector<image_desc, 10> medium_statue_images;
svector<image_desc, 10> big_statues_img;

ANK_REGISTER_CONFIG_ITERATOR(config_load_small_statue_images);
ANK_REGISTER_CONFIG_ITERATOR(config_load_medium_statue_images);
ANK_REGISTER_CONFIG_ITERATOR(config_load_big_statue_images);

template<typename T>
void config_load_statue_images_t(archive arch, pcstr key, T& config) {
    config.clear();
    arch.load_global_array(key, [&] (archive arch) {
        int pack = arch.read_integer("pack");
        int id = arch.read_integer("id");
        int offset = arch.read_integer("offset");
        config.push_back({pack, id, offset});
    });
}

void config_load_small_statue_images(archive arch) {
    config_load_statue_images_t(arch, "small_statue_images", small_statues_img);
}

void config_load_medium_statue_images(archive arch) {
    config_load_statue_images_t(arch, "medium_statue_images", medium_statue_images);
}

void config_load_big_statue_images(archive arch) {
    config_load_statue_images_t(arch, "big_statue_images", big_statues_img);
}

int building_statue_random_variant(int type, int variant) {
    int size = 1;
    switch (type) {
    case BUILDING_SMALL_STATUE: size = small_statues_img.size(); break;
    case BUILDING_MEDIUM_STATUE: size = medium_statue_images.size(); break;
    case BUILDING_LARGE_STATUE: size = big_statues_img.size(); break;
    }

    return rand() % size;
}

int building_statue_next_variant(int type, int variant) {
    if (variant < 0) {
        return 0;
    }

    int size = 0;
    switch (type) {
    case BUILDING_SMALL_STATUE: size = small_statues_img.size(); break;
    case BUILDING_MEDIUM_STATUE: size = medium_statue_images.size(); break;
    case BUILDING_LARGE_STATUE: size = big_statues_img.size(); break;
    }

    if (!size) {
        return variant;
    }

    variant = (variant + 1) % size;
    return variant;
}

int building_statue_get_image(int type, int orientation, int variant) {
    int image_id = 0;

    while (orientation < 0)
        orientation += 4;
    while (orientation > 3)
        orientation -= 4;
    while (variant < 0)
        variant += 4;
    while (variant > 3)
        variant -= 4;

    switch (type) {
    case BUILDING_SMALL_STATUE:
        variant %= small_statues_img.size();
        return image_id_from_group(small_statues_img[variant]);

    case BUILDING_MEDIUM_STATUE:
        variant %= medium_statue_images.size();
        return image_id_from_group(medium_statue_images[variant]);

    case BUILDING_LARGE_STATUE:
        variant %= big_statues_img.size();
        return image_id_from_group(big_statues_img[variant]);
    }

    return image_id;
}

int building_statue_get_image_from_value(int type, int combined, int variant, int map_orientation) {
    int orientation = combined % 4 - (map_orientation / 2);
    return building_statue_get_image(type, orientation - 1, variant);
}
