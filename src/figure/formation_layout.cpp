#include "formation_layout.h"

#include "figure/formation.h"

static const int FORMATION_LAYOUT_POSITION_X[16][16] = {
  {0, 1, 0, 1, -1, -1, 0, 1, -1, 2, 2, 2, 0, 1, -1, 2},
  {0, 0, -1, 1, -1, 1, -2, -2, 2, 2, -3, -3, 3, 3, -4, -4},
  {0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
  {0, 2, -2, 1, -1, 3, -3, 4, -4, 5, 6, -5, -6, 7, 8, -7},
  {0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1},
  {0, 0, 1, 0, -1, 1, 1, -1, -1, 1, 1, -1, -1, 1, -1, 0},
  {0, 1, 0, 1, 2, 2, 1, 0, 2, 3, 3, 3, 1, 2, 0, 3},
  {0, 1, 0, 1, 2, 2, 1, 0, 2, 3, 3, 3, 1, 2, 0, 3},
  {0, 1, 0, 0, 1, -1, 2, -1, 1, 0, 1, 0, 1, -1, 1, -1},
  {0, 2, -1, 1, 1, -1, 3, -2, 0, -4, -1, 0, 1, 4, 2, -5},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 2, 0, 2, -2, -2, 0, 2, -2, 4, 4, 4, 0, 2, -2, 4},
  {0, 1, 0, 1, 2, 2, 1, 0, 2, 3, 3, 3, 1, 2, 0, 3},
  {0, 1, 0, 1, -1, -1, 0, 1, -1, 2, 2, 2, 0, 1, -1, 2},
  {0, 1, 0, 1, -1, -1, 0, 1, -1, 2, 2, 2, 0, 1, -1, 2},
  // FORMATION_CHARGE (0x0F): same spacing as column — OG aftermath holds the charge line.
  {0, 1, 0, 1, -1, -1, 0, 1, -1, 2, 2, 2, 0, 1, -1, 2},
};
static const int FORMATION_LAYOUT_POSITION_Y[16][16] = {
  {0, 0, 1, 1, 0, 1, -1, -1, -1, -1, 0, 1, 2, 2, 2, 2},
  {0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
  {0, -1, 1, 0, -1, 1, -2, -2, 2, 2, -3, -3, 3, 3, -4, -4},
  {0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1},
  {0, -2, 2, -1, 1, -3, 3, -4, 4, -5, -6, 5, 6, -7, -8, 7},
  {0, -1, 0, 1, 0, -1, 1, 1, -1, -1, 1, 1, -1, 0, 0, 0},
  {0, 0, 1, 1, 0, 1, 2, 2, 2, 0, 1, 2, 3, 3, 3, 3},
  {0, 0, 1, 1, 0, 1, 2, 2, 2, 0, 1, 2, 3, 3, 3, 3},
  {0, -1, 1, 0, 0, 1, 1, -1, -1, 1, 0, 2, 1, 1, -2, 1},
  {0, 1, -1, 1, 0, 1, 1, -1, 2, 0, 3, 5, 4, 0, 3, 2},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 2, 2, 0, 2, -2, -2, -2, -2, 0, 2, 4, 4, 4, 4},
  {0, 0, 1, 1, 0, 1, 2, 2, 2, 0, 1, 2, 3, 3, 3, 3},
  {0, 0, 1, 1, 0, 1, -1, -1, -1, -1, 0, 1, 2, 2, 2, 2},
  {0, 0, 1, 1, 0, 1, -1, -1, -1, -1, 0, 1, 2, 2, 2, 2},
  {0, 0, 1, 1, 0, 1, -1, -1, -1, -1, 0, 1, 2, 2, 2, 2},
};

// OG herd_offsets_16+0x200 / +0x280: chariots take a wider double-line (≈2× infantry gaps).
static const int CHARIOT_DOUBLE_LINE_1_X[16] = {
  0, 0, -2, 2, -2, 2, -4, -4, 4, 4, -6, -6, 6, 6, -8, -8
};
static const int CHARIOT_DOUBLE_LINE_1_Y[16] = {
  0, 2, 0, 0, 2, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2
};
static const int CHARIOT_DOUBLE_LINE_2_X[16] = {
  0, 0, 0, 2, 2, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2
};
static const int CHARIOT_DOUBLE_LINE_2_Y[16] = {
  0, -2, 2, 0, -2, 2, -4, -4, 4, 4, -6, -6, 6, 6, -8, -8
};

tile2i formation_layout_position(int layout, int index) {
    if (layout < 0 || layout >= 16) {
        layout = 0;
    }
    if (index < 0 || index >= 16) {
        index = 0;
    }
    return tile2i(FORMATION_LAYOUT_POSITION_X[layout][index],
                  FORMATION_LAYOUT_POSITION_Y[layout][index]);
}

tile2i formation_layout_position_for_figure(e_figure_type type, int layout, int index) {
    if (index < 0 || index >= 16) {
        index = 0;
    }
    if (type == FIGURE_FCHARIOTEER) {
        if (layout == FORMATION_DOUBLE_LINE_1) {
            return tile2i(CHARIOT_DOUBLE_LINE_1_X[index], CHARIOT_DOUBLE_LINE_1_Y[index]);
        }
        if (layout == FORMATION_DOUBLE_LINE_2) {
            return tile2i(CHARIOT_DOUBLE_LINE_2_X[index], CHARIOT_DOUBLE_LINE_2_Y[index]);
        }
    }
    return formation_layout_position(layout, index);
}
