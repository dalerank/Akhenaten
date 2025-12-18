#pragma once

#include "figure/figure.h"
#include "grid/figure.h"
#include "core/custom_span.hpp"

struct city_figures_t {
    uint8_t fish_number;
    uint8_t animals_number;
    int32_t attacking_natives;
    int16_t enemies;
    int32_t kingdome_soldiers;
    int32_t rioters;
    int32_t soldiers;
    int32_t security_breach_duration;

    void reset();
    void on_post_load();
    void update();
    void add_animal();
    void init_figures();
    void reload_objects();

    void add_enemy();

    int total_invading_enemies() const;
};

void figure_clear_all();

figure *figure_get(int id);

template<typename T>
inline T* figure_get(int id) {
    figure *f = ::figure_get(id);
    T* tf = (f->type != FIGURE_NONE) ? smart_cast<T>(f) : nullptr;
    return tf;
}
custom_span<figure *> map_figures();

template<typename ... Args>
bool figure_type_none_of(const figure &f, Args ... args) {
    int types[] = { args... };
    return (std::find(std::begin(types), std::end(types), f.type) == std::end(types));
}

template<typename T, typename F>
bool figure_type_any_of(const T &f, const F& types) {
    e_figure_type type;
    if constexpr (std::is_same_v<e_figure_type, std::decay_t<T>>) {
        type = f;
    } else if constexpr (std::is_pointer_v<T>) {
        type = f ? f->type : FIGURE_NONE;
    } else {
        type = f.type;
    }
    return (std::find(types.begin(), types.end(), type) != types.end());
}

template<typename T, typename F>
void figure_valid_do(T func, const F& types) {
    for (auto *f : map_figures()) {
        if (f->is_valid() && figure_type_any_of(*f, types)) {
            func(*f);
        }
    }
}

template<typename ... Args, typename T>
void figure_valid_do(T func) {
    for (auto *f : map_figures()) {
        if (f->is_valid()) {
            func(*f);
        }
    }
}

template<typename F>
bool map_has_figure_types_at(tile2i tile, const F& types) {
    int figure_id = map_figure_id_get(tile);
    while (figure_id) {
        figure *f = figure_get(figure_id);
        if (figure_type_any_of(*f, types)) {
            return true;
        }
        figure_id = (figure_id != f->next_figure) ? f->next_figure : 0;
    }

    return false;
}