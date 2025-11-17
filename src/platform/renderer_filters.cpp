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
    // Basic filters
    gpupixel::FilterPtr bilaterial;
    bool bilaterial_active = false;
    
    gpupixel::FilterPtr grayscale;
    bool grayscale_active = false;
    
    gpupixel::FilterPtr brightness;
    bool brightness_active = false;
    
    gpupixel::FilterPtr contrast;
    bool contrast_active = false;
    
    gpupixel::FilterPtr saturation;
    bool saturation_active = false;
    
    gpupixel::FilterPtr exposure;
    bool exposure_active = false;
    
    gpupixel::FilterPtr hue;
    bool hue_active = false;
    
    gpupixel::FilterPtr colorInvert;
    bool colorInvert_active = false;
    
    gpupixel::FilterPtr posterize;
    bool posterize_active = false;
    
    gpupixel::FilterPtr gaussianBlur;
    bool gaussianBlur_active = false;
    
    gpupixel::FilterPtr boxBlur;
    bool boxBlur_active = false;
    
    gpupixel::SourceImagePtr sourceImage;
    std::shared_ptr<gpupixel::TargetView> outputImage;

    bool render_support_filters = false;
    bool any_filter_active = false;
};

renderer_filter_t g_renderer_filter;

bool platform_render_any_filter_active() {
    auto &data = g_renderer_filter;

    return data.bilaterial_active || data.grayscale_active || 
           data.brightness_active || data.contrast_active || 
           data.saturation_active || data.exposure_active || 
           data.hue_active || data.colorInvert_active || 
           data.posterize_active || data.gaussianBlur_active || 
           data.boxBlur_active;
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
    
    // Initialize all filters
    data.bilaterial = gpupixel::BilateralFilter::create();
    data.grayscale = gpupixel::GrayscaleFilter::create();
    
    gpupixel::GPUPixelContext::getInstance()->runSync([&] {
        data.brightness = gpupixel::BrightnessFilter::Create();
        data.contrast = gpupixel::ContrastFilter::Create();
        data.saturation = gpupixel::SaturationFilter::Create();
        data.exposure = gpupixel::ExposureFilter::Create();
        data.hue = gpupixel::HueFilter::Create();
        data.colorInvert = gpupixel::ColorInvertFilter::Create();
        data.posterize = gpupixel::PosterizeFilter::Create();
        data.gaussianBlur = gpupixel::GaussianBlurFilter::Create();
        data.boxBlur = gpupixel::BoxBlurFilter::Create();
    });
    
    data.outputImage = gpupixel::TargetView::create();

    data.sourceImage->addTarget(data.outputImage);
}

void game_debug_show_filter_property_float(gpupixel::FilterPtr filter, const char *name, const float step = 1.f) {
    if (!filter) {
        return;
    }

    if (!filter->hasProperty(name)) {
        return;
    }

    float value, save_value;
    filter->getProperty(name, value);
    save_value = value;
    game_debug_set_property_opt(step);
    game_debug_show_property(name, value);
    if(save_value != value) {
        filter->setProperty(name, value);
    }
}

bool platform_render_bilaterial_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.bilaterial_active;
    ImGui::PushID(0x10000000 | 0x1);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Bilateral", ImGuiTreeNodeFlags_None, "Bilateral");
    ImGui::TableSetColumnIndex(1);

    if (common_open) {
        game_debug_show_property("Active", data.bilaterial_active);
        game_debug_show_filter_property_float(data.bilaterial, "texelSpacingMultiplier");
        game_debug_show_filter_property_float(data.bilaterial, "distanceNormalizationFactor");
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.bilaterial_active);
}

bool platform_render_grayscale_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.grayscale_active;
    ImGui::PushID(0x10000000 | 0x2);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Grayscale", ImGuiTreeNodeFlags_None, "Grayscale");
    ImGui::TableSetColumnIndex(1);

    if (common_open) {
        game_debug_show_property("Active", data.grayscale_active);
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.grayscale_active);
}

bool platform_render_brightness_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.brightness_active;
    ImGui::PushID(0x10000000 | 0x3);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Brightness", ImGuiTreeNodeFlags_None, "Brightness");
    ImGui::TableSetColumnIndex(1);

    if (common_open) {
        game_debug_show_property("Active", data.brightness_active);
        game_debug_show_filter_property_float(data.brightness, "brightness_factor", 0.05f);
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.brightness_active);
}

bool platform_render_contrast_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.contrast_active;
    ImGui::PushID(0x10000000 | 0x4);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Contrast", ImGuiTreeNodeFlags_None, "Contrast");
    ImGui::TableSetColumnIndex(1);

    if (common_open) {
        game_debug_show_property("Active", data.contrast_active);
        game_debug_show_filter_property_float(data.contrast, "contrast", 0.05f);
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.contrast_active);
}

bool platform_render_saturation_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.saturation_active;
    ImGui::PushID(0x10000000 | 0x5);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Saturation", ImGuiTreeNodeFlags_None, "Saturation");
    ImGui::TableSetColumnIndex(1);

    if (common_open) {
        game_debug_show_property("Active", data.saturation_active);
        game_debug_show_filter_property_float(data.saturation, "saturation");
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.saturation_active);
}

bool platform_render_exposure_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.exposure_active;
    ImGui::PushID(0x10000000 | 0x6);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Exposure", ImGuiTreeNodeFlags_None, "Exposure");
    ImGui::TableSetColumnIndex(1);

    if (common_open) {
        game_debug_show_property("Active", data.exposure_active);
        if (data.exposure->hasProperty("exposure")) {
            game_debug_show_filter_property_float(data.exposure, "exposure");
        }
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.exposure_active);
}

