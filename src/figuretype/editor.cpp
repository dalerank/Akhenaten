#include "editor.h"

#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "scenario/editor_map.h"
#include "scenario/map.h"

void figure_create_editor_flags() {
    for (int id = MAP_FLAG_MIN; id < MAP_FLAG_MAX; id++) {
        figure* f = figure_create(FIGURE_MAP_FLAG, tile2i(-1, -1), 0);
        f->set_resource((e_resource)id);
    }
}

void figure::editor_flag_action() {
    // each flag figure tracks one stored scenario point (selected by resource_id);
    // reposition it onto that point every tick so placed points are visualized.
    map_figure_remove();

    const int id = resource_id;
    const int icon_base = image_id_from_group(GROUP_FIGURE_MAP_FLAG_ICONS);

    tile2i point = tile2i::invalid;
    int icon_offset = 0;
    if (id == MAP_FLAG_EARTHQUAKE) {
        point = scenario_editor_earthquake_point();
        icon_offset = 0;
    } else if (id == MAP_FLAG_ENTRY) {
        point = scenario_map_entry();
        icon_offset = 2;
    } else if (id == MAP_FLAG_EXIT) {
        point = scenario_map_exit();
        icon_offset = 3;
    } else if (id == MAP_FLAG_RIVER_ENTRY) {
        point = scenario_map_river_entry();
        icon_offset = 4;
    } else if (id == MAP_FLAG_RIVER_EXIT) {
        point = scenario_map_river_exit();
        icon_offset = 5;
    } else if (id >= MAP_FLAG_INVASION_MIN && id < MAP_FLAG_INVASION_MAX) {
        point = scenario_editor_land_invasion_point(id - MAP_FLAG_INVASION_MIN);
        icon_offset = 1;
    } else if (id >= MAP_FLAG_FISHING_MIN && id < MAP_FLAG_FISHING_MAX) {
        point = scenario_editor_fishing_point(id - MAP_FLAG_FISHING_MIN);
        // original used GROUP_FIGURE_FORT_STANDARD_ICONS (unavailable here); the
        // flag number drawn by draw_map_flag disambiguates fishing/herd points
        icon_offset = 1;
    } else if (id >= MAP_FLAG_HERD_MIN && id < MAP_FLAG_HERD_MAX) {
        point = scenario_editor_predator_herd_point(id - MAP_FLAG_HERD_MIN);
        icon_offset = 1;
    }

    if (!point.valid()) {
        // not placed yet: hide (draw_map_flag is skipped when cart_image_id == 0)
        cart_image_id = 0;
        tile = tile2i::invalid;
        return;
    }

    tile = point;
    use_cross_country = false;
    direction = 0;
    progress_on_tile = 0;
    main_image_id = image_id_from_group(GROUP_FIGURE_MAP_FLAG_FLAGS);
    cart_image_id = icon_base + icon_offset;
    map_figure_add();
}
