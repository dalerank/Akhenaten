#include "figure/figure.h"

struct event_create_immigrant {
    building_id bid;
    int num_people;
    pcstr src_location;
    std::function<void()> payload;
};

enum e_immigrant_action : uint16_t {
    FIGURE_ACTION_1_IMMIGRANT_CREATED = 1,
    FIGURE_ACTION_2_IMMIGRANT_ARRIVING = 2,
    FIGURE_ACTION_3_IMMIGRANT_ENTERING_HOUSE = 3,
    FIGURE_ACTION_6_IMMIGRANT_LEAVING = 6,
};

class figure_immigrant : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_IMMIGRANT, figure_immigrant)
    figure_immigrant(figure *f) : figure_impl(f) {}
    virtual figure_immigrant *dcast_immigrant() override { return this; }

    struct static_params : figure_model {
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        uint16_t adv_home_building_id;
        uint8_t migrant_num_people;
    } FIGURE_RUNTIME_DATA_T;

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
    virtual void debug_show_properties() override;
    virtual void debug_draw() override;
    virtual bool is_home(const building *b) const override {
        return (base.home_building_id > 0) &&
            (base.home_building_id == b->id || runtime_data().adv_home_building_id == b->id);
    }

    building* immigrant_home();

    void set_immigrant_home(int _id) {
        runtime_data().adv_home_building_id = _id;
    };

    void set_immigrant_home(building* b) {
        runtime_data().adv_home_building_id = b->id;
    };
};