#pragma once

#include "figure/figure.h"

enum e_dentist_action {
    ACTION_125_DENTIST_ROAMING = 125,
    ACTION_126_DENTIST_RETURNING = 126,
    ACTION_64_DENTIST_GOING_TO_NOBLE_HOUSE = 64,
    ACTION_65_DENTIST_TREATING_NOBLES = 65,
};

class figure_dentist : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_DENTIST, figure_dentist)
    figure_dentist(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual sound_key phrase_key() const override;
    virtual int provide_service() override;
    
    building_id find_noble_house_with_bad_teeth();
    void treat_nobles_in_house(building_house *house);
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;
};