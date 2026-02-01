#pragma once

#include "building/building_house_demands.h"
#include "building/building_house_model.h"
#include "building/building.h"
#include "grid/building.h"
#include "grid/grid.h"

enum e_house_progress { 
    e_house_evolve = 1,
    e_house_none = 0, 
    e_house_decay = -1
};

#define HOUSE_METAINFO(type, clsid) BUILDING_METAINFO(type, clsid, building_house);

// Base class that encapsulates shared behaviour for every housing tier.
// Derived classes only override evolution thresholds or provide different art/models.
class building_house : public building_impl {
public:
    building_house(building &b) : building_impl(b) {}
    virtual building_house *dcast_house() override { return this; }

    // Static configuration that is populated from configs for each specific house tier.
    struct house_params_t {
        model_house model;
        bool can_merge;
        animations_t variants;
        animations_t variants_merged;
        animations_t variants_merged_inside;
    };

    // Persistent state for a single house instance.
    // Counts and timers here drive evolution logic.
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
        uint8_t nobles_with_bad_teeth;
        uint8_t toothache_probability;
        building_id worst_desirability_building_id;
        uint16_t image_id;
        uint8_t fade_alpha;
        xstring evolve_text;
        xstring image_key;
    } BUILDING_RUNTIME_DATA_T;

    virtual void on_create(int orientation) override;
    //virtual void on_place(int orientation, int variant) override;
    virtual void on_destroy() override;
    virtual void on_post_load() override;
    virtual void on_place_checks() override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_STATUE; }
    virtual void on_undo() override;
    virtual void update_week() override;
    virtual void update_count() const override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
    virtual bool evolve(house_demands* demands) = 0;
    virtual int get_fire_risk(int value) const override;
    virtual void highlight_waypoints() override;
    virtual bvariant get_property(const xstring &domain, const xstring &name) const override; 
    virtual void spawn_figure() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual bool target_route_tile_blocked(int grid_offset) const override;
    
    void update_fade_alpha();

    inline short house_population() const { return runtime_data().population; }
    inline void change_population(short delta) { runtime_data().population += delta; }
    inline e_house_level house_level() const { return (e_house_level)(type() - BUILDING_HOUSE_CRUDE_HUT); }
    inline uint8_t hsize() const { return runtime_data().hsize; }
    inline bool is_nobles() const { return (house_level() >= HOUSE_COMMON_MANOR); }

    void determine_evolve_text();
    void determine_worst_desirability_building();

    void decay_services();
    void decay_tax_coverage();
    void update_monthly_nobles_toothache();

    int16_t population_room() const;
    void change_to_vacant_lot();
    bool is_vacant_lot() const;
    void add_population(int num_people);
    static void change_to(building &b, e_building_type type, bool force = false);
    void merge();
    void merge_impl();
    inline bool is_merged() const { return runtime_data().is_merged; }    
    resource_list consume_goods_weekly();
    resource_list consume_food_weekly();
    void split(int num_tiles);
    const model_house &model() const;

    e_house_progress check_evolve_desirability();
    e_house_progress has_required_goods_and_services(int for_upgrade, house_demands *demands);
    bool has_devolve_delay(int status);
    bool can_expand(int num_tiles);

    void check_for_corruption();
    e_house_progress check_requirements(house_demands *demands);

    static void create_vacant_lot(tile2i tile, int image_id);
    static const model_house &get_model(int level);
};

// --- Individual housing tiers -------------------------------------------------
// some info shared with vacant lot, so this is unique twice-config class

/**
 * First and most basic housing tier - crude hut.
 * 
 * Characteristics:
 * - Maximum population: 5 people
 * - Building size: 1x1 tile
 * - Can merge with adjacent houses (can_merge: true)
 * - Very low desirability requirements for evolution (-10)
 * - Requires no services (water, entertainment, religion, education, food)
 * - High crime risk (5) and fire risk (3)
 * - Low prosperity level (15)
 * - Tax multiplier: 2x
 * 
 * Evolution: can evolve into sturdy_hut when minimal conditions are met.
 * Devolution: cant devolve (des setup to -99).
 */
class building_house_crude_hut : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_CRUDE_HUT, building_house_crude_hut);

    struct static_params : public house_params_t, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual bool evolve(house_demands *demands) override;
};
ANK_CONFIG_STRUCT(building_house_crude_hut::static_params, 
    model, can_merge, variants, variants_merged, variants_merged_inside)

