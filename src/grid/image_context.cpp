#include "image_context.h"

#include "city/city_buildings.h"
#include "graphics/view/view.h"
#include "grid/building.h"
#include "grid/elevation.h"
#include "grid/grid.h"
#include "grid/property.h"
#include "grid/terrain.h"
#include "moisture.h"

#define MAX_TILES 8

struct terrain_image_context {
    const unsigned char tiles[MAX_TILES];
    const unsigned char offset_for_orientation[4];
    const unsigned char aqueduct_offset;
    const unsigned char max_item_offset;
    unsigned char current_item_offset;
};

// 0 = no match
// 1 = match
// 2 = don't care

static struct terrain_image_context terrain_images_water[48] = {
  {{1, 2, 1, 2, 1, 2, 1, 2}, {79, 79, 79, 79}, 0, 1}, {{1, 2, 1, 2, 1, 2, 0, 2}, {47, 46, 45, 44}, 0, 1},
  {{0, 2, 1, 2, 1, 2, 1, 2}, {44, 47, 46, 45}, 0, 1}, {{1, 2, 0, 2, 1, 2, 1, 2}, {45, 44, 47, 46}, 0, 1},
  {{1, 2, 1, 2, 0, 2, 1, 2}, {46, 45, 44, 47}, 0, 1}, {{1, 2, 0, 2, 1, 2, 0, 2}, {40, 42, 40, 42}, 0, 2},
  {{0, 2, 1, 2, 0, 2, 1, 2}, {42, 40, 42, 40}, 0, 2}, {{1, 2, 1, 2, 0, 0, 0, 2}, {32, 28, 24, 36}, 0, 4},
  {{0, 2, 1, 2, 1, 2, 0, 0}, {36, 32, 28, 24}, 0, 4}, {{0, 0, 0, 2, 1, 2, 1, 2}, {24, 36, 32, 28}, 0, 4},
  {{1, 2, 0, 0, 0, 2, 1, 2}, {28, 24, 36, 32}, 0, 4}, {{1, 2, 1, 2, 0, 1, 0, 2}, {77, 76, 75, 78}, 0, 1},
  {{0, 2, 1, 2, 1, 2, 0, 1}, {78, 77, 76, 75}, 0, 1}, {{0, 1, 0, 2, 1, 2, 1, 2}, {75, 78, 77, 76}, 0, 1},
  {{1, 2, 0, 1, 0, 2, 1, 2}, {76, 75, 78, 77}, 0, 1}, {{1, 2, 0, 0, 0, 0, 0, 2}, {16, 12, 8, 20}, 0, 4},
  {{0, 2, 1, 2, 0, 0, 0, 0}, {20, 16, 12, 8}, 0, 4},  {{0, 0, 0, 2, 1, 2, 0, 0}, {8, 20, 16, 12}, 0, 4},
  {{0, 0, 0, 0, 0, 2, 1, 2}, {12, 8, 20, 16}, 0, 4},  {{1, 2, 0, 1, 0, 0, 0, 2}, {69, 66, 63, 72}, 0, 1},
  {{0, 2, 1, 2, 0, 1, 0, 0}, {72, 69, 66, 63}, 0, 1}, {{0, 0, 0, 2, 1, 2, 0, 1}, {63, 72, 69, 66}, 0, 1},
  {{0, 1, 0, 0, 0, 2, 1, 2}, {66, 63, 72, 69}, 0, 1}, {{1, 2, 0, 0, 0, 1, 0, 2}, {70, 67, 64, 73}, 0, 1},
  {{0, 2, 1, 2, 0, 0, 0, 1}, {73, 70, 67, 64}, 0, 1}, {{0, 1, 0, 2, 1, 2, 0, 0}, {64, 73, 70, 67}, 0, 1},
  {{0, 0, 0, 1, 0, 2, 1, 2}, {67, 64, 73, 70}, 0, 1}, {{1, 2, 0, 1, 0, 1, 0, 2}, {71, 68, 65, 74}, 0, 1},
  {{0, 2, 1, 2, 0, 1, 0, 1}, {74, 71, 68, 65}, 0, 1}, {{0, 1, 0, 2, 1, 2, 0, 1}, {65, 74, 71, 68}, 0, 1},
  {{0, 1, 0, 1, 0, 2, 1, 2}, {68, 65, 74, 71}, 0, 1}, {{0, 1, 0, 1, 0, 1, 0, 1}, {62, 62, 62, 62}, 0, 1},
  {{0, 1, 0, 1, 0, 1, 0, 0}, {60, 59, 58, 61}, 0, 1}, {{0, 0, 0, 1, 0, 1, 0, 1}, {61, 60, 59, 58}, 0, 1},
  {{0, 1, 0, 0, 0, 1, 0, 1}, {58, 61, 60, 59}, 0, 1}, {{0, 1, 0, 1, 0, 0, 0, 1}, {59, 58, 61, 60}, 0, 1},
  {{0, 1, 0, 0, 0, 1, 0, 0}, {48, 49, 48, 49}, 0, 1}, {{0, 0, 0, 1, 0, 0, 0, 1}, {49, 48, 49, 48}, 0, 1},
  {{0, 1, 0, 1, 0, 0, 0, 0}, {56, 55, 54, 57}, 0, 1}, {{0, 0, 0, 1, 0, 1, 0, 0}, {57, 56, 55, 54}, 0, 1},
  {{0, 0, 0, 0, 0, 1, 0, 1}, {54, 57, 56, 55}, 0, 1}, {{0, 1, 0, 0, 0, 0, 0, 1}, {55, 54, 57, 56}, 0, 1},
  {{0, 1, 0, 0, 0, 0, 0, 0}, {52, 51, 50, 53}, 0, 1}, {{0, 0, 0, 1, 0, 0, 0, 0}, {53, 52, 51, 50}, 0, 1},
  {{0, 0, 0, 0, 0, 1, 0, 0}, {50, 53, 52, 51}, 0, 1}, {{0, 0, 0, 0, 0, 0, 0, 1}, {51, 50, 53, 52}, 0, 1},
  {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0}, 0, 6},     {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
};

