#pragma once

#include "figure/figure.h"
#include "grid/figure.h"

struct city_figures_t {
    uint8_t fish_number;
    uint8_t animals_number;
    int32_t attacking_natives;
    int32_t enemies;
    int32_t kingdome_soldiers;
    int32_t rioters;
    int32_t soldiers;
    int32_t security_breach_duration;

    void reset();
    void on_post_load();
    void update();
    void add_animal();
    void init_figures();
};

void figure_clear_all();

figure *figure_get(int id);

template<typename T>
T* figure_get(int id) {
    return smart_cast<T>(::figure_get(id));
}
std::span<figure *> map_figures();

template<typename ... Args>
bool figure_type_none_of(figure &f, Args ... args) {
    int types[] = { args... };
    return (std::find(std::begin(types), std::end(types), f.type) == std::end(types));
}

template<typename ... Args>
bool figure_type_any_of(figure &f, Args ... args) {
    int types[] = { args... };
    return (std::find(std::begin(types), std::end(types), f.type) != std::end(types));
}

template<typename ... Args, typename T>
void figure_valid_do(T func, Args ... args) {
    for (auto *f : map_figures()) {
        if (f->is_valid() && figure_type_any_of(*f, args...)) {
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

template<typename ... Args>
bool map_has_figure_types_at(tile2i tile, Args... types) {
    int figure_id = map_figure_id_get(tile);
    while (figure_id) {
        figure *f = figure_get(figure_id);
        if (figure_type_any_of(*f, types...)) {
            return true;
        }
        figure_id = (figure_id != f->next_figure) ? f->next_figure : 0;
    }

    return false;
}