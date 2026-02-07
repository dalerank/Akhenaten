#pragma once

#include "building/building.h"

struct building_palace_show_tooltip { building_id bid; int mx, my; };

class building_palace : public building_impl {
public:
    building_palace(building &b) : building_impl(b) {}
    virtual building_palace *dcast_palace() override { return this; }

    struct runtime_data_t {
        int16_t tax_income_or_storage;
    } BUILDING_RUNTIME_DATA(runtime_data_t);

    virtual void on_create(int orientation) override;
    virtual void on_post_load() override;
    virtual void on_destroy() override;
    virtual void update_count() const override;
    virtual bool can_play_animation() const override;
    virtual void update_graphic() override;
    virtual void draw_tooltip(tooltip_context *c) const override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
    virtual void spawn_figure() override;

    virtual bvariant get_property(const xstring &domain, const xstring &name) const override;
};

class building_village_palace : public building_palace {
public:
    BUILDING_METAINFO(BUILDING_VILLAGE_PALACE, building_village_palace, building_palace)
};

class building_town_palace : public building_palace {
public:
    BUILDING_METAINFO(BUILDING_TOWN_PALACE, building_town_palace, building_palace)
};

class building_city_palace : public building_palace {
public:
    BUILDING_METAINFO(BUILDING_CITY_PALACE, building_city_palace, building_palace)
};
