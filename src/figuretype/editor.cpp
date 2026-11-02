#include "editor.h"

#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "js/js_game.h"
#include "scenario/editor_map.h"
#include "scenario/map.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_map_flag);

#define GROUP_FIGURE_MAP_FLAG_HERD_ICONS PACK_GENERAL, 127
#define GROUP_FIGURE_MAP_FLAG_SEA_INVASION PACK_GENERAL, 79
#define GROUP_FIGURE_MAP_FLAG_DISEMBARK PACK_GENERAL, 177

static void create_flag(int number) {
    figure *f = figure_create(FIGURE_MAP_FLAG, tile2i(-1, -1), 0);
    f->set_resource((e_resource)number);
}

// OG also creates a fourth flag with no number; it lands on stray scenario bytes, so it is not recreated.
void figure_create_editor_flags() {
    for (int n = MAP_FLAG_EARTHQUAKE; n <= MAP_FLAG_EXIT; n++) {
        create_flag(n);
    }
    for (int n = MAP_FLAG_RIVER_ENTRY; n < MAP_FLAG_DISEMBARK_MAX; n++) {
        create_flag(n);
    }
    for (int n = MAP_FLAG_INVASION_MIN; n < MAP_FLAG_INVASION_MAX; n++) {
        create_flag(n);
    }
}

// OG quirk kept: the river entry flag (0x0C) falls into the 4..0x0C range and shows "9".
int map_flag_number(int flag) {
    if (flag >= 0x04 && flag <= 0x0C) {
        return flag - 0x03;
    }
    if (flag >= MAP_FLAG_FISHING_MIN && flag < MAP_FLAG_FISHING_MAX) {
        return flag - MAP_FLAG_FISHING_MIN + 1;
    }
    if (flag >= MAP_FLAG_PREDATOR_HERD_MIN && flag < MAP_FLAG_PREDATOR_HERD_MAX) {
        return flag - MAP_FLAG_PREDATOR_HERD_MIN + 1;
    }
    if (flag >= MAP_FLAG_PREY_HERD_MIN && flag < MAP_FLAG_PREY_HERD_MAX) {
        return flag - MAP_FLAG_PREY_HERD_MIN + 1;
    }
    if (flag >= MAP_FLAG_DISEMBARK_MIN && flag < MAP_FLAG_DISEMBARK_MAX) {
        return flag - MAP_FLAG_DISEMBARK_MIN + 1;
    }
    if (flag >= MAP_FLAG_INVASION_MIN && flag < MAP_FLAG_INVASION_MAX) {
        return flag - MAP_FLAG_INVASION_MIN + 1;
    }
    return 0;
}

void figure_map_flag::figure_action() {
    base.editor_flag_action();
}

void figure::editor_flag_action() {
    wait_ticks = (wait_ticks + 1) % MAP_FLAG_FRAMES;
    main_image_id = image_id_from_group(GROUP_FIGURE_MAP_FLAG_FLAGS) + wait_ticks;

    map_figure_remove();

    const int id = resource_id;
    const int point_icons = image_id_from_group(GROUP_FIGURE_MAP_FLAG_ICONS);

    tile2i point = tile2i::invalid;
    int icon = 0;
    if (id == MAP_FLAG_EARTHQUAKE) {
        point = scenario_editor_earthquake_point();
        icon = point_icons;
    } else if (id == MAP_FLAG_ENTRY) {
        point = scenario_map_entry();
        icon = point_icons + 2;
    } else if (id == MAP_FLAG_EXIT) {
        point = scenario_map_exit();
        icon = point_icons + 3;
    } else if (id == MAP_FLAG_RIVER_ENTRY) {
        point = scenario_map_river_entry();
        icon = point_icons + 4;
    } else if (id == MAP_FLAG_RIVER_EXIT) {
        point = scenario_map_river_exit();
        icon = point_icons + 5;
    } else if (id >= MAP_FLAG_FISHING_MIN && id < MAP_FLAG_FISHING_MAX) {
        point = scenario_editor_fishing_point(id - MAP_FLAG_FISHING_MIN);
        icon = image_id_resource_icon(RESOURCE_FISH);
    } else if (id >= MAP_FLAG_PREDATOR_HERD_MIN && id < MAP_FLAG_PREDATOR_HERD_MAX) {
        point = scenario_editor_predator_herd_point(id - MAP_FLAG_PREDATOR_HERD_MIN);
        icon = image_id_from_group(GROUP_FIGURE_MAP_FLAG_HERD_ICONS) + 1;
    } else if (id >= MAP_FLAG_PREY_HERD_MIN && id < MAP_FLAG_PREY_HERD_MAX) {
        point = scenario_editor_prey_herd_point(id - MAP_FLAG_PREY_HERD_MIN);
        icon = image_id_from_group(GROUP_FIGURE_MAP_FLAG_HERD_ICONS) + 5;
    } else if (id >= MAP_FLAG_DISEMBARK_MIN && id < MAP_FLAG_DISEMBARK_MAX) {
        point = scenario_editor_disembark_point(id - MAP_FLAG_DISEMBARK_MIN);
        icon = image_id_from_group(GROUP_FIGURE_MAP_FLAG_DISEMBARK);
    } else if (id >= MAP_FLAG_INVASION_MIN && id < MAP_FLAG_INVASION_LAND_MAX) {
        point = scenario_editor_land_invasion_point(id - MAP_FLAG_INVASION_MIN);
        icon = point_icons + 1;
    } else if (id >= MAP_FLAG_INVASION_LAND_MAX && id < MAP_FLAG_INVASION_MAX) {
        point = scenario_editor_sea_invasion_point(id - MAP_FLAG_INVASION_LAND_MAX);
        icon = image_id_from_group(GROUP_FIGURE_MAP_FLAG_SEA_INVASION);
    }

    cart_image_id = icon;
    if (!point.valid()) {
        tile = tile2i::invalid;
        return;
    }

    tile = point;
    use_cross_country = false;
    direction = 0;
    progress_on_tile = 0;
    map_figure_add();
}
