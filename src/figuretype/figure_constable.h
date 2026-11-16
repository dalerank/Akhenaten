#pragma once

#include "figuretype/figure_law_walker.h"

enum e_constable_action {
    ACTION_74_CONSTABLE_REQUESTING_WEAPONS = 74,
};

enum e_constable_limits {
    CONSTABLE_MAX_ENEMY_CANDIDATES = 100,
};

class figure_constable : public figure_law_walker {
public:
    FIGURE_METAINFO(FIGURE_CONSTABLE, figure_constable)
    figure_constable(figure* f) : figure_law_walker(f) {}

    struct static_params : public figure_static_params {
        int home_road_radius;
        int crime_reduction;
        int enemy_search_ticks;
        int enemy_search_distance;
        int native_distance_factor;
        int enemy_distance_factor;
        int animal_distance_factor;
        svector<e_figure_type, 16> chased_animals;
        int tomb_robber_arrest_distance;
    } FIGURE_STATIC_DATA_T;

    virtual void figure_action() override;
    virtual int provide_service() override;

    bool fight_enemy();
    figure_id closest_enemy(int max_distance) const;
    void arrest_tomb_robber_remake();
    void request_weapons_remake();

protected:
    virtual int home_road_radius() const override { return current_params().home_road_radius; }
    virtual void on_walk_cycle(bool wrapped) override;
    virtual void on_attack_tick() override;
};
ANK_CONFIG_STRUCT(figure_constable::static_params, home_road_radius, crime_reduction, enemy_search_ticks,
  enemy_search_distance, native_distance_factor, enemy_distance_factor, animal_distance_factor, chased_animals,
  tomb_robber_arrest_distance)
