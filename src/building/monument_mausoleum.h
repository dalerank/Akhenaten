#pragma once

#include "building/monuments.h"
#include "building/building.h"
#include "core/svector.h"
#include "core/vec2i.h"
#include "figure/figure.h"

// Mausoleum: 116 chained parts (OG mausoleum_part_descs) in a 22x8 box. Parts 0..3 are 4x4 sandstone
// blocks, the rest are 1x1 ground tiles leveled by laborers. Art skin 0/1/2 lives in runtime_data().variant.

enum mausoleum_limits : int {
    MAUSOLEUM_PARTS = 116,
    MAUSOLEUM_BLOCKS = 4,
    MAUSOLEUM_FENCE_PARTS = MAUSOLEUM_PARTS - MAUSOLEUM_BLOCKS,
    MAUSOLEUM_BOX_WIDTH = 22,
    MAUSOLEUM_BOX_DEPTH = 8,
    MAUSOLEUM_ENTRY_DX = 22,
    MAUSOLEUM_ENTRY_DY = 4,
    MAUSOLEUM_WORK_TICKS = 50,
    MAUSOLEUM_WORK_UNITS = 288,
    MAUSOLEUM_BLOCK_SUBTILES = 16,
    MAUSOLEUM_MATERIAL_PER_LOAD = 400,
};

enum mausoleum_kind_flag : uint32_t {
    MAUSOLEUM_KIND_MASK = 0xff,
    MAUSOLEUM_KIND_GROUND_FIRST = 4,
    MAUSOLEUM_KIND_BLOCK_MASK = 0xf00,
    MAUSOLEUM_KIND_BLOCK_0 = 0x100,
    MAUSOLEUM_KIND_BLOCK_1 = 0x200,
    MAUSOLEUM_KIND_BLOCK_2 = 0x400,
    MAUSOLEUM_KIND_BLOCK_3 = 0x800,
    MAUSOLEUM_KIND_PAIR_MASK = 0xf000,
    MAUSOLEUM_KIND_PAIR_0 = 0x1000,
    MAUSOLEUM_KIND_PAIR_1 = 0x2000,
    MAUSOLEUM_KIND_PAIR_2 = 0x4000,
    MAUSOLEUM_KIND_PAIR_3 = 0x8000,
    MAUSOLEUM_KIND_WALKWAY = 0x10000,
};

enum mausoleum_ground_stage : uint16_t {
    MAUSOLEUM_GROUND_UNTOUCHED = 0,
    MAUSOLEUM_GROUND_LEVELED = 1,
    MAUSOLEUM_GROUND_FINISHED = 2,
};

enum mausoleum_block_mask : uint16_t {
    MAUSOLEUM_BLOCK_LOW_DONE_MASK = 0x00ff,
    MAUSOLEUM_BLOCK_FULL = 0xffff,
    MAUSOLEUM_PAIR_LOW_SUBTILES = 0x0003,
    MAUSOLEUM_PAIR_HIGH_SUBTILES = 0x0300,
};

enum mausoleum_work_flag : uint8_t {
    MAUSOLEUM_BLOCKS_LOW_DONE = 0x01,
    MAUSOLEUM_BLOCKS_FULL = 0x02,
    MAUSOLEUM_GROUND_STARTED = 0x04,
    MAUSOLEUM_GROUND_DONE = 0x08,
    MAUSOLEUM_BLOCK_FINISHED_FIRST = 0x10,
    MAUSOLEUM_BLOCKS_FINISHED = 0xf0,
};

enum mausoleum_status : int {
    MAUSOLEUM_STATUS_SITE = 1,
    MAUSOLEUM_STATUS_STARTED = 2,
    MAUSOLEUM_STATUS_BLOCKS_RISING = 3,
};

enum mausoleum_progress_out {
    MAUSOLEUM_PROGRESS_STATUS = 0,
    MAUSOLEUM_PROGRESS_PERCENT = 1,
    MAUSOLEUM_PROGRESS_BLOCKS_LEFT = 2,
    MAUSOLEUM_PROGRESS_STONEMASONS = 3,
    MAUSOLEUM_PROGRESS_STONEMASONS_WAITING = 4,
    MAUSOLEUM_PROGRESS_LABORERS = 5,
    MAUSOLEUM_PROGRESS_CARPENTERS = 6,
    MAUSOLEUM_PROGRESS_MATERIAL = 7,
    MAUSOLEUM_PROGRESS_MATERIAL_TOTAL = 8,
    MAUSOLEUM_PROGRESS_PARTS_BELOW_2 = 9,
    MAUSOLEUM_PROGRESS_SLOTS = 10,
};

struct mausoleum_part_desc {
    xstring hint;
    vec2i offset;
    uint8_t size = 1;
    // JS writes the base kind (0..13) plus optional walkway/block/pair; pack_kind packs the OG word.
    uint32_t kind = 0;
    bool walkway = false;
    int16_t block = -1;
    int16_t pair = -1;

    void pack_kind();
};
ANK_CONFIG_STRUCT(mausoleum_part_desc, hint, offset, size, kind, walkway, block, pair)

