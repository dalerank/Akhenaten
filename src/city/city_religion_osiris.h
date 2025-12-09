#pragma once

#include "city_religion.h"

class god_osiris_t : public city_god {
public:
    int8_t sank_ships;

    virtual void perform_major_curse() override;
    virtual void perform_minor_curse() override;

    void perform_worse_flood();
    void perform_locusts();
    void perform_flood_will_destroy_farms();
    void perform_lower_flood_quality();

    bool create_shipwreck_flotsam();
};

extern god_osiris_t god_osiris;

