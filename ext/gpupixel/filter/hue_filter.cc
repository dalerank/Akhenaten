/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#include "hue_filter.h"
#include "gpupixel_context.h"
#include "../utils/math_toolbox.h"
NS_GPUPIXEL_BEGIN

// Adapted from
// http://stackoverflow.com/questions/9234724/how-to-change-hue-of-a-texture-with-glsl
// - see for code and discussion
#if defined(GPUPIXEL_GLES_SHADER) || defined(GPUPIXEL_MAC)
const std::string kHueFragmentShaderString = R"(
    precision highp float; uniform sampler2D inputImageTexture;
    uniform mediump float hueAdjustment;
    varying highp vec2 textureCoordinate;
    const highp vec4 kRGBToYPrime = vec4(0.299, 0.587, 0.114, 0.0);
    const highp vec4 kRGBToI = vec4(0.595716, -0.274453, -0.321263, 0.0);
    const highp vec4 kRGBToQ = vec4(0.211456, -0.522591, 0.31135, 0.0);
    const highp vec4 kYIQToR = vec4(1.0, 0.9563, 0.6210, 0.0);
    const highp vec4 kYIQToG = vec4(1.0, -0.2721, -0.6474, 0.0);
    const highp vec4 kYIQToB = vec4(1.0, -1.1070, 1.7046, 0.0);

    void main() {
      // Sample the input pixel
      highp vec4 color = texture2D(inputImageTexture, textureCoordinate);

      // Convert to YIQ
      highp float YPrime = dot(color, kRGBToYPrime);
      highp float I = dot(color, kRGBToI);
      highp float Q = dot(color, kRGBToQ);

      // Calculate the hue and chroma
      highp float hue = atan(Q, I);
      highp float chroma = sqrt(I * I + Q * Q);

      // Make the user's adjustments
      hue += (-hueAdjustment);  // why negative rotation?

      // Convert back to YIQ
      Q = chroma * sin(hue);
      I = chroma * cos(hue);

      // Convert back to RGB
      highp vec4 yIQ = vec4(YPrime, I, Q, 0.0);
      color.r = dot(yIQ, kYIQToR);
      color.g = dot(yIQ, kYIQToG);
      color.b = dot(yIQ, kYIQToB);

      // Save the result
      gl_FragColor = color;
    })";
#elif defined(GPUPIXEL_WIN) || defined(GPUPIXEL_MAC) || defined(GPUPIXEL_LINUX)
const std::string kHueFragmentShaderString = R"(
    uniform sampler2D inputImageTexture;
    uniform float hueAdjustment;
    varying vec2 textureCoordinate;
    const vec4 kRGBToYPrime = vec4(0.299, 0.587, 0.114, 0.0);
    const vec4 kRGBToI = vec4(0.595716, -0.274453, -0.321263, 0.0);
    const vec4 kRGBToQ = vec4(0.211456, -0.522591, 0.31135, 0.0);
    const vec4 kYIQToR = vec4(1.0, 0.9563, 0.6210, 0.0);
    const vec4 kYIQToG = vec4(1.0, -0.2721, -0.6474, 0.0);
    const vec4 kYIQToB = vec4(1.0, -1.1070, 1.7046, 0.0);

    void main() {
      // Sample the input pixel
      vec4 color = texture2D(inputImageTexture, textureCoordinate);

      // Convert to YIQ
      float YPrime = dot(color, kRGBToYPrime);
      float I = dot(color, kRGBToI);
      float Q = dot(color, kRGBToQ);

      // Calculate the hue and chroma
      float hue = atan(Q, I);
      float chroma = sqrt(I * I + Q * Q);

      // Make the user's adjustments
      hue += (-hueAdjustment);  // why negative rotation?

      // Convert back to YIQ
      Q = chroma * sin(hue);
      I = chroma * cos(hue);

      // Convert back to RGB
      vec4 yIQ = vec4(YPrime, I, Q, 0.0);
      color.r = dot(yIQ, kYIQToR);
      color.g = dot(yIQ, kYIQToG);
      color.b = dot(yIQ, kYIQToB);

      // Save the result
      gl_FragColor = color;
    })";
#endif

std::shared_ptr<HueFilter> HueFilter::Create() {
  auto ret = std::shared_ptr<HueFilter>(new HueFilter());
  gpupixel::GPUPixelContext::getInstance()->runSync([&] {
    if (ret && !ret->Init()) {
      ret.reset();
    }
  });
  return ret;
}

bool HueFilter::Init() {
  if (!initWithFragmentShaderString(kHueFragmentShaderString)) {
    return false;
  }

  hue_adjustment_ = 90;
  registerProperty(
      "hueAdjustment", hue_adjustment_,
      "The hueAdjustment (in degree) of the image",
      [this](float& hueAdjustment) { setHueAdjustment(hueAdjustment); });

  return true;
}

void HueFilter::setHueAdjustment(float hueAdjustment) {
  // Convert degrees to radians for hue rotation
  hue_adjustment_ = fmodf(hueAdjustment, 360.0) * M_PI / 180;
}

bool HueFilter::proceed(bool updateSinks, int64_t frametime) {
  _filterProgram->setUniformValue("hueAdjustment", hue_adjustment_);
  return Filter::proceed(updateSinks, frametime);
}

NS_GPUPIXEL_END
