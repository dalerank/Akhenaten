#include "window/window_building_info.h"

#include "building/building_shrine.h"
#include "window/building/common.h"
#include "city/object_info.h"

struct shrine_info_window : public building_info_window_t<shrine_info_window> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        building *b = c.building_get();
        return !!smart_cast<building_shrine>(b);
    }
};

shrine_info_window shrine_infow;

void shrine_info_window::init(object_info &c) {
    building_info_window::init(c);

    building *b = c.building_get();

    int image_offset = 0;
    switch (b->type) {
    case BUILDING_SHRINE_OSIRIS: image_offset = 21; break;
    case BUILDING_SHRINE_RA: image_offset = 22; break;
    case BUILDING_SHRINE_PTAH: image_offset = 23; break;
    case BUILDING_SHRINE_SETH: image_offset = 24; break;
    case BUILDING_SHRINE_BAST: image_offset = 25; break;

    default:
        assert(false);
    }

    ui["god_image"].image({ PACK_UNLOADED, 21, image_offset });

    //if (c.has_road_access) {
    //    ImageDraw::img_generic(ctx, image_offset + image_id_from_group(PACK_UNLOADED, 21), c.offset.x + 190, c.offset.y + 16 * c.bgsize.y - 148);
    //}
}