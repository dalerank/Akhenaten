#pragma once

#include "figure/figure.h"
#include "game/game_system.h"

struct animals_state {
    ANK_ESID(city_animals)

    bool herd_migration;
    bool allow_spawn_ostrich;
};

struct scenario_data_t;

struct animals_context {
    scenario_data_t& scenario;
};

class animals_system : public game_system {
public:
    ANK_ESID(city_animals)

    animals_system(animals_state& state, const animals_context& ctx) : _state(state), _ctx(ctx) {}

    void create_herds();
    formation* create_herd(tile2i tile, e_figure_type ftype, int num_animals);

    void update();
    void remove_all();

    void update_herd_formation(formation *m);
    void move_animals(const formation *m, int attacking_animals, int terrain_mask);

    bool can_spawn_ph_wolf(formation *m);
    bool can_spawn_ostrich(formation *m);
    void set_herd_figures_to_initial(const formation *m);
    bool breeding_ground_at(tile2i tile, int size);
    bool herd_point_in_area(tile2i a, tile2i b) const;
    bool get_free_tile(int x, int y, int allow_negative_desirability, tile2i &outtile);
    bool get_roaming_destination(int formation_id, int allow_negative_desirability, tile2i tile, int distance, int direction, tile2i &outtile);
    bool is_herd_spawn_accessible(tile2i tile, e_figure_type herd_type);

    void add_animals_point(int index, int x, int y, e_figure_type ftype, int num_animals);
    void set_animals_area(int index, int reseach_radius);

    void reset();
    void reload_config();

private:
    animals_state& _state;
    animals_context _ctx;
};

// Climate prey animal for herd spawn points.
e_figure_type climate_prey_type();
// Cleopatra Killer Type: climate pair + alt_predator_type (hyena|scorpion / croc|lion / hippo|asp).
e_figure_type climate_predator_type();
bool scenario_has_prey_points();

animals_state& city_animals_state();
animals_system city_animals();

ANK_CONFIG_STRUCT(animals_state, herd_migration)