static struct terrain_image_context terrain_images_wall[48] = {
  {{1, 2, 1, 2, 1, 2, 1, 2}, {26, 26, 26, 26}, 0, 1}, {{1, 2, 1, 2, 1, 2, 0, 2}, {15, 10, 5, 16}, 0, 1},
  {{0, 2, 1, 2, 1, 2, 1, 2}, {16, 15, 10, 5}, 0, 1},  {{1, 2, 0, 2, 1, 2, 1, 2}, {5, 16, 15, 10}, 0, 1},
  {{1, 2, 1, 2, 0, 2, 1, 2}, {10, 5, 16, 15}, 0, 1},  {{1, 2, 0, 2, 1, 2, 0, 2}, {1, 4, 1, 4}, 0, 1},
  {{0, 2, 1, 2, 0, 2, 1, 2}, {4, 1, 4, 1}, 0, 1},     {{1, 2, 1, 2, 0, 0, 0, 2}, {10, 7, 5, 12}, 0, 1},
  {{0, 2, 1, 2, 1, 2, 0, 0}, {12, 10, 7, 5}, 0, 1},   {{0, 0, 0, 2, 1, 2, 1, 2}, {5, 12, 10, 7}, 0, 1},
  {{1, 2, 0, 0, 0, 2, 1, 2}, {7, 5, 12, 10}, 0, 1},   {{1, 2, 1, 2, 0, 1, 0, 2}, {10, 22, 5, 12}, 0, 1},
  {{0, 2, 1, 2, 1, 2, 0, 1}, {12, 10, 22, 5}, 0, 1},  {{0, 1, 0, 2, 1, 2, 1, 2}, {5, 12, 10, 22}, 0, 1},
  {{1, 2, 0, 1, 0, 2, 1, 2}, {22, 5, 12, 10}, 0, 1},  {{1, 2, 0, 0, 0, 0, 0, 2}, {3, 2, 1, 4}, 0, 1},
  {{0, 2, 1, 2, 0, 0, 0, 0}, {4, 3, 2, 1}, 0, 1},     {{0, 0, 0, 2, 1, 2, 0, 0}, {1, 4, 3, 2}, 0, 1},
  {{0, 0, 0, 0, 0, 2, 1, 2}, {2, 1, 4, 3}, 0, 1},     {{1, 2, 0, 1, 0, 0, 0, 2}, {22, 24, 1, 4}, 0, 1},
  {{0, 2, 1, 2, 0, 1, 0, 0}, {4, 22, 24, 1}, 0, 1},   {{0, 0, 0, 2, 1, 2, 0, 1}, {1, 4, 22, 24}, 0, 1},
  {{0, 1, 0, 0, 0, 2, 1, 2}, {24, 1, 4, 22}, 0, 1},   {{1, 2, 0, 0, 0, 1, 0, 2}, {25, 22, 1, 4}, 0, 1},
  {{0, 2, 1, 2, 0, 0, 0, 1}, {4, 25, 22, 1}, 0, 1},   {{0, 1, 0, 2, 1, 2, 0, 0}, {1, 4, 25, 22}, 0, 1},
  {{0, 0, 0, 1, 0, 2, 1, 2}, {22, 1, 4, 25}, 0, 1},   {{1, 2, 0, 1, 0, 1, 0, 2}, {22, 22, 1, 4}, 0, 1},
  {{0, 2, 1, 2, 0, 1, 0, 1}, {4, 22, 22, 1}, 0, 1},   {{0, 1, 0, 2, 1, 2, 0, 1}, {1, 4, 22, 22}, 0, 1},
  {{0, 1, 0, 1, 0, 2, 1, 2}, {22, 1, 4, 22}, 0, 1},   {{0, 1, 0, 1, 0, 1, 0, 1}, {22, 22, 22, 22}, 0, 1},
  {{0, 1, 0, 1, 0, 1, 0, 0}, {22, 22, 23, 22}, 0, 1}, {{0, 0, 0, 1, 0, 1, 0, 1}, {22, 22, 22, 23}, 0, 1},
  {{0, 1, 0, 0, 0, 1, 0, 1}, {23, 22, 22, 22}, 0, 1}, {{0, 1, 0, 1, 0, 0, 0, 1}, {22, 23, 22, 22}, 0, 1},
  {{0, 1, 0, 0, 0, 1, 0, 0}, {17, 18, 17, 18}, 0, 1}, {{0, 0, 0, 1, 0, 0, 0, 1}, {18, 17, 18, 17}, 0, 1},
  {{0, 1, 0, 1, 0, 0, 0, 0}, {22, 21, 19, 22}, 0, 1}, {{0, 0, 0, 1, 0, 1, 0, 0}, {22, 22, 21, 19}, 0, 1},
  {{0, 0, 0, 0, 0, 1, 0, 1}, {19, 22, 22, 21}, 0, 1}, {{0, 1, 0, 0, 0, 0, 0, 1}, {21, 19, 22, 22}, 0, 1},
  {{0, 1, 0, 0, 0, 0, 0, 0}, {21, 20, 19, 22}, 0, 1}, {{0, 0, 0, 1, 0, 0, 0, 0}, {22, 21, 20, 19}, 0, 1},
  {{0, 0, 0, 0, 0, 1, 0, 0}, {19, 22, 21, 20}, 0, 1}, {{0, 0, 0, 0, 0, 0, 0, 1}, {20, 19, 22, 21}, 0, 1},
  {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0}, 0, 1},     {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0}, 0, 0},
};