/**
 * Second housing tier - sturdy hut.
 * 
 * Characteristics:
 * - Maximum population: 7 people
 * - Building size: 1x1 tile
 * - Can merge with adjacent houses
 * - Requires basic water supply (water: 1)
 * - Improved desirability requirements for evolution (-7 to -5)
 * - Crime risk: 4, fire risk: 3
 * - Prosperity level: 20-15
 * - Tax multiplier: 2x
 * 
 * Evolution: can evolve into meager_shanty when conditions improve.
 * Devolution: can devolve at desirability below -12.
 */
class building_house_sturdy_hut : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_STURDY_HUT, building_house_sturdy_hut);

    struct static_params : public house_params_t, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual bool evolve(house_demands *demands) override;
};
ANK_CONFIG_STRUCT(building_house_sturdy_hut::static_params,
    model, can_merge, variants, variants_merged, variants_merged_inside)

/**
 * Third housing tier - meager shanty.
 * 
 * Characteristics:
 * - Maximum population: 9 people
 * - Building size: 1x1 tile
 * - Can merge with adjacent houses
 * - Requires water supply and food (water: 1, food: 1, food_types: 1)
 * - Very high fire risk (20) - due to primitive materials
 * - Desirability requirements for evolution: -2 to 0
 * - Crime risk: 3
 * - Prosperity level: 25-20
 * - Tax multiplier: 3x-2x
 * 
 * Evolution: can evolve into common_shanty when conditions improve.
 * Devolution: can devolve at desirability below -9 to -7.
 */
class building_house_meager_shanty : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_MEAGER_SHANTY, building_house_meager_shanty);

    struct static_params : public house_params_t, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual bool evolve(house_demands *demands) override;
};
ANK_CONFIG_STRUCT(building_house_meager_shanty::static_params,
    model, can_merge, variants, variants_merged, variants_merged_inside)

/**
 * Fourth housing tier - common shanty.
 * 
 * Characteristics:
 * - Maximum population: 11 people
 * - Building size: 1x1 tile
 * - Can merge with adjacent houses
 * - Requires water supply, food, and religion (water: 1, food: 1, religion: 1)
 * - Desirability requirements for evolution: 2-4
 * - Crime risk: 2, fire risk: 4, damage risk: 4
 * - Prosperity level: 30-25
 * - Tax multiplier: 3x-2x
 * 
 * Evolution: can evolve into rough_cottage when conditions improve.
 * Devolution: can devolve at desirability below -4 to -2.
 */
class building_house_common_shanty : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_COMMON_SHANTY, building_house_common_shanty);

    struct static_params : public house_params_t, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual bool evolve(house_demands *demands) override;
};
ANK_CONFIG_STRUCT(building_house_common_shanty::static_params,
    model, can_merge, variants, variants_merged, variants_merged_inside)

/**
 * Fifth housing tier - rough cottage.
 * 
 * Characteristics:
 * - Maximum population: 13 people
 * - Building size: 1x1 tile
 * - Can merge with adjacent houses
 * - Requires improved water supply (water: 2), food, and religion
 * - Desirability requirements for evolution: 6-9
 * - Crime risk: 1, fire risk: 5, damage risk: 3
 * - Prosperity level: 35-30
 * - Tax multiplier: 3x-2x
 * - Improved food storage (food_storage_multiplier: 5)
 * 
 * Evolution: can evolve into ordinary_cottage when conditions improve.
 * Devolution: can devolve at desirability below 0-2.
 */
class building_house_rough_cottage : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_ROUGH_COTTAGE, building_house_rough_cottage);
    
    struct static_params : public house_params_t, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual bool evolve(house_demands *demands) override;
};
ANK_CONFIG_STRUCT(building_house_rough_cottage::static_params,
    model, can_merge, variants, variants_merged, variants_merged_inside)

/**
 * Sixth housing tier - ordinary cottage.
 * 
 * Characteristics:
 * - Maximum population: 15 people
 * - Building size: 1x1 tile
 * - Can merge with adjacent houses
 * - Requires entertainment (entertainment: 10), improved water supply, food, and religion
 * - Desirability requirements for evolution: 10-13
 * - Crime risk: 0, fire risk: 4
 * - Prosperity level: 40-35
 * - Tax multiplier: 3x-2x
 * 
 * Evolution: can evolve into modest_homestead when conditions improve.
 * Devolution: can devolve at desirability below 4-7.
 */