// Legend entry for one fence_map glyph. Unknown glyphs are skipped (e.g. '#' sandstone).
struct mausoleum_fence_token {
    xstring token;
    int16_t kind = -1;
    bool walkway = false;
    int16_t pair_dy = 0; // if set, also emit (x, y+pair_dy) as the next part
};
ANK_CONFIG_STRUCT(mausoleum_fence_token, token, kind, walkway, pair_dy)

// Masonry-link overlay for fence_map tiles (block/pair bits the ASCII cannot carry alone).
struct mausoleum_fence_link {
    vec2i offset;
    int16_t block = -1;
    int16_t pair = -1;
};
ANK_CONFIG_STRUCT(mausoleum_fence_link, offset, block, pair)

class building_mausoleum : public building_monument {
public:
    BUILDING_METAINFO(BUILDING_MAUSOLEUM, building_mausoleum, building_monument)
    virtual building_mausoleum *dcast_mausoleum() override { return this; }

    struct runtime_data_t : building_monument::runtime_data_t {
        uint16_t part_stage = 0;
        uint8_t part_index = 0;
        uint8_t work_flags = 0;
        uint8_t view = 0;
    } BUILDING_RUNTIME_DATA_T;

    struct base_params {
        svector<monument_phase_resource, 4> placement_resources;
        svector<mausoleum_part_desc, MAUSOLEUM_BLOCKS> blocks;
        svector<mausoleum_fence_token, 16> fence_tokens;
        svector<xstring, MAUSOLEUM_BOX_DEPTH> fence_map;
        svector<mausoleum_fence_link, 32> fence_links;
        svector<mausoleum_part_desc, MAUSOLEUM_PARTS> parts; // blocks + expanded fence_map
        xstring leveled;
        xstring unbuilt;
    };

    struct static_params : public base_params, public building_static_params {
        void archive_load(archive arch);
    } BUILDING_STATIC_DATA_T;

    struct preview : building_planer_renderer {
        virtual void setup_preview_graphics(build_planner &planer) const override;
        virtual int construction_place(build_planner &p, tile2i tile, tile2i end, int orientation, int variant) const override;
        virtual int can_place(build_planner &p, tile2i tile, tile2i end, int state) const override;
        virtual int finalize_check(build_planner &p, tile2i tile, tile2i end, int state) const override;
        virtual void ghost_preview(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel) const override;
    };

    virtual void on_place(int orientation, int variant) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void set_phase(int phase) override;
    virtual void on_phase_changed(int old_phase, int current) override;
    virtual void update_day() override;
    virtual void update_map_orientation(int map_orientation) override;
    virtual int building_image_get() const override;
    virtual bool need_stonemason() override;
    virtual bool need_carpenter() override;
    virtual bool need_workers() const override;
    virtual bool needs_resources() const override;
    virtual void add_workers(figure_id fid) override;
    virtual void remove_worker(figure_id fid) override;
    virtual const monument &config() const override;
    virtual tile2i center_point() const override;
    virtual tile2i access_point() const override;
    virtual grid_area get_area() const override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;

    int part_index() const { return runtime_data().part_index; }
    uint32_t part_kind_word() const;
    int part_kind() const { return part_kind_word() & MAUSOLEUM_KIND_MASK; }
    uint16_t part_stage() const { return runtime_data().part_stage; }
    uint8_t work_flags() const;
    building_mausoleum *main_mausoleum();
    const building_mausoleum *main_mausoleum() const;
    building_mausoleum *part(int index);
    const building_mausoleum *part(int index) const;

    // Returns true when the figure is done here and should leave.
    bool work_tick(figure &f);
    bool check_work_for_figure(figure_id fid, bool assign);
    bool has_work_for(e_figure_type type) const;
    static int find_work_for_figure(figure_id fid);

    int get_progress(int *out /*nullable, MAUSOLEUM_PROGRESS_SLOTS*/) const;
    void refresh_part_images();
    void update_part_image();

    int placement_amount(e_resource r) const;
    static int yards_available(e_resource r);
    static bool has_unfinished_mausoleum();
    static int parts_count();
    static const mausoleum_part_desc &part_desc(int index);
    static vec2i box_extent(int orientation);
    static tile2i origin_from_cursor(tile2i cursor);
    static vec2i part_offset(int index, int view, int orientation);
    static vec2i entry_offset(int view, int orientation);

private:
    tile2i origin() const;
    vec2i current_offset() const;
    bool part_has_active_worker() const;
    figure_id worker_figure_id() const;
    void set_worker_figure(figure_id fid);
    void clear_worker_figure();
    void send_to_part(figure &f) const;
    int check_material_laborer(figure *f, bool assign);
    bool check_work(e_figure_type type, figure *f, bool assign);
    bool laborer_tick(figure &f);
    bool block_tick(figure &f);
    void update_ground_flags();
    void recompute_block_flags();
    void finish_all();
    int block_index() const;
    int camera_view() const;
    static bool area_blocked_at(tile2i origin, vec2i extent);
};

ANK_CONFIG_STRUCT(building_mausoleum::static_params, placement_resources, blocks, fence_tokens, fence_map, fence_links, leveled, unbuilt)
ANK_CONFIG_PROPERTY(building_mausoleum::runtime_data_t, variant)
