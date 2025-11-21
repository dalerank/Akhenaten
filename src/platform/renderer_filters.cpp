#include "renderer.h"

#include "core/profiler.h"
#include "imgui.h"
#include "imgui_internal.h"
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
    
    gpupixel::FilterPtr beautyFace;
    bool beautyFace_active = false;
    
    gpupixel::FilterPtr blusher;
    bool blusher_active = false;
    
    gpupixel::FilterPtr boxDifference;
    bool boxDifference_active = false;
    
    gpupixel::FilterPtr boxMonoBlur;
    bool boxMonoBlur_active = false;
    
    gpupixel::FilterPtr cannyEdgeDetection;
    bool cannyEdgeDetection_active = false;
    
    gpupixel::FilterPtr crosshatch;
    bool crosshatch_active = false;
    
    gpupixel::FilterPtr emboss;
    bool emboss_active = false;
    
    gpupixel::FilterPtr faceReshape;
    bool faceReshape_active = false;
    
    gpupixel::FilterPtr glassSphere;
    bool glassSphere_active = false;
    
    gpupixel::FilterPtr halftone;
    bool halftone_active = false;
    
    gpupixel::FilterPtr lipstick;
    bool lipstick_active = false;
    
    gpupixel::FilterPtr nonMaximumSuppression;
    bool nonMaximumSuppression_active = false;
    
    gpupixel::FilterPtr pixellation;
    bool pixellation_active = false;
    
    gpupixel::FilterPtr rgb;
    bool rgb_active = false;
    
    gpupixel::FilterPtr smoothToon;
    bool smoothToon_active = false;
    
    gpupixel::FilterPtr toon;
    bool toon_active = false;
    
    gpupixel::FilterPtr weakPixelInclusion;
    bool weakPixelInclusion_active = false;
    
    gpupixel::FilterPtr whiteBalance;
    bool whiteBalance_active = false;
    
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
           data.boxBlur_active || data.beautyFace_active || 
           data.blusher_active || data.boxDifference_active || 
           data.boxMonoBlur_active || data.cannyEdgeDetection_active || 
           data.crosshatch_active || data.emboss_active || 
           data.faceReshape_active || data.glassSphere_active || 
           data.halftone_active || data.lipstick_active || 
           data.nonMaximumSuppression_active || data.pixellation_active || 
           data.rgb_active || data.smoothToon_active || data.toon_active || 
           data.weakPixelInclusion_active || data.whiteBalance_active;
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
        data.beautyFace = gpupixel::BeautyFaceFilter::Create();
        data.blusher = gpupixel::BlusherFilter::Create();
        data.boxDifference = gpupixel::BoxDifferenceFilter::Create();
        data.boxMonoBlur = gpupixel::BoxMonoBlurFilter::Create(gpupixel::GaussianBlurMonoFilter::HORIZONTAL);
        data.cannyEdgeDetection = gpupixel::CannyEdgeDetectionFilter::Create();
        data.crosshatch = gpupixel::CrosshatchFilter::Create();
        data.emboss = gpupixel::EmbossFilter::Create();
        data.faceReshape = gpupixel::FaceReshapeFilter::Create();
        data.glassSphere = gpupixel::GlassSphereFilter::Create();
        data.halftone = gpupixel::HalftoneFilter::Create();
        data.lipstick = gpupixel::LipstickFilter::Create();
        data.nonMaximumSuppression = gpupixel::NonMaximumSuppressionFilter::Create();
        data.pixellation = gpupixel::PixellationFilter::Create();
        data.rgb = gpupixel::RGBFilter::Create();
        data.smoothToon = gpupixel::SmoothToonFilter::Create();
        data.toon = gpupixel::ToonFilter::Create();
        data.weakPixelInclusion = gpupixel::WeakPixelInclusionFilter::Create();
        data.whiteBalance = gpupixel::WhiteBalanceFilter::Create();
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

bool platform_render_beautyFace_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.beautyFace_active;
    ImGui::PushID(0x10000000 | 0xC);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Beauty Face", ImGuiTreeNodeFlags_None, "Beauty Face");
    ImGui::TableSetColumnIndex(1);

    if (common_open) {
        game_debug_show_property("Active", data.beautyFace_active);
        if (data.beautyFace->hasProperty("whiteness")) {
            game_debug_show_filter_property_float(data.beautyFace, "whiteness", 0.05f);
        }
        if (data.beautyFace->hasProperty("skin_smoothing")) {
            game_debug_show_filter_property_float(data.beautyFace, "skin_smoothing", 0.05f);
        }
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.beautyFace_active);
}

