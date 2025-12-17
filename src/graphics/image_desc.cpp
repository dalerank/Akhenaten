#include "image_desc.h"
#include "image.h"

int image_desc::tid() {
    if (pack == -1) {
        return -1;
    }

    if (!pack && !id && !offset && !path.empty()) {
        auto o = image_desc_from_name(path);
        pack   = o.pack;
        id     = o.id;
        offset = o.offset;

        if (!pack && !id && !offset) {
            pack = -1;
            return -1;
        }
    }

    return image_id_from_group(pack, id) + offset;
}
