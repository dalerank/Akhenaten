#include "figure/figure.h"

struct event_create_immigrant {
    building_id bid;
    int num_people;
    pcstr src_location;
    std::function<void()> payload;
};

class figure_immigrant : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_IMMIGRANT, figure_immigrant)
    figure_immigrant(figure *f) : figure_impl(f) {}
    virtual figure_immigrant *dcast_immigrant() override { return this; }

    struct static_params : figures::model_t<figure_immigrant> {
    };

    virtual void on_destroy() override;
    virtual void figure_action() override;
    virtual void figure_before_action() override;
    virtual void figure_roaming_action() override { /*nothing*/ }
    virtual void update_animation() override;
    virtual bool can_move_by_water() const override;
    virtual int y_correction(int y) const override { return 10; }
    virtual figure_phrase_t phrase() const override { return {FIGURE_IMMIGRANT, "immigrant"}; }
    virtual figure_sound_t get_sound_reaction(xstring key) const override;
    virtual sound_key phrase_key() const override;
    virtual const animations_t &anim() const override;

    building* immigrant_home();

    void set_immigrant_home(int _id) {
        base.immigrant_home_building_id = _id;
    };

    void set_immigrant_home(building* b) {
        base.immigrant_home_building_id = b->id;
    };
};