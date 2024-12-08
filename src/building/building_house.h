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
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_STATUE; }
    virtual void on_undo() override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
    virtual bool evolve(house_demands* demands) = 0;
    virtual int get_fire_risk(int value) const override;
    virtual bvariant get_property(const xstring &domain, const xstring &name) const override; 

    inline short house_population() const { return base.house_population; }
    inline void change_population(short delta) { base.house_population += delta; }
    inline e_house_level house_level() const { return base.subtype.house_level; }
    void change_to_vacant_lot();
    bool is_vacant_lot() const;
    void add_population(int num_people);
    void change_to(e_building_type type);
    void merge();
    void merge_impl();
    void consume_resources();
    void split(int num_tiles);

    e_house_progress check_evolve_desirability();
    e_house_progress has_required_goods_and_services(int for_upgrade, house_demands *demands);
    bool has_devolve_delay(int status);
    bool can_expand(int num_tiles);

    void check_for_corruption();
    e_house_progress check_requirements(house_demands *demands);

    static void create_vacant_lot(tile2i tile, int image_id);
};

class building_house_crude_hut : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_CRUDE_HUT, building_house_crude_hut);
    building_house_crude_hut(building &b) : building_house(b) {}

    virtual bool evolve(house_demands *demands) override;
};

class building_house_sturdy_hut : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_STURDY_HUT, building_house_sturdy_hut);
    building_house_sturdy_hut(building &b) : building_house(b) {}

    virtual bool evolve(house_demands *demands) override;
};

class building_house_meager_shanty : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_MEAGER_SHANTY, building_house_meager_shanty);
    building_house_meager_shanty(building &b) : building_house(b) {}

    virtual bool evolve(house_demands *demands) override;
};

class building_house_common_shanty : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_COMMON_SHANTY, building_house_common_shanty);
    building_house_common_shanty(building &b) : building_house(b) {}

    virtual bool evolve(house_demands *demands) override;
};

class building_house_rough_cottage : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_ROUGH_COTTAGE, building_house_rough_cottage);
    building_house_rough_cottage(building &b) : building_house(b) {}

    virtual bool evolve(house_demands *demands) override;
};

class building_house_ordinary_cottage : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_ORDINARY_COTTAGE, building_house_ordinary_cottage);
    building_house_ordinary_cottage(building &b) : building_house(b) {}

    virtual bool evolve(house_demands *demands) override;
};

class building_house_modest_homestead : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_MODEST_HOMESTEAD, building_house_modest_homestead);
    building_house_modest_homestead(building &b) : building_house(b) {}

    virtual bool evolve(house_demands *demands) override;
};

class building_house_spacious_homestead : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_SPACIOUS_HOMESTEAD, building_house_spacious_homestead);
    building_house_spacious_homestead(building &b) : building_house(b) {}

    virtual bool evolve(house_demands *demands) override;
};

class building_house_modest_apartment : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_MODEST_APARTMENT, building_house_modest_apartment);
    building_house_modest_apartment(building &b) : building_house(b) {}

    virtual bool evolve(house_demands *demands) override;
};

class building_house_spacious_apartment : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_SPACIOUS_APARTMENT, building_house_spacious_apartment);
    building_house_spacious_apartment(building &b) : building_house(b) {}

    virtual bool evolve(house_demands *demands) override;
    void expand_to_common_residence();
};

class building_house_common_residence : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_COMMON_RESIDENCE, building_house_common_residence);
    building_house_common_residence(building &b) : building_house(b) {}

    virtual bool evolve(house_demands *demands) override;
};

class building_house_spacious_residence : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_SPACIOUS_RESIDENCE, building_house_spacious_residence);
    building_house_spacious_residence(building &b) : building_house(b) {}

    virtual bool evolve(house_demands *demands) override;
};

class building_house_elegant_residence : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_ELEGANT_RESIDENCE, building_house_elegant_residence);
    building_house_elegant_residence(building &b) : building_house(b) {}

    virtual bool evolve(house_demands *demands) override;
};

class building_house_fancy_residence : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_FANCY_RESIDENCE, building_house_fancy_residence);
    building_house_fancy_residence(building &b) : building_house(b) {}

    virtual bool evolve(house_demands *demands) override;
    void expand_to_common_manor();
};

class building_house_common_manor : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_COMMON_MANOR, building_house_common_manor);
    building_house_common_manor(building &b) : building_house(b) {}

    virtual bool evolve(house_demands *demands) override;
    void devolve_to_fancy_residence();
};

class building_house_spacious_manor : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_SPACIOUS_MANOR, building_house_spacious_manor);
    building_house_spacious_manor(building &b) : building_house(b) {}

    virtual bool evolve(house_demands *demands) override;
};

class building_house_elegant_manor : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_ELEGANT_MANOR, building_house_elegant_manor);
    building_house_elegant_manor(building &b) : building_house(b) {}

    virtual bool evolve(house_demands *demands) override;
};

class building_house_stately_manor : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_STATELY_MANOR, building_house_stately_manor);
    building_house_stately_manor(building &b) : building_house(b) {}

    virtual bool evolve(house_demands *demands) override;
    void expand_to_modest_estate();
};

class building_house_modest_estate : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_MODEST_ESTATE, building_house_modest_estate);
    building_house_modest_estate(building &b) : building_house(b) {}

    virtual bool evolve(house_demands *demands) override;
    void devolve_to_statel_manor();
};

class building_house_palatial_estate : public building_house {
public:
    BUILDING_METAINFO(BUILDING_HOUSE_PALATIAL_ESTATE, building_house_palatial_estate);
    building_house_palatial_estate(building &b) : building_house(b) {}

    virtual bool evolve(house_demands *demands) override;
};

