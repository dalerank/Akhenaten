#pragma once

#include "building/building.h"

class building_house : public building_impl {
public:
    building_house(building &b) : building_impl(b) {}
    virtual building_house *dcast_house() override { return this; }

    //virtual void on_create(int orientation) override;
    //virtual void on_place(int orientation, int variant) override;
    virtual void on_place_checks() override;
    virtual bool is_workshop() const override { return true; }
    //virtual void window_info_background(object_info &c) override;
    virtual e_sound_channel_city sound_channel() const { return SOUND_CHANNEL_CITY_STATUE; }
    virtual void on_undo() override;

    inline int house_population() const { return base.house_population; }
    inline void change_population(int delta) { base.house_population += delta; }
    inline e_house_level house_level() const { return base.subtype.house_level; }
    void change_to_vacant_lot();
    void add_population(int num_people);

    static void create_vacant_lot(tile2i tile, int image_id);
};

class building_house_vacant: public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_VACANT_LOT, building_house_vacant)
    building_house_vacant(building &b) : building_house(b) {}
};

void building_house_change_to(building* house, e_building_type type);

void building_house_merge(building* house);

int building_house_can_expand(building* house, int num_tiles);

void building_house_expand_to_large_insula(building* house);
void building_house_expand_to_large_villa(building* house);
void building_house_expand_to_large_palace(building* house);

void building_house_devolve_from_large_insula(building* house);
void building_house_devolve_from_large_villa(building* house);
void building_house_devolve_from_large_palace(building* house);

void building_house_check_for_corruption(building* house);
