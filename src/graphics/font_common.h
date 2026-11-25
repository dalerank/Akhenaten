#pragma once

#include "graphics/font.h"
#include "graphics/imagepak_holder.h"
#include "content/atlas_packer.h"
#include "content/vfs.h"
#include "config/font_config.h"

using fn_fill_font_packer_t = bool (*)(image_packer&,
                                       imagepak_handle,
                                       const font_configs_t &,
                                       const font_utf8_symbols_t &,
                                       vfs::path,
                                       int &);
