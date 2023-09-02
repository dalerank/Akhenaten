#pragma once

#include "io/io_buffer.h"

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
void map_image_set(int grid_offset, int image_id);

void map_image_backup(void);
void map_image_restore(void);
void map_image_restore_at(int grid_offset);
void map_image_fix_icorrect_tiles();

void map_image_clear(void);
void map_image_init_edges(void);

void set_image_grid_correction_shift(int shift);