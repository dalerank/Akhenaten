#include "image.h"

#include "SDL.h"

#include "core/buffer.h"
#include "core/io.h"
#include "core/log.h"
#include "core/game_environment.h"
#include "core/image_group.h"

#include <string.h>
#include <cinttypes>
#include "graphics/graphics.h"
#include "graphics/font.h"
#include "core/string.h"
#include "stopwatch.h"
#include "io/imagepaks/atlas_packer.h"

int terrain_ph_offset = 0;

////////////////////////