static struct terrain_image_context terrain_images_wall_gatehouse[10] = {
  {{1, 2, 0, 2, 0, 2, 0, 2}, {16, 15, 10, 5}, 0, 1},
  {{0, 2, 1, 2, 0, 2, 0, 2}, {5, 16, 15, 10}, 0, 1},
  {{0, 2, 0, 2, 1, 2, 0, 2}, {10, 5, 16, 15}, 0, 1},
  {{0, 2, 0, 2, 0, 2, 1, 2}, {15, 10, 5, 16}, 0, 1},
  {{1, 2, 1, 2, 0, 2, 0, 2}, {27, 12, 28, 22}, 0, 1},
  {{0, 2, 1, 2, 1, 2, 0, 2}, {22, 27, 12, 28}, 0, 1},
  {{0, 2, 0, 2, 1, 2, 1, 2}, {28, 22, 27, 12}, 0, 1},
  {{1, 2, 0, 2, 0, 2, 1, 2}, {12, 28, 22, 27}, 0, 1},
  {{1, 2, 0, 2, 1, 2, 0, 2}, {31, 32, 31, 32}, 0, 1},
  {{0, 2, 1, 2, 0, 2, 1, 2}, {32, 31, 32, 31}, 0, 1},
};

static struct terrain_image_context terrain_images_elevation[14] = {
  {{1, 1, 1, 1, 1, 1, 1, 1}, {44, 44, 44, 44}, 2, 1},
  {{1, 1, 1, 1, 1, 0, 1, 1}, {30, 18, 28, 22}, 4, 2},
  {{1, 1, 1, 1, 1, 1, 1, 0}, {22, 30, 18, 28}, 4, 2},
  {{1, 0, 1, 1, 1, 1, 1, 1}, {28, 22, 30, 18}, 4, 2},
  {{1, 1, 1, 0, 1, 1, 1, 1}, {18, 28, 22, 30}, 4, 2},
  {{1, 1, 1, 2, 2, 2, 1, 1}, {0, 8, 12, 4}, 4, 4},
  {{1, 1, 1, 1, 1, 2, 2, 2}, {4, 0, 8, 12}, 4, 4},
  {{2, 2, 1, 1, 1, 1, 1, 2}, {12, 4, 0, 8}, 4, 4},
  {{1, 2, 2, 2, 1, 1, 1, 1}, {8, 12, 4, 0}, 4, 4},
  {{1, 1, 1, 2, 2, 2, 2, 2}, {24, 16, 26, 20}, 4, 2},
  {{2, 2, 1, 1, 1, 2, 2, 2}, {20, 24, 16, 26}, 4, 2},
  {{2, 2, 2, 2, 1, 1, 1, 2}, {26, 20, 24, 16}, 4, 2},
  {{1, 2, 2, 2, 2, 2, 1, 1}, {16, 26, 20, 24}, 4, 2},
  {{2, 2, 2, 2, 2, 2, 2, 2}, {32, 32, 32, 32}, 4, 4},
};

static struct terrain_image_context terrain_images_earthquake[17] = {
  {{1, 2, 1, 2, 1, 2, 1, 2}, {29, 29, 29, 29}, 0, 1},
  {{1, 2, 1, 2, 1, 2, 0, 2}, {25, 28, 27, 26}, 0, 1},
  {{0, 2, 1, 2, 1, 2, 1, 2}, {26, 25, 28, 27}, 0, 1},
  {{1, 2, 0, 2, 1, 2, 1, 2}, {27, 26, 25, 28}, 0, 1},
  {{1, 2, 1, 2, 0, 2, 1, 2}, {28, 27, 26, 25}, 0, 1},
  {{1, 2, 1, 2, 0, 2, 0, 2}, {8, 14, 12, 10}, 0, 2},
  {{0, 2, 1, 2, 1, 2, 0, 2}, {10, 8, 14, 12}, 0, 2},
  {{0, 2, 0, 2, 1, 2, 1, 2}, {12, 10, 8, 14}, 0, 2},
  {{1, 2, 0, 2, 0, 2, 1, 2}, {14, 12, 10, 8}, 0, 2},
  {{1, 2, 0, 2, 1, 2, 0, 2}, {0, 4, 0, 4}, 0, 4},
  {{0, 2, 1, 2, 0, 2, 1, 2}, {4, 0, 4, 0}, 0, 4},
  {{1, 2, 0, 2, 0, 2, 0, 2}, {16, 22, 18, 20}, 0, 2},
  {{0, 2, 1, 2, 0, 2, 0, 2}, {20, 16, 22, 18}, 0, 2},
  {{0, 2, 0, 2, 1, 2, 0, 2}, {18, 20, 16, 22}, 0, 2},
  {{0, 2, 0, 2, 0, 2, 1, 2}, {22, 18, 20, 16}, 0, 2},
  {{0, 2, 0, 2, 0, 2, 0, 2}, {24, 24, 24, 24}, 0, 1},
  {{2, 2, 2, 2, 2, 2, 2, 2}, {24, 24, 24, 24}, 0, 1},
};

