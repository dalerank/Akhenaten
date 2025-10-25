#include "renderer.h"

#include "core/profiler.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "widget/debug_console.h"
#include "platform/platform.h"

#include <SDL.h>

ANK_REGISTER_PROPS_ITERATOR(config_load_filter_properties);

#if defined(GAME_PLATFORM_WIN) || defined(GAME_PLATFORM_LINUX)
#include "gpupixel.h"

struct renderer_filter_t {
    gpupixel::FilterPtr bilaterial;
    bool bilaterial_active = false;
    gpupixel::SourceImagePtr sourceImage;
    std::shared_ptr<gpupixel::TargetView> outputImage;

    bool render_support_filters = false;
    bool any_filter_active = false;
};

renderer_filter_t g_renderer_filter;

bool platform_render_any_filter_active() {
    auto &data = g_renderer_filter;

    return data.bilaterial_active;
}

bool platform_render_support_filters() {
    return g_renderer_filter.render_support_filters;
}

void platform_render_init_filters() {
    auto &data = g_renderer_filter;

    std::string driver = get_video_driver();
    data.render_support_filters = (driver == "opengl");
    data.render_support_filters &= SDL_VERSION_ATLEAST(2, 0, 12);

    if (!platform_render_support_filters()) {
        return;
    }

    gpupixel::GPUPixelContext::initOpengl();

    data.sourceImage = gpupixel::SourceImage::create_from_memory(0, 0, 4, nullptr);
    data.bilaterial = gpupixel::BilateralFilter::create();
    //bilaterial = gpupixel::GrayscaleFilter::create();
    data.outputImage = gpupixel::TargetView::create();

    data.sourceImage->addTarget(data.bilaterial)->addTarget(data.outputImage);
}

void game_debug_show_filter_property_float(gpupixel::FilterPtr filter, const char *name) {
    if (!filter->hasProperty(name)) {
        return;
    }

    float value, save_value;
    filter->getProperty(name, value);
    save_value = value;
    game_debug_show_property(name, value);
    if(save_value != value) {
        filter->setProperty(name, value);
    }
}

bool platform_render_bilaterial_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.bilaterial_active;
    // Use object uid as identifier. Most commonly you could also use the object pointer as a base ID.
    ImGui::PushID(0x10000000 | 0x1);

    // Text and Tree nodes are less high than framed widgets, using AlignTextToFramePadding() we add vertical spacing to make the tree lines equal high.
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Bilaterial", ImGuiTreeNodeFlags_DefaultOpen, "Bilaterial");
    ImGui::TableSetColumnIndex(1);

    int i = 0;
    if (common_open) {
        game_debug_show_property("Active", data.bilaterial_active);
        game_debug_show_filter_property_float(data.bilaterial, "texelSpacingMultiplier");
        game_debug_show_filter_property_float(data.bilaterial, "distanceNormalizationFactor");
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.bilaterial_active);
}

void platform_render_proceed_filter(int w, int h, int format, const std::vector<uint8_t>&pixels, SDL_Texture *filter_texture, SDL_Texture *source_texture) {
    auto &data = g_renderer_filter;

    // this not work, wtf?
    //float texw, texh;
    //GLint render_texture_id;
    //SDL_GL_BindTexture(source_texture, &texw, &texh);
    //glGetIntegerv(GL_TEXTURE_BINDING_2D, &render_texture_id);
    //SDL_GL_UnbindTexture(source_texture);
    //data.sourceImage->init(w, h, SDL_BYTESPERPIXEL(format), render_texture_id);
    data.sourceImage->init(w, h, SDL_BYTESPERPIXEL(format), (uint8_t *)pixels.data());
    data.sourceImage->proceed();

    void *dst_pixels = nullptr;
    int dst_pitch;
    SDL_LockTexture(filter_texture, nullptr, &dst_pixels, &dst_pitch);
    memcpy(dst_pixels, data.outputImage->getPixels(), w * h * SDL_BYTESPERPIXEL(format));
    SDL_UnlockTexture(filter_texture);
}

void config_load_filter_properties(bool header) {
    if (!platform_render_support_filters()) {
        ImGui::Dummy(ImVec2(0, 0));
        return;
    }

    auto &data = g_renderer_filter;
    static bool _debug_filter_open = false;

    bool filter_changed = false;
    if (header) {
        return;
    }

    bool common_open = ImGui::TreeNodeEx("Filters", ImGuiTreeNodeFlags_None, "Filters");
    if (common_open) {
        ImGui::BeginTable("Filters", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);

        filter_changed = platform_render_bilaterial_options();

        ImGui::EndTable();

        ImGui::TreePop();
    }

    if (filter_changed) {
        data.sourceImage->removeAllTargets();

        gpupixel::SourcePtr last = data.sourceImage;
        if (data.bilaterial_active) {
            last = last->addTarget(data.bilaterial);
        }

        last->addTarget(data.outputImage);
    }
}

#else

void platform_render_init_filters() {}
bool platform_render_support_filters() { return false; }
bool platform_render_any_filter_active() { return false; }
void platform_render_proceed_filter(int w, int h, int format, const std::vector<uint8_t> &pixels, SDL_Texture *filter_texture, SDL_Texture *source_texture) {}
void platform_render_init_filter_context() {}
void config_load_filter_properties(bool) {}

#endif // 