bool platform_render_hue_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.hue_active;
    ImGui::PushID(0x10000000 | 0x7);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Hue", ImGuiTreeNodeFlags_None, "Hue");
    ImGui::TableSetColumnIndex(1);

    if (common_open) {
        game_debug_show_property("Active", data.hue_active);
        if (data.hue->hasProperty("hueAdjustment")) {
            game_debug_show_filter_property_float(data.hue, "hueAdjustment");
        }
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.hue_active);
}

bool platform_render_colorInvert_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.colorInvert_active;
    ImGui::PushID(0x10000000 | 0x8);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Color Invert", ImGuiTreeNodeFlags_None, "Color Invert");
    ImGui::TableSetColumnIndex(1);

    if (common_open) {
        game_debug_show_property("Active", data.colorInvert_active);
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.colorInvert_active);
}

bool platform_render_posterize_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.posterize_active;
    ImGui::PushID(0x10000000 | 0x9);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Posterize", ImGuiTreeNodeFlags_None, "Posterize");
    ImGui::TableSetColumnIndex(1);

    if (common_open) {
        game_debug_show_property("Active", data.posterize_active);
        if (data.posterize->hasProperty("colorLevels")) {
            game_debug_show_filter_property_float(data.posterize, "colorLevels");
        }
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.posterize_active);
}

bool platform_render_gaussianBlur_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.gaussianBlur_active;
    ImGui::PushID(0x10000000 | 0xA);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Gaussian Blur", ImGuiTreeNodeFlags_None, "Gaussian Blur");
    ImGui::TableSetColumnIndex(1);

    if (common_open) {
        game_debug_show_property("Active", data.gaussianBlur_active);
        if (data.gaussianBlur->hasProperty("radius")) {
            game_debug_show_filter_property_float(data.gaussianBlur, "radius");
        }
        if (data.gaussianBlur->hasProperty("sigma")) {
            game_debug_show_filter_property_float(data.gaussianBlur, "sigma");
        }
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.gaussianBlur_active);
}

bool platform_render_boxBlur_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.boxBlur_active;
    ImGui::PushID(0x10000000 | 0xB);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Box Blur", ImGuiTreeNodeFlags_None, "Box Blur");
    ImGui::TableSetColumnIndex(1);

    if (common_open) {
        game_debug_show_property("Active", data.boxBlur_active);
        if (data.boxBlur->hasProperty("radius")) {
            game_debug_show_filter_property_float(data.boxBlur, "radius");
        }
        if (data.boxBlur->hasProperty("sigma")) {
            game_debug_show_filter_property_float(data.boxBlur, "sigma");
        }
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.boxBlur_active);
}

void platform_render_proceed_filter(int w, int h, int format, const std::vector<uint8_t>&pixels, std::vector<uint8_t> &output_pixels) {
    auto &data = g_renderer_filter;

    data.sourceImage->init(w, h, SDL_BYTESPERPIXEL(format), (uint8_t *)pixels.data());
    data.sourceImage->proceed();

    output_pixels.resize(w * h * SDL_BYTESPERPIXEL(format));
    memcpy(output_pixels.data(), data.outputImage->getPixels(), w * h * SDL_BYTESPERPIXEL(format));
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

        bool changed = false;
        changed |= platform_render_bilaterial_options();
        changed |= platform_render_grayscale_options();
        changed |= platform_render_brightness_options();
        changed |= platform_render_contrast_options();
        changed |= platform_render_saturation_options();
        changed |= platform_render_exposure_options();
        changed |= platform_render_hue_options();
        changed |= platform_render_colorInvert_options();
        changed |= platform_render_posterize_options();
        changed |= platform_render_gaussianBlur_options();
        changed |= platform_render_boxBlur_options();
        
        filter_changed = changed;

        ImGui::EndTable();

        ImGui::TreePop();
    }

    if (filter_changed) {
        data.sourceImage->removeAllTargets();

        gpupixel::SourcePtr last = data.sourceImage;
        
        // Apply filters in order
        if (data.bilaterial_active) {
            last = last->addTarget(data.bilaterial);
        }
        if (data.grayscale_active) {
            last = last->addTarget(data.grayscale);
        }
        if (data.brightness_active) {
            last = last->addTarget(data.brightness);
        }
        if (data.contrast_active) {
            last = last->addTarget(data.contrast);
        }
        if (data.saturation_active) {
            last = last->addTarget(data.saturation);
        }
        if (data.exposure_active) {
            last = last->addTarget(data.exposure);
        }
        if (data.hue_active) {
            last = last->addTarget(data.hue);
        }
        if (data.colorInvert_active) {
            last = last->addTarget(data.colorInvert);
        }
        if (data.posterize_active) {
            last = last->addTarget(data.posterize);
        }
        if (data.gaussianBlur_active) {
            last = last->addTarget(data.gaussianBlur);
        }
        if (data.boxBlur_active) {
            last = last->addTarget(data.boxBlur);
        }

        last->addTarget(data.outputImage);
    }
}

#else

void platform_render_init_filters() {}
bool platform_render_support_filters() { return false; }
bool platform_render_any_filter_active() { return false; }
void platform_render_proceed_filter(int w, int h, int format, const std::vector<uint8_t> &pixels, std::vector<uint8_t> &output_pixels) {}
void platform_render_init_filter_context() {}
void config_load_filter_properties(bool) {}

#endif // 