class building_house_ordinary_cottage : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_ORDINARY_COTTAGE, building_house_ordinary_cottage);

    struct static_params : public house_params_t, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual bool evolve(house_demands *demands) override;
};
ANK_CONFIG_STRUCT(building_house_ordinary_cottage::static_params,
    model, can_merge, variants, variants_merged, variants_merged_inside)

/**
 * Seventh housing tier - modest homestead.
 * 
 * Characteristics:
 * - Maximum population: 16 people
 * - Building size: 1x1 tile
 * - Can merge with adjacent houses
 * - Requires entertainment (entertainment: 12-20), water supply, food, religion, and pottery (pottery: 1)
 * - Desirability requirements for evolution: 14-17
 * - Fire risk: 4, damage risk: 4
 * - Prosperity level: 45-40
 * - Tax multiplier: 4x-3x
 * 
 * Evolution: can evolve into spacious_homestead when conditions improve.
 * Devolution: can devolve at desirability below 8-11.
 */
class building_house_modest_homestead : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_MODEST_HOMESTEAD, building_house_modest_homestead);

    struct static_params : public house_params_t, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual bool evolve(house_demands *demands) override;
};
ANK_CONFIG_STRUCT(building_house_modest_homestead::static_params,
    model, can_merge, variants, variants_merged, variants_merged_inside)

/**
 * Eighth housing tier - spacious homestead.
 * 
 * Characteristics:
 * - Maximum population: 17 people
 * - Building size: 1x1 tile
 * - Can merge with adjacent houses
 * - Requires entertainment (entertainment: 14-25), water supply, food, religion, pottery, and health (health: 1)
 * - Desirability requirements for evolution: 18-21
 * - Fire risk: 4, damage risk: 4
 * - Prosperity level: 55-50
 * - Tax multiplier: 4x-3x
 * 
 * Evolution: can evolve into modest_apartment when conditions improve.
 * Devolution: can devolve at desirability below 12-15.
 */
class building_house_spacious_homestead : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_SPACIOUS_HOMESTEAD, building_house_spacious_homestead);

    struct static_params : public house_params_t, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual bool evolve(house_demands *demands) override;
};
ANK_CONFIG_STRUCT(building_house_spacious_homestead::static_params,
    model, can_merge, variants, variants_merged, variants_merged_inside)

/**
 * Ninth housing tier - modest apartment.
 * 
 * Characteristics:
 * - Maximum population: 18 people
 * - Building size: 1x1 tile
 * - Can merge with adjacent houses
 * - Requires entertainment (entertainment: 16-30), water supply, food, religion, pottery, health, and beer (beer: 1)
 * - Desirability requirements for evolution: 22-26
 * - Fire risk: 4, damage risk: 5
 * - Prosperity level: 60-55
 * - Tax multiplier: 4x-3x
 * 
 * Evolution: can evolve into spacious_apartment when conditions improve.
 * Devolution: can devolve at desirability below 16-19.
 */
class building_house_modest_apartment : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_MODEST_APARTMENT, building_house_modest_apartment);

    struct static_params : public house_params_t, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual bool evolve(house_demands *demands) override;
};
ANK_CONFIG_STRUCT(building_house_modest_apartment::static_params,
    model, can_merge, variants, variants_merged, variants_merged_inside)

/**
 * Tenth housing tier - spacious apartment.
 * 
 * Characteristics:
 * - Maximum population: 19 people
 * - Building size: 1x1 tile
 * - Can merge with adjacent houses
 * - Requires entertainment (entertainment: 18-35), water supply, food, religion, pottery, health, beer, and physician (physician: 1)
 * - Desirability requirements for evolution: 29-33
 * - Fire risk: 4, damage risk: 5
 * - Prosperity level: 70-60
 * - Tax multiplier: 4x-3x
 * 
 * Evolution: can evolve into common_residence when conditions improve.
 *          Can also expand to common_residence via expand_to_common_residence() method.
 * Devolution: can devolve at desirability below 19-23.
 */
class building_house_spacious_apartment : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_SPACIOUS_APARTMENT, building_house_spacious_apartment);

    struct static_params : public house_params_t, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual bool evolve(house_demands *demands) override;
    void expand_to_common_residence();
};
ANK_CONFIG_STRUCT(building_house_spacious_apartment::static_params,
    model, can_merge, variants, variants_merged, variants_merged_inside)