static struct terrain_image_context terrain_images_dirt_road[17] = {
  {{1, 2, 1, 2, 1, 2, 1, 2}, {17, 17, 17, 17}, 0, 1},
  {{1, 2, 1, 2, 1, 2, 0, 2}, {13, 16, 15, 14}, 0, 1},
  {{0, 2, 1, 2, 1, 2, 1, 2}, {14, 13, 16, 15}, 0, 1},
  {{1, 2, 0, 2, 1, 2, 1, 2}, {15, 14, 13, 16}, 0, 1},
  {{1, 2, 1, 2, 0, 2, 1, 2}, {16, 15, 14, 13}, 0, 1},
  {{1, 2, 1, 2, 0, 2, 0, 2}, {4, 7, 6, 5}, 0, 1},
  {{0, 2, 1, 2, 1, 2, 0, 2}, {5, 4, 7, 6}, 0, 1},
  {{0, 2, 0, 2, 1, 2, 1, 2}, {6, 5, 4, 7}, 0, 1},
  {{1, 2, 0, 2, 0, 2, 1, 2}, {7, 6, 5, 4}, 0, 1},
  {{1, 2, 0, 2, 1, 2, 0, 2}, {0, 1, 0, 1}, 0, 1},
  {{0, 2, 1, 2, 0, 2, 1, 2}, {1, 0, 1, 0}, 0, 1},
  {{1, 2, 0, 2, 0, 2, 0, 2}, {8, 11, 10, 9}, 0, 1},
  {{0, 2, 1, 2, 0, 2, 0, 2}, {9, 8, 11, 10}, 0, 1},
  {{0, 2, 0, 2, 1, 2, 0, 2}, {10, 9, 8, 11}, 0, 1},
  {{0, 2, 0, 2, 0, 2, 1, 2}, {11, 10, 9, 8}, 0, 1},
  {{0, 2, 0, 2, 0, 2, 0, 2}, {12, 12, 12, 12}, 0, 1},
  {{2, 2, 2, 2, 2, 2, 2, 2}, {12, 12, 12, 12}, 0, 1},
};

static struct terrain_image_context terrain_images_paved_road[48] = {
  {{1, 0, 1, 0, 1, 0, 1, 0}, {17, 17, 17, 17}, 0, 1}, {{1, 0, 1, 0, 1, 2, 0, 2}, {13, 16, 15, 14}, 0, 1},
  {{1, 1, 1, 1, 1, 2, 0, 2}, {18, 21, 20, 19}, 0, 1}, {{1, 0, 1, 1, 1, 2, 0, 2}, {26, 33, 32, 31}, 0, 1},
  {{1, 1, 1, 0, 1, 2, 0, 2}, {30, 29, 28, 27}, 0, 1}, {{0, 2, 1, 0, 1, 0, 1, 2}, {14, 13, 16, 15}, 0, 1},
  {{0, 2, 1, 1, 1, 1, 1, 2}, {19, 18, 21, 20}, 0, 1}, {{0, 2, 1, 0, 1, 1, 1, 2}, {31, 26, 33, 32}, 0, 1},
  {{0, 2, 1, 1, 1, 0, 1, 2}, {27, 30, 29, 28}, 0, 1}, {{1, 2, 0, 2, 1, 0, 1, 0}, {15, 14, 13, 16}, 0, 1},
  {{1, 2, 0, 2, 1, 1, 1, 1}, {20, 19, 18, 21}, 0, 1}, {{1, 2, 0, 2, 1, 0, 1, 1}, {32, 31, 26, 33}, 0, 1},
  {{1, 2, 0, 2, 1, 1, 1, 0}, {28, 27, 30, 29}, 0, 1}, {{1, 0, 1, 2, 0, 2, 1, 0}, {16, 15, 14, 13}, 0, 1},
  {{1, 1, 1, 2, 0, 2, 1, 1}, {21, 20, 19, 18}, 0, 1}, {{1, 1, 1, 2, 0, 2, 1, 0}, {33, 32, 31, 26}, 0, 1},
  {{1, 0, 1, 2, 0, 2, 1, 1}, {29, 28, 27, 30}, 0, 1}, {{1, 1, 1, 2, 0, 0, 0, 2}, {22, 25, 24, 23}, 0, 1},
  {{0, 2, 1, 1, 1, 2, 0, 0}, {23, 22, 25, 24}, 0, 1}, {{0, 0, 0, 2, 1, 1, 1, 2}, {24, 23, 22, 25}, 0, 1},
  {{1, 2, 0, 0, 0, 2, 1, 1}, {25, 24, 23, 22}, 0, 1}, {{1, 0, 1, 0, 1, 1, 1, 1}, {34, 37, 36, 35}, 0, 1},
  {{1, 1, 1, 0, 1, 0, 1, 1}, {35, 34, 37, 36}, 0, 1}, {{1, 1, 1, 1, 1, 0, 1, 0}, {36, 35, 34, 37}, 0, 1},
  {{1, 0, 1, 1, 1, 1, 1, 0}, {37, 36, 35, 34}, 0, 1}, {{1, 0, 1, 0, 1, 0, 1, 1}, {38, 41, 40, 39}, 0, 1},
  {{1, 1, 1, 0, 1, 0, 1, 0}, {39, 38, 41, 40}, 0, 1}, {{1, 0, 1, 1, 1, 0, 1, 0}, {40, 39, 38, 41}, 0, 1},
  {{1, 0, 1, 0, 1, 1, 1, 0}, {41, 40, 39, 38}, 0, 1}, {{1, 1, 1, 1, 1, 0, 1, 1}, {42, 45, 44, 43}, 0, 1},
  {{1, 1, 1, 1, 1, 1, 1, 0}, {43, 42, 45, 44}, 0, 1}, {{1, 0, 1, 1, 1, 1, 1, 1}, {44, 43, 42, 45}, 0, 1},
  {{1, 1, 1, 0, 1, 1, 1, 1}, {45, 44, 43, 42}, 0, 1}, {{1, 1, 1, 0, 1, 1, 1, 0}, {46, 47, 46, 47}, 0, 1},
  {{1, 0, 1, 1, 1, 0, 1, 1}, {47, 46, 47, 46}, 0, 1}, {{1, 2, 1, 2, 0, 2, 0, 2}, {4, 7, 6, 5}, 0, 1},
  {{0, 2, 1, 2, 1, 2, 0, 2}, {5, 4, 7, 6}, 0, 1},     {{0, 2, 0, 2, 1, 2, 1, 2}, {6, 5, 4, 7}, 0, 1},
  {{1, 2, 0, 2, 0, 2, 1, 2}, {7, 6, 5, 4}, 0, 1},     {{1, 2, 0, 2, 1, 2, 0, 2}, {0, 1, 0, 1}, 0, 1},
  {{0, 2, 1, 2, 0, 2, 1, 2}, {1, 0, 1, 0}, 0, 1},     {{1, 2, 0, 2, 0, 2, 0, 2}, {8, 11, 10, 9}, 0, 1},
  {{0, 2, 1, 2, 0, 2, 0, 2}, {9, 8, 11, 10}, 0, 1},   {{0, 2, 0, 2, 1, 2, 0, 2}, {10, 9, 8, 11}, 0, 1},
  {{0, 2, 0, 2, 0, 2, 1, 2}, {11, 10, 9, 8}, 0, 1},   {{0, 0, 0, 0, 0, 0, 0, 0}, {12, 12, 12, 12}, 0, 1},
  {{1, 1, 1, 1, 1, 1, 1, 1}, {48, 48, 48, 48}, 0, 1}, {{2, 2, 2, 2, 2, 2, 2, 2}, {12, 12, 12, 12}, 0, 1},
};

