#pragma once

#include "building/building_mine.h"

class building_mine_gold : public building_mine {
public:
    BUILDING_METAINFO(BUILDING_GOLD_MINE, building_mine_gold, building_mine)

    struct static_params : public building_static_params {
        uint16_t production_divider;
    } BUILDING_STATIC_DATA_T;

    virtual int produce_uptick_per_day() const override;
    virtual void update_production() override;
    virtual void on_before_collapse() override;
};
ANK_CONFIG_STRUCT(building_mine_gold::static_params, production_divider)