bool platform_render_blusher_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.blusher_active;
    ImGui::PushID(0x10000000 | 0xD);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Blusher", ImGuiTreeNodeFlags_None, "Blusher");
    ImGui::TableSetColumnIndex(1);

    if (common_open) {
        game_debug_show_property("Active", data.blusher_active);
        if (data.blusher->hasProperty("blend_level")) {
            game_debug_show_filter_property_float(data.blusher, "blend_level", 0.05f);
        }
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.blusher_active);
}

bool platform_render_boxDifference_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.boxDifference_active;
    ImGui::PushID(0x10000000 | 0xE);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Box Difference", ImGuiTreeNodeFlags_None, "Box Difference");
    ImGui::TableSetColumnIndex(1);

    if (common_open) {
        game_debug_show_property("Active", data.boxDifference_active);
        // Note: BoxDifferenceFilter requires 2 input images, so it may not work correctly in current setup
        ImGui::Text("Note: Requires 2 input images");
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.boxDifference_active);
}

bool platform_render_boxMonoBlur_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.boxMonoBlur_active;
    ImGui::PushID(0x10000000 | 0xF);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Box Mono Blur", ImGuiTreeNodeFlags_None, "Box Mono Blur");
    ImGui::TableSetColumnIndex(1);

    if (common_open) {
        game_debug_show_property("Active", data.boxMonoBlur_active);
        ImGui::Text("Note: Horizontal direction only");
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.boxMonoBlur_active);
}

bool platform_render_cannyEdgeDetection_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.cannyEdgeDetection_active;
    ImGui::PushID(0x10000000 | 0x10);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Canny Edge Detection", ImGuiTreeNodeFlags_None, "Canny Edge Detection");
    ImGui::TableSetColumnIndex(1);

    if (common_open) {
        game_debug_show_property("Active", data.cannyEdgeDetection_active);
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.cannyEdgeDetection_active);
}

bool platform_render_crosshatch_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.crosshatch_active;
    ImGui::PushID(0x10000000 | 0x11);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Crosshatch", ImGuiTreeNodeFlags_None, "Crosshatch");
    ImGui::TableSetColumnIndex(1);

    if (common_open) {
        game_debug_show_property("Active", data.crosshatch_active);
        if (data.crosshatch->hasProperty("crossHatchSpacing")) {
            game_debug_show_filter_property_float(data.crosshatch, "crossHatchSpacing", 0.001f);
        }
        if (data.crosshatch->hasProperty("lineWidth")) {
            game_debug_show_filter_property_float(data.crosshatch, "lineWidth", 0.0001f);
        }
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.crosshatch_active);
}

bool platform_render_emboss_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.emboss_active;
    ImGui::PushID(0x10000000 | 0x12);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Emboss", ImGuiTreeNodeFlags_None, "Emboss");
    ImGui::TableSetColumnIndex(1);

    if (common_open) {
        game_debug_show_property("Active", data.emboss_active);
        if (data.emboss->hasProperty("intensity")) {
            game_debug_show_filter_property_float(data.emboss, "intensity", 0.1f);
        }
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.emboss_active);
}

bool platform_render_faceReshape_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.faceReshape_active;
    ImGui::PushID(0x10000000 | 0x13);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Face Reshape", ImGuiTreeNodeFlags_None, "Face Reshape");
    ImGui::TableSetColumnIndex(1);

    if (common_open) {
        game_debug_show_property("Active", data.faceReshape_active);
        if (data.faceReshape->hasProperty("thin_face")) {
            game_debug_show_filter_property_float(data.faceReshape, "thin_face", 0.05f);
        }
        if (data.faceReshape->hasProperty("big_eye")) {
            game_debug_show_filter_property_float(data.faceReshape, "big_eye", 0.05f);
        }
        ImGui::Text("Note: Requires face landmarks");
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.faceReshape_active);
}

bool platform_render_glassSphere_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.glassSphere_active;
    ImGui::PushID(0x10000000 | 0x14);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Glass Sphere", ImGuiTreeNodeFlags_None, "Glass Sphere");
    ImGui::TableSetColumnIndex(1);

    if (common_open) {
        game_debug_show_property("Active", data.glassSphere_active);
        if (data.glassSphere->hasProperty("positionX")) {
            game_debug_show_filter_property_float(data.glassSphere, "positionX", 0.01f);
        }
        if (data.glassSphere->hasProperty("positionY")) {
            game_debug_show_filter_property_float(data.glassSphere, "positionY", 0.01f);
        }
        if (data.glassSphere->hasProperty("radius")) {
            game_debug_show_filter_property_float(data.glassSphere, "radius", 0.01f);
        }
        if (data.glassSphere->hasProperty("refractiveIndex")) {
            game_debug_show_filter_property_float(data.glassSphere, "refractiveIndex", 0.01f);
        }
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.glassSphere_active);
}

