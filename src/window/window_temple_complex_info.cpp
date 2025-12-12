#include "window_building_info.h"

#include "building/building_temple_complex.h"

struct temple_complex_info_window : public building_info_window_t<temple_complex_info_window> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        building *b = c.building_get();
        return !!smart_cast<building_temple_complex>(b);
    }
};

temple_complex_info_window temple_complex_infow;

void temple_complex_info_window::init(object_info &c) {
    building_info_window::init(c);

    auto temple = smart_cast<building_temple_complex>(c.building_get());

    int16_t image_offset = 0;
    switch (temple->type()) {
    case BUILDING_TEMPLE_COMPLEX_OSIRIS: image_offset = 21; break;
    case BUILDING_TEMPLE_COMPLEX_RA: image_offset = 22; break;
    case BUILDING_TEMPLE_COMPLEX_PTAH: image_offset = 23; break;
    case BUILDING_TEMPLE_COMPLEX_SETH: image_offset = 24; break;
    case BUILDING_TEMPLE_COMPLEX_BAST: image_offset = 25; break;

    default:
        assert(false);
    }

    ui["god_image"].image({ PACK_UNLOADED, 21, image_offset });
}
