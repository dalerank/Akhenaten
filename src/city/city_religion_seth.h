#pragma once

#include "city_religion.h"

class god_seth_t : public city_god {
public:
    virtual void perform_major_curse() override;
    virtual void perform_minor_curse() override;

    void perform_hailstorm();
    int invasion_start_from_seth();
    void ships_destruction();
    bool formation_legion_curse();
    void sink_all_ships();
    bool perform_fort_destruction();
};

extern god_seth_t god_seth;