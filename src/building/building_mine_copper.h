#pragma once

#include "building/building_mine.h"
#include "construction/build_planner.h"

class building_mine_copper : public building_mine {
public:
    BUILDING_METAINFO(BUILDING_COPPER_MINE, building_mine_copper, building_mine)

    struct preview : building_planer_renderer {
        virtual bool is_need_flag(build_planner& p, e_building_flags flag) const override;
    };

    virtual int produce_uptick_per_day() const override { return base.num_workers > 0 ? std::max<int>(1, base.num_workers / 2) : 0; }
    virtual void on_before_collapse() override;
};

