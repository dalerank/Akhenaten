#pragma once

#include "city_religion.h"

class god_ra_t : public city_god {
public:
    virtual void perform_major_curse() override;
    virtual void perform_minor_curse() override;
    virtual void perform_minor_blessing() override;

    void perform_reduced_trading();
    void perform_lower_reputation();
    void perform_no_traders();
    void perform_slightly_reduced_trading();
    void perform_slightly_lower_reputation();
    void perform_slightly_increased_trading();
    void perform_slightly_increased_reputation();
};

extern god_ra_t god_ra;

