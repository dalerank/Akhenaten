#pragma once

#include "city/houses.h"
#include "building/building.h"

enum e_house_progress { 
    e_house_evolve = 1,
    e_house_none = 0, 
    e_house_decay = -1
};

class building_house : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_NONE, building_house_vacant)

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
    void change_to(e_building_type type);
    void merge();
    void merge_impl();
    void consume_resources();

    e_house_progress check_evolve_desirability();
    e_house_progress has_required_goods_and_services(int for_upgrade, house_demands *demands);
    bool has_devolve_delay(int status);
    int building_house_can_expand(int num_tiles);

    e_house_progress check_requirements(house_demands *demands);

    static void create_vacant_lot(tile2i tile, int image_id);
};

class building_house_crude_hut : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_CRUDE_HUT, building_house_crude_hut);
    building_house_crude_hut(building &b) : building_house(b) {}
};

class building_house_sturdy_hut : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_STURDY_HUT, building_house_sturdy_hut);
    building_house_sturdy_hut(building &b) : building_house(b) {}
};

class building_house_meager_shanty : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_MEAGER_SHANTY, building_house_meager_shanty);
    building_house_meager_shanty(building &b) : building_house(b) {}
};

class building_house_common_shanty : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_COMMON_SHANTY, building_house_common_shanty);
    building_house_common_shanty(building &b) : building_house(b) {}
};

class building_house_rough_cottage : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_ROUGH_COTTAGE, building_house_rough_cottage);
    building_house_rough_cottage(building &b) : building_house(b) {}
};

class building_house_ordinary_cottage : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_ORDINARY_COTTAGE, building_house_ordinary_cottage);
    building_house_ordinary_cottage(building &b) : building_house(b) {}
};

class building_house_modest_homestead : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_MODEST_HOMESTEAD, building_house_modest_homestead);
    building_house_modest_homestead(building &b) : building_house(b) {}
};

class building_house_spacious_homestead : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_SPACIOUS_HOMESTEAD, building_house_spacious_homestead);
    building_house_spacious_homestead(building &b) : building_house(b) {}
};

class building_house_common_residence : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_COMMON_RESIDENCE, building_house_common_residence);
    building_house_common_residence(building &b) : building_house(b) {}
};

class building_house_spacious_residence : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_SPACIOUS_RESIDENCE, building_house_spacious_residence);
    building_house_spacious_residence(building &b) : building_house(b) {}
};

class building_house_elegant_residence : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_ELEGANT_RESIDENCE, building_house_elegant_residence);
    building_house_elegant_residence(building &b) : building_house(b) {}
};

class building_house_fancy_residence : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_FANCY_RESIDENCE, building_house_fancy_residence);
    building_house_fancy_residence(building &b) : building_house(b) {}
};

int building_house_can_expand(building* house, int num_tiles);

void building_house_expand_to_large_insula(building* house);
void building_house_expand_to_large_villa(building* house);
void building_house_expand_to_large_palace(building* house);

void building_house_devolve_from_large_insula(building* house);
void building_house_devolve_from_large_villa(building* house);
void building_house_devolve_from_large_palace(building* house);

void building_house_check_for_corruption(building* house);