static struct terrain_image_context terrain_images_aqueduct[16] = {
  {{1, 2, 1, 2, 0, 2, 0, 2}, {4, 7, 6, 5}, 7, 1},
  {{0, 2, 1, 2, 1, 2, 0, 2}, {5, 4, 7, 6}, 8, 1},
  {{0, 2, 0, 2, 1, 2, 1, 2}, {6, 5, 4, 7}, 9, 1},
  {{1, 2, 0, 2, 0, 2, 1, 2}, {7, 6, 5, 4}, 10, 1},
  {{1, 2, 0, 2, 1, 2, 0, 2}, {2, 3, 2, 3}, 5, 1},
  {{0, 2, 1, 2, 0, 2, 1, 2}, {3, 2, 3, 2}, 6, 1},
  {{1, 2, 0, 2, 0, 2, 0, 2}, {2, 3, 2, 3}, 1, 1},
  {{0, 2, 1, 2, 0, 2, 0, 2}, {3, 2, 3, 2}, 2, 1},
  {{0, 2, 0, 2, 1, 2, 0, 2}, {2, 3, 2, 3}, 3, 1},
  {{0, 2, 0, 2, 0, 2, 1, 2}, {3, 2, 3, 2}, 4, 1},
  {{1, 2, 1, 2, 1, 2, 0, 2}, {10, 13, 12, 11}, 11, 1},
  {{0, 2, 1, 2, 1, 2, 1, 2}, {11, 10, 13, 12}, 12, 1},
  {{1, 2, 0, 2, 1, 2, 1, 2}, {12, 11, 10, 13}, 13, 1},
  {{1, 2, 1, 2, 0, 2, 1, 2}, {13, 12, 11, 10}, 14, 1},
  {{1, 2, 1, 2, 1, 2, 1, 2}, {14, 14, 14, 14}, 15, 1},
  {{2, 2, 2, 2, 2, 2, 2, 2}, {2, 2, 2, 2}, 0, 1},
};

static struct terrain_image_context terrain_images_deepwater[19] = {
  {{0, 2, 1, 1, 2, 1, 1, 2}, {0, 6, 4, 2}, 0, 1},     {{1, 2, 0, 2, 1, 1, 2, 1}, {2, 0, 6, 4}, 0, 1},
  {{2, 1, 1, 2, 0, 2, 1, 1}, {4, 2, 0, 6}, 0, 1},     {{1, 1, 2, 1, 1, 2, 0, 2}, {6, 4, 2, 0}, 0, 1},

  {{0, 2, 0, 1, 2, 1, 2, 1}, {1, 7, 5, 3}, 0, 1},     {{2, 1, 0, 2, 0, 1, 2, 1}, {3, 1, 7, 5}, 0, 1},
  {{2, 1, 2, 1, 0, 2, 0, 1}, {5, 3, 1, 7}, 0, 1},     {{0, 1, 2, 1, 2, 1, 0, 2}, {7, 5, 3, 1}, 0, 1},

  {{2, 0, 2, 1, 2, 1, 2, 1}, {8, 11, 10, 9}, 0, 1},   {{2, 1, 2, 0, 2, 1, 2, 1}, {9, 8, 11, 10}, 0, 1},
  {{2, 1, 2, 1, 2, 0, 2, 1}, {10, 9, 8, 11}, 0, 1},   {{2, 1, 2, 1, 2, 1, 2, 0}, {11, 10, 9, 8}, 0, 1},

  {{2, 0, 2, 2, 1, 1, 1, 2}, {1, 7, 5, 3}, 0, 1},     {{1, 2, 2, 0, 2, 2, 1, 1}, {3, 1, 7, 5}, 0, 1},
  {{1, 1, 1, 2, 2, 0, 2, 2}, {5, 3, 1, 7}, 0, 1},     {{2, 2, 1, 1, 1, 2, 2, 0}, {7, 5, 3, 1}, 0, 1},

  {{2, 0, 2, 1, 2, 0, 2, 1}, {12, 13, 12, 13}, 0, 1}, {{2, 1, 2, 0, 2, 1, 2, 0}, {13, 12, 13, 12}, 0, 1},

  {{1, 1, 1, 1, 1, 1, 1, 1}, {14, 14, 14, 14}, 0, 1},
};

static struct terrain_image_context terrain_images_floodsystem[46] = {
  {{1, 1, 1, 2, 0, 2, 1, 1}, {0, 12, 8, 4}, 0, 1},
  {{1, 1, 1, 1, 1, 2, 0, 2}, {4, 0, 12, 8}, 0, 1},
  {{0, 2, 1, 1, 1, 1, 1, 2}, {8, 4, 0, 12}, 0, 1},
  {{1, 2, 0, 2, 1, 1, 1, 1}, {12, 8, 4, 0}, 0, 1},

