/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#include "exposure_filter.h"
#include "gpupixel_context.h"

NS_GPUPIXEL_BEGIN

#if defined(GPUPIXEL_GLES_SHADER) || defined(GPUPIXEL_MAC)
const std::string kExposureFragmentShaderString = R"(
    uniform sampler2D inputImageTexture; uniform lowp float exposure;
    varying highp vec2 textureCoordinate;

    void main() {
      lowp vec4 color = texture2D(inputImageTexture, textureCoordinate);
      gl_FragColor = vec4(color.rgb * pow(2.0, exposure), color.a);
    })";
#elif defined(GPUPIXEL_WIN) || defined(GPUPIXEL_MAC) || defined(GPUPIXEL_LINUX)
const std::string kExposureFragmentShaderString = R"(
    uniform sampler2D inputImageTexture; uniform float exposure;
    varying vec2 textureCoordinate;

    void main() {
      vec4 color = texture2D(inputImageTexture, textureCoordinate);
      gl_FragColor = vec4(color.rgb * pow(2.0, exposure), color.a);
    })";
#endif

std::shared_ptr<ExposureFilter> ExposureFilter::Create() {
  auto ret = std::shared_ptr<ExposureFilter>(new ExposureFilter());
  gpupixel::GPUPixelContext::getInstance()->runSync([&] {
    if (ret && !ret->Init()) {
      ret.reset();
    }
  });
  return ret;
}

bool ExposureFilter::Init() {
  if (!initWithFragmentShaderString(kExposureFragmentShaderString)) {
    return false;
  }

  exposure_factor_ = 0.0;
  registerProperty("exposure", exposure_factor_,
                   "The exposure of the image. Exposure ranges from -10.0 to "
                   "10.0 (max contrast), with 0.0 as the normal level",
                   [this](float& exposure) { SetExposure(exposure); });

  return true;
}

void ExposureFilter::SetExposure(float exposure) {
  exposure_factor_ = exposure;
  if (exposure_factor_ > 10.0) {
    exposure_factor_ = 10.0;
  } else if (exposure_factor_ < -10.0) {
    exposure_factor_ = -10.0;
  }
}

bool ExposureFilter::proceed(bool updateSinks, int64_t frametime) {
  _filterProgram->setUniformValue("exposure", exposure_factor_);
  return Filter::proceed(updateSinks, frametime);
}

NS_GPUPIXEL_END
