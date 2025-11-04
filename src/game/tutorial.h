#pragma once 

#include "core/buffer.h"
#include "city/constants.h"
#include "building/building_type.h"
#include "core/xstring.h"
#include "core/svector.h"

struct tutorial_stage_t {
#define _RR(a) const xstring a = #a;
    _RR(disable_all)
    _RR(tutorial_water)
    _RR(tutorial_collapse)
    _RR(tutorial_gods)
    _RR(tutorial_entertainment)
    _RR(tutorial_industry)
    _RR(tutorial_health)
    _RR(tutorial_gardens)
    _RR(tutorial_crime)
    _RR(tutorial_finance)
    _RR(tutorial_trading)
    _RR(tutorial_education)
#undef _RR
};

struct tutorial_t {
    using tutorial_list = svector<tutorial_t *, 16>;

    tutorial_t();
    
    virtual int missionid() const = 0;
    virtual void init() = 0;
    virtual void reset() = 0;
    virtual void update_step(xstring s) = 0;
    virtual xstring goal_text() = 0;

    static tutorial_list &list();
};

struct tutorial_flags_t {
    struct {
        bool started;
        bool reserve_2;
        bool reserve_3;
        bool gamemeat_stored;
        bool building_collapsed;
        bool architector_built;
        bool bazaar_built;
    } tutorial_1;

    struct {
        bool started;
        bool population_250_reached;
        bool population_450_reached;
        bool reserved_1;
        bool gold_mined;
        bool temples_built;
        bool crime;
    } tutorial_2;

    struct {
        bool started;
        bool figs_stored;
        bool pottery_made_1;
        bool pottery_made_2;
        bool disease;
        int pottery_made_year;
    } tutorial_3;

    struct {
        bool started;
        bool beer_made;
        bool tax_collector_built;
    } tutorial_4;

    struct {
        bool started;
        bool spacious_apartment;
        bool papyrus_made;
        bool bricks_bought;
        bool can_trade_finally;
    } tutorial_5;

    struct {
        bool started;

    } tutorial_6;

    struct {
        bool flags[41];
        //
        bool crime;
        bool tut7_start;
        bool tut8_start;
    } pharaoh;

    void update_starting_message();
    void on_crime();
};

extern tutorial_flags_t g_tutorials_flags;
extern const tutorial_stage_t tutorial_stage;

bool tutorial_init(bool clear_all_flags, bool custom);

e_availability mission_empire_availability(int mission);

void tutorial_map_update(int tut);

xstring tutorial_get_immediate_goal_text();

void tutorial_update_step(xstring step);