  // L-corner
  {{1, 0, 1, 2, 0, 2, 0, 2}, {67, 70, 69, 68}, 0, 1},
  {{0, 2, 1, 0, 1, 2, 0, 2}, {68, 67, 70, 69}, 0, 1},
  {{0, 2, 0, 2, 1, 0, 1, 2}, {69, 68, 67, 70}, 0, 1},
  {{1, 2, 0, 2, 0, 2, 1, 0}, {70, 69, 68, 67}, 0, 1},

  // big corners
  {{1, 2, 1, 2, 0, 2, 0, 2}, {16, 28, 24, 20}, 0, 1},
  {{0, 2, 1, 2, 1, 2, 0, 2}, {20, 16, 28, 24}, 0, 1},
  {{0, 2, 0, 2, 1, 2, 1, 2}, {24, 20, 16, 28}, 0, 1},
  {{1, 2, 0, 2, 0, 2, 1, 2}, {28, 24, 20, 16}, 0, 1},

  // deadend
  {{1, 2, 0, 2, 0, 2, 0, 2}, {36, 39, 38, 37}, 0, 1},
  {{0, 2, 1, 2, 0, 2, 0, 2}, {37, 36, 39, 38}, 0, 1},
  {{0, 2, 0, 2, 1, 2, 0, 2}, {38, 37, 36, 39}, 0, 1},
  {{0, 2, 0, 2, 0, 2, 1, 2}, {39, 38, 37, 36}, 0, 1},

  // opposite corners
  {{1, 0, 1, 1, 1, 0, 1, 1}, {40, 41, 40, 41}, 0, 1},
  {{1, 1, 1, 0, 1, 1, 1, 0}, {41, 40, 41, 40}, 0, 1},

  // big delta junction
  {{1, 1, 1, 1, 1, 0, 1, 0}, {46, 49, 48, 47}, 0, 1},
  {{1, 0, 1, 1, 1, 1, 1, 0}, {47, 46, 49, 48}, 0, 1},
  {{1, 0, 1, 0, 1, 1, 1, 1}, {48, 47, 46, 49}, 0, 1},
  {{1, 1, 1, 0, 1, 0, 1, 1}, {49, 48, 47, 46}, 0, 1},

  // big Y-junction
  {{1, 0, 1, 1, 1, 0, 1, 0}, {50, 53, 52, 51}, 0, 1},
  {{1, 0, 1, 0, 1, 1, 1, 0}, {51, 50, 53, 52}, 0, 1},
  {{1, 0, 1, 0, 1, 0, 1, 1}, {52, 51, 50, 53}, 0, 1},
  {{1, 1, 1, 0, 1, 0, 1, 0}, {53, 52, 51, 50}, 0, 1},

  // cross
  {{1, 0, 1, 0, 1, 0, 1, 0}, {54, 54, 54, 54}, 0, 1},

  // T-junction
  {{1, 0, 1, 2, 0, 2, 1, 0}, {57, 66, 63, 60}, 0, 1},
  {{1, 0, 1, 0, 1, 2, 0, 2}, {60, 57, 66, 63}, 0, 1},
  {{0, 2, 1, 0, 1, 0, 1, 2}, {63, 60, 57, 66}, 0, 1},
  {{1, 2, 0, 2, 1, 0, 1, 0}, {66, 63, 60, 57}, 0, 1},

  // L-junction
  {{1, 2, 1, 2, 0, 2, 1, 0}, {55, 64, 61, 58}, 0, 1},
  {{1, 0, 1, 2, 1, 2, 0, 2}, {58, 55, 64, 61}, 0, 1},
  {{0, 2, 1, 0, 1, 2, 1, 2}, {61, 58, 55, 64}, 0, 1},
  {{1, 2, 0, 2, 1, 0, 1, 2}, {64, 61, 58, 55}, 0, 1},

  // L-junction (mirror)
  {{1, 0, 1, 2, 0, 2, 1, 2}, {56, 65, 62, 59}, 0, 1},
  {{1, 2, 1, 0, 1, 2, 0, 2}, {59, 56, 65, 62}, 0, 1},
  {{0, 2, 1, 2, 1, 0, 1, 2}, {62, 59, 56, 65}, 0, 1},
  {{1, 2, 0, 2, 1, 2, 1, 0}, {65, 62, 59, 56}, 0, 1},

  // puddle
  {{0, 2, 0, 2, 0, 2, 0, 2}, {71, 71, 71, 71}, 0, 1},

  // opposite edges
  {{0, 2, 1, 2, 0, 2, 1, 2}, {32, 34, 32, 34}, 0, 1},
  {{1, 2, 0, 2, 1, 2, 0, 2}, {34, 32, 34, 32}, 0, 1},

  // small corners
  {{2, 2, 2, 2, 1, 0, 1, 2}, {42, 45, 44, 43}, 0, 1},
  {{1, 2, 2, 2, 2, 2, 1, 0}, {43, 42, 45, 44}, 0, 1},
  {{1, 0, 1, 2, 2, 2, 2, 2}, {44, 43, 42, 45}, 0, 1},
  {{2, 2, 1, 0, 1, 2, 2, 2}, {45, 44, 43, 42}, 0, 1},
};

static struct terrain_image_context terrain_images_grass_corners[12] = {

  // edges
  {{0, 0, 0, 2, 1, 2, 0, 0}, {0, 6, 4, 2}, 0, 1},
  {{0, 0, 0, 0, 0, 2, 1, 2}, {2, 0, 6, 4}, 0, 1},
  {{1, 2, 0, 0, 0, 0, 0, 2}, {4, 2, 0, 6}, 0, 1},
  {{0, 2, 1, 2, 0, 0, 0, 0}, {6, 4, 2, 0}, 0, 1},

