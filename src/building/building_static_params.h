#pragma once

#include "building_type.h"
#include "building_fwd.h"
#include "core/archive.h"
#include "city/labor_category.h"
#include "graphics/animation.h"
#include "game/difficulty.h"
#include "overlays/city_overlay_fwd.h"

struct building_static_params {
    static building_static_params dummy;
    e_building_type type;
    pcstr name;
    bool fire_proof, damage_proof;
    xstring meta_id;
    metainfo meta;
    building_input input;
    building_output output;
    int output_resource_second_rate;
    e_labor_category labor_category;
    animations_t animations;
    uint8_t building_size;
    uint8_t min_houses_coverage;
    uint16_t production_rate;
    xstring info_title_id;
    uint16_dcy cost;
    building_desirability_t desirability;
    building_crime_t crime;
    uint16_t progress_max;
    e_overlay overlay;
    uint16_t max_service;
    uint16_t max_storage_amount;

    uint8_dcy laborers;
    int8_dcy fire_risk;
    int8_dcy damage_risk;

    building_planner_update_rule planner_update_rule;
    building_planner_need_rule needs;
    xstring build_menu_text;

    void archive_unload();
    void initialize();

    virtual bool is_unique_building() const { return planner_update_rule.unique_building; }
    virtual uint16_t get_cost() const;

    inline const int first_img(const xstring &anim_key) const { return animations[anim_key].first_img(); }
    const int base_img() const;

    static void for_each(std::function<void(const building_static_params &params)> f);

    static void register_model(e_building_type, const building_static_params &);
    static const building_static_params &get(e_building_type);
    static building_static_params &ref(e_building_type e);
};
ANK_CONFIG_STRUCT(building_static_params,
    labor_category, fire_proof, damage_proof, input, output,
    fire_proof, damage_proof, animations, laborers, fire_risk, damage_risk, planner_update_rule, needs,
    build_menu_text, cost, desirability, crime,
    output_resource_second_rate, building_size, info_title_id, progress_max, overlay, max_service, max_storage_amount,
    meta_id, meta, production_rate, min_houses_coverage)