bool platform_render_halftone_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.halftone_active;
    ImGui::PushID(0x10000000 | 0x15);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Halftone", ImGuiTreeNodeFlags_None, "Halftone");
    ImGui::TableSetColumnIndex(1);

    if (common_open) {
        game_debug_show_property("Active", data.halftone_active);
        if (data.halftone->hasProperty("pixelSize")) {
            game_debug_show_filter_property_float(data.halftone, "pixelSize", 0.001f);
        }
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.halftone_active);
}

bool platform_render_lipstick_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.lipstick_active;
    ImGui::PushID(0x10000000 | 0x16);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Lipstick", ImGuiTreeNodeFlags_None, "Lipstick");
    ImGui::TableSetColumnIndex(1);

    if (common_open) {
        game_debug_show_property("Active", data.lipstick_active);
        if (data.lipstick->hasProperty("blend_level")) {
            game_debug_show_filter_property_float(data.lipstick, "blend_level", 0.05f);
        }
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.lipstick_active);
}

bool platform_render_nonMaximumSuppression_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.nonMaximumSuppression_active;
    ImGui::PushID(0x10000000 | 0x17);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Non Maximum Suppression", ImGuiTreeNodeFlags_None, "Non Maximum Suppression");
    ImGui::TableSetColumnIndex(1);

    if (common_open) {
        game_debug_show_property("Active", data.nonMaximumSuppression_active);
        if (data.nonMaximumSuppression->hasProperty("texelSizeMultiplier")) {
            game_debug_show_filter_property_float(data.nonMaximumSuppression, "texelSizeMultiplier", 0.1f);
        }
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.nonMaximumSuppression_active);
}

bool platform_render_pixellation_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.pixellation_active;
    ImGui::PushID(0x10000000 | 0x18);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Pixellation", ImGuiTreeNodeFlags_None, "Pixellation");
    ImGui::TableSetColumnIndex(1);

    if (common_open) {
        game_debug_show_property("Active", data.pixellation_active);
        if (data.pixellation->hasProperty("pixelSize")) {
            game_debug_show_filter_property_float(data.pixellation, "pixelSize", 0.01f);
        }
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.pixellation_active);
}

bool platform_render_rgb_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.rgb_active;
    ImGui::PushID(0x10000000 | 0x19);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("RGB", ImGuiTreeNodeFlags_None, "RGB");
    ImGui::TableSetColumnIndex(1);

    if (common_open) {
        game_debug_show_property("Active", data.rgb_active);
        if (data.rgb->hasProperty("redAdjustment")) {
            game_debug_show_filter_property_float(data.rgb, "redAdjustment", 0.05f);
        }
        if (data.rgb->hasProperty("greenAdjustment")) {
            game_debug_show_filter_property_float(data.rgb, "greenAdjustment", 0.05f);
        }
        if (data.rgb->hasProperty("blueAdjustment")) {
            game_debug_show_filter_property_float(data.rgb, "blueAdjustment", 0.05f);
        }
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.rgb_active);
}

bool platform_render_smoothToon_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.smoothToon_active;
    ImGui::PushID(0x10000000 | 0x1A);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Smooth Toon", ImGuiTreeNodeFlags_None, "Smooth Toon");
    ImGui::TableSetColumnIndex(1);

    if (common_open) {
        game_debug_show_property("Active", data.smoothToon_active);
        if (data.smoothToon->hasProperty("blurRadius")) {
            game_debug_show_filter_property_float(data.smoothToon, "blurRadius", 0.5f);
        }
        if (data.smoothToon->hasProperty("toonThreshold")) {
            game_debug_show_filter_property_float(data.smoothToon, "toonThreshold", 0.01f);
        }
        if (data.smoothToon->hasProperty("toonQuantizationLevels")) {
            game_debug_show_filter_property_float(data.smoothToon, "toonQuantizationLevels", 0.5f);
        }
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.smoothToon_active);
}

