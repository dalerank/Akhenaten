#include "formation_layout.h"

#include "core/svector.h"
#include "core/vec2i.h"
#include "figure/formation.h"
#include "core/archive.h"
#include "js/js_register.h"

struct formation_layout_row {
    e_formation_layout layout;
    xstring hint;
    svector<vec2i, FORMATION_LAYOUT_SPOTS> spots;
    svector<vec2i, FORMATION_LAYOUT_SPOTS> chariot_spots;
};
ANK_CONFIG_STRUCT(formation_layout_row, layout, hint, spots, chariot_spots)

svector<formation_layout_row, FORMATION_LAYOUT_COUNT> ANK_VARIABLE(formation_layouts);

static vec2i layout_spot(const svector<vec2i, FORMATION_LAYOUT_SPOTS>& spots, int index) {
    return index < (int)spots.size() ? spots[index] : vec2i{0, 0};
}

tile2i formation_layout_position(int layout, int index) {
    if (layout < 0 || layout >= (int)formation_layouts.size()) {
        layout = 0;
    }
    if (index < 0 || index >= FORMATION_LAYOUT_SPOTS || formation_layouts.empty()) {
        return tile2i(0, 0);
    }
    const vec2i p = layout_spot(formation_layouts[layout].spots, index);
    return tile2i(p.x, p.y);
}

tile2i formation_layout_position_for_figure(e_figure_type type, int layout, int index) {
    if (type == FIGURE_FCHARIOTEER && layout >= 0 && layout < (int)formation_layouts.size()
        && !formation_layouts[layout].chariot_spots.empty() && index >= 0 && index < FORMATION_LAYOUT_SPOTS) {
        const vec2i p = layout_spot(formation_layouts[layout].chariot_spots, index);
        return tile2i(p.x, p.y);
    }
    return formation_layout_position(layout, index);
}
