#pragma once

#include "city_religion.h"

class god_bast_t : public city_god {
public:
    virtual void perform_major_curse() override;
    virtual void perform_minor_curse() override;

    bool perform_houses_destruction();
    void perform_malaria_plague();
};

extern god_bast_t god_bast;

