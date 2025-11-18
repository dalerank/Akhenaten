/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#include "saturation_filter.h"
#include "gpupixel_context.h"

NS_GPUPIXEL_BEGIN

#if defined(GPUPIXEL_GLES_SHADER) || defined(GPUPIXEL_MAC)
const std::string kSaturationFragmentShaderString = R"(
    uniform sampler2D inputImageTexture; uniform lowp float saturation;
    varying highp vec2 textureCoordinate;

    // Values from "Graphics Shaders: Theory and Practice" by Bailey and
    // Cunningham
    const mediump vec3 luminanceWeighting = vec3(0.2125, 0.7154, 0.0721);

    void main() {
      lowp vec4 color = texture2D(inputImageTexture, textureCoordinate);
      lowp float luminance = dot(color.rgb, luminanceWeighting);
      lowp vec3 greyScaleColor = vec3(luminance);

      gl_FragColor = vec4(mix(greyScaleColor, color.rgb, saturation), color.a);
    })";
#elif defined(GPUPIXEL_WIN) || defined(GPUPIXEL_MAC) || defined(GPUPIXEL_LINUX)
const std::string kSaturationFragmentShaderString = R"(
    uniform sampler2D inputImageTexture; uniform float saturation;
    varying vec2 textureCoordinate;

    // Values from "Graphics Shaders: Theory and Practice" by Bailey and
    // Cunningham
    const vec3 luminanceWeighting = vec3(0.2125, 0.7154, 0.0721);

    void main() {
      vec4 color = texture2D(inputImageTexture, textureCoordinate);
      float luminance = dot(color.rgb, luminanceWeighting);
      vec3 greyScaleColor = vec3(luminance);

      gl_FragColor = vec4(mix(greyScaleColor, color.rgb, saturation), color.a);
    })";
#endif

std::shared_ptr<SaturationFilter> SaturationFilter::Create() {
  auto ret = std::shared_ptr<SaturationFilter>(new SaturationFilter());
  gpupixel::GPUPixelContext::getInstance()->runSync([&] {
    if (ret && !ret->Init()) {
      ret.reset();
    }
  });
  return ret;
}

bool SaturationFilter::Init() {
  if (!initWithFragmentShaderString(kSaturationFragmentShaderString)) {
    return false;
  }

  saturation_ = 1.0;
  registerProperty(
      "saturation", saturation_,
      "The saturation of an image. Saturation ranges from 0.0 (fully "
      "desaturated) to 2.0 (max saturation), with 1.0 as the normal level",
      [this](float& saturation) { setSaturation(saturation); });

  return true;
}

void SaturationFilter::setSaturation(float saturation) {
  saturation_ = saturation;
  if (saturation_ > 2.0) {
    saturation_ = 2.0;
  } else if (saturation_ < 0.0) {
    saturation_ = 0.0;
  }
}

bool SaturationFilter::proceed(bool updateSinks, int64_t frametime) {
  _filterProgram->setUniformValue("saturation", saturation_);
  return Filter::proceed(updateSinks, frametime);
}

NS_GPUPIXEL_END