/**
 * Eleventh housing tier - common residence.
 * 
 * Characteristics:
 * - Maximum population: 80 people (significant increase!)
 * - Building size: 1x1 tile
 * - Can merge with adjacent houses
 * - Requires entertainment (entertainment: 20-40), water supply, food, religion, education (education: 1),
 *   pottery, health, beer, and physician
 * - Desirability requirements for evolution: 37-41
 * - Fire risk: 4, damage risk: 4
 * - Prosperity level: 80-70
 * - Tax multiplier: 5x-4x
 * - Improved food storage (food_storage_multiplier: 6)
 * 
 * Evolution: can evolve into spacious_residence when conditions improve.
 * Devolution: can devolve at desirability below 26-30.
 */
class building_house_common_residence : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_COMMON_RESIDENCE, building_house_common_residence);

    struct static_params : public house_params_t, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual bool evolve(house_demands *demands) override;
};
ANK_CONFIG_STRUCT(building_house_common_residence::static_params,
    model, can_merge, variants, variants_merged, variants_merged_inside)

/**
 * Twelfth housing tier - spacious residence.
 * 
 * Characteristics:
 * - Maximum population: 84 people
 * - Building size: 1x1 tile
 * - Can merge with adjacent houses
 * - Requires entertainment (entertainment: 25-45), water supply, food, religion, education,
 *   pottery, health, beer, physician, dentist (dentist: 1), and food variety (food_types: 2)
 * - Desirability requirements for evolution: 45-50
 * - Fire risk: 4, damage risk: 4
 * - Prosperity level: 90-80
 * - Tax multiplier: 5x-4x
 * 
 * Evolution: can evolve into elegant_residence when conditions improve.
 * Devolution: can devolve at desirability below 33-37.
 */
class building_house_spacious_residence : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_SPACIOUS_RESIDENCE, building_house_spacious_residence);

    struct static_params : public house_params_t, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual bool evolve(house_demands *demands) override;
};
ANK_CONFIG_STRUCT(building_house_spacious_residence::static_params,
    model, can_merge, variants, variants_merged, variants_merged_inside)

/**
 * Thirteenth housing tier - elegant residence.
 * 
 * Characteristics:
 * - Maximum population: 88 people
 * - Building size: 1x1 tile
 * - Can merge with adjacent houses
 * - Requires entertainment (entertainment: 30-50), water supply, food, religion, education,
 *   pottery, health, beer, physician, dentist, linen (linen: 1), and food variety
 * - Desirability requirements for evolution: 50-55
 * - Fire risk: 3, damage risk: 5
 * - Prosperity level: 100-90
 * - Tax multiplier: 6x-5x
 * 
 * Evolution: can evolve into fancy_residence when conditions improve.
 * Devolution: can devolve at desirability below 40-45.
 */
class building_house_elegant_residence : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_ELEGANT_RESIDENCE, building_house_elegant_residence);

    struct static_params : public house_params_t, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual bool evolve(house_demands *demands) override;
};
ANK_CONFIG_STRUCT(building_house_elegant_residence::static_params,
    model, can_merge, variants, variants_merged, variants_merged_inside)

/**
 * Fourteenth housing tier - fancy residence.
 * 
 * Characteristics:
 * - Maximum population: 92 people
 * - Building size: 1x1 tile
 * - Can merge with adjacent houses
 * - Requires entertainment (entertainment: 35-55), water supply, food, improved religion (religion: 2),
 *   education, pottery, health, beer, physician, dentist, linen, and food variety
 * - Desirability requirements for evolution: 55-60
 * - Fire risk: 3, damage risk: 5
 * - Prosperity level: 120-100
 * - Tax multiplier: 6x-5x
 * 
 * Evolution: can evolve into common_manor when conditions improve.
 *          Can also expand to common_manor via expand_to_common_manor() method.
 * Devolution: can devolve at desirability below 45-50.
 */
class building_house_fancy_residence : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_FANCY_RESIDENCE, building_house_fancy_residence);

    struct static_params : public house_params_t, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual bool evolve(house_demands *demands) override;
    void expand_to_common_manor();
};
ANK_CONFIG_STRUCT(building_house_fancy_residence::static_params,
    model, can_merge, variants, variants_merged, variants_merged_inside)

