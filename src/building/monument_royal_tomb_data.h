#pragma once

#include <cstdint>
#include <iterator>

enum {
    ROYAL_TOMB_SIZES = 4,
    ROYAL_TOMB_CHAMBER_KINDS = 30,
    ROYAL_TOMB_SPOT_TABLES = 25,
    ROYAL_TOMB_ENTRANCE_KINDS = 3,
    ROYAL_TOMB_CLOSED_VARIANTS = 5,
};

enum e_royal_tomb_chamber_kind : uint8_t {
    ROYAL_TOMB_KIND_SEALING = 17,
    ROYAL_TOMB_KIND_ENTRANCE_A = 18,
    ROYAL_TOMB_KIND_ENTRANCE_B = 27,
    ROYAL_TOMB_KIND_ENTRANCE_C = 28,
};

struct royal_tomb_part_init {
    int8_t dx;
    int8_t dy;
    int8_t size;
    int8_t anim_key;
    int8_t kind;
    int8_t neighbours[2];
    int16_t work;
    uint8_t completed_image;
    int8_t closed_variant; // -1: rand() % ROYAL_TOMB_CLOSED_VARIANTS at placement
};

struct royal_tomb_access_offset {
    int8_t dx;
    int8_t dy;
};

struct royal_tomb_chamber_image {
    uint8_t kind;
    uint8_t group;
};

struct royal_tomb_layout {
    const royal_tomb_part_init* parts;
    uint16_t part_count;
    uint8_t chambers;
    uint16_t last_part;
    const royal_tomb_access_offset* access;
    uint8_t access_count;
    bool access_outside_own_tile;
    bool last_part_closed;
    bool sealing_adds_stage;
    uint8_t sealing_group;
    uint8_t entrance_groups[ROYAL_TOMB_ENTRANCE_KINDS];
    const royal_tomb_chamber_image* chamber_images;
    uint8_t chamber_image_count;
};

extern const royal_tomb_layout g_royal_tomb_layouts[ROYAL_TOMB_SIZES];
// Work spot table per chamber kind (-1: the kind is never worked).
extern const int8_t g_royal_tomb_spot_tables[ROYAL_TOMB_CHAMBER_KINDS];
