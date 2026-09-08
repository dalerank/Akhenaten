#include "building_mine.h"

#include "building/building.h"
#include "graphics/animation.h"

void building_mine::on_create(int orientation) {
    building_industry::on_create(orientation);
}

void building_mine::update_graphic() {
    update_graphic_work_anim();
}