/**
 * Fifteenth housing tier - common manor (beginning of nobility level).
 * 
 * Characteristics:
 * - Maximum population: 100 people
 * - Building size: 1x1 tile
 * - CANNOT merge with adjacent houses (can_merge: false)
 * - Requires entertainment (entertainment: 40-60), water supply, food, improved religion,
 *   education, pottery, health, beer, physician, dentist, linen, jewelry (jewelry: 1), and food variety
 * - Desirability requirements for evolution: 60-65
 * - Fire risk: 2, damage risk: 6
 * - Prosperity level: 650-600 (very high!)
 * - Tax multiplier: 13x-12x (significantly higher)
 * 
 * Evolution: can evolve into spacious_manor when conditions improve.
 * Devolution: can devolve at desirability below 47-52.
 *            Also has devolve_to_fancy_residence() method for forced devolution.
 * Special features: has monthly update (update_month()) for handling special nobility logic.
 */
class building_house_common_manor : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_COMMON_MANOR, building_house_common_manor);

    struct static_params : public house_params_t, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual bool evolve(house_demands *demands) override;
    virtual void update_month() override;
    void devolve_to_fancy_residence();
};
ANK_CONFIG_STRUCT(building_house_common_manor::static_params,
    model, can_merge, variants, variants_merged, variants_merged_inside)

/**
 * Sixteenth housing tier - spacious manor.
 * 
 * Characteristics:
 * - Maximum population: 108 people
 * - Building size: 1x1 tile
 * - CANNOT merge with adjacent houses
 * - Requires entertainment (entertainment: 45-65), water supply, food, improved religion,
 *   education, pottery, improved health (health: 2), beer, physician, dentist,
 *   linen, jewelry, and food variety
 * - Desirability requirements for evolution: 64-70
 * - Fire risk: 2, damage risk: 6
 * - Prosperity level: 750-700
 * - Tax multiplier: 14x-13x
 * 
 * Evolution: can evolve into elegant_manor when conditions improve.
 * Devolution: can devolve at desirability below 50-55.
 * Special features: has monthly update (update_month()) for handling special nobility logic.
 */
class building_house_spacious_manor : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_SPACIOUS_MANOR, building_house_spacious_manor);

    struct static_params : public house_params_t, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual bool evolve(house_demands *demands) override;
    virtual void update_month() override;
};
ANK_CONFIG_STRUCT(building_house_spacious_manor::static_params,
    model, can_merge, variants, variants_merged, variants_merged_inside)

/**
 * Seventeenth housing tier - elegant manor.
 * 
 * Characteristics:
 * - Maximum population: 116 people
 * - Building size: 1x1 tile
 * - CANNOT merge with adjacent houses
 * - Requires entertainment (entertainment: 50-70), water supply, food, improved religion (religion: 3),
 *   improved education (education: 2), pottery, improved health, beer, physician,
 *   dentist, linen, jewelry, and food variety
 * - Desirability requirements for evolution: 70-76
 * - Fire risk: 2, damage risk: 6
 * - Prosperity level: 850-800
 * - Tax multiplier: 15x-14x
 * 
 * Evolution: can evolve into stately_manor when conditions improve.
 * Devolution: can devolve at desirability below 55-62.
 * Special features: has monthly update (update_month()) for handling special nobility logic.
 */
class building_house_elegant_manor : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_ELEGANT_MANOR, building_house_elegant_manor);

    struct static_params : public house_params_t, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual bool evolve(house_demands *demands) override;
    virtual void update_month() override;
};
ANK_CONFIG_STRUCT(building_house_elegant_manor::static_params,
    model, can_merge, variants, variants_merged, variants_merged_inside)

/**
 * Eighteenth housing tier - stately manor.
 * 
 * Characteristics:
 * - Maximum population: 124 people
 * - Building size: 1x1 tile
 * - CANNOT merge with adjacent houses
 * - Requires entertainment (entertainment: 55-80), water supply, food, improved religion (religion: 3),
 *   improved education, pottery, improved health, beer, physician, dentist,
 *   linen, jewelry, and food variety
 * - Desirability requirements for evolution: 75-82
 * - Fire risk: 2, damage risk: 6
 * - Prosperity level: 950-900
 * - Tax multiplier: 16x-15x
 * 
 * Evolution: can evolve into modest_estate when conditions improve.
 *          Can also expand to modest_estate via expand_to_modest_estate() method.
 * Devolution: can devolve at desirability below 64-70.
 * Special features: has monthly update (update_month()) for handling special nobility logic.
 */
