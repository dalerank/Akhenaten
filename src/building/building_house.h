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
    BUILDING_METAINFO_RT(BUILDING_NONE, building_house_vacant)

    building_house(building &b) : building_impl(b) {}
    virtual building_house *dcast_house() override { return this; }

    struct runtime_data_t {
        e_house_level level;
        uint16_t foods[8];
        uint16_t inventory[8];
        uint16_t highest_population;
        uint16_t unreachable_ticks;
        building_id tax_collector_id;
        uint16_t population;
        uint8_t is_merged;
        uint8_t booth_juggler;
        uint8_t bandstand_juggler;
        uint8_t bandstand_musician;
        uint8_t pavillion_musician;
        uint8_t pavillion_dancer;
        uint8_t senet_player;
        uint8_t magistrate;
        uint8_t bullfighter;
        uint8_t school;
        uint8_t library;
        uint8_t academy;
        uint8_t apothecary;
        uint8_t dentist;
        uint8_t mortuary;
        uint8_t physician;
        uint8_t temple_osiris;
        uint8_t temple_ra;
        uint8_t temple_ptah;
        uint8_t temple_seth;
        uint8_t temple_bast;
        uint8_t no_space_to_expand;
        uint8_t num_foods;
        uint8_t entertainment;
        uint8_t education;
        uint8_t health;
        uint8_t num_gods;
        uint8_t shrine_access;
        uint8_t devolve_delay;
        uint8_t evolve_text_id;
        uint8_t bazaar_access;
        uint8_t water_supply;
        uint8_t house_happiness;
        uint8_t criminal_active;
        uint8_t tax_coverage;
    };

    virtual void on_create(int orientation) override;
    //virtual void on_place(int orientation, int variant) override;
    virtual void on_place_checks() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_STATUE; }
    virtual void on_undo() override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
    virtual bool evolve(house_demands* demands) = 0;
    virtual int get_fire_risk(int value) const override;
    virtual bvariant get_property(const xstring &domain, const xstring &name) const override; 

    inline short house_population() const { return runtime_data().population; }
    inline void change_population(short delta) { runtime_data().population += delta; }
    inline e_house_level house_level() const { return runtime_data().level; }
    int16_t population_room() const;
    void change_to_vacant_lot();
    bool is_vacant_lot() const;
    void add_population(int num_people);
    void change_to(e_building_type type);
    void merge();
    void merge_impl();
    inline bool is_merged() const { return runtime_data().is_merged; }
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

