/*
 * GPUPixel
 *
 * Created by PixPark on 2021/6/24.
 * Copyright © 2021 PixPark. All rights reserved.
 */

#include "pixellation_filter.h"
#include "gpupixel_context.h"

NS_GPUPIXEL_BEGIN

#if defined(GPUPIXEL_GLES_SHADER) || defined(GPUPIXEL_MAC)
const std::string kPixellationFragmentShaderString = R"(
    uniform highp float pixelSize; uniform highp float aspectRatio;

    uniform sampler2D inputImageTexture;
    varying highp vec2 textureCoordinate;

    void main() {
      highp vec2 pixelSizeVec = vec2(pixelSize, pixelSize / aspectRatio);
      highp vec2 samplePos =
          floor(textureCoordinate / pixelSizeVec) * pixelSizeVec +
          0.5 * pixelSizeVec;
      gl_FragColor = texture2D(inputImageTexture, samplePos);
    })";
#elif defined(GPUPIXEL_WIN) || defined(GPUPIXEL_MAC) || defined(GPUPIXEL_LINUX)
const std::string kPixellationFragmentShaderString = R"(
    uniform float pixelSize; uniform float aspectRatio;

    uniform sampler2D inputImageTexture;
    varying vec2 textureCoordinate;

    void main() {
      vec2 pixelSizeVec = vec2(pixelSize, pixelSize / aspectRatio);
      vec2 samplePos =
          floor(textureCoordinate / pixelSizeVec) * pixelSizeVec +
          0.5 * pixelSizeVec;
      gl_FragColor = texture2D(inputImageTexture, samplePos);
    })";
#endif

std::shared_ptr<PixellationFilter> PixellationFilter::Create() {
  auto ret = std::shared_ptr<PixellationFilter>(new PixellationFilter());
  gpupixel::GPUPixelContext::getInstance()->runSync([&] {
    if (ret && !ret->Init()) {
      ret.reset();
    }
  });
  return ret;
}

bool PixellationFilter::Init() {
  if (!initWithFragmentShaderString(kPixellationFragmentShaderString)) {
    return false;
  }

  pixel_size_ = 0.1;
  registerProperty(
      "pixelSize", pixel_size_,
      "The size of a pixel that you want to pixellate, ranges from 0 to 1.",
      [this](float& pixelSize) { setPixelSize(pixelSize); });

  return true;
}

void PixellationFilter::setPixelSize(float pixelSize) {
  pixel_size_ = pixelSize;
  if (pixel_size_ > 1.0) {
    pixel_size_ = 1.0;
  } else if (pixel_size_ < 0.0) {
    pixel_size_ = 0.0;
  }
}

bool PixellationFilter::proceed(bool updateSinks, int64_t frametime) {
  float aspectRatio = 1.0;
  FramebufferPtr firstInputFramebuffer =
      _inputFramebuffers.begin()->second.frameBuffer;
  aspectRatio = firstInputFramebuffer->getHeight() /
                (float)(firstInputFramebuffer->getWidth());
  _filterProgram->setUniformValue("aspectRatio", aspectRatio);

  float pixelSize = pixel_size_;
  float singlePixelWidth = 1.0 / firstInputFramebuffer->getWidth();
  if (pixelSize < singlePixelWidth) {
    pixelSize = singlePixelWidth;
  }
  _filterProgram->setUniformValue("pixelSize", pixelSize);

  return Filter::proceed(updateSinks, frametime);
}

NS_GPUPIXEL_END
