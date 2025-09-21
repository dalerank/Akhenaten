#pragma once

#include "building/building_house_demands.h"
#include "building/building.h"

enum e_house_progress { 
    e_house_evolve = 1,
    e_house_none = 0, 
    e_house_decay = -1
};

struct model_house;

#define HOUSE_METAINFO(type, clsid)                                                                 \
    BUILDING_METAINFO(type, clsid, building_house);                                                 \
    using static_params = static_params_t<clsid>;                                                   \
    static const static_params &current_params() { return (const static_params &)params(TYPE); }

class building_house : public building_impl {
public:
    building_house(building &b) : building_impl(b) {}
    virtual building_house *dcast_house() override { return this; }

    template<typename T>
    struct static_params_t : buildings::model_t<T> {
    };

    struct runtime_data_t : no_copy_assignment {
        //e_house_level level;
        uint16_t foods[8];
        uint16_t inventory[8];
        uint16_t highest_population;
        uint16_t unreachable_ticks;
        uint16_t last_update_day;
        building_id tax_collector_id;
        uint16_t population;
        int16_t tax_income_or_storage;
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
        uint8_t bazaar_access;
        uint8_t fancy_bazaar_access;
        uint8_t water_supply;
        uint8_t house_happiness;
        uint8_t criminal_active;
        uint8_t tax_coverage;
        uint8_t days_without_food;
        uint8_t hsize;
        uint8_t drunkard_active;
        building_id worst_desirability_building_id;
        xstring evolve_text;
    };

    virtual void on_create(int orientation) override;
    //virtual void on_place(int orientation, int variant) override;
    virtual void on_destroy() override;
    virtual void on_place_checks() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_STATUE; }
    virtual void on_undo() override;
    virtual void update_count() const override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
    virtual bool evolve(house_demands* demands) = 0;
    virtual int get_fire_risk(int value) const override;
    virtual void highlight_waypoints() override;
    virtual bvariant get_property(const xstring &domain, const xstring &name) const override; 
    virtual void spawn_figure() override;

    inline short house_population() const { return runtime_data().population; }
    inline void change_population(short delta) { runtime_data().population += delta; }
    inline e_house_level house_level() const { return (e_house_level)(type() - BUILDING_HOUSE_CRUDE_HUT); }
    inline uint8_t hsize() const { return runtime_data().hsize; }
    inline bool is_nobles() const { return (house_level() >= HOUSE_COMMON_MANOR); }

    void determine_evolve_text();
    void determine_worst_desirability_building();

    void decay_services();
    void decay_tax_coverage();

    int16_t population_room() const;
    void change_to_vacant_lot();
    bool is_vacant_lot() const;
    void add_population(int num_people);
    static void change_to(building &b, e_building_type type);
    void merge();
    void merge_impl();
    inline bool is_merged() const { return runtime_data().is_merged; }
    resource_list consume_resources();
    resource_list consume_food();
    void split(int num_tiles);
    const model_house &model() const;

    e_house_progress check_evolve_desirability();
    e_house_progress has_required_goods_and_services(int for_upgrade, house_demands *demands);
    bool has_devolve_delay(int status);
    bool can_expand(int num_tiles);

    void check_for_corruption();
    e_house_progress check_requirements(house_demands *demands);

    static void create_vacant_lot(tile2i tile, int image_id);

    runtime_data_t &runtime_data() { return *(runtime_data_t *)base.runtime_data; }                     
    const runtime_data_t &runtime_data() const { return *(runtime_data_t *)base.runtime_data; }
};

class building_house_crude_hut : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_CRUDE_HUT, building_house_crude_hut);

    virtual bool evolve(house_demands *demands) override;
};

class building_house_sturdy_hut : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_STURDY_HUT, building_house_sturdy_hut);

    virtual bool evolve(house_demands *demands) override;
};

class building_house_meager_shanty : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_MEAGER_SHANTY, building_house_meager_shanty);

    virtual bool evolve(house_demands *demands) override;
};

class building_house_common_shanty : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_COMMON_SHANTY, building_house_common_shanty);

    virtual bool evolve(house_demands *demands) override;
};

class building_house_rough_cottage : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_ROUGH_COTTAGE, building_house_rough_cottage);

    virtual bool evolve(house_demands *demands) override;
};

class building_house_ordinary_cottage : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_ORDINARY_COTTAGE, building_house_ordinary_cottage);

    virtual bool evolve(house_demands *demands) override;
};

class building_house_modest_homestead : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_MODEST_HOMESTEAD, building_house_modest_homestead);

    virtual bool evolve(house_demands *demands) override;
};

class building_house_spacious_homestead : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_SPACIOUS_HOMESTEAD, building_house_spacious_homestead);

    virtual bool evolve(house_demands *demands) override;
};

class building_house_modest_apartment : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_MODEST_APARTMENT, building_house_modest_apartment);

    virtual bool evolve(house_demands *demands) override;
};

class building_house_spacious_apartment : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_SPACIOUS_APARTMENT, building_house_spacious_apartment);

    virtual bool evolve(house_demands *demands) override;
    void expand_to_common_residence();
};

class building_house_common_residence : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_COMMON_RESIDENCE, building_house_common_residence);

    virtual bool evolve(house_demands *demands) override;
};

class building_house_spacious_residence : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_SPACIOUS_RESIDENCE, building_house_spacious_residence);

    virtual bool evolve(house_demands *demands) override;
};

class building_house_elegant_residence : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_ELEGANT_RESIDENCE, building_house_elegant_residence);

    virtual bool evolve(house_demands *demands) override;
};

class building_house_fancy_residence : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_FANCY_RESIDENCE, building_house_fancy_residence);

    virtual bool evolve(house_demands *demands) override;
    void expand_to_common_manor();
};

class building_house_common_manor : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_COMMON_MANOR, building_house_common_manor);

    virtual bool evolve(house_demands *demands) override;
    void devolve_to_fancy_residence();
};

class building_house_spacious_manor : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_SPACIOUS_MANOR, building_house_spacious_manor);

    virtual bool evolve(house_demands *demands) override;
};

class building_house_elegant_manor : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_ELEGANT_MANOR, building_house_elegant_manor);

    virtual bool evolve(house_demands *demands) override;
};

class building_house_stately_manor : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_STATELY_MANOR, building_house_stately_manor);

    virtual bool evolve(house_demands *demands) override;
    void expand_to_modest_estate();
};

class building_house_modest_estate : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_MODEST_ESTATE, building_house_modest_estate);

    virtual bool evolve(house_demands *demands) override;
    void devolve_to_statel_manor();
};

class building_house_palatial_estate : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_PALATIAL_ESTATE, building_house_palatial_estate);

    virtual bool evolve(house_demands *demands) override;
};

template<typename T>
void buildings_house_do(T func) {
    for (auto it = building_begin(), end = building_end(); it != end; ++it) {
        auto house = it->dcast_house();
        if (house) {
            func(house);
        }
    }
}

template<typename T>
void buildings_houses_get(T &arr) {
    arr.clear();

    buildings_house_do([&] (building_house *house) {
        if (house->is_valid() && house->hsize())
            arr.push_back(house);
    });
}