  // big corners
  {{2, 0, 2, 0, 0, 1, 0, 0}, {1, 7, 5, 3}, 0, 1},
  {{0, 0, 2, 0, 2, 0, 0, 1}, {3, 1, 7, 5}, 0, 1},
  {{0, 1, 0, 0, 2, 0, 2, 0}, {5, 3, 1, 7}, 0, 1},
  {{2, 0, 0, 1, 0, 0, 2, 0}, {7, 5, 3, 1}, 0, 1},

  // small corners
  {{2, 2, 2, 2, 1, 2, 1, 2}, {8, 11, 10, 9}, 0, 1},
  {{1, 2, 2, 2, 2, 2, 1, 2}, {9, 8, 11, 10}, 0, 1},
  {{1, 2, 1, 2, 2, 2, 2, 2}, {10, 9, 8, 11}, 0, 1},
  {{2, 2, 1, 2, 1, 2, 2, 2}, {11, 10, 9, 8}, 0, 1},
};

// [5][6][7]
// [4]   [0]
// [3][2][1]

enum E_CONTEXT {
    CONTEXT_WATER,
    CONTEXT_WALL,
    CONTEXT_WALL_GATEHOUSE,
    CONTEXT_ELEVATION,
    CONTEXT_EARTHQUAKE,
    CONTEXT_DIRT_ROAD,
    CONTEXT_PAVED_ROAD,
    CONTEXT_AQUEDUCT,
    CONTEXT_DEEPWATER,
    CONTEXT_FLOODSYSTEM,
    CONTEXT_GRASSCORNERS,

    CONTEXT_MAX_ITEMS
};

struct image_context_t {
    struct terrain_image_context* context;
    int size;
};

image_context_t g_context_pointers[] = {{terrain_images_water, 48},
                        {terrain_images_wall, 48},
                        {terrain_images_wall_gatehouse, 10},
                        {terrain_images_elevation, 14},
                        {terrain_images_earthquake, 17},
                        {terrain_images_dirt_road, 17},
                        {terrain_images_paved_road, 48},
                        {terrain_images_aqueduct, 16},
                        {terrain_images_deepwater, 19},
                        {terrain_images_floodsystem, 46},
                        {terrain_images_grass_corners, 12}};

static void clear_current_offset(struct terrain_image_context* items, int num_items) {
    for (int i = 0; i < num_items; i++) {
        items[i].current_item_offset = 0;
    }
}
void map_image_context_init(void) {
    for (int i = 0; i < CONTEXT_MAX_ITEMS; i++) {
        clear_current_offset(g_context_pointers[i].context, g_context_pointers[i].size);
    }
}
void map_image_context_reset_water(void) {
    clear_current_offset(g_context_pointers[CONTEXT_WATER].context, g_context_pointers[CONTEXT_WATER].size);
}
void map_image_context_reset_elevation(void) {
    clear_current_offset(g_context_pointers[CONTEXT_ELEVATION].context, g_context_pointers[CONTEXT_ELEVATION].size);
}

static bool context_matches_tiles(const struct terrain_image_context* context, const int tiles[MAX_TILES]) {
    for (int i = 0; i < MAX_TILES; i++) {
        if (context->tiles[i] != 2 && tiles[i] != context->tiles[i]) // if pattern isn't "2", it must match!
            return false;
    }
    return true;
}
static void fill_matches(int grid_offset, int terrain, int match_value, int no_match_value, int tiles[MAX_TILES]) {
    for (int i = 0; i < MAX_TILES; i++)
        tiles[i] = map_terrain_is(grid_offset + map_grid_direction_delta(i), terrain) ? match_value : no_match_value;
}
static void fill_matches_grass(int grid_offset, int match_value, int no_match_value, int tiles[MAX_TILES]) {
    for (int i = 0; i < MAX_TILES; i++) {
        int moisture = map_moisture_get(grid_offset + map_grid_direction_delta(i));
        if (moisture & MOISTURE_TRANSITION)
            tiles[i] = no_match_value;
        else if (moisture >= 46 && moisture <= 50)
            tiles[i] = match_value;
        else
            tiles[i] = no_match_value;
    }
}

static const terrain_image* get_image(int group, int tiles[MAX_TILES]) {
    static terrain_image result;

    result.is_valid = 0;
    struct terrain_image_context* context = g_context_pointers[group].context;
    int size = g_context_pointers[group].size;
    for (int i = 0; i < size; i++) {
        if (context_matches_tiles(&context[i], tiles)) {
            context[i].current_item_offset++;
            if (context[i].current_item_offset >= context[i].max_item_offset)
                context[i].current_item_offset = 0;

            result.is_valid = 1;
            result.group_offset = context[i].offset_for_orientation[city_view_orientation() / 2];
            result.item_offset = context[i].current_item_offset;
            result.aqueduct_offset = context[i].aqueduct_offset;
            break;
        }
    }
    return &result;
}

const terrain_image* map_image_context_get_elevation(int grid_offset, int elevation) {
    int tiles[MAX_TILES];
    for (int i = 0; i < MAX_TILES; i++) {
        tiles[i] = map_elevation_at(grid_offset + map_grid_direction_delta(i)) >= elevation ? 1 : 0;
    }
    return get_image(CONTEXT_ELEVATION, tiles);
}

const terrain_image* map_image_context_get_earthquake(int grid_offset) {
    int tiles[MAX_TILES];
    for (int i = 0; i < MAX_TILES; i++) {
        int offset = grid_offset + map_grid_direction_delta(i);
        tiles[i] = (map_terrain_is(offset, TERRAIN_ROCK) && map_property_is_plaza_or_earthquake(tile2i(grid_offset))) ? 1 : 0;
    }
    return get_image(CONTEXT_EARTHQUAKE, tiles);
}

