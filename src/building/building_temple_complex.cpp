#include "building_temple_complex.h"

template<class T>
struct building_temple_complex_model : public buildings::model_t<T> {
    using inherited = buildings::model_t<T>;

    using inherited::load;
    virtual void load(archive arch) override {
    }

    virtual void setup_preview_graphics(build_planner &planer) const override {
        inherited::setup_preview_graphics(planer);
    }
};

building_temple_complex_model<building_temple_complex_osiris> building_temple_complex_osiris_m;
building_temple_complex_model<building_temple_complex_ra> building_temple_complex_ra_m;
building_temple_complex_model<building_temple_complex_ptah> building_temple_complex_ptah_m;
building_temple_complex_model<building_temple_complex_seth> building_temple_complex_seth_m;
building_temple_complex_model<building_temple_complex_bast> building_temple_complex_bast_m;

void building_temple_complex::on_create(int orientation) {
    data.monuments.variant = (10 - (2 * orientation)) % 8; // ugh!
}
