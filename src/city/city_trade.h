#pragma once

#include "game/resource.h"

struct city_trade_t {
    int16_t num_land_routes;
    int16_t num_sea_routes;
    int16_t land_trade_problem_duration;
    int16_t sea_trade_problem_duration;

    e_resource caravan_import_resource = RESOURCES_MIN;
    e_resource caravan_backup_import_resource = RESOURCES_MIN;

    e_resource docker_import_resource;
    e_resource docker_export_resource;

    // OG trade_export_keep: not saved, recomputed on load and once a day.
    int32_t export_keep[RESOURCES_MAX];

    bool has_land_route() const { return num_land_routes > 0; }
    bool has_sea_route() const { return num_sea_routes > 0; }
    bool has_land_problems() const { return land_trade_problem_duration > 0; }
    bool has_sea_problems() const { return sea_trade_problem_duration > 0; }
    e_resource current_caravan_import() const { return caravan_import_resource; }
    int keep_for_export(e_resource resource) const;

    void update();
    void update_export_keep();
    void add_land_route();
    void add_sea_route();
    void start_land_problems(int duration);
    void start_sea_problems(int duration);
    e_resource next_caravan_import();
    e_resource next_caravan_backup_import();
    e_resource next_docker_import();
    e_resource next_docker_export();
    void reset();

private:
    int recommended_keep(int good_index) const;
    int monument_need(e_resource resource) const;
    int material_keep(e_resource resource) const;
};

city_trade_t& city_trade();