class building_house_stately_manor : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_STATELY_MANOR, building_house_stately_manor);

    struct static_params : public house_params_t, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual bool evolve(house_demands *demands) override;
    virtual void update_month() override;
    void expand_to_modest_estate();
};
ANK_CONFIG_STRUCT(building_house_stately_manor::static_params,
    model, can_merge, variants, variants_merged, variants_merged_inside)

/**
 * Nineteenth housing tier - modest estate (highest nobility level).
 * 
 * Characteristics:
 * - Maximum population: 184 people (very large!)
 * - Building size: 1x1 tile
 * - CANNOT merge with adjacent houses
 * - Requires entertainment (entertainment: 65-90), water supply, food, improved religion,
 *   improved education, pottery, improved health, beer, physician, dentist,
 *   linen, improved jewelry (jewelry: 2), and food variety
 * - Desirability requirements for evolution: 85-92
 * - Fire risk: 2, damage risk: 6
 * - Prosperity level: 2000-1900 (extremely high!)
 * - Tax multiplier: 17x-16x
 * 
 * Evolution: can evolve into palatial_estate when conditions improve.
 * Devolution: can devolve at desirability below 65-72.
 *            Also has devolve_to_statel_manor() method for forced devolution.
 * Special features: has monthly update (update_month()) for handling special nobility logic.
 */
class building_house_modest_estate : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_MODEST_ESTATE, building_house_modest_estate);

    struct static_params : public house_params_t, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual bool evolve(house_demands *demands) override;
    virtual void update_month() override;
    void devolve_to_statel_manor();
};
ANK_CONFIG_STRUCT(building_house_modest_estate::static_params,
    model, can_merge, variants, variants_merged, variants_merged_inside)

/**
 * Twentieth housing tier - palatial estate (maximum housing level).
 * 
 * Characteristics:
 * - Maximum population: 200 people (maximum!)
 * - Building size: 1x1 tile
 * - CANNOT merge with adjacent houses
 * - Requires entertainment (entertainment: 75-100), water supply, food, improved religion,
 *   improved education, pottery, improved health, beer, physician, dentist,
 *   linen, improved jewelry, and extended food variety (food_types: 2-3)
 * - Desirability requirements for evolution: 100 (maximum - further evolution impossible)
 * - Fire risk: 1 (minimal!), damage risk: 7
 * - Prosperity level: 2300-2200 (maximum!)
 * - Tax multiplier: 18x-17x (maximum!)
 * 
 * Evolution: this is the final housing tier, further evolution is impossible.
 * Devolution: can devolve at desirability below 80-87.
 * Special features: has monthly update (update_month()) for handling special nobility logic.
 *                  Represents the highest level of luxury and comfort in the game.
 */
class building_house_palatial_estate : public building_house {
public:
    HOUSE_METAINFO(BUILDING_HOUSE_PALATIAL_ESTATE, building_house_palatial_estate);

    struct static_params : public house_params_t, public building_static_params {
    } BUILDING_STATIC_DATA_T;

    virtual bool evolve(house_demands *demands) override;
    virtual void update_month() override;
};
ANK_CONFIG_STRUCT(building_house_palatial_estate::static_params,
    model, can_merge, variants, variants_merged, variants_merged_inside)

// ----------------------------------------------------------------------
// Helpers that iterate over all valid houses. They are used by various
// gameplay systems (overlays, advisors, economy calculations).
template<typename T>
void buildings_house_do(T func) {
    for (auto it = building_begin(), end = building_end(); it != end; ++it) {
        auto house = it->dcast_house();
        if (house) {
            func(house);
        }
    }
}

template<typename T, typename Processed>
void buildings_house_in_radius_do(tile2i center, int radius, Processed* processed_buildings, T func) {
    grid_area area = map_grid_get_area(center, 1, radius);
    for (int yy = area.tmin.y(); yy <= area.tmax.y(); yy++) {
        for (int xx = area.tmin.x(); xx <= area.tmax.x(); xx++) {
            tile2i current_tile(xx, yy);
            int grid_offset = current_tile.grid_offset();
            int building_id = map_building_at(grid_offset);

            if (!building_id) {
                continue;
            }

            if (processed_buildings && processed_buildings->find(building_id) != processed_buildings->end()) {
                continue;
            }

            building *b = building_get(building_id);
            auto house = b->dcast_house();

            if (house) {
                if (processed_buildings) {
                    processed_buildings->insert({ building_id, true });
                }

                func(house);
            }
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