bool platform_render_toon_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.toon_active;
    ImGui::PushID(0x10000000 | 0x1B);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Toon", ImGuiTreeNodeFlags_None, "Toon");
    ImGui::TableSetColumnIndex(1);

    if (common_open) {
        game_debug_show_property("Active", data.toon_active);
        if (data.toon->hasProperty("threshold")) {
            game_debug_show_filter_property_float(data.toon, "threshold", 0.01f);
        }
        if (data.toon->hasProperty("quantizationLevels")) {
            game_debug_show_filter_property_float(data.toon, "quantizationLevels", 0.5f);
        }
        if (data.toon->hasProperty("texelSizeMultiplier")) {
            game_debug_show_filter_property_float(data.toon, "texelSizeMultiplier", 0.1f);
        }
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.toon_active);
}

bool platform_render_weakPixelInclusion_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.weakPixelInclusion_active;
    ImGui::PushID(0x10000000 | 0x1C);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("Weak Pixel Inclusion", ImGuiTreeNodeFlags_None, "Weak Pixel Inclusion");
    ImGui::TableSetColumnIndex(1);

    if (common_open) {
        game_debug_show_property("Active", data.weakPixelInclusion_active);
        if (data.weakPixelInclusion->hasProperty("texelSizeMultiplier")) {
            game_debug_show_filter_property_float(data.weakPixelInclusion, "texelSizeMultiplier", 0.1f);
        }
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.weakPixelInclusion_active);
}

bool platform_render_whiteBalance_options() {
    auto &data = g_renderer_filter;

    bool save_active = data.whiteBalance_active;
    ImGui::PushID(0x10000000 | 0x1D);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx("White Balance", ImGuiTreeNodeFlags_None, "White Balance");
    ImGui::TableSetColumnIndex(1);

    if (common_open) {
        game_debug_show_property("Active", data.whiteBalance_active);
        if (data.whiteBalance->hasProperty("temperature")) {
            game_debug_show_filter_property_float(data.whiteBalance, "temperature", 100.0f);
        }
        if (data.whiteBalance->hasProperty("tint")) {
            game_debug_show_filter_property_float(data.whiteBalance, "tint", 1.0f);
        }
        ImGui::TreePop();
    }

    ImGui::PopID();

    return (save_active != data.whiteBalance_active);
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
        changed |= platform_render_beautyFace_options();
        changed |= platform_render_blusher_options();
        changed |= platform_render_boxDifference_options();
        changed |= platform_render_boxMonoBlur_options();
        changed |= platform_render_cannyEdgeDetection_options();
        changed |= platform_render_crosshatch_options();
        changed |= platform_render_emboss_options();
        changed |= platform_render_faceReshape_options();
        changed |= platform_render_glassSphere_options();
        changed |= platform_render_halftone_options();
        changed |= platform_render_lipstick_options();
        changed |= platform_render_nonMaximumSuppression_options();
        changed |= platform_render_pixellation_options();
        changed |= platform_render_rgb_options();
        changed |= platform_render_smoothToon_options();
        changed |= platform_render_toon_options();
        changed |= platform_render_weakPixelInclusion_options();
        changed |= platform_render_whiteBalance_options();
        
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
        if (data.beautyFace_active) {
            last = last->addTarget(data.beautyFace);
        }
        if (data.blusher_active) {
            last = last->addTarget(data.blusher);
        }
        if (data.boxDifference_active) {
            // Note: BoxDifferenceFilter requires 2 inputs, may need special handling
            last = last->addTarget(data.boxDifference);
        }
        if (data.boxMonoBlur_active) {
            last = last->addTarget(data.boxMonoBlur);
        }
        if (data.cannyEdgeDetection_active) {
            last = last->addTarget(data.cannyEdgeDetection);
        }
        if (data.crosshatch_active) {
            last = last->addTarget(data.crosshatch);
        }
        if (data.emboss_active) {
            last = last->addTarget(data.emboss);
        }
        if (data.faceReshape_active) {
            last = last->addTarget(data.faceReshape);
        }
        if (data.glassSphere_active) {
            last = last->addTarget(data.glassSphere);
        }
        if (data.halftone_active) {
            last = last->addTarget(data.halftone);
        }
        if (data.lipstick_active) {
            last = last->addTarget(data.lipstick);
        }
        if (data.nonMaximumSuppression_active) {
            last = last->addTarget(data.nonMaximumSuppression);
        }
        if (data.pixellation_active) {
            last = last->addTarget(data.pixellation);
        }
        if (data.rgb_active) {
            last = last->addTarget(data.rgb);
        }
        if (data.smoothToon_active) {
            last = last->addTarget(data.smoothToon);
        }
        if (data.toon_active) {
            last = last->addTarget(data.toon);
        }
        if (data.weakPixelInclusion_active) {
            last = last->addTarget(data.weakPixelInclusion);
        }
        if (data.whiteBalance_active) {
            last = last->addTarget(data.whiteBalance);
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