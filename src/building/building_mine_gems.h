#pragma once

#include "building/building_mine.h"
#include <algorithm>

class building_mine_gems : public building_mine {
public:
    BUILDING_METAINFO(BUILDING_GEMSTONE_MINE, building_mine_gems, building_mine)

    virtual int produce_uptick_per_day() const override { return base.num_workers > 0 ? std::max<int>(1, base.num_workers / 3) : 0; }
};

