#pragma once

#include "building/monument_pyramid_figure.h"
#include "figure/figure.h"

// OG FIGURE_ACTION_LABORER_IDLE — train members stay here while they follow.
enum e_sled_action {
    ACTION_8_SLED_TRAIN_FOLLOW = 8,
    // Remake (gameplay_change_sled_pullers_flee): left on the map with its cargo, follows nobody.
    ACTION_9_SLED_DROPPED = 9,
};

class figure_sled : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_SLED, figure_sled)
    figure_sled(figure* f) : figure_impl(f) {}

    struct resource_image_t {
        e_resource resource;
        xstring ground;
        xstring ramp;
    };

    struct static_params : public figure_static_params {
        svector<resource_image_t, 16> resource_images;
        resource_image_t default_image;
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        uint8_t walk_mode;
        pyramid_figure_work_t climb;
    } FIGURE_RUNTIME_DATA_T;

    virtual void figure_action() override;
    virtual void update_animation() override;
    virtual figure_sled* dcast_sled() override { return this; }
};
ANK_CONFIG_STRUCT(figure_sled::resource_image_t, resource, ground, ramp)
ANK_CONFIG_STRUCT(figure_sled::static_params, resource_images, default_image)

class figure_sled_puller : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_SLED_PULLER, figure_sled_puller)
    figure_sled_puller(figure *f) : figure_impl(f) {}

    struct static_params : public figure_static_params {
        uint8_t flee_enemy_distance;
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        uint8_t walk_mode;
        // OG resource_id 0/1: which hand of the pair, picks the front or pulling sprite.
        uint8_t side;
        pyramid_figure_work_t climb;
    } FIGURE_RUNTIME_DATA_T;

    virtual void figure_action() override;
    virtual void update_animation() override;
    virtual figure_sled_puller *dcast_sled_puller() override { return this; }

private:
    bool enemy_near() const;
};
ANK_CONFIG_STRUCT(figure_sled_puller::static_params, flee_enemy_distance)
