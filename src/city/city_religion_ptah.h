#pragma once

#include "city_religion.h"

class god_ptah_t : public city_god {
public:
    virtual void perform_major_curse() override;
    virtual void perform_minor_curse() override;
    virtual void perform_minor_blessing() override;

    bool perform_industry_destruction();
    void perform_frogs();
    bool perform_warehouse_destruction();
    bool perform_industry_restock();
};

extern god_ptah_t god_ptah;

