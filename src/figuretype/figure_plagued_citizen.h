#pragma once

#include "figure/figure.h"

class building;

enum e_plagued_citizen_action {
    ACTION_120_PLAGUED_CREATED = 120,
    ACTION_121_PLAGUED_ROAMING = 121,
};

// Plague carrier — Bast malaria / city health outbreak walker.
// Infects houses within r=2; herbalist (and Isis altar Bast priestess) remove on meet.
class figure_plagued_citizen : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_PLAGUED_CITIZEN, figure_plagued_citizen)
    figure_plagued_citizen(figure *f) : figure_impl(f) {}

    struct runtime_data_t {
        uint8_t tiles_walked;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override;
    virtual void figure_action() override;
    virtual void figure_roaming_action() override { /* free roam; no home return */ }
    virtual void update_animation() override;
    virtual int provide_service() override;
    virtual bool ignores_roadblocks() const override { return true; }

    // Spawn one carrier at house road access. Returns figure id, or 0.
    static int spawn_from_house(building &house);

    // Despawn live plagued citizens on/near tile (herbalist / Isis encounter).
    static int cure_nearby(tile2i tile, int radius = 1);
};
