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

    std::vector<option> gods;

    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        return !!c.building_get<building_shrine>();
    }

    virtual void load(archive arch, pcstr section) override {
        inherited::load(arch, section);

        gods.clear();
        arch.r_objects("gods", [this] (pcstr key, archive g_arch) {
            auto &config = gods.emplace_back();
            config.type = g_arch.r_type<e_building_type>("type");
            config.title = g_arch.r_string("title");
            config.text = g_arch.r_string("text");
            g_arch.r_desc("image", config.image);
        });
    }
};

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