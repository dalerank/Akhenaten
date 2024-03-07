#pragma once

#include "io/io_buffer.h"
#include "graphics/image_desc.h"

class io_image_grid : public io_buffer {
public:
    io_image_grid() {
        inherited = true;
    }
    virtual void bind_data(size_t version) override;
    uint32_t fix_img_index(int grid_offset, uint32_t index) const;
    void fix_incorrect_tiles_img();

    static io_image_grid& instance();
};

int map_image_at(int grid_offset);
inline int map_image_at(tile2i tile) { return map_image_at(tile.grid_offset()); }
int map_image_alt_at(int grid_offset);
void map_image_set(int grid_offset, int image_id);
inline void map_image_set(tile2i tile, int image_id) { map_image_set(tile.grid_offset(), image_id); }
void map_image_alt_set(int grid_offset, int image_id, int alpha);
void map_image_set(int grid_offset, e_image_id img);
inline void map_image_set(tile2i tile, e_image_id img) { map_image_set(tile.grid_offset(), img); }
void map_image_set(int grid_offset, e_image_id img, int offset);
inline void map_image_set(tile2i tile, e_image_id img, int offset) { map_image_set(tile.grid_offset(), img, offset); }

void map_image_backup();
void map_image_restore();
void map_image_restore_at(int grid_offset);
void map_image_fix_icorrect_tiles();

void map_image_clear();
void map_image_init_edges();

void set_image_grid_correction_shift(int shift);