const terrain_image* map_image_context_get_shore(int grid_offset) {
    int tiles[MAX_TILES];
    fill_matches(grid_offset, TERRAIN_WATER, 0, 1, tiles);
    return get_image(CONTEXT_WATER, tiles);
}
const terrain_image* map_image_context_get_river(int grid_offset) {
    int tiles[MAX_TILES];
    fill_matches(grid_offset, TERRAIN_DEEPWATER, 1, 0, tiles);
    return get_image(CONTEXT_DEEPWATER, tiles);
}
const terrain_image* map_image_context_get_floodplain_shore(int grid_offset) {
    int tiles[MAX_TILES];
    fill_matches(grid_offset, TERRAIN_FLOODPLAIN, 0, 1, tiles);
    return get_image(CONTEXT_DEEPWATER, tiles);
}
const terrain_image* map_image_context_get_floodplain_waterline(int grid_offset) {
    int tiles[MAX_TILES];
    fill_matches(grid_offset, TERRAIN_WATER, 1, 0, tiles);
    return get_image(CONTEXT_FLOODSYSTEM, tiles);
}
const terrain_image* map_image_context_get_reeds_transition(int grid_offset) {
    int tiles[MAX_TILES];
    fill_matches(grid_offset, TERRAIN_MARSHLAND, 1, 0, tiles);
    return get_image(CONTEXT_FLOODSYSTEM, tiles);
}
const terrain_image* map_image_context_get_grass_corners(int grid_offset) {
    int tiles[MAX_TILES];
    fill_matches_grass(grid_offset, 1, 0, tiles);
    return get_image(CONTEXT_GRASSCORNERS, tiles);
}

const terrain_image* map_image_context_get_wall(int grid_offset) {
    int tiles[MAX_TILES];
    fill_matches(grid_offset, TERRAIN_WALL, 0, 1, tiles);
    return get_image(CONTEXT_WALL, tiles);
}
const terrain_image* map_image_context_get_wall_gatehouse(int grid_offset) {
    int tiles[MAX_TILES] = {0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < MAX_TILES; i += 2) {
        tiles[i] = map_terrain_is(grid_offset + map_grid_direction_delta(i), TERRAIN_WALL_OR_GATEHOUSE) ? 1 : 0;
    }
    return get_image(CONTEXT_WALL_GATEHOUSE, tiles);
}

static void set_tiles_road(int grid_offset, int tiles[MAX_TILES]) {
    fill_matches(grid_offset, TERRAIN_ROAD, 1, 0, tiles);
    for (int i = 0; i < MAX_TILES; i += 2) {
        int offset = grid_offset + map_grid_direction_delta(i);
        if (map_terrain_is(offset, TERRAIN_GATEHOUSE)) {
            building* b = building_at(offset);
            if (b->type == BUILDING_MUD_GATEHOUSE && b->subtype.orientation == 1 + ((i / 2) & 1)) { // 1,2,1,2
                tiles[i] = 1;
            }
        } else if (map_terrain_is(offset, TERRAIN_ACCESS_RAMP)) {
            tiles[i] = 1;
        } else if (map_terrain_is(offset, TERRAIN_BUILDING)) {
            building* b = building_at(offset);
            //if (b->type == BUILDING_GRANARY) {
            //    tiles[i] = (offset == b->tile.grid_offset() + GRID_OFFSET(1, 0)) ? 1 : 0;
            //    tiles[i] |= (offset == b->tile.grid_offset() + GRID_OFFSET(0, 1)) ? 1 : 0;
            //    tiles[i] |= (offset == b->tile.grid_offset() + GRID_OFFSET(2, 1)) ? 1 : 0;
            //    tiles[i] |= (offset == b->tile.grid_offset() + GRID_OFFSET(1, 2)) ? 1 : 0;
            //}
        }
    }
}

const terrain_image* map_image_context_get_dirt_road(int grid_offset) {
    int tiles[MAX_TILES];
    set_tiles_road(grid_offset, tiles);
    return get_image(CONTEXT_DIRT_ROAD, tiles);
}

const terrain_image* map_image_context_get_paved_road(int grid_offset) {
    int tiles[MAX_TILES];
    set_tiles_road(grid_offset, tiles);
    return get_image(CONTEXT_PAVED_ROAD, tiles);
}

static void set_terrain_canal_connections(int grid_offset, int direction, int multi_tile_mask, int* tiles) {
    int offset = grid_offset + map_grid_direction_delta(direction);
    if (map_terrain_is(offset, TERRAIN_BUILDING)) {
        building* b = building_at(offset);
        if (b->type == BUILDING_WATER_LIFT) {
            int lift_direction_binary = b->data.industry.orientation % 2;
            int canal_direction_binary = (direction / 2) % 2;
            if (lift_direction_binary == canal_direction_binary)
                tiles[direction] = 1;
            return;
        }
    }

    if (map_terrain_is(offset, TERRAIN_WATER)) {
        tiles[direction] = 1;
    }
}

const terrain_image* map_image_context_get_canal(int grid_offset) {
    int tiles[MAX_TILES] = {0, 0, 0, 0, 0, 0, 0, 0};
    int has_road = map_terrain_is(grid_offset, TERRAIN_ROAD) ? 1 : 0;
    for (int i = 0; i < MAX_TILES; i += 2) {
        int offset = grid_offset + map_grid_direction_delta(i);
        if (map_terrain_is(offset, TERRAIN_CANAL)) {
            if (has_road) {
                if (!map_terrain_is(offset, TERRAIN_ROAD))
                    tiles[i] = 1;
            } else
                tiles[i] = 1;
        }
    }
    set_terrain_canal_connections(grid_offset, 0, EDGE_X1Y2, tiles);
    set_terrain_canal_connections(grid_offset, 2, EDGE_X0Y1, tiles);
    set_terrain_canal_connections(grid_offset, 4, EDGE_X1Y0, tiles);
    set_terrain_canal_connections(grid_offset, 6, EDGE_X2Y1, tiles);
    return get_image(CONTEXT_AQUEDUCT, tiles);
}
