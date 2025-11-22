/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#include "contrast_filter.h"
#include "gpupixel_context.h"

NS_GPUPIXEL_BEGIN

#if defined(GPUPIXEL_GLES_SHADER) || defined(GPUPIXEL_MAC)
const std::string kContrastFragmentShaderString = R"(
    uniform sampler2D inputImageTexture; uniform lowp float contrast;
    varying highp vec2 textureCoordinate;

    void main() {
      lowp vec4 color = texture2D(inputImageTexture, textureCoordinate);
      gl_FragColor =
          vec4(((color.rgb - vec3(0.5)) * contrast + vec3(0.5)), color.a);
    })";
#elif defined(GPUPIXEL_WIN) || defined(GPUPIXEL_MAC) || defined(GPUPIXEL_LINUX)
const std::string kContrastFragmentShaderString = R"(
    uniform sampler2D inputImageTexture; uniform float contrast;
    varying vec2 textureCoordinate;

    void main() {
      vec4 color = texture2D(inputImageTexture, textureCoordinate);
      gl_FragColor =
          vec4(((color.rgb - vec3(0.5)) * contrast + vec3(0.5)), color.a);
    })";
#endif

std::shared_ptr<ContrastFilter> ContrastFilter::Create() {
    auto ret = std::shared_ptr<ContrastFilter>(new ContrastFilter());
    gpupixel::GPUPixelContext::getInstance()->runSync([&] {
        if (ret && !ret->Init()) {
            ret.reset();
        }
    });
    return ret;
}

bool ContrastFilter::Init() {
    if (!initWithFragmentShaderString(kContrastFragmentShaderString)) {
        return false;
    }

    contrast_factor_ = 1.0;
    registerProperty("contrast", contrast_factor_,
        "The contrast of the image. Contrast ranges from 0.0 to 4.0 "
        "(max contrast), with 1.0 as the normal level",
        [this] (float &contrast) { setContrast(contrast); });

    return true;
}

void ContrastFilter::setContrast(float contrast) {
    contrast_factor_ = contrast;
    if (contrast_factor_ > 4.0) {
        contrast_factor_ = 4.0;
    } else if (contrast_factor_ < 0.0) {
        contrast_factor_ = 0.0;
    }
}

bool ContrastFilter::proceed(bool updateSinks, int64_t frametime) {
    _filterProgram->setUniformValue("contrast", contrast_factor_);
    return Filter::proceed(updateSinks, frametime);
}

NS_GPUPIXEL_END
