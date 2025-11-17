#pragma once

#include "building/building_entertainment.h"
#include "window/window_building_info.h"

/**
 * @class building_dancer_school
 * @brief Represents a dance school building that trains dancers for entertainment venues.
 * 
 * Dance schools spawn dancers who perform at pavilions. When enabled via game feature,
 * conservatories can help dance schools by reducing the spawn delay for new dancers.
 * The help is distributed evenly - conservatories automatically find dance schools
 * with the least amount of help and provide assistance to them.
 */
class building_dancer_school : public building_entertainment {
public:
    BUILDING_METAINFO(BUILDING_DANCE_SCHOOL, building_dancer_school, building_entertainment)
    virtual building_dancer_school* dcast_dancer_school() override { return this; }

    /**
     * The spawn delay is reduced if one or more conservatories are helping
     * this dance school (when gameplay_conservatory_helps_dance_school feature is enabled).
     */
    virtual void spawn_figure() override;
    virtual void update_day() override;
    virtual void on_tick(bool refresh_only) override;
    virtual void update_graphic() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual e_sound_channel_city sound_channel() const override { return SOUND_CHANNEL_CITY_DANCE_SCHOOL; }
    
    /**
     * @brief Gets the number of conservatories currently helping this dance school.
     * 
     * @return Number of conservatories helping (0-255, stored in ent_reserved_u8)
     */
    uint8_t conservatory_help() const;
};
