#pragma once

#include "figure/figure.h"

class building;

enum e_plagued_citizen_action {
    ACTION_8_PLAGUED_CREATED = 8,
    ACTION_9_PLAGUED_GOING_TO_ROAD = 9,
    ACTION_10_PLAGUED_ROAMING = 10,
    // Saves made before the OG port: carriers spawned on the road and roaming.
    ACTION_120_PLAGUED_LEGACY_CREATED = 120,
    ACTION_121_PLAGUED_LEGACY_ROAMING = 121,
};

struct plagued_corpse_frame_t {
    int16_t wait_ticks;
    uint8_t frame;
};
ANK_CONFIG_STRUCT(plagued_corpse_frame_t, wait_ticks, frame)

// OG figure/plagues.c figure_plague_citizen_action: leaves its sick house cross-country to the nearest road,
// roams for wait_ticks, infects the houses around it; a herbalist or a Bast priest (Bast complex with altar)
// on the same tile ends it (OG military.c figure_combat_attack_figure_at).
class figure_plagued_citizen : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_PLAGUED_CITIZEN, figure_plagued_citizen)
    figure_plagued_citizen(figure *f) : figure_impl(f) {}

    struct static_params : public figure_static_params {
        int16_t spawn_wait_ticks;
        uint8_t road_radius;
        svector<plagued_corpse_frame_t, 16> corpse_frames;
    } FIGURE_STATIC_DATA_T;

    virtual void on_create() override;
    virtual void figure_action() override;
    virtual void figure_roaming_action() override {}
    virtual void figure_dying_action() override;
    virtual void update_animation() override;
    virtual void main_image_update() override;
    virtual int provide_service() override;
    virtual bool ignores_roadblocks() const override { return true; }

    // OG city_disasters.c city_health_start_plague_at_house: one carrier on the house tile. Returns figure id, or 0.
    static int create_at_house(building& house);

    // OG military.c: herbalist / Bast priest meets a carrier on one tile; true when one of them died.
    static bool cure_on_meeting(figure& f, figure& opponent);

    // gameplay_change_plagued_citizen_remake: cure carriers within a tile of a herbalist / complex priest stop.
    static int cure_nearby(tile2i tile, int radius = 1);
};
ANK_CONFIG_STRUCT(figure_plagued_citizen::static_params, spawn_wait_ticks, road_radius, corpse_frames)
