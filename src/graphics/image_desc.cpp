#include "image_desc.h"

#include "image.h"

int image_desc::tid() const {
    return image_id_from_group(pack, id) + offset;
}
