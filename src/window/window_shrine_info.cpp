#include "window/window_building_info.h"

#include "building/building_shrine.h"
#include "window/building/common.h"
#include "city/object_info.h"

struct shrine_info_window : public building_info_window_t<shrine_info_window> {
    using inherited = building_info_window_t<shrine_info_window>;
    struct option {
        e_building_type type;
        image_desc image;
        xstring title;
        xstring text;
    };

    svector<option, 8> gods;

    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        return !!c.building_get<building_shrine>();
    }

    virtual void archive_load(archive arch) override {
        inherited::archive_load(arch);

        gods.clear();
        arch.r("gods", gods);
    }
};
ANK_CONFIG_STRUCT(shrine_info_window::option, type, image, title, text)

shrine_info_window shrine_infow;

void shrine_info_window::init(object_info &c) {
    building_info_window::init(c);

    auto shrine = c.building_get<building_shrine>();
    if (!shrine) {
        return;
    }

    const auto it = std::find_if(gods.begin(), gods.end(), [shrine] (auto &it) { return it.type == shrine->type(); });
    if (it == gods.end()) {
        return;
    }

    ui["god_image"] = it->image;
    ui["title"] = it->title;
    ui["warning_text"] = it->text;
}