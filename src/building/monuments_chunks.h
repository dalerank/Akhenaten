#pragma once

#include "io/io_buffer.h"

struct monuments_progress_chunk : grid_chunk<monuments_progress_chunk, FS_UINT32> {
    static constexpr const char* name = "monuments_progress";
};
