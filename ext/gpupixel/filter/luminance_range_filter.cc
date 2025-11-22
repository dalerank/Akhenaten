/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#include "luminance_range_filter.h"
#include "gpupixel_context.h"

NS_GPUPIXEL_BEGIN

#if defined(GPUPIXEL_GLES_SHADER)
const std::string kLuminanceRangeFragmentShaderString = R"(
    uniform sampler2D inputImageTexture;
    uniform lowp float rangeReductionFactor;
    varying highp vec2 textureCoordinate;

    // Values from "Graphics Shaders: Theory and Practice" by Bailey and
    // Cunningham
    const mediump vec3 luminanceWeighting = vec3(0.2125, 0.7154, 0.0721);

    void main() {
      lowp vec4 color = texture2D(inputImageTexture, textureCoordinate);
      mediump float luminance = dot(color.rgb, luminanceWeighting);
      mediump float luminanceRatio = ((0.5 - luminance) * rangeReductionFactor);
      gl_FragColor = vec4((color.rgb) + (luminanceRatio), color.a);
    })";
#else
const std::string kLuminanceRangeFragmentShaderString = R"(
    uniform sampler2D inputImageTexture; uniform float rangeReductionFactor;
    varying vec2 textureCoordinate;

    // Values from "Graphics Shaders: Theory and Practice" by Bailey and
    // Cunningham
    const vec3 luminanceWeighting = vec3(0.2125, 0.7154, 0.0721);

    void main() {
      vec4 color = texture2D(inputImageTexture, textureCoordinate);
      float luminance = dot(color.rgb, luminanceWeighting);
      float luminanceRatio = ((0.5 - luminance) * rangeReductionFactor);
      gl_FragColor = vec4((color.rgb) + (luminanceRatio), color.a);
    })";
#endif

std::shared_ptr<LuminanceRangeFilter> LuminanceRangeFilter::Create() {
  auto ret = std::shared_ptr<LuminanceRangeFilter>(new LuminanceRangeFilter());
  gpupixel::GPUPixelContext::getInstance()->runSync([&] {
    if (ret && !ret->Init()) {
      ret.reset();
    }
  });
  return ret;
}

bool LuminanceRangeFilter::Init() {
  if (!initWithFragmentShaderString(kLuminanceRangeFragmentShaderString)) {
    return false;
  }

  range_reduction_factor_ = 0.6;
  registerProperty("rangeReductionFactor", range_reduction_factor_,
                   "The degree to reduce the luminance range, from 0.0 to 1.0. "
                   "Default is 0.6.",
                   [this](float& rangeReductionFactor) {
                     setRangeReductionFactor(rangeReductionFactor);
                   });

  return true;
}

void LuminanceRangeFilter::setRangeReductionFactor(float rangeReductionFactor) {
  range_reduction_factor_ = rangeReductionFactor;
  if (range_reduction_factor_ > 1.0) {
    range_reduction_factor_ = 1.0;
  } else if (range_reduction_factor_ < 0.0) {
    range_reduction_factor_ = 0.0;
  }
}

bool LuminanceRangeFilter::proceed(bool updateSinks, int64_t frametime) {
  _filterProgram->setUniformValue("rangeReductionFactor",
                                   range_reduction_factor_);
  return Filter::proceed(updateSinks, frametime);
}

NS_GPUPIXEL_END
