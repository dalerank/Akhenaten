#include "window_building_info.h"

#include "building/building_temple.h"

struct temple_info_window : public building_info_window_t<temple_info_window> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        building *b = c.building_get();
        return !!b->dcast_temple();
    }
};

temple_info_window temple_infow;

void temple_info_window::init(object_info &c) {
    building_info_window::init(c);

    auto temple = c.building_get()->dcast_temple();

    int16_t image_offset = 0;
    switch (temple->type()) {
    case BUILDING_TEMPLE_OSIRIS: image_offset = 21; break;
    case BUILDING_TEMPLE_RA: image_offset = 22; break;
    case BUILDING_TEMPLE_PTAH: image_offset = 23; break;
    case BUILDING_TEMPLE_SETH: image_offset = 24; break;
    case BUILDING_TEMPLE_BAST: image_offset = 25; break;

    default:
        assert(false);
    }

    ui["god_image"].image({ PACK_UNLOADED, 21, image_offset });
}
