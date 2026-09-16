#pragma once

#include "building/building.h"
#include "empire/trader_handler.h"

class building_dock : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_DOCK, building_dock, building_impl)

    struct runtime_data_t {
        short queued_docker_id;
        sbitarray64 trading_goods;
        uint8_t num_ships;
        short docker_ids[3];
        figure_id trade_ship;
        uint8_t docker_anim_frame;
        e_figure_type process_type;
        bool reparing;
        short progress;
        bool has_fish;
    } BUILDING_RUNTIME_DATA_T;

    virtual building_dock *dcast_dock() override { return this; }

    virtual void on_create(int orientation) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_place(int orientation, int variant) override;
    virtual void on_tick(bool refresh_only) override;
    virtual void update_count() const override;
    virtual void update_month() override;
    virtual void update_map_orientation(int orientation) override;
    virtual void spawn_figure() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;

    void unaccept_all_goods();
    void accept_all_goods();
    bool accepts_any_goods() const;
    empire_trader_handle empire_trader() const;
    empire_city_handle trader_city();
    bool is_trade_accepted(e_resource r) const;
    void toggle_good_accepted(e_resource r);
    int count_idle_dockers() const;
    /** Count goods from empire lists that this dock accepts (unweighted). */
    int count_matching_goods(const resource_list &importable, const resource_list &exportable) const;
    /**
     * Weighted overlap: import matches count 2, export-only matches count 1
     * (prefer docks that can unload the ship's cargo).
     */
    int trade_match_score(const resource_list &importable, const resource_list &exportable) const;
    /**
     * Ship-aware score: prefer remaining import budgets when populated, else full
     * empire importable; always include currently exportable city goods.
     */
    int match_score_for_ship(int ship_id) const;
    bool accepts_ship(int ship_id);
    /** Lower is better: distance to nearest dock-permission storage yard on the same road net. */
    int yard_proximity_cost() const;
    tile2i moor_tile() const;
    tile2i wait_tile() const;
    tile2i reid_tile() const;
};

ANK_CONFIG_PROPERTY(building_dock::runtime_data_t, has_fish, num_ships)

building_dest map_get_free_destination_dock(int ship_id);
/** Free pier with score strictly greater than min_exclusive_score; no reservation change if none. */
building_dest map_get_better_free_destination_dock(int ship_id, int min_exclusive_score);
building_dest map_get_queue_destination_dock(int ship_id);
bool map_tile_is_connected_to_open_water(tile2i tile);